#
# Mocks provided for the unit test framework
#
# Copyright (C) 2021-2024, HENSOLDT Cyber GmbH
# 
# SPDX-License-Identifier: GPL-2.0-or-later
#
# For commercial licensing, contact: info.cyber@hensoldt.net
#

cmake_minimum_required(VERSION 3.17)

#-------------------------------------------------------------------------------
add_library("${PROJECT_NAME}_mocks" INTERFACE)

target_include_directories("${PROJECT_NAME}_mocks"
    INTERFACE
        "../include"
)
