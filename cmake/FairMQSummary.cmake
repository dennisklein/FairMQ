################################################################################
# Copyright (C) 2018-2021 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

include_guard(GLOBAL)

include(FairCMakeModules)
include(FairFormattedOutput)
include(FairSummary)

macro(fairmq_summary_components)
  message(STATUS "  ")
  message(STATUS "  ${Cyan}COMPONENT         BUILT?  INFO${CR}")
  if(BUILD_FAIRMQ)
    set(fairmq_summary "${BGreen}YES${CR}    (default, disable with ${BMagenta}-DBUILD_FAIRMQ=OFF${CR})")
  else()
    set(fairmq_summary "${BRed} NO${CR}    (enable with ${BMagenta}-DBUILD_FAIRMQ=ON${CR})")
  endif()
  message(STATUS "  ${BWhite}fairmq${CR}             ${fairmq_summary}")
  if(BUILD_TESTING)
    set(tests_summary "${BGreen}YES${CR}    (default, disable with ${BMagenta}-DBUILD_TESTING=OFF${CR})")
  else()
    set(tests_summary "${BRed} NO${CR}    (enable with ${BMagenta}-DBUILD_TESTING=ON${CR})")
  endif()
  message(STATUS "  ${BWhite}tests${CR}              ${tests_summary}")
  if(BUILD_OFI_TRANSPORT)
    set(ofi_summary "${BGreen}YES${CR}    EXPERIMENTAL (disable with ${BMagenta}-DBUILD_OFI_TRANSPORT=OFF${CR})")
  else()
    set(ofi_summary "${BRed} NO${CR}    EXPERIMENTAL (default, enable with ${BMagenta}-DBUILD_OFI_TRANSPORT=ON${CR})")
  endif()
  message(STATUS "  ${BWhite}ofi_transport${CR}      ${ofi_summary}")
  if(BUILD_DDS_PLUGIN)
    set(dds_summary "${BGreen}YES${CR}    (disable with ${BMagenta}-DBUILD_DDS_PLUGIN=OFF${CR})")
  else()
    set(dds_summary "${BRed} NO${CR}    (default, enable with ${BMagenta}-DBUILD_DDS_PLUGIN=ON${CR})")
  endif()
  message(STATUS "  ${BWhite}dds_plugin${CR}         ${dds_summary}")
  if(BUILD_PMIX_PLUGIN)
    set(pmix_summary "${BGreen}YES${CR}    EXPERIMENTAL (disable with ${BMagenta}-DBUILD_PMIX_PLUGIN=OFF${CR})")
  else()
    set(pmix_summary "${BRed} NO${CR}    EXPERIMENTAL (default, enable with ${BMagenta}-DBUILD_PMIX_PLUGIN=ON${CR})")
  endif()
  message(STATUS "  ${BWhite}pmix_plugin${CR}        ${pmix_summary}")
  if(BUILD_EXAMPLES)
    set(examples_summary "${BGreen}YES${CR}    (default, disable with ${BMagenta}-DBUILD_EXAMPLES=OFF${CR})")
  else()
    set(examples_summary "${BRed} NO${CR}    (enable with ${BMagenta}-DBUILD_EXAMPLES=ON${CR})")
  endif()
  message(STATUS "  ${BWhite}examples${CR}           ${examples_summary}")
  if(BUILD_DOCS)
    set(docs_summary "${BGreen}YES${CR}    (disable with ${BMagenta}-DBUILD_DOCS=OFF${CR})")
  else()
    set(docs_summary "${BRed} NO${CR}    (default, enable with ${BMagenta}-DBUILD_DOCS=ON${CR})")
  endif()
  message(STATUS "  ${BWhite}docs${CR}               ${docs_summary}")
  if(BUILD_SDK)
    set(sdk_summary "${BGreen}YES${CR}    EXPERIMENTAL (disable with ${BMagenta}-DBUILD_SDK=OFF${CR})")
  else()
    set(sdk_summary "${BRed} NO${CR}    EXPERIMENTAL (default, enable with ${BMagenta}-DBUILD_SDK=ON${CR})")
  endif()
  message(STATUS "  ${BWhite}sdk${CR}                ${sdk_summary}")
  if(BUILD_SDK_COMMANDS)
    set(sdk_commands_summary "${BGreen}YES${CR}    (disable with ${BMagenta}-DBUILD_SDK_COMMANDS=OFF${CR})")
  else()
    set(sdk_commands_summary "${BRed} NO${CR}    (default, enable with ${BMagenta}-DBUILD_SDK_COMMANDS=ON${CR})")
  endif()
  message(STATUS "  ${BWhite}sdk_commands${CR}       ${sdk_commands_summary}")
endmacro()

macro(fairmq_summary_static_analysis)
  message(STATUS "  ")
  if(RUN_STATIC_ANALYSIS)
    list(LENGTH PROJECT_STATIC_ANALYSERS size)
    unset(analyser_list)
    set(count 0)
    foreach(analyser IN LISTS PROJECT_STATIC_ANALYSERS)
      if(${analyser}_FOUND)
        set(${analyser}_status "${analyser} ${BGreen}YES${CR}")
      else()
        set(${analyser}_status "${analyser} ${BRed}NO${CR}")
      endif()
      math(EXPR count "${count} + 1")
      string(APPEND analyser_list "${${analyser}_status}")
      if(count LESS size)
        string(APPEND analyser_list "${BWhite},${CR} ")
      endif()
    endforeach()
    set(static_ana_summary "${BWhite}(${CR}${analyser_list}${BWhite})${CR}  (disable with ${BMagenta}-DRUN_STATIC_ANALYSIS=OFF${CR})")
  else()
    set(static_ana_summary "${BRed}OFF${CR}  (default, enable with ${BMagenta}-DRUN_STATIC_ANALYSIS=ON${CR})")
  endif()
  message(STATUS "  ${Cyan}RUN STATIC ANALYSIS  ${static_ana_summary}")
endmacro()

macro(fairmq_summary_install_prefix)
  message(STATUS "  ")
  message(STATUS "  ${Cyan}INSTALL PREFIX${CR}     ${BGreen}${CMAKE_INSTALL_PREFIX}${CR} (change with ${BMagenta}-DCMAKE_INSTALL_PREFIX=...${CR})")
endmacro()

macro(fairmq_summary_debug_mode)
  message(STATUS "  ")
  if(FAIRMQ_DEBUG_MODE)
    message(STATUS "  ${Cyan}DEBUG MODE${CR}         ${BGreen}${FAIRMQ_DEBUG_MODE}${CR} (disable with ${BMagenta}-DFAIRMQ_DEBUG_MODE=OFF${CR})")
  else()
    message(STATUS "  ${Cyan}DEBUG MODE${CR}         ${BRed}${FAIRMQ_DEBUG_MODE}${CR} (enable with ${BMagenta}-DFAIRMQ_DEBUG_MODE=ON${CR})")
  endif()
endmacro()