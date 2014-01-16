#!/usr/bin/python
# -*- coding: utf-8 -*-
import os, sys, shutil, tempfile
import threading
import pywapi
import string
import locale
import urllib2, urllib
from urllib import urlencode
from xml.dom.minidom import parseString
import re
import json
import datetime
import calendar
from pytz import timezone
import pytz
import time
import math

#weather_com_result = pywapi.get_weather_from_weather_com('10001')
#yahoo_result = pywapi.get_weather_from_yahoo('10001')
#print weather_com_result
#print yahoo_result
class NumberFormatter:
    """
    Formats a number with respect to the locale settings
    """

    # regex to remove trailing zeros
    re_trailing_zeros = None
    # regex to replace -0
    re_minus_zero = re.compile("^-0$")

    def format_float(self, value, precision = 1):
        """
        Formats a float with current locale's conventions (decimal point &
        grouping), with specified precision.
        It strips trailing zeros after the decimal point and replaces -0 with 0.
        """
        p = int(precision)
        v = float(value)
        s = locale.format("%.*f", (p, v), True)
        if p > 0:
            # compile regex if needed
            if NumberFormatter.re_trailing_zeros is None:
                try: dp = locale.localeconv().get('decimal_point', '.')
                except: dp = '.'
                NumberFormatter.re_trailing_zeros = re.compile(dp + "?0+$")

            s = NumberFormatter.re_trailing_zeros.sub('', s)
        return NumberFormatter.re_minus_zero.sub('0', s)


