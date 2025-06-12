# Pound
Also check out [obomori](https://github.com/Nikilites/oboromi), another emulator like Pound!

> ⚠️ **Development Notice:**
> Backend development is currently on hold until it becomes possible to dump firmware from a Nintendo Switch 2 console.

### Build status

<a><img src="https://img.shields.io/badge/current Linux x64 build-none-aaaaaa.svg"></a>
<a><img src="https://img.shields.io/badge/current Linux A64 build-none-aaaaaa.svg"></a>
<a><img src="https://img.shields.io/badge/current Android A64 build-none-aaaaaa.svg"></a>

## Overview

**Pound** aims to be one of the first functional emulators for the **Nintendo Switch 2**.

Development will begin with the **CPU**, as its architecture is nearly identical to the original Switch. After that, work will focus on bridging the differences between the two hardware generations.

## Firmware Requirement

To use Pound, you **will** need to **dump your own Switch 2 firmware** and place it in the following directory:

```
/assets/fw/
```

No firmware or system files are provided with this emulator.

## Codebase

Pound may reuse certain components from existing Nintendo Switch 1 emulators, such as **Yuzu**.
All reused code will be explicitly documented and credited in the appropriate sections of the repository.
