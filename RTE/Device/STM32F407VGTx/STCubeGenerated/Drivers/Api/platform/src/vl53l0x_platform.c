//?????#include "hal.h"
#include "vl53l0x_platform.h"
#include "vl53l0x_api.h"


#include "stm32f4xx_hal.h"
//#include "i2c_err.h"
#include <string.h>

#define I2C_TIME_OUT_BASE   10
#define I2C_TIME_OUT_BYTE   1
#define VL53L0X_OsDelay(...) HAL_Delay(2)


#ifndef HAL_I2C_MODULE_ENABLED
#warning "HAL I2C module must be enable "
#endif
//extern I2C_HandleTypeDef hi2c1;
//#define VL53L0X_pI2cHandle    (&hi2c1)

/* when not customized by application define dummy one */
#ifndef VL53L0X_GetI2cBus
/** This macro can be overloaded by user to enforce i2c sharing in RTOS context
 */
#   define VL53L0X_GetI2cBus(...) (void)0
#endif

#ifndef VL53L0X_PutI2cBus
/** This macro can be overloaded by user to enforce i2c sharing in RTOS context
 */
#   define VL53L0X_PutI2cBus(...) (void)0
#endif

#ifndef VL53L0X_OsDelay
#   define  VL53L0X_OsDelay(...) (void)0
#endif


uint8_t _I2CBuffer[64];

static uint8_t wait_for_gpio_state_timeout(GPIO_TypeDef *port, uint16_t pin, GPIO_PinState state, uint32_t timeout)
 {
    uint32_t Tickstart = HAL_GetTick();
    uint8_t ret = 1;

    for(;(state != HAL_GPIO_ReadPin(port, pin)) && (1 == ret);) // Wait until flag is set
    {
        if(timeout != HAL_MAX_DELAY) // Check for the timeout
        {
            if((timeout == 0U) || ((HAL_GetTick() - Tickstart) > timeout)) ret = 0;
        }

        __ASM("nop");
    }
    return ret;
}

static void I2C_ClearBusyFlagErratum(I2C_HandleTypeDef *hi2c, uint32_t timeout)
{
        // 2.13.7 I2C analog filter may provide wrong value, locking BUSY. STM32F10xx8 STM32F10xxB Errata sheet

    GPIO_InitTypeDef GPIO_InitStructure = {0};

    // 1. Clear PE bit.
    CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_PE);

    //  2. Configure the SCL and SDA I/Os as General Purpose Output Open-Drain, High level (Write 1 to GPIOx_ODR).
    HAL_I2C_DeInit(hi2c);

    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStructure.Pull = GPIO_NOPULL;

    GPIO_InitStructure.Pin = GPIO_PIN_8; // SCL // если пин другой, то укажите нужный
    HAL_GPIO_Init(GPIOB, &GPIO_InitStructure); // если порт другой, то укажите нужную букву GPIOх, и ниже там все порты и пины поменяйте на своё

    GPIO_InitStructure.Pin = GPIO_PIN_9; // SDA
    HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

    // 3. Check SCL and SDA High level in GPIOx_IDR.
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);

    wait_for_gpio_state_timeout(GPIOB, GPIO_PIN_8, GPIO_PIN_SET, timeout);
    wait_for_gpio_state_timeout(GPIOB, GPIO_PIN_9, GPIO_PIN_SET, timeout);

    // 4. Configure the SDA I/O as General Purpose Output Open-Drain, Low level (Write 0 to GPIOx_ODR).
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);

    // 5. Check SDA Low level in GPIOx_IDR.
    wait_for_gpio_state_timeout(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET, timeout);

    // 6. Configure the SCL I/O as General Purpose Output Open-Drain, Low level (Write 0 to GPIOx_ODR).
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);

    // 7. Check SCL Low level in GPIOx_IDR.
    wait_for_gpio_state_timeout(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET, timeout);

    // 8. Configure the SCL I/O as General Purpose Output Open-Drain, High level (Write 1 to GPIOx_ODR).
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);

    // 9. Check SCL High level in GPIOx_IDR.
    wait_for_gpio_state_timeout(GPIOB, GPIO_PIN_8, GPIO_PIN_SET, timeout);

    // 10. Configure the SDA I/O as General Purpose Output Open-Drain , High level (Write 1 to GPIOx_ODR).
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);

    // 11. Check SDA High level in GPIOx_IDR.
    wait_for_gpio_state_timeout(GPIOB, GPIO_PIN_9, GPIO_PIN_SET, timeout);

    // 12. Configure the SCL and SDA I/Os as Alternate function Open-Drain.
    GPIO_InitStructure.Mode = GPIO_MODE_AF_OD;
    //GPIO_InitStructure.Alternate = GPIO_AF4_I2C2; // F4

    GPIO_InitStructure.Pin = GPIO_PIN_8;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

    GPIO_InitStructure.Pin = GPIO_PIN_9;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStructure);

    // 13. Set SWRST bit in I2Cx_CR1 register.
    SET_BIT(hi2c->Instance->CR1, I2C_CR1_SWRST);
    __ASM("nop");

    /* 14. Clear SWRST bit in I2Cx_CR1 register. */
    CLEAR_BIT(hi2c->Instance->CR1, I2C_CR1_SWRST);
    __ASM("nop");

    /* 15. Enable the I2C peripheral by setting the PE bit in I2Cx_CR1 register */
    SET_BIT(hi2c->Instance->CR1, I2C_CR1_PE);
    __ASM("nop");
    

    // Call initialization function.
    HAL_I2C_Init(hi2c);
}

