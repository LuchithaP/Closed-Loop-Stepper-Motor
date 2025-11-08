################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
src/%.obj: ../src/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1281/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 --include_path="C:/Users/Luchitha/workspace_v12/closed_loop_stepper_2" --include_path="C:/Users/Luchitha/workspace_v12/closed_loop_stepper_2/include" --include_path="C:/Users/Luchitha/workspace_v12/closed_loop_stepper_2/src" --include_path="C:/Users/Luchitha/workspace_v12/closed_loop_stepper_2" --include_path="C:/ti/c2000/C2000Ware_5_00_00_00/device_support/f2806x/headers/include" --include_path="C:/ti/c2000/C2000Ware_5_00_00_00/libraries/math/IQmath/c28/include" --include_path="C:/ti/ccs1281/ccs/tools/compiler/ti-cgt-c2000_22.6.1.LTS/include" --define=FLASH --define=_DEBUG --define=cla0 --define=fpu32 --define=vcu0 -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="src/$(basename $(<F)).d_raw" --obj_directory="src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


