#!/usr/bin/env python
# -*- coding: utf-8 -*-

### BEGIN LICENSE
# Copyright (C) 2013 ~ 2014 National University of Defense Technology(NUDT) & Kylin Ltd
# Author: Kobe Lee
#
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
### END LICENSE

"""This module provides the RatingsAndReviewsAPI class for talking to the
ratings and reviews API, plus a few helper classes.
"""

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

# These are factored out as constants for if you need to work against a
# server that doesn't support both schemes (like http-only dev servers)
PUBLIC_API_SCHEME = 'http'
AUTHENTICATED_API_SCHEME = 'https'

class WeatherPistonAPI(PistonAPI):
    """A client for talking to the reviews and ratings API.

    If you pass no arguments into the constructor it will try to connect to
    localhost:8000 so you probably want to at least pass in the
    ``service_root`` constructor argument.
    """
    default_service_observe = 'observe'
    default_service_forecast3d = 'forecast3d'
    default_service_forecast6d = 'forecast6d'
    default_content_type = 'application/x-www-form-urlencoded'

    @validate_pattern('cityid', r'[0-9a-z+-.:/]+', required=False)
    @returns_json
    def get_cma_observe_weather(self, cityid):
        url = '%s/%s/' % (self.default_service_observe, cityid)
        return self._get(url, scheme=PUBLIC_API_SCHEME)

    @validate_pattern('cityid', r'[0-9a-z+-.:/]+', required=False)
    @returns_json
    def get_cma_forecast3d_weather(self, cityid):
        url = '%s/%s/' % (self.default_service_forecast3d, cityid)
        return self._get(url, scheme=PUBLIC_API_SCHEME)

    @validate_pattern('cityid', r'[0-9a-z+-.:/]+', required=False)
    @returns_json
    def get_cma_forecast6d_weather(self, cityid):
        url = '%s/%s/' % (self.default_service_forecast6d, cityid)
        return self._get(url, scheme=PUBLIC_API_SCHEME)
