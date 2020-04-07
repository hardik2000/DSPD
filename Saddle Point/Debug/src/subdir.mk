################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Saddle\ Point.c 

OBJS += \
./src/Saddle\ Point.o 

C_DEPS += \
./src/Saddle\ Point.d 


# Each subdirectory must supply rules for building sources it contributes
src/Saddle\ Point.o: ../src/Saddle\ Point.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"src/Saddle Point.d" -MT"src/Saddle\ Point.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


