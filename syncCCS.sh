#!/bin/bash
echo "**BE CAUTIOUS this script may harm your project dir**"
echo "Are you sure you want to copy back to the project dir?"
read ans
if [[ "$ans" != "y" ]]; then
  echo "Exiting"
  exit 0
fi
echo "cd piccolo_code"
cd piccolo_code || exit 1
echo "cp -r . /home/markos/ti/C2000Ware_1_00_03_00_Software/device_support/f2802x/examples/drivers/adc_soc/" 
cp -r . /home/markos/ti/C2000Ware_1_00_03_00_Software/device_support/f2802x/examples/drivers/adc_soc || exit 1
echo "DONE"