int _I2CWrite(VL53L0X_DEV Dev, uint8_t *pdata, uint32_t count) 
{
  int status;
  int i2c_time_out = I2C_TIME_OUT_BASE+ count* I2C_TIME_OUT_BYTE;

  status = HAL_I2C_Master_Transmit(Dev->I2cHandle, Dev->I2cDevAddr, pdata, count, i2c_time_out);
  if (status != HAL_OK)
  {
    I2C_ClearBusyFlagErratum(Dev->I2cHandle, I2C_TIME_OUT_BASE);
  }
  return status;
}

int _I2CRead(VL53L0X_DEV Dev, uint8_t *pdata, uint32_t count) 
{
  int status;
  int i2c_time_out = I2C_TIME_OUT_BASE+ count* I2C_TIME_OUT_BYTE;
  
  status = HAL_I2C_Master_Receive(Dev->I2cHandle, Dev->I2cDevAddr|1, pdata, count, i2c_time_out);
  if (status != HAL_OK)
  {
    I2C_ClearBusyFlagErratum(Dev->I2cHandle, I2C_TIME_OUT_BASE);
  }
  return status;
}

// the ranging_sensor_comms.dll will take care of the page selection
VL53L0X_Error VL53L0X_WriteMulti(VL53L0X_DEV Dev, uint8_t index, uint8_t *pdata, uint32_t count) 
{
  static uint8_t data[32];
  
  if (count >=(sizeof (data)-1))
  {
    return  VL53L0X_ERROR_UNDEFINED;
  }
  
  data[0] = index;
  memcpy(data+1,pdata,count);
  
  HAL_StatusTypeDef status = HAL_I2C_Master_Transmit(Dev->I2cHandle, Dev->I2cDevAddr, data, count+1, I2C_TIME_OUT_BASE);  
  if (status != HAL_OK)
  {
    I2C_ClearBusyFlagErratum(Dev->I2cHandle, I2C_TIME_OUT_BASE);
  }
  return status == HAL_OK ? VL53L0X_ERROR_NONE : VL53L0X_ERROR_UNDEFINED;
}

// the ranging_sensor_comms.dll will take care of the page selection
VL53L0X_Error VL53L0X_ReadMulti(VL53L0X_DEV Dev, uint8_t index, uint8_t *pdata, uint32_t count) 
{
  HAL_StatusTypeDef status = HAL_OK;
  if ((status=HAL_I2C_Master_Transmit(Dev->I2cHandle, Dev->I2cDevAddr, &index, 1, I2C_TIME_OUT_BASE)) != HAL_OK)
  {
    if (status != HAL_OK)
    {
      I2C_ClearBusyFlagErratum(Dev->I2cHandle, I2C_TIME_OUT_BASE);
    }
    return VL53L0X_ERROR_CONTROL_INTERFACE;
  }
  status = HAL_I2C_Mem_Read(Dev->I2cHandle, Dev->I2cDevAddr, index, 1, pdata, count, I2C_TIME_OUT_BASE);
  if (status != HAL_OK)
  {
    I2C_ClearBusyFlagErratum(Dev->I2cHandle, I2C_TIME_OUT_BASE);
  }
  return status == HAL_OK ? VL53L0X_ERROR_NONE : VL53L0X_ERROR_UNDEFINED;
}

VL53L0X_Error VL53L0X_WrByte(VL53L0X_DEV Dev, uint8_t index, uint8_t data)
{
  uint8_t buff[2];
  buff[0] = index;
  buff[1] = data;
 
  HAL_StatusTypeDef status = HAL_I2C_Master_Transmit(Dev->I2cHandle, Dev->I2cDevAddr, buff, 2, I2C_TIME_OUT_BASE);
  if (status != HAL_OK)
  {
    I2C_ClearBusyFlagErratum(Dev->I2cHandle, I2C_TIME_OUT_BASE);
  }
  return status == HAL_OK ? VL53L0X_ERROR_NONE : VL53L0X_ERROR_UNDEFINED;
}

