################################################################################
#    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

add_executable(fairmq-ex-n-m-synchronizer synchronizer.cxx)
target_link_libraries(fairmq-ex-n-m-synchronizer PRIVATE FairMQ)

add_executable(fairmq-ex-n-m-sender sender.cxx)
target_link_libraries(fairmq-ex-n-m-sender PRIVATE FairMQ)

add_executable(fairmq-ex-n-m-receiver receiver.cxx)
target_link_libraries(fairmq-ex-n-m-receiver PRIVATE FairMQ)

add_custom_target(ExampleNM DEPENDS fairmq-ex-n-m-synchronizer fairmq-ex-n-m-sender fairmq-ex-n-m-receiver)

list(JOIN Boost_LIBRARY_DIRS ":" LIB_DIR)
set(BIN_DIR ${CMAKE_CURRENT_BINARY_DIR}:${CMAKE_BINARY_DIR}/fairmq/sdk)
set(DATA_DIR ${CMAKE_CURRENT_BINARY_DIR})
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fairmq-start-ex-n-m.sh.in          ${CMAKE_CURRENT_BINARY_DIR}/fairmq-start-ex-n-m.sh @ONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fairmq-start-ex-n-m-pair.sh.in     ${CMAKE_CURRENT_BINARY_DIR}/fairmq-start-ex-n-m-pair.sh @ONLY)

# install
install(
  TARGETS
  fairmq-ex-n-m-synchronizer
  fairmq-ex-n-m-sender
  fairmq-ex-n-m-receiver

  LIBRARY DESTINATION ${PROJECT_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${PROJECT_INSTALL_BINDIR}
)

# configure run script with different executable paths for build and for install directories
set(BIN_DIR ${CMAKE_INSTALL_PREFIX}/${PROJECT_INSTALL_BINDIR})
set(DATA_DIR ${CMAKE_INSTALL_PREFIX}/${PROJECT_INSTALL_DATADIR})
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fairmq-start-ex-n-m.sh.in          ${CMAKE_CURRENT_BINARY_DIR}/fairmq-start-ex-n-m.sh_install @ONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fairmq-start-ex-n-m-pair.sh.in     ${CMAKE_CURRENT_BINARY_DIR}/fairmq-start-ex-n-m-pair.sh_install @ONLY)

install(
  PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/fairmq-start-ex-n-m.sh_install
  DESTINATION ${PROJECT_INSTALL_BINDIR}
  RENAME fairmq-start-ex-n-m.sh
)

install(
  PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/fairmq-start-ex-n-m-pair.sh_install
  DESTINATION ${PROJECT_INSTALL_BINDIR}
  RENAME fairmq-start-ex-n-m-pair.sh
)
