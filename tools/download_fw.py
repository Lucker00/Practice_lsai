# #!/usr/bin/env python3
# -*-coding:utf-8 -*-
'''
@File    :   par.py
@Time    :   2024/04/30 13:07:52
@Author  :   TsMax(TianShuang Ke)
@Version :   1.0
@Contact :   QinYUN575@Gmail.com
@License :   (C)Copyright 2015-2022, TsMax
@Desc    :   None
'''

import argparse
import os
from rich import print

import pylink


class DOWNLOADER:
    def __init__(self, firmware, device, type):
        self.jlink = pylink.JLink()
        if firmware is None:
            self.firmware = "./build/stm32_test.hex"
        else:
            self.firmware = firmware
        if os.path.exists(self.firmware):
            # print("Firmware file found: {}".format(self.firmware))
            pass
        else:
            print("Firmware file not found: {}".format(self.firmware))
            exit(1)
        self.device = device
        self.type = type
        self.opened = False

    def open(self):
        if (self.opened):
            return
        self.jlink.open()
        self.jlink.set_tif(pylink.enums.JLinkInterfaces.SWD)
        self.jlink.connect('STM32f407VE', speed='auto', verbose=True)
        # self.jlink.connect('STM32f407VE', speed=400000, verbose=True)
        self.opened = True

    def print_target_info(self):
        if self.jlink.target_connected():
            print("Target Core ID:", self.jlink.core_id())
            print("Target Device Family:", self.jlink.device_family())
            # print("Target Device Name:", self.jlink.device_name())
            # print("Target Device Series:", str(self.jlink.serial_number()))
        else:
            print("Target is not connected")

    def download(self, offset_addr):
        print("Downloading firmware({})...".format(self.firmware))
        
        result =self.jlink.flash_file(self.firmware, offset_addr)
        print("Download result:", ("Success" if result == 0 else "Failed"), "({})".format(result))

    def target_reset(self):
        self.jlink.reset()

    def close(self):
        self.jlink.close()

# pylink emulator -s STM32f407VE
if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Download firmware')
    parser.add_argument('-f', '--firmware', help='Firmware file path', required=False)
    # parser.add_argument('-d', '--device', help='Device name', required=True)
    # parser.add_argument('-t', '--type', help='Firmware type', required=True)

    args = parser.parse_args()
    # downloader = DOWNLOADER(args.firmware, args.device, args.type)
    # downloader.download()

    downloader = DOWNLOADER(args.firmware, 'STM32f407VE', 'bin')
    downloader.open()
    downloader.print_target_info()
    downloader.download(0x08000000)
    downloader.target_reset()


