#!/usr/bin/python
# -*- coding: utf-8 -*-

### BEGIN LICENSE

# Copyright (C) 2013 National University of Defense Technology(NUDT) & Kylin Ltd

# Author:
#     Shine Huang<shenghuang@ubuntukylin.com>
# Maintainer:
#     Shine Huang<shenghuang@ubuntukylin.com>

# This program is free software: you can redistribute it and/or modify it
# under the terms of the GNU General Public License version 3, as published
# by the Free Software Foundation.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranties of
# MERCHANTABILITY, SATISFACTORY QUALITY, or FITNESS FOR A PARTICULAR
# PURPOSE.  See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program.  If not, see <http://www.gnu.org/licenses/>.


from urllib import quote_plus
from piston_mini_client import (
    PistonAPI,
    PistonResponseObject,
    PistonSerializable,
    returns,
    returns_json,
    returns_list_of,
    )
from piston_mini_client.validators import validate_pattern, validate
from piston_mini_client import APIError
import httplib2
import sys
reload(sys)
sys.setdefaultencoding('utf8')


class ReviewUK(PistonResponseObject):
    """
    id
    content
    date
    user_display
    user
    aid: {
        id
        review_total
    }
    """
    pass


class PingbackmainRequest(PistonSerializable):
    _atts = ('machine', 'distro', 'version_os', 'version_uksc')


class PingbackappRequest(PistonSerializable):
    _atts = ('app_name', 'machine', 'isrcm')


class PistonRemoter(PistonAPI):

    default_service_observe = 'observe'
    default_service_forecast3d = 'forecast3d'
    default_content_type = 'application/x-www-form-urlencoded'

    @returns_json
    def get_all_ratings(self):
        return self._get("getallratings", scheme="http")

    @returns_list_of(ReviewUK)
    def get_reviews(self, app, start, range_):
        return self._get('getreviews/?app=%s;start=%s;range=%s' % (app, start, range_), scheme="http")

    @returns_list_of(ReviewUK)
    def get_newest_review(self, app):
        start = 0
        range_ = 1
        return self._get('getreviews/?app=%s;start=%s;range=%s' % (app, start, range_), scheme="http")

    @returns_json
    def submit_pingback_main(self, machine, distro, version_os, version_uksc):
        postdata = PingbackmainRequest()
        postdata.machine = machine
        postdata.distro = distro
        postdata.version_os = version_os
        postdata.version_uksc = version_uksc
        return self._post('pingbackmain/', data=postdata, scheme='http', content_type='application/json')

    @returns_json
    def submit_pingback_app(self, app_name, machine, isrcm):
        postdata = PingbackappRequest()
        postdata.app_name = app_name
        postdata.machine = machine
        postdata.isrcm = isrcm
        return self._post('pingbackapp/', data=postdata, scheme='http', content_type='application/json')

    @returns_json
    def get_all_categories(self):
        return self._get("getallcategories", scheme="http")

    @returns_json
    def get_all_rank_and_recommend(self):
        return self._get("getallrankandrecommend", scheme='http')

    @returns_json
    def get_newer_application_info(self, last_update_date):
        return self._get('getnewerapplicationinfo/?modify_time=%s' % last_update_date, scheme="http")
        
    @returns_json
    def allapp_forxapianupdate(self):
        return self._get('allappforxapianupdate/?', scheme="http")
    
    @returns_json
    def newerapp_for_xapianupdate(self, the_latest_update_time):
        return self._get('newerappforxapianupdate/?update_datetime=%s' % the_latest_update_time, scheme="http")

if __name__ == '__main__':
    s = PistonRemoter(service_root="http://192.168.30.12/uksc/")
    # res = s.get_all_categories()
    # res = s.get_all_rank_and_recommend()
    # print res
    # res = s.submit_pingback_main("123123","ubuntutu","1414","0.99")
    # print res
    # res = s.submit_pingback_app("pyracerz","jioqjwfiqwf","True")
    # print res
    # res = s.get_newer_application_info('2014-07-23')
    # print res
    # reslist = s._get("getallratings", scheme="http")
    # reslist = s.get_all_ratings()
    # print len(reslist)
    # import json
    # decoded = json.loads(reslist)
    # print len(decoded)
    #
    # try:
    # res = s.get_all_ratings()
    # print res[0]
    # print "res : ",res[0]['app_name']
    # print "res : ",res[0]['rating_avg']
    # print "res : ",res[0]['rating_total']

    # res = s.get_reviews('gedit', 2)


    # res = s.get_newest_review('gedit')
    # for r in res:
    #     print r.user
    #     print r.user_display
    #     print r.content
    #     print r.date
    #     print r.aid['review_total']
    #     print '\n'


    # except ValueError as e:
    #     print "failed to parse '%s'" % e
    # except APIError as e:
    #     print e
    # except httplib2.ServerNotFoundError:
    #     s._offline_mode = True
    #     res = s.get_all_ratings('hehehe')
    # except:
    #     print "other except"


    # s2 = PistonRemoter(service_root="http://reviews.ubuntu.com/reviews/api/1.0")
    # res = s2.get_reviewss("gedit",language="zh_CN",page=1)
    # Review.from_piston_mini_client(res[0])

    # reviews = []
    # for r in res:
    #     review = Review.from_piston_mini_client(r)
    #     print review.review_text

        # print review.reviewer_username
        # print review.reviewer_displayname
        # print review.summary
        # print review.rating
        # print review.date_created
        # print review.review_text

        # reviews.append(review)
