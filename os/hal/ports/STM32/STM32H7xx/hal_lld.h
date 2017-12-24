/*
    ChibiOS - Copyright (C) 2006..2016 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/**
 * @file    STM32H7xx/hal_lld.h
 * @brief   STM32H7xx HAL subsystem low level driver header.
 * @pre     This module requires the following macros to be defined in the
 *          @p board.h file:
 *          - STM32_LSECLK.
 *          - STM32_LSEDRV.
 *          - STM32_LSE_BYPASS (optionally).
 *          - STM32_HSECLK.
 *          - STM32_HSE_BYPASS (optionally).
 *          - STM32_VDD (as hundredths of Volt).
 *          .
 *          One of the following macros must also be defined:
 *          - STM32H743xx, STM32H753xx very high-performance MCUs.
 *          .
 *
 * @addtogroup HAL
 * @{
 */

#ifndef HAL_LLD_H
#define HAL_LLD_H

#include "stm32_registry.h"

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/**
 * @name    Platform identification macros
 * @{
 */
#if defined(STM32H743xx) || defined(__DOXYGEN__)
#define PLATFORM_NAME           "STM32H743 Very High Performance with DSP and FPU"

#elif defined(STM32H753xx)
#define PLATFORM_NAME           "STM32H753 Very High Performance with DSP and FPU"

#else
#error "STM32H7xx device not specified"
#endif
/** @} */

/**
 * @name    Sub-family identifier
 */
#if !defined(STM32H7XX) || defined(__DOXYGEN__)
#define STM32H7XX
#endif
/** @} */

/**
 * @name    Absolute Maximum Ratings
 * @{
 */
/**
 * @brief   Absolute maximum system clock.
 */
#define STM32_SYSCLK_MAX        400000000

/**
 * @brief   Absolute maximum HCLK clock.
 */
#define STM32_HCLK_MAX          200000000

/**
 * @brief   Maximum HSE clock frequency.
 */
#define STM32_HSECLK_MAX        48000000

/**
 * @brief   Maximum HSE clock frequency using an external source.
 */
#define STM32_HSECLK_BYP_MAX    50000000

/**
 * @brief   Minimum HSE clock frequency.
 */
#define STM32_HSECLK_MIN        4000000

/**
 * @brief   Minimum HSE clock frequency.
 */
#define STM32_HSECLK_BYP_MIN    4000000

/**
 * @brief   Maximum LSE clock frequency.
 */
#define STM32_LSECLK_MAX        32768

/**
 * @brief   Maximum LSE clock frequency.
 */
#define STM32_LSECLK_BYP_MAX    1000000

/**
 * @brief   Minimum LSE clock frequency.
 */
#define STM32_LSECLK_MIN        32768

/**
 * @brief   Minimum PLLs input clock frequency..
 */
#define STM32_PLLIN_MIN         1000000

/**
 * @brief   PLLs input threshold frequency 1.
 */
#define STM32_PLLIN_THRESHOLD1  2000000

/**
 * @brief   PLLs input threshold frequency 2.
 */
#define STM32_PLLIN_THRESHOLD2  4000000

/**
 * @brief   PLLs input threshold frequency 3.
 */
#define STM32_PLLIN_THRESHOLD3  8000000

/**
 * @brief   Maximum PLLs input clock frequency.
 */
#define STM32_PLLIN_MAX         16000000

/**
 * @brief   Minimum PLLs VCO clock frequency.
 */
#define STM32_PLLVCO_MIN        150000000

/**
 * @brief   Threshold PLLs clock frequency.
 */
#define STM32_PLLVCO_THRESHOLD  420000000

/**
 * @brief   Maximum PLLs VCOH clock frequency.
 */
#define STM32_PLLVCO_MAX        836000000

/**
 * @brief   Maximum APB1 clock frequency.
 */
#define STM32_PCLK1_MAX         (STM32_HCLK_MAX / 2)

/**
 * @brief   Maximum APB2 clock frequency.
 */
#define STM32_PCLK2_MAX         (STM32_HCLK_MAX / 2)

/**
 * @brief   Maximum APB3 clock frequency.
 */
#define STM32_PCLK3_MAX         (STM32_HCLK_MAX / 2)

/**
 * @brief   Maximum APB4 clock frequency.
 */
#define STM32_PCLK4_MAX         (STM32_HCLK_MAX / 2)

/**
 * @brief   Maximum SPI1, SPI2 and SPI3 max clock frequency.
 */
#define STM32_SPI123_MAX        133000000

/**
 * @brief   Maximum SPI4, SPI5 and SPI6 max clock frequency.
 */
#define STM32_SPI456_MAX        100000000
/** @} */

/**
 * @name    Internal clock sources
 * @{
 */
#define STM32_HSICLK            64000000
#define STM32_HSI48CLK          48000000
#define STM32_CSICLK            4000000
#define STM32_LSICLK            32000
/** @} */

/**
 * @name    Register helpers not found in ST headers
 * @{
 */
#define RCC_CR_HSIDIV_VALUE(n)          ((n) << 3U)

#define RCC_CFGR_SW_VALUE(n)            ((n) << 0U)
#define RCC_CFGR_RTCPRE_VALUE(n)        ((n) << 8U)
#define RCC_CFGR_MCO1PRE_VALUE(n)       ((n) << 18U)
#define RCC_CFGR_MCO1_VALUE(n)          ((n) << 22U)
#define RCC_CFGR_MCO2PRE_VALUE(n)       ((n) << 25U)
#define RCC_CFGR_MCO2_VALUE(n)          ((n) << 29U)

#define RCC_D1CFGR_D1HPRE_VALUE(n)      ((n) << RCC_D1CFGR_HPRE_Pos)
#define RCC_D1CFGR_D1CPRE_VALUE(n)      ((n) << RCC_D1CFGR_D1CPRE_Pos)
#define RCC_D1CFGR_D1PPRE3_VALUE(n)     ((n) << RCC_D1CFGR_D1PPRE_Pos)

#define RCC_D2CFGR_D2PPRE1_VALUE(n)     ((n) << RCC_D2CFGR_D2PPRE1_Pos)
#define RCC_D2CFGR_D2PPRE2_VALUE(n)     ((n) << RCC_D2CFGR_D2PPRE2_Pos)

#define RCC_D3CFGR_D3PPRE4_VALUE(n)     ((n) << RCC_D3CFGR_D3PPRE_Pos)

#define RCC_PLLCKSELR_PLLSRC_VALUE(n)   ((n) << RCC_PLLCKSELR_PLLSRC_Pos)

#define RCC_PLLCKSELR_DIVM1_VALUE(n)    ((n) << RCC_PLLCKSELR_DIVM1_Pos)
#define RCC_PLLCKSELR_DIVM2_VALUE(n)    ((n) << RCC_PLLCKSELR_DIVM2_Pos)
#define RCC_PLLCKSELR_DIVM3_VALUE(n)    ((n) << RCC_PLLCKSELR_DIVM3_Pos)

#define RCC_PLL1DIVR_DIVN1_VALUE(n)     ((n) << RCC_PLL1DIVR_N1)
#define RCC_PLL1DIVR_DIVP1_VALUE(n)     ((n) << RCC_PLL1DIVR_P1)
#define RCC_PLL1DIVR_DIVQ1_VALUE(n)     ((n) << RCC_PLL1DIVR_Q1)
#define RCC_PLL1DIVR_DIVR1_VALUE(n)     ((n) << RCC_PLL1DIVR_R1)

#define RCC_PLL1FRACR_FRACN1_VALUE(n)   ((n) << RCC_PLL1FRACR_FRACN1_Pos)

#define RCC_PLL2DIVR_DIVN2_VALUE(n)     ((n) << RCC_PLL2DIVR_N2)
#define RCC_PLL2DIVR_DIVP2_VALUE(n)     ((n) << RCC_PLL2DIVR_P2)
#define RCC_PLL2DIVR_DIVQ2_VALUE(n)     ((n) << RCC_PLL2DIVR_Q2)
#define RCC_PLL2DIVR_DIVR2_VALUE(n)     ((n) << RCC_PLL2DIVR_R2)

#define RCC_PLL2FRACR_FRACN2_VALUE(n)   ((n) << RCC_PLL2FRACR_FRACN2_Pos)

#define RCC_PLL3DIVR_DIVN3_VALUE(n)     ((n) << RCC_PLL3DIVR_N3)
#define RCC_PLL3DIVR_DIVP3_VALUE(n)     ((n) << RCC_PLL3DIVR_P3)
#define RCC_PLL3DIVR_DIVQ3_VALUE(n)     ((n) << RCC_PLL3DIVR_Q3)
#define RCC_PLL3DIVR_DIVR3_VALUE(n)     ((n) << RCC_PLL3DIVR_R3)

#define RCC_PLL3FRACR_FRACN3_VALUE(n)   ((n) << RCC_PLL3FRACR_FRACN3_Pos)

#define RCC_D1CCIPR_CKPERSEL_VALUE(n)   ((n) << RCC_D1CCIPR_CKPERSEL_Pos)

#define RCC_BDCR_RTCSEL_VALUE(n)        ((n) << RCC_BDCR_RTCSEL_Pos)
/** @} */

/**
 * @name    Configuration switches to be used in @p mcuconf.h
 * @{
 */
#define STM32_VOS_SCALE3                (PWR_D3CR_VOS_0)
#define STM32_VOS_SCALE2                (PWR_D3CR_VOS_1)
#define STM32_VOS_SCALE1                (PWR_D3CR_VOS_1 | PWR_D3CR_VOS_0)

#define STM32_SW_HSI_CK                 RCC_CFGR_SW_VALUE(0U)
#define STM32_SW_CSI_CK                 RCC_CFGR_SW_VALUE(1U)
#define STM32_SW_HSE_CK                 RCC_CFGR_SW_VALUE(2U)
#define STM32_SW_PLL1_P_CK              RCC_CFGR_SW_VALUE(3U)

#define STM32_D1CPRE_DIV1               RCC_D1CFGR_D1CPRE_VALUE(0U)
#define STM32_D1CPRE_DIV2               RCC_D1CFGR_D1CPRE_VALUE(8U)
#define STM32_D1CPRE_DIV4               RCC_D1CFGR_D1CPRE_VALUE(9U)
#define STM32_D1CPRE_DIV8               RCC_D1CFGR_D1CPRE_VALUE(10U)
#define STM32_D1CPRE_DIV16              RCC_D1CFGR_D1CPRE_VALUE(11U)
#define STM32_D1CPRE_DIV64              RCC_D1CFGR_D1CPRE_VALUE(12U)
#define STM32_D1CPRE_DIV128             RCC_D1CFGR_D1CPRE_VALUE(13U)
#define STM32_D1CPRE_DIV256             RCC_D1CFGR_D1CPRE_VALUE(14U)
#define STM32_D1CPRE_DIV512             RCC_D1CFGR_D1CPRE_VALUE(15U)

#define STM32_D1HPRE_DIV1               RCC_D1CFGR_D1HPRE_VALUE(0U)
#define STM32_D1HPRE_DIV2               RCC_D1CFGR_D1HPRE_VALUE(8U)
#define STM32_D1HPRE_DIV4               RCC_D1CFGR_D1HPRE_VALUE(9U)
#define STM32_D1HPRE_DIV8               RCC_D1CFGR_D1HPRE_VALUE(10U)
#define STM32_D1HPRE_DIV16              RCC_D1CFGR_D1HPRE_VALUE(11U)
#define STM32_D1HPRE_DIV64              RCC_D1CFGR_D1HPRE_VALUE(12U)
#define STM32_D1HPRE_DIV128             RCC_D1CFGR_D1HPRE_VALUE(13U)
#define STM32_D1HPRE_DIV256             RCC_D1CFGR_D1HPRE_VALUE(14U)
#define STM32_D1HPRE_DIV512             RCC_D1CFGR_D1HPRE_VALUE(15U)

