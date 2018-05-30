#!/bin/bash
echo "Erasing code..."
rm -rf ./piccolo_code
echo "cp -r /home/markos/ti/C2000Ware_1_00_03_00_Software/device_support/f2802x/examples/drivers/adc_soc ./piccolo_code" 
cp -r /home/markos/ti/C2000Ware_1_00_03_00_Software/device_support/f2802x/examples/drivers/adc_soc ./piccolo_code 
echo "DONE"
