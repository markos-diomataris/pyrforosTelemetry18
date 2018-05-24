################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
Example_2802xAdcSoc.obj: ../Example_2802xAdcSoc.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"/opt/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt --include_path="/opt/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" --include_path="/home/markos/ti/C2000Ware_1_00_03_00_Software/device_support/f2802x/common/include" --include_path="/home/markos/ti/C2000Ware_1_00_03_00_Software/device_support/f2802x/headers/include" --include_path="/home/markos/ti/C2000Ware_1_00_03_00_Software/device_support/f2802x" --include_path="/home/markos/ti/C2000Ware_1_00_03_00_Software/libraries/math/IQmath/c28/include" --define=_DEBUG --define=_FLASH --define=LARGE_MODEL -g --diag_suppress=232 --diag_suppress=10063 --diag_warning=225 --verbose_diagnostics --quiet --preproc_with_compile --preproc_dependency="Example_2802xAdcSoc.d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '


