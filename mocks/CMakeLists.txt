#
# Mocks provided for the unit test framework
#
# Copyright (C) 2021, HENSOLDT Cyber GmbH
#

cmake_minimum_required(VERSION 3.17)

#-------------------------------------------------------------------------------
add_library("${PROJECT_NAME}_mocks" INTERFACE)

target_include_directories("${PROJECT_NAME}_mocks"
    INTERFACE
        "../include"
)