class YahooWeather(threading.Thread):
    # Available conditions by yahoo condition code
    # Format: condition code: (day icon, night icon, is a severe weather condition, localized condition name)
    _YahooConditions = {
        '0' : ("weather-storm",             "weather-storm",            True,  "Tornado"),
        '1' : ("weather-storm",             "weather-storm",            True,  "Tropical storm"),
        '2' : ("weather-storm",             "weather-storm",            True,  "Hurricane"),
        '3' : ("weather-storm",             "weather-storm",            True,  "Severe thunderstorms"),
        '4' : ("weather-storm",             "weather-storm",            True,  "Thunderstorms"),
        '5' : ("weather-snow",              "weather-snow",             False, "Mixed rain and snow"),
        # Use American meaning of sleet - see http://en.wikipedia.org/wiki/Sleet
        '6' : ("weather-showers",           "weather-showers",          False, "Mixed rain and sleet"),
        '7' : ("weather-snow",              "weather-snow",             False, "Mixed snow and sleet"),
        '8' : ("weather-showers",           "weather-showers",          False, "Freezing drizzle"),
        '9' : ("weather-showers",           "weather-showers",          False, "Drizzle"),
        '10': ("weather-snow",              "weather-snow",             False, "Freezing rain"),
        '11': ("weather-showers",           "weather-showers",          False, "Showers"),
        '12': ("weather-showers",           "weather-showers",          False, "Showers"),
        '13': ("weather-snow",              "weather-snow",             False, "Snow flurries"),
        '14': ("weather-snow",              "weather-snow",             False, "Light snow showers"),
        '15': ("weather-snow",              "weather-snow",             False, "Blowing snow"),
        '16': ("weather-snow",              "weather-snow",             False, "Snow"),
        '17': ("weather-showers",           "weather-showers",          False, "Hail"),
        '18': ("weather-snow",              "weather-snow",             False, "Sleet"),
        '19': ("weather-fog",               "weather-fog",              False, "Dust"),
        '20': ("weather-fog",               "weather-fog",              False, "Foggy"),
        '21': ("weather-fog",               "weather-fog",              False, "Haze"),
        '22': ("weather-fog",               "weather-fog",              False, "Smoky"),
        '23': ("weather-clear",             "weather-clear-night",      False, "Blustery"),
        '24': ("weather-clear",             "weather-clear-night",      False, "Windy"),
        '25': ("weather-clear",             "weather-clear-night",      False, "Cold"),
        '26': ("weather-clouds",            "weather-clouds-night",     False, "Cloudy"),
        '27': ("weather-clouds",            "weather-clouds-night",     False, "Mostly cloudy"),
        '28': ("weather-clouds",            "weather-clouds-night",     False, "Mostly cloudy"),
        '29': ("weather-few-clouds",        "weather-few-clouds-night", False, "Partly cloudy"),
        '30': ("weather-few-clouds",        "weather-few-clouds-night", False, "Partly cloudy"),
        '31': ("weather-clear",             "weather-clear-night",      False, "Clear"),
        '32': ("weather-clear",             "weather-clear-night",      False, "Sunny"),
        '33': ("weather-clear",             "weather-clear-night",      False, "Fair"),
        '34': ("weather-clear",               "weather-clear-night",      False, "Fair"),
        '35': ("weather-showers-scattered",   "weather-showers-scattered",False, "Mixed rain and hail"),
        '36': ("weather-clear",               "weather-clear-night",      False, "Hot"),
        '37': ("weather-storm",               "weather-storm",            True,  "Isolated thunderstorms"),
        '38': ("weather-storm",               "weather-storm",            True,  "Scattered thunderstorms"),
        '39': ("weather-storm",               "weather-storm",            True,  "Scattered thunderstorms"),
        '40': ("weather-showers-scattered",   "weather-showers-scattered",False, "Scattered showers"),
        '41': ("weather-snow",                "weather-snow",             False, "Heavy snow"),
        '42': ("weather-snow",                "weather-snow",             False, "Scattered snow showers"),
        '43': ("weather-snow",                "weather-snow",             False, "Heavy snow"),
        '44': ("weather-few-clouds",          "weather-few-clouds-night", False, "Partly cloudy"),
        '45': ("weather-storm",               "weather-storm",            True,  "Thundershowers"),
        '46': ("weather-snow",                "weather-snow",             False, "Snow showers"),
        '47': ("weather-storm",               "weather-storm",            True,  "Isolated thundershowers"),
        #'3200': (False,                     False,                      False, "Unknown condition")
        '3200': ("weather-indicator-unknown", "weather-indicator-unknown", False, "Unknown condition"),
        '9999': ("weather-indicator-error", "weather-indicator-error", False, "Network connection unavailable")
    }

    # Available conditions by Weather.com condition code; same as Yahoo
    _WeathercomConditions = _YahooConditions
    def __init__(self, sessionDaemon):
        threading.Thread.__init__(self)
        self.sessionDaemon = sessionDaemon
        self.cityName = None
        self.geonameId = None
        self.__lat = None
        self.__lon = None
        self.code = ''
        self.locale_name = ''
        self.get_locale()
        self.weatherData = {}
        self.forecastData = {}

    def get_locale(self):
        (localeName, encode) = locale.getdefaultlocale()
        print 'locale...'
        print localeName
        if localeName is not None:
            self.locale_name = localeName.split('_')[0]
            print 'aaa1'
            print self.locale_name
        else:
            #locale.setlocale(locale.LC_ALL, 'C') # use default (C) locale
            self.locale_name = 'en'
            print 'aaa2'
            print self.locale_name

    def get_weather(self, id):
        #self.prepare_time_zone()
        self.yahoo_result = pywapi.get_weather_from_yahoo(id, self.locale_name)#'CHXX0008'  2151330         10001   USNY0996
        self.get_temperature_unit()
        self.deal_with_test()
        #fp = open("/tmp/yahoo1.txt", "w")
        #print >> fp, "--------------"
        #print >> fp, self.yahoo_result
        #fp.close()
        self.sessionDaemon.access_weather('yahoo', 'kobe')
        #print self.yahoo_result

    # Get current weather
    def getYahooCurrentWeather(self, latlon, cityId):
        cityIdStr = str(cityId)
        self.__lat = latlon[0]
        self.__lon = latlon[1]
        threading.Thread(target=self.get_weather, args=(cityIdStr,), name='YahooWeather').start()

    def get_current_yahoo_weather_dict(self):
        self.weatherData.clear()
        #self.get_sun_data()
        #print self.get_icon_name()
        self.weatherData['code'] = self.code
        self.weatherData['city'] = self.get_city()
        self.weatherData['temp'] = self.get_temperature()
        #self.weatherData['humidity'] = self.get_humidity()
        #self.weatherData['pressure'] = self.get_pressure()
        #self.weatherData['visibility'] = self.get_visibility()
        self.weatherData['text'] = self.get_weather_text()
        self.weatherData['time'] = self.get_release_time()
        self.weatherData['wind'] = self.get_wind()
        (self.weatherData['sunrise'], self.weatherData['sunset']) = self.get_sun()
        #fp = open("/tmp/yahoo2.txt", "w")
        #print >> fp, "--------------"
        #print >> fp, self.weatherData
        #fp.close()
        return self.weatherData

    def deal_with_test(self):
        if 'error' in self.yahoo_result:
            icon_name = '9999'
        elif 'condition' not in self.yahoo_result:
            icon_name = '3200'
        elif 'code' in self.yahoo_result['condition']:
            icon_name = self.yahoo_result['condition']['code']
        else:
            icon_name = '3200'
        self.__current_condition = self._YahooConditions.get(icon_name)
        self.code = icon_name
        print self.__current_condition

    #def get_sun_data(self):
    #    """ Get sunrise/sunset times and calculate whether it is night already """
    #    self.__night = False
    #    self.__sunrise_t = None
    #    self.__sunset_t = None
    #    self.__time_zone = timezone(self.timezoneId)

        # Grab local datetime from earthtools.org
    #    url = 'http://www.earthtools.org/timezone-1.1/%s/%s' % \
    #        (self.__lat, self.__lon)#(self.__lat, self.__lon)
    #    try:
    #        print "11Weather: Get local datetime, url %s" % url
    #        handler = urllib2.urlopen(url)
    #    except urllib2.URLError:
    #        print "22Weather: error reaching url '%s'" % url
    #        return

    #    content_type = handler.info().dict['content-type']
    #    try:
    #        charset = re.search('charset\=(.*)',content_type).group(1)
    #    except AttributeError:
    #        charset = 'utf-8'
    #    if charset.lower() != 'utf-8':
    #        xml_response = handler.read().decode(charset).encode('utf-8')
    #    else:
    #        xml_response = handler.read()
    #    dom = parseString(xml_response)
    #    handler.close()
    #    localtime = dom.getElementsByTagName(
    #        "isotime")[0].firstChild.nodeValue
    #    localtime = datetime.datetime.strptime(localtime.rsplit(' ',1)[0],
    #                                           '%Y-%m-%d %H:%M:%S')
    #    # Grab sunrise/sunset data from met.no
    #    baseurl = 'http://api.met.no/weatherapi/sunrise/1.0/'
    #    query = 'lat=%s;lon=%s;date=%s' % (self.__lat, self.__lon,
    #                                       localtime.date().isoformat())
    #    url = '?'.join((baseurl, query))
    #    try:
    #        print "33Weather: Get sunrise/sunset data, url %s" % url
    #        handler = urllib2.urlopen(url)
    #    except urllib2.URLError:
    #        print "44Weather: error reaching url '%s'" % url
    #        return
    #    content_type = handler.info().dict['content-type']
    #    try:
    #        charset = re.search('charset\=(.*)', content_type).group(1)
    #    except AttributeError:
    #        charset = 'utf-8'
    #    if charset.lower() != 'utf-8':
    #        xml_response = handler.read().decode(charset).encode('utf-8')
    #    else:
    #        xml_response = handler.read()
    #    dom = parseString(xml_response)
    #    handler.close()
    #    sun_data = dom.getElementsByTagName('sun')[0]
    #    sunrise = sun_data.getAttribute('rise')
    #    sunset = sun_data.getAttribute('set')
    #    dom.unlink()

        # 2013-06-07T09:27:15Z
    #    sunrise_t = datetime.datetime.strptime(sunrise, '%Y-%m-%dT%H:%M:%SZ')
        # 2013-06-08T00:22:49Z
    #    sunset_t = datetime.datetime.strptime(sunset, '%Y-%m-%dT%H:%M:%SZ')
        # convert sun data into local time for location
    #    utc = timezone('UTC')
    #    utc_sunrise_dt = datetime.datetime(sunrise_t.year, sunrise_t.month, sunrise_t.day,
    #                              sunrise_t.hour, sunrise_t.minute, sunrise_t.second, tzinfo=utc)
    #    utc_sunset_dt = datetime.datetime(sunset_t.year, sunset_t.month, sunset_t.day,
    #                             sunset_t.hour, sunset_t.minute, sunset_t.second, tzinfo=utc)
    #    self.__sunrise_t = utc_sunrise_dt.astimezone(self.__time_zone)
    #    self.__sunset_t = utc_sunset_dt.astimezone(self.__time_zone)
        # Calculate whether it is night or day
    #    local_dt = self.__time_zone.localize(localtime, is_dst=self.dst)
    #    if local_dt < self.__sunrise_t or local_dt > self.__sunset_t:
    #        self.__night = True
    #        print '111'
    #    else:
     #       self.__night = False
    #        print '222'
    #    print "Weather: got localtime " + "%s, sunrise '%s', sunset '%s', night = %s" % (localtime, self.__sunrise_t, self.__sunset_t, self.__night)

    #def get_icon_name(self):
    #    """ Get icon name associated with current condition """
    #    if self.__current_condition != None:
    #        if self.__night:
    #            print 'night...'
    #            print "Weather: night, show '%s' icon" % self.__current_condition[1]
    #            print self.__current_condition[1]#weather-few-clouds-night
    #            return self.__current_condition[1]
    #        else:
    #            #log.debug("Weather: day, show '%s' icon" % self.__current_condition[0])
    #            print 'day...'
    #            print self.__current_condition[0]#weather-fog
    #            return self.__current_condition[0]
    #    else:
    #        print "Weather: return 'offline' icon due to empty condition"
    #        return False

    #def prepare_time_zone(self):
    #    """ Get timezone of location with specified lat/lon """
    #    #TODO: need to figure out how often to call this...
    #    #      once a day? whenever location is changed?
    #    self.timezoneId = None
    #    self.dst = None
    #    # Grab utc datetime from earthtools.org
    #    url = 'http://www.earthtools.org/timezone-1.1/%s/%s' % (self.__lat, self.__lon)
    #    try:
    #        handler = urllib2.urlopen(url)
    #        content_type = handler.info().dict['content-type']
    #        try:
    #            charset = re.search('charset\=(.*)',content_type).group(1)
    #        except AttributeError:
    #            charset = 'utf-8'
    #        if charset.lower() != 'utf-8':
    #            xml_response = handler.read().decode(charset).encode('utf-8')
    #        else:
    #            xml_response = handler.read()
    #        dom = parseString(xml_response)
    #        handler.close()
    #        utctime = dom.getElementsByTagName("utctime")[0].firstChild.nodeValue
    #        utctime = datetime.datetime.strptime(utctime, '%Y-%m-%d %H:%M:%S')
    #        print 'b1'
    #    except urllib2.URLError:
    #        print "Location: error reaching url '%s'" % url
    #        # fallback to getting UTC time from system time (less accurate)
    #        utctime = datetime.datetime.utcnow()
    #    # Grab timezone id and dst status from Google
    #    tz_info = None
    #    timestamp = calendar.timegm(utctime.timetuple())
    #    baseurl = 'https://maps.googleapis.com/maps/api/timezone/json'
    #    params = {'location': '%s,%s' % (self.__lat, self.__lon),
    #              'timestamp': timestamp, 'sensor': 'false'}
    #    url = '?'.join((baseurl, urlencode(params)))
    #    print 'b2'
    #    try:
    #        print 'c1'
    #        print url
    #        handler = urllib2.urlopen(url)
    #        print 'c0'
    #        content_type = handler.info().dict['content-type']
    #        print 'c2'
    #        try:
    #            charset = re.search('charset\=(.*)', content_type).group(1)
    #            print 'c3'
    #        except AttributeError:
    #            charset = 'utf-8'
    #            print 'c4'
    #        if charset.lower() != 'utf-8':
    #            print 'c5'
    #            json_response = handler.read().decode(charset).encode('utf-8')
    #            print 'c6'
    #        else:
    #            print 'c7'
    #            json_response = handler.read()
    #            print 'c8'
    #        tz_info = json.loads(json_response)
    #        print 'c9'
    #        handler.close()
    #        print 'b3'
    #        if tz_info['status'] == 'OK':
    #            self.timezoneId = tz_info['timeZoneId']
    #            if tz_info['dstOffset'] != 0:
    #                self.dst = True
    #            else:
    #                self.dst = False
    #        else:
    #            tz_info = None
    #    except urllib2.URLError:
    #        print "Location: error reaching url '%s'" % url
    #    # fallback to getting timezone/dst from system (less accurate)
    #    # note: reading /etc/timezone will only work on debian/ubuntu
    #    if tz_info is None:
    #        print 'b4'
    #        with open('/etc/timezone', 'r') as f:
    #            tz_id = f.readline().strip()
    #            self.timezoneId = tz_id
    #        if time.localtime().tm_isdst == 1:
    #            self.dst = True
    #        else:
    #            self.dst = False

    def get_temperature_unit(self):
        self._unit = ""
        if 'units' in self.yahoo_result \
            and 'temperature' in self.yahoo_result['units']:
            self._unit = u"°%s" % self.yahoo_result['units']['temperature']

    def get_temperature(self):
        _value = None
        try:
            if 'temp' in self.yahoo_result['condition']:
                _value = self.yahoo_result['condition']['temp']
        except KeyError:
            pass
        if _value is None:
            _value = "---"
        return "%s %s" % (_value, self._unit)

    def get_humidity(self):
        """ Get text string for current humidity """
        humidity = "---"
        if 'atmosphere' in self.yahoo_result \
           and 'humidity' in self.yahoo_result['atmosphere']:
            humidity = "%s%%" % (self.yahoo_result['atmosphere']['humidity'])
        return humidity

    def get_visibility(self):
        visibility = "---"
        if 'atmosphere' in self.yahoo_result \
           and 'visibility' in self.yahoo_result['atmosphere']:
            visibility = self.yahoo_result['atmosphere']['visibility']
        return visibility

    def get_wind(self):
        """ Get text string for current wind speed and direction """
        wind_direction = "---"
        wind_speed = ""
        wind_units = ""
        try:
            # Create a wind_info structure from Yahoo data
            #wind_direction = u"%s (%s°)" % (pywapi.get_wind_direction(self.yahoo_result['wind']['direction']), self.yahoo_result['wind']['direction'])
            #wind_direction = self.yahoo_result['wind']['direction']
            wind_speed = self.yahoo_result['wind']['speed']
            wind_units = self.yahoo_result['units']['speed']
            print 'wind---------------'
            #pre_wind  = "%s %s %s" % (wind_direction, wind_speed, wind_units)
            pre_wind  = "%s %s" % (wind_speed, wind_units)
            print pre_wind
            return pre_wind
        except KeyError:
            pass
            return '---'
        #try:
        #    wind_info = [wind_direction, wind_speed, wind_units]
        #    _value = float(wind_speed)
        #except ValueError as ex:
        #    _value = -1.0
        #_value *= 0.621371
        #_unit  = "mph"
        #wind_info[len(wind_info)-1] = _unit
        #yahoo_format = NumberFormatter()
        #wind_info[len(wind_info)-2] = yahoo_format.format_float(_value, 1)
        #if _value < 0.0:
        #    wind_info[1:] = ["", "N/A", ""]
        #if _value == 0.0:
        #    wind_info[1:] = ["Calm", "", ""]
        #wind = "%s %s %s" % (wind_info[0], wind_info[1], \
        #                        wind_info[2])
        #print wind
        #return wind

    def get_pressure(self):
        """ Get text string for current air pressure """
        _value = "---"
        _unit = ""
        if 'pressure' in self.yahoo_result['atmosphere'] \
           and 'pressure' in self.yahoo_result['units']:
            _value = self.yahoo_result['atmosphere']['pressure']
            _unit = self.yahoo_result['units']['pressure']
        return "%s %s" % (_value, _unit)

    def get_release_time(self):
        release = "---"
        if 'condition' in self.yahoo_result \
            and 'date' in self.yahoo_result['condition']:
            release = self.yahoo_result['condition']['date']
        return release

    def get_weather_text(self):#Haze
        weather = "---"
        if 'condition' in self.yahoo_result \
           and 'text' in self.yahoo_result['condition']:
            weather = self.yahoo_result['condition']['text']
        return weather

    def get_forecast(self):
        self.forecastData.clear()
        self.forecastData['city'] = self.get_city()
        self.forecastData['time'] = self.get_release_time()
        for i in range(len(self.yahoo_result['forecasts'])):
            high = '---'
            low = '---'
            temp = '---'
            if 'code' in self.yahoo_result['forecasts'][i]:
                self.forecastData['code%s' %(str(i))] = self.yahoo_result['forecasts'][i]['code']
            if 'text' in self.yahoo_result['forecasts'][i]:
                self.forecastData['text%s' %(str(i))] = self.yahoo_result['forecasts'][i]['text']
            if 'high' in self.yahoo_result['forecasts'][i] \
                and 'low' in self.yahoo_result['forecasts'][i]:
                high = self.yahoo_result['forecasts'][i]['high']
                low = self.yahoo_result['forecasts'][i]['low']
                self.forecastData['temp%s' %(str(i))] = "%s %s ~ %s %s" % (low, self._unit, high, self._unit)
            if 'date' in self.yahoo_result['forecasts'][i]:
                self.forecastData['date%s' %(str(i))] = self.yahoo_result['forecasts'][i]['date']
            if 'day' in self.yahoo_result['forecasts'][i]:
                self.forecastData['day%s' %(str(i))] = self.yahoo_result['forecasts'][i]['day']
                #print self.yahoo_result['forecasts'][i]['code']
        #print forecast
        return self.forecastData

    def get_sun(self):
        sunrise = "---"
        sunset = "---"
        if 'astronomy' in self.yahoo_result:
            if 'sunrise' in self.yahoo_result['astronomy']:
                sunrise = self.yahoo_result['astronomy']['sunrise']
            if 'sunset' in self.yahoo_result['astronomy']:
                sunset = self.yahoo_result['astronomy']['sunset']
        #print sunrise
        #print sunset
        return sunrise, sunset

    def get_city(self):
        city = "---"
        if 'location' in self.yahoo_result \
           and 'city' in self.yahoo_result['location']:
            city = self.yahoo_result['location']['city']
        return city

if __name__ == '__main__':
    pass
    #yahoo = YahooWeather()
    #yahoo.get_locale()
    #yahoo.search_city_names("beijing")
    #yahoo.prepare_location_for_yahoo("1816670")
    #yahoo.prepare_time_zone()
    #yahoo.get_weather()
    #yahoo.deal_with_test()
    #yahoo.get_sun_data()
    #yahoo.get_icon_name()
    #print yahoo.get_temperature()
    #print yahoo.get_humidity()
    #print yahoo.get_sunrise()
    #print yahoo.get_sunset()
    #print yahoo.get_pressure()
    #print yahoo.get_visibility()
    #print yahoo.get_release_time()
    #print yahoo.get_weather_text()
    #print yahoo.get_forecast()
    #aa, bb = yahoo.get_sun()
    #print aa
    #print bb
