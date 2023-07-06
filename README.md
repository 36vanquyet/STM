# Install ARM GNU Toolchain on Codebase

Determine the latest version of toolchain via command line:
    '''ARM_TOOLCHAIN_VERSION=$(curl -s https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads | grep -Po '<h4>Version \K.+(?=</h4>)')'''