#define STM32_D1PPRE3_DIV1              RCC_D1CFGR_D1PPRE3_VALUE(0U)
#define STM32_D1PPRE3_DIV2              RCC_D1CFGR_D1PPRE3_VALUE(4U)
#define STM32_D1PPRE3_DIV4              RCC_D1CFGR_D1PPRE3_VALUE(5U)
#define STM32_D1PPRE3_DIV8              RCC_D1CFGR_D1PPRE3_VALUE(6U)
#define STM32_D1PPRE3_DIV16             RCC_D1CFGR_D1PPRE3_VALUE(7U)

#define STM32_D2PPRE1_DIV1              RCC_D2CFGR_D2PPRE1_VALUE(0U)
#define STM32_D2PPRE1_DIV2              RCC_D2CFGR_D2PPRE1_VALUE(4U)
#define STM32_D2PPRE1_DIV4              RCC_D2CFGR_D2PPRE1_VALUE(5U)
#define STM32_D2PPRE1_DIV8              RCC_D2CFGR_D2PPRE1_VALUE(6U)
#define STM32_D2PPRE1_DIV16             RCC_D2CFGR_D2PPRE1_VALUE(7U)

#define STM32_D2PPRE2_DIV1              RCC_D2CFGR_D2PPRE2_VALUE(0U)
#define STM32_D2PPRE2_DIV2              RCC_D2CFGR_D2PPRE2_VALUE(4U)
#define STM32_D2PPRE2_DIV4              RCC_D2CFGR_D2PPRE2_VALUE(5U)
#define STM32_D2PPRE2_DIV8              RCC_D2CFGR_D2PPRE2_VALUE(6U)
#define STM32_D2PPRE2_DIV16             RCC_D2CFGR_D2PPRE2_VALUE(7U)

#define STM32_D3PPRE4_DIV1              RCC_D3CFGR_D3PPRE4_VALUE(0U)
#define STM32_D3PPRE4_DIV2              RCC_D3CFGR_D3PPRE4_VALUE(4U)
#define STM32_D3PPRE4_DIV4              RCC_D3CFGR_D3PPRE4_VALUE(5U)
#define STM32_D3PPRE4_DIV8              RCC_D3CFGR_D3PPRE4_VALUE(6U)
#define STM32_D3PPRE4_DIV16             RCC_D3CFGR_D3PPRE4_VALUE(7U)

#define STM32_HSIDIV_DIV1               RCC_CR_HSIDIV_VALUE(0U)
#define STM32_HSIDIV_DIV2               RCC_CR_HSIDIV_VALUE(1U)
#define STM32_HSIDIV_DIV4               RCC_CR_HSIDIV_VALUE(2U)
#define STM32_HSIDIV_DIV8               RCC_CR_HSIDIV_VALUE(3U)

#define STM32_MCO1SEL_HSI_CK            RCC_CFGR_MCO1_VALUE(0U)
#define STM32_MCO1SEL_LSE_CK            RCC_CFGR_MCO1_VALUE(1U)
#define STM32_MCO1SEL_HSE_CK            RCC_CFGR_MCO1_VALUE(2U)
#define STM32_MCO1SEL_PLL1_Q_CK         RCC_CFGR_MCO1_VALUE(3U)
#define STM32_MCO1SEL_HSI48_CK          RCC_CFGR_MCO1_VALUE(4U)

#define STM32_MCO2SEL_SYS_CK            RCC_CFGR_MCO2_VALUE(0U)
#define STM32_MCO2SEL_PLL2_P_CK         RCC_CFGR_MCO2_VALUE(1U)
#define STM32_MCO2SEL_HSE_CK            RCC_CFGR_MCO2_VALUE(2U)
#define STM32_MCO2SEL_PLL1_P_CK         RCC_CFGR_MCO2_VALUE(3U)
#define STM32_MCO2SEL_CSI_CK            RCC_CFGR_MCO2_VALUE(4U)
#define STM32_MCO2SEL_LSI_CK            RCC_CFGR_MCO2_VALUE(5U)

#define STM32_RTCSEL_MASK               RCC_BDCR_RTCSEL_Msk
#define STM32_RTCSEL_NOCLK              RCC_BDCR_RTCSEL_VALUE(0U)
#define STM32_RTCSEL_LSE_CK             RCC_BDCR_RTCSEL_VALUE(1U)
#define STM32_RTCSEL_LSI_CK             RCC_BDCR_RTCSEL_VALUE(2U)
#define STM32_RTCSEL_HSE_1M_CK          RCC_BDCR_RTCSEL_VALUE(3U)

#define STM32_PLLSRC_HSI_CK             RCC_PLLCKSELR_PLLSRC_VALUE(0U)
#define STM32_PLLSRC_CSI_CK             RCC_PLLCKSELR_PLLSRC_VALUE(1U)
#define STM32_PLLSRC_HSE_CK             RCC_PLLCKSELR_PLLSRC_VALUE(2U)

#define STM32_CKPERSEL_HSI_CK           RCC_D1CCIPR_CKPERSEL_VALUE(0U)
#define STM32_CKPERSEL_CSI_CK           RCC_D1CCIPR_CKPERSEL_VALUE(1U)
#define STM32_CKPERSEL_HSE_CK           RCC_D1CCIPR_CKPERSEL_VALUE(2U)
/** @} */

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/**
 * @name    Configuration options
 * @{
 */
/**
 * @brief   Disables the PWR/RCC initialization in the HAL.
 */
#if !defined(STM32_NO_INIT) || defined(__DOXYGEN__)
#define STM32_NO_INIT                       FALSE
#endif

/**
 * @brief   SYS_CK value assumed if @p STM32_NO_INIT is enabled.
 */
#if !defined(STM32_SYS_CK_ENFORCED_VALUE) || defined(__DOXYGEN__)
#define STM32_SYS_CK_ENFORCED_VALUE         STM32_HSICLK
#endif

/**
 * @brief   PWR CR1 initializer.
 */
#if !defined(STM32_PWR_CR1) || defined(__DOXYGEN__)
#define STM32_PWR_CR1                       (PWR_CR1_PVDEN |                \
                                             PWR_CR1_SVOS_1 |               \
                                             PWR_CR1_SVOS_0)
#endif

/**
 * @brief   PWR CR2 initializer.
 */
#if !defined(STM32_PWR_CR2) || defined(__DOXYGEN__)
#define STM32_PWR_CR2                       (PWR_CR2_BREN)
#endif

/**
 * @brief   PWR CR3 initializer.
 */
#if !defined(STM32_PWR_CR3) || defined(__DOXYGEN__)
#define STM32_PWR_CR3                       (PWR_CR3_SCUEN |                \
                                             PWR_CR3_LDOEN |                \
                                             PWR_CR3_USBREGEN |             \
                                             PWR_CR3_USB33DEN)
#endif

/**
 * @brief   PWR CPUCR initializer.
 */
#if !defined(STM32_PWR_CPUCR) || defined(__DOXYGEN__)
#define STM32_PWR_CPUCR                     0
#endif

/**
 * @brief   VOS setting.
 */
#if !defined(STM32_VOS) || defined(__DOXYGEN__)
#define STM32_VOS                           STM32_VOS_SCALE1
#endif

/**
 * @brief   Enables or disables the HSI clock source.
 */
#if !defined(STM32_HSI_ENABLED) || defined(__DOXYGEN__)
#define STM32_HSI_ENABLED                   TRUE
#endif

/**
 * @brief   Enables or disables the LSI clock source.
 */
#if !defined(STM32_LSI_ENABLED) || defined(__DOXYGEN__)
#define STM32_LSI_ENABLED                   FALSE
#endif

/**
 * @brief   Enables or disables the LSI clock source.
 */
#if !defined(STM32_CSI_ENABLED) || defined(__DOXYGEN__)
#define STM32_CSI_ENABLED                   FALSE
#endif

/**
 * @brief   Enables or disables the HSI48 clock source.
 */
#if !defined(STM32_HSI48_ENABLED) || defined(__DOXYGEN__)
#define STM32_HSI48_ENABLED                 TRUE
#endif

/**
 * @brief   Enables or disables the HSE clock source.
 */
#if !defined(STM32_HSE_ENABLED) || defined(__DOXYGEN__)
#define STM32_HSE_ENABLED                   TRUE
#endif

/**
 * @brief   Enables or disables the LSE clock source.
 */
#if !defined(STM32_LSE_ENABLED) || defined(__DOXYGEN__)
#define STM32_LSE_ENABLED                   TRUE
#endif

/**
 * @brief   HSI divider.
 */
#if !defined(STM32_HSIDIV) || defined(__DOXYGEN__)
#define STM32_HSIDIV                        STM32_HSIDIV_DIV1
#endif

/**
 * @brief   RTC HSE prescaler value.
 * @note    The allowed values are 2..63.
 */
#if !defined(STM32_RTCPRE_VALUE) || defined(__DOXYGEN__)
#define STM32_RTCPRE_VALUE                  8
#endif

/**
 * @brief   Clock source for all PLLs.
 */
#if !defined(STM32_PLLSRC) || defined(__DOXYGEN__)
#define STM32_PLLSRC                        STM32_PLLSRC_HSE_CK
#endif

/**
 * @brief   Masking of PLLCFGR register.
 * @note    By default all options in PLLCFGR are enabled, this option
 *          allows to mask specific bits for power saving reasons.
 *          Use with caution.
 */
#if !defined(STM32_PLLCFGR_MASK) || defined(__DOXYGEN__)
#define STM32_PLLCFGR_MASK                  ~0
#endif

/**
 * @brief   Enables or disables the PLL1.
 */
#if !defined(STM32_PLL1_ENABLED) || defined(__DOXYGEN__)
#define STM32_PLL1_ENABLED                  TRUE
#endif

/**
 * @brief   PLL1 DIVM divider.
 * @note    The allowed values are 1..63.
 */
#if !defined(STM32_PLL1_DIVM_VALUE) || defined(__DOXYGEN__)
#define STM32_PLL1_DIVM_VALUE               4
#endif

/**
 * @brief   PLL1 DIVN multiplier.
 * @note    The allowed values are 4..512.
 */
#if !defined(STM32_PLL1_DIVN_VALUE) || defined(__DOXYGEN__)
#define STM32_PLL1_DIVN_VALUE               400
#endif

/**
 * @brief   PLL1 FRACN multiplier, zero if no fractional part.
 * @note    The allowed values are 0..8191.
 */
#if !defined(STM32_PLL1_FRACN_VALUE) || defined(__DOXYGEN__)
#define STM32_PLL1_FRACN_VALUE              0
#endif

/**
 * @brief   PLL1 DIVP divider.
 * @note    The allowed values are 2..128, odd values not allowed.
 */
#if !defined(STM32_PLL1_DIVP_VALUE) || defined(__DOXYGEN__)
#define STM32_PLL1_DIVP_VALUE               2
#endif

/**
 * @brief   PLL1 DIVQ divider.
 * @note    The allowed values are 1..128.
 */
#if !defined(STM32_PLL1_DIVQ_VALUE) || defined(__DOXYGEN__)
#define STM32_PLL1_DIVQ_VALUE               8
#endif

/**
 * @brief   PLL1 DIVR divider.
 * @note    The allowed values are 1..128.
 */
#if !defined(STM32_PLL1_DIVR_VALUE) || defined(__DOXYGEN__)
#define STM32_PLL1_DIVR_VALUE               8
#endif

/**
 * @brief   Enables or disables the PLL2.
 */
#if !defined(STM32_PLL2_ENABLED) || defined(__DOXYGEN__)
#define STM32_PLL2_ENABLED                  TRUE
#endif

/**
 * @brief   PLL2 DIVM divider.
 * @note    The allowed values are 1..63.
 */
#if !defined(STM32_PLL2_DIVM_VALUE) || defined(__DOXYGEN__)
#define STM32_PLL2_DIVM_VALUE               4
#endif

/**
 * @brief   PLL2 DIVN multiplier.
 * @note    The allowed values are 4..512.
 */
