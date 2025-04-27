################
### Template ###
################

FROM mcr.microsoft.com/devcontainers/cpp:1-ubuntu-22.04

ARG REINSTALL_CMAKE_VERSION_FROM_SOURCE="3.22.2"

# Optionally install the cmake for vcpkg
COPY ./reinstall-cmake.sh /tmp/

RUN if [ "${REINSTALL_CMAKE_VERSION_FROM_SOURCE}" != "none" ]; then \
        chmod +x /tmp/reinstall-cmake.sh && /tmp/reinstall-cmake.sh ${REINSTALL_CMAKE_VERSION_FROM_SOURCE}; \
    fi \
    && rm -f /tmp/reinstall-cmake.sh

# [Optional] Uncomment this section to install additional vcpkg ports.
# RUN su vscode -c "${VCPKG_ROOT}/vcpkg install <your-port-name-here>"

# [Optional] Uncomment this section to install additional packages.
# RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
#     && apt-get -y install --no-install-recommends <your-package-list-here>


##############
### Custom ###
##############

# Install dependencies
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    cmake \
    ninja-build \
    make \
    git \
    wget \
    ca-certificates \
    xz-utils \
    libncurses-dev \
    libssl-dev \
    vim \
    && rm -rf /var/lib/apt/lists/*

# Set versions and URLs
ARG TOOLCHAIN_URL=https://developer.arm.com/-/media/Files/downloads/gnu/14.2.rel1/binrel/arm-gnu-toolchain-14.2.rel1-x86_64-arm-none-eabi.tar.xz
ARG TOOLCHAIN_FILENAME=arm-gnu-toolchain-14.2.rel1-x86_64-arm-none-eabi.tar.xz

# Download toolchain separately first to cache layer
ADD ${TOOLCHAIN_URL} /tmp/${TOOLCHAIN_FILENAME}

# Install ARM GCC toolchain
RUN mkdir -p /opt/arm-gnu-toolchain && \
    tar -xf /tmp/${TOOLCHAIN_FILENAME} --strip-components=1 -C /opt/arm-gnu-toolchain && \
    rm /tmp/${TOOLCHAIN_FILENAME}
# Check everything installed properly
# `arm-none-eabi-gcc --version`
# `arm-none-eabi-g++ --version`
# `arm-none-eabi-gcc --print-sysroot`

# Add ARM toolchain to path
ENV PATH="/opt/arm-gnu-toolchain/bin:${PATH}"

# Install python
RUN apt-get update && \
    apt-get install -y \
    python3 \
    python3-pip

# Set default working directory
WORKDIR /workspace

# Opens bash shell after build
CMD ["/bin/bash"]

