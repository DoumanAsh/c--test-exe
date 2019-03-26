include(ExternalProject)
ExternalProject_Add(
    catch
    PREFIX "catch"
    DOWNLOAD_NO_EXTRACT 1
    URL https://github.com/catchorg/Catch2/releases/download/v2.7.0/catch.hpp
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
)

ExternalProject_Get_Property(catch download_dir)
set(CATCH_DIR ${download_dir})