#if !defined(STM32_PLL2_DIVN_VALUE) || defined(__DOXYGEN__)
#define STM32_PLL2_DIVN_VALUE               400
#endif

/**
 * @brief   PLL2 FRACN multiplier, zero if no fractional part.
 * @note    The allowed values are 0..8191.
 */
#if !defined(STM32_PLL2_FRACN_VALUE) || defined(__DOXYGEN__)
#define STM32_PLL2_FRACN_VALUE              0
#endif

/**
 * @brief   PLL2 DIVP divider.
 * @note    The allowed values are 2..128, odd values not allowed.
 */
#if !defined(STM32_PLL2_DIVP_VALUE) || defined(__DOXYGEN__)
#define STM32_PLL2_DIVP_VALUE               2
#endif

/**
 * @brief   PLL2 DIVQ divider.
 * @note    The allowed values are 1..128.
 */
#if !defined(STM32_PLL2_DIVQ_VALUE) || defined(__DOXYGEN__)
#define STM32_PLL2_DIVQ_VALUE               8
#endif

/**
 * @brief   PLL2 DIVR divider.
 * @note    The allowed values are 1..128.
 */
#if !defined(STM32_PLL2_DIVR_VALUE) || defined(__DOXYGEN__)
#define STM32_PLL2_DIVR_VALUE               8
#endif

/**
 * @brief   Enables or disables the PLL3.
 */
#if !defined(STM32_PLL3_ENABLED) || defined(__DOXYGEN__)
#define STM32_PLL3_ENABLED                  TRUE
#endif

/**
 * @brief   PLL3 DIVM divider.
 * @note    The allowed values are 1..63.
 */
#if !defined(STM32_PLL3_DIVM_VALUE) || defined(__DOXYGEN__)
#define STM32_PLL3_DIVM_VALUE               4
#endif

/**
 * @brief   PLL3 DIVN multiplier.
 * @note    The allowed values are 4..512.
 */
#if !defined(STM32_PLL3_DIVN_VALUE) || defined(__DOXYGEN__)
#define STM32_PLL3_DIVN_VALUE               400
#endif

/**
 * @brief   PLL3 FRACN multiplier, zero if no fractional part.
 * @note    The allowed values are 0..8191.
 */
#if !defined(STM32_PLL3_FRACN_VALUE) || defined(__DOXYGEN__)
#define STM32_PLL3_FRACN_VALUE              0
#endif

/**
 * @brief   PLL3 DIVP divider.
 * @note    The allowed values are 2..128, odd values not allowed.
 */
#if !defined(STM32_PLL3_DIVP_VALUE) || defined(__DOXYGEN__)
#define STM32_PLL3_DIVP_VALUE               2
#endif

/**
 * @brief   PLL3 DIVQ divider.
 * @note    The allowed values are 1..128.
 */
#if !defined(STM32_PLL3_DIVQ_VALUE) || defined(__DOXYGEN__)
#define STM32_PLL3_DIVQ_VALUE               8
#endif

/**
 * @brief   PLL3 DIVR divider.
 * @note    The allowed values are 1..128.
 */
#if !defined(STM32_PLL3_DIVR_VALUE) || defined(__DOXYGEN__)
#define STM32_PLL3_DIVR_VALUE               8
#endif

/**
 * @brief   Peripherals clock selector.
 */
#if !defined(STM32_CKPERSEL) || defined(__DOXYGEN__)
#define STM32_CKPERSEL                      STM32_CKPERSEL_HSE_CK
#endif

/**
 * @brief   MCO1 clock selector.
 */
#if !defined(STM32_MCO1SEL) || defined(__DOXYGEN__)
#define STM32_MCO1SEL                       STM32_MCO1SEL_HSI_CK
#endif

/**
 * @brief   MCO1 clock prescaler.
 */
#if !defined(STM32_MCO1PRE_VALUE) || defined(__DOXYGEN__)
#define STM32_MCO1PRE_VALUE                 4
#endif

/**
 * @brief   MCO2 clock selector.
 */
#if !defined(STM32_MCO2SEL) || defined(__DOXYGEN__)
#define STM32_MCO2SEL                       STM32_MCO2SEL_SYS_CK
#endif

/**
 * @brief   MCO2 clock prescaler.
 */
#if !defined(STM32_MCO2PRE_VALUE) || defined(__DOXYGEN__)
#define STM32_MCO2PRE_VALUE                 4
#endif

/**
 * @brief   Main clock source selection.
 * @note    This setting can be modified at runtime.
 */
#if !defined(STM32_SW) || defined(__DOXYGEN__)
#define STM32_SW                            STM32_SW_PLL1_P_CK1_P_CK
#endif

/**
 * @brief   RTC clock selector.
 * @note    This setting can be modified at runtime.
 */
#if !defined(STM32_RTCSEL) || defined(__DOXYGEN__)
#define STM32_RTCSEL                        STM32_RTCSEL_LSE_CK
#endif

/**
 * @brief   Clock domain 1 core bus prescaler.
 * @note    This setting can be modified at runtime.
 */
#if !defined(STM32_D1CPRE) || defined(__DOXYGEN__)
#define STM32_D1CPRE                        STM32_D1CPRE_DIV1
#endif

/**
 * @brief   Clock domain 1 HPRE prescaler.
 * @note    This setting can be modified at runtime.
 */
#if !defined(STM32_D1HPRE) || defined(__DOXYGEN__)
#define STM32_D1HPRE                        STM32_D1HPRE_DIV2
#endif

/**
 * @brief   Clock domain 1 peripherals bus prescaler.
 * @note    This setting can be modified at runtime.
 */
#if !defined(STM32_D1PPRE) || defined(__DOXYGEN__)
#define STM32_D1PPRE3                       STM32_D1PPRE3_DIV2
#endif

/**
 * @brief   Clock domain 2 peripherals bus 1 prescaler.
 * @note    This setting can be modified at runtime.
 */
#if !defined(STM32_D2PPRE1) || defined(__DOXYGEN__)
#define STM32_D2PPRE1                       STM32_D2PPRE1_DIV2
#endif

/**
 * @brief   Clock domain 2 peripherals bus 2 prescaler.
 * @note    This setting can be modified at runtime.
 */
#if !defined(STM32_D2PPRE2) || defined(__DOXYGEN__)
#define STM32_D2PPRE2                       STM32_D2PPRE2_DIV2
#endif

/**
 * @brief   Clock domain 3 peripherals bus prescaler.
 * @note    This setting can be modified at runtime.
 */
#if !defined(STM32_D3PPRE4) || defined(__DOXYGEN__)
#define STM32_D3PPRE4                       STM32_D3PPRE4_DIV2
#endif















#if 0
/**
 * @brief   I2S clock source.
 */
#if !defined(STM32_I2SSRC) || defined(__DOXYGEN__)
#define STM32_I2SSRC                        STM32_I2SSRC_PLLI2S
#endif

/**
 * @brief   PLLI2SN multiplier value.
 * @note    The allowed values are 49..432.
 */
#if !defined(STM32_PLLI2SN_VALUE) || defined(__DOXYGEN__)
#define STM32_PLLI2SN_VALUE                 192
#endif

/**
 * @brief   PLLI2SP divider value.
 * @note    The allowed values are 2, 4, 6 and 8.
 */
#if !defined(STM32_PLLI2SP_VALUE) || defined(__DOXYGEN__)
#define STM32_PLLI2SP_VALUE                 4
#endif

/**
 * @brief   PLLI2SQ divider value.
 * @note    The allowed values are 2..15.
 */
#if !defined(STM32_PLLI2SQ_VALUE) || defined(__DOXYGEN__)
#define STM32_PLLI2SQ_VALUE                 4
#endif

/**
 * @brief   PLLI2SDIVQ divider value (SAI clock divider).
 */
#if !defined(STM32_PLLI2SDIVQ_VALUE) || defined(__DOXYGEN__)
#define STM32_PLLI2SDIVQ_VALUE              2
#endif

/**
 * @brief   PLLI2SR divider value.
 * @note    The allowed values are 2..7.
 */
#if !defined(STM32_PLLI2SR_VALUE) || defined(__DOXYGEN__)
#define STM32_PLLI2SR_VALUE                 4
#endif

/**
 * @brief   PLLSAIN multiplier value.
 * @note    The allowed values are 49..432.
 */
#if !defined(STM32_PLLSAIN_VALUE) || defined(__DOXYGEN__)
#define STM32_PLLSAIN_VALUE                 192
#endif

/**
 * @brief   PLLSAIP divider value.
 * @note    The allowed values are 2, 4, 6 and 8.
 */
#if !defined(STM32_PLLSAIP_VALUE) || defined(__DOXYGEN__)
#define STM32_PLLSAIP_VALUE                 4
#endif

/**
 * @brief   PLLSAIQ divider value.
 * @note    The allowed values are 2..15.
 */
#if !defined(STM32_PLLSAIQ_VALUE) || defined(__DOXYGEN__)
#define STM32_PLLSAIQ_VALUE                 4
#endif

/**
 * @brief   PLLSAIR divider value.
 * @note    The allowed values are 2..7.
 */
#if !defined(STM32_PLLSAIR_VALUE) || defined(__DOXYGEN__)
#define STM32_PLLSAIR_VALUE                 4
#endif

/**
 * @brief   PLLSAIDIVQ divider value (SAI clock divider).
 */
#if !defined(STM32_PLLSAIDIVQ_VALUE) || defined(__DOXYGEN__)
#define STM32_PLLSAIDIVQ_VALUE              2
#endif

/**
 * @brief   PLLSAIDIVR divider value (LCD clock divider).
 */
#if !defined(STM32_PLLSAIDIVR_VALUE) || defined(__DOXYGEN__)
#define STM32_PLLSAIDIVR_VALUE              2
#endif

/**
 * @brief   SAI1SEL value (SAI1 clock source).
 */
#if !defined(STM32_SAI1SEL) || defined(__DOXYGEN__)
#define STM32_SAI1SEL                       STM32_SAI1SEL_OFF
#endif

/**
 * @brief   SAI2SEL value (SAI2 clock source).
 */
#if !defined(STM32_SAI2SEL) || defined(__DOXYGEN__)
#define STM32_SAI2SEL                       STM32_SAI2SEL_OFF
#endif

/**
 * @brief   LCD-TFT clock enable switch.
 */
#if !defined(STM32_LCDTFT_REQUIRED) || defined(__DOXYGEN__)
#define STM32_LCDTFT_REQUIRED               FALSE
#endif

/**
 * @brief   USART1 clock source.
 */
#if !defined(STM32_USART1SEL) || defined(__DOXYGEN__)
#define STM32_USART1SEL                     STM32_USART1SEL_PCLK2
#endif

/**
 * @brief   USART2 clock source.
 */
#if !defined(STM32_USART2SEL) || defined(__DOXYGEN__)
#define STM32_USART2SEL                     STM32_USART2SEL_PCLK1
#endif

/**
 * @brief   USART3 clock source.
 */
#if !defined(STM32_USART3SEL) || defined(__DOXYGEN__)
#define STM32_USART3SEL                     STM32_USART3SEL_PCLK1
#endif

/**
 * @brief   UART4 clock source.
 */
#if !defined(STM32_UART4SEL) || defined(__DOXYGEN__)
#define STM32_UART4SEL                      STM32_UART4SEL_PCLK1
#endif

/**
 * @brief   UART5 clock source.
 */
#if !defined(STM32_UART5SEL) || defined(__DOXYGEN__)
#define STM32_UART5SEL                      STM32_UART5SEL_PCLK1
#endif

/**
 * @brief   USART6 clock source.
 */
#if !defined(STM32_USART6SEL) || defined(__DOXYGEN__)
#define STM32_USART6SEL                     STM32_USART6SEL_PCLK2
#endif

/**
 * @brief   UART7 clock source.
 */
#if !defined(STM32_UART7SEL) || defined(__DOXYGEN__)
#define STM32_UART7SEL                      STM32_UART7SEL_PCLK1
#endif

/**
 * @brief   UART8 clock source.
 */
#if !defined(STM32_UART8SEL) || defined(__DOXYGEN__)
#define STM32_UART8SEL                      STM32_UART8SEL_PCLK1
#endif

/**
 * @brief   I2C1 clock source.
 */
#if !defined(STM32_I2C1SEL) || defined(__DOXYGEN__)
#define STM32_I2C1SEL                       STM32_I2C1SEL_PCLK1
#endif

/**
 * @brief   I2C2 clock source.
 */
#if !defined(STM32_I2C2SEL) || defined(__DOXYGEN__)
#define STM32_I2C2SEL                       STM32_I2C2SEL_PCLK1
#endif

/**
 * @brief   I2C3 clock source.
 */
#if !defined(STM32_I2C3SEL) || defined(__DOXYGEN__)
#define STM32_I2C3SEL                       STM32_I2C3SEL_PCLK1
#endif

/**
 * @brief   I2C4 clock source.
 */
#if !defined(STM32_I2C4SEL) || defined(__DOXYGEN__)
#define STM32_I2C4SEL                       STM32_I2C4SEL_PCLK1
#endif

/**
 * @brief   LPTIM1 clock source.
 */
#if !defined(STM32_LPTIM1SEL) || defined(__DOXYGEN__)
#define STM32_LPTIM1SEL                     STM32_LPTIM1SEL_PCLK1
#endif

/**
 * @brief   CEC clock source.
 */
#if !defined(STM32_CECSEL) || defined(__DOXYGEN__)
#define STM32_CECSEL                        STM32_CECSEL_LSE
#endif

/**
 * @brief   PLL48CLK clock source.
 */
#if !defined(STM32_CK48MSEL) || defined(__DOXYGEN__)
#define STM32_CK48MSEL                      STM32_CK48MSEL_PLL
#endif

/**
 * @brief   SDMMC clock source.
 */
#if !defined(STM32_SDMMCSEL) || defined(__DOXYGEN__)
#define STM32_SDMMCSEL                      STM32_SDMMCSEL_PLL48CLK
#endif

/**
 * @brief   SRAM2 cache-ability.
 * @note    This setting uses the MPU region 7 if at @p TRUE.
 */
#if !defined(STM32_SRAM2_NOCACHE) || defined(__DOXYGEN__)
#define STM32_SRAM2_NOCACHE                 FALSE
#endif
#endif
/** @} */

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*
 * Configuration-related checks.
 */
#if !defined(STM32H7xx_MCUCONF)
#error "Using a wrong mcuconf.h file, STM32H7xx_MCUCONF not defined"
#endif

/*
 * Board file checks.
 */
#if !defined(STM32_LSECLK)
#error "STM32_LSECLK not defined in board.h"
#endif
#if !defined(STM32_LSEDRV)
#error "STM32_LSEDRV not defined in board.h"
#endif
#if !defined(STM32_HSECLK)
#error "STM32_HSECLK not defined in board.h"
#endif
#if !defined(STM32_VDD)
#error "STM32_VDD not defined in board.h"
#endif

/**
 * @name    Constants depending on VOS setting
 * @{
 */
#if (STM32_VOS == STM32_VOS_SCALE1) || defined(__DOXYGEN__)
#define STM32_0WS_THRESHOLD         70000000
#define STM32_1WS_THRESHOLD         140000000
#define STM32_2WS_THRESHOLD         210000000
#define STM32_3WS_THRESHOLD         0
#define STM32_4WS_THRESHOLD         0
#define STM32_PLLOUT_MAX            400000000
#define STM32_PLLOUT_MIN            1500000

#elif STM32_VOS == STM32_VOS_SCALE2
#define STM32_0WS_THRESHOLD         55000000
#define STM32_1WS_THRESHOLD         110000000
#define STM32_2WS_THRESHOLD         165000000
#define STM32_3WS_THRESHOLD         220000000
#define STM32_4WS_THRESHOLD         0
#define STM32_PLLOUT_MAX            300000000
#define STM32_PLLOUT_MIN            1500000

#elif STM32_VOS == STM32_VOS_SCALE3
#define STM32_0WS_THRESHOLD         45000000
#define STM32_1WS_THRESHOLD         90000000
#define STM32_2WS_THRESHOLD         135000000
#define STM32_3WS_THRESHOLD         180000000
#define STM32_4WS_THRESHOLD         225000000
#define STM32_PLLOUT_MAX            200000000
#define STM32_PLLOUT_MIN            1500000

#else
#error "invalid STM32_VOS setting specified"
#endif
/** @} */

/*
 * HSI related checks.
 */
#if STM32_HSI_ENABLED
#else /* !STM32_HSI_ENABLED */

#if STM32_SW == STM32_SW_HSI_CK
#error "HSI not enabled, required by STM32_SW"
#endif

#if (STM32_PLLSRC == STM32_PLLSRC_HSI_CK) &&                                \
    (STM32_PLL1_ENABLED || STM32_PLL2_ENABLED || STM32_PLL3_ENABLED)
#error "HSI not enabled, required by STM32_PLLSRC and STM32_PLLx_ENABLED"
#endif

#if STM32_CKPERSEL == STM32_CKPERSEL_HSI_CK
#error "HSI not enabled, required by STM32_CKPERSEL"
#endif

#if STM32_MCO1SEL == STM32_MCO1SEL_HSI_CK
#error "HSI not enabled, required by STM32_MCO1SEL"
#endif

#endif /* !STM32_HSI_ENABLED */

/*
 * HSI48 related checks.
 */
#if STM32_HSI48_ENABLED
#else /* !STM32_HSI48_ENABLED */

#if STM32_MCO1SEL == STM32_MCO1SEL_HSI48_CK
#error "HSI48 not enabled, required by STM32_MCO1SEL"
#endif

#endif /* !STM32_HSI48_ENABLED */

/*
 * CSI related checks.
 */
#if STM32_CSI_ENABLED
#else /* !STM32_CSI_ENABLED */

#if STM32_SW == STM32_SW_CSI_CK
#error "CSI not enabled, required by STM32_SW"
#endif

#if (STM32_PLLSRC == STM32_PLLSRC_CSI_CK) &&                                \
    (STM32_PLL1_ENABLED || STM32_PLL2_ENABLED || STM32_PLL3_ENABLED)
#error "CSI not enabled, required by STM32_PLLSRC and STM32_PLLx_ENABLED"
#endif

#if STM32_CKPERSEL == STM32_CKPERSEL_CSI_CK
#error "CSI not enabled, required by STM32_CKPERSEL"
#endif

#if STM32_MCO2SEL == STM32_MCO2SEL_CSI_CK
#error "CSI not enabled, required by STM32_MCO2SEL"
#endif

#endif /* !STM32_CSI_ENABLED */

/*
 * HSE related checks.
 */
#if STM32_HSE_ENABLED

#if STM32_HSECLK == 0
#error "HSE frequency not defined"
#else /* STM32_HSECLK != 0 */
#if defined(STM32_HSE_BYPASS)
#if (STM32_HSECLK < STM32_HSECLK_BYP_MIN) || (STM32_HSECLK > STM32_HSECLK_BYP_MAX)
#error "STM32_HSECLK outside acceptable range (STM32_HSECLK_BYP_MIN..STM32_HSECLK_BYP_MAX)"
#endif
#else /* !defined(STM32_HSE_BYPASS) */
#if (STM32_HSECLK < STM32_HSECLK_MIN) || (STM32_HSECLK > STM32_HSECLK_MAX)
#error "STM32_HSECLK outside acceptable range (STM32_HSECLK_MIN..STM32_HSECLK_MAX)"
#endif
#endif /* !defined(STM32_HSE_BYPASS) */
#endif /* STM32_HSECLK != 0 */
#else /* !STM32_HSE_ENABLED */

#if STM32_SW == STM32_SW_HSE_CK
#error "HSE not enabled, required by STM32_SW"
#endif

#if (STM32_PLLSRC == STM32_PLLSRC_HSE_CK) &&                                \
    (STM32_PLL1_ENABLED || STM32_PLL2_ENABLED || STM32_PLL3_ENABLED)
#error "HSE not enabled, required by STM32_PLLSRC and STM32_PLLx_ENABLED"
#endif

#if STM32_MCO1SEL == STM32_MCO1SEL_HSE_CK
#error "HSE not enabled, required by STM32_MCO1SEL"
#endif

#if STM32_MCO2SEL == STM32_MCO2SEL_HSE_CK
#error "HSE not enabled, required by STM32_MCO2SEL"
#endif

#if STM32_RTCSEL == STM32_RTCSEL_HSE_1M_CK
#error "HSE not enabled, required by STM32_RTCSEL"
#endif

#endif /* !STM32_HSE_ENABLED */

/*
 * LSI related checks.
 */
#if STM32_LSI_ENABLED
#else /* !STM32_LSI_ENABLED */

#if STM32_RTCSEL == STM32_RTCSEL_LSI_CK
#error "LSI not enabled, required by STM32_RTCSEL"
#endif

#if STM32_MCO2SEL == STM32_MCO2SEL_LSI_CK
#error "HSE not enabled, required by STM32_MCO2SEL"
#endif

#endif /* !STM32_LSI_ENABLED */

/*
 * LSE related checks.
 */
#if STM32_LSE_ENABLED

#if (STM32_LSECLK == 0)
#error "LSE frequency not defined"
#endif

#if defined(STM32_LSE_BYPASS)
#if (STM32_LSECLK < STM32_LSECLK_MIN) || (STM32_LSECLK > STM32_LSECLK_BYP_MAX)
#error "STM32_LSECLK outside acceptable range (STM32_LSECLK_MIN..STM32_LSECLK_BYP_MAX)"
#endif
#else
#if (STM32_LSECLK < STM32_LSECLK_MIN) || (STM32_LSECLK > STM32_LSECLK_MAX)
#error "STM32_LSECLK outside acceptable range (STM32_LSECLK_MIN..STM32_LSECLK_MAX)"
#endif
#endif

#if !defined(STM32_LSEDRV)
#error "STM32_LSEDRV not defined"
#endif

#if (STM32_LSEDRV >> 3) > 3
#error "STM32_LSEDRV outside acceptable range ((0<<3)..(3<<3))"
#endif

#else /* !STM32_LSE_ENABLED */

#if STM32_RTCSEL == STM32_RTCSEL_LSE_CK
#error "LSE not enabled, required by STM32_RTCSEL"
#endif

#if STM32_MCO1SEL == STM32_MCO1SEL_LSE_CK
#error "LSE not enabled, required by STM32_MCO1SEL"
#endif

#endif /* !STM32_LSE_ENABLED */

/**
 * @brief   HSI divided clock.
 */
#if (STM32_HSIDIV == STM32_HSIDIV_DIV1) || defined(__DOXYGEN__)
#define STM32_HSI_CK                (STM32_HSICLK / 1U)
#elif STM32_HSIDIV == STM32_HSIDIV_DIV2
#define STM32_HSI_CK                (STM32_HSICLK / 2U)
#elif STM32_HSIDIV == STM32_HSIDIV_DIV4
#define STM32_HSI_CK                (STM32_HSICLK / 4U)
#elif STM32_HSIDIV == STM32_HSIDIV_DIV8
#define STM32_HSI_CK                (STM32_HSICLK / 8U)
#else
#error "invalid STM32_HSIDIV value specified"
#endif

/**
 * @brief   HSE divided clock for RTC.
 */
#if ((STM32_RTCPRE_VALUE >= 2) && (STM32_RTCPRE_VALUE <= 63)) ||            \
    defined(__DOXYGEN__)
#define STM32_HSE_1M_CK             (STM32_HSECLK / STM32_RTCPRE_VALUE)
#else
#error "invalid STM32_RTCPRE_VALUE value specified"
#endif

/**
 * @brief   PLLs input clock frequency.
 */
#if (STM32_PLLSRC == STM32_PLLSRC_HSE_CK) || defined(__DOXYGEN__)
#define STM32_PLLCLKIN              STM32_HSECLK

#elif STM32_PLLSRC == STM32_PLLSRC_HSI_CK
#define STM32_PLLCLKIN              STM32_HSI_CK

#elif STM32_PLLSRC == STM32_PLLSRC_CSI_CK
#define STM32_PLLCLKIN              STM32_CSICLK

#else
#error "invalid STM32_PLLSRC value specified"
#endif

/**
 * @brief   PLL1 DIVM field.
 */
#if ((STM32_PLL1_DIVM_VALUE >= 1) && (STM32_PLL1_DIVM_VALUE <= 63)) ||      \
    defined(__DOXYGEN__)
#define STM32_PLL1_DIVM             (STM32_PLL1_DIVM_VALUE << 4)
#define STM32_PLL1_REF_CK           (STM32_PLLCLKIN / STM32_PLL1_DIVM_VALUE)
#else
#error "invalid STM32_PLL1_DIVM_VALUE value specified"
#endif

/*
 * PLL1 input frequency range check.
 */
#if (STM32_PLL1_REF_CK < STM32_PLLIN_MIN) || (STM32_PLL1_REF_CK > STM32_PLLIN_MAX)
#error "STM32_PLL1_REF_CK outside acceptable range (STM32_PLLIN_MIN..STM32_PLLIN_MAX)"
#endif

/**
 * @brief   PLL1 input range selector.
 */
#if (STM32_PLL1_REF_CK < STM32_PLLIN_THRESHOLD1) || defined(__DOXYGEN__)
#define STM32_PLLCFGR_PLL1RGE       RCC_PLLCFGR_PLL1RGE_0
#elif STM32_PLL1_REF_CK < STM32_PLLIN_THRESHOLD2
#define STM32_PLLCFGR_PLL1RGE       RCC_PLLCFGR_PLL1RGE_1
#elif STM32_PLL1_REF_CK < STM32_PLLIN_THRESHOLD3
#define STM32_PLLCFGR_PLL1RGE       RCC_PLLCFGR_PLL1RGE_2
#else
#define STM32_PLLCFGR_PLL1RGE       RCC_PLLCFGR_PLL1RGE_3
#endif

/**
 * @brief   PLL2 DIVM field.
 */
#if ((STM32_PLL2_DIVM_VALUE >= 1) && (STM32_PLL2_DIVM_VALUE <= 63)) ||      \
    defined(__DOXYGEN__)
#define STM32_PLL2_DIVM             (STM32_PLL2_DIVM_VALUE << 12)
#define STM32_PLL2_REF_CK           (STM32_PLLCLKIN / STM32_PLL2_DIVM_VALUE)
#else
#error "invalid STM32_PLL2_DIVM_VALUE value specified"
#endif

/*
 * PLL2 input frequency range check.
 */
#if (STM32_PLL2_REF_CK < STM32_PLLIN_MIN) || (STM32_PLL2_REF_CK > STM32_PLLIN_MAX)
#error "STM32_PLL2_REF_CK outside acceptable range (STM32_PLLIN_MIN..STM32_PLLIN_MAX)"
#endif

/**
 * @brief   PLL2 input range selector.
 */
#if (STM32_PLL2_REF_CK < STM32_PLLIN_THRESHOLD1) || defined(__DOXYGEN__)
#define STM32_PLLCFGR_PLL2RGE       RCC_PLLCFGR_PLL2RGE_0
#elif STM32_PLL2_REF_CK < STM32_PLLIN_THRESHOLD2
#define STM32_PLLCFGR_PLL2RGE       RCC_PLLCFGR_PLL2RGE_1
#elif STM32_PLL2_REF_CK < STM32_PLLIN_THRESHOLD3
#define STM32_PLLCFGR_PLL2RGE       RCC_PLLCFGR_PLL2RGE_2
#else
#define STM32_PLLCFGR_PLL2RGE       RCC_PLLCFGR_PLL2RGE_3
#endif

/**
 * @brief   PLL3 DIVM field.
 */
#if ((STM32_PLL3_DIVM_VALUE >= 1) && (STM32_PLL3_DIVM_VALUE <= 63)) ||      \
    defined(__DOXYGEN__)
#define STM32_PLL3_DIVM             (STM32_PLL3_DIVM_VALUE << 20)
#define STM32_PLL3_REF_CK           (STM32_PLLCLKIN / STM32_PLL3_DIVM_VALUE)
#else
#error "invalid STM32_PLL3_DIVM_VALUE value specified"
#endif

/*
 * PLL3 input frequency range check.
 */
#if (STM32_PLL3_REF_CK < STM32_PLLIN_MIN) || (STM32_PLL3_REF_CK > STM32_PLLIN_MAX)
#error "STM32_PLL3_REF_CK outside acceptable range (STM32_PLLIN_MIN..STM32_PLLIN_MAX)"
#endif

/**
 * @brief   PLL3 input range selector.
 */
#if (STM32_PLL3_REF_CK < STM32_PLLIN_THRESHOLD1) || defined(__DOXYGEN__)
#define STM32_PLLCFGR_PLL3RGE       RCC_PLLCFGR_PLL3RGE_0
#elif STM32_PLL3_REF_CK < STM32_PLLIN_THRESHOLD2
#define STM32_PLLCFGR_PLL3RGE       RCC_PLLCFGR_PLL3RGE_1
#elif STM32_PLL3_REF_CK < STM32_PLLIN_THRESHOLD3
#define STM32_PLLCFGR_PLL3RGE       RCC_PLLCFGR_PLL3RGE_2
#else
#define STM32_PLLCFGR_PLL3RGE       RCC_PLLCFGR_PLL3RGE_3
#endif

/**
 * @brief   PLL1 DIVN field.
 */
#if ((STM32_PLL1_DIVN_VALUE >= 4) && (STM32_PLL1_DIVN_VALUE <= 512)) ||    \
    defined(__DOXYGEN__)
#define STM32_PLL1_DIVN             ((STM32_PLL1_DIVN_VALUE - 1U) << 0U)
#else
#error "invalid STM32_PLL1_DIVN_VALUE value specified"
#endif

/**
 * @brief   PLL2 DIVN field.
 */
#if ((STM32_PLL2_DIVN_VALUE >= 4) && (STM32_PLL2_DIVN_VALUE <= 512)) ||    \
    defined(__DOXYGEN__)
#define STM32_PLL2_DIVN             ((STM32_PLL2_DIVN_VALUE - 1U) << 0U)
#else
#error "invalid STM32_PLL2_DIVN_VALUE value specified"
#endif

/**
 * @brief   PLL3 DIVN field.
 */
#if ((STM32_PLL3_DIVN_VALUE >= 4) && (STM32_PLL3_DIVN_VALUE <= 512)) ||    \
    defined(__DOXYGEN__)
#define STM32_PLL3_DIVN             ((STM32_PLL3_DIVN_VALUE - 1U) << 0U)
#else
#error "invalid STM32_PLL3_DIVN_VALUE value specified"
#endif

/**
 * @brief   PLL1 FRACN field.
 */
#if ((STM32_PLL1_FRACN_VALUE >= 0) && (STM32_PLL1_FRACN_VALUE <= 8191)) ||  \
    defined(__DOXYGEN__)
#define STM32_PLL1_FRACN             (STM32_PLL1_FRACN_VALUE << 3U)
#else
#error "invalid STM32_PLL1_FRACN_VALUE value specified"
#endif

/**
 * @brief   PLL2 FRACN field.
 */
#if ((STM32_PLL2_FRACN_VALUE >= 0) && (STM32_PLL2_FRACN_VALUE <= 8191)) ||  \
    defined(__DOXYGEN__)
#define STM32_PLL2_FRACN             (STM32_PLL2_FRACN_VALUE << 3U)
#else
#error "invalid STM32_PLL2_FRACN_VALUE value specified"
#endif

/**
 * @brief   PLL3 FRACN field.
 */
#if ((STM32_PLL3_FRACN_VALUE >= 0) && (STM32_PLL3_FRACN_VALUE <= 8191)) ||  \
    defined(__DOXYGEN__)
#define STM32_PLL3_FRACN             (STM32_PLL3_FRACN_VALUE << 3U)
#else
#error "invalid STM32_PLL3_FRACN_VALUE value specified"
#endif

/**
 * @brief   PLL1 DIVP field.
 */
#if ((STM32_PLL1_DIVP_VALUE >= 2) && (STM32_PLL1_DIVP_VALUE <= 128) &&      \
     ((STM32_PLL1_DIVP_VALUE & 1U) == 0U)) ||                               \
    defined(__DOXYGEN__)
#define STM32_PLL1_DIVP             ((STM32_PLL1_DIVP_VALUE - 1U) << 9U)
#else
#error "invalid STM32_PLL1_DIVP_VALUE value specified"
#endif

/**
 * @brief   PLL2 DIVP field.
 */
#if ((STM32_PLL2_DIVP_VALUE >= 2) && (STM32_PLL2_DIVP_VALUE <= 128) &&      \
     ((STM32_PLL2_DIVP_VALUE & 1U) == 0U)) ||                               \
    defined(__DOXYGEN__)
#define STM32_PLL2_DIVP             ((STM32_PLL2_DIVP_VALUE - 1U) << 9U)
#else
#error "invalid STM32_PLL2_DIVP_VALUE value specified"
#endif

/**
 * @brief   PLL3 DIVP field.
 */
#if ((STM32_PLL3_DIVP_VALUE >= 2) && (STM32_PLL3_DIVP_VALUE <= 128) &&      \
     ((STM32_PLL3_DIVP_VALUE & 1U) == 0U)) ||                               \
    defined(__DOXYGEN__)
#define STM32_PLL3_DIVP             ((STM32_PLL3_DIVP_VALUE - 1U) << 9U)
#else
#error "invalid STM32_PLL3_DIVP_VALUE value specified"
#endif

/**
 * @brief   PLL1 DIVQ field.
 */
#if ((STM32_PLL1_DIVQ_VALUE >= 1) && (STM32_PLL1_DIVQ_VALUE <= 128)) ||     \
    defined(__DOXYGEN__)
#define STM32_PLL1_DIVQ             ((STM32_PLL1_DIVQ_VALUE - 1U) << 16U)
#else
#error "invalid STM32_PLL1_DIVQ_VALUE value specified"
#endif

/**
 * @brief   PLL2 DIVQ field.
 */
#if ((STM32_PLL2_DIVQ_VALUE >= 1) && (STM32_PLL2_DIVQ_VALUE <= 128)) ||     \
    defined(__DOXYGEN__)
#define STM32_PLL2_DIVQ             ((STM32_PLL2_DIVQ_VALUE - 1U) << 16U)
#else
#error "invalid STM32_PLL2_DIVQ_VALUE value specified"
#endif

/**
 * @brief   PLL3 DIVQ field.
 */
#if ((STM32_PLL3_DIVQ_VALUE >= 1) && (STM32_PLL3_DIVQ_VALUE <= 128)) ||     \
    defined(__DOXYGEN__)
#define STM32_PLL3_DIVQ             ((STM32_PLL3_DIVQ_VALUE - 1U) << 16U)
#else
#error "invalid STM32_PLL3_DIVQ_VALUE value specified"
#endif

/**
 * @brief   PLL1 DIVR field.
 */
#if ((STM32_PLL1_DIVR_VALUE >= 1) && (STM32_PLL1_DIVR_VALUE <= 128)) ||     \
    defined(__DOXYGEN__)
#define STM32_PLL1_DIVR             ((STM32_PLL1_DIVR_VALUE - 1U) << 24U)
#else
#error "invalid STM32_PLL1_DIVR_VALUE value specified"
#endif

/**
 * @brief   PLL2 DIVR field.
 */
#if ((STM32_PLL2_DIVR_VALUE >= 1) && (STM32_PLL2_DIVR_VALUE <= 128)) ||     \
    defined(__DOXYGEN__)
#define STM32_PLL2_DIVR             ((STM32_PLL2_DIVR_VALUE - 1U) << 24U)
#else
#error "invalid STM32_PLL2_DIVR_VALUE value specified"
#endif

/**
 * @brief   PLL3 DIVR field.
 */
#if ((STM32_PLL3_DIVR_VALUE >= 1) && (STM32_PLL3_DIVR_VALUE <= 128)) ||     \
    defined(__DOXYGEN__)
#define STM32_PLL3_DIVR             ((STM32_PLL3_DIVR_VALUE - 1U) << 24U)
#else
#error "invalid STM32_PLL3_DIVR_VALUE value specified"
#endif

/**
 * @brief   PLL1 VCO frequency.
 */
#define STM32_PLL1_VCO_CK           (STM32_PLL1_REF_CK * STM32_PLL1_DIVN_VALUE)

/*
 * PLL1 VCO frequency range check.
 */
#if (STM32_PLL1_VCO_CK < STM32_PLLVCO_MIN) || (STM32_PLL1_VCO_CK > STM32_PLLVCO_MAX)
#error "STM32_PLL1_VCO_CK outside acceptable range (STM32_PLLVCO_MIN..STM32_PLLVCO_MAX)"
#endif

/*
 * PLL1 VCO mode.
 */
#if (STM32_PLL1_VCO_CK > STM32_PLLVCO_THRESHOLD) || defined(__DOXYGEN__)
#define STM32_PLLCFGR_PLL1VCOSEL    0U
#else
#define STM32_PLLCFGR_PLL1VCOSEL    RCC_PLLCFGR_PLL1VCOSEL
#endif

/**
 * @brief   PLL2 VCO frequency.
 */
#define STM32_PLL2_VCO_CK           (STM32_PLL2_REF_CK * STM32_PLL2_DIVN_VALUE)

/*
 * PLL2 VCO frequency range check.
 */
#if (STM32_PLL2_VCO_CK < STM32_PLLVCO_MIN) || (STM32_PLL2_VCO_CK > STM32_PLLVCO_MAX)
#error "STM32_PLL2_VCO_CK outside acceptable range (STM32_PLLVCO_MIN..STM32_PLLVCO_MAX)"
#endif

/*
 * PLL2 VCO mode.
 */
#if (STM32_PLL2_VCO_CK > STM32_PLLVCO_THRESHOLD) || defined(__DOXYGEN__)
#define STM32_PLLCFGR_PLL2VCOSEL    0U
#else
#define STM32_PLLCFGR_PLL2VCOSEL    RCC_PLLCFGR_PLL2VCOSEL
#endif

/**
 * @brief   PLL3 VCO frequency.
 */
#define STM32_PLL3_VCO_CK           (STM32_PLL3_REF_CK * STM32_PLL3_DIVN_VALUE)

/*
 * PLL3 VCO frequency range check.
 */
#if (STM32_PLL3_VCO_CK < STM32_PLLVCO_MIN) || (STM32_PLL3_VCO_CK > STM32_PLLVCO_MAX)
#error "STM32_PLL3_VCO_CK outside acceptable range (STM32_PLLVCO_MIN..STM32_PLLVCO_MAX)"
#endif

/*
 * PLL3 VCO mode.
 */
#if (STM32_PLL3_VCO_CK > STM32_PLLVCO_THRESHOLD) || defined(__DOXYGEN__)
#define STM32_PLLCFGR_PLL3VCOSEL    0U
#else
#define STM32_PLLCFGR_PLL3VCOSEL    RCC_PLLCFGR_PLL3VCOSEL
#endif

/**
 * @brief   PLL1 P output clock frequency.
 */
#define STM32_PLL1_P_CK             (STM32_PLL1_VCO_CK / STM32_PLL1_DIVP_VALUE)

/*
 * PLL1 P output frequency range check.
 */
#if (STM32_PLL1_P_CK < STM32_PLLOUT_MIN) || (STM32_PLL1_P_CK > STM32_PLLOUT_MAX)
#error "STM32_PLL1_P_CLKOUT outside acceptable range (STM32_PLLOUT_MIN..STM32_PLLOUT_MAX)"
#endif

/**
 * @brief   PLL2 P output clock frequency.
 */
#define STM32_PLL2_P_CK             (STM32_PLL2_VCO_CK / STM32_PLL2_DIVP_VALUE)

/*
 * PLL2 P output frequency range check.
 */
#if (STM32_PLL2_P_CK < STM32_PLLOUT_MIN) || (STM32_PLL2_P_CK > STM32_PLLOUT_MAX)
#error "STM32_PLL2_P_CLKOUT outside acceptable range (STM32_PLLOUT_MIN..STM32_PLLOUT_MAX)"
#endif

/**
 * @brief   PLL3 P output clock frequency.
 */
#define STM32_PLL3_P_CK             (STM32_PLL3_VCO_CK / STM32_PLL3_DIVP_VALUE)

/*
 * PLL3 P output frequency range check.
 */
#if (STM32_PLL3_P_CK < STM32_PLLOUT_MIN) || (STM32_PLL3_P_CK > STM32_PLLOUT_MAX)
#error "STM32_PLL3_P_CLKOUT outside acceptable range (STM32_PLLOUT_MIN..STM32_PLLOUT_MAX)"
#endif

/**
 * @brief   PLL1 Q output clock frequency.
 */
#define STM32_PLL1_Q_CK             (STM32_PLL1_VCO_CK / STM32_PLL1_DIVQ_VALUE)

/*
 * PLL1 Q output frequency range check.
 */
#if (STM32_PLL1_Q_CK < STM32_PLLOUT_MIN) || (STM32_PLL1_Q_CK > STM32_PLLOUT_MAX)
#error "STM32_PLL1_Q_CLKOUT outside acceptable range (STM32_PLLOUT_MIN..STM32_PLLOUT_MAX)"
#endif

/**
 * @brief   PLL2 Q output clock frequency.
 */
#define STM32_PLL2_Q_CK             (STM32_PLL2_VCO_CK / STM32_PLL2_DIVQ_VALUE)

/*
 * PLL2 Q output frequency range check.
 */
#if (STM32_PLL2_Q_CK < STM32_PLLOUT_MIN) || (STM32_PLL2_Q_CK > STM32_PLLOUT_MAX)
#error "STM32_PLL2_Q_CLKOUT outside acceptable range (STM32_PLLOUT_MIN..STM32_PLLOUT_MAX)"
#endif

/**
 * @brief   PLL3 Q output clock frequency.
 */
#define STM32_PLL3_Q_CK             (STM32_PLL3_VCO_CK / STM32_PLL3_DIVQ_VALUE)

/*
 * PLL3 Q output frequency range check.
 */
#if (STM32_PLL3_Q_CK < STM32_PLLOUT_MIN) || (STM32_PLL3_Q_CK > STM32_PLLOUT_MAX)
#error "STM32_PLL3_Q_CLKOUT outside acceptable range (STM32_PLLOUT_MIN..STM32_PLLOUT_MAX)"
#endif

/**
 * @brief   PLL1 R output clock frequency.
 */
#define STM32_PLL1_R_CK             (STM32_PLL1_VCO_CK / STM32_PLL1_DIVR_VALUE)

/*
 * PLL1 R output frequency range check.
 */
#if (STM32_PLL1_R_CK < STM32_PLLOUT_MIN) || (STM32_PLL1_R_CK > STM32_PLLOUT_MAX)
#error "STM32_PLL1_R_CLKOUT outside acceptable range (STM32_PLLOUT_MIN..STM32_PLLOUT_MAX)"
#endif

/**
 * @brief   PLL2 R output clock frequency.
 */
#define STM32_PLL2_R_CK             (STM32_PLL2_VCO_CK / STM32_PLL2_DIVR_VALUE)

/*
 * PLL2 R output frequency range check.
 */
#if (STM32_PLL2_R_CK < STM32_PLLOUT_MIN) || (STM32_PLL2_R_CK > STM32_PLLOUT_MAX)
#error "STM32_PLL2_R_CLKOUT outside acceptable range (STM32_PLLOUT_MIN..STM32_PLLOUT_MAX)"
#endif

/**
 * @brief   PLL3 R output clock frequency.
 */
#define STM32_PLL3_R_CK             (STM32_PLL3_VCO_CK / STM32_PLL3_DIVR_VALUE)

/*
 * PLL3 R output frequency range check.
 */
#if (STM32_PLL3_R_CK < STM32_PLLOUT_MIN) || (STM32_PLL3_R_CK > STM32_PLLOUT_MAX)
#error "STM32_PLL3_R_CLKOUT outside acceptable range (STM32_PLLOUT_MIN..STM32_PLLOUT_MAX)"
#endif

/**
 * @brief   System clock source.
 */
#if STM32_NO_INIT || defined(__DOXYGEN__)
#define STM32_SYS_CK                STM32_SYS_CK_ENFORCED_VALUE

#elif (STM32_SW == STM32_SW_HSI_CK)
#define STM32_SYS_CK                STM32_HSI_CK

#elif (STM32_SW == STM32_SW_CSI_CK)
#define STM32_SYS_CK                STM32_CSICLK

#elif (STM32_SW == STM32_SW_HSE_CK)
#define STM32_SYS_CK                STM32_HSECLK

#elif (STM32_SW == STM32_SW_PLL1_P_CK)
#define STM32_SYS_CK                STM32_PLL1_P_CK

#else
#error "invalid STM32_SW value specified"
#endif

/*
 * Check on the system clock.
 */
#if STM32_SW > STM32_SYSCLK_MAX
#error "STM32_SYS_CK above maximum rated frequency (STM32_SYSCLK_MAX)"
#endif

/**
 * @brief   Peripherals clock source.
 */
#if (STM32_CKPERSEL == STM32_CKPERSEL_HSI_CK) || defined(__DOXYGEN__)
#define STM32_PER_CK                STM32_HSI_CK

#elif (STM32_CKPERSEL == STM32_CKPERSEL_CSI_CK)
#define STM32_PER_CK                STM32_CSICLK

#elif (STM32_CKPERSEL == STM32_CKPERSEL_HSE_CK)
#define STM32_PER_CK                STM32_HSECLK

#else
#error "invalid STM32_CKPERSEL value specified"
#endif

/*
 * Check on the peripherals clock.
 */
#if STM32_PER_CK > STM32_HCLK_MAX
#error "STM32_PER_CK above maximum rated frequency (STM32_HCLK_MAX)"
#endif

/**
 * @brief   MCO1 divider clock.
 */
#if (STM32_MCO1SEL == STM32_MCO1SEL_HSI_CK) || defined(__DOXYGEN__)
#define STM32_MCO1DIVCLK            STM32_HSI_CK

#elif STM32_MCO1SEL == STM32_MCO1SEL_LSE_CK
#define STM32_MCO1DIVCLK            STM32_LSECLK

#elif STM32_MCO1SEL == STM32_MCO1SEL_HSE_CK
#define STM32_MCO1DIVCLK            STM32_HSECLK

#elif STM32_MCO1SEL == STM32_MCO1SEL_PLL1_Q_CK
#define STM32_MCO1DIVCLK            STM32_PLL1_P_CK

#elif STM32_MCO1SEL == STM32_MCO1SEL_HSI48_CK
#define STM32_MCO1DIVCLK            STM32_HSI48CLK

#else
#error "invalid STM32_MCO1SEL value specified"
#endif

/**
 * @brief   MCO1 output pin clock.
 */
#if (STM32_MCO1PRE_VALUE < 1) || (STM32_MCO1PRE_VALUE > 15)
#error "STM32_MCO1PRE_VALUE outside acceptable range (1..15)"
#endif

/**
 * @brief   MCO2 divider clock.
 */
#if (STM32_MCO2SEL == STM32_MCO2SEL_SYS_CK) || defined(__DOXYGEN__)
#define STM32_MCO2DIVCLK            STM32_SYS_CK

#elif STM32_MCO2SEL == STM32_MCO2SEL_PLL1_P_CK
#define STM32_MCO2DIVCLK            STM32_PLL2_P_CK

#elif STM32_MCO2SEL == STM32_MCO2SEL_HSE_CK
#define STM32_MCO2DIVCLK            STM32_HSECLK

#elif STM32_MCO2SEL == STM32_MCO2SEL_PLL2_P_CK
#define STM32_MCO2DIVCLK            STM32_PLL2_P_CK

#elif STM32_MCO2SEL == STM32_MCO2SEL_CSI_CK
#define STM32_MCO2DIVCLK            STM32_CSICLK

#elif STM32_MCO2SEL == STM32_MCO2SEL_LSI_CK
#define STM32_MCO2DIVCLK            STM32_LSICLK

#else
#error "invalid STM32_MCO2SEL value specified"
#endif

/**
 * @brief   MCO2 output pin clock.
 */
#if (STM32_MCO2PRE_VALUE < 1) || (STM32_MCO2PRE_VALUE > 15)
#error "STM32_MCO2PRE_VALUE outside acceptable range (1..15)"
#endif

/**
 * @brief   RTC clock.
 */
#if (STM32_RTCSEL == STM32_RTCSEL_NOCLK) || defined(__DOXYGEN__)
#define STM32_RTC_CK                0

#elif STM32_RTCSEL == STM32_RTCSEL_LSE_CK
#define STM32_RTC_CK                STM32_LSECLK

#elif STM32_RTCSEL == STM32_RTCSEL_LSI_CK
#define STM32_RTC_CK                STM32_LSICLK

#elif STM32_RTCSEL == STM32_RTCSEL_HSE_1M_CK
#define STM32_RTC_CK                STM32_HSE_1M_CK

#else
#error "invalid STM32_RTCSEL value specified"
#endif

/*
 * Check on the RTC clock.
 */
#if STM32_RTC_CK > 1000000
#error "STM32_RTC_CK above maximum rated frequency (1000000)"
#endif

/**
 * @brief   D1CPRE clock.
 */
#if (STM32_D1CPRE == STM32_D1CPRE_DIV1) || defined(__DOXYGEN__)
#define STM32_SYS_D1CPRE_CK         (STM32_SYS_CK / 1U)
#elif STM32_D1CPRE == STM32_D1CPRE_DIV2
#define STM32_SYS_D1CPRE_CK         (STM32_SYS_CK / 2U)
#elif STM32_D1CPRE == STM32_D1CPRE_DIV4
#define STM32_SYS_D1CPRE_CK         (STM32_SYS_CK / 4U)
#elif STM32_D1CPRE == STM32_D1CPRE_DIV8
#define STM32_SYS_D1CPRE_CK         (STM32_SYS_CK / 8U)
#elif STM32_D1CPRE == STM32_D1CPRE_DIV16
#define STM32_SYS_D1CPRE_CK         (STM32_SYS_CK / 16U)
#elif STM32_D1CPRE == STM32_D1CPRE_DIV64
#define STM32_SYS_D1CPRE_CK         (STM32_SYS_CK / 64U)
#elif STM32_D1CPRE == STM32_D1CPRE_DIV128
#define STM32_SYS_D1CPRE_CK         (STM32_SYS_CK / 128U)
#elif STM32_D1CPRE == STM32_D1CPRE_DIV256
#define STM32_SYS_D1CPRE_CK         (STM32_SYS_CK / 256U)
#elif STM32_D1CPRE == STM32_D1CPRE_DIV512
#define STM32_SYS_D1CPRE_CK         (STM32_SYS_CK / 512U)
#else
#error "invalid STM32_D1CPRE value specified"
#endif

/**
 * @brief   HCLK clock.
 */
#if (STM32_D1HPRE == STM32_D1HPRE_DIV1) || defined(__DOXYGEN__)
#define STM32_HCLK                  (STM32_SYS_D1CPRE_CK / 1U)
#elif STM32_D1HPRE == STM32_D1HPRE_DIV2
#define STM32_HCLK                  (STM32_SYS_D1CPRE_CK / 2U)
#elif STM32_D1HPRE == STM32_D1HPRE_DIV4
#define STM32_HCLK                  (STM32_SYS_D1CPRE_CK / 4U)
#elif STM32_D1HPRE == STM32_D1HPRE_DIV8
#define STM32_HCLK                  (STM32_SYS_D1CPRE_CK / 8U)
#elif STM32_D1HPRE == STM32_D1HPRE_DIV16
#define STM32_HCLK                  (STM32_SYS_D1CPRE_CK / 16U)
#elif STM32_D1HPRE == STM32_D1HPRE_DIV64
#define STM32_HCLK                  (STM32_SYS_D1CPRE_CK / 64U)
#elif STM32_D1HPRE == STM32_D1HPRE_DIV128
#define STM32_HCLK                  (STM32_SYS_D1CPRE_CK / 128U)
#elif STM32_D1HPRE == STM32_D1HPRE_DIV256
#define STM32_HCLK                  (STM32_SYS_D1CPRE_CK / 256U)
#elif STM32_D1HPRE == STM32_D1HPRE_DIV512
#define STM32_HCLK                  (STM32_SYS_D1CPRE_CK / 512U)
#else
#error "invalid STM32_D1HPRE value specified"
#endif

/*
 * AHB frequency check.
 */
#if STM32_HCLK > STM32_HCLK_MAX
#error "STM32_HCLK exceeding maximum frequency (STM32_HCLK_MAX)"
#endif

/**
 * @brief   D1 PCLK3 clock.
 */
#if (STM32_D1PPRE3 == STM32_D1PPRE3_DIV1) || defined(__DOXYGEN__)
#define STM32_PCLK3                 (STM32_HCLK / 1U)
#elif STM32_D1PPRE3 == STM32_D1PPRE3_DIV2
#define STM32_PCLK3                 (STM32_HCLK / 2U)
#elif STM32_D1PPRE3 == STM32_D1PPRE3_DIV4
#define STM32_PCLK3                 (STM32_HCLK / 4U)
#elif STM32_D1PPRE3 == STM32_D1PPRE3_DIV8
#define STM32_PCLK3                 (STM32_HCLK / 8U)
#elif STM32_D1PPRE3 == STM32_D1PPRE3_DIV16
#define STM32_PCLK3                 (STM32_HCLK / 16U)
#else
#error "invalid STM32_D1PPRE3 value specified"
#endif

/*
 * D1 PCLK3 frequency check.
 */
#if STM32_PCLK3 > STM32_PCLK3_MAX
#error "STM32_PCLK3 exceeding maximum frequency (STM32_PCLK3_MAX)"
#endif

/**
 * @brief   D2 PCLK1 clock.
 */
#if (STM32_D2PPRE1 == STM32_D2PPRE1_DIV1) || defined(__DOXYGEN__)
#define STM32_PCLK1                 (STM32_HCLK / 1U)
#elif STM32_D2PPRE1 == STM32_D2PPRE1_DIV2
#define STM32_PCLK1                 (STM32_HCLK / 2U)
#elif STM32_D2PPRE1 == STM32_D2PPRE1_DIV4
#define STM32_PCLK1                 (STM32_HCLK / 4U)
#elif STM32_D2PPRE1 == STM32_D2PPRE1_DIV8
#define STM32_PCLK1                 (STM32_HCLK / 8U)
#elif STM32_D2PPRE1 == STM32_D2PPRE1_DIV16
#define STM32_PCLK1                 (STM32_HCLK / 16U)
#else
#error "invalid STM32_D2PPRE1 value specified"
#endif

/*
 * D2 PCLK1 frequency check.
 */
#if STM32_PCLK1 > STM32_PCLK1_MAX
#error "STM32_PCLK1 exceeding maximum frequency (STM32_PCLK1_MAX)"
#endif

/**
 * @brief   D2 PCLK2 clock.
 */
#if (STM32_D2PPRE2 == STM32_D2PPRE2_DIV1) || defined(__DOXYGEN__)
#define STM32_PCLK2                 (STM32_HCLK / 1U)
#elif STM32_D2PPRE2 == STM32_D2PPRE2_DIV2
#define STM32_PCLK2                 (STM32_HCLK / 2U)
#elif STM32_D2PPRE2 == STM32_D2PPRE2_DIV4
#define STM32_PCLK2                 (STM32_HCLK / 4U)
#elif STM32_D2PPRE2 == STM32_D2PPRE2_DIV8
#define STM32_PCLK2                 (STM32_HCLK / 8U)
#elif STM32_D2PPRE2 == STM32_D2PPRE2_DIV16
#define STM32_PCLK2                 (STM32_HCLK / 16U)
#else
#error "invalid STM32_D2PPRE2 value specified"
#endif

/*
 * D2 PCLK2 frequency check.
 */
#if STM32_PCLK2 > STM32_PCLK2_MAX
#error "STM32_PCLK2 exceeding maximum frequency (STM32_PCLK2_MAX)"
#endif

/**
 * @brief   D3 PCLK4 clock.
 */
#if (STM32_D3PPRE4 == STM32_D3PPRE4_DIV1) || defined(__DOXYGEN__)
#define STM32_PCLK4                 (STM32_HCLK / 1U)
#elif STM32_D3PPRE4 == STM32_D3PPRE4_DIV2
#define STM32_PCLK4                 (STM32_HCLK / 2U)
#elif STM32_D3PPRE4 == STM32_D3PPRE4_DIV4
#define STM32_PCLK4                 (STM32_HCLK / 4U)
#elif STM32_D3PPRE4 == STM32_D3PPRE4_DIV8
#define STM32_PCLK4                 (STM32_HCLK / 8U)
#elif STM32_D3PPRE4 == STM32_D3PPRE4_DIV16
#define STM32_PCLK4                 (STM32_HCLK / 16U)
#else
#error "invalid STM32_D3PPRE4 value specified"
#endif

/*
 * D3 PCLK4 frequency check.
 */
#if STM32_PCLK4 > STM32_PCLK4_MAX
#error "STM32_PCLK4 exceeding maximum frequency (STM32_PCLK4_MAX)"
#endif

/**
 * @brief   Flash settings.
 */
#if (STM32_HCLK <= STM32_0WS_THRESHOLD) || defined(__DOXYGEN__)
#define STM32_FLASHBITS             0x00000000

#elif STM32_HCLK <= STM32_1WS_THRESHOLD
#define STM32_FLASHBITS             0x00000001

#elif STM32_HCLK <= STM32_2WS_THRESHOLD
#define STM32_FLASHBITS             0x00000002

#elif STM32_HCLK <= STM32_3WS_THRESHOLD
#define STM32_FLASHBITS             0x00000003

#elif STM32_HCLK <= STM32_4WS_THRESHOLD
#define STM32_FLASHBITS             0x00000004

#else
#define STM32_FLASHBITS             0x00000007
#endif
























#if 0
/**
 * @brief   USART1 frequency.
 */
#if (STM32_USART1SEL == STM32_USART1SEL_PCLK2) || defined(__DOXYGEN__)
#define STM32_USART1CLK             STM32_PCLK2
#elif STM32_USART1SEL == STM32_USART1SEL_SYSCLK
#define STM32_USART1CLK             STM32_SYSCLK
#elif STM32_USART1SEL == STM32_USART1SEL_HSI
#define STM32_USART1CLK             STM32_HSICLK
#elif STM32_USART1SEL == STM32_USART1SEL_LSE
#define STM32_USART1CLK             STM32_LSECLK
#else
#error "invalid source selected for USART1 clock"
#endif

/**
 * @brief   USART2 frequency.
 */
#if (STM32_USART2SEL == STM32_USART2SEL_PCLK1) || defined(__DOXYGEN__)
#define STM32_USART2CLK             STM32_PCLK1
#elif STM32_USART2SEL == STM32_USART2SEL_SYSCLK
#define STM32_USART2CLK             STM32_SYSCLK
#elif STM32_USART2SEL == STM32_USART2SEL_HSI
#define STM32_USART2CLK             STM32_HSICLK
#elif STM32_USART2SEL == STM32_USART2SEL_LSE
#define STM32_USART2CLK             STM32_LSECLK
#else
#error "invalid source selected for USART2 clock"
#endif

/**
 * @brief   USART3 frequency.
 */
#if (STM32_USART3SEL == STM32_USART3SEL_PCLK1) || defined(__DOXYGEN__)
#define STM32_USART3CLK             STM32_PCLK1
#elif STM32_USART3SEL == STM32_USART3SEL_SYSCLK
#define STM32_USART3CLK             STM32_SYSCLK
#elif STM32_USART3SEL == STM32_USART3SEL_HSI
#define STM32_USART3CLK             STM32_HSICLK
#elif STM32_USART3SEL == STM32_USART3SEL_LSE
#define STM32_USART3CLK             STM32_LSECLK
#else
#error "invalid source selected for USART3 clock"
#endif

/**
 * @brief   UART4 frequency.
 */
#if (STM32_UART4SEL == STM32_UART4SEL_PCLK1) || defined(__DOXYGEN__)
#define STM32_UART4CLK              STM32_PCLK1
#elif STM32_UART4SEL == STM32_UART4SEL_SYSCLK
#define STM32_UART4CLK              STM32_SYSCLK
#elif STM32_UART4SEL == STM32_UART4SEL_HSI
#define STM32_UART4CLK              STM32_HSICLK
#elif STM32_UART4SEL == STM32_UART4SEL_LSE
#define STM32_UART4CLK              STM32_LSECLK
#else
#error "invalid source selected for UART4 clock"
#endif

/**
 * @brief   UART5 frequency.
 */
#if (STM32_UART5SEL == STM32_UART5SEL_PCLK1) || defined(__DOXYGEN__)
#define STM32_UART5CLK              STM32_PCLK1
#elif STM32_UART5SEL == STM32_UART5SEL_SYSCLK
#define STM32_UART5CLK              STM32_SYSCLK
#elif STM32_UART5SEL == STM32_UART5SEL_HSI
#define STM32_UART5CLK              STM32_HSICLK
#elif STM32_UART5SEL == STM32_UART5SEL_LSE
#define STM32_UART5CLK              STM32_LSECLK
#else
#error "invalid source selected for UART5 clock"
#endif

/**
 * @brief   USART6 frequency.
 */
#if (STM32_USART6SEL == STM32_USART6SEL_PCLK2) || defined(__DOXYGEN__)
#define STM32_USART6CLK             STM32_PCLK2
#elif STM32_USART6SEL == STM32_USART6SEL_SYSCLK
#define STM32_USART6CLK             STM32_SYSCLK
#elif STM32_USART6SEL == STM32_USART6SEL_HSI
#define STM32_USART6CLK             STM32_HSICLK
#elif STM32_USART6SEL == STM32_USART6SEL_LSE
#define STM32_USART6CLK             STM32_LSECLK
#else
#error "invalid source selected for USART6 clock"
#endif

/**
 * @brief   UART7 frequency.
 */
#if (STM32_UART7SEL == STM32_UART7SEL_PCLK1) || defined(__DOXYGEN__)
#define STM32_UART7CLK              STM32_PCLK1
#elif STM32_UART7SEL == STM32_UART7SEL_SYSCLK
#define STM32_UART7CLK              STM32_SYSCLK
#elif STM32_UART7SEL == STM32_UART7SEL_HSI
#define STM32_UART7CLK              STM32_HSICLK
#elif STM32_UART7SEL == STM32_UART7SEL_LSE
#define STM32_UART7CLK              STM32_LSECLK
#else
#error "invalid source selected for UART7 clock"
#endif

/**
 * @brief   UART8 frequency.
 */
#if (STM32_UART8SEL == STM32_UART8SEL_PCLK1) || defined(__DOXYGEN__)
#define STM32_UART8CLK              STM32_PCLK1
#elif STM32_UART8SEL == STM32_UART8SEL_SYSCLK
#define STM32_UART8CLK              STM32_SYSCLK
#elif STM32_UART8SEL == STM32_UART8SEL_HSI
#define STM32_UART8CLK              STM32_HSICLK
#elif STM32_UART8SEL == STM32_UART8SEL_LSE
#define STM32_UART8CLK              STM32_LSECLK
#else
#error "invalid source selected for UART8 clock"
#endif

/**
 * @brief   I2C1 frequency.
 */
#if (STM32_I2C1SEL == STM32_I2C1SEL_PCLK1) || defined(__DOXYGEN__)
#define STM32_I2C1CLK               STM32_PCLK1
#elif STM32_I2C1SEL == STM32_I2C1SEL_SYSCLK
#define STM32_I2C1CLK               STM32_SYSCLK
#elif STM32_I2C1SEL == STM32_I2C1SEL_HSI
#define STM32_I2C1CLK               STM32_HSICLK
#else
#error "invalid source selected for I2C1 clock"
#endif

/**
 * @brief   I2C2 frequency.
 */
#if (STM32_I2C2SEL == STM32_I2C2SEL_PCLK1) || defined(__DOXYGEN__)
#define STM32_I2C2CLK               STM32_PCLK1
#elif STM32_I2C2SEL == STM32_I2C2SEL_SYSCLK
#define STM32_I2C2CLK               STM32_SYSCLK
#elif STM32_I2C2SEL == STM32_I2C2SEL_HSI
#define STM32_I2C2CLK               STM32_HSICLK
#else
#error "invalid source selected for I2C2 clock"
#endif

/**
 * @brief   I2C3 frequency.
 */
#if (STM32_I2C3SEL == STM32_I2C3SEL_PCLK1) || defined(__DOXYGEN__)
#define STM32_I2C3CLK               STM32_PCLK1
#elif STM32_I2C3SEL == STM32_I2C3SEL_SYSCLK
#define STM32_I2C3CLK               STM32_SYSCLK
#elif STM32_I2C3SEL == STM32_I2C3SEL_HSI
#define STM32_I2C3CLK               STM32_HSICLK
#else
#error "invalid source selected for I2C3 clock"
#endif

/**
 * @brief   I2C4 frequency.
 */
#if (STM32_I2C4SEL == STM32_I2C4SEL_PCLK1) || defined(__DOXYGEN__)
#define STM32_I2C4CLK               STM32_PCLK1
#elif STM32_I2C4SEL == STM32_I2C4SEL_SYSCLK
#define STM32_I2C4CLK               STM32_SYSCLK
#elif STM32_I2C4SEL == STM32_I2C4SEL_HSI
#define STM32_I2C4CLK               STM32_HSICLK
#else
#error "invalid source selected for I2C4 clock"
#endif

/**
 * @brief   LPTIM1 frequency.
 */
#if (STM32_LPTIM1SEL == STM32_LPTIM1SEL_PCLK1) || defined(__DOXYGEN__)
#define STM32_LPTIM1CLK             STM32_PCLK1
#elif STM32_LPTIM1SEL == STM32_LPTIM1SEL_LSI
#define STM32_LPTIM1CLK             STM32_LSICLK
#elif STM32_LPTIM1SEL == STM32_LPTIM1SEL_HSI
#define STM32_LPTIM1CLK             STM32_HSICLK
#elif STM32_LPTIM1SEL == STM32_LPTIM1SEL_LSE
#define STM32_LPTIM1CLK             STM32_LSECLK
#else
#error "invalid source selected for LPTIM1 clock"
#endif

/**
 * @brief   48MHz frequency.
 */
#if STM32_CLOCK48_REQUIRED || defined(__DOXYGEN__)
#if (STM32_CK48MSEL == STM32_CK48MSEL_PLL) || defined(__DOXYGEN__)
#define STM32_PLL48CLK              (STM32_PLLVCO / STM32_PLLQ_VALUE)
#elif STM32_CK48MSEL == STM32_CK48MSEL_PLLSAI
#define STM32_PLL48CLK              (STM32_PLLSAIVCO / STM32_PLLSAIQ_VALUE)
#else
#error "invalid source selected for PLL48CLK clock"
#endif
#else /* !STM32_CLOCK48_REQUIRED */
#define STM32_PLL48CLK              0
#endif /* !STM32_CLOCK48_REQUIRED */

/**
 * @brief   I2S frequency.
 */
#if (STM32_I2SSRC == STM32_I2SSRC_OFF) || defined(__DOXYGEN__)
#define STM32_I2SCLK                0
#elif STM32_I2SSRC == STM32_I2SSRC_CKIN
#define STM32_I2SCLK                0 /* Unknown, would require a board value */
#elif STM32_I2SSRC == STM32_I2SSRC_PLLI2S
#define STM32_I2SCLK                STM32_PLLI2S_R_CLKOUT
#else
#error "invalid source selected for I2S clock"
#endif

/**
 * @brief   SAI1 frequency.
 */
#if (STM32_SAI1SEL == STM32_SAI1SEL_OFF) || defined(__DOXYGEN__)
#define STM32_SAI1CLK               0
#elif STM32_SAI1SEL == STM32_SAI1SEL_SAIPLL
#define STM32_SAI1CLK               STM32_PLLSAIDIVQ_CLKOUT
#elif STM32_SAI1SEL == STM32_SAI1SEL_I2SPLL
#define STM32_SAI1CLK               STM32_PLLI2SDIVQ_CLKOUT
#elif STM32_SAI1SEL == STM32_SAI1SEL_CKIN
#define STM32_SAI1CLK               0 /* Unknown, would require a board value */
#else
#error "invalid source selected for SAI1 clock"
#endif

/**
 * @brief   SAI2 frequency.
 */
#if (STM32_SAI2SEL == STM32_SAI2SEL_OFF) || defined(__DOXYGEN__)
#define STM32_SAI2CLK               0
#elif STM32_SAI2SEL == STM32_SAI2SEL_SAIPLL
#define STM32_SAI2CLK               STM32_PLLSAIDIVQ_CLKOUT
#elif STM32_SAI2SEL == STM32_SAI2SEL_I2SPLL
#define STM32_SAI2CLK               STM32_PLLI2SDIVQ_CLKOUT
#elif STM32_SAI2SEL == STM32_SAI2SEL_CKIN
#define STM32_SAI2CLK               0 /* Unknown, would require a board value */
#else
#error "invalid source selected for SAI2 clock"
#endif

/**
 * @brief   SDMMC frequency.
 */
#if (STM32_SDMMCSEL == STM32_SDMMCSEL_PLL48CLK) || defined(__DOXYGEN__)
#define STM32_SDMMCCLK               STM32_PLL48CLK
#elif STM32_SDMMCSEL == STM32_SDMMCSEL_SYSCLK
#define STM32_SDMMCCLK               STM32_SYSCLK
#else
#error "invalid source selected for SDMMC clock"
#endif

/**
 * @brief   Clock of timers connected to APB1
 */
#if (STM32_PPRE1 == STM32_PPRE1_DIV1) || defined(__DOXYGEN__)
#define STM32_TIMCLK1               (STM32_PCLK1 * 1)
#else
#define STM32_TIMCLK1               (STM32_PCLK1 * 2)
#endif

/**
 * @brief   Clock of timers connected to APB2.
 */
#if (STM32_PPRE2 == STM32_PPRE2_DIV1) || defined(__DOXYGEN__)
#define STM32_TIMCLK2               (STM32_PCLK2 * 1)
#else
#define STM32_TIMCLK2               (STM32_PCLK2 * 2)
#endif
#endif

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

/* Various helpers.*/
#include "nvic.h"
#include "mpu.h"
#include "stm32_isr.h"
//#include "stm32_dma.h"
#include "stm32_rcc.h"

#ifdef __cplusplus
extern "C" {
#endif
  void hal_lld_init(void);
  void stm32_clock_init(void);
#ifdef __cplusplus
}
#endif

#endif /* HAL_LLD_H */

/** @} */