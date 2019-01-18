///*****************************************
//  Copyright (C) 2009-2018
//  ITE Tech. Inc. All Rights Reserved
//  Proprietary and Confidential
///*****************************************
//   @file   <iTE6615_CEC_DRV.h>
//   @author Kuro.Chung@ite.com.tw
//   @date   2018/09/18
//   @fileversion: iTE6615_MCUSRC_0.80
//******************************************/
#if defined(__USE_IT6615_TX__)

#ifndef _iTE6615_CEC_DRV_H_
#define _iTE6615_CEC_DRV_H_

void    iTE6615_CEC_Fire_Tx(void);

void    iTE6615_CEC_INIT_CMD(u8 Initiator,u8 Follower);

  u8    iTE6615_CEC_Check_IsPollingMsg(void);
  u8    iTE6615_CEC_Check_Fire_Ready(void);

  u8    iTE6615_CEC_Get_TxFailStatus(void);

void    iTE6615_CEC_Reset_RX_FIFO(void);

void    iTE6615_CEC_Clear_INT(void);

// Queue
u8   iTE6615_CEC_RX_CMD_Push(pu8 pHeader);
u8   iTE6615_CEC_RX_CMD_Pull(void);

#endif


#endif		//__USE_IT6615_TX__
