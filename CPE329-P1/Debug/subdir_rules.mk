################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
delay.obj: /home/teslaman/CCS/923EPC/utils/delay.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/home/teslaman/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/home/teslaman/ti/ccsv8/ccs_base/arm/include" --include_path="/home/teslaman/ti/ccsv8/ccs_base/arm/include/CMSIS" --include_path="/home/teslaman/CCS/923EPC/CPE329-P1" --include_path="/home/teslaman/CCS/923EPC/CPE329-A4" --include_path="/home/teslaman/CCS/923EPC/CPE329-A3" --include_path="/home/teslaman/CCS/923EPC/CPE329_A2" --include_path="/home/teslaman/CCS/923EPC/utils" --include_path="/home/teslaman/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=FCPU=FREQ_24_MHZ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

gpio.obj: /home/teslaman/CCS/923EPC/utils/gpio.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/home/teslaman/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/home/teslaman/ti/ccsv8/ccs_base/arm/include" --include_path="/home/teslaman/ti/ccsv8/ccs_base/arm/include/CMSIS" --include_path="/home/teslaman/CCS/923EPC/CPE329-P1" --include_path="/home/teslaman/CCS/923EPC/CPE329-A4" --include_path="/home/teslaman/CCS/923EPC/CPE329-A3" --include_path="/home/teslaman/CCS/923EPC/CPE329_A2" --include_path="/home/teslaman/CCS/923EPC/utils" --include_path="/home/teslaman/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=FCPU=FREQ_24_MHZ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

interrupt.obj: /home/teslaman/CCS/923EPC/utils/interrupt.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/home/teslaman/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/home/teslaman/ti/ccsv8/ccs_base/arm/include" --include_path="/home/teslaman/ti/ccsv8/ccs_base/arm/include/CMSIS" --include_path="/home/teslaman/CCS/923EPC/CPE329-P1" --include_path="/home/teslaman/CCS/923EPC/CPE329-A4" --include_path="/home/teslaman/CCS/923EPC/CPE329-A3" --include_path="/home/teslaman/CCS/923EPC/CPE329_A2" --include_path="/home/teslaman/CCS/923EPC/utils" --include_path="/home/teslaman/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=FCPU=FREQ_24_MHZ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

keypad.obj: /home/teslaman/CCS/923EPC/utils/keypad.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/home/teslaman/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/home/teslaman/ti/ccsv8/ccs_base/arm/include" --include_path="/home/teslaman/ti/ccsv8/ccs_base/arm/include/CMSIS" --include_path="/home/teslaman/CCS/923EPC/CPE329-P1" --include_path="/home/teslaman/CCS/923EPC/CPE329-A4" --include_path="/home/teslaman/CCS/923EPC/CPE329-A3" --include_path="/home/teslaman/CCS/923EPC/CPE329_A2" --include_path="/home/teslaman/CCS/923EPC/utils" --include_path="/home/teslaman/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=FCPU=FREQ_24_MHZ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

lcd.obj: /home/teslaman/CCS/923EPC/utils/lcd.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/home/teslaman/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/home/teslaman/ti/ccsv8/ccs_base/arm/include" --include_path="/home/teslaman/ti/ccsv8/ccs_base/arm/include/CMSIS" --include_path="/home/teslaman/CCS/923EPC/CPE329-P1" --include_path="/home/teslaman/CCS/923EPC/CPE329-A4" --include_path="/home/teslaman/CCS/923EPC/CPE329-A3" --include_path="/home/teslaman/CCS/923EPC/CPE329_A2" --include_path="/home/teslaman/CCS/923EPC/utils" --include_path="/home/teslaman/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=FCPU=FREQ_24_MHZ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/home/teslaman/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/home/teslaman/ti/ccsv8/ccs_base/arm/include" --include_path="/home/teslaman/ti/ccsv8/ccs_base/arm/include/CMSIS" --include_path="/home/teslaman/CCS/923EPC/CPE329-P1" --include_path="/home/teslaman/CCS/923EPC/CPE329-A4" --include_path="/home/teslaman/CCS/923EPC/CPE329-A3" --include_path="/home/teslaman/CCS/923EPC/CPE329_A2" --include_path="/home/teslaman/CCS/923EPC/utils" --include_path="/home/teslaman/ti/ccsv8/tools/compiler/ti-cgt-arm_18.1.3.LTS/include" --advice:power=all --define=__MSP432P401R__ --define=FCPU=FREQ_24_MHZ --define=ccs -g --gcc --diag_warning=225 --diag_wrap=off --display_error_number --abi=eabi --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '


