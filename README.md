Associated article: [Attacking ANY.RUN for Sandbox Detection Development](https://medium.com/@orangemaster674/attacking-any-run-for-sandbox-detection-development-747c1a8aa4fd)

# ANY.RUN Sandbox Detection

- Part 1: The symblic device name of the driver.
- Part 2: The non-standard filesystem behaviour under protected ANY.RUN installed files and folders.

![IMG](.png)

<sup>
Part <u>3</u>: Coming Soon
</sup>

### Irrelevant Glossaries

- The ANY.RUN components are under `%ProgramFiles%\\KernelLogger`.
- The usermode agent (a Windows service) is registered as `aga` with binary path `%ProgramFiles%\\KernelLogger\\aga.exe`.
- The virtual machine runs in a test signing mode.
  - ANY.RUN driver `A3E64E55_fl_x64.sys` is signed by WDK test certificate [attached here](./WDKTestCert%20SYSTEM,133087515274835630.cer).
- The macshift embedded in the ANY.RUN package spoofs MAC address but it is still able to obtain the original *permanent* MAC address by calling out the NDIS driver.
- The hypervisor presense bit in the CPU indicates is not present.
- Pinning SSL/TLS certificate against most popular and stable website may help you identify the intermediate certificate inserted by ANY.RUN to sniff the traffics.
