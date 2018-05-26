################################################################################
# Automatically-generated file. Do not edit!
################################################################################

CG_TOOL_ROOT := /opt/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./Communication.obj" \
"./DigitalFilters.obj" \
"./Example_2802xAdcSoc.obj" \
"./Initialization.obj" \
"/home/markos/ti/C2000Ware_1_00_03_00_Software/device_support/f2802x/common/ccs/Debug/driverlib.lib" \
$(GEN_CMDS__FLAG) \
-l"/home/markos/ti/C2000Ware_1_00_03_00_Software/device_support/f2802x/common/cmd/F2802x_generic_flash.cmd" \
-lrts2800_ml.lib \
-lIQmath.lib \

-include ../makefile.init

RM := rm -rf
RMDIR := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
Example_F2802xAdcSoc.out \

EXE_OUTPUTS__QUOTED += \
"Example_F2802xAdcSoc.out" \

BIN_OUTPUTS += \
Example_F2802xAdcSoc.hex \

BIN_OUTPUTS__QUOTED += \
"Example_F2802xAdcSoc.hex" \


# All Target
all: Example_F2802xAdcSoc.out

# Tool invocations
Example_F2802xAdcSoc.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: C2000 Linker'
	"/opt/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/cl2000" -v28 -ml -mt --define=_DEBUG --define=_FLASH --define=LARGE_MODEL -g --diag_suppress=232 --diag_suppress=10063 --diag_warning=225 --verbose_diagnostics --quiet -z -m"Example_F2802xAdcSoc.map" --stack_size=0x200 --warn_sections -i"/opt/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/lib" -i"/opt/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/include" -i"/home/markos/ti/C2000Ware_1_00_03_00_Software/device_support/f2802x/examples/drivers/adc_soc" -i"/home/markos/ti/C2000Ware_1_00_03_00_Software/device_support/f2802x/common/lib" -i"/home/markos/ti/C2000Ware_1_00_03_00_Software/libraries/math/IQmath/c28/lib" --reread_libs --issue_remarks --verbose_diagnostics --xml_link_info="Example_F2802xAdcSoc_linkInfo.xml" --entry_point=code_start --rom_model -o "Example_F2802xAdcSoc.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

Example_F2802xAdcSoc.hex: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: C2000 Hex Utility'
	"/opt/ti/ccsv8/tools/compiler/ti-cgt-c2000_18.1.1.LTS/bin/hex2000"  -o "Example_F2802xAdcSoc.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "Communication.obj" "DigitalFilters.obj" "Example_2802xAdcSoc.obj" "Initialization.obj" 
	-$(RM) "Communication.d" "DigitalFilters.d" "Example_2802xAdcSoc.d" "Initialization.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

