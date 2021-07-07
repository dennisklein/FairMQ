################################################################################
#    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

add_executable(fairmq-ex-qc-sampler sampler.cxx)
target_link_libraries(fairmq-ex-qc-sampler PRIVATE FairMQ)

add_executable(fairmq-ex-qc-dispatcher qCDispatcher.cxx)
target_link_libraries(fairmq-ex-qc-dispatcher PRIVATE FairMQ)

add_executable(fairmq-ex-qc-task qCTask.cxx)
target_link_libraries(fairmq-ex-qc-task PRIVATE FairMQ)

add_executable(fairmq-ex-qc-sink sink.cxx)
target_link_libraries(fairmq-ex-qc-sink PRIVATE FairMQ)

add_custom_target(ExampleQC DEPENDS fairmq-ex-qc-sampler fairmq-ex-qc-dispatcher fairmq-ex-qc-task fairmq-ex-qc-sink)

# install
install(
  TARGETS
  fairmq-ex-qc-sampler
  fairmq-ex-qc-dispatcher
  fairmq-ex-qc-task
  fairmq-ex-qc-sink

  LIBRARY DESTINATION ${PROJECT_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${PROJECT_INSTALL_BINDIR}
)