VL53L0X_Error VL53L0X_WrWord(VL53L0X_DEV Dev, uint8_t index, uint16_t data) 
{
  uint8_t buff[3];
  buff[2] = data & 0xFF;
  buff[1] = data >> 8;
  buff[0] = index;
  
  HAL_StatusTypeDef status = HAL_I2C_Master_Transmit(Dev->I2cHandle, Dev->I2cDevAddr, buff, 3, I2C_TIME_OUT_BASE);
  if (status != HAL_OK)
  {
    I2C_ClearBusyFlagErratum(Dev->I2cHandle, I2C_TIME_OUT_BASE);
  }
  return status == HAL_OK ? VL53L0X_ERROR_NONE : VL53L0X_ERROR_UNDEFINED;
}



VL53L0X_Error VL53L0X_WrDWord(VL53L0X_DEV Dev, uint8_t index, uint32_t data) 
{
  uint8_t buff[5];
 
  buff[4] = data & 0xFF;
  buff[3] = data >> 8;
  buff[2] = data >> 16;
  buff[1] = data >> 24;
  buff[0] = index;
  HAL_StatusTypeDef status = HAL_I2C_Master_Transmit(Dev->I2cHandle, Dev->I2cDevAddr, buff, 5, I2C_TIME_OUT_BASE);
  if (status != HAL_OK)
  {
    I2C_ClearBusyFlagErratum(Dev->I2cHandle, I2C_TIME_OUT_BASE);
  }
  return status == HAL_OK ? VL53L0X_ERROR_NONE : VL53L0X_ERROR_UNDEFINED;
}

VL53L0X_Error VL53L0X_UpdateByte(VL53L0X_DEV Dev, uint8_t index, uint8_t AndData, uint8_t OrData) 
{
  VL53L0X_Error Status = VL53L0X_ERROR_NONE;
  uint8_t data;
  
  Status = VL53L0X_RdByte(Dev, index, &data);
  if (Status) 
  {
    goto done;
  }
  data = (data & AndData) | OrData;
  Status = VL53L0X_WrByte(Dev, index, data);
  done:
    return Status;
}

VL53L0X_Error VL53L0X_RdByte(VL53L0X_DEV Dev, uint8_t index, uint8_t *data) 
{
  if ((HAL_I2C_Master_Transmit(Dev->I2cHandle, Dev->I2cDevAddr, &index, 1, I2C_TIME_OUT_BASE)) != HAL_OK)
  {
    I2C_ClearBusyFlagErratum(Dev->I2cHandle, I2C_TIME_OUT_BASE);
    return VL53L0X_ERROR_CONTROL_INTERFACE;
  }
  if ((HAL_I2C_Master_Receive(Dev->I2cHandle, Dev->I2cDevAddr, data, 1, I2C_TIME_OUT_BASE)) != HAL_OK) 
  {
    I2C_ClearBusyFlagErratum(Dev->I2cHandle, I2C_TIME_OUT_BASE);
    return VL53L0X_ERROR_CONTROL_INTERFACE;
  }
  return VL53L0X_ERROR_NONE;
}

VL53L0X_Error VL53L0X_RdWord(VL53L0X_DEV Dev, uint8_t index, uint16_t *data) 
{
  if ((HAL_I2C_Master_Transmit(Dev->I2cHandle, Dev->I2cDevAddr, &index, 1, I2C_TIME_OUT_BASE)) != HAL_OK)
  {
    I2C_ClearBusyFlagErratum(Dev->I2cHandle, I2C_TIME_OUT_BASE);
    return VL53L0X_ERROR_CONTROL_INTERFACE;
  }
  
  uint8_t buff[2];
  VL53L0X_Error status = VL53L0X_ReadMulti(Dev, index, buff, 2);
  
  uint16_t tmp;
  tmp = buff[0];
  tmp <<= 8;
  tmp |= buff[1];
  *data = tmp;
  
  return status;
}

VL53L0X_Error VL53L0X_RdDWord(VL53L0X_DEV Dev, uint8_t index, uint32_t *data) 
{
  if ((HAL_I2C_Master_Transmit(Dev->I2cHandle, Dev->I2cDevAddr, &index, 1, I2C_TIME_OUT_BASE)) != HAL_OK)
  {
    I2C_ClearBusyFlagErratum(Dev->I2cHandle, I2C_TIME_OUT_BASE);
    return VL53L0X_ERROR_CONTROL_INTERFACE;//-x;
  }
    
  uint8_t buff[4];
  VL53L0X_Error status = VL53L0X_ReadMulti(Dev, index, buff, 4);
 
  uint32_t tmp;
  tmp = buff[0];
  tmp <<= 8;
  tmp |= buff[1];
  tmp <<= 8;
  tmp |= buff[2];
  tmp <<= 8;
  tmp |= buff[3];
  
  *data = tmp;
  
  return status;
}

VL53L0X_Error VL53L0X_PollingDelay(VL53L0X_DEV Dev) 
{
  VL53L0X_Error status = VL53L0X_ERROR_NONE;

  // do nothing
  VL53L0X_OsDelay();
  return status;
}

//end of file
