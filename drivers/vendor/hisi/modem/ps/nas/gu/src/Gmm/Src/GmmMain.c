/*******************************************************************************
  Copyright     : 2005-2007, Huawei Tech. Co., Ltd.
  File name     : GmmMain.c
  Description   : GMM TASK启动、初期化及消息分发处理用源文件
  Function List :
              GmmMsgProc
              Gmm_AbortCurrentService
              Gmm_BufSmDataReqMsg
              GMM_ComCheckIntegrityProtection
              GMM_ComCheckRauIntegrityProtection
              Gmm_ComCmpLai
              Gmm_ComForbiddenList
              Gmm_ComNetModeChange
              Gmm_ComNetModeChangeGsm
              Gmm_ComPlmnSearchInit
              Gmm_ComReset
              Gmm_ComServiceSts
              Gmm_ComStaChg
              Gmm_ComUnrealProc
              Gmm_ComVariantInit
              Gmm_DealWithBuffAfterProc
              Gmm_DealWithBuffInProc
              GMM_GetCurServiceStatus
              Gmm_GetGprsState
              Gmm_GetState
              Gmm_GmmStatusMsgMake
              Gmm_HoldBufferFree
              Gmm_MsgDistribute
              GMM_PrintState
              Gmm_RcvAcInfoChangeInd
              Gmm_RcvCmServReq_DeregAtmpToAtch
              Gmm_RcvCmServReq_RegAtmpToUpdt
              Gmm_RcvGmmStatusMsg
              Gmm_RcvLLCInform
              Gmm_RcvMmcAuthenticationFailureInd
              Gmm_RcvMmcCmServiceInd
              Gmm_RcvMmcCmServiceInd_InProc
              Gmm_RcvMmcCmServiceInd_RegNmlServ
              Gmm_RcvMmcCmServiceRejectInd
              Gmm_RcvMmcCoverageLostInd
              Gmm_RcvMmcGmmModeChangeReq
              Gmm_RcvMmcPlmnSearchInitiated
              Gmm_RcvMmcPlmnUserSelReq
              Gmm_RcvMmcRegisterInitiation
              Gmm_RcvMmcRegisterInitiation_DeregAtmpToAtch
              Gmm_RcvMmcRegisterInitiation_RegAtmpToUpdt
              Gmm_RcvMmcRegisterInitiation_ServReqInit
              Gmm_RcvMmcStartReq
              Gmm_RcvMmcSysInfoInd
              Gmm_RcvMmcSysInfoInd_DeregAtmpToAtch
              Gmm_RcvMmcSysInfoInd_DeregInit
              Gmm_RcvMmcSysInfoInd_DeregNmlServ
              Gmm_RcvMmcSysInfoInd_RauInit
              Gmm_RcvMmcSysInfoInd_RegAtmpToUpdt
              Gmm_RcvMmcSysInfoInd_RegInit
              Gmm_RcvMmcSysInfoInd_RegNmlServ
              Gmm_RcvMmcSysInfoInd_RegNoCell
              Gmm_RcvMmcSysInfoInd_RegUpdtNeed
              Gmm_RcvMmcSysInfoInd_ServReqInit
              Gmm_RcvMmcSysInfoInd_SuspWaitSys
              Gmm_RcvRrmmDataInd
              Gmm_RcvRrmmEstCnf
              Gmm_RcvRrmmEstCnf_DeregInit
              Gmm_RcvRrmmEstCnf_DeregNmlServ
              Gmm_RcvRrmmEstCnf_RauInit
              Gmm_RcvRrmmEstCnf_RegImsiDtchInit
              Gmm_RcvRrmmEstCnf_RegInit
              Gmm_RcvRrmmEstCnf_ServReqInit
              Gmm_RcvRrmmRelInd
              Gmm_RcvRrmmRelInd_DeregInit
              Gmm_RcvRrmmRelInd_DeregNmlServ
              Gmm_RcvRrmmRelInd_RauInit
              Gmm_RcvRrmmRelInd_RegImsiDtchInit
              Gmm_RcvRrmmRelInd_RegInit
              Gmm_RcvRrmmRelInd_RegNmlServ
              Gmm_RcvRrmmRelInd_ServReqInit
              Gmm_RcvSmDataReq
              Gmm_RcvSmDataReq_DeregInit
              Gmm_RcvSmDataReq_RegNmlServ
              Gmm_RcvSmPdpStatusInd
              Gmm_RcvTcDataReq
              Gmm_RcvTcTestReq
              Gmm_TaskInit
              GRM_Inform_Gmm
              WuepsGmmPidInit

  History       :
    1.  张志勇  2003.12.05  新规作成
    2.  l40632  2005.10.19  打印全局数据结构 问题单A32D00636
    3.日    期   : 2006年2月17日
      作    者   : liuyang id:48197
      修改内容   : 问题单号：A32D01287，打印错误
    4.  s46746  2006-03-15  根据问题单A32D02388修改
    5.  s46746  2006-03-18  根据问题单A32D02141修改

    6.日    期   : 2006年3月24日
      作    者   : liuyang id:48197
      修改内容   : 问题单号：A32D01882，网侧释放RR连接指示重建连接，当前重建时
                   所填建立RR连接原因错误
    7.  s46746  2006-03-27  根据问题单A32D02387修改
    8.  s46746  2006-04-03  根据问题单A32D01509修改

    9.日    期   : 2006年4月19日
      作    者   : liuyang id:48197
      修改内容   : 问题单号：A32D03208
    10.x51137 2006/4/21 A32D03244
    11. l40632  2006-04-24  根据问题单A32D03344修改
    12. s46746  2006-05-08  根据问题单A32D03487修改
    13. l40632  2006-05-19  根据问题单A32D03888修改
    14. l40632 2006-05-29 根据问题单A32D03821修改
    15. l40632 2006-06-19 根据问题单A32D04282修改
    16.  s46746  2006-06-16  根据问题单A32D03581修改
    17.日    期   : 2006年9月9日
       作    者   : sunxibo id:46746
       修改内容   : 根据问题单号：A32D05604
    18.日    期   : 2006年9月9日
       作    者   : sunxibo id:46746
       修改内容   : 根据问题单号：A32D05653
    19.日    期   : 2006年9月23日
       作    者   : sunxibo id:46746
       修改内容   : 根据问题单号：A32D06377
    20.日    期   : 2006年10月9日
       作    者   : s46746
       修改内容   : 根据问题单号：A32D05744
    21.x51137 2006/11/3 A32D06511
    22.日    期   : 2006年11月1日
       作    者   : s46746
       修改内容   : 根据问题单号：A32D06572
    23.日    期   : 2006年11月2日
       作    者   : sunxibo id:46746
       修改内容   : 根据问题单号：A32D06406
    24.日    期   : 2006年11月6日
       作    者   : s46746
       修改内容   : 问题单号:A32D06867
    25.日    期   : 2006年11月20日
       作    者   : s46746
       修改内容   : 创建，根据问题单号：A32D07433
    26.日    期   : 2006年12月07日
       作    者   : s46746
       修改内容   : 创建，根据问题单号：A32D07799
    27.日    期   : 2007年1月10日
       作    者   : x51137
       修改内容   : A32D08279
    28.日    期   : 2007年01月04日
       作    者   : luojian,id:60022475
       修改内容   : 根据问题单号：A32D06408
    29.日    期   : 2007年03月20日
       作    者   : x51137
       修改内容   : A32D09192
    30.日    期   : 2007年3月22日
       作    者   : liurui id:40632
       修改内容   : 根据问题单号：A32D09593
    31.日    期   : 2007年3月30日
       作    者   : s46746
       修改内容   : 问题单号:A32D09854
    32.日    期   : 2007年4月2日
       作    者   : x51137
       修改内容   : A32D09789
    33.日    期   : 2007年4月5日
       作    者   : luojian id:60022475
       修改内容   : 根据问题单号：A32D10023
    34.日    期   : 2007年4月26日
       作    者   : liurui id:40632
       修改内容   : 根据问题单号：A32D10052
    35.日    期   : 2007年6月9日
       作    者   : luojian id:60022475
       修改内容   : 根据问题单号：A32D11579
    36.日    期   : 2007年06月22日
       作    者   : l60022475
       修改内容   : 根据问题单号: A32D11911
    37.日    期   : 2007年06月29日
       作    者   : l65478
       修改内容   : 根据问题单号: A32D11896
    38.日    期   : 2007年07月02日
       作    者   : l65478
       修改内容   : 根据问题单号: A32D10052
    39.日    期   : 2007年07月05日
        作    者   : Li Jilin
        修改内容   : A32D11950
    40.日    期   : 2007年07月10日
       作    者   : luojian id:60022475
       修改内容   : 根据问题单A32D11966
    41.日    期   : 2007年7月14日
       作    者   : luojian id:60022475
       修改内容   : 根据问题单号：A32D12438
    42.日    期   : 2007年07月11日
       作    者   : hanlufeng 41410
       修改内容   : 根据问题单号：A32D12294
    43.日    期   : 2007年07月10日
       作    者   : s46746
       修改内容   : 根据问题单号：A32D12268
    44.日    期   : 2007年07月11日
       作    者   : hanlufeng 41410
       修改内容   : 根据问题单号：A32D11966
    45.日    期   : 2007年08月08日
       作    者   : l65478
       修改内容   : 根据问题单号：A32D12663
    46.日    期   : 2007年08月14日
       作    者   : luojian id:60022475
       修改内容   : 根据问题单号：A32D12689,
                    GMM_REGISTERED_IMSI_DETACH_INITIATED状态响应PDP激活请求
    47.日    期   : 2007年8月28日
       作    者   : l60022475
       修改内容   : 问题单号：A32D12744,初始化GMM Timer句柄
    48.日    期   : 2007年09月03日
       作    者   : luojian id:60022475
       修改内容   : 根据问题单号：AT2D01459
    49.日    期   : 2007年09月10日
       作    者   : s46746
       修改内容   : 根据问题单号：A32D12829
    50.日    期   : 2007年9月27日
       作    者   : s46746
       修改内容   : 将卡无效信息从RRMM_NAS_INFO_CHANGE消息中拿掉
    51.日    期   : 2007年10月10日
       作    者   : s46746
       修改内容   : 根据问题单号：A32D12948
    52.日    期   : 2007年10月13日
       作    者   : s46746
       修改内容   : 根据问题单号：A32D13060
    53.日    期   : 2007年10月26日
       作    者   : l39007
       修改内容   : A32D13207  Gmm_RcvMmcSysInfoInd中增加指定W搜网时清除GMM信令
                    连接标志的处理
    54.日    期   : 2007-10-26
       作    者   : hanlufeng
       修改内容   : A32D13172
    55.日    期   : 2007年11月16日
       作    者   : hanlufeng 41410
       修改内容   : A32D12187
    56.日    期   : 2007年11月20日
       作    者   : s46746
       修改内容   : 根据问题单号：A32D13510,在搜网状态指示接入层P/TMSI
    57.日    期   : 2007年11月22日
       作    者   : s46746
       修改内容   : 根据问题单号：A32D13475,修改异系统改变后指派的old TLLI和开机加密密钥为全0问题
    58.日    期   : 2007年12月04日
       作    者   : s46746
       修改内容   : 1.GMM模块进行ATTACH和RAU时，如果此时接入层进行临区任务，
                      会导致LLC将ATTACH和RAU延迟发送，使得ATTACH和RAU时间过长；
                    2.GMM在进行RAU请求时，如果DRX参数不改变，将不会在消息中
                      带DRX参数，这样跨SGSN的RAU时，可能导致网侧不识别UE的DR
                      X参数，  使得RAU不能成功。
    59.日    期   : 2007年12月08日
       作    者   : l00107747
       修改内容   : 根据问题单号：A32D13826,收到REL_IND如果缓存有关机消息需要处理
    60.日    期   : 2007年12月11日
       作    者   : s46746
       修改内容   : 根据问题单号：A32D13845,出服务区后，MMC立即启动异系统相同PLMN
                    搜索
    61.日    期   : 2007年12月15日
       作    者   : l00107747
       修改内容   : 问题单号:A32D13897
    62.日    期   : 2007年12月18日
       作    者   : s46746
       修改内容   : 问题单A32D13913，GMM在进行鉴权过程中，如果rand相同，也需要指
                    示层2加密算法和密钥
    63.日    期   : 2007年12月18日
       作    者   : l00107747
       修改内容   : 根据问题单号：A32D13917,GMM处理SM缓存和当前不能处理需要缓存需要区别处理，
                    否则会造成内存问题
    64.日    期   : 2007年12月20日
       作    者   : s46746
       修改内容   : 2G3切换，W下RAU过程中挂断电话，RAU ACCEPT消息接收到后，
                    在RAU COMPLETE消息未发送就进行联合RAU
    65.日    期   : 2007年12月21日
       作    者   : l00107747
       修改内容   : 问题单A32D13950,W支持CS&PS,G下不支持PS，切换到W模式后GMM没有发起联合RAU
    66.日    期   : 2007年12月21日
       作    者   : l00107747
       修改内容   : 问题单号:A32D13951
    67.日    期   : 2007年12月28日
       作    者   : s46746
       修改内容   : 根据问题单号：A32D13954,修改GMM在2G3过程中缓存消息机制
    68.日    期   : 2008年3月17日
       作    者   : s46746
       修改内容   : 问题单号:AT2D02570,NAS B005版本新增需求合入
    69.日    期   : 2008年7月2日
       作    者   : l00107747
       修改内容   : 根据问题单号：AT2D03900,FOLLOW ON标志清除排查
    70.日    期   : 2008年7月18日
       作    者   : luojian 00107747
       修改内容   : 根据问题单号：AT2D03887,修改CS无效情况下网络模式变更处理
    71.日    期   : 2008年7月24日
       作    者   : luojian 00107747
       修改内容   : 根据问题单号：AT2D04627/AT2D04237,
                      ATTEMPT TO UPDATE/ATTACH 状态对CM服务处理
    72.日    期   : 2008年7月28日
       作    者   : s46746
       修改内容   : 问题单号:AT2D03915,修改联合RAU类型,CS如果已经单独LAU成功，需要
                    发起with IMSI Attach的RAU
    73.日    期   : 2008年08月1日
       作    者   : luojian id:00107747
       修改内容   : 根据问题单AT2D04486/AT2D04822,修改CM服务请求拒绝原因值为#4,
                    RR连接释放后处理,依据 24.008 4.5.1.1,4.2.2.3
    74.日    期   : 2008年08月1日
       作    者   : luojian id:00107747
       修改内容   : 根据问题单AT2D04837/AT2D04947,依据 24.008 4.1.1.1，对L3消息统一进行完整性检查
    75.日    期   : 2008年08月25日
       作    者   : ouyangfei id:00132663
       修改内容   : 根据问题单号：AT2D04509,消除不必要的告警。
    76.日    期   : 2008年9月18日
       作    者   : ouyangfei 00132663
       修改内容   : 根据问题单号：AT2D05816，在GMM过程中，来自CM层的SMS请求应该被缓存，等GMM过程结束再发起。
    77.日    期   : 2008年9月23日
       作    者   : o00132663
       修改内容   : 根据问题单号：AT2D05839,清除无用全局变量 ucRlsMsgFlg和状态GMM_REGISTERED_WAIT_FOR_RAU
    78.日    期   : 2008年9月26日
       作    者   : x00115505
       修改内容   : 问题单号:AT2D05431
    79.日    期   : 2008年10月20日
       作    者   : x00115505
       修改内容   : 问题单号:AT2D06272
    80.日    期   : 2008年10月20日
       作    者   : x00115505
       修改内容   : 问题单号:AT2D06271
    81.日    期   : 2008年10月30日
       作    者   : x00115505
       修改内容   : 问题单号:AT2D06422
    82.日    期   : 2008年11月03日
       作    者   : x00115505
       修改内容   : 问题单号:AT2D06493
    83.日    期   : 2008年12月3日
       作    者   : ouyangfei id:00132663
       修改内容   : 根据问题单号：AT2D07165,在W下如果RR连接建立过程中丢网，不给WRR发RRMM_REL_REQ。
    84.日    期   : 2008年12月08日
       作    者   : x00115505
       修改内容   : 问题单号:AT2D06899:MS Detach过程中收到底层释放，
                    此时认为Detach成功，但是没有将全局量
                    g_MmSubLyrShare.MmcShare.ucPsAttachFlg置为MMC_ATTACH_NOT_ALLOW
    85.日    期   : 2008年12月26日
       作    者   : x00115505
       修改内容   : 问题单号:AT2D07892:2G模式下设置用户模式A或者B，
                    在SDT工具中查询NAS MM，其中Ue Operation Mode
                    显示为UE_OPERATE_MODE_A
    86.日    期   : 2009年01月15日
       作    者   : l00130025
       修改内容   : 问题单号:AT2D07018,LAU或RAU过程中搜网和SYSCFG设置,发起底层释放链接的操作
    88.日    期   : 2009年02月13日
       作    者   : o00132663
       修改内容   : 问题单号:AT2D08906,【TA 认证】【外场用例-HK】smartone UE没有处于attach状态,就发起了业务请求.
    90.日    期   : 2009年2月19日
       作    者   : o00132663
       修改内容  : 问题单号:AT2D09274,【GCF测试】用例12.4.1.3失败，RAC改变时，没有发起RAU。
    91.日    期   : 2009年02月24日
       作    者   : x00115505
       修改内容   : 问题单号:AT2D09321,MM给WRR下发的NAS_INFO_CHANGE_REQ TMSI中
                    的 plmn全 F，使WAS编码失败，RRC连接建立失败。
    92.日    期   : 2009年03月12日
       作    者   : ouyangfei id:00132663
       修改内容   : 问题单AT2D09683,丢网时，GMM上报服务状态异常导致MMC没有发起搜网。
    93.日    期   : 2009年03月21日
       作    者   : l00130025
       修改内容   : 问题单号:AT2D09534,异系统切换后的建链失败过程中关机，Gmm/MM对关机消息没有处理，后续设置AT^CPAM超时，无响应
    94.日    期   : 2009年3月31日
       作    者   : l00130025
       修改内容   : 问题单号：AT2D10231/AT2D10624 当RABM不能收到Dsflowrpt流量上报，
                    在PDP激活后W下丢网，涉及 W->G->W的切换时，数传不能恢复
    95.日    期   : 2009年04月06日
       作    者   : l00130025
       修改内容   : 根据问题单号：AT2D10790/AT2D10804，Gmm调用VOS_RestartRelTimer时，传入空指针，导致单板复位
    96.日    期   : 2009年4月9日
       作    者   : s46746
       修改内容   : 问题单号:AT2D10867,异系统改变后，未完成的Detach流程没有继续
    97.日    期   : 2009年4月22日
       作    者   : x00115505
       修改内容   : 问题单号:AT2D11234,RRC连接释放，原因值为"Directed Signalling
                    Connection Re-Establishment"，之后上报系统消息改变，网络模式
                    从I变为II，发起Rau，建立原因填写的是Registration，而不是
                    Call Re-Establishment，不符合协议要求。
    98.日    期   : 2009年5月5日
       作    者   : s62952
       修改内容   : AT2D11639
    99.日    期   : 2009年5月5日
       作    者   : x00115505
       修改内容   : AT2D11784,设置AT模式从A到CG时，发起imsi detach过程，
                    收到detach accept后未释放链路，直接发起pdp激活，UE收到pdp
                    激活接受后不理会重复发起pdp激活请求。
   100.日    期   : 2009年5月8日
       作    者   : x00115505
       修改内容   : AT2D11792,执行GCF测试用例8.2.2.50时由于GMM环回时不响应paging消息导致用例失败。
   101.日    期   : 2009年5月12日
       作    者   : x00115505
       修改内容   : AT2D11814,2G下PPP拨号失败
   102.日    期   : 2009年6月30日
       作    者   : x00115505
       修改内容   : AT2D12552,W重选到不支持GPRS的GSM小区，发PS短信，TAF没有判断
                    当前状态是否应该发起，仍然发送该短信
   103.日    期   : 2009年7月2日
       作    者   : l60609
       修改内容   : AT2D12314,【CMU自动化】已收到寻呼数据，但未建立R5链路
   104.日    期   : 2009年7月7日
       作    者   : l60609
       修改内容   : AT2D12732,设置CGCLASS为A然后设置为CG，拨号异常
   105.日    期   : 2009年7月22日
       作    者   : x00115505
       修改内容   : AT2D13182,SM对同一个NSAPI连续发起了两次PDP激活请求
   106.日    期   : 2009年7月23日
       作    者   : s46746
       修改内容   : 根据问题单号：AT2D12878，GSM下HPLMN搜索时接收到GPRS寻呼或PDP激活(W下PDP激活相同处理)请求需要能及时响应
   107.日    期   : 2009年7月31日
       作    者   : s46746
       修改内容   : 根据问题单号：AT2D13446，GMM在进行Detach过程中重选，需要立即进行RAU流程，因此释放接入层，
                    但在Deregister状态未记录标志g_GmmGlobalCtrl.ucRaiChgRelFlg，导致接收到释放指示后立即又进行了Detach流程
   108.日    期   : 2009年8月3日
       作    者   : s46746
       修改内容   : 根据问题单号：AT2D13469，测试GCF用例12.9.7c，PDP激活时Service Req被拒，
                    上层没有立即终止该过程，之后驻留正常服务小区后再次发起了PDP激活请求消息，导致用例失败
   109.日    期   : 2009年8月22日
       作    者   : l60609
       修改内容   : 根据问题单号：AT2D13782，G单模开机注册成功，设置W单模搜网失败，再设置回G单模，RAI不变
                    PDP激活失败
   110.日    期   : 2009年08月24日
       作    者   : x00115505
       修改内容   : AT2D14023,测试GCF用例44.2.2.1.9失败
   111.日    期   : 2009年08月29日
       作    者   : s46746
       修改内容   : AT2D14108,GMM模块在异系统重选状态接收到系统消息，如果小区被禁止，没有更新服务状态
   112.日    期   : 2009年9月7日
       作    者   : s46746
       修改内容   : 根据问题单号：AT2D14311，出服务区后，GMM存在连接时先进行了连接释放，会导致服务状态临时更新为Normal service
   113.日    期   : 2009年09月12日
       作    者   : s46746
       修改内容   : 问题单号：AT2D14432,HPLMN定时器在异系统重选过程中超时没有立即进行HPLMN搜索
   114.日    期   : 2009年09月19日
       作    者   : x00115505
       修改内容   : 问题单号：AT2D14251,Service Requset流程中，网络下发去激活，GMM直接丢弃
   115.日    期   : 2009年09月22日
       作    者   : x00115505
       修改内容   : 问题单号：AT2D14627,从W下网络模式I到G下网络模式II，没有发起Rau
   116.日    期   : 2009年09月25日
       作    者   : x00115505
       修改内容   : 问题单号:AT2d14773,关机时，SDT中可维可测功能查询IMSI为空
   117.日    期   : 2009年09月30日
       作    者   : x00115505
       修改内容   : AT2D14857,驻留到FPLMN上，GMM将更新状态修改为GU3了
   118.日    期   : 2009年10月22日
       作    者   : x00115505
       修改内容   : AT2D15174,PDP去激活失败
   119.日    期   : 2009年10月31日
       作    者   : x00115505
       修改内容   : AT2D15076,仅PS注册，PS短信发送中连接释放，转向CS域发送
   120.日    期   : 2009年11月3日
       作    者   : s46746
       修改内容   : AT2D15367,接入层点灯无服务后，正在搜网过程中，NAS在数据业务建立失败会改变灯状态
   121.日    期   : 2009年12月7日
       作    者   : s46746
       修改内容   : 问题单号：AT2D15718,CS LAU失败四次搜网修改为CS LAU失败四次PS RAU/ATTACH失败五次后搜网
   122.日    期   : 2009年12月17日
       作    者   : x00115505
       修改内容   : 问题单号:GCF用例8.1.2.3和8.1.2.9测试失败
   123.日    期   : 2010年04月21日
       作    者   : x00115505
       修改内容   : 问题单号:AT2D17739,单板特定场景下闪灯与要求不一致
   125.日    期   : 2010年6月17日
       作    者   : s46746
       修改内容   : DTS2010061500077,无卡出服务区后搜网异常
*******************************************************************************/
#include "GmmInc.h"
#include "psprimitive.h"
#include "GmmCasGlobal.h"
#include "GmmCasMain.h"
#include "GmmCasComm.h"
#include "GmmCasSuspend.h"
#include "GmmCasGsm.h"
#include "GmmCasSend.h"
#include "NasCommDef.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "GmmLmmInterface.h"
#include "NasGmmProcLResult.h"
#endif
#include "GmmMmInterface.h"
#include "NasMmcSndOm.h"
#include "GmmExt.h"
#include "NasGmmSndOm.h"
#include "NasUsimmApi.h"

#include "NasUtranCtrlInterface.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767 修改人:luojian 107747;检视人:sunshaohua65952;原因:LOG方案设计需要*/
#define    THIS_FILE_ID        PS_FILE_ID_GMM_MAIN_C
/*lint +e767 修改人:luojian 107747;检视人:sunshaohua*/

NAS_GMM_CTRL_STATUS_ENUM_UINT8  gucGmmInitState = NAS_GMM_CTRL_STATUS_STARTUP;

/*lint -save -e958 */

/*******************************************************************************
  Module:      GMM_ReportN2MOtaMsg
  Function:    在trace中勾取GMM的空口消息
  Input:       NAS_MSG_STRU*   pNasMsg     SM空口消息
  NOTE:
  Return:      VOS_VOID
  History:
      1. 鲁琳    2009.07.11   新规作成
*******************************************************************************/
VOS_VOID GMM_ReportN2MOtaMsg(NAS_MSG_STRU *pNasMsg)
{
    NAS_OTA_MSG_ID_ENUM_UINT16 usNasOtaMsyId = NAS_OTA_MSG_ID_BUTT;

    PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "GMM_ReportN2MOtaMsg:NORMAL: msg type is ", pNasMsg->aucNasMsg[1]);

    switch(pNasMsg->aucNasMsg[1])
    {
        case GMM_MSG_ATTACH_ACCEPT:
            usNasOtaMsyId = NAS_OTA_MSG_ATTACH_ACCEPT;
            break;

        case GMM_MSG_ATTACH_REJECT:
            usNasOtaMsyId = NAS_OTA_MSG_ATTACH_REJECT;
            break;

        case GMM_MSG_DETACH_REQUEST:
            usNasOtaMsyId = NAS_OTA_MSG_DETACH_REQ_BY_NET;
            break;

        case GMM_MSG_DETACH_ACCEPT:
            usNasOtaMsyId = NAS_OTA_MSG_DETACH_ACCEPT;
            break;

        case GMM_MSG_RAU_ACCEPT:
            usNasOtaMsyId = NAS_OTA_MSG_RAU_ACCEPT;
            break;

        case GMM_MSG_RAU_REJECT:
            usNasOtaMsyId = NAS_OTA_MSG_RAU_REJECT;
            break;

        case GMM_MSG_SERVICE_ACCEPT:
            usNasOtaMsyId = NAS_OTA_MSG_DATA_SERVICE_ACC;
            break;

        case GMM_MSG_SERVICE_REJECT:
            usNasOtaMsyId = NAS_OTA_MSG_DATA_SERVICE_REJ;
            break;

        case GMM_MSG_P_TMSI_REALLOCATION_COMMAND:
            usNasOtaMsyId = NAS_OTA_MSG_P_TMSI_REALLOCATION;
            break;

        case GMM_MSG_AUTHENTICATION_AND_CIPHERING_REQUEST:
            usNasOtaMsyId = NAS_OTA_MSG_AUTH_AND_CIPHER_REQ;
            break;

        case GMM_MSG_AUTHENTICATION_AND_CIPHERING_REJECT:
            usNasOtaMsyId = NAS_OTA_MSG_AUTH_AND_CIPHER_REJ;
            break;

        case GMM_MSG_IDENTITY_REQUEST:
            usNasOtaMsyId = NAS_OTA_MSG_IDENTITY_REQUEST;
            break;

        case GMM_MSG_GMM_STATUS:
            usNasOtaMsyId = NAS_OTA_MSG_GMM_STATUS;
            break;

        case GMM_MSG_GMM_INFORMATION:
            usNasOtaMsyId = NAS_OTA_MSG_GMM_INFORMATION;
            break;

        default:
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "GMM_ReportN2MOtaMsg:WARNING: invalid msg type!");
            /*不属于GMM模块的空口消息，不在trace中显示*/
            return;
    }

    NAS_SendAirMsgToOM(WUEPS_PID_GMM, usNasOtaMsyId, NAS_OTA_DIRECTION_DOWN, pNasMsg->ulNasMsgSize + 4, (VOS_UINT8 *)pNasMsg);
}


#ifdef __PS_WIN32_RECUR__


/*****************************************************************************
 函 数 名  : NAS_GMM_SetGmmSigFunc
 功能描述  : 设置GMM的g_GmmImportFunc的函数指针,G模不使用该指针，直接设置为W的处理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月1日
    作    者   : l00130025
    修改内容   : 回放调整，避免空指针或指针地址错误

*****************************************************************************/
VOS_VOID  NAS_GMM_SetGmmSigFunc(VOS_VOID)
{
    g_GmmImportFunc.RrmmDataReqFunc  = As_RrDataReq;
    g_GmmImportFunc.RrmmEstReqFunc   = NAS_GMM_AsEstReq;
    g_GmmImportFunc.RrmmRelReqFunc   = As_RrRelReq;
}


/*****************************************************************************
 函 数 名  : NAS_GMM_RestoreContextData
 功能描述  : 恢复GMM全局变量。
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年01月04日
    作    者   : 欧阳飞 00132663
    修改内容   : 新生成函数
  2.日    期   : 2012年2月1日
    作    者   : l00130025
    修改内容   : 回放调整，避免空指针或指针地址错误
  3.日    期   : 2011年11月30日
    作    者   : z00161729
    修改内容   : pc回放压缩功能修改
*****************************************************************************/
VOS_UINT32 NAS_GMM_RestoreContextData(struct MsgCB * pMsg)
{
    NAS_MML_PC_REPLAY_COMPRESS_CONTEXT_STRU                 *pstRcMsg;
    VOS_UINT32                                               ulExpectCount;
    VOS_UINT32                                               ulCount;
    VOS_UINT32                                               ulItemCount;
    VOS_UINT8                                               *pucDest;
    VOS_UINT8                                               *pucSrc;
    VOS_UINT32                                               ulDestLen;
    VOS_UINT32                                               ulMsgAddrForSm;

    ulExpectCount = 0;
    ulCount       = 0;
    ulItemCount   = 0;
    ulExpectCount = sizeof(NAS_GMM_CTRL_STATUS_ENUM_UINT8) /* gucGmmInitState */
                  + sizeof(VOS_UINT8)                      /* g_GmmInterRatCellReselect */
                  + sizeof(GMM_CAS_CTRL_STRU)              /* gstGmmCasGlobalCtrl */
                  + sizeof(GMM_SUSPEND_CTRL_STRU)          /* gstGmmSuspendCtrl */
                  + sizeof(GMM_GLOBAL_CTRL_STRU)           /* g_GmmGlobalCtrl */
                  + sizeof(GMM_TIMER_STRU)                 /* g_GmmTimerMng */
                  + sizeof(GMM_ATTACH_CTRL_STRU)           /* g_GmmAttachCtrl*/
                  + sizeof(GMM_RAU_CTRL_STRU)              /* g_GmmRauCtrl */
                  + sizeof(GMM_DOWNLINK_NPDU_STRU)         /* g_GmmDownLinkNpduBake */
                  + sizeof(GMM_DETACH_CTRL_STRU)           /* g_GmmDetachCtrl */
                  + sizeof(GMM_AUTHEN_CTRL_STRU)           /* g_GmmAuthenCtrl */
                  + sizeof(GMM_REQ_CNF_MNG_STRU)           /* g_GmmReqCnfMng */
                  + sizeof(GMM_SR_CTRL_STRU);              /* g_GmmServiceCtrl */

    pstRcMsg = (NAS_MML_PC_REPLAY_COMPRESS_CONTEXT_STRU *)pMsg;
    pucSrc   = pstRcMsg->aucData;

    /* 解析总长度 */
    PS_MEM_CPY(&ulCount, pucSrc, sizeof(VOS_UINT32));
    pucSrc += sizeof(VOS_UINT32);

    if( ulExpectCount != ulCount )
    {
        return VOS_FALSE;
    }

    /* gucGmmInitState目标地址 */
    pucDest     = (VOS_UINT8 *)&gucGmmInitState;
    ulDestLen   = sizeof(NAS_GMM_CTRL_STATUS_ENUM_UINT8);

    /* 解压缩 */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }
    pucSrc += (ulItemCount);

    /* g_GmmInterRatCellReselect目标地址 */
    pucDest     = (VOS_UINT8 *)&g_GmmInterRatCellReselect;
    ulDestLen   = sizeof(g_GmmInterRatCellReselect);

    /* 解压缩 */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }
    pucSrc += (ulItemCount);

    /* gstGmmCasGlobalCtrl目标地址 */
    pucDest     = (VOS_UINT8 *)&gstGmmCasGlobalCtrl;
    ulDestLen   = sizeof(GMM_CAS_CTRL_STRU);

    /* 解压缩 */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }
    pucSrc += (ulItemCount);

    /* gstGmmSuspendCtrl目标地址 */
    pucDest     = (VOS_UINT8 *)&gstGmmSuspendCtrl;
    ulDestLen   = sizeof(GMM_SUSPEND_CTRL_STRU);

    /* 解压缩 */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }
    pucSrc += (ulItemCount);

    /* g_GmmGlobalCtrl目标地址 */
    pucDest     = (VOS_UINT8 *)&g_GmmGlobalCtrl;
    ulDestLen   = sizeof(GMM_GLOBAL_CTRL_STRU);

    /*GTR运行时GMM保存的SM请求数据包为地址，而与实际回放时SM的请求包地址不同，所以不需要恢复该地址。*/
    ulMsgAddrForSm = g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSm;

    /* 解压缩 */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }

    g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSm = ulMsgAddrForSm;
    pucSrc += (ulItemCount);

    /* g_GmmTimerMng目标地址 */
    pucDest     = (VOS_UINT8 *)&g_GmmTimerMng;
    ulDestLen   = sizeof(GMM_TIMER_STRU);

    /* 解压缩 */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }
    pucSrc += (ulItemCount);

    /* g_GmmAttachCtrl目标地址 */
    pucDest     = (VOS_UINT8 *)&g_GmmAttachCtrl;
    ulDestLen   = sizeof(GMM_ATTACH_CTRL_STRU);

    /* 解压缩 */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }
    pucSrc += (ulItemCount);

    /* g_GmmRauCtrl目标地址 */
    pucDest     = (VOS_UINT8 *)&g_GmmRauCtrl;
    ulDestLen   = sizeof(GMM_RAU_CTRL_STRU);

    /* 解压缩 */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }
    pucSrc += (ulItemCount);

    /* g_GmmDownLinkNpduBake目标地址 */
    pucDest     = (VOS_UINT8 *)&g_GmmDownLinkNpduBake;
    ulDestLen   = sizeof(GMM_DOWNLINK_NPDU_STRU);

    /* 解压缩 */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }
    pucSrc += (ulItemCount);

    /* g_GmmDetachCtrl目标地址 */
    pucDest     = (VOS_UINT8 *)&g_GmmDetachCtrl;
    ulDestLen   = sizeof(GMM_DETACH_CTRL_STRU);

    /* 解压缩 */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }
    pucSrc += (ulItemCount);

    /* g_GmmAuthenCtrl目标地址 */
    pucDest     = (VOS_UINT8 *)&g_GmmAuthenCtrl;
    ulDestLen   = sizeof(GMM_AUTHEN_CTRL_STRU);

    /* 解压缩 */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }
    pucSrc += (ulItemCount);

    /* g_GmmReqCnfMng目标地址 */
    pucDest     = (VOS_UINT8 *)&g_GmmReqCnfMng;
    ulDestLen   = sizeof(GMM_REQ_CNF_MNG_STRU);

    /* 解压缩 */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }
    pucSrc += (ulItemCount);

    /* g_GmmServiceCtrl目标地址 */
    pucDest     = (VOS_UINT8 *)&g_GmmServiceCtrl;
    ulDestLen   = sizeof(GMM_SR_CTRL_STRU);

    /* 解压缩 */
    if (VOS_FALSE == NAS_MML_UnCompressData(pucDest, &ulDestLen, pucSrc, &ulItemCount) )
    {
        return VOS_FALSE;
    }
    pucSrc += (ulItemCount);

    NAS_INFO_LOG(WUEPS_PID_GMM, "NAS_GMM_RestoreContextData - data is restored.");

    NAS_GMM_SetGmmSigFunc();

    return VOS_TRUE;
}
#endif

/*****************************************************************************
 函 数 名  : NAS_GMM_SndOutsideContextData
 功能描述  : 把GMM外部上下文作为SDT消息发送出去，以便在回放时通过桩函数还原
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年01月03日
    作    者   : 欧阳飞 00132663
    修改内容   : 新生成函数
  2.日    期   : 2011年11月30日
    作    者   : z00161729
    修改内容   : 增加pc回放压缩功能

*****************************************************************************/
VOS_VOID NAS_GMM_SndOutsideContextData()
{
    VOS_UINT8                                              *pucCompressBuf;
    NAS_MML_PC_REPLAY_COMPRESS_CONTEXT_STRU                *pstPcreplayCompressCtx;
    VOS_UINT32                                              ulCompressDataLen;
    VOS_UINT32                                              ulCount;
    VOS_UINT8                                              *pucEndBuf;
    VOS_UINT32                                              ulItemCount;
    VOS_UINT8                                              *pucDest;
    VOS_UINT8                                              *pucSrc;
    VOS_UINT32                                              ulCmLen;

    ulCount     = sizeof(NAS_GMM_CTRL_STATUS_ENUM_UINT8) /* gucGmmInitState */
                + sizeof(VOS_UINT8)                      /* g_GmmInterRatCellReselect */
                + sizeof(GMM_CAS_CTRL_STRU)              /* gstGmmCasGlobalCtrl */
                + sizeof(GMM_SUSPEND_CTRL_STRU)          /* gstGmmSuspendCtrl */
                + sizeof(GMM_GLOBAL_CTRL_STRU)           /* g_GmmGlobalCtrl */
                + sizeof(GMM_TIMER_STRU)                 /* g_GmmTimerMng */
                + sizeof(GMM_ATTACH_CTRL_STRU)           /* g_GmmAttachCtrl*/
                + sizeof(GMM_RAU_CTRL_STRU)              /* g_GmmRauCtrl */
                + sizeof(GMM_DOWNLINK_NPDU_STRU)         /* g_GmmDownLinkNpduBake */
                + sizeof(GMM_DETACH_CTRL_STRU)           /* g_GmmDetachCtrl */
                + sizeof(GMM_AUTHEN_CTRL_STRU)           /* g_GmmAuthenCtrl */
                + sizeof(GMM_REQ_CNF_MNG_STRU)           /* g_GmmReqCnfMng */
                + sizeof(GMM_SR_CTRL_STRU);              /* g_GmmServiceCtrl */

    ulItemCount = 0;

    ulCompressDataLen  = NAS_MML_PC_RECUR_COMPRESS_DATA_LEN;
    pucCompressBuf     = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_GMM, ulCompressDataLen);

    if (VOS_NULL_PTR == pucCompressBuf)
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM,"NAS_GMM_SndOutsideContextData: Alloc Fail.");
        return;
    }

    pstPcreplayCompressCtx = (NAS_MML_PC_REPLAY_COMPRESS_CONTEXT_STRU *)pucCompressBuf;

    /* 获取buf结尾地址，用于计算剩余空间*/
    pucEndBuf = pucCompressBuf + ulCompressDataLen;
    pucDest   = pstPcreplayCompressCtx->aucData;

    /* 原始数据大小 */
    PS_MEM_CPY(pucDest, &ulCount, sizeof(VOS_UINT32));
    pucDest += sizeof(VOS_UINT32);

    /* 压缩gucGmmInitState*/
    pucSrc      = (VOS_UINT8 *)&gucGmmInitState;
    ulItemCount = sizeof(NAS_GMM_CTRL_STATUS_ENUM_UINT8);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if ( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen , pucSrc , ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_GMM, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);

    /* 压缩g_GmmInterRatCellReselect */
    pucSrc      = (VOS_UINT8 *)&g_GmmInterRatCellReselect;
    ulItemCount = sizeof(g_GmmInterRatCellReselect);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if ( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen, pucSrc, ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_GMM, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);

    /* 压缩gstGmmCasGlobalCtrl */
    pucSrc      = (VOS_UINT8 *)&gstGmmCasGlobalCtrl;
    ulItemCount = sizeof(GMM_CAS_CTRL_STRU);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if ( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen, pucSrc, ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_GMM, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);

    /* 压缩gstGmmSuspendCtrl */
    pucSrc      = (VOS_UINT8 *)&gstGmmSuspendCtrl;
    ulItemCount = sizeof(GMM_SUSPEND_CTRL_STRU);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if ( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen, pucSrc, ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_GMM, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);

    /* 压缩g_GmmGlobalCtrl */
    pucSrc      = (VOS_UINT8 *)&g_GmmGlobalCtrl;
    ulItemCount = sizeof(GMM_GLOBAL_CTRL_STRU);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if ( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen, pucSrc, ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_GMM, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);

    /* 压缩g_GmmTimerMng */
    pucSrc      = (VOS_UINT8 *)&g_GmmTimerMng;
    ulItemCount = sizeof(GMM_TIMER_STRU);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if ( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen, pucSrc, ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_GMM, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);

    /* 压缩g_GmmAttachCtrl */
    pucSrc      = (VOS_UINT8 *)&g_GmmAttachCtrl;
    ulItemCount = sizeof(GMM_ATTACH_CTRL_STRU);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if ( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen, pucSrc, ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_GMM, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);

    /* 压缩g_GmmRauCtrl */
    pucSrc      = (VOS_UINT8 *)&g_GmmRauCtrl;
    ulItemCount = sizeof(GMM_RAU_CTRL_STRU);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if ( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen, pucSrc, ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_GMM, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);

    /* 压缩g_GmmDownLinkNpduBake */
    pucSrc      = (VOS_UINT8 *)&g_GmmDownLinkNpduBake;
    ulItemCount = sizeof(GMM_DOWNLINK_NPDU_STRU);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if ( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen, pucSrc, ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_GMM, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);

    /* 压缩g_GmmDetachCtrl */
    pucSrc      = (VOS_UINT8 *)&g_GmmDetachCtrl;
    ulItemCount = sizeof(GMM_DETACH_CTRL_STRU);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if ( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen, pucSrc, ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_GMM, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);


    /* 压缩g_GmmAuthenCtrl */
    pucSrc      = (VOS_UINT8 *)&g_GmmAuthenCtrl;
    ulItemCount = sizeof(GMM_AUTHEN_CTRL_STRU);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if ( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen, pucSrc, ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_GMM, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);

    /* 压缩g_GmmReqCnfMng */
    pucSrc      = (VOS_UINT8 *)&g_GmmReqCnfMng;
    ulItemCount = sizeof(GMM_REQ_CNF_MNG_STRU);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if ( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen, pucSrc, ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_GMM, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);

    /* 压缩g_GmmServiceCtrl */
    pucSrc      = (VOS_UINT8 *)&g_GmmServiceCtrl;
    ulItemCount = sizeof(GMM_SR_CTRL_STRU);
    /*lint -e961*/
    ulCmLen     = (VOS_UINT32)(pucEndBuf - pucDest + 1);
    /*lint +e961*/
    if( VOS_FALSE == NAS_MML_CompressData(pucDest, &ulCmLen, pucSrc, ulItemCount) )
    {
        PS_MEM_FREE(WUEPS_PID_GMM, pucCompressBuf);
        return;
    }
    pucDest += (ulCmLen);

    ulCompressDataLen = (VOS_UINT32)(pucDest - (VOS_UINT8 *)pstPcreplayCompressCtx);

    pstPcreplayCompressCtx->ulReceiverPid      = WUEPS_PID_GMM;
    pstPcreplayCompressCtx->ulSenderPid        = WUEPS_PID_GMM;
    pstPcreplayCompressCtx->ulSenderCpuId      = VOS_LOCAL_CPUID;
    pstPcreplayCompressCtx->ulReceiverCpuId    = VOS_LOCAL_CPUID;
    pstPcreplayCompressCtx->ulLength           = ulCompressDataLen;
    pstPcreplayCompressCtx->ulMsgName          = EVT_NAS_GMM_OUTSIDE_RUNNING_CONTEXT_FOR_PC_REPLAY;
    DIAG_TraceReport(pstPcreplayCompressCtx);

    PS_MEM_FREE(WUEPS_PID_GMM, pucCompressBuf);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_MsgProcAtStatusNull
 功能描述  : GMM模块控制状态为NULL时的消息处理函数
 输入参数  : MsgCB *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月20日
    作    者   : o00132663
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_GMM_MsgProcAtStatusNull(
    struct MsgCB                        *pMsg
)
{
    MSG_HEADER_STRU                     *pMsgHeader;

    pMsgHeader                          = (MSG_HEADER_STRU *)pMsg;

    if ((WUEPS_PID_ADMIN == pMsgHeader->ulSenderPid)
     && (WUEPS_START_REQ == pMsgHeader->ulMsgName))
    {
        #ifdef __PS_WIN32_RECUR__
        Gmm_TaskInit();
        #endif

        gucGmmInitState = NAS_GMM_CTRL_STATUS_STARTUP;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_MsgProcAtStatusStartup
 功能描述  : GMM模块控制状态为Startup时的消息处理函数
 输入参数  : struct MsgCB *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月20日
    作    者   : o00132663
    修改内容   : 新生成函数
  2.日    期  : 2012年08月24日
    作    者  : m00217266
    修改内容  : 修改Gmm_SndSmEstablishCnf接口，添加原因值

*****************************************************************************/
VOS_VOID NAS_GMM_MsgProcAtStatusStartup(
    struct MsgCB                        *pMsg
)
{
    MSG_HEADER_STRU                     *pMsgHeader;

    pMsgHeader                          = (MSG_HEADER_STRU *)pMsg;

    if ((WUEPS_PID_MMC == pMsgHeader->ulSenderPid)
     && (MMCGMM_START_REQ == pMsgHeader->ulMsgName))
    {
        Gmm_TaskInit();
        Gmm_RcvMmcStartReq();
        gucGmmInitState = NAS_GMM_CTRL_STATUS_INSERVICE;

        #ifndef __PS_WIN32_RECUR__


        if ( VOS_TRUE == NAS_MML_IsSndOmPcRecurMsgValid() )
        {
            NAS_GMM_SndOutsideContextData();
        }

        #endif
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_MsgProcAtStatusStartup:Receive message at state NAS_GMM_CTRL_STATUS_STARTUP.");

        if ((WUEPS_PID_SM == pMsgHeader->ulSenderPid)
            && (GMMSM_ESTABLISH_REQ == pMsgHeader->ulMsgName))
        {
            Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_STARTUP);
        }
        else if ((WUEPS_PID_SMS == pMsgHeader->ulSenderPid)
            && (PMMSMS_EST_REQ == pMsgHeader->ulMsgName))
        {
            Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);
        }
        else
        {

        }
    }

    return;
}

/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-29, begin */
/*****************************************************************************
 函 数 名  : NAS_GMM_RcvMmCsConnectInd_PreProc
 功能描述  : 收到MM的信令连接指示消息的预处理
 输入参数  : pstRcvMsg:消息的首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2013年10月29日
   作    者   : w00176964
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID NAS_GMM_RcvMmCsConnectInd_PreProc(
    VOS_VOID                           *pstRcvMsg                               /* 接收消息使用的头地址定义                 */
)
{
    MMGMM_CS_CONNECT_IND_STRU          *pstMmCmServiceInd;                      /* 定义原语类型指针                         */

    pstMmCmServiceInd = (MMGMM_CS_CONNECT_IND_STRU *)pstRcvMsg;                   /* 强制类型转换                             */

    if (MMGMM_CS_CONNECT_ESTING == pstMmCmServiceInd->enCsConnectStatus)
    {
        g_GmmGlobalCtrl.CsInfo.ucCsTransFlg = GMM_TRUE;                         /* 置CS通信中为真                           */
    }
    else if (MMGMM_CS_CONNECT_EXIST == pstMmCmServiceInd->enCsConnectStatus)
    {
        g_GmmGlobalCtrl.CsInfo.ucCsTransFlg = GMM_TRUE;
    }
    else
    {
        g_GmmGlobalCtrl.CsInfo.ucCsTransFlg = GMM_FALSE;                        /* 置CS通信中为假                           */
    }

    return;                                                                     /* 返回                                     */
}

/* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-29, end */


/*****************************************************************************
 函 数 名  : NAS_GMM_MsgProcAtStatusInService
 功能描述  : GMM模块控制状态为INSERVICE时的消息处理
 输入参数  : struct MsgCB *pMsg
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年1月20日
    作    者   : o00132663
    修改内容   : 新生成函数
  2.日    期   : 2010年12月21日
    作    者   : o00132663
    修改内容   : 问题单号:DTS2010121800152,GMM关机关不掉，状态挂死
  3.日    期   : 2011年7月10日
    作    者   : w00166186
    修改内容   : V7R1 PHASE II ATTACH/DETACH调整
  4.日    期   : 2011年10月21日
    作    者   : h44270
    修改内容   : V7R1 FAST DORMANCY特性，增加来自RABM消息的处理
  5.日    期   : 2013年7月11日
    作    者   : M00217266
    修改内容   : GMM状态查询函数添加入参
  6.日    期   : 2013年10月29日
     作    者  : W00176964
     修改内容  : VoLTE_PhaseII 项目修改:增加MM的连接指示消息预处理
  7.日    期   : 2014年05月22日
    作    者   : W00242748
    修改内容   : DTS2014050900899:将GMM的处理状态通知给WAS
  8.日    期   : 2015年09月23日
    作    者   : c00318887
    修改内容   : DTS2015082604451:修改DSDS宏控
*****************************************************************************/
VOS_UINT8 NAS_GMM_MsgProcAtStatusInService(
    struct MsgCB                        *pMsg
)
{
    VOS_UINT8                           ucFollowOn;
    REL_TIMER_MSG                       *pTimerMsg;
    MSG_HEADER_STRU                     *pMsgHeader;

    pMsgHeader = (MSG_HEADER_STRU *)pMsg;

    if ((WUEPS_PID_MMC == pMsg->ulSenderPid)
     && (MMCGMM_START_REQ == pMsgHeader->ulMsgName))
    {
        Gmm_RcvMmcStartReq();
        return VOS_TRUE;
    }

    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-29, begin */
    if ((WUEPS_PID_MM         == pMsg->ulSenderPid)
     && (MMGMM_CS_CONNECT_IND == pMsgHeader->ulMsgName))
    {
        NAS_GMM_RcvMmCsConnectInd_PreProc(pMsg);
    }
    /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-29, end */

    if ((WUEPS_PID_MMC == pMsg->ulSenderPid)
     && (MMCGMM_ATTACH_REQ == pMsgHeader->ulMsgName))
    {
        if (VOS_TRUE == NAS_GMM_RcvMmcAttachReq_PreProc((MMCGMM_ATTACH_REQ_STRU*)pMsg))
        {
            return VOS_TRUE;
        }
    }

    if ((WUEPS_PID_MMC == pMsg->ulSenderPid)
    && (MMCGMM_DETACH_REQ == pMsgHeader->ulMsgName))
    {
        if (VOS_TRUE == NAS_GMM_RcvMmcDetachReq_PreProc((MMCGMM_DETACH_REQ_STRU*)pMsg))
        {
            return VOS_TRUE;
        }
    }

    if (WUEPS_PID_SMS == pMsg->ulSenderPid)
    {
        if (GMMSMS_BEGIN_SESSION_NOTIFY == pMsgHeader->ulMsgName)
        {
            NAS_GMM_RcvSmsBeginSessionNotify_PreProc((GMMSMS_BEGIN_SESSION_NOTIFY_STRU *)pMsg);
            return VOS_TRUE;
        }

        if (GMMSMS_END_SESSION_NOTIFY == pMsgHeader->ulMsgName)
        {
            NAS_GMM_RcvSmsEndSessionNotify_PreProc((GMMSMS_END_SESSION_NOTIFY_STRU *)pMsg);
            return VOS_TRUE;
        }
    }

    if (WUEPS_PID_SM == pMsg->ulSenderPid)
    {
        if (GMMSM_BEGIN_SESSION_NOTIFY == pMsgHeader->ulMsgName)
        {
            NAS_GMM_RcvSmBeginSessionNotify_PreProc((GMMSM_BEGIN_SESSION_NOTIFY_STRU *)pMsg);
            return VOS_TRUE;
        }

        if (GMMSM_END_SESSION_NOTIFY == pMsgHeader->ulMsgName)
        {
            NAS_GMM_RcvSmEndSessionNotify_PreProc((GMMSM_END_SESSION_NOTIFY_STRU *)pMsg);
            return VOS_TRUE;

        }
    }

    if ((WUEPS_PID_RABM == pMsg->ulSenderPid)
    && (ID_RABM_GMM_MML_PROC_STATUS_QRY_REQ == pMsgHeader->ulMsgName))
    {
        NAS_GMM_RcvRabmMmlProcStatusQryReq((struct MsgCB *)pMsg);
        return VOS_TRUE;
    }

    if (RRMM_GMM_PROC_ENQ == pMsgHeader->ulMsgName)
    {
        if ( (WUEPS_PID_WRR == pMsgHeader->ulSenderPid)
          || (UEPS_PID_GAS == pMsgHeader->ulSenderPid) )
        {
            NAS_GMM_SndRrmmGmmProcAns();
        }

        return VOS_TRUE;
    }

    GMM_CasMsgProc(pMsg, &ucFollowOn);

    if (VOS_FALSE == ucFollowOn)
    {
        return VOS_FALSE;
    }

    if (VOS_PID_TIMER == pMsg->ulSenderPid)
    {
        pTimerMsg = (REL_TIMER_MSG*)pMsg;

        Gmm_RcvTimerExpired((VOS_UINT8)pTimerMsg->ulName);
    }
    else if (WUEPS_PID_ADMIN == pMsg->ulSenderPid)
    {
        if (WUEPS_RESET_REQ == pMsgHeader->ulMsgName)
        {
            gucGmmInitState = NAS_GMM_CTRL_STATUS_NULL;
        }
    }
    else
    {
        if (WUEPS_PID_GMM == pMsgHeader->ulReceiverPid)
        {
            Gmm_MsgDistribute((VOS_VOID*)pMsg);
        }
        else
        {
            NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_MsgProcAtStatusInService: The message is not GMM message.");
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;

}
/*******************************************************************************
  Module   : GmmMsgProc
  Function : GMM TASK入口函数
  Input    : MsgCB* pMsg
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2005.01.25  新规作成
    2. 日    期   : 2007年10月24日
       作    者   : l65478
       修改内容   : A32D13102

  2.日    期   : 2014年3月22日
    作    者   : z00234330
    修改内容   : dts2014032202060增加可谓可测，gmm没收到一条消息，输出信息
*******************************************************************************/
VOS_VOID GmmMsgProc(
    struct MsgCB*                       pMsg
)
{
    VOS_UINT8                ucResult;

#ifdef __PS_WIN32_RECUR__
    if ((WUEPS_PID_GMM == pMsg->ulSenderPid)
     && (WUEPS_PID_GMM == pMsg->ulReceiverPid))
    {
        NAS_GMM_RestoreContextData(pMsg);
    }
#endif


    NAS_GMM_LogGmmStateInfo(g_GmmGlobalCtrl.ucState);

    switch (gucGmmInitState)
    {
        case NAS_GMM_CTRL_STATUS_NULL:
            NAS_GMM_MsgProcAtStatusNull(pMsg);
            break;

        case NAS_GMM_CTRL_STATUS_STARTUP:
            NAS_GMM_MsgProcAtStatusStartup(pMsg);
            break;

        case NAS_GMM_CTRL_STATUS_INSERVICE:
            ucResult = NAS_GMM_MsgProcAtStatusInService(pMsg);
            if (VOS_FALSE == ucResult)
            {
                return;
            }
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_GMM, "GmmMsgProc:WARNING: gucGmmInitState is Abnormal!");
            break;
    }
/*
#ifndef __PS_WIN32_RECUR__
    NAS_MML_SetUePcRecurFlg(VOS_TRUE);
#endif
*/
    return;
}

/*****************************************************************************
 函 数 名  : Gmm_MsgDistribute_GMM_TC_ACTIVE
 功能描述  : TC状态下的消息处理
 输入参数  : VOS_VOID *pRcvMsg
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年06月14日
    作    者   : 欧阳飞
    修改内容   : 新生成函数
  2.日    期   : 2011年7月10日
    作    者   : w00166186
    修改内容   : V7R1 PHASE II ATTACH/DETACH调整
  3.日    期   : 2012年5月16日
    作    者   : l00171473
    修改内容   : DTS2012051501127, 进入TC状态后, W2G时未通知GPHY.
  4.日    期   : 2013年6月7日
    作    者   : w00167002
    修改内容   : SVLTE:收到DETACH消息，则发起去注册
*****************************************************************************/
VOS_UINT8 Gmm_MsgDistribute_GMM_TC_ACTIVE(
    VOS_VOID                           *pRcvMsg                                 /* 接收消息使用的头地址定义                 */
)
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* 定义MSG_HEADER_STRU类型指针              */
    VOS_UINT8            ucRst = GMM_TRUE;

    MMCGMM_DETACH_REQ_STRU             *pstDetachReq = VOS_NULL_PTR;

    pstDetachReq  = (MMCGMM_DETACH_REQ_STRU *)pRcvMsg;

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                                 /* 得到消息头                               */

    if ((WUEPS_PID_RABM == pNasMsgHeader->ulSenderPid)
        || (WUEPS_PID_SM == pNasMsgHeader->ulSenderPid)
        || (WUEPS_PID_SMS == pNasMsgHeader->ulSenderPid))
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_MsgDistribute:WARNING: Receive Msg from AGENT,RABM,SM or SMS is Abnormal when GMM is in GMM_TC_ACTIVE");
        ucRst = GMM_FALSE;
    }
    else if ((WUEPS_PID_WRR == pNasMsgHeader->ulSenderPid)
        && (RRMM_REL_IND != pNasMsgHeader->ulMsgName)
        && (RRMM_DATA_IND != pNasMsgHeader->ulMsgName)
        && (RRMM_PAGING_IND != pNasMsgHeader->ulMsgName))
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_MsgDistribute:WARNING: Receive Msg except RRMM_REL_IND,RRMM_DATA_IND is Abnormal when GMM is in GMM_TC_ACTIVE");
        ucRst = GMM_FALSE;
    }
    else if ((WUEPS_PID_MMC == pNasMsgHeader->ulSenderPid)
           &&(MMCGMM_ATTACH_REQ == pNasMsgHeader->ulMsgName))
    {
        /* 判断等待标志是否存在，如果存在则发送MMCGMM_ATTACH CNF */
        if (GMM_WAIT_PS_ATTACH == (g_GmmGlobalCtrl.stAttachInfo.enAttachType
                                 & GMM_WAIT_PS_ATTACH))
        {
            NAS_GMM_SndMmcAttachCnf();
        }
        g_GmmGlobalCtrl.stAttachInfo.enAttachType = GMM_WAIT_NULL_ATTACH;
    }

    else if ( (WUEPS_PID_MMC     == pNasMsgHeader->ulSenderPid)
           && (MMCGMM_DETACH_REQ == pNasMsgHeader->ulMsgName) )
    {
        /* 判断等待Detach标志是否存在，如果存在则发送detach */
        if ( GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType )
        {
            Gmm_MsInitNormalDetach(pstDetachReq->enDetachType);
        }

        /* 当前DETACH消息不需要再进行处理 */
        ucRst = GMM_FALSE;
    }
    else if (WUEPS_PID_MMC == pNasMsgHeader->ulSenderPid)
    {
        ucRst = NAS_Gmm_IsValidMmcMsg_GmmTcActive(pRcvMsg);
    }
    else
    {
    }
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_MsgDistribute:INFO: GMM is in GMM_TC_ACTIVE");


    /* 收到接入层PS域连接释放消息时，通知TC连接释放 */
    if ( (WUEPS_PID_WRR == pNasMsgHeader->ulSenderPid)
      && (RRMM_REL_IND == pNasMsgHeader->ulMsgName) )
    {
        NAS_GMM_SndTcRrRelInd();
    }

    /* 从MMC收到COVERAGE LOST消息时，通知TC连接释放 */
    if ( (WUEPS_PID_MMC == pNasMsgHeader->ulSenderPid)
      && (MMCGMM_COVERAGE_LOST_IND == pNasMsgHeader->ulMsgName) )
    {
        NAS_GMM_SndTcRrRelInd();
    }


    return ucRst;
}

/***********************************************************************
 *  MODULE   : Gmm_MsgDistribute_GMM_NULL
 *  FUNCTION : Gmm_MsgDistribute函数降复杂度: GMM_NULL状态的处理
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1.  欧阳飞   2009.06.11  新版作成
     2.日    期  : 2012年08月24日
       作    者  : m00217266
       修改内容  : 修改Gmm_SndSmEstablishCnf接口，添加原因值
     3.日    期   : 2012年11月24日
       作    者   : z60575
       修改内容   : DTS2012112003432，飞行模式问题修改

     3.日    期   : 2013年6月20日
       作    者   : w00167002
       修改内容   : V9R1_SVLTE:GMM NULL状态处理MMC消息
 ************************************************************************/
VOS_UINT8 Gmm_MsgDistribute_GMM_NULL(
                       VOS_VOID *pRcvMsg                                        /* 接收消息使用的头地址定义                 */
                       )
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* 定义MSG_HEADER_STRU类型指针              */
    VOS_UINT8            ucRst = GMM_TRUE;

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                                 /* 得到消息头                               */

    if (WUEPS_PID_RABM == pNasMsgHeader->ulSenderPid)
    {
        if(ID_RABM_GMM_REESTABLISH_REQ == pNasMsgHeader->ulMsgName)
        {
            Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);
        }
        ucRst = GMM_FALSE;
    }
    else if(WUEPS_PID_SM == pNasMsgHeader->ulSenderPid)
    {
        if(GMMSM_ESTABLISH_REQ == pNasMsgHeader->ulMsgName)
        {
            Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_NULL);
        }
        ucRst = GMM_FALSE;
    }
    else if(WUEPS_PID_SMS == pNasMsgHeader->ulSenderPid)
    {
        if(PMMSMS_EST_REQ == pNasMsgHeader->ulMsgName)
        {
            Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);
        }
        else if(PMMSMS_UNITDATA_REQ == pNasMsgHeader->ulMsgName)
        {
            Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);
        }
        else
        {
        }
        ucRst = GMM_FALSE;
    }

    else if (WUEPS_PID_MMC == pNasMsgHeader->ulSenderPid)
    {
        ucRst = Gmm_MsgDistribute_ProcMmcMsg_GmmNull(pRcvMsg);
    }
    else if(WUEPS_PID_WRR == pNasMsgHeader->ulSenderPid)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_MsgDistribute:WARNING: Receive Msg from AGENT or RRC is Abnormal when GMM is in GMM_NULL");
        ucRst = GMM_FALSE;
    }
    else if ((WUEPS_PID_TC == pNasMsgHeader->ulSenderPid)
        && (TCGMM_TEST_REQ != pNasMsgHeader->ulMsgName))
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_MsgDistribute:WARNING: Receive TCGMM_TEST_REQ Msg is Abnormal when  is in GMM_NULL");
        ucRst = GMM_FALSE;
    }
    else
    {
    }

    return ucRst;
}

/***********************************************************************
 *  MODULE   : Gmm_MsgDistribute_SpecProc_Handling
 *  FUNCTION : Gmm_MsgDistribute函数降复杂度: SpecProc的处理
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1.  欧阳飞   2009.06.11  新版作成
     2.日    期  : 2012年08月24日
       作    者  : m00217266
       修改内容  : 修改Gmm_SndSmEstablishCnf接口，添加原因值
 ************************************************************************/
VOS_UINT8 Gmm_MsgDistribute_SpecProc_Handling(
                       VOS_VOID *pRcvMsg                                        /* 接收消息使用的头地址定义                 */
                       )
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* 定义MSG_HEADER_STRU类型指针              */
    VOS_UINT8            ucRst = GMM_TRUE;

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                                 /* 得到消息头                               */

    if (GMM_ABORT_CURRENT_SERVICE == g_GmmGlobalCtrl.ucSpecProc)
    {
        if (WUEPS_PID_MMC != pNasMsgHeader->ulSenderPid)
        {
            if ((WUEPS_PID_WRR == pNasMsgHeader->ulSenderPid)
                && (RRMM_REL_IND == pNasMsgHeader->ulMsgName))
            {
                g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;
            }
            else
            {
                ucRst = GMM_FALSE;
            }
        }
    }

    if ((GMM_DETACH_COMBINED_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc)
        || (GMM_DETACH_NORMAL_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc)
        || (GMM_DETACH_COMBINED_SIM_REMOVE == g_GmmGlobalCtrl.ucSpecProc)
        || (GMM_DETACH_NORMAL_SIM_REMOVE == g_GmmGlobalCtrl.ucSpecProc))
    {
        if (WUEPS_PID_RABM == pNasMsgHeader->ulSenderPid)
        {
            if(ID_RABM_GMM_REESTABLISH_REQ == pNasMsgHeader->ulMsgName)
            {
                Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);
            }
            ucRst = GMM_FALSE;
        }
        else if(WUEPS_PID_SM == pNasMsgHeader->ulSenderPid)
        {
            if(GMMSM_ESTABLISH_REQ == pNasMsgHeader->ulMsgName)
            {
                Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_PS_DETACH);
            }
            ucRst = GMM_FALSE;
        }
        else if(WUEPS_PID_SMS == pNasMsgHeader->ulSenderPid)
        {
            if(PMMSMS_EST_REQ == pNasMsgHeader->ulMsgName)
            {
                Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);
            }
            else if(PMMSMS_UNITDATA_REQ == pNasMsgHeader->ulMsgName)
            {
                Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);
            }
            else
            {
            }
            ucRst = GMM_FALSE;
        }
        else if((WUEPS_PID_MMC == pNasMsgHeader->ulSenderPid)
            || (WUEPS_PID_TC == pNasMsgHeader->ulSenderPid))
        {
            if (MMCGMM_ATTACH_REQ == pNasMsgHeader->ulMsgName)
            {

                /* 判断等待标志是否存在，如果存在则发送MMCGMM_ATTACH CNF */
                if (GMM_WAIT_PS_ATTACH == (g_GmmGlobalCtrl.stAttachInfo.enAttachType
                                         & GMM_WAIT_PS_ATTACH))
                {
                    NAS_GMM_SndMmcAttachCnf();
                }
                g_GmmGlobalCtrl.stAttachInfo.enAttachType = GMM_WAIT_NULL_ATTACH;
            }

            ucRst = GMM_FALSE;
        }
        else if ((WUEPS_PID_WRR == pNasMsgHeader->ulSenderPid)
            && (RRMM_EST_CNF != pNasMsgHeader->ulMsgName)
            && (RRMM_REL_IND != pNasMsgHeader->ulMsgName))
        {
            ucRst = GMM_FALSE;
        }
        else
        {
        }
    }

    return ucRst;
}

/***********************************************************************
 *  MODULE   : Gmm_MsgDistribute_Rat_Handling
 *  FUNCTION : Gmm_MsgDistribute函数降复杂度: 不同接入技术下消息的处理
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1.  欧阳飞   2009.06.11  新版作成
 ************************************************************************/
VOS_UINT8 Gmm_MsgDistribute_Rat_Handling(
                       VOS_VOID *pRcvMsg                                        /* 接收消息使用的头地址定义                 */
                       )
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* 定义MSG_HEADER_STRU类型指针              */
    VOS_UINT8            ucRst = GMM_TRUE;

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                                 /* 得到消息头                               */

    if (GMM_TRUE == GMM_IsCasGsmMode())
    {/* 2G网络模式 */
        /* 不处理WRRC消息和SMS消息 */
        if (WUEPS_PID_SMS == pNasMsgHeader->ulSenderPid)
        {
            ucRst = GMM_FALSE;
        }
        else if (WUEPS_PID_WRR == pNasMsgHeader->ulSenderPid)
        {
            if ((RRMM_EST_CNF != pNasMsgHeader->ulMsgName)
                && (RRMM_REL_IND != pNasMsgHeader->ulMsgName)
                && (RRMM_INTER_RAT_HANDOVER_INFO_CNF != pNasMsgHeader->ulMsgName))
            {
                ucRst = GMM_FALSE;
            }
        }
        else
        {
        }
    }
    else
    {/* 3G网络模式 */
        /* 不处理GAS消息和LLC消息 */
        if (UEPS_PID_LL == pNasMsgHeader->ulSenderPid)
        {
            ucRst = GMM_FALSE;
        }
    }

    return ucRst;
}

/***********************************************************************
 *  MODULE   : Gmm_MsgDistribute_From_USIM
 *  FUNCTION : Gmm_MsgDistribute函数降复杂度: USIM消息的处理
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1.  欧阳飞   2009.06.11  新版作成
 ************************************************************************/
VOS_VOID Gmm_MsgDistribute_From_USIM(
                       VOS_VOID *pRcvMsg                                        /* 接收消息使用的头地址定义                 */
                       )
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* 定义MSG_HEADER_STRU类型指针              */

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                                 /* 得到消息头                               */

    switch (pNasMsgHeader->ulMsgName)
    {
    case USIMM_AUTHENTICATION_CNF:
        Gmm_RcvAgentUsimAuthenticationCnf(pRcvMsg);                         /* AGENT_USIM_AUTHENTICATION_CNF接收处理    */
        break;
    default :
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_MsgDistribute:INFO: The Msg from USIM is ignored");
        break;
    }

    return;
}

/***********************************************************************
 *  MODULE   : Gmm_MsgDistribute_From_RRCF
 *  FUNCTION : Gmm_MsgDistribute函数降复杂度: RRCF消息的处理
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1.  欧阳飞   2009.06.11  新版作成
 ************************************************************************/
VOS_VOID Gmm_MsgDistribute_From_RRCF(
    VOS_VOID                            *pRcvMsg
                       )
{
    MSG_HEADER_STRU     *pNasMsgHeader;

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;

    switch (pNasMsgHeader->ulMsgName)
    {
    case RRMM_PAGING_IND:
        Gmm_RcvRrmmPagingInd(pRcvMsg);
        break;
    case RRMM_EST_CNF:
        Gmm_RcvRrmmEstCnf(pRcvMsg);
        break;
    case RRMM_DATA_IND:
        Gmm_RcvRrmmDataInd(pRcvMsg);
        break;
    case RRMM_REL_IND:
        Gmm_RcvRrmmRelInd(pRcvMsg);
        break;
    case RRMM_SECURITY_IND:
        Gmm_RcvRrmmSecurityInd(pRcvMsg);
        break;
    case RRMM_INTER_RAT_HANDOVER_INFO_CNF:
        NAS_GMM_RcvInterRatHandoverInfoCnf(pRcvMsg);
        break;
    default :
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_MsgDistribute:INFO: The Msg from RRC is ignored");
        break;
    }

    return;
}

/***********************************************************************
 *  MODULE   : Gmm_MsgDistribute_From_RABM
 *  FUNCTION : Gmm_MsgDistribute函数降复杂度: RABM消息的处理
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1.  欧阳飞   2009.06.11  新版作成
     2.日    期   : 2015年7月9日
       作    者   : z00161729
       修改内容   : DTS2015071505434:rau或attach请求不带follow on，网络回复attach accept或rau accept中携带follow on proceed标识，gmm需要
                增加判断如果ps rab存在或存在rabm重建或sm业务请求或cds存在缓存数据则不启动T3340，否则启动t3340开启网络防呆功能
 ************************************************************************/
VOS_VOID Gmm_MsgDistribute_From_RABM(
                       VOS_VOID *pRcvMsg                                        /* 接收消息使用的头地址定义                 */
                       )
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* 定义MSG_HEADER_STRU类型指针              */

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                                 /* 得到消息头                               */

    switch (pNasMsgHeader->ulMsgName)
    {
    case ID_RABM_GMM_REESTABLISH_REQ:
        Gmm_RcvRabmReestablishReq(pRcvMsg);                                 /* GMMRABM_REESTABLISH_REQ接收处理          */
        break;
    case ID_RABM_GMM_ROUTING_AREA_UPDATE_RSP:
        NAS_GMM_RcvGmmRabmRoutingAreaUpdateRsp(pRcvMsg);
        break;
    case ID_RABM_GMM_RAB_REL_IND:
        Gmm_RcvRabRelInd();                                                 /* RAB释放指示接收处理                      */
        break;

    case ID_RABM_GMM_RAB_SETUP_IND:
        NAS_GMM_RcvRabmRabSetupInd((GMMRABM_RAB_SETUP_IND_STRU *)pRcvMsg);
        break;

    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_MsgDistribute:INFO: The Msg from RABM is ignored");
        break;
    }

    return;
}

/***********************************************************************
 *  MODULE   : Gmm_MsgDistribute_From_MMC
 *  FUNCTION : Gmm_MsgDistribute函数降复杂度: MMC消息的处理
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1.  欧阳飞   2009.06.11  新版作成
     2. 日    期   : 2011年10月27日
        作    者   : s46746
        修改内容   : V7R1 PhaseIII,支持L模联合注册
     3. 日    期   : 2011年12月29日
        作    者   : l00130025
        修改内容   : DTS2011082201679/DTS2011121504358,切换模式，回退后W/G下注册状态没有与NAS同步
     4. 日    期   : 2012年02月29日
        作    者   : l00130025
        修改内容   : DTS2012022206186:不发起RAU,而注册成功时，需要同步注册状态给AS
     5. 日    期   : 2012年03月02日
        作    者   : l00130025
        修改内容   : DTS2012022102014:L->G->L->G后，没有重新分配TLLI,导致G下RAU被网侧ImplicityDetached
      6.日    期   : 2012年3月17日
        作    者   : w00176964
        修改内容   : DTS2012031308021:[GCF测试]L2U重选,携带RAU request的上行消息
                     中的RAU参数以及PTMSI类型错误。
     7. 日    期   : 2012年2月15日
        作    者   : w00166186
        修改内容   : CSFB&PPAC&ETWS&ISR 开发
     8. 日    期   : 2012年3月20日
        作    者   : z00161729
        修改内容   : ISR 开发
     9. 日    期   : 2012年10月16日
        作    者   : z00161729
        修改内容   : DTS2012101503609,网络模式II，L异系统到G,rai未改变isr未激活不做rau，
                     原因第一条系统消息缓存不处理将gstGmmSuspendCtrl.ucPreRat改为g，lau结束gprs
                     resume后收到系统消息已判断不出是异系统，rai未改变认为无需rau
    10. 日    期   : 2015年2月5日
        作    者   : s00217060
        修改内容   : VOLTE SWITCH修改
 ************************************************************************/
VOS_VOID Gmm_MsgDistribute_From_MMC(
    VOS_VOID                            *pRcvMsg                                /* 接收消息使用的头地址定义                 */
)
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* 定义MSG_HEADER_STRU类型指针              */

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                                 /* 得到消息头                               */

    switch (pNasMsgHeader->ulMsgName)
    {
    case MMCGMM_SYS_INFO_IND:
        Gmm_RcvMmcSysInfoInd(pRcvMsg);                                      /* MMCGMM_SYS_INFO_IND接收处理              */

        NAS_GMM_SyncNasInfoChange_RegisteredStatus(RRC_NAS_MASK_SYNC_WRR);


        /* 如果此时GMM需要获取LMM的安全上下文,可能会启动定时器,此时这个标记应该暂时不清除
           待收到LMM的安全上下文的回复或者定时器超时后再清除 */
        if ( VOS_FALSE == NAS_GMM_GetLmmSecInfoFlg())
        {
            /* 需要获取安全上下文时,挂起前的接入技术延迟更新 */
            gstGmmSuspendCtrl.ucPreRat = NAS_MML_NET_RAT_TYPE_WCDMA;

            g_GmmInterRatCellReselect = 0;
        }


        break;
    case MMCGMM_COVERAGE_LOST_IND:
        Gmm_RcvMmcCoverageLostInd();                                        /* MMCGMM_COVERAGE_LOST_IND接收处理         */
        break;
    case MMCGMM_POWER_OFF_REQ:
        Gmm_RcvMmcPowerOffReq(pRcvMsg);                                     /* MMCGMM_POWER_OFF_REQ接收处理             */
        break;

    case MMCGMM_PLMN_SEARCH_INITIATED:
        Gmm_RcvMmcPlmnSearchInitiated();                                    /* MMCGMM_PLMN_SEARCH_INITIATED接收处理     */
        break;
    case MMCGMM_START_REQ:
        Gmm_RcvMmcStartReq();                                               /* MMCGMM_START_REQ接收处理                 */
        break;
    case MMCGMM_PLMN_USER_SEL_REQ:
        Gmm_RcvMmcPlmnUserSelReq();                                         /* MMCGMM_PLMN_USER_SEL_REQ接收处理         */
        break;
    case MMCGMM_DETACH_REQ:
        Gmm_RcvMmcDetachReq(pRcvMsg);                                       /* MMCGMM_DETACH_REQ接收处理                */
        break;
    case MMCGMM_MODE_CHANGE_REQ:
        Gmm_RcvMmcGmmModeChangeReq(pRcvMsg);                                /* MMCGMM_MODE_CHANGE_REQ接收处理           */
        break;
    case MMCGMM_ATTACH_REQ:
        Gmm_RcvMmcGmmAttachReq(pRcvMsg);                                    /* MMCGMM_ATTACH_REQ接收处理                */
        break;
    case MMCGMM_GSM_SYS_INFO_IND:
        GMM_RcvGasSysInfoInd(pRcvMsg);



        NAS_GMM_SyncNasInfoChange_RegisteredStatus(RRC_NAS_MASK_SYNC_GAS);


        break;
    case MMCGMM_SUSPEND_IND:
        GMM_RcvMmcSuspendInd(pRcvMsg);
        break;
    case MMCGMM_RESUME_IND:
        GMM_RcvMmcResumeInd(pRcvMsg);
        break;
    case MMCGMM_REL_REQ:
        GMM_RcvMmcRelReq(pRcvMsg);
        break;
    case MMCGMM_W_AC_INFO_CHANGE_IND:
        NAS_GMM_RcvMmcWasAcInfoChgInd((NAS_MSG_STRU *)pRcvMsg);
        break;
#if (FEATURE_ON == FEATURE_LTE)
    case MMCGMM_LTE_SYS_INFO_IND:
        NAS_GMM_RcvMmcLteSysInfoInd((MMC_GMM_LTE_SYS_INFO_IND_STRU*)pRcvMsg);
        gstGmmSuspendCtrl.ucPreRat = NAS_MML_NET_RAT_TYPE_LTE;
        break;

    case MMCGMM_LMM_ATTACH_IND:
        NAS_GMM_RcvLmmAttachResult((struct MsgCB*)pRcvMsg);
        break;

    case MMCGMM_LMM_TAU_RESULT_IND:
        NAS_GMM_RcvLmmTauResult((struct MsgCB*)pRcvMsg);
        break;

    case MMCGMM_LMM_MT_DETACH_IND:
        NAS_GMM_RcvLmmMtDetachInd((struct MsgCB*)pRcvMsg);
        break;

    case MMCGMM_LMM_SERVICE_RESULT_IND:
        NAS_GMM_RcvLmmServiceResult((struct MsgCB*)pRcvMsg);
        break;

    case MMCGMM_LMM_MO_DETACH_IND:
        NAS_GMM_RcvLmmMoDetachInd((struct MsgCB*)pRcvMsg);
        break;

    case MMCGMM_LMM_LOCAL_DETACH_IND:
        NAS_GMM_RcvLmmLocalDetachInd((struct MsgCB*)pRcvMsg);
        break;


    case MMCGMM_LMM_STATUS_IND:
        NAS_GMM_RcvMmcLmmStatusInd((MMCGMM_LMM_STATUS_IND_STRU*)pRcvMsg);
        break;

    case MMCGMM_LMM_TIMER_STATE_NOTIFY:
        NAS_GMM_RcvLmmTimerStateNotify((struct MsgCB*)pRcvMsg);
        break;

    case MMCGMM_EMERGENCY_NUM_LIST_IND:
        NAS_GMM_RcvMmcEmergencyNumList((struct MsgCB*)pRcvMsg);
        break;

    case MMCGMM_VOICE_DOMAIN_CHANGE_NOTIFY:
        NAS_GMM_RcvMmcVoiceDomainChangeNotify((struct MsgCB*)pRcvMsg);
        break;
#endif

    default :
        NAS_INFO_LOG1(WUEPS_PID_GMM, "Gmm_MsgDistribute: The Msg from MMC is ignored, MsgId: ", pNasMsgHeader->ulMsgName);
        break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_RcvSmAbortReq
 功能描述  : 消息GMMSM_ABORT_REQ的接收处理
 输入参数  : 包含所有PDP状态的消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年12月20日
    作    者   : h44270
    修改内容   : 新生成函数，PS Project，增加对于Abort消息的处理
******************************************************************************/
VOS_VOID NAS_GMM_RcvSmAbortReq(
    VOS_VOID                            *pRcvMsg)
{
    NAS_GMM_ClearBufferedSmDataReq();
}

/***********************************************************************
 *  MODULE   : Gmm_MsgDistribute_From_SM
 *  FUNCTION : Gmm_MsgDistribute函数降复杂度: SM消息的处理
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
 1.  欧阳飞   2009.06.11  新版作成
 2.日    期   : 2011年9月14日
   作    者   : h44270
   修改内容   : modify for PS Project,增加对于Abort消息的处理
 ************************************************************************/
VOS_VOID Gmm_MsgDistribute_From_SM(
                       VOS_VOID *pRcvMsg                                        /* 接收消息使用的头地址定义                 */
                       )
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* 定义MSG_HEADER_STRU类型指针              */

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                                 /* 得到消息头                               */

    switch (pNasMsgHeader->ulMsgName)
    {
    case GMMSM_ESTABLISH_REQ:
        Gmm_RcvSmEstablishReq(pRcvMsg);                                     /* GMMSM_ESTABLISH_REQ接收处理              */
        break;
    case GMMSM_DATA_REQ:
        Gmm_RcvSmDataReq(pRcvMsg);                                          /* GMMSM_DATA_REQ接收处理                   */
        break;
    case GMMSM_PDP_STATUS_IND:
        Gmm_RcvSmPdpStatusInd(pRcvMsg);                                     /* GMMSM_PDP_STATUS_IND接收处理             */
        break;
    case GMMSM_PDP_DEACTIVATED_IND:
        NAS_GMM_RcvSmPdpDeactivatedInd(pRcvMsg);
        break;

    case GMMSM_ABORT_REQ:
        NAS_GMM_RcvSmAbortReq(pRcvMsg);
        break;

    case GMMSM_PDP_MODIFY_IND:
        NAS_GMM_RcvSmPdpModifyInd(pRcvMsg);
        break;
    default :
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_MsgDistribute:INFO: The Msg from SM is ignored");
        break;
    }

    return;
}

/***********************************************************************
 *  MODULE   : Gmm_MsgDistribute_From_SMS
 *  FUNCTION : Gmm_MsgDistribute函数降复杂度: SMS消息的处理
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1.  欧阳飞   2009.06.11  新版作成
 ************************************************************************/
VOS_VOID Gmm_MsgDistribute_From_SMS(
                       VOS_VOID *pRcvMsg                                        /* 接收消息使用的头地址定义                 */
                       )
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* 定义MSG_HEADER_STRU类型指针              */

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                                 /* 得到消息头                               */

    switch (pNasMsgHeader->ulMsgName)
    {
    case PMMSMS_EST_REQ:
        Gmm_RcvSmsEstReq(pRcvMsg);                                          /* PMMSMS_EST_REQ接收处理                   */
        break;
    case PMMSMS_UNITDATA_REQ:
        Gmm_RcvSmsUnitdataReq(pRcvMsg);                                     /* GMMSM_DATA_REQ接收处理                   */
        break;
    default :
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_MsgDistribute:INFO: The Msg from SMS is ignored");
        break;
    }

    return;
}

/***********************************************************************
 *  MODULE   : Gmm_MsgDistribute_From_LL
 *  FUNCTION : Gmm_MsgDistribute函数降复杂度: LL消息的处理
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
    1.欧阳飞   2009.06.11  新版作成
    2.日    期   : 2015年4月7日
      作    者   : wx270776
      修改内容   : 问题单号:DTS2015040701865，天际通关机优化，增加对ID_LL_UNITDATA_CNF的消息处理
 ************************************************************************/
VOS_VOID Gmm_MsgDistribute_From_LL(
                       VOS_VOID *pRcvMsg                                        /* 接收消息使用的头地址定义                 */
                       )
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* 定义MSG_HEADER_STRU类型指针              */

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                                 /* 得到消息头                               */

    switch (pNasMsgHeader->ulMsgName)
    {
    case ID_LL_GMM_STATUS_IND:                                                  /* 上报LLC状态信息 */
        GMM_CasCellS0E45(pRcvMsg);
        break;
    case ID_LL_UNITDATA_IND:                                                    /* 直传数据请求 */
        GMM_RcvLlcDataInd(pRcvMsg);
        break;

    case ID_LL_UNITDATA_CNF:                                                    /* 直传数据请求 */
        NAS_GMM_RcvLlcDataCnf(pRcvMsg);
        break;

    case ID_LL_DATA_INFORM :
        Gmm_RcvLLCInform(pRcvMsg);
        break;
    default :
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_MsgDistribute:INFO: The Msg from LLC is ignored");
        break;
    }

    return;
}

/***********************************************************************
 *  MODULE   : Gmm_MsgDistribute_From_TC
 *  FUNCTION : Gmm_MsgDistribute函数降复杂度: TC消息的处理
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1.  欧阳飞   2009.06.11  新版作成
 ************************************************************************/
VOS_VOID Gmm_MsgDistribute_From_TC(
                       VOS_VOID *pRcvMsg                                        /* 接收消息使用的头地址定义                 */
                       )
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* 定义MSG_HEADER_STRU类型指针              */

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                                 /* 得到消息头                               */

    switch (pNasMsgHeader->ulMsgName)
    {
    case TCGMM_DATA_REQ:
        Gmm_RcvTcDataReq(pRcvMsg);                                          /* TCGMM_DATA_REQ接收处理                   */
        break;
    case TCGMM_TEST_REQ:
        Gmm_RcvTcTestReq(pRcvMsg);                                          /* TCGMM_TEST_REQ接收处理                   */
        break;
    default :
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_MsgDistribute:INFO: The Msg from TC is ignored");
        break;
    }

    return;
}

/***********************************************************************
 *  MODULE   : Gmm_MsgDistribute_From_GAS
 *  FUNCTION : Gmm_MsgDistribute函数降复杂度: GAS消息的处理
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
 1.欧阳飞   2009.06.11  新版作成
 2.日    期    : 2009年9月03日
   作    者    : l65478
   修改内容    : created AT2D14239,detach完成后,再次发起ATTATCH REQ时,GAS使用旧的TLLI建立的TBF发送数据,没有及时使用新的TLLI,导致MS和仪器侧维护的TLLI不一致,从而导致GAS因为TLLI不匹配丢弃了建立下行TBF的指派命令,最终导致用例失败
 3.日    期   : 2011年7月12日
   作    者   : h44270
   修改内容   : V7R1 PhaseII阶段调整，增加消息原语，用于知道是否G下GPRS接入成功
************************************************************************/
VOS_VOID Gmm_MsgDistribute_From_GAS(
                       VOS_VOID *pRcvMsg                                        /* 接收消息使用的头地址定义                 */
                       )
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* 定义MSG_HEADER_STRU类型指针              */

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                                 /* 得到消息头                               */

    switch (pNasMsgHeader->ulMsgName)
    {
        case GRRMM_PAGING_IND:                                                  /* GAS寻呼请求 */
            GMM_RcvGasPagingInd(pRcvMsg);
            break;
        case RRMM_GPRS_SUSPENSION_IND:                                          /* GAS GPRS挂起指示 */
            GMM_RcvGasSuspensionInd(pRcvMsg);
            break;
        case RRMM_GPRS_RESUME_IND:                                              /* GAS GPRS恢复指示 */
            GMM_RcvGasGprsResumeInd(pRcvMsg);
            break;
        case RRMM_CELL_RESELECT_IND:                                              /* GAS GPRS恢复指示 */
            GMM_RcvCellReselectInd(pRcvMsg);
            break;
        case GRRGMM_TBF_REL_IND:                                              /* GAS GPRS恢复指示 */
            GMM_RcvGasTbfRleInd(pRcvMsg);
            break;

        case GRRMM_MS_RADIO_ACCESS_CAPABILITIES_IND:                                              /* GAS GPRS恢复指示 */
            GMM_RcvGasRadioAccessCapa(pRcvMsg);
            break;

        /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-22, begin */
        case RRMM_CLASSMARK_CHANGE_IND:
            GMM_RcvGasClassMarkChangeInd(pRcvMsg);
            break;
        /* Added by w00176964 for VoLTE_PhaseII 项目, 2013-10-22, end */

        case GRRMM_MS_RADIO_ACCESS_CAPABILITIES_TDS_IND:                                              /* GAS GPRS恢复指示 */
            GMM_RcvGasTdsRadioAccessCapa(pRcvMsg);
            break;

        case GRRGMM_GPRS_ACCESS_RESULT_IND:
            NAS_GMM_RcvGprsAccessResultInd(pRcvMsg);
            break;

        default :
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_MsgDistribute:INFO: The Msg from GAS is ignored");
            break;
    }

    return;
}

#if   (FEATURE_ON == FEATURE_LTE)

/*****************************************************************************
 函 数 名  : NAS_GMM_RcvLmmReselSecInfoCnf
 功能描述  : 收到LMM的重选安全参数处理，解析相应参数
             并重新调用被终止的SYS_INFO消息处理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月11日
    作    者   : luokaihui /00167671
    修改内容   : 新生成函数
  2.日    期   : 2011年12月2日
    作    者   : s46746
    修改内容   : 从L异系统改变到GU后，没有指派加密密钥到GU接入层
  3.日    期   : 2012年3月17日
    作    者   : w00176964
    修改内容   : DTS2012031308021:[GCF测试]L2U重选,携带RAU request的上行消息
                 中的RAU参数以及PTMSI类型错误。
  4.日    期   : 2012年3月21日
    作    者   : z40661
    修改内容   : DTS2011110201060:L重选到W，被网络拒绝#9后携带的PTMSI不正确
  5.日    期   : 2014年4月24日
    作    者   : s00217060
    修改内容   : 从L模获取映射的安全上下文之后，通知GU模
  6.日    期   : 2014年10月30日
    作    者   : s00217060
    修改内容   : 从L模获取安全上下文后，如果当前状态不是ATTACH_INIT或RAU_INIT，不发attach/rau req
*****************************************************************************/
VOS_VOID NAS_GMM_RcvLmmReselSecInfoCnf(
    VOS_VOID                             *pRcvMsg
)
{
    LMM_GMM_RESEL_SECU_INFO_CNF_STRU     *pstMsg;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8       enCurrRat;

    pstMsg = (LMM_GMM_RESEL_SECU_INFO_CNF_STRU *)pRcvMsg;

    Gmm_TimerStop(GMM_TIMER_WAIT_GET_RESEL_SECU_INFO_CNF);

    NAS_GMM_GetGUSecContextFromEpsSecContextInReselect((struct MsgCB *)pstMsg);

    enCurrRat   = NAS_MML_GetCurrNetRatType();

    /* 从L模获取映射的安全上下文之后，通知GU模 */
    if (NAS_MML_NET_RAT_TYPE_WCDMA  == enCurrRat)
    {
        NAS_GMM_SndWasInfoChangeReq(RRC_NAS_MASK_MAPPED_SECURITY_KEY);
    }
    else if (NAS_MML_NET_RAT_TYPE_GSM  == enCurrRat)
    {
        NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_MAPPED_SECURITY_KEY);
    }
    else
    {
    }

    /* 从L模获取安全上下文后，如果当前状态不是ATTACH_INIT或RAU_INIT，不发attach/rau req
       对应场景为:LTE限制服务，启available timer,重选到GU过程中available timer超时触发搜网，
       GMM状态更新为PLMN_SRCH,搜网与RAU流程冲突 */
    if ( (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
      || (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState) )
    {
        if (NAS_GMM_SPEC_PROC_RAU == NAS_GMM_GetSpecProcNeedSecInfo())
        {
            Gmm_SndRoutingAreaUpdateReq(NAS_GMM_GetRauUpdateType());
        }
        else
        {
            Gmm_SndAttachReq();
        }

        /* 需要获取安全上下文时,挂起前的接入技术延迟更新 */
        gstGmmSuspendCtrl.ucPreRat = enCurrRat;
    }

    NAS_GMM_SetLmmSecInfoFlg(VOS_FALSE);

    g_GmmInterRatCellReselect = 0;


    gstGmmSuspendCtrl.ucGetLteSecContext = VOS_TRUE;

    NAS_GMM_SetSpecProcNeedSecInfo(NAS_GMM_SPEC_PROC_BUTT);

}
/*****************************************************************************
 函 数 名  : NAS_GMM_RcvLmmHoSecInfoCnf
 功能描述  : 收到LMM的重选安全参数处理，解析相应参数
             并重新调用被终止的SYS_INFO消息处理函数
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月11日
    作    者   : luokaihui /00167671
    修改内容   : 新生成函数

  2.日    期   : 2011年7月20日
    作    者   : w00176964
    修改内容   : V7R1 Phase II调整:挂起过程中获取到L的安全上下文后，向MMC回复挂起结果
  3.日    期   : 2011年12月2日
    作    者   : s46746
    修改内容   : 从L异系统改变到GU后，没有指派加密密钥到GU接入层

*****************************************************************************/
VOS_VOID NAS_GMM_RcvLmmHoSecInfoCnf(
    VOS_VOID                            *pRcvMsg
)
{
    LMM_GMM_HO_SECU_INFO_CNF_STRU       *pstMsg;

    pstMsg = (LMM_GMM_HO_SECU_INFO_CNF_STRU *)pRcvMsg;

    Gmm_TimerStop(GMM_TIMER_WAIT_GET_HO_SECU_INFO_CNF);

    NAS_GMM_GetGUSecContextFromEpsSecContextInHandOver((struct MsgCB *)pstMsg);

    /* 如果此时在GMM的挂起状态，而且挂起发起方为LTE，则向MMC回复挂起回复 */
    if ( (NAS_MML_NET_RAT_TYPE_LTE      == NAS_MML_GetCurrNetRatType())
      && (GMM_SUSPENDED_NORMAL_SERVICE  == g_GmmGlobalCtrl.ucState))
    {
        Gmm_TimerStart(GMM_TIMER_SUSPENDED);

        GMM_SndMmcSuspendRsp();
    }
}

/* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-12, begin */
/* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-12, end */

/*****************************************************************************
 函 数 名  : Gmm_MsgDistribute_From_Lmm
 功能描述  :
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年3月14日
    作    者   : luokaihui /00167671
    修改内容   : 新生成函数
  2.日    期   : 2013年7月12日
    作    者   : y00245242
    修改内容   : 增加处理LTE网络业务能力参数上报
*****************************************************************************/
VOS_VOID Gmm_MsgDistribute_From_Lmm(
    VOS_VOID *pRcvMsg
)
{
    MSG_HEADER_STRU     *pNasMsgHeader;

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;

    switch (pNasMsgHeader->ulMsgName)
    {
        case ID_LMM_GMM_RESEL_SECU_INFO_CNF:
            NAS_GMM_RcvLmmReselSecInfoCnf(pRcvMsg);
            break;

        case ID_LMM_GMM_HO_SECU_INFO_CNF:
            NAS_GMM_RcvLmmHoSecInfoCnf(pRcvMsg);
            break;

        /* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-12, begin */
        /* Added by y00245242 for VoLTE_PhaseI  项目, 2013-7-12, end */
        default :
            break;
    }

    return;
}

#endif

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
/*****************************************************************************
 函 数 名  : NAS_GMM_ProcMtcRrcAreaLostInd
 功能描述  : 对于来自Mtc的rrc假丢网消息
 输入参数  : pstRcvMsg - 来自Mtc的消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月8日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2013年12月8日
   作    者   : z00161729
   修改内容   : dts2014010202583
*****************************************************************************/
VOS_VOID NAS_GMM_ProcMtcRrcAreaLostInd(VOS_VOID  *pstRcvMsg)
{

    /* svlte特性开启时ps从modem0迁移到modem1，设置全局变量，后续gmm收到
       detach ps请求直接进行本地detach以减少时间 */
    NAS_MML_SetPsLocalDetachFlag(VOS_TRUE);

    return;
}


/*****************************************************************************
 函 数 名  : NAS_GMM_ProcMtcMsg
 功能描述  : 对于来自Mtc消息的分发处理
 输入参数  : pstRcvMsg - 来自Mtc的消息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年12月8日
   作    者   : z00161729
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_GMM_ProcMtcMsg(VOS_VOID  *pstRcvMsg)
{
    MSG_HEADER_STRU                    *pstNasMsgHeader;

    pstNasMsgHeader = (MSG_HEADER_STRU *)pstRcvMsg;

    switch (pstNasMsgHeader->ulMsgName)
    {
        case ID_MTC_GMM_RRC_AREA_LOST_IND:
            NAS_GMM_ProcMtcRrcAreaLostInd(pstRcvMsg);
            break;

        default :
            NAS_INFO_LOG1(WUEPS_PID_GMM, "NAS_GMM_ProcMtcMsg: The Msg from MTC is ignored, MsgId: ", pstNasMsgHeader->ulMsgName);
            break;
    }

    return;
}

#endif



/*****************************************************************************
 函 数 名  : Gmm_MsgDistribute_From_MM
 功能描述  : 对于来自MM消息的分发处理
 输入参数  : pstRcvMsg:来自MM的消息
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月22日
   作    者   : h44270
   修改内容   : 新生成函数
 2.日    期   : 2015年1月5日
   作    者   : z00161729
   修改内容   : AT&T 支持DAM特性修改
*****************************************************************************/
VOS_VOID Gmm_MsgDistribute_From_MM(
    VOS_VOID                           *pstRcvMsg                                /* 接收消息使用的头地址定义                 */
)
{
    MSG_HEADER_STRU                    *pstNasMsgHeader;                                         /* 定义MSG_HEADER_STRU类型指针              */

    pstNasMsgHeader = (MSG_HEADER_STRU *)pstRcvMsg;                                 /* 得到消息头                               */

    switch (pstNasMsgHeader->ulMsgName)
    {
        case MMGMM_LU_RESULT_IND:
            NAS_GMM_ProcMmLuResult(pstRcvMsg);
            break;

        case MMGMM_CS_CONNECT_IND:
            NAS_GMM_RcvMmCsConnectInd(pstRcvMsg);                               /* MMGMM_CS_CONNECT_IND接收处理            */
            break;
        case MMGMM_CM_SERVICE_REJECT_IND:
            NAS_GMM_RcvMmCmServiceRejectInd(pstRcvMsg);                         /* MMGMM_CM_SERVICE_REJECT_IND接收处理     */
            break;

        case MMGMM_AUTHENTICATON_FAILURE_IND:
            NAS_GMM_RcvMmAuthenticationFailureInd();                            /* MMCGMM_AUTHENTICATON_FAILURE_IND接收处理 */
            break;

        case MMGMM_REGISTER_INITIATION:
            Gmm_RcvMmRegisterInitiation(pstRcvMsg);                              /* MMCGMM_REGISTER_INITIATION接收处理       */
            break;

        case MMGMM_CS_LOCAL_DETACH_IND:
            NAS_Gmm_RcvMmCsLocalDetachInd(pstRcvMsg);                           /* MMGMM_CS_LOCAL_DETACH_IND接收处理 */
            break;


        case MMGMM_T3211_TIMER_EXPIRED_NOTIFY:
            NAS_Gmm_RcvMmT3211ExpiredNotify(pstRcvMsg);
            break;

        default :
            NAS_INFO_LOG1(WUEPS_PID_GMM, "Gmm_MsgDistribute: The Msg from MMC is ignored, MsgId: ", pstNasMsgHeader->ulMsgName);
            break;
    }

    return;
}

/*******************************************************************************
  Module   : Gmm_MsgDistribute
  Function : GMM TASK消息分发处理
  Input    : VOS_VOID *pRcvMsg  接收消息使用的头地址定义
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
  1.  张志勇  2003.12.09  新规作成
  2. x51137   2006/4/21 A32D03244
  3. 日    期   : 2006年11月2日
     作    者   : sunxibo id:46746
     修改内容   : 根据问题单号：A32D06406
  4. 日    期   : 2007年01月04日
     作    者   : luojian id:60022475
     修改内容   : 根据问题单号：A32D06408
  5. 日    期   : 2007年03月20日
     作    者   : x51137
     修改内容   : A32D09192
  6. 日    期   : 2008年7月23日
     作    者   : luojian id:107747
     修改内容   : 根据问题单：AT2D04627/AT2D04237
  7.日    期   : 2009年01月15日
    作    者   : l00130025
    修改内容   : 问题单号:AT2D07018,LAU或RAU过程中搜网和SYSCFG设置,发起底层释放链接的操作
  8.日    期   : 2011年7月22日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  9.日    期   : 2013年12月8日
    作    者   : z00161729
    修改内容   : SVLTE优化G-TL ps切换性能修改
*******************************************************************************/
VOS_VOID Gmm_MsgDistribute(
    VOS_VOID                            *pRcvMsg                                /* 接收消息使用的头地址定义                 */
)
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* 定义MSG_HEADER_STRU类型指针              */
    VOS_UINT8            ucRst = GMM_TRUE;

    pNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                                 /* 得到消息头                               */
    if (WUEPS_PID_GMM != pNasMsgHeader->ulReceiverPid)
    {                                                                           /* ulDestTskId不是GMM                       */
        NAS_WARNING_LOG(WUEPS_PID_GMM, "Gmm_MsgDistribute: Receive PID is not GMM.");
        return;
    }

    if (GMM_TC_ACTIVE == g_GmmGlobalCtrl.ucState)
    {
        ucRst = Gmm_MsgDistribute_GMM_TC_ACTIVE(pRcvMsg);
        if(GMM_FALSE == ucRst)
        {
            return;
        }
    }

    if (GMM_NULL == g_GmmGlobalCtrl.ucState)
    {
        ucRst = Gmm_MsgDistribute_GMM_NULL(pRcvMsg);
        if(GMM_FALSE == ucRst)
        {
            return;
        }
    }

    ucRst = Gmm_MsgDistribute_SpecProc_Handling(pRcvMsg);
    if(GMM_FALSE == ucRst)
    {
        return;
    }

    ucRst = Gmm_MsgDistribute_Rat_Handling(pRcvMsg);
    if(GMM_FALSE == ucRst)
    {
        return;
    }

    switch (pNasMsgHeader->ulSenderPid)
    {                                                                           /* 根据message class分发消息                */
    case WUEPS_PID_USIM:                                                        /* AGENT发送给GMM                           */
        Gmm_MsgDistribute_From_USIM(pRcvMsg);
        break;

    case WUEPS_PID_WRR:                                                        /* RRC发送给GMM                             */
        Gmm_MsgDistribute_From_RRCF(pRcvMsg);
        break;

    case WUEPS_PID_RABM:                                                        /* RABM发送给GMM                            */
        Gmm_MsgDistribute_From_RABM(pRcvMsg);
        break;

    case WUEPS_PID_MMC:                                                         /* MMC发送给GMM                             */
        Gmm_MsgDistribute_From_MMC(pRcvMsg);
        break;

    case WUEPS_PID_MM:                                                         /* SMS发送给GMM                             */
        Gmm_MsgDistribute_From_MM(pRcvMsg);
        break;

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    case UEPS_PID_MTC:
        NAS_GMM_ProcMtcMsg(pRcvMsg);
        break;
#endif

    case WUEPS_PID_SM:                                                          /* SM发送给GMM                              */
        Gmm_MsgDistribute_From_SM(pRcvMsg);
        break;

    case WUEPS_PID_SMS:                                                         /* SMS发送给GMM                             */
        Gmm_MsgDistribute_From_SMS(pRcvMsg);
        break;

    case WUEPS_PID_TC:                                                        /* TC发送给GMM                              */
        Gmm_MsgDistribute_From_TC(pRcvMsg);
        break;

    case UEPS_PID_LL:                                                           /* LLC发送给GMM */
        Gmm_MsgDistribute_From_LL(pRcvMsg);
        break;

    case UEPS_PID_GAS:                                                          /* GRR发送给GMM */
        Gmm_MsgDistribute_From_GAS(pRcvMsg);
        break;

#if   (FEATURE_ON == FEATURE_LTE)
    case PS_PID_MM:                                                          /* GRR发送给GMM */
        Gmm_MsgDistribute_From_Lmm(pRcvMsg);
        break;
#endif

    default :
        NAS_WARNING_LOG1(WUEPS_PID_GMM, "Gmm_MsgDistribute: Receive Message from unexpected PID, PID : ", pNasMsgHeader->ulSenderPid);
        break;
    }

    return;
}

/*******************************************************************************
  Module   : Gmm_ComVariantInit
  Function : GMM TASK全局变量的初期化处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2003.12.10  新规作成
    2.日    期   : 2009年5月9日
      作    者   : l00130025
      修改内容   : 根据问题单号：AT2D11645/AT2D11797,关机，若detach的EST_REQ失败，Gmm会反复发起EST_REQ
    3.日    期   : 2009年7月23日
      作    者   : l65478
      修改内容   : 问题单号:AT2D13173,GMM在收到系统信息后，给MMC发送了NO SERVICE，导致MMC启动了搜网定时器
    4.日    期   : 2009年9月16日
      作    者   : l65478
      修改内容   : 问题单号:AT2D13861,RAU失败通知OM口的原因值错误 不应该是rr－connect fail
    5.日    期   : 2010年10月05日
      作    者   : o00132663
      修改内容   : DTS2010100500115，增加设置RAC初始值
    6.日    期   : 2011年10月11日
      作    者   : f00179208
      修改内容   : DTS2011101001459，【功耗】GSM模式下，网络广播系统消息13，
                   E5从专用态回到IDLE态，读取完整的系统消息与标杆不一致
    7.日    期   : 2012年8月10日
      作    者   : L00171473
      修改内容   : DTS2012082204471, TQE清理
    8.日    期   : 2012年8月15日
      作    者   : z00161729
      修改内容   : DCM定制需求和遗留问题修改
    9.日    期   : 2012年9月03日
      作    者   : w00176964
      修改内容   : GUTL PhaseII:增加TDS的RAC能力变量
   10.日    期   : 2012年9月25日
      作    者   : h00216089
      修改内容   : DTS2012090304976:调整，网侧Detach(re-attach not required)后，MM定时器超时发起LU，
                     LU结束后收到系统消息GMM不会再发起Attach
   11.日    期   : 2012年12月13日
      作    者   : L00171473
      修改内容   : DTS2012121802573, TQE清理
   12.日    期   : 2014年01月13日
      作    者   : l65478
      修改内容   : DTS2013102508485, 澳电PDP去激活后UE主动释放了RRC连接
   13.日    期   : 2014年6月17日
      作    者   : s00217060
      修改内容   : DTS2014061003286:3311定时器超时标志初始化
   14.日    期   : 2015年1月15日
      作    者   : z00161729
      修改内容   : AT&T 支持DAM特性修改
   15.日    期   : 2015年2月12日
      作    者   : s00217060
      修改内容   : VOLTE SWITCH修改
   16.日    期   : 2015年6月15日
      作    者   : z00161729
      修改内容   : 24008 23122 R11 CR升级项目修改
*******************************************************************************/
VOS_VOID Gmm_ComVariantInit(VOS_VOID)
{
    VOS_UINT8                           ucLen;
    VOS_UINT16                          usNonDrxTimerLen;
    VOS_UINT8                           aucDefaultRac[] = {0x15, 0x17, 0x73, 0x43, 0x2b, 0x25, 0x96, 0x62, 0x00,
                                                           0x42, 0x68, 0x8b, 0x19, 0x88, 0x01, 0x0b, 0xa2,
                                                           0x8c, 0x66, 0x20, 0x04, 0x00};
    NV_NAS_GMM_REL_CONN_AFTER_PDP_DEACT_STRU    stRelConnAfterPdpDeact;
    VOS_UINT32                                  ulResult;
    VOS_UINT32                                  ulLength;

    NAS_MML_PLMN_WITH_RAT_STRU                  stPlmnWithRat;

    stPlmnWithRat.stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
    stPlmnWithRat.stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
    stPlmnWithRat.enRat          = NAS_MML_NET_RAT_TYPE_BUTT;


    usNonDrxTimerLen = 0;

    /* 将GMM的全局变量初期化为0 */
    Gmm_MemSet(&g_GmmGlobalCtrl, 0, sizeof(GMM_GLOBAL_CTRL_STRU));
    Gmm_MemSet(&g_GmmReqCnfMng,  0, sizeof(GMM_REQ_CNF_MNG_STRU));
    Gmm_MemSet(&g_GmmAttachCtrl, 0, sizeof(GMM_ATTACH_CTRL_STRU));
    Gmm_MemSet(&g_GmmRauCtrl,    0, sizeof(GMM_RAU_CTRL_STRU));
    Gmm_MemSet(&g_GmmDetachCtrl, 0, sizeof(GMM_DETACH_CTRL_STRU));
    Gmm_MemSet(&g_GmmAuthenCtrl, 0, sizeof(GMM_AUTHEN_CTRL_STRU));
    Gmm_MemSet(&g_GmmServiceCtrl,0, sizeof(GMM_SR_CTRL_STRU));
    Gmm_MemSet(&g_MmSubLyrShare.GmmShare, 0, sizeof(GMM_SHARE_STRU));
    Gmm_MemSet(&g_GmmInterRatInfoCtrl, 0, sizeof(GMM_INTER_RAT_HANDOVER_INFO_CTRL_STRU));

    g_GmmTimerMng.ulTimerRunMask             = 0;
    g_GmmTimerMng.ulTimerSusMask             = 0;
    g_GmmTimerMng.ulTimerValMask             = 0;
    g_GmmTimerMng.ulTimerRunMaskEx           = 0;
    g_GmmTimerMng.ulTimerSusMaskEx           = 0;
    g_GmmTimerMng.ulTimerValMaskEx           = 0;    
    g_MmSubLyrShare.GmmShare.ucPsSpecificFlg = GMM_SPECIFIC_OFF;

    GMM_InitCasGlobalVariable();

    NAS_GMM_InitRaiInfo(NAS_GMM_GetAttemptUpdateRaiInfo());

    NAS_GMM_SetAllocT3302ValuePlmnWithRat(&stPlmnWithRat);

    g_GmmGlobalCtrl.UeInfo.ucSupportInfoFlg  = GMM_SUPPORT_INFORMATION_MSG;

    /* Modified by t00212959 for DCM定制需求和遗留问题, 2012-8-14, begin */

    /* 从GAS维护的NV项中读取nonDRXTimer值 */
    if(NV_OK != NV_Read (en_NV_Item_GPRS_Non_Drx_Timer_Length, &usNonDrxTimerLen, sizeof(VOS_UINT16)))
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "Gmm_ComVariantInit():en_NV_Item_GPRS_Non_Drx_Timer_Length Error");
        usNonDrxTimerLen = 0;
    }

    NAS_MML_SetNonDrxTimer((VOS_UINT8)usNonDrxTimerLen);



    g_GmmGlobalCtrl.ucRelConnAfterPdpDeact = VOS_FALSE;
    PS_MEM_SET(&stRelConnAfterPdpDeact, 0x00, sizeof(NV_NAS_GMM_REL_CONN_AFTER_PDP_DEACT_STRU));

    ulLength = 0;
    (VOS_VOID)NV_GetLength(en_NV_Item_NAS_GMM_REL_CONN_AFTER_PDP_DEACT, &ulLength);
    if (ulLength > sizeof(stRelConnAfterPdpDeact))
    {
        return;
    }
    ulResult = NV_Read(en_NV_Item_NAS_GMM_REL_CONN_AFTER_PDP_DEACT,
                       &stRelConnAfterPdpDeact,
                       ulLength);

    if (NV_OK == ulResult)
    {
        g_GmmGlobalCtrl.ucRelConnAfterPdpDeact = stRelConnAfterPdpDeact.ucRelFlg;
    }

    /*这里将记录上次attach或RAU是否携带Drx参数的变量enLatestAttachOrRauContainDrx 初始化*/
    g_GmmGlobalCtrl.UeInfo.enLatestAttachOrRauContainDrx = NAS_MML_PS_REG_CONTAIN_BUTT;
    /* Modified by t00212959 for DCM定制需求和遗留问题, 2012-8-14, end */

    g_GmmGlobalCtrl.ucSuspendProc                = GMM_FALSE;
    g_GmmGlobalCtrl.stPowerOffCtrl.ulEstResult   = RRC_NAS_EST_RESULT_BUTT;
    Gmm_TimerStop(GMM_TIMER_ALL);

    g_GmmGlobalCtrl.ucNeedChgServiceStatus = VOS_TRUE;

    g_GmmInterRatCellReselect = 0;
    g_GmmGlobalCtrl.ucEventCause = GMM_EVENT_CAUSE_INVALID;
    /* 初始化为没有收到网侧detach消息 */
    g_GmmGlobalCtrl.ucRcvNetDetachFlg = VOS_FALSE;

    g_GmmGlobalCtrl.ucIsNeedStartT3340PdpExist = VOS_FALSE;

    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-15, begin */
#if (FEATURE_ON == FEATURE_LTE)
    /* 默认支持L能力 */
    g_GmmGlobalCtrl.UeInfo.ucMsRadioCapSupportLteFromAs     = (VOS_UINT8)NAS_MML_IsSupportLteCapability();
    g_GmmGlobalCtrl.UeInfo.ucMsRadioCapSupportLteFromRegReq = (VOS_UINT8)NAS_MML_IsSupportLteCapability();
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-15, end */
    g_GmmGlobalCtrl.UeInfo.enVoiceDomainFromRegReq          = NAS_MML_GetVoiceDomainPreference();
#endif

    /* 给RAC赋初始值 */
    ucLen = aucDefaultRac[0] + 1;
    PS_MEM_CPY(g_GmmGlobalCtrl.UeInfo.aucRadioCpb, aucDefaultRac, ucLen);

    /* 给RAC赋初始值 */
    ucLen = aucDefaultRac[0] + 1;
    PS_MEM_CPY(g_GmmGlobalCtrl.UeInfo.aucTdsRadioCpb, aucDefaultRac, ucLen);

    /* 初始化3311定时器未超时 */
    g_GmmRauCtrl.ucT3311ExpiredFlg  = GMM_FALSE;

    return;
}

/*******************************************************************************
  Module   : Gmm_TaskInit
  Function : GMM TASK定时器创建及AS API函数指针的初期化处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2003.12.10  新规作成
    2. 日    期   : 2006年11月6日
       作    者   : s46746
       修改内容   : 问题单号:A32D06867
    3. 日    期   : 2006年12月07日
       作    者   : s46746
       修改内容   : 创建，根据问题单号：A32D07799
    4. 日    期   : 2007年3月30日
       作    者   : s46746
       修改内容   : 问题单号:A32D09854
    5. 日    期   : 2007年8月28日
       作    者   : l60022475
       修改内容   : 问题单号：A32D12744,初始化GMM Timer句柄
    6. 日    期   : 2010年01月03日
       作    者   : o00132663
       修改内容   : 问题单号：xxxx,NAS R7协议升级，引入监控PS 信令链接释放定时器T3340
     7.日    期   : 2011年10月11日
       作    者   : l00171473
       修改内容   : V7R1 phase II,TC环回调整, 新增延迟向MMC回复SUSPEND_RSP定时器
     8.日    期   : 2011年12月2日
       作    者   : s46746
       修改内容   : 从L异系统改变到GU后，没有指派加密密钥到GU接入层
     9.日    期   : 2011年12月29日
       作    者   : l00130025
       修改内容   : DTS2011082201679/DTS2011121504358,切换模式，回退后W/G下注册状态没有与NAS同步
    10.日    期   : 2012年3月21日
       作    者   : z40661
       修改内容   : DTS2011110201060:L重选到W，被网络拒绝#9后携带的PTMSI不正确
     11.日    期   : 2012年3月7日
        作    者   : z00161729
        修改内容   : ISR修改
     12.日    期   : 2012年4月17日
        作    者   : z00161729
        修改内容  : DTS2012041402264：L小区下发起CS语音业务，通过重定向CS Fallback到W小区。激活PDP后释放CS语音，未上系统消息，UE不会发起联合RAU
    11.日    期   : 2012年5月15日
       作    者   : l00130025
       修改内容   : DTS2012041002516: 添加RadioCapa改变触发RAU延迟时间
    12.日    期   : 2012年08月24日
       作    者   : m00217266
       修改内容   : 删除GMM_ClearErrCode（PS域错误码上报项目）
    13.日    期   : 2012年8月15日
       作    者   : z00161729
       修改内容   : DCM定制需求和遗留问题修改
    14.日    期   : 2012年10月12日
       作    者   : w00176964
       修改内容   : DTS2012091400694:G模关机慢
    15.日    期   : 2013年01月4日
       作    者   : w00176964
       修改内容   : DTS2012122509167:GCF W协议用例7.1.5.6失败(关机detach时长过短5S，网络建链6S才回)
    16.日    期   : 2013年6月5日
       作    者   : w00242748
       修改内容   : svlte和usim接口调整
    17.日    期   : 2014年12月25日
       作    者   : w00167002
       修改内容   : DTS2014122201960:在L下SRVCC HO到G再HO到W,RABM触发重建，导致立即
                    触发RAU，后续收到系统消息又再次发起RAU,导致网络REL了链路，导致
                    掉话。修改为在HO后，启动保护定时器等系统消息。
    18.日    期   : 2015年7月2日
       作    者   : z00161729
       修改内容   : 24008 23122 R11 CR升级项目修改
*******************************************************************************/
VOS_VOID Gmm_TaskInit(VOS_VOID)
{
    VOS_UINT8 i;

    Gmm_MemSet(&g_GmmTimerMng, 0, sizeof(GMM_TIMER_STRU));

    g_GmmTimerMng.aTimerInf[GMM_TIMER_T3302].ulTimerVal = GMM_TIMER_T3302_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_T3310].ulTimerVal = GMM_TIMER_T3310_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_T3311].ulTimerVal = GMM_TIMER_T3311_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_T3312].ulTimerVal = GMM_TIMER_T3312_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_T3316].ulTimerVal = GMM_TIMER_T3316_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_T3317].ulTimerVal = GMM_TIMER_T3317_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_T3318].ulTimerVal = GMM_TIMER_T3318_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_T3319].ulTimerVal = GMM_TIMER_T3319_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_T3320].ulTimerVal = GMM_TIMER_T3320_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_T3321].ulTimerVal = GMM_TIMER_T3321_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_T3330].ulTimerVal = GMM_TIMER_T3330_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_1S   ].ulTimerVal = GMM_TIMER_1S_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_DETACH_FOR_POWER_OFF].ulTimerVal = GMM_TIMER_DETACH_FOR_POWER_OFF_VALUE;

    g_GmmTimerMng.aTimerInf[GMM_TIMER_PROTECT_PS_DETACH].ulTimerVal = GMM_TIMER_PROTECT_DETACH_NOT_BY_SYSCFG_VALUE;

    /* GCF测试,关机detach定时器时长为8S */
    if (VOS_TRUE == NAS_USIMMAPI_IsTestCard())
    {
        g_GmmTimerMng.aTimerInf[GMM_TIMER_DETACH_FOR_POWER_OFF].ulTimerVal = GMM_TIMER_DETACH_FOR_GCF_POWER_OFF_VALUE;
    }

    g_GmmTimerMng.aTimerInf[GMM_TIMER_PROTECT].ulTimerVal
            = GMM_TIMER_PROTECT_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_PROTECT_FOR_SIGNALING].ulTimerVal
            = GMM_TIMER_PROTECT_FOR_SIGNALING_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_SUSPENDED].ulTimerVal
            = GMM_TIMER_SUSPENDED_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_T3314].ulTimerVal
            = GMM_TIMER_T3314_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_RAU_RSP].ulTimerVal
            = GMM_TIMER_RAU_RSP_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_PROTECT_OLD_TLLI].ulTimerVal
            = GMM_TIMER_PROTECT_OLD_TLLI_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_T3340].ulTimerVal = GMM_TIMER_T3340_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_INTERRAT_HANDOVER_INFO_CNF].ulTimerVal = GMM_TIMER_INTERRAT_HANDOVER_INFO_CNF_VALUE;

    g_GmmTimerMng.aTimerInf[GMM_TIMER_WAIT_GET_RESEL_SECU_INFO_CNF].ulTimerVal = GMM_TIMER_WAIT_GET_RESEL_SECU_INFO_CNF_VALUE;
    g_GmmTimerMng.aTimerInf[GMM_TIMER_WAIT_GET_HO_SECU_INFO_CNF].ulTimerVal    = GMM_TIMER_WAIT_GET_HO_SECU_INFO_CNF_VALUE;

    g_GmmTimerMng.aTimerInf[GMM_TIMER_WAIT_CONNECT_REL].ulTimerVal    = GMM_TIMER_WAIT_CONNECT_REL_VALUE;

    g_GmmTimerMng.aTimerInf[GMM_TIMER_TC_DELAY_SUSPEND_RSP].ulTimerVal = GMM_TIMER_TC_DELAY_SUSPEND_RSP_VALUE;

    g_GmmTimerMng.aTimerInf[GMM_TIMER_T3323].ulTimerVal = GMM_TIMER_T3323_VALUE;


    /* GMM HO到GU后等系统消息的时长 */
    g_GmmTimerMng.aTimerInf[GMM_TIMER_HO_WAIT_SYSINFO].ulTimerVal = GMM_TIMER_WAIT_SYSINFO_VALUE;

    g_GmmTimerMng.aTimerInf[GMM_TIMER_DELAY_RADIO_CAPA_TRIGED_RAU].ulTimerVal = GMM_TIMER_DELAY_RADIO_CAPA_TRIGED_RAU_VALUE;


    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-15, begin */
    g_GmmTimerMng.aTimerInf[GMM_TIMER_WAIT_AS_MS_RADIO_CAPA_INFO].ulTimerVal = GMM_TIMER_WAIT_AS_MS_RADIO_CAPA_INFO_VALUE;
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-15, end */

    g_GmmTimerMng.aTimerInf[GMM_TIMER_DELAY_VOICE_DOMAIN_TRIG_RAU].ulTimerVal = GMM_TIMER_DELAY_VOICE_DOMAIN_TRIG_RAU_VALUE;

    g_GmmTimerMng.aTimerInf[GMM_TIMER_DELAY_PS_SMS_CONN_REL].ulTimerVal    = GMM_TIMER_DELAY_PS_SMS_CONN_REL_VALUE;
    
    for (i = 0; i < GMM_TIMER_NUM; i++)
    {
        g_GmmTimerMng.aTimerInf[i].ucMode = VOS_RELTIMER_NOLOOP;
        g_GmmTimerMng.aTimerInf[i].hTimer = VOS_NULL_PTR;
    }
    g_GmmImportFunc.RrmmDataReqFunc  = As_RrDataReq;
    g_GmmImportFunc.RrmmEstReqFunc   = NAS_GMM_AsEstReq;
    g_GmmImportFunc.RrmmRelReqFunc   = As_RrRelReq;

    Gmm_MemSet(&gstGmmSuspendCtrl, 0x0, sizeof(GMM_SUSPEND_CTRL_STRU));

    gstGmmSuspendCtrl.ucPreRat                    = NAS_MML_NET_RAT_TYPE_WCDMA;
    gstGmmSuspendCtrl.ucRauCause                  = GMM_RAU_FOR_NORMAL;
    gstGmmSuspendCtrl.ucT3312State                = GMM_T3312_NOT_TIMEOUT;
    gstGmmSuspendCtrl.ucNetModeChange             = GMM_FALSE;
    gstGmmSuspendCtrl.ucPowerOff                  = GMM_POWER_OFF_NOT_RCV;

    gstGmmSuspendCtrl.ucGetLteSecContext          = VOS_FALSE;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_GMM_SetLteGutiValid(VOS_TRUE);
#endif

    Gmm_ComVariantInit();

    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_MakeDetachMsg
 功能描述  : 生成DETACH消息
 输入参数  : 包含所有PDP状态的消息
 输出参数  : 无
 返 回 值  : 新成生成的MMCGMM_DETACH_REQ_STRU结构体指针，即DETACH消息
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年10月29日
    作    者   : l00167671/罗开辉
    修改内容   : 新建函数，问题单号：DTS2010100802035,CS ONLY模式去注册的处理
*****************************************************************************/
MMCGMM_DETACH_REQ_STRU* NAS_GMM_MakeDetachMsg( VOS_UINT32  ulDetachCause )
{

    MMCGMM_DETACH_REQ_STRU* pSndMsg = VOS_NULL_PTR;                                     /* 定义原语类型指针                         */

    /*申请消息  */
    pSndMsg = (MMCGMM_DETACH_REQ_STRU*)Gmm_MemMalloc(sizeof(MMCGMM_DETACH_REQ_STRU));

    if ( VOS_NULL_PTR == pSndMsg )
    {                                                                           /* 内存申请失败                             */
        PS_NAS_LOG(WUEPS_PID_MMC, VOS_NULL, PS_LOG_LEVEL_ERROR, "Mmc_SndGmmDetachReq:ERROR: Memory Alloc Error for pMsg");
        return VOS_NULL_PTR;                                                                 /* 返回                                     */
    }

    Gmm_MemSet(pSndMsg, 0x00, sizeof(MMCGMM_DETACH_REQ_STRU));

    pSndMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pSndMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pSndMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pSndMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_GMM;
    pSndMsg->MsgHeader.ulLength          = sizeof(MMCGMM_DETACH_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* 填写消息类别                             */
    pSndMsg->MsgHeader.ulMsgName   = MMCGMM_DETACH_REQ;                         /* 填写消息名称                             */

    pSndMsg->enDetachType          = ulDetachCause;

    return pSndMsg;

}
/*****************************************************************************
 函 数 名  : NAS_GMM_RcvSmPdpModifyInd
 功能描述  : 处理GMMSM_PDP_MODIFY_IND消息
 输入参数  : pRcvMsg - GMMSM_PDP_MODIFY_IND消息内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月27日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_GMM_RcvSmPdpModifyInd(VOS_VOID *pRcvMsg)
{
#if (FEATURE_LTE == FEATURE_ON)
    GMMSM_PDP_MODIFY_IND_STRU          *pSmPdpModifyInd;
    NAS_MML_TIN_TYPE_ENUM_UINT8         enCurrTinType;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrRatType;
    VOS_UINT8                           ucNsapi;
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo;

    pSmPdpModifyInd = (GMMSM_PDP_MODIFY_IND_STRU *)pRcvMsg;
    ucNsapi         =  pSmPdpModifyInd->ucNsapi;
    enCurrTinType   =  NAS_MML_GetTinType();
    enCurrRatType   =  NAS_MML_GetCurrNetRatType();
    pstRplmnCfgInfo =  NAS_MML_GetRplmnCfg();

    /* 3GPP 24008 6.3  Coordination between SM and GMM for supporting ISR章节描述：
       This subclause applies to a MS with its TIN set as "RAT related TMSI" for which ISR is activated.
       The MS shall change its TIN to "P-TMSI" to deactivate ISR:
       -   upon modification of any PDP context which was activated before the ISR is activated in the MS
    */
    if ((VOS_TRUE == NAS_MML_IsPsBearerExistBeforeIsrAct(ucNsapi))
     && (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == enCurrTinType)
     && (NAS_MML_NET_RAT_TYPE_LTE != enCurrRatType))
    {
        NAS_GMM_WriteTinInfoNvim(NAS_MML_TIN_TYPE_PTMSI, pstRplmnCfgInfo->aucLastImsi);
        Gmm_TimerStop(GMM_TIMER_T3323);

        /* ISR去激活，需要更新pdp激活是在ISR激活前激活的 */
        NAS_MML_UpdateAllPsBearIsrFlg(NAS_MML_PS_BEARER_EXIST_BEFORE_ISR_ACT);
    }
#endif
    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_RcvSmPdpDeactivatedInd
 功能描述  : 消息GMMSM_PDP_DEACTIVATED_IND的接收处理,据条件发起PS去注册
 输入参数  : 包含所有PDP状态的消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年8月10日
    作    者   : LUOKAIHUI/l00167671
    修改内容   : 新生成函数
  2.日    期   : 2010年10月22日
    作    者   : z00161729
    修改内容   : 问题单:DTS2010102003076,E5 GCF测试要求pdp激活或去激活达到最大次数后,如果网侧没响应则主动释放链路
  3.日    期   : 2010年10月29日
    作    者   : l00167671/罗开辉
    修改内容   : 问题单号：DTS2010100802035,CS ONLY模式去注册的处理
  4.日    期   : 2010年11月23日
    作    者   : A00165503
    修改内容   : 问题单号: DTS2010112304706，重选过程中断开拨号后，再次拨号失败
  5.日    期   : 2011年02月21日
    作    者   : z00161729
    修改内容   : 问题单号DTS2011021900432:GMM在GMM_SERVICE_REQUEST_INITIATED状态收到sm pdp去激活
                 指示未启T3340释放RRC连接,导致RRC常时间未释放,影响BG正常进行
  6.日    期   : 2011年3月2日
    作    者   : z00161729
    修改内容   : DTS2010071601574:RAU过程完成收到rau accept需要等待RABM或WRR回复后再发送RAU cmp消息期间,
                 cs only场景缓存detach请求,等RAU结束再发起

  7.日    期   : 2011年7月14日
    作    者   : zhoujun 40661
    修改内容   : 更新MML_CTX中的链接存在状态
  8.日    期   : 2011年8月12日
    作    者   : l65478
    修改内容   : DTS2011081001476:印度外场测试,无法设置G->W
  9.日    期   : 2011年12月23日
    作    者   : s46746
    修改内容   : DTS2011122007386:PDP被去激活后,PS缓存标志未清除
  10.日    期   : 2012年3月31日
     作    者   : z00161729
     修改内容   : 支持ISR修改

  11.日    期   : 2012年10月17日
    作    者   : z40661
    修改内容   : DTS2012092004258:PDP去激活,启动T3340定时器，而GCF协议要求重传次数为3次，需要启动15s
                 定时器。

  12.日    期   : 2012年11月17日
     作    者   : w00167002
     修改内容   : DTS2012111409855:若以前有缓存消息,则释放掉，在TD下内部list搜时候，如果用户发起PDP激活，
                   此时虽然ulMsgHoldMsk为空，但仍缓存了PS SERVICE标识，所以需要清楚掉.
                   否则，会将此标识维护得不正确，导致内部LIST搜网定时器一直起停。
  13.日    期   : 2013年3月30日
     作    者   : l00167671
     修改内容   : 主动上报AT命令控制下移至C核
  14.日    期   : 2013年8月7日
     作    者   : w00167002
     修改内容   : DTS2013080207367:在CS only时候，用户发起PDP激活，网络模式I时候，
                  会触发联合注册.用户发起PDP去激活，会导致PS域的去注册。收到网侧
                  的去注册成功后需要通知MM，否则MM当前在NORMAL SERVICE状态，不
                  触发T3212定时器的启动，长时间可能导致丢寻呼.
   15.日    期   : 2014年01月13日
      作    者   : l65478
      修改内容   : DTS2013102508485, 澳电PDP去激活后UE主动释放了RRC连接
*****************************************************************************/
VOS_VOID NAS_GMM_RcvSmPdpDeactivatedInd(VOS_VOID *pRcvMsg)
{
    GMMSM_PDP_DEACTIVATED_IND_STRU     *pSmPdpStatusInd;
    MMCGMM_DETACH_REQ_STRU             *ptr;
    NAS_MML_CONN_STATUS_INFO_STRU       *pstConnStatus;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8      enCurRat;

#if (FEATURE_LTE == FEATURE_ON)
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo;

    pstRplmnCfgInfo = NAS_MML_GetRplmnCfg();
#endif

    enCurRat = NAS_MML_GetCurrNetRatType();

    pstConnStatus   = NAS_MML_GetConnStatus();

    pSmPdpStatusInd = (GMMSM_PDP_DEACTIVATED_IND_STRU *)pRcvMsg;

    /* 没有短信时,清除follow on标志 */
    if (GMM_FALSE == g_GmmServiceCtrl.ucSmsFlg)
    {
        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;
    }


    /* 若以前有缓存消息,则释放掉，在TD下内部list搜时候，如果用户发起PDP激活，
       此时虽然ulMsgHoldMsk为空，但仍缓存了PS SERVICE标识，所以需要清楚掉 */
    if (GMM_MSG_HOLD_FOR_SM ==
        (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SM))
    {
        NAS_NORMAL_LOG(WUEPS_PID_GMM, "NAS_GMM_RcvSmPdpDeactivatedInd(): Clear cached SM Data Req");

        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSm);
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SM;
    }


    if ((0x0 == g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk)
     && (GMM_FALSE == g_GmmGlobalCtrl.ucFollowOnFlg))
    {
        g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);
    }

    if ((NAS_MML_MS_MODE_CS_ONLY == NAS_MML_GetMsMode())
     && (VOS_FALSE == g_GmmGlobalCtrl.ucUserPsAttachFlag))
    {
        /* pSmPdpStatusInd->ulPdpContextStatus中仅用到了低十六位 */
        if (GMM_SM_PDP_CONTEXT_NOT_EXIST == (pSmPdpStatusInd->ulPdpContextStatus & 0xFFFF))
        {
            /* 已经没有激活的PDP */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING,
                   "NAS_GMM_RcvSmPdpDeactivatedInd:Normal: Service is CS ONLY,Detach PS");

            NAS_MML_SetPsAttachAllowFlg( VOS_FALSE );

            /* 根据GMM状态做去注册还是做本地去注册 */
            if ((GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
             || (VOS_TRUE == gstGmmCasGlobalCtrl.ucRauCmpFlg))
            {
                g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_DETACH;

				/* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
                ptr = NAS_GMM_MakeDetachMsg(NAS_MSCC_PIF_DETACH_TYPE_GPRS);
				/* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

                if (VOS_NULL_PTR == ptr)
                {
                    g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_DETACH;
                    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_RcvMmcDetachReq:ERROR: Allocate memory error in Gmm_RcvMmcDetachReq");
                    return;
                }
                g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach = (VOS_UINT32)ptr;
            }
            else if ((GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
                  || (GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM == g_GmmGlobalCtrl.ucState))
            {
                Gmm_MsInitNormalDetach(MMC_GMM_PS_DETACH);
            }
            else if (GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucState)
            {
                if ((GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
                && (GMM_RRC_RRMM_EST_CNF_FLG
                == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)))
                {                                                               /* 无信令且正在建立信令连接                 */
                    g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_DETACH;

					 /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
                    ptr = NAS_GMM_MakeDetachMsg(NAS_MSCC_PIF_DETACH_TYPE_GPRS);
					 /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

                    if (VOS_NULL_PTR == ptr)
                    {
                        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_DETACH;
                        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_RcvMmcDetachReq:ERROR: Allocate memory error in Gmm_RcvMmcDetachReq");
                        return;
                    }
                    g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach = (VOS_UINT32)ptr;
                }
                else
                {
                    Gmm_MsInitNormalDetach(MMC_GMM_PS_DETACH);
                }
            }
            else if ((GMM_REGISTERED_PLMN_SEARCH== g_GmmGlobalCtrl.ucState)
                  || (GMM_REGISTERED_ATTEMPTING_TO_UPDATE == g_GmmGlobalCtrl.ucState)
                  || (GMM_REGISTERED_NO_CELL_AVAILABLE == g_GmmGlobalCtrl.ucState)
                  || (GMM_REGISTERED_LIMITED_SERVICE == g_GmmGlobalCtrl.ucState)
                  || (GMM_REGISTERED_UPDATE_NEEDED == g_GmmGlobalCtrl.ucState))
            {   /* 本地将GMM状态迁到未注册状态,如果是出服务区则LL已经被挂起,进服务区时若t3312未超时
                   是否需要发起DETACH,待定*/
                Gmm_ComStaChg(GMM_DEREGISTERED_NO_CELL_AVAILABLE);
                NAS_MML_SetPsAttachAllowFlg( VOS_FALSE );


                /* 通知GMM当前PS域DETACH完成 */
                NAS_GMM_SndMmGprsDetachComplete();

                Gmm_ClearLlcData(LL_GMM_CLEAR_DATA_TYPE_ALL);

                if (GMM_TRUE == GMM_IsCasGsmMode())
                {
                    Gmm_TimerStop(GMM_TIMER_T3314);
                    gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_IDLE;

                    /* default 44s */
                    gstGmmCasGlobalCtrl.ulReadyTimerValue = 44000;
#if (FEATURE_LTE == FEATURE_ON)
                    if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
                    {
                        NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
                    }
#endif
                    Gmm_TimerStop(GMM_TIMER_T3312);
                    NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);

                }
            }
            else
            {
            }
        }
    }


    /* W下PDP去激活且GMM处于正常服务状态或GMM_SERVICE_REQUEST_INITIATED且没有短信业务时需要启T3340,
       等待RRC链路释放,期间收到的PDP激活请求GMM将缓存等PDP去激活链路释放后再发起 */
    if ((GMM_FALSE == GMM_IsCasGsmMode())
     && (GMM_SM_PDP_CONTEXT_NOT_EXIST == (pSmPdpStatusInd->ulPdpContextStatus & 0xFFFF))
     && (GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
     && (VOS_TRUE == g_GmmGlobalCtrl.ucRelConnAfterPdpDeact))
    {
        if ((GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
         || ((GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucState)
          && (GMM_FALSE == g_GmmServiceCtrl.ucSmsFlg)))
        {
            g_GmmTimerMng.aTimerInf[GMM_TIMER_T3340].ulTimerVal = GMM_TIMER_WAIT_REL_PS_SIGNAL_VALUE;
            Gmm_TimerStart(GMM_TIMER_T3340);
            g_GmmTimerMng.aTimerInf[GMM_TIMER_T3340].ulTimerVal = GMM_TIMER_T3340_VALUE;
        }
    }

    if ((VOS_FALSE == pstConnStatus->ucPsTbfStatusFlg)
     && (NAS_MML_NET_RAT_TYPE_GSM == enCurRat))
    {
        Gmm_SndMmcTBFRelInd();
    }

    g_GmmGlobalCtrl.enServReq = GMM_SERVICE_REQ_NONE;

#if (FEATURE_LTE == FEATURE_ON)
    if (GMM_SM_PDP_CONTEXT_NOT_EXIST == (pSmPdpStatusInd->ulPdpContextStatus & 0xFFFF))
    {
        if ((NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == NAS_MML_GetTinType())
         && (NAS_MML_NET_RAT_TYPE_LTE != enCurRat))
        {
            NAS_GMM_WriteTinInfoNvim(NAS_MML_TIN_TYPE_PTMSI, pstRplmnCfgInfo->aucLastImsi);
            Gmm_TimerStop(GMM_TIMER_T3323);

            /* ISR去激活，需要更新pdp激活是在ISR激活前激活的 */
            NAS_MML_UpdateAllPsBearIsrFlg(NAS_MML_PS_BEARER_EXIST_BEFORE_ISR_ACT);
        }
    }
#endif

    return;
}

/*******************************************************************************
  Module   : Gmm_RcvSmPdpStatusInd
  Function : 原语GMMSM_PDP_STATUS_IND的接收处理
  Input    : VOS_VOID *pRcvMsg  接收消息使用的头地址定义
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2003.12.10  新规作成
    2. 日    期   : 2009年05月05日
       作    者   : s62952
       修改内容   : AT2D11639
    3. 日    期   : 2009年06月30日
       作    者   : l65478
       修改内容   : 问题单：AT2D12655,增加清除LLC数据类型的处理
    4. 日    期   : 2009年06月30日
       作    者   : l65478
       修改内容   : 问题单：AT2D12677,增加判断，在W下不给LL发送清除数据消息
    5. 日    期   : 2010年11月23日
       作    者   : A00165503
       修改内容   : 问题单号: DTS2010112304706，重选过程中断开拨号后，再次拨号失败

    6. 日    期   : 2011年8月9日
       作    者   : l00167671
       修改内容   : 问题单号DTS2011080502405 PDP STATUS维护错误，导致做RAU时IE填写错误
    7. 日    期   : 2012年10月18日
       作    者   : s00217060
       修改内容   : DTS2012071702125:ucPdpStatusFlg标志维护更改
    8.日    期   : 2012年12月13日
      作    者   : L00171473
      修改内容   : DTS2012121802573, TQE清理
    9.日    期   : 2012年3月15日
      作    者   : l65478
      修改内容   : DTS2013120300990:在PDP激活过程中发起RAU,第一次PDP激活失败
   10.日    期   : 2014年12月06日
      作    者   : A00165503
      修改内容   : DTS2014120207400: 连续去激活多个PDP, 网侧不释放RRC连接
   11.日    期   : 2015年07月20日
      作    者   : zwx247453
      修改内容   : 3 modem tas
*******************************************************************************/
VOS_VOID Gmm_RcvSmPdpStatusInd(
                           VOS_VOID *pRcvMsg                                    /* 接收消息使用的头地址定义                 */
                           )
{
    GMMSM_PDP_STATUS_IND_STRU          *pSmPdpStatusInd;                        /* 定义GMMSM_PDP_STATUS_IND_STRU类型指针    */
    VOS_UINT8                           ucPrePdpStatusFlg;                      /* 原来是否存在激活的PDP context标志        */
    VOS_UINT8                           ucCurPdpStatusFlg;                      /* 当前是否存在激活的PDP context标志        */
    NAS_MML_PS_BEARER_CONTEXT_STRU      stPsBearCtx;
    VOS_UINT32                          i;
    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus;

    pstConnStatus   = NAS_MML_GetConnStatus();


    PS_MEM_SET(&stPsBearCtx, 0x00, sizeof(stPsBearCtx));

    ucCurPdpStatusFlg = MMC_GMM_ACTIVE_PDP_CONTEXT_NOT_EXIST;

    pSmPdpStatusInd = (GMMSM_PDP_STATUS_IND_STRU *)pRcvMsg;                     /* 得到消息指针                             */

    ucPrePdpStatusFlg = pstConnStatus->ucPdpStatusFlg;

    /* 根据消息中pdp状态更新MML中全局变量 g_stNasMmlCtx.stNetworkInfo.astPsBearerContext*/
    for (i = 0; i < NAS_MML_MAX_PS_BEARER_NUM; i++)
    {
        stPsBearCtx.enPsBearerIsrFlg = NAS_MML_PS_BEARER_EXIST_BEFORE_ISR_ACT;
        stPsBearCtx.enPsBearerState  = NAS_MML_PS_BEARER_STATE_INACTIVE;
        stPsBearCtx.ucPsActPending   = VOS_FALSE;
        stPsBearCtx.ucPsDeactPending = VOS_FALSE;

        if (GMMSM_PDP_STATE_ACTIVE == pSmPdpStatusInd->aucPdpContextStatus[i])
        {
            stPsBearCtx.enPsBearerState = NAS_MML_PS_BEARER_STATE_ACTIVE;
            ucCurPdpStatusFlg           = MMC_GMM_ACTIVE_PDP_CONTEXT_EXIST;

            if (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == NAS_MML_GetTinType())
            {
                stPsBearCtx.enPsBearerIsrFlg = NAS_MML_PS_BEARER_EXIST_AFTER_ISR_ACT;
            }
        }
        else if (GMMSM_PDP_STATE_ACTIVE_PENDING == pSmPdpStatusInd->aucPdpContextStatus[i])
        {
            stPsBearCtx.ucPsActPending  = VOS_TRUE;
            ucCurPdpStatusFlg           = MMC_GMM_ACTIVE_PDP_CONTEXT_EXIST;
        }
        else if (GMMSM_PDP_STATE_INACTIVE_PENDING == pSmPdpStatusInd->aucPdpContextStatus[i])
        {
            stPsBearCtx.ucPsDeactPending = VOS_TRUE;
            ucCurPdpStatusFlg            = MMC_GMM_ACTIVE_PDP_CONTEXT_EXIST;
        }
        else
        {
        }

        /* 驻留在L,由L更新pdp状态 */
        if (NAS_MML_NET_RAT_TYPE_LTE != NAS_MML_GetCurrNetRatType())
        {
            NAS_MML_SetPsBearerCtx((VOS_UINT8)(i + NAS_MML_MIN_NSAPI), &stPsBearCtx);
        }
        /* LTE下时,只需要更新状态为PENDING的PDP状态 */
        else
        {
            NAS_Gmm_ClearPendingPdpStatus();
        }

    }

    if ( MMC_GMM_ACTIVE_PDP_CONTEXT_NOT_EXIST == ucCurPdpStatusFlg)
    {
        pstConnStatus->ucPdpStatusFlg       = VOS_FALSE;
    }
    else
    {
        pstConnStatus->ucPdpStatusFlg       = VOS_TRUE;
    }

    if (ucPrePdpStatusFlg != pstConnStatus->ucPdpStatusFlg)
    {                                                                           /* PDP CONTEXT状态变化                      */
        Gmm_SndMmcPdpStatusInd(ucCurPdpStatusFlg);                              /* 通知MMC最新的PDP CONTEXT状态             */
    }

    /* PDP去激活后，通知LL和GRM清除缓存的用户和信令面数据 */
    if(MMC_GMM_ACTIVE_PDP_CONTEXT_NOT_EXIST == ucCurPdpStatusFlg)
    {
        if (GMM_TRUE == GMM_IsCasGsmMode())
        {
            Gmm_SndLlcAbortReq(LL_GMM_CLEAR_DATA_TYPE_USER);
        }
    }

    return;
}

#if (FEATURE_ON == FEATURE_DSDS)
/*****************************************************************************
 函 数 名  : NAS_GMM_RcvSmBeginSessionNotify
 功能描述  : 将gmm和sm接口中的session type转换为gmm和gu接入层的session type
 输入参数  : enGmmSmSessionType  - gmm和sm接口中的session type
 输出参数  : pucRrcSessionType   - gmm和gu接入层的session type
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月25日
    作    者   : z00161729
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_GMM_ConvertSmSessionTypeToRrc(
    GMMSM_SESSION_TYPE_ENUM_UINT8       enGmmSmSessionType,
    RRC_NAS_SESSION_TYPE_ENUM_UINT8    *pucRrcSessionType
)
{
    switch (enGmmSmSessionType)
    {
        case GMMSM_SESSION_TYPE_CONVERSAT_CALL:
            *pucRrcSessionType = RRC_NAS_SESSION_TYPE_PS_CONVERSAT_CALL;
            break;

        case GMMSM_SESSION_TYPE_STREAM_CALL:
            *pucRrcSessionType = RRC_NAS_SESSION_TYPE_PS_STREAM_CALL;
            break;

        case GMMSM_SESSION_TYPE_INTERACT_CALL:
            *pucRrcSessionType = RRC_NAS_SESSION_TYPE_PS_INTERACT_CALL;
            break;

        case GMMSM_SESSION_TYPE_BACKGROUND_CALL:
            *pucRrcSessionType = RRC_NAS_SESSION_TYPE_PS_BACKGROUND_CALL;
            break;

        case GMMSM_SESSION_TYPE_SUBSCRIB_TRAFFIC_CALL:
            *pucRrcSessionType = RRC_NAS_SESSION_TYPE_PS_SUBSCRIB_TRAFFIC_CALL;
            break;

        default:
            *pucRrcSessionType = RRC_NAS_SESSION_TYPE_BUTT;
            break;
    }
    return;
}
#endif

/*****************************************************************************
 函 数 名  : NAS_GMM_RcvSmBeginSessionNotify_PreProc
 功能描述  : 收到sm的begin session消息的处理
 输入参数  : pstBeginSessionMsg  - 收到sm begin session消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月25日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2015年09月23日
    作    者   : c00318887
    修改内容   : DTS2015082604451:修改DSDS宏控
*****************************************************************************/
VOS_VOID NAS_GMM_RcvSmBeginSessionNotify_PreProc(
    GMMSM_BEGIN_SESSION_NOTIFY_STRU    *pstBeginSessionMsg
)
{
#if (FEATURE_ON == FEATURE_DSDS)
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enRrcSessionType;
#endif

#if (FEATURE_ON == FEATURE_DSDS)
    if (GMMSM_SESSION_TYPE_BUTT != pstBeginSessionMsg->enSessionType)
    {
        NAS_GMM_ConvertSmSessionTypeToRrc(pstBeginSessionMsg->enSessionType, &enRrcSessionType);

        NAS_GMM_SndBeginSessionNotify(enRrcSessionType);
    }
#endif     

    NAS_MML_SetSmProcFlag(NAS_MML_SM_PROC_FLAG_START);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_RcvSmEndSessionNotify_PreProc
 功能描述  : 收到sm的end session消息的处理
 输入参数  : pstEndSessionMsg  - 收到sm end session消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年6月25日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2015年09月23日
    作    者   : c00318887
    修改内容   : DTS2015082604451:修改DSDS宏控
*****************************************************************************/
VOS_VOID NAS_GMM_RcvSmEndSessionNotify_PreProc(
    GMMSM_END_SESSION_NOTIFY_STRU      *pstEndSessionMsg
)
{
#if (FEATURE_ON == FEATURE_DSDS)
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enRrcSessionType;
#endif

#if (FEATURE_ON == FEATURE_DSDS)
    if (GMMSM_SESSION_TYPE_BUTT != pstEndSessionMsg->enSessionType)
    {
        NAS_GMM_ConvertSmSessionTypeToRrc(pstEndSessionMsg->enSessionType, &enRrcSessionType);

        NAS_GMM_SndEndSessionNotify(enRrcSessionType);
    }
#endif 

    NAS_MML_SetSmProcFlag(NAS_MML_SM_PROC_FLAG_FINISH);

    return;
}



/*******************************************************************************
  Module   : Gmm_ComPlmnSearchInit
  Function : 进行PLMN搜索时GMM进行内部变量的初始化
  Input    : VOS_VOID
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1.日    期   : 2007年07月05日
      作    者   : L65478
      修改内容   : created
    2.日    期   : 2008年7月2日
      作    者   : l00107747
      修改内容   : 根据问题单号：AT2D03900
    3.日    期   : 2011年3月12日
      作    者   : z00161729
      修改内容   : 根据问题单号：DTS2011022400350开机未注册时pdp拨号在指定搜网pdp拨号失败
    4.日    期   : 2011年07月13日
      作    者   : w00166186
      修改内容   : V7R1 PHASE II ATTACH/DETACH调整
    5.日    期   : 2011年04月14日
      作    者   : 欧阳飞
      修改内容   : DTS2011041202700,在PS域卡无效后，状态又迁到受限服务，导致应用查询SYSINFO
                   时显示卡有效。
    6.日    期   : 2011年03月24日
      作    者   : 欧阳飞
      修改内容   : 问题单号:DTS2011032400460，驻留成功后，用户指定不存在网络搜网，
                   受限驻留后，T3312超时后，MM发起了不期望的LAU
    7.日    期   : 2011年11月18日
      作    者   : w00167002
      修改内容   : DTS2011110300229:G下CSonly时，背景搜CS失败3次后用户发起ATTACH，
                   失败4此后，用户回RPlmn，发起了PS域的注册。在GMM suspend状态，
                   收到搜网请求后，将GMM状态迁移到搜网状态。
    8.日    期   : 2013年8月7日
      作    者   : w00167002
      修改内容   : DTS2013080207367:在CS only时候，用户发起PDP激活，网络模式I时候，
                 会触发联合注册.用户发起PDP去激活，会导致PS域的去注册。收到网侧
                 的去注册成功后需要通知MM，否则MM当前在NORMAL SERVICE状态，不
                 触发T3212定时器的启动，长时间可能导致丢寻呼.
    9.日    期   : 2013年10月05日
      作    者   : l65478
      修改内容   : DTS2013092509860:GPRS detach过程被BG搜索终止后,GMM又自动发起了注册
    10.日    期   : 2015年1月26日
       作    者   : z00161729
       修改内容   : AT&T 支持DAM特性修改
*******************************************************************************/
VOS_VOID Gmm_ComPlmnSearchInit()
{
    if (0x10 == (g_GmmGlobalCtrl.ucState & 0xF0))
    {
        /* 当前不为PS域卡无效 */
        if (GMM_DEREGISTERED_NO_IMSI != g_GmmGlobalCtrl.ucState)
        {
            Gmm_ComStaChg(GMM_DEREGISTERED_PLMN_SEARCH);                        /* 调用状态的公共处理                       */
            if (GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH != g_GmmGlobalCtrl.ucPlmnSrchPreSta)
            {
                Gmm_TimerStop(GMM_TIMER_T3311);

                if (VOS_FALSE == NAS_MML_IsPlmnSupportDam(NAS_MML_GetCurrCampPlmnId()))
                {
                    Gmm_TimerStop(GMM_TIMER_T3302);
                }
            }
        }
    }
    else if ((0x20 == (g_GmmGlobalCtrl.ucState & 0xF0))
        && (GMM_REGISTERED_IMSI_DETACH_INITIATED != g_GmmGlobalCtrl.ucPlmnSrchPreSta)
        && (GMM_REGISTERED_ATTEMPTING_TO_UPDATE != g_GmmGlobalCtrl.ucPlmnSrchPreSta)
        && (GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM != g_GmmGlobalCtrl.ucPlmnSrchPreSta))
    {                                                                           /* REGISTERED状态下且非流程中               */
        Gmm_ComStaChg(GMM_REGISTERED_PLMN_SEARCH);                              /* 调用状态的公共处理                       */
        Gmm_TimerStop(GMM_TIMER_T3311);

        if (VOS_FALSE == NAS_MML_IsPlmnSupportDam(NAS_MML_GetCurrCampPlmnId()))
        {
            Gmm_TimerStop(GMM_TIMER_T3302);
        }
    }

    else if (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
    {
        Gmm_TimerStop(GMM_TIMER_T3310);                                         /* 停T3310                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */

        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask
            & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* 等待鉴权响应                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* 停保护定时器                             */
            g_GmmReqCnfMng.ucCnfMask
                &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;                      /* 清除原语等待标志                         */
        }


        Gmm_ComStaChg(GMM_DEREGISTERED_PLMN_SEARCH);
    }

    else if (GMM_DEREGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
    {   /*只有用户发起的detach过程才会进入GMM_DEREGISTERED_INITIATED*/
        /*不需要判断当前detach类型*/
        Gmm_TimerStop(GMM_TIMER_T3321);                                         /* 停T3321                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */

        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask
            & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* 等待鉴权响应                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* 停保护定时器                             */
            g_GmmReqCnfMng.ucCnfMask
                &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;                      /* 清除原语等待标志                         */
        }
        /* 判断等待标志是否存在，如果存在则向MMC,MM发送DETACH信息 */
        if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
        {
            if (GMM_WAIT_PS_DETACH == (g_GmmGlobalCtrl.stDetachInfo.enDetachType & GMM_WAIT_PS_DETACH))
            {
                NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);
            }
            NAS_GMM_SndMmcMmDetachInfo();
        }

        else if ( VOS_FALSE == NAS_MML_GetPsAttachAllowFlg() )
        {
            /* 收到网侧的去注册成功后需要通知MM，否则MM不启动T3212定时器 */
            NAS_GMM_SndMmGprsDetachComplete();
        }
        else
        {

        }

        Gmm_ComStaChg(GMM_DEREGISTERED_PLMN_SEARCH);
    }

    else if (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
    {
        Gmm_TimerStop(GMM_TIMER_T3330);                                         /* 停T3330                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */
        Gmm_TimerStop(GMM_TIMER_T3311);
        Gmm_TimerStop(GMM_TIMER_T3302);

        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask
            & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* 等待鉴权响应                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* 停保护定时器                             */
            g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG; /* 清除原语等待标志                         */
        }

        if (GMM_MSG_HOLD_FOR_RAU
            == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_RAU))
        {                                                                       /* 如果有保留的RAU原语                      */
            g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_RAU;      /* 清除缓存标志                             */
            Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForRau);   /* 读取RAU原语地址                          */
        }
        Gmm_ComCnfHandle();
        Gmm_ComStaChg(GMM_REGISTERED_PLMN_SEARCH);
    }

    else if (GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucState)
    {
        Gmm_TimerStop(GMM_TIMER_T3317);                                         /* 停T3317                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */

        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask
            & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* 等待鉴权响应                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* 停保护定时器                             */
            g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG; /* 清除原语等待标志                         */
        }

        Gmm_ComCnfHandle();
    }
    else if (GMM_SUSPENDED_WAIT_FOR_SYSINFO == g_GmmGlobalCtrl.ucState)
    {
        Gmm_TimerStop(GMM_TIMER_SUSPENDED);

        g_GmmRauCtrl.ucNpduCnt = 0x0;
        if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
        {
            GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_HANDOVER, GMM_RABM_RAU_FAILURE);
        }
        else
        {
#if 0
            GMM_SndRabmGprsInfoInd(GMM_RABM_GPRS_SUPPORTED, GMM_RABM_PROC_HANDOVER,
                           GMM_RABM_IMMEDIATELY_RAU);
#endif

            GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_HANDOVER, GMM_RABM_RAU_FAILURE);
        }
        GMM_BufferMsgDump();

        Gmm_ComStaChg(GMM_REGISTERED_PLMN_SEARCH);
    }
    else if ( GMM_GPRS_SUSPENSION == g_GmmGlobalCtrl.ucState )
    {
        /* 签到搜网状态 */
        if ( (0x10 == (gstGmmSuspendCtrl.ucPreState & 0xF0))
          || (GMM_REGISTERED_INITIATED == gstGmmSuspendCtrl.ucPreState) )
        {
            Gmm_ComStaChg(GMM_DEREGISTERED_PLMN_SEARCH);
        }
        else
        {
            Gmm_ComStaChg(GMM_REGISTERED_PLMN_SEARCH);
        }

        /* GSM下的系统消息初始化 */
        NAS_GMM_FreeGsmSysInfo();

        /* 缓存内容的处理 */
        GMM_BufferMsgResume();
    }
    else
    {
        Gmm_ComStaChg(GMM_REGISTERED_PLMN_SEARCH);
    }

    g_GmmReqCnfMng.ucCnfMask = 0;                                               /* 清所有等待cnf                            */
    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                            /* 清除当前流程                             */
    g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;                        /* 清除保留的过程                           */
    g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;                   /* 清除记录的CS通信中流程                   */

}


/*******************************************************************************
  Module   : Gmm_RcvMmcPlmnUserSelReq
  Function : 收到原语MMCGMM_PLMN_USER_SEL_REQ的处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
  1. 李  炎  2003.12.10  新规作成
  2. 日    期   : 2006年12月5日
     作    者   : l65478
     修改内容   : 问题单号：A32D10052
  3. 日    期   : 2007年09月03日
     作    者   : luojian id:60022475
     修改内容   : 根据问题单号：AT2D01459
  4. 日    期   : 2007年10月16日
     作    者   : l65478
     修改内容   : 根据问题单号：A32D11957
  5. 日    期   : 2011年07月13日
     作    者   : w00166186
     修改内容   : V7R1 PHASE II ATTACH/DETACH调整
  6.日    期   : 2011年7月27日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  7.日    期   : 2013年08月23日
    作    者   : f00179208
    修改内容   : ErrLog&FTM项目,PTMSI发生改变时上报给OM
*******************************************************************************/
VOS_VOID Gmm_RcvMmcPlmnUserSelReq(VOS_VOID)
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* 定义MSG_HEADER_STRU类型指针              */
    VOS_VOID            *pAddr;

    if (GMM_RRC_RRMM_EST_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG))
    {                                                                           /* 判断是否有信令存在                       */
        Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);                                   /* 释放信令                                 */
    }

    if (GMM_REGISTERED_PLMN_SEARCH != g_GmmGlobalCtrl.ucState)
    {
        g_GmmGlobalCtrl.ucPlmnSrchPreSta = g_GmmGlobalCtrl.ucState;
    }

    Gmm_ComPlmnSearchInit();

    if (GMM_MSG_HOLD_FOR_POWEROFF
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_POWEROFF))
    {                                                                           /* 如果有保留的power off原语                */
        pNasMsgHeader =
            (MSG_HEADER_STRU *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPowerOff;    /* 得到消息头                               */

        if (MMCGMM_POWER_OFF_REQ == pNasMsgHeader->ulMsgName)
        {
            if (GMM_UEID_P_TMSI_SIGNATURE
                == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
                & GMM_UEID_P_TMSI_SIGNATURE))
            {                                                                   /* DETACH成功且使用了P_TMSI_SIGNATURE       */
                g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
                    &= ~GMM_UEID_P_TMSI_SIGNATURE;                              /* 清除P_TMSI_SIGNATURE                     */

                NAS_MML_InitUeIdPtmsiSignatureInvalid();
                if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
                {
                    Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* 更新SIM卡信息                            */
                }
                else
                {
                    Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
                }
            }
            Gmm_ComStaChg(GMM_NULL);                     /* 调用状态的公共处理                       */
            Gmm_SndMmcPowerOffCnf();                                            /* 向MMC发送MMCGMM_DETACH_CNF               */
            Gmm_ComVariantInit();
        }
        else
        {
            /* 判断等待标志是否存在，如果存在则向MMC,MM发送DETACH信息 */
            if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
            {
                NAS_GMM_SndMmcMmDetachInfo();
            }
            Gmm_ComStaChg(GMM_DEREGISTERED_NO_IMSI);                            /* 调用状态的公共处理                       */
            g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                    /* 清当前流程                               */
            NAS_MML_SetSimPsRegStatus(VOS_FALSE);                /* 置SIM卡不存在标志                        */
            g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_IMSI;           /* 清除IMSI存在MASK                         */
            g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI;         /* 清除P_TMSI存在MASK                       */
            g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI_SIGNATURE;      /* 清除P_TMSI_SIGNATURE存在MASK             */

            NAS_MML_InitUeIdPtmisInvalid();
            NAS_MML_InitUeIdPtmsiSignatureInvalid();

            Gmm_SndRrmmNasInfoChangeReq(RRC_NAS_MASK_PTMSI_RAI);                 /* 通知RRC NAS层信息变化                    */

#if (FEATURE_ON == FEATURE_PTM)
            /* 工程菜单打开后，PTMSI发生改变需要上报给OM */
            NAS_GMM_SndAcpuOmChangePtmsi();
#endif
        }

        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_POWEROFF;     /* 清除保留标志                             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPowerOff;
        Gmm_MemFree(pAddr);
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPowerOff = (VOS_UINT32)VOS_NULL_PTR;
    }

    Gmm_HoldBufferFree();                                                       /* 清除保留消息                             */

    return;                                                                     /* 返回                                     */
}

/*****************************************************************************
 函 数 名  : GMM_ComCheckRauIntegrityProtection
 功能描述  : RAU Accept消息完整性检查
 输入参数  : VOS_UINT8 *pucMsgContent
             VOS_UINT16  usMsgLen
 输出参数  : 无
 返 回 值  : GMM_TRUE--RAU ACCEPT消息完整性检查通过
             GMM_FALSE--RAU ACCEPT消息完整性检查不通过
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2008年8月4日
   作    者   : luojian id:107747
   修改内容   : 新生成函数
 2.日    期   : 2011年1月18日
   作    者   : o00132663
   修改内容   : DTS2011011803318,周期性RAU流程中无完整性保护，RAU ACCEPT中分配了新的P-TMSI，消息应该被丢弃
 3.日    期   : 2011年3月3日
   作    者   : z00161729
   修改内容   : DTS2011021201997:PS、CS完整性保护是否开启由GMM和MM分开维护,MMC不再维护
 4.日    期   : 2011年7月27日
   作    者   : h44270
   修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
 5. 日    期   : 2012年7月17日
    作    者   : z00161729
    修改内容   : DTS2012071606177:W(LAI1)-L(TAI2/LAI2 ISR激活CS LAI改变)-W(LAI1网络模式I)需要
                 发起联合rau
*****************************************************************************/
VOS_UINT32 GMM_ComCheckRauIntegrityProtection(VOS_UINT8 *pucMsgContent,
                                                VOS_UINT32  ulMsgLen)
{
    GMM_RAI_STRU                        stRauRai;
    VOS_UINT8                           aucRauPtmsi[NAS_MML_MAX_PTMSI_LEN];
    VOS_UINT8                           ucPtmsiAvail;
    VOS_UINT32                          ulIeCount;
    VOS_UINT32                          ulIntegrityCheckResult;

    /* 完整性保护已经启动 */
    if (NAS_MML_RRC_INTEGRITY_PROTECT_ACTIVE == g_MmSubLyrShare.GmmShare.ucPsIntegrityProtect)
    {
        ulIntegrityCheckResult = GMM_TRUE;
    }
    /* 完整性保护没有启动 */
    else
    {
        ulIntegrityCheckResult = GMM_FALSE;

        /*ROUTING AREA UPDATE ACCEPT (at periodic routing area update with no
        change of routing area or temporary identity)*/
        if (GMM_FALSE == g_GmmRauCtrl.ucPeriodicRauFlg)
        {
            return GMM_FALSE;
        }

        /* 获取 RAU ACCEPT消息 RAI参数*/
        Gmm_FillRaiForRcv(&stRauRai, &pucMsgContent[4]);

        ucPtmsiAvail = GMM_FALSE;
        PS_MEM_SET(aucRauPtmsi, 0x00, NAS_MML_MAX_PTMSI_LEN);

        /* 获取 RAU ACCEPT消息 PTMSI参数*/
        for (ulIeCount=10; ulIeCount < ulMsgLen; ulIeCount++ )
        {
            if (GMM_IEI_P_TMSI_SIGNATURE == pucMsgContent[ulIeCount])
            {
                /* P-TMSI signature为4个字节，此处加3，For循环再加1 */
                ulIeCount += 3;
                continue;
            }

            if (GMM_IEI_ALLOCATED_PTMSI == pucMsgContent[ulIeCount])
            {
                if ( GMM_MOBILE_ID_TMSI_PTMSI == (pucMsgContent[ulIeCount+2] & 0x07) )
                {
                    ucPtmsiAvail = GMM_TRUE;
                    PS_MEM_CPY(aucRauPtmsi, &pucMsgContent[ulIeCount+3], NAS_MML_MAX_PTMSI_LEN);
                }
                break;
            }
        }

        /* 如果RAI没有发生改变 */
        if (GMM_TRUE == Gmm_Com_CmpRai(&stRauRai, &g_GmmGlobalCtrl.SysInfo.Rai, g_GmmGlobalCtrl.ucNetMod))
        {
            /* 没有分配PTMSI */
            if (GMM_FALSE == ucPtmsiAvail)
            {
                ulIntegrityCheckResult = GMM_TRUE;
            }
            /* 分配的PTMSI和以前相同 */
            else if ( 0 == VOS_MemCmp(aucRauPtmsi,NAS_MML_GetUeIdPtmsi(),NAS_MML_MAX_PTMSI_LEN) )
            {
                ulIntegrityCheckResult = GMM_TRUE;
            }
            else
            {
            }
        }
    }
    return ulIntegrityCheckResult;
}

/*****************************************************************************
 函 数 名  : GMM_ComCheckIntegrityProtection
 功能描述  : 完整性检查
 输入参数  : VOS_UINT8 *pucMsgContent
             VOS_UINT16  usMsgLen
 输出参数  : 无
 返 回 值  : GMM_TRUE -- 完整性检查通过
             GMM_FALSE -- 完整性检查不通过
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年8月4日
    作    者   : luojian id:107747
    修改内容   : 新生成函数
  2.日    期   : 2011年3月3日
    作    者   : z00161729
    修改内容   : DTS2011021201997:PS、CS完整性保护是否开启由GMM和MM分开维护,MMC不再维护
  3.日    期   : 2013年11月18日
    作    者   : w00167002
    修改内容   : DTS2013112006986:控制在3G TDD模式下是否需要开启SMC验证标记:中国移动拉萨网络设备在
                 TD下不发起SMC流程。
*****************************************************************************/
VOS_UINT32 GMM_ComCheckIntegrityProtection(VOS_UINT8 *pucMsgContent,
                                            VOS_UINT32  ulMsgLen)
{
    VOS_UINT8                           ucPD;
    VOS_UINT8                           ucMsgType;
    VOS_UINT32                          ulIntegrityCheckResult;

    /* 快速接入模式属于测试模式，不进行完整性检查 */
    if ( VOS_TRUE == NAS_MML_IsQuickStartFlg())
    {
        return GMM_TRUE;
    }

    /* 完整性检查仅适用于UMTS网络 */


    /* 完整性检查仅适用于UMTS网络 */
    if (NAS_MML_NET_RAT_TYPE_WCDMA != NAS_MML_GetCurrNetRatType())
    {
        return GMM_TRUE;
    }

    if (VOS_FALSE == NAS_UTRANCTRL_IsUtranPsSmcNeeded())

    {
        return GMM_TRUE;
    }

    ucPD = pucMsgContent[0] & 0x0f;

    /* 完整性保护已经启动 */
    if (NAS_MML_RRC_INTEGRITY_PROTECT_ACTIVE == g_MmSubLyrShare.GmmShare.ucPsIntegrityProtect)
    {
        ulIntegrityCheckResult = GMM_TRUE;
    }
    /* 完整性保护没有启动 */
    else
    {
        ulIntegrityCheckResult = GMM_FALSE;

        /*
        24.008 4.1.1.1 Except the messages listed below, no layer 3 signalling
        messages shall be processed by the receiving MM and GMM entities or
        forwarded to the CM entities, unless the security mode control procedure
        is activated for that domain. */
        if (GMM_PD_GMM == ucPD)
        {
            ucMsgType = pucMsgContent[1];
            switch (ucMsgType)
            {
                case GMM_MSG_AUTHENTICATION_AND_CIPHERING_REQUEST:
                case GMM_MSG_AUTHENTICATION_AND_CIPHERING_REJECT:
                case GMM_MSG_IDENTITY_REQUEST:
                case GMM_MSG_ATTACH_REJECT:
                case GMM_MSG_RAU_REJECT:
                case GMM_MSG_SERVICE_REJECT:
                    ulIntegrityCheckResult = GMM_TRUE;
                    break;
                case GMM_MSG_RAU_ACCEPT:
                    ulIntegrityCheckResult =
                     GMM_ComCheckRauIntegrityProtection(pucMsgContent,ulMsgLen);
                    break;

                case GMM_MSG_DETACH_ACCEPT:
                    /* DETACH ACCEPT (for non power-off) */
                    if ((GMM_GPRS_DETACH_POWEROFF != g_GmmGlobalCtrl.ucSpecProc)
                      && (GMM_COMBINED_DETACH_POWEROFF !=
                                            g_GmmGlobalCtrl.ucSpecProc))
                    {
                        ulIntegrityCheckResult = GMM_TRUE;
                    }
                    break;
                default:
                    break;
            }
        }
        else if (GMM_PD_RSV_FOR_TEST == ucPD)
        {
            ulIntegrityCheckResult = GMM_TRUE;
        }
        else
        {
        }
    }
    return ulIntegrityCheckResult;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_IsNeedProcPtmsiReallocationCommandMsg
 功能描述  : 是否需要处理ptmsi重分配消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 需要
             VOS_FALSE - 不需要
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年6月5日
   作    者   : z00161729
   修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_UINT32 NAS_GMM_IsNeedProcPtmsiReallocationCommandMsg (VOS_VOID)
{
    /* 24008 4.7.5.1.5 章节描述如下:
    Routing area updating and P-TMSI reallocation procedure collision
    - If the MS receives a P-TMSI REALLOCATION C0MMAND message before the routing area
    updating procedure has been completed, the P-TMSI reallocation procedure shall
    be aborted and the routing area updating procedure shall be progressed.*/
    if (NAS_GMM_SPEC_PROC_TYPE_RAU == (g_GmmGlobalCtrl.ucSpecProc & NAS_MML_OCTET_HIGH_FOUR_BITS))
    {
        return VOS_FALSE;
    }

    /* 24008_CR1941_(Rel-11)_C1-113955 24008 4.7.4.1.4章节描述如下:
    GPRS detach containing other causes than "power off" and containing detach type "IMSI detach":
    -   If the MS receives a message used in a GMM common procedure before the GPRS detach
    procedure has been completed, both the GMM common procedure and the GPRS detach procedure
    shall continue. detach流程中如果detach 类型不为imsi detach则不处理 */
    if ((NAS_GMM_SPEC_PROC_TYPE_DETACH == (g_GmmGlobalCtrl.ucSpecProc & NAS_MML_OCTET_HIGH_FOUR_BITS))
     && (GMM_DETACH_WITH_IMSI != g_GmmGlobalCtrl.ucSpecProc))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : NAS_GMM_IsNeedProcStatusMsg
 功能描述  : 是否需要处理gmm status消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 需要
             VOS_FALSE - 不需要
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年6月5日
   作    者   : z00161729
   修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_UINT32 NAS_GMM_IsNeedProcStatusMsg (VOS_VOID)
{
    /* 24008_CR1941_(Rel-11)_C1-113955 24008 4.7.4.1.4章节描述如下:
    GPRS detach containing other causes than "power off" and containing detach type "IMSI detach":
    -   If the MS receives a message used in a GMM common procedure before the GPRS detach
    procedure has been completed, both the GMM common procedure and the GPRS detach procedure
    shall continue. */

    /* detach流程中如果detach 类型不为imsi detach则不处理 */
    if ((NAS_GMM_SPEC_PROC_TYPE_DETACH == (g_GmmGlobalCtrl.ucSpecProc & NAS_MML_OCTET_HIGH_FOUR_BITS))
     && (GMM_DETACH_WITH_IMSI != g_GmmGlobalCtrl.ucSpecProc))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_GMM_IsNeedProcGmmInfoMsg
 功能描述  : 是否需要处理gmm infomation消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 需要
             VOS_FALSE - 不需要
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年6月5日
   作    者   : z00161729
   修改内容   : 24301 R11 CR升级项目修改
*****************************************************************************/
VOS_UINT32 NAS_GMM_IsNeedProcGmmInfoMsg (VOS_VOID)
{
    /* 24008_CR1941_(Rel-11)_C1-113955 24008 4.7.4.1.4章节描述如下:
    GPRS detach containing other causes than "power off" and containing detach type "IMSI detach":
    -   If the MS receives a message used in a GMM common procedure before the GPRS detach
    procedure has been completed, both the GMM common procedure and the GPRS detach procedure
    shall continue. */

    /* detach流程中如果detach 类型不为imsi detach则不处理 */
    if ((NAS_GMM_SPEC_PROC_TYPE_DETACH == (g_GmmGlobalCtrl.ucSpecProc & NAS_MML_OCTET_HIGH_FOUR_BITS))
     && (GMM_DETACH_WITH_IMSI != g_GmmGlobalCtrl.ucSpecProc))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}



/*******************************************************************************
  Module   : Gmm_RcvRrmmDataInd
  Function : RRMM_DATA_IND接收处理
  Input    : VOS_VOID *pRcvMsg  接收消息使用的头地址定义
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1.  张志勇  2003.12.09  新规作成
    2.日    期   : 2006年12月5日
      作    者   : luojian 60022475
      修改内容   : Maps3000接口修改
    3.日    期  : 2007年12月21日
      作    者  : l00107747
      修改内容  : 问题单号:A32D13951
    4.日    期   : 2009年09月25日
      作    者   : l00130025
      修改内容   : 问题单号:AT2D14675,RAU/Attach过程中，list搜网失败
    5. 日    期   : 2010年10月16日
       作    者   : o00132663
       修改内容   : DTS2010101401399:收到小区重选结束消息后，GMM通知LL清除除CM层以外的信令
    6. 日    期   : 2011年05月11日
       作    者   : f00179208
       修改内容   : DTS2011051003575:G模GCF用例:44.2.3.2.5-1失败。
                    RAU被拒后，立即发起了搜网，导致层2没有将RLC ACK发送到仪器，因此仪器重发了RAU Reject
    7.日    期  : 2013年03月13日
      作    者  : z00214637
      修改内容  : BodySAR项目
    8.日    期   : 2013年3月30日
      作    者   : l00167671
      修改内容   : 主动上报AT命令控制下移至C核
    9.日    期   : 2015年6月5日
      作    者   : z00161729
      修改内容   : 24008 23122 R11 CR升级项目修改

*******************************************************************************/
VOS_VOID Gmm_RcvRrmmDataInd(
                        VOS_VOID *pRcvMsg                                       /* 接收消息使用的头地址定义                 */
                        )
{
    RRMM_DATA_IND_FOR_PCLINT_STRU  *pRrmmDataInd;
    NAS_MSG_FOR_PCLINT_STRU        *pNasMsg;
    NAS_MSG_STRU                   *pGmmStatus;

    pRrmmDataInd = (RRMM_DATA_IND_FOR_PCLINT_STRU *)pRcvMsg;                    /* 得到消息的首地址                         */
    if ( RRC_NAS_CS_DOMAIN == pRrmmDataInd->ulCnDomainId )
    {                                                                           /* 错误的消息                               */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRrmmDataInd:WARNING: CS data is received in RRMM_DATA_IND");
        return;
    }
    if (GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
    {                                                                           /* 当前没有信令                             */
        if (GMM_FALSE == GMM_IsCasGsmMode())
        {                                                                       /*3G下如果当前没有信令，直接返回。2G下信令连接标志始终有效 */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRrmmDataInd:WARNING: Signalling connection is not existed");
            return;
        }
    }

    pNasMsg = &pRrmmDataInd->RcvNasMsg;                                         /* 得到NAS消息结构的地址                    */
    if ((GMM_TC_ACTIVE == g_GmmGlobalCtrl.ucState)
        && (GMM_PD_RSV_FOR_TEST != (pNasMsg->aucNasMsg[0] & 0x0F)))
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRrmmDataInd:WARNING: In TC_ACTIVE, other NT message than TC is omitted");
        Gmm_MemFree(pRcvMsg);                                                   /* 释放接收到的消息内存                     */
        return;
    }

    if (2 > pNasMsg->ulNasMsgSize)
    {                                                                           /* 消息过短                                 */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRrmmDataInd:WARNING: Message from NT is too short");
        return;
    }

    if (GMM_FALSE == GMM_ComCheckIntegrityProtection(pNasMsg->aucNasMsg, pNasMsg->ulNasMsgSize))
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRrmmDataInd:WARNING: Integrity Check Fail");
    }
    else
    {

        /* 收到了从网侧来的NAS层消息 */
        g_GmmGlobalCtrl.stGmmLinkCtrl.ucSmcOrFirstNasMsgRcvdFlg = VOS_TRUE;

        switch (pNasMsg->aucNasMsg[0] & 0x0F)
        {                                                                       /* 按照Protocol discriminator分发           */
        case GMM_PD_GMM:
            if (0 != ( pNasMsg->aucNasMsg[0] & 0xF0))
            {
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRrmmDataInd:WARNING: NT message is invalid");
                return;
            }

            GMM_ReportN2MOtaMsg((NAS_MSG_STRU *)pNasMsg);


            switch (pNasMsg->aucNasMsg[1])
            {                                                                   /* 按照Message type分发                     */
            case GMM_MSG_ATTACH_ACCEPT:
                if (GMM_TRUE == GMM_IsCasGsmMode())
                {
                    /* 2G网络下，通知GAS层GMM过程完成，GRR将停止non_DRX状态 */

                    /* deleted by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */

                    /* deleted by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

                    NAS_MML_SetPsTbfStatusFlg(VOS_TRUE);
                }

                Gmm_RcvAttachAcceptMsg(pNasMsg);                                /* 空口消息Attach accept的接收处理          */
                break;
            case GMM_MSG_ATTACH_REJECT:
                if (GMM_TRUE == GMM_IsCasGsmMode())
                {/* 2G网络下，通知GAS层GMM过程完成，GRR将停止non_DRX状态 */

                    /* deleted by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */

                    /* deleted by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

                    NAS_MML_SetPsTbfStatusFlg(VOS_TRUE);
                }
                Gmm_RcvAttachRejectMsg(pNasMsg);                                /* 空口消息Attach reject的接收处理          */
                break;
            case GMM_MSG_DETACH_REQUEST:
                if(GMM_TRUE == GMM_IsCasGsmMode())
                {
                    NAS_MML_SetPsTbfStatusFlg(VOS_TRUE);
                }
                Gmm_RcvDetachRequestMsg(pNasMsg);                               /* 空口消息Detach request的接收处理         */
                break;
            case GMM_MSG_DETACH_ACCEPT:
                Gmm_RcvDetachAcceptMsg(pNasMsg);                                /* 空口消息Detach accept的接收处理          */
                break;
            case GMM_MSG_RAU_ACCEPT:
                if (GMM_TRUE == GMM_IsCasGsmMode())
                {
                    /* deleted by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */

                    /* deleted by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

                    NAS_MML_SetPsTbfStatusFlg(VOS_TRUE);
                }
                Gmm_RcvRoutingAreaUpdateAcceptMsg(pNasMsg);                     /* 空口消息Routing area update accept的接收 */
                break;
            case GMM_MSG_RAU_REJECT:
                if (GMM_TRUE == GMM_IsCasGsmMode())
                {
                    /* deleted by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */

                    /* deleted by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

                    NAS_MML_SetPsTbfStatusFlg(VOS_TRUE);
                }
                Gmm_RcvRoutingAreaUpdateRejectMsg(pNasMsg);                     /* 空口消息Routing area update reject的接收 */
                break;
            case GMM_MSG_SERVICE_ACCEPT:
                Gmm_RcvServiceAcceptMsg(pNasMsg);                               /* 空口消息Service Accept的接收处理         */
                break;
            case GMM_MSG_SERVICE_REJECT:
                Gmm_RcvServiceRejectMsg(pNasMsg);                               /* 空口消息Service Reject的接收处理         */
                break;
            case GMM_MSG_P_TMSI_REALLOCATION_COMMAND:
                if (VOS_TRUE == NAS_GMM_IsNeedProcPtmsiReallocationCommandMsg())
                {
                    Gmm_RcvPtmsiReallocationCommandMsg(pNasMsg);                /* 空口消息P-TMSI reallocation command接收  */
                }
                break;
            case GMM_MSG_AUTHENTICATION_AND_CIPHERING_REQUEST:
                Gmm_RcvAuthenAndCipherRequestMsg(pNasMsg);                      /* Authentication and ciphering request接收 */
                break;
            case GMM_MSG_AUTHENTICATION_AND_CIPHERING_REJECT:
                Gmm_RcvAuthenAndCipherRejectMsg(pNasMsg);                       /* Authentication and ciphering reject接收  */
                break;
            case GMM_MSG_IDENTITY_REQUEST:
                Gmm_RcvIdentityRequestMsg(pNasMsg);                             /* 空口消息Identity request的接收处理       */
                break;
            case GMM_MSG_GMM_STATUS:
                if (VOS_TRUE == NAS_GMM_IsNeedProcStatusMsg())
                {
                    Gmm_RcvGmmStatusMsg(pNasMsg);                               /* 空口消息GMM Status的接收处理 */
                }
                break;
            case GMM_MSG_GMM_INFORMATION:
                if (VOS_TRUE == NAS_GMM_IsNeedProcGmmInfoMsg())
                {
                    Gmm_RcvGmmInformationMsg(pNasMsg);                          /* 空口消息GMM Information的接收处理 */
                }
                break;
            default :
                pGmmStatus = Gmm_GmmStatusMsgMake(
                    NAS_MML_REG_FAIL_CAUSE_MSG_NONEXIST_NOTIMPLEMENTE);

                Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRrmmDataInd:WARNING: The MsgType is Abnormal");
                break;
            }
            break;

        case GMM_PD_SM:
            Gmm_SndSmDataInd(pNasMsg);                                          /* 原语GMMSM_DATA_IND的发送处理             */
            break;

        case GMM_PD_SMS:
            if (GMM_NULL_PROCEDURE == g_GmmGlobalCtrl.ucSpecProc)
            {
                Gmm_SndSmsUnitdataInd(pNasMsg);                                 /* 原语PMMSMS_UNITDATA_IND的发送处理        */
            }
            break;

        case GMM_PD_RSV_FOR_TEST:
            Gmm_SndTcDataInd(pNasMsg);
            break;

        default :
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRrmmDataInd:WARNING: Protocol discriminator is Error");
            break;
        }
    }

    return;
}

/*******************************************************************************
  Module   : GMM_RcvMmcRelReq
  Function : 收到原语MMCGMM_REL_REQ的处理
  Input    : VOS_VOID   *pMsg                     消息指针
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
  1. 日    期   : 2008年12月7日
     作    者   : l00130025
     修改内容   : 根据问题单号：AT2D07018,有链接存在时SYSCFG设置时间过长
  2. 日    期   : 2009年10月3日
     作    者   : l00130025
     修改内容   : 根据问题单号：AT2D14890,W网络模式I下,CS detach后设置SYSCFG失败
  3. 日    期   : 2010年10月11日
     作    者   : z00161729
     修改内容   : 问题单号DTS2010100900058:GMM收到MMC的REL_REQ消息时需要清除attch/RAU计数器,因为如果attach/RAU
                     计数器超过最大次数,MMC会发起list搜网,导致不相应用户的手动搜网请求
  4. 日    期   : 2011年7月11日
     作    者   : sunxibo 46746
     修改内容   : V7R1 phase II,autoplmnsrch状态机调整为PlmnSelection状态机
  5. 日    期   : 2011年7月14日
     作    者   : zhoujun 40661
     修改内容   : 更新MML_CTX中的链接存在状态
  6. 日    期   : 2011年11月14日
     作    者   : w00167002
     修改内容   : 背景搜注册被指定搜打断，MMC向GMM主动发送链接释放请求，此时需要
                   记录此前的GMM状态，当指定搜的网络和BG搜尝试注册时的网络相同时，
                   但和上次成功注册的网络不一样时，也需要进行路由区更新。
  7. 日    期   : 2012年11月7日
     作    者   : s00217060
     修改内容   : DTS2012060507813: GU下存在PS业务时，MMC向MM/GMM发送释放请求，
                   GMM给接入层发送释放请求，连接释放后，下发SYSCFG
  8. 日    期   : 2013年06月27日
     作    者   : l65478
     修改内容   : DTS2013062406563:EMO的卡在OOS时没有驻留到SBM的网络
*******************************************************************************/
VOS_VOID GMM_RcvMmcRelReq(
    VOS_VOID                           *pMsg                                    /* 消息指针                                 */
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    enCurRat = NAS_MML_GetCurrNetRatType();

    /* GU下存在PS业务时，MMC向MM/GMM发送释放请求，
       GMM给接入层发送释放请求，连接释放后，下发SYSCFG */

    /* 通知WRR释放连接.当状态在搜网状态时,说明原来已经通知了连接释放,不需要重复通知 */
    if (((GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
      || (GMM_RRC_RRMM_EST_CNF_FLG == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)))
     && (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat)
     && (GMM_REGISTERED_PLMN_SEARCH != g_GmmGlobalCtrl.ucState)
     && (GMM_DEREGISTERED_PLMN_SEARCH != g_GmmGlobalCtrl.ucState))
    {
        Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);
        Gmm_TimerStart(GMM_TIMER_WAIT_CONNECT_REL);
    }

    if ((VOS_TRUE == NAS_MML_GetPsTbfStatusFlg())
     && (NAS_MML_NET_RAT_TYPE_GSM == enCurRat))
    {
        Gmm_TimerStart(GMM_TIMER_WAIT_CONNECT_REL);
    }

    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* 根据状态分发                             */
        case GMM_REGISTERED_INITIATED:
            NAS_GMM_RcvMmcRelReq_RegInit();
            break;
        case GMM_DEREGISTERED_INITIATED:
            NAS_GMM_RcvMmcRelReq_DeregInit();
            break;
        case GMM_ROUTING_AREA_UPDATING_INITIATED:
            NAS_GMM_RcvMmcRelReq_RauInit();
            break;
        case GMM_REGISTERED_IMSI_DETACH_INITIATED:
            NAS_GMM_RcvMmcRelReq_RegImsiDtchInit();
            break;
        case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
            NAS_GMM_RcvMmcRelReq_SuspendWaitSysinfo();
            break;
        case GMM_GPRS_SUSPENSION:
        case GMM_SUSPENDED_GPRS_SUSPENSION:
            Gmm_ComStaChg(gstGmmSuspendCtrl.ucPreState);
            break;
        default:
            break;
    }

    if (GMM_SUSPENDED_WAIT_FOR_SYSINFO == g_GmmGlobalCtrl.ucState)
    {
        g_GmmGlobalCtrl.ucPlmnSrchPreSta = gstGmmSuspendCtrl.ucPreState;
    }
    else
    {
        g_GmmGlobalCtrl.ucPlmnSrchPreSta = g_GmmGlobalCtrl.ucState;
    }

    if (0x10 == (g_GmmGlobalCtrl.ucState & 0xF0))
    {                                                                           /* 当前处于非注册状态                       */
        Gmm_ComStaChg(GMM_DEREGISTERED_PLMN_SEARCH);
    }
    else
    {                                                                           /* 当前处于注册状态                         */
        Gmm_ComStaChg(GMM_REGISTERED_PLMN_SEARCH);
    }

    /* 挂起用户面，保证数据不再下发 */
    NAS_GMM_SndRabmSysSrvChgInd(NAS_MML_NET_RAT_TYPE_BUTT,
                                VOS_FALSE,
                                VOS_TRUE,
                                VOS_TRUE);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_RcvMmcRelReq_RegInit
 功能描述  : 正在注册过程中接收到MMC模块的释放请求
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月11日
   作    者   : s46746
   修改内容   : 新生成函数
 2. 日    期   : 2014年06月12日
    作    者   : s00217060
    修改内容   : DTS2014061003286:TD2G重选，G下RAU过程中，用户指定搜TD的网络，网络不回应数据业务accept

*****************************************************************************/
VOS_VOID NAS_GMM_RcvMmcRelReq_RegInit()
{
    /* 停止注册过程中的相关定时器 */
    Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);
    Gmm_TimerStop(GMM_TIMER_T3310);
    Gmm_TimerStop(GMM_TIMER_T3318);
    Gmm_TimerStop(GMM_TIMER_T3320);

    /* 如果正在鉴权，则清除等待标志 */
    if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
    {
        Gmm_TimerStop(GMM_TIMER_PROTECT);
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;
    }


    /* 收到MMC的rel req,认为注册失败，增加注册失败的处理，与RauInit状态时收到rel_ind的处理类似 */
    g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg  = GMM_FALSE;                        /* 清除标志                                 */
    g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg = GMM_FALSE;                        /* 清除标志                                 */

    Gmm_AttachAttemptCounter(NAS_MML_REG_FAIL_CAUSE_RR_CONN_ABORT);             /* 调用attach attempt counter的处理         */

    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;

    g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;                                  /* 清除fallowon标志                         */

    NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);



    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_RcvMmcRelReq_DeregInit
 功能描述  : 正在去注册过程中接收到MMC模块的释放请求
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1. 日    期   : 2011年7月11日
    作    者   : s46746
    修改内容   : 新生成函数
 2. 日    期   : 2011年07月13日
    作    者   : w00166186
    修改内容   : V7R1 PHASE II ATTACH/DETACH调整
 3. 日    期   : 2013年8月7日
    作    者   : w00167002
    修改内容   : DTS2013080207367:在CS only时候，用户发起PDP激活，网络模式I时候，
                 会触发联合注册.用户发起PDP去激活，会导致PS域的去注册。收到网侧
                 的去注册成功后需要通知MM，否则MM当前在NORMAL SERVICE状态，不
                 触发T3212定时器的启动，长时间可能导致丢寻呼.
*****************************************************************************/
VOS_VOID NAS_GMM_RcvMmcRelReq_DeregInit()
{
    /* 停止去注册过程中的相关定时器 */
    Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);
    Gmm_TimerStop(GMM_TIMER_T3321);                                             /* 停T3321                                  */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* 停止T3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* 停止T3320                                */
    Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_RR_REL);

#if (FEATURE_LTE == FEATURE_ON)
    if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
    {
        NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
    }
#endif
    Gmm_TimerStop(GMM_TIMER_T3312);

    /* 如果正在鉴权，则清除等待标志 */
    if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
    {
        Gmm_TimerStop(GMM_TIMER_PROTECT);
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;
    }

    if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
    {
        if (GMM_UEID_P_TMSI_SIGNATURE
            == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask & GMM_UEID_P_TMSI_SIGNATURE))
        {
            /* Upon completion of an MS initiated detach procedure, the used P-TMSI signature shall be deleted */
            g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI_SIGNATURE;

            NAS_MML_InitUeIdPtmsiSignatureInvalid();
            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* 更新SIM卡信息                            */
            }
            else
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
            }
        }
    }
    else
    {
        if (GMM_DETACH_NORMAL_NETMODE_CHANGE != g_GmmGlobalCtrl.ucSpecProc)
        {
            NAS_MML_SetPsAttachAllowFlg( VOS_FALSE );
        }
    }

    /* 判断等待标志是否存在，如果存在则向MMC,MM发送DETACH信息 */
    if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
    {
        NAS_GMM_SndMmcMmDetachInfo();
    }
    else
    {
        /* 收到网侧的去注册成功后需要通知MM，否则MM不启动T3212定时器 */
        NAS_GMM_SndMmGprsDetachComplete();
    }

    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                            /* 将流程清空                               */

    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_GMM_RcvMmcRelReq_DeregInit:INFO: specific procedure ended");

    Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_RcvMmcRelReq_RauInit
 功能描述  : 正在路由区更新过程中接收到MMC模块的释放请求
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月11日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2014年06月12日
   作    者   : s00217060
   修改内容   : DTS2014061003286:TD2G重选，G下RAU过程中，用户指定搜TD的网络，网络不回应数据业务accept

*****************************************************************************/
VOS_VOID NAS_GMM_RcvMmcRelReq_RauInit()
{

    /* 停止路由区过程中的相关定时器 */
    Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);
    Gmm_TimerStop(GMM_TIMER_T3330);
    Gmm_TimerStop(GMM_TIMER_T3318);
    Gmm_TimerStop(GMM_TIMER_T3320);

    /* 收到MMC的rel req,认为注册失败，增加注册失败的处理，与RauInit状态时收到rel_ind的处理类似 */

    /* 完整性保护标志置为DEACTIVE */
    g_MmSubLyrShare.GmmShare.ucPsIntegrityProtect =
                                    NAS_MML_RRC_INTEGRITY_PROTECT_DEACTIVE;

    /* 清除RAU和LU标志 */
    g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg  = GMM_FALSE;                        /* 清除标志                                 */
    g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg = GMM_FALSE;                        /* 清除标志                                 */

    /* 如果正在鉴权，则清除等待标志 */
    NAS_GMM_ClearAuthInfo();


    /* 如果正在建链，清除等待标志 */
    if (GMM_RRC_RRMM_EST_CNF_FLG ==
        (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG))
    {
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_RRC_RRMM_EST_CNF_FLG;                  /* 清等待响应标志                           */
    }

    Gmm_RoutingAreaUpdateAttemptCounter(NAS_MML_REG_FAIL_CAUSE_RR_CONN_ABORT);         /* 调用RAU attempt counter的处理            */

    /* free之前保存的系统消息 */
    NAS_GMM_FreeGsmSysInfo();

    NAS_GMM_FreeWasSysInfo();


    if (GMM_RAU_FOR_NORMAL != gstGmmSuspendCtrl.ucRauCause)
    {
        GMM_RauFailureInterSys();
    }
    else
    {
        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_FAILURE);
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_RcvMmcRelReq_RegImsiDtchInit
 功能描述  : 正在IMSI去注册过程中接收到MMC模块的释放请求
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月11日
   作    者   : s46746
   修改内容   : 新生成函数
 2.日    期   : 2011年7月27日
   作    者   : h44270
   修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整

*****************************************************************************/
VOS_VOID NAS_GMM_RcvMmcRelReq_RegImsiDtchInit()
{
    /* 停止去注册过程中的相关定时器 */
    Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);
    Gmm_TimerStop(GMM_TIMER_T3321);                                             /* 停T3321                                  */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* 停止T3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* 停止T3320                                */

    /* 如果正在鉴权，则清除等待标志 */
    if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
    {
        Gmm_TimerStop(GMM_TIMER_PROTECT);
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;
    }

    /* Upon completion of an MS initiated detach procedure, the used P-TMSI signature shall be deleted */
    if (GMM_UEID_P_TMSI_SIGNATURE
        == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask & GMM_UEID_P_TMSI_SIGNATURE))
    {
        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI_SIGNATURE;

        NAS_MML_InitUeIdPtmsiSignatureInvalid();
        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* 更新SIM卡信息                            */
        }
        else
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
        }
    }

    if (GMM_TIMER_T3311_FLG
        == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3311_FLG))
    {                                                                           /* 存在被挂起的T3311                        */
        Gmm_TimerResume(GMM_TIMER_T3311);                                       /* 恢复T3311                                */
    }
    else if (GMM_TIMER_T3302_FLG
        == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3302_FLG))
    {                                                                           /* 存在被挂起的T3302                        */
        Gmm_TimerResume(GMM_TIMER_T3302);                                       /* 恢复T3302                                */
    }
    else
    {
#if (FEATURE_LTE == FEATURE_ON)
        if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
        {
            NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
        }
#endif
        Gmm_TimerStart(GMM_TIMER_T3312);                                        /* 起T3312                                  */
    }

    /* 判断等待标志是否存在，如果存在则向MMC,MM发送DETACH信息 */
    if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
    {
        NAS_GMM_SndMmcMmDetachInfo();
    }
    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                            /* 将流程清空                               */

    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_GMM_RcvMmcRelReq_RegImsiDtchInit:INFO: specific procedure ended");

    Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_RcvMmcRelReq_SuspendWaitSysinfo
 功能描述  : 正在异系统重选等待系统消息过程中接收到MMC模块的释放请求
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月11日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_GMM_RcvMmcRelReq_SuspendWaitSysinfo()
{
    /*异系统改变时通知RABM*/
    g_GmmRauCtrl.ucNpduCnt = 0x0;
    GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_HANDOVER, GMM_RABM_RAU_SUCCESS);
}


/*******************************************************************************
  Module   : Gmm_RcvMmcCoverageLostInd
  Function : 收到原语MMCGMM_COVERAGE_LOST_IND的处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
  1. 张志勇  2003.12.08  新规作成
  2. 日    期   : 2007年6月9日
     作    者   : luojian id:60022475
     修改内容   : 根据问题单号：A32D11579,清除CS Service Exit标志
  3. 日    期   : 2008年12月3日
     作    者   : ouyangfei id:00132663
     修改内容   : 根据问题单号：AT2D07165,在W下如果RR连接建立过程中丢网，不给WRR回RRMM_REL_REQ。
  4.日    期   : 2009年01月14日
    作    者   : l65478
    修改内容   : 问题单号：AT2D07971,在搜网状态下上报的接入技术错误
  5.日    期   : 2009年03月12日
    作    者   : ouyangfei id:00132663
    修改内容   : 问题单AT2D09683,丢网时，GMM上报服务状态异常导致MMC没有发起搜网。
  6. 日    期   : 2009年05月23日
     作    者   : L65478
     修改内容   : 问题单号:AT2D06770,RAU失败，因为GRM建链的原因是DATA，实际应该是信令
  7.日    期   : 2009年08月13日
    作    者   : l65478
    修改内容   : 问题单号：AT2D13662,3G下上报了out of coverage后总是会接着上报PS_Service
  8.日    期   : 2011年7月13日
    作    者   : w00176964
    修改内容   : V7R1 PhaseII阶段调整，向RABM指示RAB是否需要重建
  9.日    期   : 2011年7月27日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
 10.日    期   : 2011年7月28日
    作    者   : sunxibo 46746
    修改内容   : V7R1 phase II,autoplmnsrch状态机调整为PlmnSelection状态机
 11.日    期   : 2011年04月14日
    作    者   : 欧阳飞
    修改内容   : DTS2011041202700,在PS域卡无效后，状态又迁到受限服务，导致应用查询SYSINFO
                   时显示卡有效。
 12.日    期   : 2011年11月22日
    作    者   : w00166186
    修改内容   : DTS2011112101648,OOS等待系统消息超时后，信令链接标志没有清除，导致后续AVAILABLE
                 定时器超时后没有发起搜网
 13.日    期   : 2011年12月26日
    作    者   : w00166186
    修改内容   : DTS2011122305611,was连接态上报AREA_LOST没有立即搜网
 14.日    期   : 2012年05月04日
    作    者   : l65478
    修改内容   : DTS2012042802989,在出服务区时清除了缓存的SM消息,
                   重进服务区后PDP激活慢
 15.日    期   : 2011年12月28日
    作    者  : l00167671
    修改内容  : 修改问题单DTS2012122001075,问题单场景如下:
                 PS建链过程中发生RA改变，该场景中如果CS域有业务则PS域做RAU
                 会被不确定的推迟到CS连接释放时才做，修改此场景中的操作如下:
                 若CS域有业务则给WAS发送RRMM_REL_REQ请求，请WAS释放连接，
                 并保存系统消息。在收到WAS的RRMM_REL_IND时用保存的系统消息做RAU
 16.日    期   : 2013年07月23日
    作    者   : l65478
    修改内容   : DTS2013071809030,MMC收到RRMM_SUSPEND_REL_CNF后没有立刻处理缓存的SYSCFG
 17.日    期   : 2013年08月23日
    作    者   : f00179208
    修改内容   : ErrLog&FTM项目,PTMSI发生改变时上报给OM
 18.日    期   : 2013年10月05日
    作    者   : l65478
    修改内容   : DTS2013092509860:GPRS detach过程被BG搜索终止后,GMM又自动发起了注册
 19.日    期   : 2015年1月12日
    作    者   : s00217060
    修改内容   : Service_State_Optimize_PhaseI修改
  20.日    期   : 2015年6月5日
     作    者   : z00161729
     修改内容   : 24008 23122 R11 CR升级项目修改
*******************************************************************************/
VOS_VOID Gmm_RcvMmcCoverageLostInd(VOS_VOID)
{
    MSG_HEADER_STRU     *pNasMsgHeader;                                         /* 定义MSG_HEADER_STRU类型指针              */
    VOS_VOID            *pAddr;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    enCurRat = NAS_MML_GetCurrNetRatType();
    /* 丢网时, 指示RABM当前系统模式, 并挂起RABM */
    NAS_GMM_SndRabmSysSrvChgInd(enCurRat,
                                VOS_FALSE,
                                VOS_TRUE,
                                VOS_TRUE);

    /* 停HO等待系统消息定时器 */
    Gmm_TimerStop(GMM_TIMER_HO_WAIT_SYSINFO);

    /* 在GSM模式下，如果出服务区，此时需要挂起LLC，阻止用户面继续发送数据 */
    if(GMM_TRUE == GMM_IsCasGsmMode())
    {
        if (GMM_TRUE == gstGmmCasGlobalCtrl.ucTlliAssignFlg)
        {
            if(GMM_NOT_SUSPEND_LLC == gstGmmCasGlobalCtrl.ucSuspendLlcCause)
            {
                GMM_SndLlcSuspendReq();
            }
            gstGmmCasGlobalCtrl.ucSuspendLlcCause = GMM_SUSPEND_LLC_FOR_OUT_OF_SERVICE;
        }
    }

    if (RR_REL_CAUSE_DIRECTED_SINGNALING_CONNECTION_RE_ESTABLISHMENT
        == g_GmmGlobalCtrl.ucRelCause)
    {
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_NORMAL_EVENT;
    }

    g_MmSubLyrShare.GmmShare.ucPsSpecificFlg = GMM_SPECIFIC_OFF;

    g_GmmGlobalCtrl.ucCvrgAreaLostFlg     = GMM_TRUE;
    g_GmmGlobalCtrl.SysInfo.ucSysValidFlg = GMM_FALSE;
    g_GmmGlobalCtrl.CsInfo.ucCsTransFlg   = GMM_FALSE;
    g_GmmGlobalCtrl.ucCipherStartFlg      = GMM_FALSE;

    Gmm_TimerStop(GMM_TIMER_T3310);                                             /* 停止T3310                                */
    Gmm_TimerStop(GMM_TIMER_T3317);                                             /* 停止T3317                                */
    Gmm_TimerStop(GMM_TIMER_T3321);                                             /* 停止T3321                                */
    Gmm_TimerStop(GMM_TIMER_T3330);                                             /* 停止T3330                                */
    Gmm_TimerStop(GMM_TIMER_T3340);                                             /* 停止T3340                                */

    if (GMM_TIMER_PROTECT_FOR_SIGNALING_FLG
        == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_PROTECT_FOR_SIGNALING_FLG))

    {                                                                           /* 保护Timer是否在运行,是                   */
        Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);                         /* 停保护Timer                              */
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_RRC_RRMM_EST_CNF_FLG;                  /* 清等待cnf                                */
    }
    if (GMM_TIMER_T3311_FLG
        == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3311_FLG))
    {                                                                           /* 如果T3311在运行                          */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停止T3311                                */
    }

    if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
    {                                                                           /* 等待鉴权响应                             */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* 停保护定时器                             */
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;     /* 清除原语等待标志                         */
    }

    if (GMM_TC_ACTIVE == g_GmmGlobalCtrl.ucState)
    {
        Gmm_TimerResumeForTc(GMM_TIMER_ALL);                                    /* 恢复所有被挂起的Timer                    */
    }

    NAS_GMM_FreeGsmSysInfo();

    NAS_GMM_FreeWasSysInfo();

    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* 根据状态分发                             */
    case GMM_REGISTERED_INITIATED:
        Gmm_RcvCoverLost_RegInit();
        break;
    case GMM_DEREGISTERED_INITIATED:
        Gmm_RcvCoverLost_DeregInit();
        break;
    case GMM_ROUTING_AREA_UPDATING_INITIATED:
        Gmm_RcvCoverLost_RauInit();
        break;
    case GMM_SERVICE_REQUEST_INITIATED:
        Gmm_RcvCoverLost_ServReqInit();
        break;
    case GMM_REGISTERED_NORMAL_SERVICE:
        Gmm_RcvCoverLost_RegNmlServ();
        break;
    case GMM_REGISTERED_IMSI_DETACH_INITIATED:
        Gmm_RcvCoverLost_RegImsiDtchInit();
        break;
    case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
        Gmm_RcvCoverLost_SuspendWaitForSys();
        break;
    default:
        break;
    }

    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        g_GmmGlobalCtrl.ucSigConFlg = GMM_TRUE;
        NAS_MML_SetPsTbfStatusFlg(VOS_FALSE);

        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
    }
    else
    {
        g_GmmGlobalCtrl.ucSigConFlg = GMM_FALSE;
        NAS_MML_SetPsSigConnStatusFlg(VOS_FALSE);

        NAS_GMM_DeleteRandAndResInfoInPmmIdleMode();

        NAS_MML_SetRrcConnStatusFlg(VOS_FALSE);

        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
    }

    /* PS 域卡无效，状态不迁移 */
    if (GMM_DEREGISTERED_NO_IMSI != g_GmmGlobalCtrl.ucState)
    {
        if ((0x10 == (g_GmmGlobalCtrl.ucState & 0xF0))
            || (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState))
        {                                                                       /* 当前处于非注册状态                       */
            Gmm_ComStaChg(GMM_DEREGISTERED_NO_CELL_AVAILABLE);                  /* 调用状态的公共处理                       */
        }
        else
        {                                                                       /* 当前处于注册状态                         */
            Gmm_ComStaChg(GMM_REGISTERED_NO_CELL_AVAILABLE);                    /* 调用状态的公共处理                       */
        }
    }

    if (GMM_MSG_HOLD_FOR_POWEROFF
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_POWEROFF))
    {                                                                           /* 如果有保留的power off原语                */
        pNasMsgHeader =
            (MSG_HEADER_STRU *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPowerOff;    /* 得到消息头                               */

        if (MMCGMM_POWER_OFF_REQ == pNasMsgHeader->ulMsgName)
        {
            if (GMM_UEID_P_TMSI_SIGNATURE
                == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
                & GMM_UEID_P_TMSI_SIGNATURE))
            {                                                                   /* DETACH成功且使用了P_TMSI_SIGNATURE       */
                g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
                    &= ~GMM_UEID_P_TMSI_SIGNATURE;                              /* 清除P_TMSI_SIGNATURE                     */

                NAS_MML_InitUeIdPtmsiSignatureInvalid();
                if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
                {
                    Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* 更新SIM卡信息                            */
                }
                else
                {
                    Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
                }
            }
            Gmm_ComStaChg(GMM_NULL);                     /* 调用状态的公共处理                       */
            Gmm_SndMmcPowerOffCnf();                                            /* 向MMC发送MMCGMM_DETACH_CNF               */
            Gmm_ComVariantInit();
        }
        else
        {
            /* 判断等待标志是否存在，如果存在则向MMC,MM发送DETACH信息 */
            if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
            {
                if (GMM_WAIT_PS_DETACH == (g_GmmGlobalCtrl.stDetachInfo.enDetachType & GMM_WAIT_PS_DETACH))
                {
                    NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);
                }
                NAS_GMM_SndMmcMmDetachInfo();
            }
            Gmm_ComStaChg(GMM_DEREGISTERED_NO_IMSI);                            /* 调用状态的公共处理                       */
            g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                    /* 清当前流程                               */
            NAS_MML_SetSimPresentStatus(VOS_FALSE);                             /* 置SIM卡不存在标志                        */
            g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_IMSI;           /* 清除IMSI存在MASK                         */
            g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI;         /* 清除P_TMSI存在MASK                       */
            g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI_SIGNATURE;/* 清除P_TMSI_SIGNATURE存在MASK             */

            NAS_MML_InitUeIdPtmisInvalid();
            NAS_MML_InitUeIdPtmsiSignatureInvalid();

            Gmm_SndRrmmNasInfoChangeReq(RRC_NAS_MASK_PTMSI_RAI);                /* 通知RRC NAS层信息变化                    */

#if (FEATURE_ON == FEATURE_PTM)
            /* 工程菜单打开后，PTMSI发生改变需要上报给OM */
            NAS_GMM_SndAcpuOmChangePtmsi();
#endif
        }

        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_POWEROFF;     /* 清除保留标志                             */

        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPowerOff;
        Gmm_MemFree(pAddr);
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPowerOff = (VOS_UINT32)VOS_NULL_PTR;
    }

    if (GMM_TRUE == g_GmmGlobalCtrl.ucFollowOnFlg)
    {
        switch (g_GmmGlobalCtrl.ucSpecProcHold)
        {                                                                       /* 保留的specific流程                       */
        case GMM_SERVICE_REQUEST_DATA_IDLE:
        case GMM_SERVICE_REQUEST_DATA_CONN:
            Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);             /* 通知RABM结果                             */
            break;
        default:
            break;
        }
        g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;                    /* 清除保留流程                             */
        g_GmmGlobalCtrl.ucFollowOnFlg  = GMM_FALSE;                             /* 清除followon标志                         */
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

    }

    Gmm_FreeBufferMsgWithoutSm();

    g_GmmReqCnfMng.ucCnfMask            = 0;                                    /* 清所有等待cnf                            */
    g_GmmGlobalCtrl.ucSpecProc          = GMM_NULL_PROCEDURE;                   /* 清除当前流程                             */
    g_GmmGlobalCtrl.ucSpecProcHold      = GMM_NULL_PROCEDURE;                   /* 清除保留的过程                           */
    g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;                   /* 清除记录的CS通信中流程                   */
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcCoverageLostInd:INFO: specific procedure ended");

    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvMmcPlmnSearchInitiated
  Function : 收到原语MMCGMM_PLMN_SEARCH_INITIATED的处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2003.12.08  新规作成
    2. 日    期   : 2007年4月26日
       作    者   : liurui id:40632
       修改内容   : 根据问题单号：A32D10052
    3. 日    期   : 2007年07月02日
       作    者   : l65478
       修改内容   : 根据问题单号：A32D10052
    4. 日    期   : 2007年10月16日
       作    者   : l65478
       修改内容   : 根据问题单号：A32D11957
     5.日    期   : 2010年12月23日
       作    者   : s46746
       修改内容   : DTS2010122305821:GPRS数传过程中高优先级定时器超时会发起指定搜网
    6. 日    期   : 2010年12月24日
       作    者   : s46746
       修改内容   : 根据问题单号：DTS2010121400435，五次联合注册失败后，只进行了一次CS注册
    7. 日    期   : 2011年7月28日
       作    者   : sunxibo 46746
       修改内容   : V7R1 phase II,autoplmnsrch状态机调整为PlmnSelection状态机
    8. 日    期   : 2011年12月8日
       作    者   : s46746
       修改内容   : 问题单号：DTS2011111603445,接收到系统消息而且层2已经指派后才能恢复RABM
    9. 日    期   : 2011年12月7日
       作    者   : w00176964
       修改内容   : RRC链接清理
    10.日    期   : 2011年12月28日
       作    者  : l00167671
       修改内容  : 修改问题单DTS2012122001075,问题单场景如下:
                 PS建链过程中发生RA改变，该场景中如果CS域有业务则PS域做RAU
                 会被不确定的推迟到CS连接释放时才做，修改此场景中的操作如下:
                 若CS域有业务则给WAS发送RRMM_REL_REQ请求，请WAS释放连接，
                 并保存系统消息。在收到WAS的RRMM_REL_IND时用保存的系统消息做RAU
     11.日    期   : 2015年6月5日
        作    者   : z00161729
        修改内容   : 24008 23122 R11 CR升级项目修改
*******************************************************************************/
VOS_VOID Gmm_RcvMmcPlmnSearchInitiated(VOS_VOID)
{

    g_GmmGlobalCtrl.SysInfo.ucSysValidFlg = GMM_FALSE;                          /* 设置系统消息无效的标志                   */

    NAS_MML_SetRrcConnStatusFlg(VOS_FALSE);

    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        NAS_MML_SetPsTbfStatusFlg(VOS_FALSE);
    }
    else
    {
        NAS_MML_SetPsSigConnStatusFlg(VOS_FALSE);


        NAS_GMM_DeleteRandAndResInfoInPmmIdleMode();
    }

    if (GMM_NULL == g_GmmGlobalCtrl.ucState)
    {                                                                           /* 当前状态为NULL状态                       */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcPlmnSearchInitiated:WARNING: GMM state is VOS_NULL_PTR(Gmm_RcvMmcPlmnSearchInitiated)");
        return;
    }

    NAS_GMM_FreeGsmSysInfo();

    NAS_GMM_FreeWasSysInfo();

    g_GmmGlobalCtrl.SysInfo.ucNtType = NAS_MML_GetCurrNetRatType();

    if ((GMM_REGISTERED_PLMN_SEARCH != g_GmmGlobalCtrl.ucState)
     && (GMM_DEREGISTERED_PLMN_SEARCH != g_GmmGlobalCtrl.ucState))
    {
        if (GMM_SUSPENDED_WAIT_FOR_SYSINFO == g_GmmGlobalCtrl.ucState)
        {
            g_GmmGlobalCtrl.ucPlmnSrchPreSta = gstGmmSuspendCtrl.ucPreState;
        }
        else
        {
            g_GmmGlobalCtrl.ucPlmnSrchPreSta = g_GmmGlobalCtrl.ucState;
        }

        NAS_GMM_SndRabmSysSrvChgInd(NAS_MML_NET_RAT_TYPE_BUTT,
                                    VOS_FALSE,
                                    VOS_TRUE,
                                    VOS_TRUE);

        Gmm_ComPlmnSearchInit();
    }

    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvMmcStartReq
  Function : 收到原语MMCGMM_START_REQ的处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2003.12.08  新规作成
    2. 张志勇  2004.10.27  CK，IK存储结构变更

 3.日    期   : 2011年7月12日
   作    者   : zhoujun 40661
   修改内容   : SIM卡内容保存在MML中，删除GMM需要更新的内容
 4.日    期   : 2012年2月22日
   作    者   : w00199382
   修改内容   : B060项目移植防卡贴
 5.日    期   : 2012年5月15日
   作    者   : l00130025
   修改内容   : DTS2012041002516: L下默认承载存在数据连接时设置W only失败
 6.日    期   : 2014年4月8日
   作    者   : y00245242
   修改内容   : 为eCall feature增加
*******************************************************************************/
VOS_VOID Gmm_RcvMmcStartReq(VOS_VOID)
{
    VOS_UINT32                          i;
    VOS_UINT8                          *pucTmpTmsi;
    VOS_UINT32                          ulInvalidCnt;
    VOS_UINT8                          *pucTmpTmsiSig;
#if (FEATURE_ON == FEATURE_ECALL)
    NAS_MML_CALL_MODE_ENUM_UINT8        enCallMode;
#endif

    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNetRatType;                           /* 当前驻留的网络接入技术 */

    enNetRatType = NAS_MML_GetCurrNetRatType();

    Gmm_ComReset();                                                             /* 调用reset公共处理 */

    GMM_CasChangSysMode(enNetRatType);


#if (FEATURE_ON == FEATURE_LTE)

    /* 记录开机时，MS Radio Capability对应的接入技术列表 */
    PS_MEM_CPY(&(g_GmmGlobalCtrl.UeInfo.stRadioCpbRelatedRatList),
               NAS_MML_GetMsPrioRatList(),
               sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));
#endif


    /* 当前必然支持UMTS鉴权 */
    g_GmmAuthenCtrl.ucUmtsAuthFlg           = GMM_UMTS_AUTHEN_SUPPORTED;

    /* 当前必然支持GMM INFORMATION */
    g_GmmGlobalCtrl.UeInfo.ucSupportInfoFlg = GMM_SUPPORT_INFORMATION_MSG;

    Gmm_ComStaChg(GMM_DEREGISTERED_NO_CELL_AVAILABLE);

    /* Added by y00245242 for V3R3C60_eCall项目, 2014-4-15, begin */
#if (FEATURE_ON == FEATURE_ECALL)
    enCallMode = NAS_MML_GetCallMode();
#endif

    /* 设置当前PS域是否有效 */
    if ((VOS_TRUE == NAS_MML_GetSimPresentStatus())
#if (FEATURE_ON == FEATURE_ECALL)
     /* 根据3GPP 24.008 section 4.7:
     * 1. An eCall only mobile station shall not perform a normal or combined GPRS attach procedure.
     * 2. An eCall only mobile station shall not perform any kind of GPRS detach procedure.
     * 3. An eCall only mobile station shall not perform a normal or combined routing area updating procedure.
     * 这里，让GMM进入设置PS sim无效，使后续GMM进入NO_IMSI状态
     */

     && (NAS_MML_ECALL_ONLY != enCallMode)
#endif
       )
    /* Added by y00245242 for V3R3C60_eCall项目, 2014-4-15, end */
    {
        NAS_MML_SetSimPsRegStatus(VOS_TRUE);
        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask |= GMM_UEID_IMSI;
    }
    else
    {
        NAS_MML_SetSimPsRegStatus(VOS_FALSE);
        Gmm_SndMmcStartCnf();
        return;
    }

    /* 根据当前存储的TMSI是否有效，设定是否存在PTMSI */
    ulInvalidCnt = 0;
    pucTmpTmsi = NAS_MML_GetUeIdPtmsi();
    for (i = 0; i < NAS_MML_MAX_PTMSI_LEN; i++)
    {
        if (GMM_PTMSI_INVALID == pucTmpTmsi[i])
        {
            ulInvalidCnt++;
        }
    }
    if (NAS_MML_MAX_PTMSI_LEN == ulInvalidCnt)
    {                                                                           /* P-TMSI 无效                              */
        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI;
    }
    else
    {
        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask |= GMM_UEID_P_TMSI;
    }

    ulInvalidCnt = 0;
    pucTmpTmsiSig = NAS_MML_GetUeIdPtmsiSignature();

    ulInvalidCnt = 0;
    for (i=0; i<NAS_MML_MAX_PTMSI_SIGNATURE_LEN; i++)
    {
        if (GMM_PTMSI_SIGNATURE_INVALID == pucTmpTmsiSig[i])
        {
            ulInvalidCnt++;
        }
    }
    if (NAS_MML_MAX_PTMSI_SIGNATURE_LEN == ulInvalidCnt)
    {                                                                           /* P-TMSI signature无效                     */
        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI_SIGNATURE;

    }
    else
    {                                                                           /* P-TMSI signature有效                     */
        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask |= GMM_UEID_P_TMSI_SIGNATURE;    /* 设置相应存在标识                         */
    }


    /* 为了防止使用测试号段避过IMSI的检查，使得能够使用TMSI进行注册，需要
       进行防卡贴的判定，在NV项激活的情况下，特殊号段TMSI置为无效
    */
    if (VOS_TRUE == NAS_PreventTestImsiRegFlg())
    {
        NAS_MML_InitUeIdPtmisInvalid();

        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI;
    }


    Gmm_SndMmcStartCnf();

    return;                                                                     /* 返回                                     */
}

/*****************************************************************************
 函 数 名  : NAS_GMM_CheckSimStatusAffectAttach
 功能描述  : 检查ATTACH类型和USIM状态的冲突
 输入参数  : MMCGMM_ATTACH_REQ_STRU              *pstAttachReq
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月5日
   作    者   : 王毛/00166186
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_GMM_CheckSimStatusAffectAttach(
    MMCGMM_ATTACH_REQ_STRU             *pstAttachReq
)
{
    NAS_MML_SIM_STATUS_STRU            *pstUsimStatus;

    pstUsimStatus = NAS_MML_GetSimStatus();

    /* USIM CS域无效，MMC_GMM_ATTACH_TYPE_GPRS_IMSI类型转换为MMC_GMM_ATTACH_TYPE_GPRS */
    if ( ( MMC_GMM_ATTACH_TYPE_GPRS != pstAttachReq->enAttachType )
      && ( VOS_TRUE != pstUsimStatus->ucSimCsRegStatus ) )
    {
        NAS_NORMAL_LOG(WUEPS_PID_GMM, "NAS_GMM_IsAttachTypeConfictWithSimStatus:WARNING: CS USIM is invalid.");

        if ( MMC_GMM_ATTACH_TYPE_GPRS_IMSI == pstAttachReq->enAttachType )
        {
            pstAttachReq->enAttachType = MMC_GMM_ATTACH_TYPE_GPRS;
        }
        else
        {
            return VOS_TRUE;
        }
    }

    /* USIM PS域无效，直接回复ATTACH CNF */
    if ( ( MMC_GMM_ATTACH_TYPE_IMSI != pstAttachReq->enAttachType )
      && ( VOS_TRUE                 != pstUsimStatus->ucSimPsRegStatus ) )
    {
        NAS_NORMAL_LOG(WUEPS_PID_GMM,"NAS_GMM_IsAttachTypeConfictWithSimStatus:WARNING: PS USIM is invalid.");

        NAS_GMM_SndMmcAttachCnf();

        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_ModifyAttachType
 功能描述  : 修改attach类型
 输入参数  : MMCGMM_ATTACH_REQ_STRU              *pstAttachReq
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月5日
   作    者   : 王毛/00166186
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_GMM_ModifyAttachType(
    MMCGMM_ATTACH_REQ_STRU             *pstAttachReq
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampInfo;

    pstCampInfo = NAS_MML_GetCurrCampPlmnInfo();

    if (NAS_MML_NET_MODE_I != pstCampInfo->enNetworkMode)
    {
        /* 非网络模式I下收到CS ATTACH，GMM不处理 */
        if (MMC_GMM_ATTACH_TYPE_IMSI == pstAttachReq->enAttachType)
        {
            return VOS_TRUE;
        }

        /* 非网络模式I下收到CS+PS ATTACH，改为GPRS ATTACH */
        if (MMC_GMM_ATTACH_TYPE_GPRS_IMSI == pstAttachReq->enAttachType)
        {
            pstAttachReq->enAttachType = MMC_GMM_ATTACH_TYPE_GPRS;
        }
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_GMM_IsAttachRepeated
 功能描述  : 检查ATTACH冲突
 输入参数  : VOS_UINT32 enAttachType
             VOS_UINT32 ulOpID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年07月13日
   作    者   : W00166186
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_GMM_IsAttachRepeated(
    VOS_UINT32                          ulAttachType,
    VOS_UINT32                          ulOpID)
{
    /* 之前存在PS ATTACH 收到PS ATTACH，更新OPID后直接返回 */
    if ( ( GMM_WAIT_PS_ATTACH == g_GmmGlobalCtrl.stAttachInfo.enAttachType )
      && ( MMC_GMM_ATTACH_TYPE_GPRS == ulAttachType ) )
    {
        g_GmmGlobalCtrl.stAttachInfo.ulOpid = ulOpID;
        return VOS_TRUE;
    }

    /* 之前存在CS ATTACH 收到CS ATTACH，直接返回 */
    if ( ( GMM_WAIT_CS_ATTACH == g_GmmGlobalCtrl.stAttachInfo.enAttachType )
      && ( MMC_GMM_ATTACH_TYPE_IMSI == ulAttachType ) )
    {
        return VOS_TRUE;
    }

    if ( GMM_WAIT_CS_PS_ATTACH == g_GmmGlobalCtrl.stAttachInfo.enAttachType )
    {
        /* 之前存在PS ATTACH 收到CS+PS ATTACH，收到PS ATTACH更新OPID */
        if (MMC_GMM_ATTACH_TYPE_GPRS == (ulAttachType & MMC_GMM_ATTACH_TYPE_GPRS))
        {
            g_GmmGlobalCtrl.stAttachInfo.ulOpid = ulOpID;
        }

        return VOS_TRUE;
    }

    return VOS_FALSE;
}
/*******************************************************************************
 函 数 名  : NAS_GMM_IsDetachNotAcceptNeedAttach
 功能描述  : 在detach没有完成时，收到Attach请求时是否需要进行attach
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:detach没有完成时就需要attach；
             VOS_FALSE:不需要进行attach；

 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年3月5日
    作    者   : t00212959
    修改内容   : 新生成函数
  2.日    期   : 2013年6月6日
    作    者   : w00167002
    修改内容   : V9R1_SVLTE项目修改
*******************************************************************************/
VOS_UINT32 NAS_GMM_IsDetachNotAcceptNeedAttach(VOS_VOID)
{
    if (GMM_WAIT_PS_DETACH == g_GmmGlobalCtrl.stDetachInfo.enDetachType )
    {
        if ((GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
         && (GMM_DEREGISTERED_INITIATED == g_GmmGlobalCtrl.ucState))
        {
            NAS_GMM_SndMmGprsDetachComplete();

            NAS_GMM_SndMmcDetachCnf();
        }

        g_GmmGlobalCtrl.stDetachInfo.enDetachType &=~GMM_WAIT_PS_DETACH;


        /* GMM停止PS域的DETACH保护定时器 */
        Gmm_TimerStop(GMM_TIMER_PROTECT_PS_DETACH);

        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_GMM_IsAttachDetachConflicted
 功能描述  : 检查ATTACH和之前的DETACH是否冲突
 输入参数  : VOS_UINT32 ulAttachType
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月5日
   作    者   : 王毛/00166186
   修改内容   : 新生成函数
 2.日    期   : 2013年3月5日
   作    者   : t00212959
   修改内容   :DTS2013030407991
*****************************************************************************/
VOS_UINT32 NAS_GMM_IsAttachDetachConflicted(VOS_UINT32 ulAttachType)
{
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampInfo;

    pstCampInfo = NAS_MML_GetCurrCampPlmnInfo();

    /* 之前不存在DETACH流程 */
    if ( GMM_WAIT_NULL_DETACH == g_GmmGlobalCtrl.stDetachInfo.enDetachType )
    {
        return VOS_FALSE;
    }

    /* A+I模式 */
    if ( ( NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode() )
      && ( NAS_MML_NET_MODE_I    == pstCampInfo->enNetworkMode ) )
    {
        /* 网络模式I下,存DETACH流程,直接回复CNF */
        if ( MMC_GMM_ATTACH_TYPE_GPRS == (ulAttachType
                                        & MMC_GMM_ATTACH_TYPE_GPRS))
        {
            if (VOS_TRUE == NAS_GMM_IsDetachNotAcceptNeedAttach() )
            {
                return VOS_FALSE;
            }

            NAS_GMM_SndMmcAttachCnf();
        }
        return VOS_TRUE;
    }

    /* 非A+I模式 */
    if ( ( ( MMC_GMM_ATTACH_TYPE_GPRS == ulAttachType )
        && (GMM_WAIT_PS_DETACH == (g_GmmGlobalCtrl.stDetachInfo.enDetachType
                                 & GMM_WAIT_PS_DETACH ) ) )
      || ( MMC_GMM_ATTACH_TYPE_GPRS_IMSI == ulAttachType ) )
    {
        if (VOS_TRUE == NAS_GMM_IsDetachNotAcceptNeedAttach() )
        {
            return VOS_FALSE;
        }

        NAS_GMM_SndMmcAttachCnf();
        return VOS_TRUE;
    }

    /* IMSI ATTACH和之前的有冲突 */
    if ( (MMC_GMM_ATTACH_TYPE_IMSI == ulAttachType )
        && (GMM_WAIT_CS_DETACH == (g_GmmGlobalCtrl.stDetachInfo.enDetachType
                                 & GMM_WAIT_CS_DETACH ) ) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
/*****************************************************************************
 函 数 名  : NAS_GMM_CheckSigConnStatusAffectAttach
 功能描述  : 检查信令连接是否影响ATTACH
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年8月29日
    作    者   : w00166186
    修改内容   : 新生成函数
 2. 日    期   : 2013年6月18日
    作    者   : l65478
    修改内容   : 问题单号：DTS2013061406222,发起RAU时应该判断 CS的业务状态

*****************************************************************************/
VOS_UINT32 NAS_GMM_CheckSigConnStatusAffectAttach(
    MMCGMM_ATTACH_REQ_STRU             *pstAttachReq
)
{
    /* 检查是否由专有流程存在 */
    if((MM_COM_SRVST_NORMAL_SERVICE == Gmm_ComServiceSts())
    && ( MMC_MM_ATTACH_TYPE_GPRS == pstAttachReq->enAttachType )
    && (GMM_SPECIFIC_ON == g_MmSubLyrShare.GmmShare.ucPsSpecificFlg))
    {
        return VOS_TRUE;
    }

    if(((MM_COM_SRVST_NORMAL_SERVICE == Gmm_ComServiceSts())
      && (MM_NORMAL_SERVICE == g_MmGlobalInfo.ucMmServiceState ))
    && (MMC_MM_ATTACH_TYPE_GPRS_IMSI == pstAttachReq->enAttachType)
    && ((GMM_SPECIFIC_ON == g_MmSubLyrShare.GmmShare.ucPsSpecificFlg)
     || (MM_SPECIFIC_ON     == g_MmSubLyrShare.MmShare.ucCsSpecificFlg)))
    {
        return VOS_TRUE;
    }


    if (( MMC_MM_ATTACH_TYPE_IMSI == pstAttachReq->enAttachType )
     && (MM_SPECIFIC_ON     == g_MmSubLyrShare.MmShare.ucCsSpecificFlg))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
/*****************************************************************************
 函 数 名  : NAS_GMM_CheckAttachStatus
 功能描述  : 检查ATTACH状态
 输入参数  : MMCGMM_ATTACH_REQ_STRU             *pstAttachReq
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月13日
   作    者   : 王毛/00166186
   修改内容   : 新生成函数
 2.日    期   : 2013年3月6日
   作    者   : t00212959
   修改内容   : DTS2013030407991
 3.日    期   : 2013年3月30日
   作    者   : l00167671
   修改内容   : 主动上报AT命令控制下移至C核
*****************************************************************************/
VOS_UINT32 NAS_GMM_CheckAttachStatus(
    MMCGMM_ATTACH_REQ_STRU             *pstAttachReq
)
{
    VOS_UINT32                          ulRet;

    ulRet = VOS_TRUE;

    if ( MMC_GMM_ATTACH_TYPE_IMSI != pstAttachReq->enAttachType )
    {                                                                           /* 要求ATTACH PS域                          */
        NAS_MML_SetPsAttachAllowFlg(VOS_TRUE);
        g_GmmGlobalCtrl.ucUserPsAttachFlag  = VOS_TRUE;

        /* GMM处于注册状态，直接回复PS CNF */
        if ((GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta )
         && (GMM_DEREGISTERED_INITIATED != g_GmmGlobalCtrl.ucState))
        {                                                                       /* PS域已经ATTACH                           */
            NAS_GMM_SndMmcAttachCnf();

            if ( MMC_GMM_ATTACH_TYPE_GPRS_IMSI == pstAttachReq->enAttachType )
            {
                pstAttachReq->enAttachType = MMC_GMM_ATTACH_TYPE_IMSI;
                ulRet                      = VOS_FALSE;
            }
        }
        else
        {                                                                       /* PS域没有ATTACH                           */
            g_GmmGlobalCtrl.stAttachInfo.enAttachType |= GMM_WAIT_PS_ATTACH;
            g_GmmGlobalCtrl.stAttachInfo.ulOpid        = pstAttachReq->ulOpid;
            ulRet = VOS_FALSE;
        }
    }

    if ( MMC_GMM_ATTACH_TYPE_GPRS != pstAttachReq->enAttachType )
    {                                                                           /* 要求ATTACH CS域                          */
        /* CS 处于ATTACHED状态，修改GPRS_IMSI类型为GPRS ATTACH */
        if ( MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState )
        {                                                                       /* CS域已经ATTACH                           */
            ulRet = VOS_TRUE;

            /* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
            if ( NAS_MSCC_PIF_ATTACH_TYPE_GPRS_IMSI == pstAttachReq->enAttachType )
            {
                pstAttachReq->enAttachType  = MMC_GMM_ATTACH_TYPE_GPRS;
                ulRet                       = VOS_FALSE;
            }
			/* Modified by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

        }
        else
        {                                                                       /* CS域没有ATTACH                           */
            g_GmmGlobalCtrl.stAttachInfo.enAttachType |= GMM_WAIT_CS_ATTACH;
            ulRet                                      = VOS_FALSE;
        }
    }

    return ulRet;
}


/*****************************************************************************
 函 数 名  : NAS_GMM_RcvMmcAttachReq_PreProc
 功能描述  : GMM收到ATTACH的预处理
 输入参数  : MMCMM_ATTACH_REQ_STRU *pstmsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年6月30日
   作    者   : 王毛/00166186
   修改内容   : 新生成函数
 2.日    期   : 2011年11月16日
   作    者   : l00130025
   修改内容   : 问题单号:DTS2011111402583,opid值错误，导致AT挂死

*****************************************************************************/
VOS_UINT32 NAS_GMM_RcvMmcAttachReq_PreProc(
    MMCGMM_ATTACH_REQ_STRU             *pstmsg
)
{
    /* 判定是否需要处理该消息，无效消息返函数返回 */
    if ((MMC_MM_ATTACH_TYPE_IMSI      != pstmsg->enAttachType)
     && (MMC_MM_ATTACH_TYPE_GPRS      != pstmsg->enAttachType)
     && (MMC_MM_ATTACH_TYPE_GPRS_IMSI != pstmsg->enAttachType))
    {

        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_MM_RcvMmcAttachReq_PreProc:ATTACH TYPE INVALID");
        return VOS_TRUE;
    }


    if (MMC_MM_ATTACH_TYPE_IMSI != pstmsg->enAttachType)
    {
        g_GmmGlobalCtrl.stAttachInfo.ulOpid = pstmsg->ulOpid;
    }


    /* 检查是否有业务存在 */
    if (VOS_TRUE == NAS_GMM_CheckSigConnStatusAffectAttach(pstmsg))
    {
        if (MMC_MM_ATTACH_TYPE_IMSI != pstmsg->enAttachType)
        {
            NAS_GMM_SndMmcAttachCnf();
        }

        return VOS_TRUE;
    }

    /* 检查ATTACH类型是否和SIM卡状态冲突 */
    if ( VOS_TRUE == NAS_GMM_CheckSimStatusAffectAttach(pstmsg) )
    {
        return VOS_TRUE;
    }

    /* 根据网络模式调整ATTACH类型 */
    if ( VOS_TRUE == NAS_GMM_ModifyAttachType(pstmsg) )
    {
        return VOS_TRUE;
    }

    /* 检查是否和之前存在DETACH有冲突 */
    if ( VOS_TRUE == NAS_GMM_IsAttachDetachConflicted(pstmsg->enAttachType) )
    {
        return VOS_TRUE;
    }

    /* 检查之前存在ATTACH */
    if ( VOS_TRUE == NAS_GMM_IsAttachRepeated(pstmsg->enAttachType, pstmsg->ulOpid) )
    {
        return VOS_TRUE;
    }

    /* 检查注册情况 */
    if ( VOS_TRUE == NAS_GMM_CheckAttachStatus(pstmsg) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_CheckNeedBuffDetach
 功能描述  : 检查是否需要缓存DETACH
 输入参数  : MMCMM_DETACH_REQ_STRU *pstmsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月13日
   作    者   : 王毛/00166186
   修改内容   : 新生成函数
 2.日    期   : 2011年11月16日
   作    者   : l00130025
   修改内容   : 问题单号:DTS2011111402583,opid值错误，导致AT挂死

  3.日    期   : 2013年6月4日
    作    者   : w00167002
    修改内容   : V9R1_SVLTE:已经有DETACH流程进行时，网络模式I下缓存DETACH消息，
                 增加对缓存去注册消息的定时器保护。
*****************************************************************************/
VOS_UINT32 NAS_GMM_CheckNeedBuffDetach(
    MMCGMM_DETACH_REQ_STRU             *pstmsg
)
{
    MMCGMM_DETACH_REQ_STRU             *pstDetach;
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampInfo;

    pstCampInfo = NAS_MML_GetCurrCampPlmnInfo();

    if ( GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType )
    {
        /* 已经有DETACH流程进行时，网络模式I下缓存DETACH消息 */
        if ( ( NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode() )
          && ( NAS_MML_NET_MODE_I    == pstCampInfo->enNetworkMode) )
        {
            pstDetach = (MMCGMM_DETACH_REQ_STRU *)Gmm_MemMalloc(sizeof(MMCGMM_DETACH_REQ_STRU));
            if ( VOS_NULL_PTR == pstDetach )
            {
                  PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "NAS_GMM_CheckNeedBuffDetach:ERROR: Allocate memory error in Gmm_RcvMmcDetachReq");
                  return VOS_TRUE;
            }

            g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_DETACH;    /* 置原语缓存标志                           */
            g_GmmGlobalCtrl.stDetachInfo.ulOpid = pstmsg->ulOpid;

            Gmm_MemCpy(pstDetach, pstmsg, sizeof(MMCGMM_DETACH_REQ_STRU));
            g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach = (VOS_UINT32)pstDetach;       /* 缓存原语                                 */
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
/*****************************************************************************
 函 数 名  : NAS_GMM_ProcPsDetach
 功能描述  : GMM处理pS DETACH
 输入参数  : VOS_UINT32 ulOpID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月15日
    作    者   : 王毛/00166186
    修改内容   : 新生成函数
  2.日    期   : 2011年11月16日
    作    者   : l00130025
    修改内容   : 问题单号:DTS2011111402583,opid值错误，导致AT挂死

  3.日    期   : 2013年6月4日
    作    者   : w00167002
    修改内容   : V9R1_SVLTE:当前PDP激活时候，如果是SYSCFG设置的PS去注册，也进行
                 PS去注册。
  4.日    期   : 2013年6月11日
    作    者   : w00167002
    修改内容   : V9R1_SVLTE:检视意见修改，在预处理收到DETACH时候，就启动DETACH的
                 保护定时器，在回复MMC的detach CNF时候停止保护定时器。
                 修改函数入参。
  5.日    期   : 2015年1月15日
    作    者   : z00161729
    修改内容   : AT&T 支持DAM特性修改
*****************************************************************************/

VOS_UINT32 NAS_GMM_ProcPsDetach(
    MMCGMM_DETACH_REQ_STRU             *pstmsg
)
{

    g_GmmGlobalCtrl.ucUserPsAttachFlag  = VOS_FALSE;


    g_GmmGlobalCtrl.stDetachInfo.ulOpid = pstmsg->ulOpid;

    NAS_GMM_InitRaiInfo(NAS_GMM_GetAttemptUpdateRaiInfo());



    g_GmmGlobalCtrl.stAttachInfo.enAttachType &=~GMM_WAIT_PS_ATTACH;
    g_GmmGlobalCtrl.stDetachInfo.enDetachType |= GMM_WAIT_PS_DETACH;

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_ProcCsDetach
 功能描述  : GMM处理CS DETACH
 输入参数  : VOS_UINT32 ulOpID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月15日
    作    者   : 王毛/00166186
    修改内容   : 新生成函数
  2.日    期   : 2012年4月23日
    作    者   : w00166186
    修改内容   : 问题单号:DTS2012041805421,L下开机后，在GU下网络模式I IMSI DETACH不成功

  3.日    期   : 2013年6月8日
    作    者   : w00167002
    修改内容   : V9R1_SVLTE:网络模式I，CS当前有业务链接存在，不处理syscfg设置
                 引起的detach cs操作。
                 联合注册的时候，处理CS域的DETACH
                 增加判断GMM处理CS域的DETACH消息
*****************************************************************************/
VOS_UINT32 NAS_GMM_ProcCsDetach(
    MMCGMM_DETACH_REQ_STRU             *pstmsg
)
{
    /* 非网络模式I下，不处理，直接返回 */

    if (VOS_FALSE == NAS_GMM_IsNeedProcUserCsDetach())
    {
        return VOS_TRUE;
    }
    else
    {
        /* CS处于ATTACHED状态保留标志位, 否则直接回复DETACH CNF*/
        if ( (MM_STATUS_ATTACHED                  == g_MmSubLyrShare.MmShare.ucCsAttachState)
          || (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
          || (GMM_REGISTERED_INITIATED            == g_GmmGlobalCtrl.ucState) )
        {
            if ( VOS_TRUE == NAS_MML_GetCsServiceExistFlg() )
            {
                /*  网络模式I下，CS当前有业务链接存在，syscfg设置引起的detach cs操作，则直接返回 */
                if (VOS_TRUE == g_GmmDetachCtrl.ucSysCfgDetachFlg)
                {
                    return VOS_TRUE;
                }
            }

            g_GmmGlobalCtrl.stAttachInfo.enAttachType &= ~MM_WAIT_CS_ATTACH;
            g_GmmGlobalCtrl.stDetachInfo.enDetachType |= MM_WAIT_CS_DETACH;
            g_GmmGlobalCtrl.stDetachInfo.ulOpid = pstmsg->ulOpid;
        }
        else
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_ProcCsPsDetach
 功能描述  : GMM处理CS+PS类型的DETACH
 输入参数  : VOS_UINT32 ulOpID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月15日
   作    者   : 王毛/00166186
   修改内容   : 新生成函数


  2.日    期   : 2013年6月11日
    作    者   : w00167002
    修改内容   : V9R1_SVLTE:检视意见修改，在预处理收到DETACH时候，就启动DETACH的
                 保护定时器，在回复MMC的detach CNF时候停止保护定时器。
                 修改函数入参。
  3.日    期   : 2015年1月15日
    作    者   : z00161729
    修改内容   : AT&T 支持DAM特性修改
*****************************************************************************/

VOS_UINT32 NAS_GMM_ProcCsPsDetach(
    MMCGMM_DETACH_REQ_STRU             *pstmsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampInfo;

    /* 获取当前网络模式 */
    pstCampInfo     = NAS_MML_GetCurrCampPlmnInfo();

    NAS_GMM_InitRaiInfo(NAS_GMM_GetAttemptUpdateRaiInfo());

    /* 非网络模式I下,只保留PS的标志位 */
    if (NAS_MML_NET_MODE_I != pstCampInfo->enNetworkMode)
    {
        g_GmmGlobalCtrl.stAttachInfo.enAttachType &= ~GMM_WAIT_PS_ATTACH;
        g_GmmGlobalCtrl.stDetachInfo.enDetachType |=  GMM_WAIT_PS_DETACH;

        g_GmmGlobalCtrl.stDetachInfo.ulOpid        = pstmsg->ulOpid;
    }
    else
    {
        /* 清楚ATTACH等待标志 */
        g_GmmGlobalCtrl.stAttachInfo.enAttachType = GMM_WAIT_NULL_ATTACH;

        /* CS处于ATTACHED状态保留标志位 */
        if (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
        {
            g_GmmGlobalCtrl.stDetachInfo.enDetachType    |= GMM_WAIT_CS_DETACH;
        }

        g_GmmGlobalCtrl.stDetachInfo.enDetachType    |= GMM_WAIT_PS_DETACH;

        g_GmmGlobalCtrl.stDetachInfo.ulOpid           = pstmsg->ulOpid;
    }

    g_GmmGlobalCtrl.ucUserPsAttachFlag = VOS_FALSE;

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_RcvMmcDetachReq_PreProc
 功能描述  : GMM收到MMC DETACH的预处理
 输入参数  : MMCMM_ATTACH_REQ_STRU *pstmsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月13日
   作    者   : 王毛/00166186
   修改内容   : 新生成函数
 2.日    期   : 2013年6月11日
   作    者   : w00167002
   修改内容   : V9R1_SVLTE:检视意见修改，在预处理收到DETACH时候，就启动DETACH的
                 保护定时器，在回复MMC的detach CNF时候停止保护定时器。
                 修改函数入参。
 3.日    期   : 2015年4月15日
   作    者   : y00245242
   修改内容   : iteration 13开发
*****************************************************************************/
VOS_UINT32 NAS_GMM_RcvMmcDetachReq_PreProc(
    MMCGMM_DETACH_REQ_STRU             *pstmsg
)
{

    /* 启动Detach流程保护定时器 */
    NAS_GMM_StartDetachProtectingTimer(pstmsg);

    /* 判断是否需要缓存DETACH */
    if ( VOS_TRUE == NAS_GMM_CheckNeedBuffDetach(pstmsg) )
    {
        return VOS_TRUE;
    }


    if ( (MMC_GMM_DETACH_CAUSE_RAT_OR_BAND_DETACH == pstmsg->enDetachReason)
      || (MMC_GMM_DETACH_CAUSE_SRV_DOMAIN_CHANGE  == pstmsg->enDetachReason) )
    {
        g_GmmDetachCtrl.ucSysCfgDetachFlg = VOS_TRUE;
    }
    else
    {
        g_GmmDetachCtrl.ucSysCfgDetachFlg = VOS_FALSE;
    }

    /*  根据DETACH类型分别处理 */
    switch ( pstmsg->enDetachType )
    {
        case MMC_GMM_PS_DETACH:
            if (VOS_TRUE == NAS_GMM_ProcPsDetach(pstmsg))
            {
                return VOS_TRUE;
            }
            break;

        case MMC_GMM_CS_DETACH:
            if (VOS_TRUE == NAS_GMM_ProcCsDetach(pstmsg))
            {
                return VOS_TRUE;
            }
            break;
        case MMC_GMM_PS_CS_DETACH:
            if (VOS_TRUE == NAS_GMM_ProcCsPsDetach(pstmsg))
            {
                return VOS_TRUE;
            }
            break;
        default:
            GMM_LOG_WARN("NAS_GMM_RcvMmcDetachReq_PreProc:DETACH TYPE INVALID!");
            return VOS_TRUE;
     }


    return VOS_FALSE;
}

/*******************************************************************************
  Module   : Gmm_ComReset
  Function : GMM Reset的公共处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2003.12.08  新规作成
    2.日    期  : 2012年08月24日
      作    者  : m00217266
      修改内容  : 修改Gmm_SndSmEstablishCnf接口，添加原因值
*******************************************************************************/
VOS_VOID Gmm_ComReset(VOS_VOID)
{
    Gmm_TimerStop(GMM_TIMER_ALL);                                               /* 停所有Timer                              */
    if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
    {                                                                           /* 需要向SM回响应                           */
        Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_GMM_RESET);/* 通知SM GMM注册失败                       */

        g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;
    }
    if (GMM_TRUE == g_GmmServiceCtrl.ucSmsFlg)
    {                                                                           /* SMS在等待响应                            */
        Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);                              /* 发送PMMSMS_ERROR_IND                     */
        g_GmmServiceCtrl.ucSmsFlg = GMM_FALSE;
    }
    if (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta)
    {                                                                           /* GMM当前状态为ATTACHED                    */
        GMM_CasFsmStateChangeTo(GMM_NULL);

        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_ComReset:NORMAL: STATUS IS GMM_NULL");

        Gmm_SndSmStatusInd();                                                   /* 发送原语GMMSM_STATUS_IND                 */
    }
    if ((GMM_SERVICE_REQUEST_DATA_IDLE == g_GmmGlobalCtrl.ucSpecProc)
        || (GMM_SERVICE_REQUEST_DATA_CONN == g_GmmGlobalCtrl.ucSpecProc))
    {                                                                           /* 需要向RABM回响应                         */
        Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);                 /* 发送GMMRABM_REESTABLISH_CNF(failure)     */
    }
    if (GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
    {                                                                           /* 有PS域信令                               */
        Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);                                                    /* 释放信令                                 */
    }
    Gmm_HoldBufferFree();                                                       /* 清除保留消息                             */
    Gmm_ComVariantInit();                                                       /* GMM初始化                                */

    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module   : Gmm_DealWithBuffInProc
  Function : 收到RRMM_EST_CNF后对buffer的处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : GMM_FALSE    没有缓存
             GMM_TRUE     有缓存
  History  :
    1. 张志勇  2003.12.08  新规作成
  2.日    期   : 2012年5月21日
   作    者   : l65478
   修改内容   : DTS2012052101009:在RAU过程中发起DETACH,GMM没有处理
*******************************************************************************/
VOS_UINT8 Gmm_DealWithBuffInProc(VOS_VOID)
{
    VOS_VOID               *pAddr;                                              /* 定义指针                                 */
    VOS_UINT8               ucRet;                                              /* 定义返回值                               */

    ucRet = GMM_FALSE;                                                          /* 返回值初始化为FALSE                      */

    if (GMM_MSG_HOLD_FOR_POWEROFF
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_POWEROFF))
    {                                                                           /* 如果有保留的power off原语                */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPowerOff;       /* 读取power off原语地址                    */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_POWEROFF;     /* 清除保留标志                             */
        Gmm_MsgDistribute(pAddr);                                               /* 保留的消息分发                           */
        Gmm_MemFree(pAddr);
        Gmm_HoldBufferFree();                                                   /* 将保留buffer中所有的消息释放             */
        ucRet = GMM_TRUE;
    }
    else if (GMM_MSG_HOLD_FOR_PAGING
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_PAGING))
    {                                                                           /* 如果有保留的paging(IMSI)原语             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPaging;         /* 读取paging(IMSI)原语地址                 */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_PAGING;       /* 清除保留标志                             */
        Gmm_MsgDistribute(pAddr);                                               /* 保留的消息分发                           */
        Gmm_MemFree(pAddr);
        Gmm_HoldBufferFree();                                                   /* 将保留buffer中所有的消息释放             */
        ucRet = GMM_TRUE;
    }
    else if (GMM_MSG_HOLD_FOR_RAU
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_RAU))
    {                                                                           /* 如果有保留的RAU原语                      */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForRau;            /* 读取RAU原语地址                          */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_RAU;          /* 清除保留标志                             */
        Gmm_MsgDistribute(pAddr);                                               /* 保留的消息分发                           */
        Gmm_MemFree(pAddr);
        ucRet = GMM_TRUE;
    }

    else if (GMM_MSG_HOLD_FOR_DETACH
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_DETACH))
    {                                                                           /* 如果有保留的DETACH原语                   */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach;         /* 读取detach原语地址                       */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_DETACH;       /* 清除保留标志                             */
        Gmm_MsgDistribute(pAddr);                                               /* 保留的消息分发                           */
        Gmm_MemFree(pAddr);
        NAS_GMM_FreeBufferCmMsg();
        ucRet = GMM_TRUE;
    }

    else if (GMM_MSG_HOLD_FOR_ATTACH
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_ATTACH))
    {                                                                           /* 如果有保留的attach原语                   */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForAttach;         /* 读取attach原语地址                       */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_ATTACH;       /* 清除保留标志                             */
        Gmm_MsgDistribute(pAddr);                                               /* 保留的消息分发                           */
        Gmm_MemFree(pAddr);
        ucRet = GMM_TRUE;
    }
    else
    {
    }
    return ucRet;
}

/*******************************************************************************
  Module   : Gmm_DealWithBuffAfterProc
  Function : 流程结束后对buffer的处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2003.12.08  新规作成
    2. 韩鲁峰  2007.11.16  A32D12187 增加对缓存的待向网络发送的SM消息的处理
    3.日    期   : 2007年12月18日
      作    者   : l00107747
      修改内容   : 根据问题单号：GMM处理SM缓存和当前不能处理需要缓存需要区别处理，
                   否则会造成内存问题
    4.日    期   : 2011年12月23日
      作    者   : s46746
      修改内容   : DTS2011122007386:PDP被去激活后,PS缓存标志未清除
*******************************************************************************/
VOS_VOID Gmm_DealWithBuffAfterProc(VOS_VOID)
{
    VOS_VOID                            *pMsg;
    GMMSM_DATA_REQ_STRU                 *ptr;
    GMMRABM_REESTABLISH_REQ_STRU        *pRabmReEst;

    if (GMM_MSG_HOLD_FOR_DETACH
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_DETACH))
    {                                                                           /* 如果有保留的DETACH原语                   */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_DETACH;       /* 清除缓存标志                             */
        Gmm_MsgDistribute((VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach);  /* 保留的消息分发                           */
        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach);
    }

    if (GMM_MSG_HOLD_FOR_SERVICE
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SERVICE))
    {                                                                           /* 如果有保留的SR原语                       */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SERVICE;      /* 清除缓存标志                             */

        pMsg = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForService;

        /*构造分发消息*/
        pRabmReEst = (GMMRABM_REESTABLISH_REQ_STRU *)Gmm_MemMalloc(sizeof(GMMRABM_REESTABLISH_REQ_STRU));

        if (VOS_NULL_PTR == pRabmReEst)
        {
            Gmm_MemFree(pMsg);
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "Gmm_DealWithBuffAfterProc:ERROR: Gmm_MemMalloc fail !! ");
            return;
        }

        Gmm_MemCpy(pRabmReEst, pMsg, sizeof(GMMRABM_REESTABLISH_REQ_STRU));

        /*释放保存的RAMB消息*/
        Gmm_MemFree(pMsg);

        /*分发缓存的Service消息*/
        Gmm_MsgDistribute((VOS_VOID *)(pRabmReEst));

        /*释放新申请的内存*/
        Gmm_MemFree(pRabmReEst);
    }

    if (GMM_MSG_HOLD_FOR_SMS
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SMS))
    {                                                                           /* 如果有保留的SR原语                       */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SMS;          /* 清除缓存标志                             */
        Gmm_MsgDistribute((VOS_VOID *)(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSMS)); /* 保留的消息分发                           */
        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSMS);
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSMS = (VOS_UINT32)NULL;

    }

    /* 对于SM消息，GMM处于暂态，需要两次缓存，第一次缓存等到GMM处于
    *  正常服务态才处理，这时先发起服务请求，消息需要第二次缓存
    *  等到安全模式完成后再处理。因是两次缓存使用同一变量记录消息地址，
    *  因此每次处理时都是重新申请空间，及时释放原申请空间。
    */
    if (GMM_MSG_HOLD_FOR_SM ==
        (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SM))
    {
        /*清除缓存SM消息的标志*/
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SM;
        pMsg = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSm;

        if (VOS_NULL_PTR == pMsg)
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "Gmm_DealWithBuffAfterProc:ERROR: GMM MSG HOLD FOR SM PTR IS NULL.");
            return;
        }
        /*申请缓存消息的内存*/
        if (4 > ((GMMSM_DATA_REQ_STRU *)pMsg)->SmMsg.ulNasMsgSize)
        {
            ptr = (GMMSM_DATA_REQ_STRU *)Gmm_MemMalloc(sizeof(GMMSM_DATA_REQ_STRU));
        }
        else
        {
            ptr = (GMMSM_DATA_REQ_STRU *)Gmm_MemMalloc((sizeof(GMMSM_DATA_REQ_STRU)
                   + ((GMMSM_DATA_REQ_STRU *)pMsg)->SmMsg.ulNasMsgSize) - 4);
        }
        if (VOS_NULL_PTR == ptr)
        {
            Gmm_MemFree(pMsg);
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "Gmm_DealWithBuffAfterProc:ERROR: Gmm_MemMalloc fail !! ");
            return;
        }

        /*把消息暂存到申请的内存中*/
        if (4 > ((GMMSM_DATA_REQ_STRU *)pMsg)->SmMsg.ulNasMsgSize)
        {
            Gmm_MemCpy(ptr, pMsg, sizeof(GMMSM_DATA_REQ_STRU));
        }
        else
        {
            Gmm_MemCpy(ptr, pMsg, ((sizeof(GMMSM_DATA_REQ_STRU)
                + ((GMMSM_DATA_REQ_STRU *)pMsg)->SmMsg.ulNasMsgSize) - 4));
        }
        NAS_NORMAL_LOG(WUEPS_PID_GMM, "Gmm_DealWithBuffAfterProc(): Process cached SM Data Req");
        /*释放保存的SM消息*/
        Gmm_MemFree(pMsg);
        /*分发缓存的SM消息*/
        Gmm_MsgDistribute((VOS_VOID *)(ptr));
        /*释放新申请的内存*/
        Gmm_MemFree(ptr);
    }

    if ((0x0 == g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk)
     && (GMM_FALSE == g_GmmGlobalCtrl.ucFollowOnFlg))
    {
        g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);
    }

    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module   : Gmm_HoldBufferFree
  Function : 将保留buffer中所有的消息释放的处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2004.01.04  新规作成
    2.日    期   : 2007年12月18日
      作    者   : l00107747
      修改内容   : 根据问题单号:AA32D13917,GMM处理SM缓存和当前不能处理需要缓存需要区别处理，
                   否则会造成内存问题
    3.日    期   : 2009年03月21日
      作    者   : l00130025
      修改内容   : 问题单号:AT2D09534,异系统切换后的建链失败过程中关机，Gmm/MM对关机消息没有处理，后续设置AT^CPAM超时，无响应
    4.日    期   : 2011年12月23日
      作    者   : s46746
      修改内容   : DTS2011122007386:PDP被去激活后,PS缓存标志未清除
*******************************************************************************/
VOS_VOID Gmm_HoldBufferFree(VOS_VOID)
{
    VOS_VOID                *pAddr;                                             /* 定义指针                                 */

    if (GMM_MSG_HOLD_FOR_PAGING
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_PAGING))
    {                                                                           /* 如果有保留的paging(IMSI)原语             */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_PAGING;       /* 清除保留标志                             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPaging;         /* 读取paging(IMSI)原语地址                 */
        Gmm_MemFree(pAddr);                                                     /* 将保留buffer中所有的消息释放             */
    }

    if (GMM_MSG_HOLD_FOR_RAU
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_RAU))
    {                                                                           /* 如果有保留的RAU原语                      */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_RAU;          /* 清除缓存标志                             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForRau;            /* 读取RAU原语地址                          */
        Gmm_MemFree(pAddr);                                                     /* 将保留buffer中所有的消息释放             */
    }

    if (GMM_MSG_HOLD_FOR_DETACH
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_DETACH))
    {                                                                           /* 如果有保留的DETACH原语                   */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_DETACH;       /* 清除保留标志                             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach;         /* 读取detach原语地址                       */
        Gmm_MemFree(pAddr);                                                     /* 将保留buffer中所有的消息释放             */
    }

    if (GMM_MSG_HOLD_FOR_ATTACH
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_ATTACH))
    {                                                                           /* 如果有保留的attach原语                   */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_ATTACH;       /* 清除保留标志                             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForAttach;         /* 读取attach原语地址                       */
        Gmm_MemFree(pAddr);                                                     /* 将保留buffer中所有的消息释放             */
    }

    if (GMM_MSG_HOLD_FOR_SERVICE
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &GMM_MSG_HOLD_FOR_SERVICE))
    {                                                                           /* 如果有保留的ServiceRequest原语           */
        Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);                 /* 通知RABM结果                             */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SERVICE;      /* 清除保留标志                             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForService;        /* 读取ServiceRequest原语地址               */
        Gmm_MemFree(pAddr);                                                     /* 将保留buffer中所有的消息释放             */
    }

    if (GMM_MSG_HOLD_FOR_SM
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SM))
    {                                                                           /* 如果有保留的SmDataReq原语                */
        NAS_NORMAL_LOG(WUEPS_PID_GMM, "Gmm_HoldBufferFree(): Clear cached SM Data Req");

        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SM;           /* 清除保留标志                             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSm;             /* 读取SmDataReq原语地址                    */
        Gmm_MemFree(pAddr);                                                     /* 将保留buffer中所有的消息释放             */
    }

    if ((0x0 == g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk)
     && (GMM_FALSE == g_GmmGlobalCtrl.ucFollowOnFlg))
    {
        g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_RcvMmCmServiceRejectInd
 功能描述  : 收到原语MMGMM_CM_SERVICE_REJECT_IND的处理
 输入参数  : pstmsg:MMGMM_CM_SERVICE_REJECT_IND消息的首地址
 输出参数  : 无
 返 回 值  : VOS_UINT32:VOS_TRUE, VOS_FALSE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年7月22日
   作    者   : h44270
   修改内容   : 新生成函数
 2.日    期   : 2013年2月4日
   作    者   : w00176964
   修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册

*****************************************************************************/
VOS_VOID NAS_GMM_RcvMmCmServiceRejectInd(
    VOS_VOID                           *pstMsg
)
{
    MMGMM_CM_SERVICE_REJECT_IND_STRU   *pstMmServRejInd;                      /* 定义指针                                 */

    if ((VOS_TRUE != NAS_MML_GetCsAttachAllowFlg())
     || (GMM_NET_MODE_I != g_GmmGlobalCtrl.ucNetMod))
    {                                                                           /* 不是用户模式A且网络模式I                 */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcCmServiceRejectInd:WARNING: It is not A+I(Gmm_RcvMmcCmServiceRejectInd)");
        return;
    }

    pstMmServRejInd = (MMGMM_CM_SERVICE_REJECT_IND_STRU *)pstMsg;                 /* 初始化指针                               */

    if (NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_VLR == pstMmServRejInd->enCause)
    {                                                                           /* 原因值为#4                               */
        g_GmmRauCtrl.ucCsSpringRauFlg = GMM_TRUE;                               /* 设置MmcCmServiceRejectInd#4触发RAU的标志 */
    }

    return;
}

/*******************************************************************************
  Module   : NAS_GMM_RcvMmCsConnectInd_InProc
  Function : RAU/SR过程中收到原语MMGMM_CS_CONNECT_IND的处理
  Input    : VOS_VOID       *pMsg        原语指针
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2003.12.09  新规作成
    2.日    期   : 2012年12月5日
      作    者   : t00212959
      修改内容   : DTS2012120504420:CSFB，rau被#10拒绝，ATTACH成功，CS结束，不发RAU
*******************************************************************************/
VOS_VOID NAS_GMM_RcvMmCsConnectInd_InProc(
    VOS_VOID                           *pstMsg                               /* 原语指针                                 */
)
{
    MMGMM_CS_CONNECT_IND_STRU          *pstTmpMsg;

    if (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
    {                                                                           /* 当前流程为RAU                            */
        g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg = GMM_TRUE;                      /* 流程结束之后进行RAU                      */
        g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg = GMM_TRUE;                     /* 标记GMM不能进行RAU时要触发MM的LU过程     */
        g_GmmRauCtrl.ucCsSpringRauFlg = GMM_FALSE;                              /* 清除CS触发RAU的标志                      */
        return;
    }

    if (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
    {                                                                           /* 当前流程为ATTACH                            */
        g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg = GMM_TRUE;                      /* 流程结束之后进行RAU                      */
        g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg = GMM_TRUE;                     /* 标记GMM不能进行RAU时要触发MM的LU过程     */
        g_GmmRauCtrl.ucCsSpringRauFlg = GMM_FALSE;                              /* 清除CS触发RAU的标志                      */
        return;
    }

    if ((GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
        && (GMM_RRC_RRMM_EST_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)))
    {                                                                           /* 无信令且正在建立信令连接                 */
        pstTmpMsg = (MMGMM_CS_CONNECT_IND_STRU *)Gmm_MemMalloc(sizeof(MMGMM_CS_CONNECT_IND_STRU));
        if (VOS_NULL_PTR == pstTmpMsg)
        {
              PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_RcvMmcCmServiceInd_InProc:ERROR: Memory is not allocated");
              return;
        }
        Gmm_MemCpy(pstTmpMsg, pstMsg, sizeof(MMGMM_CS_CONNECT_IND_STRU));
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForRau = (VOS_UINT32)pstTmpMsg;              /* 保留该原语                               */

        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_RAU;           /* 置保留标志                               */
    }
    else
    {                                                                           /* 有信令或没有信令且还没建信令             */
        if (GMM_TIMER_T3317_FLG
            == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3317_FLG))
        {                                                                       /* 如果T3317在运行                          */
            Gmm_TimerStop(GMM_TIMER_T3317);                                     /* 停T3317                                  */
        }
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */
        g_GmmGlobalCtrl.ucSpecProcHold = g_GmmGlobalCtrl.ucSpecProc;            /* 保留被中断的SR流程                       */
        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;                               /* 设置follow on标志                        */
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* 执行RAU                                  */
        g_GmmRauCtrl.ucCsSpringRauFlg = GMM_FALSE;                              /* 清除CS触发RAU的标志                      */
    }
    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module   : NAS_GMM_RcvMmCsConnectInd_RegNmlServ
  Function : 在GMM_REGISTERED_NORMAL_SERVICE状态下收到
             原语MMGMM_CM_SERVICE_IND的处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2003.12.09  新规作成
    2.日    期   : 2008年08月1日
      作    者   : luojian id:00107747
      修改内容   : 根据问题单AT2D04486/AT2D04822
    3.日    期   : 2012年4月17日
      作    者   : z00161729
      修改内容  : DTS2012041402264：L小区下发起CS语音业务，通过重定向CS Fallback到W小区。激活PDP后释放CS语音，未上系统消息，UE不会发起联合RAU
    4.日    期   : 2012年9月17日
      作    者   : l65478
      修改内容  : DTS2012091204262：连续发起两次RAU
    5.日    期   : 2012年10月30日
      作    者   : s00217060
      修改内容  : DTS2012050301830：调整 RRC连接存在时,立即做联合RAU;否则等收到系统消息后再做联合RAU
*******************************************************************************/
VOS_VOID NAS_GMM_RcvMmCsConnectInd_RegNmlServ(VOS_VOID)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrRatType;

    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus = VOS_NULL_PTR;

    /* 取得当前的链接信息 */
    pstConnStatus = NAS_MML_GetConnStatus();

    enCurrRatType = NAS_MML_GetCurrNetRatType();

    if (GMM_REGISTERED_ATTEMPTING_TO_UPDATE == g_GmmGlobalCtrl.ucState )
    {
        /*
        3gpp 24.008 4.7.5 : The routing area updating attempt counter shall be
        reset when the MS is in substate ATTEMPTING-TO-UPDATE and
            - a new routing area is entered;
            - expiry of timer T3302; or
            - at request from registration function.
        */
        g_GmmRauCtrl.ucRauAttmptCnt = 0;
    }

    /* CS业务结束，GS关联不存在，RRC存在，立即发起联合RAU，否则等上报系统消息，再发起联合rau*/
    if ((VOS_TRUE == pstConnStatus->ucRrcStatusFlg)
     && (VOS_FALSE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
     && (NAS_MML_NET_RAT_TYPE_WCDMA == enCurrRatType)
     && (GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState))
    {
        NAS_GMM_RcvMmCsConnectInd_RrcConnExist();
        g_GmmRauCtrl.ucCsSpringRauFlg = GMM_FALSE;                                  /* 清除CS触发RAU的标志                      */
    }
    else
    {
    }
}

/*****************************************************************************
 函 数 名  : NAS_GMM_IsRcvRrmmEstCnfMsgValid
 功能描述  : 降Gmm_RcvRrmmEstCnf函数圈复杂度，判断接收到的rrmm est cnf消息是否合法
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE: 合法
             VOS_FALSE: 不合法
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年6月13日
    作    者   : z00161729
    修改内容   : 24008 23122 R11 CR升级项目修改
*****************************************************************************/
VOS_UINT32 NAS_GMM_IsRcvRrmmEstCnfMsgValid(
    RRMM_EST_CNF_STRU                  *pRrmmEstCnf
)
{
    if (RRC_NAS_PS_DOMAIN != pRrmmEstCnf->ulCnDomainId)
    {                                                                           /* 判断是PS域信息,否                        */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_GMM_IsRcvRrmmEstCnfMsgValid:WARNING: It is not PS domain(Gmm_RcvRrmmEstCnf)");
        return VOS_FALSE;
    }
    if (GMM_RRC_RRMM_EST_CNF_FLG
        != (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG))
    {                                                                           /* 判断是否正在等该响应,否                  */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_GMM_IsRcvRrmmEstCnfMsgValid:WARNING: RRMM_EST_CNF is unexpected");
        return VOS_FALSE;
    }
    if (g_GmmReqCnfMng.ucRrmmEstOpid != pRrmmEstCnf->ulOpId)
    {                                                                           /* OP ID不相等                              */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_GMM_IsRcvRrmmEstCnfMsgValid:WARNING: RRMM_EST_CNF is unexpected(OPID is not same)");
        return VOS_FALSE;
    }

    if (RRC_EST_ESTING == pRrmmEstCnf->ulResult)
    {                                                                           /* 结果为正在建                             */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_GMM_IsRcvRrmmEstCnfMsgValid:WARNING: The result is invalid(Gmm_RcvRrmmEstCnf)");
        return VOS_FALSE;
    }

    return VOS_TRUE;

}

/*******************************************************************************
  Module   : Gmm_RcvRrmmEstCnf
  Function : 收到原语RRMM_EST_CNF 的处理
  Input    : VOS_VOID     *pMsg    原语指针
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2003.12.09  新规作成
    2.日    期   : 2006年2月17日
      作    者   : liuyang id:48197
      修改内容   : 问题单号：A32D01287，打印错误

    3.日    期   : 2011年7月14日
      作    者   : zhoujun 40661
      修改内容   : 更新PS域连接存在标志位

    4.日    期   : 2011年04月20日
      作    者   : s46746
      修改内容   : 根据问题单号：DTS2011040804149，【V3R1C31B027】【RAU】PS ONLY下，PMM_IDLE态W2G重选后，发起ping未进行RAU流程，无法进行数传
    5.日    期   : 2012年2月15日
      作    者   : w00166186
      修改内容   : CSFB&PPAC&ETWS&ISR 开发
    6.日    期   : 2012年03月12日
      作    者   : z00161729
      修改内容   : 支持ISR修改
    7.日    期   : 2012年7月14日
      作    者   : l65478
      修改内容   : DTS2012071303294在连接建立失败时没有清除连接标志
    8.日    期   : 2013年08月16日
      作    者   : l65478
      修改内容   : DTS2013092202614,G CCO到W失败回退到G,在G下通知了GAS进入了REDAY态
    9.日    期   : 2013年4月10日
      作    者   : y00176023
      修改内容   : DSDS GUNAS II项目:增加对RRC_EST_RJ_NO_RF的处理
    10.日    期   : 2014年9月18日
       作    者   : z00161729
       修改内容   : DTS2014091705885:l csfb到w网络模式I的小区，位置区改变lau和rau随机接入失败，业务失败，T3311失败发起联合rau成功后又多发了一次联合rau

*******************************************************************************/
VOS_VOID Gmm_RcvRrmmEstCnf(
                       VOS_VOID *pMsg                                           /* 原语指针                                 */
                       )
{
    RRMM_EST_CNF_STRU      *pRrEstCnf;                                          /* 定义指针                                 */

    pRrEstCnf = (RRMM_EST_CNF_STRU *)pMsg;                                      /* 初始化指针                               */

    if (VOS_FALSE == NAS_GMM_IsRcvRrmmEstCnfMsgValid(pRrEstCnf))
    {
        return;
    }

    if (RRC_EST_PRESENT == pRrEstCnf->ulResult)
    {                                                                           /* 结果为已经存在                           */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmEstCnf:INFO: The result of RRMM_EST_CNF is unexpected");
    }

    switch(pRrEstCnf->ulResult)
    {
    case RRC_EST_RJ_CONGEST:
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_CONGESTION;
        break;
    case RRC_EST_RJ_UNSPEC:
    case RRC_EST_RJ_AIRMSG_DECODE_ERR:
    case RRC_EST_RJ_CURR_PROTOCOL_NOT_SUPPORT:
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CASUE_UNSPECIFIED;
        break;
    case RRC_EST_OTHER_ACCESS_BARRED:
        g_GmmGlobalCtrl.ucRelCause =
                    RR_REL_CAUSE_ACCESS_BARRED_CAUSE_ACCESS_CLASS_CONTROL;
        break;
    case RRC_EST_EST_CONN_FAIL:
    case RRC_EST_RJ_NOT_ALLOW:
    case RRC_EST_RJ_TIME_OUT:
    case RRC_EST_RJ_RA_RESOURCE_FAIL:
    case RRC_EST_RJ_IMMEDIATE_ASSIGN_INVALID:
    case RRC_EST_RJ_ACTIVE_PHISICAL_CHANNEL_FAIL:
    case RRC_EST_RJ_FASTRETURN_LTE:
    case RRC_EST_RJ_NO_RF:
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_RR_CONNECTION_FAILURE;
        break;

    case RRC_EST_RJ_SNW:
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_RRC_SNW;
        break;

    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmEstCnf:INFO: The result item of RRMM_EST_CNF Msg is SUCCESS");
        break;

    }

    g_GmmReqCnfMng.ucCnfMask &= ~GMM_RRC_RRMM_EST_CNF_FLG;                      /* 清等待响应标志                           */

    if ((RRC_EST_SUCCESS == pRrEstCnf->ulResult)
        || (RRC_EST_PRESENT == pRrEstCnf->ulResult))
    {                                                                           /* 信令建立成功                             */
        g_GmmGlobalCtrl.ucSigConFlg = GMM_TRUE;                                 /* 置信令标志位                             */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmEstCnf:INFO: PS signatual exist");
        if (GMM_TIMER_T3312_FLG
            == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
        {                                                                       /* 如果T3312在运行                          */
#if (FEATURE_LTE == FEATURE_ON)
            if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
            {
                NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
            }
#endif
            Gmm_TimerStop(GMM_TIMER_T3312);                                     /* 停T3312                                  */
        }
        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_PRESENT);         /* 通知MMC PS域信令连接存在                 */

#if (FEATURE_LTE == FEATURE_ON)
        if (NAS_GMM_TIMER_T3323_FLG == (NAS_GMM_TIMER_T3323_FLG & g_GmmTimerMng.ulTimerRunMask))
        {
            Gmm_TimerStop(GMM_TIMER_T3323);
        }
#endif
        /* 24.008, 4.4.4.9, case f1, CR1099 update:
           W下更新GMM链路控制结构，并更新RRC链路状态 */
        if (VOS_FALSE == GMM_IsCasGsmMode())
        {
            /* 在收到RRMM_RESUME_IND时,没有停止T3314,是为了避免CCO失败回退
               所以在收到连接建立成功时需要停止此定时器 */
            Gmm_TimerStop(GMM_TIMER_T3314);

            NAS_MML_SetPsSigConnStatusFlg(VOS_TRUE);

            NAS_MML_SetRrcConnStatusFlg(VOS_TRUE);

            gstGmmCasGlobalCtrl.ucLastDataSender = NAS_MML_NET_RAT_TYPE_WCDMA;

        }

    }
    else
    {
        /* 链路建立失败，清除GMM链路控制变量 */
        if (VOS_FALSE == GMM_IsCasGsmMode())
        {
            NAS_GMM_ClearGmmLinkCtrlStru();
        }

        NAS_MML_SetPsSigConnStatusFlg(VOS_FALSE);

        NAS_GMM_DeleteRandAndResInfoInPmmIdleMode();

        g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg = GMM_FALSE;
        g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg = GMM_FALSE;
    }


    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* 根据状态分发                             */
    case GMM_REGISTERED_INITIATED:
        Gmm_RcvRrmmEstCnf_RegInit(pRrEstCnf);                                   /* 调用该状态下的处理                       */
        break;
    case GMM_DEREGISTERED_INITIATED:
        Gmm_RcvRrmmEstCnf_DeregInit(pRrEstCnf);                                 /* 调用该状态下的处理                       */
        break;
    case GMM_ROUTING_AREA_UPDATING_INITIATED:
        Gmm_RcvRrmmEstCnf_RauInit(pRrEstCnf);                                   /* 调用该状态下的处理                       */
        break;
    case GMM_SERVICE_REQUEST_INITIATED:
        Gmm_RcvRrmmEstCnf_ServReqInit(pRrEstCnf);                               /* 调用该状态下的处理                       */
        break;
    case GMM_DEREGISTERED_NORMAL_SERVICE:
        Gmm_RcvRrmmEstCnf_DeregNmlServ(pRrEstCnf);                              /* 调用该状态下的处理                       */
        break;
    case GMM_REGISTERED_IMSI_DETACH_INITIATED:
        Gmm_RcvRrmmEstCnf_RegImsiDtchInit(pRrEstCnf);                           /* 调用该状态下的处理                       */
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRrmmEstCnf:WARNING: g_GmmGlobalCtrl.ucState is Error");
        break;
    }
    return;
}

/*******************************************************************************
  Module   : Gmm_RcvRrmmEstCnf_RegInit
  Function : 在GMM-REGISTERED-INITIATED状态下收到原语RRMM_EST_CNF 的处理
  Input    : VOS_VOID     *pMsg    原语指针
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
  1.张志勇  2003.12.09  新规作成
  2.日    期   : 2008年7月2日
    作    者   : l00107747
    修改内容   : 根据问题单号：AT2D03900
  3.日    期   : 2010年01月04日
    作    者   : w00166186
    修改内容   : 问题单号:DTS2010122004132 W CS ONLY PDP激活过程重定向到G,PDP激活失败
  4.日    期   : 2011年7月14日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  5.日    期   : 2012年2月15日
    作    者   : w00166186
    修改内容   : CSFB&PPAC&ETWS&ISR 开发
  6.日    期   : 2012年08月24日
    作    者   : m00217266
    修改内容   : 修改Gmm_SndSmEstablishCnf接口，添加原因值
  7.日    期   : 2015年8月13日
    作    者   : l00289540
    修改内容   : User_Exp_Improve修改
*******************************************************************************/
VOS_VOID Gmm_RcvRrmmEstCnf_RegInit(
                               VOS_VOID *pMsg                                   /* 原语指针                                 */
                               )
{
    RRMM_EST_CNF_STRU                      *pRrEstCnf;                          /* 定义指针                                 */
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16      enCause;

    pRrEstCnf = (RRMM_EST_CNF_STRU *)pMsg;                                      /* 初始化指针                               */

    Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);

    if (0 != g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk)
    {                                                                           /* 有消息保留                               */
        if (GMM_TRUE == Gmm_DealWithBuffInProc())
        {                                                                       /* 保留消息处理成功                         */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvRrmmEstCnf_RegInit:NORMAL: Deal Hold Msg success");
            return;
        }
    }

    if ((RRC_EST_SUCCESS == pRrEstCnf->ulResult)
        || (RRC_EST_PRESENT == pRrEstCnf->ulResult))
    {                                                                           /* 信令连接建立成功                         */
        Gmm_TimerStart(GMM_TIMER_T3310);                                        /* 起T3310                                  */
    }
    else if (RRC_EST_REGISTER_ACCESS_BARRED == pRrEstCnf->ulResult)
    {                                                                           /* Access barred                            */
        Gmm_ComStaChg(GMM_DEREGISTERED_ATTACH_NEEDED);                          /* 调用状态的公共处理                       */
        enCause = NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED;
        if ((GMM_ATTACH_WHILE_IMSI_ATTACHED == g_GmmGlobalCtrl.ucSpecProc)
            || (GMM_ATTACH_COMBINED         == g_GmmGlobalCtrl.ucSpecProc))
        {                                                                       /* 当前流程为combined attach                */
            NAS_GMM_SndMmCombinedAttachRejected(enCause);       /* 发送MMCGMM_COMBINED_ATTACH_REJECTED      */
        }
        else
        {                                                                       /* 当前流程为normal attach                  */
            NAS_GMM_SndMmGmmActionResultInd(GMMMM_ACTION_FAILURE,
                                            enCause);                         /* 发送MMCGMM_GMM_ACTION_RESULT_IND         */
        }


        /* 向MMC发送PS注册结果 */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                     GMM_MMC_ACTION_RESULT_FAILURE,
                                     enCause);

        /* 事件上报 */
        NAS_EventReport(WUEPS_PID_GMM,
                        NAS_OM_EVENT_ATTACH_FAIL,
                        &enCause,
                        NAS_OM_EVENT_ATTACH_FAIL_LEN
                        );

        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
        if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
        {                                                                       /* ATTACH过程是由SM触发的                   */
            Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_ACCESS_BARRED);      /* 通知SM GMM注册失败                       */
            g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;                             /* 清ucSmCnfFlg标志                         */
        }
        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;                              /* 清除followon标志                         */
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* 清除当前流程                             */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmEstCnf_RegInit:INFO: specific procedure ended");
    }
    else
    {                                                                           /* 信令连接建立失败                         */
        Gmm_ComConvertRrcEstCnfCauseToMmlRegCause(pRrEstCnf->ulResult,&enCause);
        Gmm_AttachAttemptCounter(enCause);                                      /* 调用attach attempt counter的处理         */

        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
        g_GmmGlobalCtrl.ucSpecProc    = GMM_NULL_PROCEDURE;                     /* 清除正在进行的specific过程标志           */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmEstCnf_RegInit:INFO: specific procedure ended");
    }
    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvRrmmEstCnf_DeregInit
  Function : 在GMM-DEREGISTERED-INITIATED状态下收到原语RRMM_EST_CNF的处理
  Input    : VOS_VOID     *pMsg    原语指针
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
  1. 张志勇  2003.12.09  新规作成
  2. 日    期   : 2008年9月18日
     作    者   : ouyangfei 00132663
     修改内容   : 根据问题单号：AT2D05816，在GMM过程中，来自CM层的请求应该被缓存，等GMM过程结束再发起。
  3.日    期   : 2010年12月03日
    作    者   : w00166186
    修改内容   : DTS2010112403161 搜网整理发现问题
  4.日    期   : 2011年07月13日
    作    者   : w00166186
    修改内容   : V7R1 PHASE II ATTACH/DETACH调整
  5.日    期   : 2011年7月27日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  6. 日    期   : 2012年1月12日
     作    者   : w00166186
     修改内容   : DTS2011122704039:开机搜网后CS注册被拒#12,PS注册被拒#14，在ON
                   PLMN状态，服务域被设置为不支持GMM需要将服务域不支持信息通知给MMC.

  7.日    期   : 2013年8月7日
    作    者   : w00167002
    修改内容   : DTS2013080207367:在CS only时候，用户发起PDP激活，网络模式I时候，
                 会触发联合注册.用户发起PDP去激活，会导致PS域的去注册。收到网侧
                 的去注册成功后需要通知MM，否则MM当前在NORMAL SERVICE状态，不
                 触发T3212定时器的启动，长时间可能导致丢寻呼.
*******************************************************************************/
VOS_VOID Gmm_RcvRrmmEstCnf_DeregInit(
                                 VOS_VOID *pMsg                                 /* 原语指针                                 */
                                 )
{
    RRMM_EST_CNF_STRU   *pRrEstCnf = (RRMM_EST_CNF_STRU *)pMsg;                 /* 定义指针                                 */

    Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);

    if (0 != g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk)
    {                                                                           /* 有其他消息保留                           */
        if (GMM_TRUE == Gmm_DealWithBuffInProc())
        {                                                                       /* 保留消息处理成功                         */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvRrmmEstCnf_DeregInit:NORMAL: Deal Hold Msg success");
            return;
        }
    }

    if ((RRC_EST_SUCCESS == pRrEstCnf->ulResult)
        || (RRC_EST_PRESENT == pRrEstCnf->ulResult))
    {                                                                           /* 信令连接建立成功                         */
        Gmm_TimerStart(GMM_TIMER_T3321);                                        /* 起T3321                                  */
    }
    else
    {                                                                           /* 信令连接建立失败                         */
        Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);                         /* 调用状态的公共处理                       */
        NAS_MML_SetPsAttachAllowFlg( VOS_FALSE );         /* 设置PS域禁止注册标志                     */
        Gmm_TimerStop(GMM_TIMER_T3312);
#if (FEATURE_LTE == FEATURE_ON)
        NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
#endif

        if (GMM_UEID_P_TMSI_SIGNATURE
            == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
            & GMM_UEID_P_TMSI_SIGNATURE))
        {                                                                       /* DETACH成功且使用了P_TMSI_SIGNATURE       */
            g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
                &= ~GMM_UEID_P_TMSI_SIGNATURE;                                  /* 清除P_TMSI_SIGNATURE                     */

            NAS_MML_InitUeIdPtmsiSignatureInvalid();
            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* 更新SIM卡信息                            */
            }
            else
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
            }
        }
        /* 判断等待标志是否存在，如果存在则向MMC,MM发送DETACH信息 */
        if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
        {
            NAS_GMM_SndMmcMmDetachInfo();
        }
        else
        {
            /* 收到网侧的去注册成功后需要通知MM，否则MM不启动T3212定时器 */
            NAS_GMM_SndMmGprsDetachComplete();
        }



        /* 向MMC发送PS注册结果 */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                      GMM_MMC_ACTION_RESULT_FAILURE,
                                      NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* 清除当前流程                             */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmEstCnf_DeregInit:INFO: specific procedure ended");
    }
    return;
}

  /*******************************************************************************

  Module   : Gmm_RcvRrmmEstCnfAccessBar_RauInit
  Function : 在RauInit状态下建链失败原因为Access Barred的处理，将此处理封装为函数是
             为了降低原函数的复杂度
  Input    : VOS_VOID
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
  1.日    期   : 2015年8月13日
    作    者   : l00289540
    修改内容   : User_Exp_Improve修改
*******************************************************************************/

VOS_VOID Gmm_RcvRrmmEstCnfAccessBar_RauInit( VOS_VOID )
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16      enCause;

    Gmm_ComStaChg(GMM_REGISTERED_UPDATE_NEEDED);                            /* 调用状态的公共处理                       */
    Gmm_ComCnfHandle();
    enCause = NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED;

    /* 判断等待标志是否存在，如果存在则发送MMCGMM_ATTACH CNF */
    if (GMM_WAIT_PS_ATTACH == (g_GmmGlobalCtrl.stAttachInfo.enAttachType
                             & GMM_WAIT_PS_ATTACH))
    {
        NAS_GMM_SndMmcAttachCnf();
    }
    g_GmmGlobalCtrl.stAttachInfo.enAttachType = GMM_WAIT_NULL_ATTACH;

    if ((GMM_RAU_COMBINED          == g_GmmGlobalCtrl.ucSpecProc)
     || (GMM_RAU_WITH_IMSI_ATTACH  == g_GmmGlobalCtrl.ucSpecProc))
    {                                                                       /* 如果当前流程是combined RAU               */
        NAS_GMM_SndMmCombinedRauRejected(enCause);          /* 发送MMCGMM_COMBINED_ATTACH_REJECTED      */
    }
    else
    {                                                                       /* 如果当前流程是normal RAU                 */
        NAS_GMM_SndMmGmmActionResultInd(GMMMM_ACTION_FAILURE,
                                        enCause);                         /* 发送MMCGMM_GMM_ACTION_RESULT_IND         */
    }


    /* 向MMC发送PS注册结果 */
    NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                 GMM_MMC_ACTION_RESULT_FAILURE,
                                 enCause);

    /* 事件上报 */
    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_ATTACH_FAIL,
                    &enCause,
                    NAS_OM_EVENT_ATTACH_FAIL_LEN
                    );

    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* 清除当前流程                             */

    Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);

    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmEstCnfAccessBar_RauInit:INFO: specific procedure ended");

}

/*******************************************************************************
  Module   : Gmm_RcvRrmmEstCnf_RauInit
  Function : 在GMM-ROUTING-AREA-UPDATING-INITIATED状态下
             收到原语RRMM_EST_CNF 的处理
  Input    : VOS_VOID     *pMsg    原语指针
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
  1.张志勇  2003.12.09  新规作成
  2.日    期   : 2008年9月18日
    作    者   : ouyangfei 00132663
    修改内容   : 根据问题单号：AT2D05816，在GMM过程中，来自CM层的SMS请求应该被缓存，等GMM过程结束再发起。
  3.日    期   : 2010年11月22日
    作    者   : h44270
    修改内容   : 根据问题单号：DTS2010111700109，小区被bar的情况下，状态不正确，导致MM状态不对，没有发起LAU
  4.日    期   : 2011年7月14日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  5.日    期   : 2012年2月15日
    作    者   : w00166186
    修改内容   : CSFB&PPAC&ETWS&ISR 开发

  6.日    期   : 2013年6月5日
    作    者   : w00167002
    修改内容   : V9R1_SVLTE:从协议中看，如果当前在RAU流程中，收到IMSI detach，则先处理RAU;
                 如果在Detach流程中，进入了新的路由区，则先处理RAU.根据协议描述，判定UE的动作
                 为:在RAU流程中，如果收到DETACH，则缓存Detach，待RAU结束后，处理缓存的Detach。
  7.日    期   : 2015年8月13日
    作    者   : l00289540
    修改内容   : User_Exp_Improve修改

*******************************************************************************/
VOS_VOID Gmm_RcvRrmmEstCnf_RauInit(
                               VOS_VOID *pMsg                                   /* 原语指针                                 */
                               )
{
    RRMM_EST_CNF_STRU                      *pRrEstCnf;                          /* 定义指针                                 */
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16      enCause;
    pRrEstCnf = (RRMM_EST_CNF_STRU *)pMsg;                                      /* 初始化指针                               */

    Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);

    if (GMM_RAU_FOR_NORMAL != gstGmmSuspendCtrl.ucRauCause)
    {
        if ((RRC_EST_SUCCESS != pRrEstCnf->ulResult)
        && (RRC_EST_PRESENT != pRrEstCnf->ulResult))
        {
            GMM_RauFailureInterSys();
        }
    }
    else
    {
        if ((RRC_EST_SUCCESS != pRrEstCnf->ulResult)
        && (RRC_EST_PRESENT != pRrEstCnf->ulResult))
        {
            GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_FAILURE);
        }
    }


    /* 在RAU过程中，不处理Detach */
    if (0 != (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & ~GMM_MSG_HOLD_FOR_DETACH) )
    {                                                                           /* 有其他消息保留                           */
        if (GMM_TRUE == Gmm_DealWithBuffInProc())
        {                                                                       /* 保留消息处理成功                         */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvRrmmEstCnf_RauInit:NORMAL: Deal Hold Msg success");
            return;
        }
    }

    if ((RRC_EST_SUCCESS == pRrEstCnf->ulResult)
        || (RRC_EST_PRESENT == pRrEstCnf->ulResult))
    {                                                                           /* 信令连接建立成功                         */
        Gmm_TimerStart(GMM_TIMER_T3330);                                        /* 起T3330                                  */
    }
    else if (RRC_EST_REGISTER_ACCESS_BARRED == pRrEstCnf->ulResult)
    {                                                                           /* Access barred                            */
        /* 为降低函数复杂度，将建链Access bar的处理封装为如下的函数 */
        Gmm_RcvRrmmEstCnfAccessBar_RauInit();
    }
    else
    {
        /* TS24.008
        4.7.5.1.5 Abnormal cases in the MS
        g) Routing area updating and detach procedure collision
        GPRS detach containing detach type"re-attach required" or "re-attach not required":
        If the MS receives a DETACH REQUEST message before the routing area updating procedure has been
        completed, the routing area updating procedure shall be aborted and the GPRS detach procedure shall be
        progressed. If the DETACH REQUEST message contains detach type "re-attach not required" and GMM
        cause #2 "IMSI unknown in HLR", the MS will follow the procedure as described below for the detach type
        "IMSI detach".
        GPRS detach containing detach type "IMSI detach":
        If the MS receives a DETACH REQUEST message before the routing area updating procedure has been
        completed, the routing area updating procedure shall be progressed, i.e. the DETACH REQUEST message
        shall be ignored.


            4.7.4.1.4 Abnormal cases in the MS

            f) Change of cell into a new routing area
        If a cell change into a new routing area occurs before a DETACH ACCEPT message has been received, the
        GPRS detach procedure shall be aborted and re-initiated after successfully performing a routing area updating
        procedure. If the detach procedure is performed due to the removal of the SIM/USIM the MS shall abort the
        detach procedure and enter the state GMM-DEREGISTERED. */

        /* 信令连接建立失败                         */
        Gmm_ComConvertRrcEstCnfCauseToMmlRegCause(pRrEstCnf->ulResult,&enCause);
        Gmm_RoutingAreaUpdateAttemptCounter(enCause);                           /* 调用RAU attempt counter的处理            */

        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);


        /* 判断等待标志是否存在，如果存在则发送MMCGMM_ATTACH CNF */
        if (GMM_WAIT_PS_ATTACH == (g_GmmGlobalCtrl.stAttachInfo.enAttachType
                                 & GMM_WAIT_PS_ATTACH))
        {
            NAS_GMM_SndMmcAttachCnf();
        }
        g_GmmGlobalCtrl.stAttachInfo.enAttachType = GMM_WAIT_NULL_ATTACH;
    }
    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvRrmmEstCnf_ServReqInit
  Function : 在GMM-SERVICE-REQUEST-INITIATED状态下收到原语RRMM_EST_CNF 的处理
  Input    : VOS_VOID     *pMsg    原语指针
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
  1.张志勇  2003.12.09  新规作成
  2.日    期   : 2008年9月18日
    作    者   : ouyangfei 00132663
    修改内容   : 根据问题单号：AT2D05816，在GMM过程中，来自CM层的SMS请求应该被缓存，等GMM过程结束再发起。
  3.日    期   : 2009年3月11日
    作    者   : ouyangfei 00132663
    修改内容   : 根据问题单号：AT2D09927，如果PS域不可用，回复SM SERVICE REJ，中止当前请求，避免SM启定时器，
                 重复发起请求。
  4.日    期   : 2011年7月14日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  5.日    期   : 2012年3月17日
    作    者   : w00176964
    修改内容   : DTS2012031900095 V7R1 C30 SBM&EM定制需求:增加拨号被拒定制
  6.日    期   : 2012年08月24日
    作    者   : m00217266
    修改内容   : 修改GMM_SndSmServiceRej接口，添加原因值


  7.日    期   : 2015年1月14日
    作    者   : w00167002
    修改内容   : DTS2015010509687:DSDS优化,在业务建联失败NO RF后，需要SM重新触发PDP
                 激活，这样通知WAS发起发起资源抢占。
                 在NORMAL SERVICE时候收到NO RF rel时，通过REL IND通知SM当前需要重新触发PDP
                 激活，这样通知WAS发起发起资源抢占。
  8.日    期   : 2015年1月15日
    作    者   : z00161729
    修改内容   : AT&T 支持DAM特性修改
*******************************************************************************/
VOS_VOID Gmm_RcvRrmmEstCnf_ServReqInit(
                                   VOS_VOID *pMsg                               /* 原语指针                                 */
                                   )
{
    VOS_UINT32           ulCause;                                               /* 定义局部变量                             */
    RRMM_EST_CNF_STRU   *pRrEstCnf = (RRMM_EST_CNF_STRU *)pMsg;                 /* 定义指针                                 */

    Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);

    if (0 != g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk)
    {                                                                           /* 有其他消息保留                           */
        if (GMM_TRUE == Gmm_DealWithBuffInProc())
        {                                                                       /* 保留消息处理成功                         */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvRrmmEstCnf_ServReqInit:NORMAL: Deal Hold Msg success");
            return;
        }
    }

    if ((RRC_EST_SUCCESS == pRrEstCnf->ulResult)
        || (RRC_EST_PRESENT == pRrEstCnf->ulResult))
    {                                                                           /* 信令连接建立成功                         */
        Gmm_TimerStart(GMM_TIMER_T3317);                                        /* 起T3317                                  */
    }
    else
    {                                                                           /* 信令连接建立失败                         */
        if (RRC_EST_OTHER_ACCESS_BARRED == pRrEstCnf->ulResult)
        {                                                                       /* 接入阻塞                                 */
            ulCause = NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED;

            /* 当前是SM发起的 Service Request流程, 给SM 回复 Service Rej 消息，以释放上层应用。 */
            if ((GMM_SERVICE_REQUEST_SIGNALLING == g_GmmGlobalCtrl.ucSpecProc)
                && (GMM_TRUE == g_GmmServiceCtrl.ucSmFlg))
            {
                GMM_SndSmServiceRej(GMM_SM_CAUSE_ACCESS_BARRED);

                g_GmmServiceCtrl.ucSmFlg = GMM_FALSE;
            }
        }
        else
        {
            ulCause = NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL;
        }

        NAS_NORMAL_LOG(WUEPS_PID_GMM, "Gmm_RcvRrmmEstCnf_ServReqInit(): call Gmm_ComCnfHandle to clear msg buffer");

        /* 此处不上报服务状态是因为接入层可能已经点了无服务的灯，如果上报会更改灯状态 */
        g_GmmGlobalCtrl.ucNeedChgServiceStatus = VOS_FALSE;
        Gmm_ComStaChg(g_GmmGlobalCtrl.ucServPreSta);                            /* 调用状态的公共处理                       */
        g_GmmGlobalCtrl.ucNeedChgServiceStatus = VOS_TRUE;
        Gmm_ComCnfHandle();

        NAS_GMM_ProcSavedMmT3211ExpiredNotify();

        if (GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
        {                                                                       /* 状态是GMM-REGISTERED NORMAL-SERVICE      */
            if (GMM_TIMER_T3311_FLG
                == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3311_FLG))
            {                                                                   /* 存在被挂起的T3311                        */
                Gmm_TimerResume(GMM_TIMER_T3311);                               /* 恢复T3311                                */
            }
            else if (GMM_TIMER_T3302_FLG
                == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3302_FLG))
            {                                                                   /* 存在被挂起的T3302                        */
                Gmm_TimerResume(GMM_TIMER_T3302);                               /* 恢复T3302                                */
            }
            else
            {
#if (FEATURE_LTE == FEATURE_ON)
                if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
                {
                    NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
                }
#endif
                Gmm_TimerStart(GMM_TIMER_T3312);                                /* 起T3312                                  */
            }
        }
        else if (GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM
                 == g_GmmGlobalCtrl.ucState)
        {
            if (GMM_TIMER_T3311_FLG
                == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3311_FLG))
            {                                                                   /* 存在被挂起的T3311                        */
                Gmm_TimerResume(GMM_TIMER_T3311);                               /* 恢复T3311                                */
            }
            else if (GMM_TIMER_T3302_FLG
                == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3302_FLG))
            {                                                                   /* 存在被挂起的T3302                        */
                Gmm_TimerResume(GMM_TIMER_T3302);                               /* 恢复T3302                                */
            }
            else
            {
            }
        }
        else
        {
        }

        if ((VOS_TRUE == NAS_MML_GetDailRejectCfg())
         && (NAS_MML_REG_FAIL_CAUSE_RR_CONN_EST_FAIL == ulCause))
        {
            GMM_SndSmServiceRej(GMM_SM_CAUSE_RRC_EST_FAIL);
            g_GmmServiceCtrl.ucSmFlg = GMM_FALSE;
        }


        /* 如果当前是NO RF的建联失败，则通知SM需要重新发起PDP激活 */
        else if ( (GMM_FALSE         == GMM_IsCasGsmMode())
          && (RRC_EST_RJ_NO_RF  == pRrEstCnf->ulResult) )
        {
            Gmm_SndSmRelInd();
            g_GmmServiceCtrl.ucSmFlg = GMM_FALSE;
        }
        else
        {

        }

        NAS_GMM_SndMmGmmActionResultInd(GMMMM_ACTION_FAILURE,
                                        ulCause);                             /* 发送MMCGMM_GMM_ACTION_RESULT_IND()       */


        /* 向MMC发送service request结果 */
        NAS_GMM_SndMmcServiceRequestResultInd(GMM_MMC_ACTION_RESULT_FAILURE,
                                              (NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16)ulCause);
        /* 事件上报 */
        NAS_EventReport(WUEPS_PID_GMM,
                        NAS_OM_EVENT_DATA_SERVICE_REJ,
                        (VOS_VOID *)&ulCause,
                        NAS_OM_EVENT_SERVICE_REJ_LEN);

        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* 清除当前流程                             */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmEstCnf_ServReqInit:INFO: specific procedure ended");
    }

    NAS_GMM_ProcSavedMmT3211ExpiredNotify();

    return;
}

/*******************************************************************************
  Module   : Gmm_RcvRrmmEstCnf_DeregNmlServ
  Function : 在GMM-DEREGISTERED.NORMAL-SERVICE状态下收到原语RRMM_EST_CNF 的处理
  Input    : VOS_VOID     *pMsg    原语指针
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2003.12.09  新规作成
    2. x51137 2007/4/2 A32D09789
    3.日    期   : 2009年5月9日
      作    者   : l00130025
      修改内容   : 根据问题单号：AT2D11645/AT2D11797,关机，若detach的EST_REQ失败，Gmm会反复发起EST_REQ
*******************************************************************************/
VOS_VOID Gmm_RcvRrmmEstCnf_DeregNmlServ(
                                    VOS_VOID *pMsg                              /* 原语指针                                 */
                                    )
{
    RRMM_EST_CNF_STRU      *pRrEstCnf;                                          /* 定义指针                                 */
    NAS_MSG_STRU           *pNasMsg;                                            /* 定义指针                                 */

    pRrEstCnf = (RRMM_EST_CNF_STRU *)pMsg;                                      /* 初始化指针                               */

    Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);

    if ((GMM_DETACH_COMBINED_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc)
        || (GMM_DETACH_NORMAL_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc))
    {                                                                           /* 当前流程为power off流程                  */
        if (RRC_EST_PRESENT == pRrEstCnf->ulResult)
        {
            pNasMsg = Gmm_DetachRequestMsgMake();                               /* DETACH REQUEST消息作成                   */

            Gmm_SndRrmmDataReq (RRC_NAS_MSG_PRIORTY_HIGH, pNasMsg);             /* 发送RRMM_EST_REQ                         */
        }
        else if (RRC_EST_SUCCESS != pRrEstCnf->ulResult)
        {                                                                       /* 信令连接建立失败                         */
            g_GmmGlobalCtrl.stPowerOffCtrl.ulEstResult = pRrEstCnf->ulResult;
        }
        else
        {
        }
    }
    if ((GMM_DETACH_COMBINED_SIM_REMOVE  == g_GmmGlobalCtrl.ucSpecProc)
        || (GMM_DETACH_NORMAL_SIM_REMOVE == g_GmmGlobalCtrl.ucSpecProc))
    {                                                                           /* 当前流程为SIM卡拔出的detach流程          */
        if (RRC_EST_PRESENT == pRrEstCnf->ulResult)
        {
            pNasMsg = Gmm_DetachRequestMsgMake();                               /* DETACH REQUEST消息作成                   */

            Gmm_SndRrmmDataReq (RRC_NAS_MSG_PRIORTY_HIGH, pNasMsg);             /* 发送RRMM_EST_REQ                         */
        }
        else if (RRC_EST_SUCCESS != pRrEstCnf->ulResult)
        {                                                                       /* 信令连接建立失败                         */
            g_GmmGlobalCtrl.stPowerOffCtrl.ulEstResult = pRrEstCnf->ulResult;
        }
        else
        {
        }
    }
    return;
}

/*******************************************************************************
  Module   : Gmm_RcvRrmmEstCnf_RegImsiDtchInit
  Function : 在GMM-REGISTERED.IMSI-DETACH-INITIATED状态下
             收到原语RRMM_EST_CNF 的处理
  Input    : VOS_VOID     *pMsg    原语指针
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
  1. 张志勇  2003.12.09  新规作成
  2. 日    期   : 2008年9月18日
     作    者   : ouyangfei 00132663
     修改内容   : 根据问题单号：AT2D05816，在GMM过程中，来自CM层的SMS请求应该被缓存，等GMM过程结束再发起。
  3. 日    期   : 2011年07月13日
     作    者   : w00166186
     修改内容   : V7R1 PHASE II ATTACH/DETACH调整
  4.日    期   : 2011年7月27日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
*******************************************************************************/
VOS_VOID Gmm_RcvRrmmEstCnf_RegImsiDtchInit(
                                       VOS_VOID *pMsg                               /* 原语指针                                 */
                                       )
{
    RRMM_EST_CNF_STRU   *pRrEstCnf = (RRMM_EST_CNF_STRU *)pMsg;                 /* 定义指针                                 */

    Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);

    if (0 != g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk)
    {                                                                           /* 有其他消息保留                           */
        if (GMM_TRUE == Gmm_DealWithBuffInProc())
        {                                                                       /* 保留消息处理成功                         */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvRrmmEstCnf_RegImsiDtchInit:NORMAL: Deal Hold Msg success");
            return;
        }
    }

    if ((RRC_EST_SUCCESS == pRrEstCnf->ulResult)
     || (RRC_EST_PRESENT == pRrEstCnf->ulResult))
    {                                                                           /* 信令连接建立成功                         */
        Gmm_TimerStart(GMM_TIMER_T3321);                                        /* 起T3321                                  */
    }
    else
    {                                                                           /* 信令连接建立失败                         */
        Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);                           /* 调用状态的公共处理                       */
        if (GMM_UEID_P_TMSI_SIGNATURE
            == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
            & GMM_UEID_P_TMSI_SIGNATURE))
        {                                                                       /* DETACH成功且使用了P_TMSI_SIGNATURE       */
            g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
                &= ~GMM_UEID_P_TMSI_SIGNATURE;                                  /* 清除P_TMSI_SIGNATURE                     */

            NAS_MML_InitUeIdPtmsiSignatureInvalid();

            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* 更新SIM卡信息                            */
            }
            else
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
            }
        }
        /* 判断等待标志是否存在，如果存在则向MMC,MM发送DETACH信息 */
        if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
        {
            NAS_GMM_SndMmcMmDetachInfo();
        }
        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
        if (GMM_TIMER_T3311_FLG
            == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3311_FLG))
        {                                                                       /* 存在被挂起的T3311                        */
            Gmm_TimerResume(GMM_TIMER_T3311);                                   /* 恢复T3311                                */
        }
        else if (GMM_TIMER_T3302_FLG
            == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3302_FLG))
        {                                                                       /* 存在被挂起的T3302                        */
            Gmm_TimerResume(GMM_TIMER_T3302);                                   /* 恢复T3302                                */
        }
        else
        {
#if (FEATURE_LTE == FEATURE_ON)
            if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
            {
                NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
            }
#endif
            Gmm_TimerStart(GMM_TIMER_T3312);                                    /* 起T3312                                  */
        }
        g_GmmGlobalCtrl.ucSpecProc               = GMM_NULL_PROCEDURE;          /* 清除当前流程                             */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmEstCnf_RegImsiDtchInit:INFO: specific procedure ended");
    }
    return;
}

/*******************************************************************************
  Module   : Gmm_RcvRrmmRelInd
  Function : 收到原语RRMM_REL_IND 的处理
  Input    : VOS_VOID     *pMsg    原语指针
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2003.12.09  新规作成
    2. 日    期   : 2007年12月08日
       作    者   : l00107747
       修改内容   : 根据问题单号：A32D13826
    3. 日    期   : 2008年9月18日
       作    者   : ouyangfei 00132663
       修改内容   : 根据问题单号：AT2D05816，在GMM过程中，来自CM层的SMS请求应该被缓存，等GMM过程结束再发起。
    4. 日    期   : 2009年03月31日
       作    者   : L65478
       修改内容   : 根据问题单号：AT2D10529两次鉴权失败后没有释放RRC连接

    5.日    期   : 2011年7月14日
      作    者   : zhoujun 40661
      修改内容   : 更新MML_CTX中的链接存在状态
    6.日    期   : 2011年12月15日
      作    者   : W00166186
      修改内容   : DTS20111205018756,大于上次时长，且没有经过完整性保护的3312定时器时长生效
                   不符合协议规范
    7.日    期   : 2012年3月07日
      作    者   : w00166186
      修改内容   : CSFB&PPAC&ETWS&ISR 开发
    8.日    期   : 2012年6月13日
      作    者   : l00130025
      修改内容   : DTS2012061302495:RB重建，发生小区重选,RAI变化时,链路释放后，没有通知RABM释放。导致无法数传
    9.日    期   : 2012年08月18日
      作    者   : l65478
      修改内容   : 问题单号：DTS2012081506413:NMOI下PS detach后,MM不发起注册
   10.日    期   : 2011年12月28日
      作    者  : l00167671
      修改内容  : 修改问题单DTS2012122001075,问题单场景如下:
                 PS建链过程中发生RA改变，该场景中如果CS域有业务则PS域做RAU
				 会被不确定的推迟到CS连接释放时才做，修改此场景中的操作如下:
				 若CS域有业务则给WAS发送RRMM_REL_REQ请求，请WAS释放连接，
				 并保存系统消息。在收到WAS的RRMM_REL_IND时用保存的系统消息做RAU
   11. 日    期   : 2013年8月2日
       作    者  : z00234330
       修改内容  :stk项目修改
   12.日    期  :2014年01月09日
      作    者  :l65478
      修改内容  :DTS2014010704608:第一次鉴权响应和网络发起的第二次鉴权请求冲突
   13.日    期  :2014年07月09日
      作    者  :s00217060
      修改内容  :DTS2014070205755:等接入层est_cnf时收到rel_ind,延迟15s再发attach
   14.日    期  :2014年07月28日
      作    者  :b00269685
      修改内容  :DTS2014072802678:等接入层est_cnf时收到rel_ind,停止保护定时器
   15.日    期   : 2015年1月15日
      作    者   : z00161729
      修改内容   : AT&T 支持DAM特性修改
   16.日    期   : 2015年6月5日
      作    者   : z00161729
      修改内容   : 24008 23122 R11 CR升级项目修改
*******************************************************************************/
VOS_VOID Gmm_RcvRrmmRelInd(
                       VOS_VOID *pMsg                                           /* 原语指针                                 */
                       )
{
    VOS_VOID                *pAddr;
    RRMM_REL_IND_STRU       *pRrRelInd;                                         /* 定义指针                                 */

    pRrRelInd = (RRMM_REL_IND_STRU *)pMsg;                                      /* 初始化指针                               */

    /* 如果不是PS域的，GMM丢弃不处理 */
    /* 如果是在以下几个状态等待est_cnf，并且rel cause为RRC_REL_CAUSE_NAS_DATA_ABSENT，丢弃不处理:
        GMM_REGISTERED_INITIATED:
        GMM_DEREGISTERED_INITIATED:
        GMM_ROUTING_AREA_UPDATING_INITIATED:
        GMM_SERVICE_REQUEST_INITIATED:
        GMM_REGISTERED_IMSI_DETACH_INITIATED:
    */
    if (VOS_FALSE == NAS_GMM_IsNeedProcRelInd(pRrRelInd))
    {
        return;
    }



    g_MmSubLyrShare.GmmShare.ucPsIntegrityProtect =
                                    NAS_MML_RRC_INTEGRITY_PROTECT_DEACTIVE;

    /* 清除鉴权相关全局变量 */
    NAS_GMM_ClearAuthInfo();

    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* 停止T3318                                */
    Gmm_TimerStop(GMM_TIMER_T3319);                                             /* 停止T3319                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* 停止T3320                                */
    Gmm_TimerStop(GMM_TIMER_T3340);                                             /* 停止T3340                                */
        
    Gmm_TimerStop(GMM_TIMER_DELAY_PS_SMS_CONN_REL);                       


    if (GMM_RRC_RRMM_EST_CNF_FLG ==
        (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG))
    {
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_RRC_RRMM_EST_CNF_FLG;                  /* 清等待响应标志                           */
        Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);
    }

    /* 如果缓存有关机事件在收到REL_IND时需要处理 */
    if (GMM_MSG_HOLD_FOR_POWEROFF
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_POWEROFF))
    {                                                                           /* 如果有保留的power off原语                */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmRelInd:INFO:DEAL HOLD_POWEROFF_MSG");
        Gmm_TimerStop( GMM_TIMER_PROTECT_FOR_SIGNALING );
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_RRC_RRMM_EST_CNF_FLG;
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPowerOff;       /* 读取power off原语地址                    */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_POWEROFF;     /* 清除保留标志                             */
        Gmm_MsgDistribute( pAddr );                                             /* 保留的消息分发                           */
        Gmm_MemFree( pAddr );
        Gmm_HoldBufferFree();                                                   /* 将保留buffer中所有的消息释放             */
        return;
    }

    switch(pRrRelInd->ulRelCause)
    {
    case RRC_REL_CAUSE_RR_NORM_EVENT:
    case RRC_REL_CAUSE_CELL_UPDATE_FAIL:
    case RRC_REL_CAUSE_T315_EXPIRED:
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_NORMAL_EVENT;
        break;
    case RRC_REL_CAUSE_RR_UNSPEC:
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CASUE_UNSPECIFIED;
        break;
    case RRC_REL_CAUSE_RR_PRE_EMPT_REL:
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CASUE_PRE_EMPTIVE_RELEASE;
        break;
    case RRC_REL_CAUSE_RR_CONGEST:
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_CONGESTION;
        break;
    case RRC_REL_CAUSE_RR_RE_EST_REJ:
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_RE_ESTABLISH_REJ;
        break;
    case RRC_REL_CAUSE_RR_USER_INACT:
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_USER_INACTIVITY;
        break;
    case RRC_REL_CAUSE_RR_DRIECT_SIGN_CONN_EST:
        g_GmmGlobalCtrl.ucRelCause =
                 RR_REL_CAUSE_DIRECTED_SINGNALING_CONNECTION_RE_ESTABLISHMENT;
        break;
    case RRC_REL_CAUSE_NAS_REL_ABSENT:
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_ABORT_RR_UNEXIST_CONNECTION;
        break;
    case RRC_REL_CAUSE_NAS_REL_SUCCESS:
    case RRC_REL_CAUSE_NAS_ABORT:
    case RRC_REL_CAUSE_NAS_STOP_SETUP:
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_ABORT_RR_NORMAL;
        break;
    default:
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_RR_CONNECTION_FAILURE;
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmRelInd:INFO: The Relase Cause is default");
        break;

    }

    g_GmmGlobalCtrl.ucCipherStartFlg = GMM_FALSE;

    if (GMM_TC_ACTIVE == g_GmmGlobalCtrl.ucState)
    {
        if (GMM_TRUE == GMM_IsCasGsmMode())
        {
            g_GmmGlobalCtrl.ucSigConFlg = GMM_TRUE;         /* 2G下信令连接标志始终有效 */
        }
        else
        {
            g_GmmGlobalCtrl.ucSigConFlg = GMM_FALSE;        /* 3G下信令连接标志清除 */
        }

        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmRelInd:INFO: PS signatual nonexist");
        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
        if (GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucTcPreSta)
        {
            g_GmmGlobalCtrl.ucTcPreSta = GMM_REGISTERED_NORMAL_SERVICE;
            g_GmmGlobalCtrl.ucSpecProc   = GMM_NULL_PROCEDURE;
            g_GmmGlobalCtrl.ucServPreSta = GMM_NULL;
        }
        if (GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucTcPreSta)
        {
#if (FEATURE_LTE == FEATURE_ON)
            if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
            {
                NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
            }
#endif
            Gmm_TimerStart(GMM_TIMER_T3312);                                    /* 起T3312                                  */
            Gmm_TimerPauseForTc(GMM_TIMER_T3312);                               /* 挂起T3312                                */
        }
        return;
    }

    if (((GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
          ||(GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM == g_GmmGlobalCtrl.ucState))
        &&(GMM_MSG_HOLD_FOR_SMS == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SMS)) )
    {   /* 当前有缓存的 SMS 消息,且当前过程正常结束,发起缓存的SMS呼叫 */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmRelInd:INFO: Buffered SMS Request will be handled.");
    }
    else
    {
        if (!((GMM_TRUE == g_GmmServiceCtrl.ucSmsFlg)
            && (GMM_TRUE == g_GmmGlobalCtrl.ucFollowOnFlg)))
        {

            if (GMM_MSG_HOLD_FOR_SMS
                ==(g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SMS))
            {
                Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSMS);
                g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SMS;
                g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSMS = (VOS_UINT32)VOS_NULL_PTR;

                g_GmmServiceCtrl.ucSmsFlg = GMM_FALSE;
            }

            /* Added by z00234330 for V9R1 STK升级, 2013/07/11, begin */

            /* GCF34.4.8.1测试不通过，由于在G下发短信时候收到T3314超时，此处通知SMS释放 */
            if ( NAS_MML_NET_RAT_TYPE_GSM != NAS_MML_GetCurrNetRatType() )
            {
                Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);                      /* 发送PMMSMS_ERROR_IND                     */
            }

            /* Added by z00234330 for V9R1 STK升级, 2013/07/11, end */
        }
    }

    /* GMM收到接入层的连接释放指示，RABM也一定会收到接入层的连接释放指示，RABM
       收到释放指示后会终止当前的RAB重建过程，此时GMM就没有必要继续缓存RABM的
       重建消息了;此时WRR可能没有重建RB,需要GMM通知RABM 建链失败*/
    if (GMM_MSG_HOLD_FOR_SERVICE
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SERVICE))
    {                                                                           /* 如果有保留的ServiceRequest原语           */
        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForService);               /* 将保留buffer中所有的消息释放             */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SERVICE;
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForService = (VOS_UINT32)VOS_NULL_PTR;

        Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);                 /* 通知RABM结果                             */
    }
    if ((GMM_TRUE == g_GmmGlobalCtrl.ucFollowOnFlg)
        &&(GMM_SERVICE_REQUEST_DATA_IDLE == g_GmmGlobalCtrl.ucSpecProcHold))
    {
        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

        g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;

        Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);                 /* 通知RABM结果                             */
    }

    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        g_GmmGlobalCtrl.ucSigConFlg = GMM_TRUE;                                 /* 2G下信令连接标志始终有效 */
    }
    else
    {
        g_GmmGlobalCtrl.ucSigConFlg = GMM_FALSE;                                /* 3G下信令连接标志清除 */
        /* W下清除RRC信令状态 */
        NAS_MML_SetPsSigConnStatusFlg(VOS_FALSE);


        NAS_GMM_DeleteRandAndResInfoInPmmIdleMode();

        if (RRC_RRC_CONN_STATUS_ABSENT == pRrRelInd->ulRrcConnStatus)
        {
            NAS_MML_SetRrcConnStatusFlg(VOS_FALSE);
        }
    }

    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmRelInd:INFO: PS signatual nonexist");

    if ( VOS_TRUE == NAS_MML_GetCsSigConnStatusFlg() )
    {
        if (VOS_TRUE == NAS_GMM_ProcSavedWasSysInfo())
        {
            NAS_GMM_FreeWasSysInfo();
            return;
        }
    }
    NAS_GMM_FreeWasSysInfo();

    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* 根据状态分发                             */
    case GMM_REGISTERED_INITIATED:
        Gmm_RcvRrmmRelInd_RegInit(pRrRelInd);
        break;
    case GMM_DEREGISTERED_INITIATED:
        Gmm_RcvRrmmRelInd_DeregInit(pRrRelInd);
        break;
    case GMM_ROUTING_AREA_UPDATING_INITIATED:
        Gmm_RcvRrmmRelInd_RauInit(pRrRelInd);
        break;
    case GMM_SERVICE_REQUEST_INITIATED:
        Gmm_RcvRrmmRelInd_ServReqInit(pRrRelInd);
        break;
    case GMM_REGISTERED_NORMAL_SERVICE:
    case GMM_REGISTERED_UPDATE_NEEDED:
        Gmm_RcvRrmmRelInd_RegNmlServ(pRrRelInd);
        break;
    case GMM_REGISTERED_IMSI_DETACH_INITIATED:
        Gmm_RcvRrmmRelInd_RegImsiDtchInit(pRrRelInd);
        break;
    case GMM_DEREGISTERED_NORMAL_SERVICE:
        Gmm_RcvRrmmRelInd_DeregNmlServ();
        break;
    case GMM_REGISTERED_PLMN_SEARCH:
    case GMM_DEREGISTERED_PLMN_SEARCH:
        Gmm_RcvRrmmRelInd_PlmnSearch();
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvRrmmRelInd:WARNING: g_GmmGlobalCtrl.ucState is WRong");
        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
        break;
    }

    /* W下，链路释放后，清除GMM链路控制变量 */
    if (VOS_FALSE == GMM_IsCasGsmMode())
    {
        NAS_GMM_ClearGmmLinkCtrlStru();
    }

    /* 在连接释放后，如果缓存的有PS DETACH消息,进行PS detach */
    if (GMM_MSG_HOLD_FOR_DETACH
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_DETACH))
    {                                                                           /* 如果有保留的DETACH原语                   */
        Gmm_MsgDistribute((VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach);  /* 保留的消息分发                           */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_DETACH;       /* 清除缓存标志                             */
        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach);
    }

    NAS_GMM_ProcSavedMmT3211ExpiredNotify();
    return;
}

/*******************************************************************************
Module   : Gmm_RcvRrmmRelInd_DeregNmlServ
Function : 在GMM-DEREGISTERED-NORMAL-SERVICE状态下收到原语RRMM_REL_IND 的处理
Input    : 无
Output   : 无
NOTE     : 无
Return   : 无
History  :
1. 张志勇  2005.02.22  新规作成
2.日    期   : 2009年5月9日
  作    者   : l00130025
  修改内容   : 根据问题单号：AT2D11645/AT2D11797,关机，若detach的EST_REQ失败，Gmm会反复发起EST_REQ
3.日    期   : 2011年07月13日
  作    者   : w00166186
  修改内容   : V7R1 PHASE II ATTACH/DETACH调整
4.日    期   : 2011年7月27日
  作    者   : h44270
  修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
5.日    期   : 2011年11月8日
  作    者   : s46746
  修改内容   : V7R1 PhaseII阶段解决关机慢问题
*******************************************************************************/
VOS_VOID Gmm_RcvRrmmRelInd_DeregNmlServ(VOS_VOID)
{

    Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);

    if ((GMM_DETACH_COMBINED_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc)
        || (GMM_DETACH_NORMAL_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc))
    {                                                                           /* 当前流程为power off流程                  */
        Gmm_TimerStop(GMM_TIMER_1S);                                            /* 停5s保护Timer                            */

        NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_DETACH_FINISH,
                    VOS_NULL_PTR,
                    NAS_OM_EVENT_NO_PARA);

        if (GMM_UEID_P_TMSI_SIGNATURE
            == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
            & GMM_UEID_P_TMSI_SIGNATURE))
        {                                                                       /* DETACH成功且使用了P_TMSI_SIGNATURE       */
            g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
                &= ~GMM_UEID_P_TMSI_SIGNATURE;                                  /* 清除P_TMSI_SIGNATURE                     */

            NAS_MML_InitUeIdPtmsiSignatureInvalid();

            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* 更新SIM卡信息                            */
            }
            else
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
            }
        }

        if (GMM_DETACH_COMBINED_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc)
        {
            NAS_GMM_SndMmGprsDetachComplete();
        }

        Gmm_ComStaChg(GMM_NULL);
        Gmm_SndMmcPowerOffCnf();                                                /* 发送MMCGMM_POWER_OFF_CNF                 */
        /*Gmm_TimerDistroy();*/                                                     /* 销毁所有Timer                            */
        Gmm_ComVariantInit();                                                   /* 清除全局变量                             */
    }
    if ((GMM_DETACH_COMBINED_SIM_REMOVE  == g_GmmGlobalCtrl.ucSpecProc)
        || (GMM_DETACH_NORMAL_SIM_REMOVE == g_GmmGlobalCtrl.ucSpecProc))
    {                                                                           /* 当前流程为SIM卡拔出的detach流程          */
        NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_DETACH_FINISH,
                    VOS_NULL_PTR,
                    NAS_OM_EVENT_NO_PARA);

        Gmm_TimerStop(GMM_TIMER_1S);                                            /* 停5s保护Timer                            */
        Gmm_ComStaChg(GMM_DEREGISTERED_NO_IMSI);                                /* 调用状态的公共处理                       */
        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* 清当前流程                               */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmRelInd_DeregNmlServ:INFO: specific procedure ended");
    }

}

/*******************************************************************************
  Module   : Gmm_RcvRrmmRelInd_RegInit
  Function : 在GMM-REGISTERED-INITIATED状态下收到原语RRMM_REL_IND 的处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2003.12.09  新规作成
    2.日    期   : 2010年01月04日
      作    者   : w00166186
      修改内容   : 问题单号:DTS2010122004132 W CS ONLY PDP激活过程重定向到G,PDP激活失败
    3.日    期   : 2012年12月6日
      作    者   : t00212959
      修改内容   : 问题单号:DTS2012120704835 清除RAU标志应该在Return前
    4.日    期  :2014年01月09日
      作    者  :l65478
      修改内容  :DTS2014010704608:第一次鉴权响应和网络发起的第二次鉴权请求冲突
*******************************************************************************/
VOS_VOID Gmm_RcvRrmmRelInd_RegInit(RRMM_REL_IND_STRU *pRrRelInd)
{
    VOS_UINT8                           ucRst;

    Gmm_TimerStop(GMM_TIMER_T3310);                                             /* 停T3310                                  */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* 停止T3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* 停止T3320                                */

    Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);

    g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg  = GMM_FALSE;                        /* 清除标志                                 */
    g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg = GMM_FALSE;                        /* 清除标志                                 */

    /* 检查是否需要重新发起Attach 流程*/
    ucRst = NAS_GMM_RetryAttachProcedureCheck(pRrRelInd->ulRelCause,
                pRrRelInd->ulRrcConnStatus);
    if (VOS_TRUE ==  ucRst)
    {
        if (RRC_RRC_CONN_STATUS_PRESENT == pRrRelInd->ulRrcConnStatus )
        {
            /* RRC链路存在，直接重新发起Attach流程 */
            Gmm_AttachInitiate(GMM_NULL_PROCEDURE);
        }
        else
        {
            /* 记录标志位，在收到系统消息后重新发起attach流程 */
            g_GmmAttachCtrl.ucRetryAttachForRelCtrlFlg = VOS_TRUE;
        }
        return;
    }

    g_GmmAttachCtrl.ucRetryFlg = GMM_TRUE;                                      /* 设置换小区不进行attach标志               */


    Gmm_AttachAttemptCounter(NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL);                        /* 调用attach attempt counter的处理         */


    /* 判断等待标志是否存在，如果存在则发送MMCGMM_ATTACH CNF */
    if (GMM_WAIT_PS_ATTACH == (g_GmmGlobalCtrl.stAttachInfo.enAttachType
                             & GMM_WAIT_PS_ATTACH))
    {
        NAS_GMM_SndMmcAttachCnf();
    }
    g_GmmGlobalCtrl.stAttachInfo.enAttachType = GMM_WAIT_NULL_ATTACH;


    g_GmmGlobalCtrl.ucSpecProc    = GMM_NULL_PROCEDURE;                         /* 清除正在进行的specific过程标志           */
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmRelInd_RegInit:INFO: specific procedure ended");
    g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;                                  /* 清除fallowon标志                         */
    NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvRrmmRelInd_DeregInit
  Function : 在GMM-DEREGISTERED-INITIATED状态下收到原语RRMM_REL_IND 的处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
  1. 张志勇  2003.12.09  新规作成
  2.日    期   : 2006年3月24日
    作    者   : liuyang id:48197
    修改内容   : 问题单号：A32D01882，网侧释放RR连接指示重建连接，当前重建时
                 所填建立RR连接原因错误
  3.日    期   : 2010年12月03日
    作    者   : w00166186
    修改内容   : DTS2010112403161 搜网整理发现问题
  4.日    期   : 2011年07月13日
    作    者   : w00166186
    修改内容   : V7R1 PHASE II ATTACH/DETACH调整
  5.日    期   : 2011年7月27日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  6. 日    期   : 2012年1月12日
     作    者   : w00166186
     修改内容   : DTS2011122704039:开机搜网后CS注册被拒#12,PS注册被拒#14，在ON
                   PLMN状态，服务域被设置为不支持GMM需要将服务域不支持信息通知给MMC.
  7.日    期   : 2012年12月11日
    作    者   : l00167671
    修改内容   : DTS2012121802573, TQE清理

  8.日    期   : 2013年8月7日
    作    者   : w00167002
    修改内容   : DTS2013080207367:在CS only时候，用户发起PDP激活，网络模式I时候，
                 会触发联合注册.用户发起PDP去激活，会导致PS域的去注册。收到网侧
                 的去注册成功后需要通知MM，否则MM当前在NORMAL SERVICE状态，不
                 触发T3212定时器的启动，长时间可能导致丢寻呼.
*******************************************************************************/
VOS_VOID Gmm_RcvRrmmRelInd_DeregInit(RRMM_REL_IND_STRU *pRrRelInd)
{
    VOS_UINT8                           ucRst;
    RRC_REL_CAUSE_ENUM_UINT32           ulRelCause;

    ulRelCause = pRrRelInd->ulRelCause;

    Gmm_TimerStop(GMM_TIMER_T3321);                                             /* 停T3321                                  */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* 停止T3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* 停止T3320                                */
#if (FEATURE_LTE == FEATURE_ON)
    if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
    {
        NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
    }
#endif
    Gmm_TimerStop(GMM_TIMER_T3312);

    if (VOS_OK !=
        Mm_StopRelTimer(WUEPS_PID_GMM, GMM_TIMER_PROTECT_FOR_RR_REL, &g_stGmmProtectRrRelTimer))
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_StopRelTimer:WARNING: Stop timer unsuccessfully");
    }
    g_GmmTimerMng.ulTimerRunMask &= ~(0x00000001 << GMM_TIMER_PROTECT_FOR_RR_REL);

    if (RRC_REL_CAUSE_RR_DRIECT_SIGN_CONN_EST != ulRelCause)
    {
        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
    }

    /* 检查是否需要重新发起Detach 流程 */
    ucRst = NAS_GMM_RetryDetachProcedureCheck(ulRelCause,
                pRrRelInd->ulRrcConnStatus);
    if (VOS_TRUE ==  ucRst)
    {
        if (RRC_RRC_CONN_STATUS_PRESENT == pRrRelInd->ulRrcConnStatus )
        {
            /* RRC链路存在，直接重新发起Detach流程 */
            Gmm_Com_MsInitNormalDetach();
        }
        else
        {
            /* 记录标志位，在收到系统消息后重新发起Detach流程 */
            g_GmmDetachCtrl.ucRetryDetachForRelCtrlFlg = VOS_TRUE;
        }
        return;
    }

    /*接收到了Detach Accept消息或之前未注册成功*/
    if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
    {
        Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);                             /* 调用状态的公共处理                       */

        if (GMM_UEID_P_TMSI_SIGNATURE
            == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask & GMM_UEID_P_TMSI_SIGNATURE))
        {                                                                           /* DETACH成功且使用了P_TMSI_SIGNATURE       */
            g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI_SIGNATURE;   /* 清除P_TMSI_SIGNATURE                     */

            NAS_MML_InitUeIdPtmsiSignatureInvalid();

            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* 更新SIM卡信息                            */
            }
            else
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
            }
        }
    }
    else
    {
        Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);

        if (GMM_DETACH_NORMAL_NETMODE_CHANGE != g_GmmGlobalCtrl.ucSpecProc)
        {
            NAS_MML_SetPsAttachAllowFlg( VOS_FALSE );
        }
    }

    /* 判断等待标志是否存在，如果存在则向MMC,MM发送DETACH信息 */
    if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
    {
        NAS_GMM_SndMmcMmDetachInfo();
    }
    else
    {
        /* 收到网侧的去注册成功后需要通知MM，否则MM不启动T3212定时器 */
        NAS_GMM_SndMmGprsDetachComplete();
    }


    /* 向MMC发送PS注册结果 */
    NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                 GMM_MMC_ACTION_RESULT_FAILURE,
                                 NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                            /* 将流程清空                               */

    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmRelInd_DeregInit:INFO: specific procedure ended");

    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvRrmmRelInd_RauInit
  Function : 在GMM-ROUTING-AREA-UPDATING-INITIATED状态下
             收到原语RRMM_REL_IND 的处理
  Input    : RRMM_REL_IND_STRU *pRrRelInd  RRMM_REL_IND_STRU类型指针
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2003.12.09  新规作成
    2.日    期   : 2006年3月24日
      作    者   : liuyang id:48197
      修改内容   : 问题单号：A32D01882，网侧释放RR连接指示重建连接，当前重建时
                   所填建立RR连接原因错误
    3.日    期   : 2009年01月15日
      作    者   : l00130025
      修改内容   : 问题单号:AT2D07018,LAU或RAU过程中搜网和SYSCFG设置,发起底层释放链接的操作
    4.日    期   : 2012年12月6日
      作    者   : t00212959
      修改内容   : 问题单号:DTS2012120704835 CSFB第一次LAURAU都释放导致失败后再做CSFB会多发RAU
*******************************************************************************/
VOS_VOID Gmm_RcvRrmmRelInd_RauInit(
                               RRMM_REL_IND_STRU *pRrRelInd                     /* RRMM_REL_IND_STRU类型指针                */
                               )
{
    VOS_UINT8                           ucRst;

    Gmm_TimerStop(GMM_TIMER_T3330);                                             /* 停T3330                                  */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* 停止T3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* 停止T3320                                */

    g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg  = GMM_FALSE;                        /* 清除标志                                 */
    g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg = GMM_FALSE;                        /* 清除标志                                 */

    if (RRC_REL_CAUSE_RR_DRIECT_SIGN_CONN_EST == pRrRelInd->ulRelCause)
    {
        return;
    }

    Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);

    /* 检查是否需要重新发起RAU 流程*/
    ucRst = NAS_GMM_RetryRauProcedureCheck(pRrRelInd->ulRelCause,
                pRrRelInd->ulRrcConnStatus);
    if (VOS_TRUE ==  ucRst)
    {
        if (RRC_RRC_CONN_STATUS_PRESENT == pRrRelInd->ulRrcConnStatus )
        {
            /* RRC链路存在，直接重新发起RAU流程 */
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        }
        else
        {
            /* 记录标志位，在收到系统消息后重新发起RAU流程 */
            g_GmmRauCtrl.ucRetryRauForRelCtrlFlg = VOS_TRUE;
        }
        return;
    }

    /* RAU过程中收到SM请求，被缓存，如果RAU失败，判断当前是否有SM缓存请求，有则给SM发送REL消息 */
    if ((GMM_FALSE == GMM_IsCasGsmMode())
     && (GMM_MSG_HOLD_FOR_SM ==(g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SM))
     && (  (RRC_REL_CAUSE_RR_NORM_EVENT     == pRrRelInd->ulRelCause)
        || (RRC_REL_CAUSE_RR_USER_INACT     == pRrRelInd->ulRelCause)
        || (RRC_REL_CAUSE_CELL_UPDATE_FAIL  == pRrRelInd->ulRelCause)
        || (RRC_REL_CAUSE_T315_EXPIRED      == pRrRelInd->ulRelCause) ))
    {
        NAS_NORMAL_LOG(WUEPS_PID_GMM, "Gmm_RcvRrmmRelInd_RauInit(): RAU fail, notify SM when there's SM msg cached");

        Gmm_SndSmRelInd();
    }

    g_GmmRauCtrl.ucRetryFlg = GMM_TRUE;                                     /* 设置换小区需要进行RAU标志                */
    Gmm_RoutingAreaUpdateAttemptCounter(NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL);         /* 调用RAU attempt counter的处理            */


    /* 判断等待标志是否存在，如果存在则发送MMCGMM_ATTACH CNF */
    if (GMM_WAIT_PS_ATTACH == (g_GmmGlobalCtrl.stAttachInfo.enAttachType
                             & GMM_WAIT_PS_ATTACH))
    {
        NAS_GMM_SndMmcAttachCnf();
    }
    g_GmmGlobalCtrl.stAttachInfo.enAttachType = GMM_WAIT_NULL_ATTACH;

    if (GMM_RAU_FOR_NORMAL != gstGmmSuspendCtrl.ucRauCause)
    {
        GMM_RauFailureInterSys();
    }
    else
    {
        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_FAILURE);
    }

    return;
}

/*******************************************************************************
  Module   : Gmm_RcvRrmmRelInd_ServReqInit
  Function : 在GMM-SERVICE-REQUEST-INITIATED状态下收到原语RRMM_REL_IND 的处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2003.12.09  新规作成
    2.日    期   : 2006年3月24日
      作    者   : liuyang id:48197
      修改内容   : 问题单号：A32D01882，网侧释放RR连接指示重建连接，当前重建时
                   所填建立RR连接原因错误
    3.日    期   : 2009年08月13日
      作    者   : l65478
      修改内容   : 问题单号：AT2D13662,3G下上报了out of coverage后总是会接着上报PS_Service
    4.日    期   : 2010年09月27日
      作    者   : z00161729
      修改内容   : 问题单号：AT2D19560
    5.日    期   : 2011年09月6日
      作    者   : s46746
      修改内容   : 同步V3R1版本问题单DTS2011072005340
    6.日    期   : 2012年02月16日
      作    者   : L65478
      修改内容   : 问题单号;DTS2012021602026,GCF测试失败,PDP激活被网络拒绝后立刻又重新发起了PDP激活请求
    7.日    期   : 2012年3月17日
      作    者   : w00176964
      修改内容   : DTS2012031900095 V7R1 C30 SBM&EM定制需求:增加拨号被拒定制
    8.日    期  : 2012年08月24日
      作    者  : m00217266
      修改内容  : 修改接口GMM_SndSmServiceRej，添加原因值
    9.日    期  : 2013年06月5日
      作    者  : w00242748
      修改内容  : svlte和usim接口调整

    10.日    期   : 2015年1月14日
       作    者   : w00167002
       修改内容   : DTS2015010509687:DSDS优化,在业务建联失败NO RF后，需要SM重新触发PDP
                 激活，这样通知WAS发起发起资源抢占。
                 在NORMAL SERVICE时候收到NO RF rel时，通过REL IND通知SM当前需要重新触发PDP
                 激活，这样通知WAS发起发起资源抢占。

*******************************************************************************/
VOS_VOID Gmm_RcvRrmmRelInd_ServReqInit(
                                   RRMM_REL_IND_STRU *pRrRelInd
                                   )
{
    VOS_UINT8                           ucRst;
    NAS_MSG_STRU                       *pServiceReqMsg;
    VOS_UINT8                           ucDellRejectEnableFlg;
    VOS_UINT32                          ulIsTestCardFlg;

    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause;
    enCause = NAS_MML_REG_FAIL_CAUSE_RR_CONN_FAIL;

    ulIsTestCardFlg = NAS_USIMMAPI_IsTestCard();

    /* 获取拨号被拒定制是否使能 */
    ucDellRejectEnableFlg = NAS_MML_GetDailRejectCfg();

    Gmm_TimerStop(GMM_TIMER_T3317);
    Gmm_TimerStop(GMM_TIMER_T3318);
    Gmm_TimerStop(GMM_TIMER_T3320);

    Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);

    /* 检查是否需要重新发起SR流程*/
    ucRst = NAS_GMM_RetrySrProcedureCheck(pRrRelInd->ulRelCause,
                pRrRelInd->ulRrcConnStatus);
    if (VOS_TRUE ==  ucRst)
    {
        if (RRC_RRC_CONN_STATUS_PRESENT == pRrRelInd->ulRrcConnStatus )
        {
            /* RRC链路存在，直接重新发起SR流程 */
            pServiceReqMsg = Gmm_ServiceRequestMsgMake();

            if (VOS_NULL_PTR != pServiceReqMsg)
            {
                Gmm_SndRrmmEstReq(g_GmmGlobalCtrl.ulEstCause,
                                  GMM_RRC_IDNNS_UNKNOWN,
                                  pServiceReqMsg);

                Gmm_TimerStart(GMM_TIMER_PROTECT_FOR_SIGNALING);

                /* 此时PS信令连接已经释放,因此过程应该是idle态进行数据业务请求 */
                g_GmmGlobalCtrl.ucSpecProc = GMM_SERVICE_REQUEST_DATA_IDLE;
            }
        }
        else
        {
            /* 记录标志位，在收到系统消息后,根据g_GmmGlobalCtrl.MsgHold中的缓存，
                重新发起SR流程 */
            Gmm_ComStaChg(g_GmmGlobalCtrl.ucServPreSta);                                /* 调用状态的公共处理                       */
            g_GmmServiceCtrl.ucRetrySrForRelCtrlFlg = VOS_TRUE;

        }
        return;
    }

    if (((RRC_REL_CAUSE_RR_NORM_EVENT       == pRrRelInd->ulRelCause)
      || (RRC_REL_CAUSE_RR_USER_INACT       == pRrRelInd->ulRelCause)
      || (RRC_REL_CAUSE_CELL_UPDATE_FAIL    == pRrRelInd->ulRelCause)
      || (RRC_REL_CAUSE_T315_EXPIRED        == pRrRelInd->ulRelCause)
      || (RRC_REL_CAUSE_NO_RF               == pRrRelInd->ulRelCause))
     && (GMM_SERVICE_REQUEST_PAGING_RSP != g_GmmGlobalCtrl.ucSpecProc)
     && (VOS_FALSE == ulIsTestCardFlg)
     && (VOS_FALSE == ucDellRejectEnableFlg))
    {
        Gmm_SndSmRelInd();
    }

    if (VOS_TRUE == ucDellRejectEnableFlg)
    {
        GMM_SndSmServiceRej(GMM_SM_CAUSE_UNKNOWN);

        g_GmmServiceCtrl.ucSmFlg = GMM_FALSE;
    }

    Gmm_ComStaChg(g_GmmGlobalCtrl.ucServPreSta);                                /* 调用状态的公共处理                       */
    NAS_GMM_SndMmGmmActionResultInd(GMMMM_ACTION_FAILURE,
                                    enCause);                                         /* 发送MMCGMM_GMM_ACTION_RESULT_IND()       */


    /* 向MMC发送service request结果 */
    NAS_GMM_SndMmcServiceRequestResultInd(GMM_MMC_ACTION_RESULT_FAILURE,
                                          enCause);
    /* 事件上报 */
    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_DATA_SERVICE_REJ,
                    (VOS_VOID *)&enCause,
                    NAS_OM_EVENT_SERVICE_REJ_LEN);

    NAS_NORMAL_LOG(WUEPS_PID_GMM, "Gmm_RcvRrmmRelInd_ServReqInit(): call Gmm_ComCnfHandle to clear msg buffer");

    Gmm_ComCnfHandle();

    if (GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
    {                                                                           /* 状态是GMM-REGISTERED NORMAL-SERVICE      */
        if (GMM_TIMER_T3311_FLG
            == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3311_FLG))
        {                                                                       /* 存在被挂起的T3311                        */
            Gmm_TimerResume(GMM_TIMER_T3311);                                   /* 恢复T3311                                */
        }
        else if (GMM_TIMER_T3302_FLG
            == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3302_FLG))
        {                                                                       /* 存在被挂起的T3302                        */
            Gmm_TimerResume(GMM_TIMER_T3302);                                   /* 恢复T3302                                */
        }
        else
        {
#if (FEATURE_LTE == FEATURE_ON)
            if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
            {
                NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
            }
#endif
            Gmm_TimerStart(GMM_TIMER_T3312);                                    /* 起T3312                                  */
        }
    }
    else if (GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM
                 == g_GmmGlobalCtrl.ucState)
    {
        if (GMM_TIMER_T3311_FLG
            == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3311_FLG))
        {                                                                       /* 存在被挂起的T3311                        */
            Gmm_TimerResume(GMM_TIMER_T3311);                                   /* 恢复T3311                                */
        }
        else if (GMM_TIMER_T3302_FLG
            == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3302_FLG))
        {                                                                       /* 存在被挂起的T3302                        */
            Gmm_TimerResume(GMM_TIMER_T3302);                                   /* 恢复T3302                                */
        }
        else
        {
        }
    }
    else
    {
    }

    if (RRC_REL_CAUSE_RR_DRIECT_SIGN_CONN_EST == pRrRelInd->ulRelCause)
    {                                                                           /* Directed signalling connection           *
                                                                                 * re-establishment                         */
    }
    else
    {                                                                           /* 其他原因                                 */
        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* 清除当前流程                             */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmRelInd_ServReqInit:INFO: specific procedure ended");
    }

    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvRrmmRelInd_RegNmlServ
  Function : 在GMM-REGISTERED.NORMAL-SERVICE状态下收到原语RRMM_REL_IND 的处理
  Input    : VOS_VOID    *pRrRelInd       消息指针
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2003.12.09  新规作成
    2.日    期   : 2006年3月24日
      作    者   : liuyang id:48197
      修改内容   : 问题单号：A32D01882，网侧释放RR连接指示重建连接，当前重建时
                   所填建立RR连接原因错误
    3.日    期   : 2007年11月1日
      作    者   : l65478
      修改内容   : 问题单号：A32D13307，释放原因值#5，没有释放缓存
    4.日    期   : 2009年01月15日
      作    者   : l00130025
      修改内容   : 问题单号:AT2D07018,LAU或RAU过程中搜网和SYSCFG设置,发起底层释放链接的操作
    5.日    期   : 2011年7月26日
      作    者   : l00130025
      修改内容   : V7R1 PhaseII阶段调整，删除UserDelay标志，由MMC处理
    6.日    期   : 2012年02月16日
      作    者   : L65478
      修改内容   : 问题单号;DTS2012021602026,GCF测试失败,PDP激活被网络拒绝后立刻又重新发起了PDP激活请求
    7.日    期   : 2013年6月5日
      作    者   : w00242748
      修改内容   : SVLTE和USIM接口调整
    8.日    期   : 2014年7月28日
      作    者   : b00269685
      修改内容   : DTS2014072802678:注册成功后，启动T3340等待链接释放，收到SM的激活请求，
                   进行缓存，此后若是再收到WRR连接释放，不需要通知SM连接释放
    9.日    期   : 2015年1月14日
      作    者   : w00167002
      修改内容   : DTS2015010509687:DSDS优化,在业务建联失败NO RF后，需要SM重新触发PDP
                 激活，这样通知WAS发起发起资源抢占。
                 在NORMAL SERVICE时候收到NO RF rel时，通过REL IND通知SM当前需要重新触发PDP
                 激活，这样通知WAS发起发起资源抢占。
    10.日    期   : 2015年8月13日
       作    者   : l00289540
       修改内容   : User_Exp_Improve修改
*******************************************************************************/
VOS_VOID Gmm_RcvRrmmRelInd_RegNmlServ(
                                  RRMM_REL_IND_STRU *pRrRelInd                  /* 消息指针                                 */
                                  )
{
    VOS_UINT32                          ulIsTestCardFlg;

    ulIsTestCardFlg = NAS_USIMMAPI_IsTestCard();

    /* 开机注册过程中，收到SM的激活请求，注册成功后，立即在原链路上将激活请求发给
        网侧，链路被释放，此时需要通知SM链路释放消息,以重新发起 */
    if ((GMM_FALSE == GMM_IsCasGsmMode())
     && (  (RRC_REL_CAUSE_RR_NORM_EVENT     == pRrRelInd->ulRelCause)
        || (RRC_REL_CAUSE_RR_USER_INACT     == pRrRelInd->ulRelCause)
        || (RRC_REL_CAUSE_CELL_UPDATE_FAIL  == pRrRelInd->ulRelCause)
        || (RRC_REL_CAUSE_T315_EXPIRED      == pRrRelInd->ulRelCause)
        || (RRC_REL_CAUSE_NO_RF             == pRrRelInd->ulRelCause))
     && (GMM_SERVICE_REQUEST_PAGING_RSP != g_GmmGlobalCtrl.ucSpecProc)
     && (VOS_FALSE == ulIsTestCardFlg)
     && (GMM_MSG_HOLD_FOR_SM
            != (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &
                                        GMM_MSG_HOLD_FOR_SM)))
    {
        NAS_NORMAL_LOG(WUEPS_PID_GMM, "Gmm_RcvRrmmRelInd_RegNmlServ(): Connection release, notify SM when there's SM msg cached");

        Gmm_SndSmRelInd();
    }

    if (RRC_REL_CAUSE_RR_DRIECT_SIGN_CONN_EST == pRrRelInd->ulRelCause)
    {                                                                           /* 如果RRC释放原因为Directed signalling con
                                                                                 * nection re-establishment                 */
        /* 在正常状态下，只有可能有缓存的SR消息，所以此处只需要清除SR */
        if(GMM_MSG_HOLD_FOR_SERVICE
            == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SERVICE))
        {
            g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SERVICE;      /* 清除缓存标志                             */
            Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForService);
        }

        Gmm_TimerStart(GMM_TIMER_T3312);

        return;
    }
    Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
#if (FEATURE_LTE == FEATURE_ON)
    if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
    {
        NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
    }
#endif

    Gmm_TimerStart(GMM_TIMER_T3312);                                            /* 起T3312                                  */

    if (GMM_RAU_FOR_INTERSYSTEM == gstGmmSuspendCtrl.ucRauCause)
    {
        GMM_RauSuccessInterSys();
    }

    if(GMM_FALSE == g_GmmGlobalCtrl.ucRaiChgRelFlg)
    {
        /* 当前REL后不需要发起RAU，可以处理缓存的流程 */
        NAS_GMM_HandleDelayedEvent();
    }

    return;
}

/*******************************************************************************
  Module   : Gmm_RcvRrmmRelInd_RegImsiDtchInit
  Function : 在GMM-REGISTERED.IMSI-DETACH-INITIATED状态下
             收到原语RRMM_REL_IND 的处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
  1. 张志勇  2003.12.09  新规作成
  2.日    期   : 2006年3月24日
    作    者   : liuyang id:48197
    修改内容   : 问题单号：A32D01882，网侧释放RR连接指示重建连接，当前重建时
                 所填建立RR连接原因错误
  3.日    期   : 2011年07月13日
    作    者   : w00166186
    修改内容   : V7R1 PHASE II ATTACH/DETACH调整
  4.日    期   : 2011年7月27日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  5.日    期   : 2015年2月6日
    作    者   : h00313353
    修改内容   : USIMM卡接口调整
*******************************************************************************/
VOS_VOID Gmm_RcvRrmmRelInd_RegImsiDtchInit(RRMM_REL_IND_STRU *pRrRelInd)
{
    RRC_REL_CAUSE_ENUM_UINT32           ulRelCause;
    VOS_UINT8                           ucRst;

    ulRelCause = pRrRelInd->ulRelCause;

    Gmm_TimerStop(GMM_TIMER_T3321);                                             /* 停T3321                                  */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* 停止T3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* 停止T3320                                */

    if (RRC_REL_CAUSE_RR_DRIECT_SIGN_CONN_EST != ulRelCause)
    {
        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
    }

    /* 检查是否需要重新发起Detach 流程*/
    ucRst = NAS_GMM_RetryDetachProcedureCheck(ulRelCause,
                pRrRelInd->ulRrcConnStatus);
    if (VOS_TRUE ==  ucRst)
    {
        if (RRC_RRC_CONN_STATUS_PRESENT == pRrRelInd->ulRrcConnStatus )
        {
            /* RRC链路存在，直接重新发起Detach流程 */
            Gmm_Com_MsInitNormalDetach();
        }
        else
        {
            /* 记录标志位，在收到系统消息后重新发起Detach流程 */
            g_GmmDetachCtrl.ucRetryDetachForRelCtrlFlg = VOS_TRUE;
        }
        return;
    }

    Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);                               /* 调用状态的公共处理                       */
    if (GMM_UEID_P_TMSI_SIGNATURE
        == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask & GMM_UEID_P_TMSI_SIGNATURE))
    {                                                                           /* DETACH成功且使用了P_TMSI_SIGNATURE       */
        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI_SIGNATURE;   /* 清除P_TMSI_SIGNATURE                     */

        NAS_MML_InitUeIdPtmsiSignatureInvalid();

        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* 更新SIM卡信息                            */
        }
        else
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
        }
    }
    /* 判断等待标志是否存在，如果存在则向MMC,MM发送DETACH信息 */
    if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
    {
        NAS_GMM_SndMmcMmDetachInfo();
    }
    if (GMM_TIMER_T3311_FLG
        == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3311_FLG))
    {                                                                           /* 存在被挂起的T3311                        */
        Gmm_TimerResume(GMM_TIMER_T3311);                                       /* 恢复T3311                                */
    }
    else if (GMM_TIMER_T3302_FLG
        == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3302_FLG))
    {                                                                           /* 存在被挂起的T3302                        */
        Gmm_TimerResume(GMM_TIMER_T3302);                                       /* 恢复T3302                                */
    }
    else
    {
#if (FEATURE_LTE == FEATURE_ON)
        if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
        {
            NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
        }
#endif
        Gmm_TimerStart(GMM_TIMER_T3312);                                        /* 起T3312                                  */
    }
    g_GmmGlobalCtrl.ucSpecProc               = GMM_NULL_PROCEDURE;              /* 将流程清空                               */
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvRrmmRelInd_RegImsiDtchInit:INFO: specific procedure ended");

}

/*****************************************************************************
 函 数 名  : Gmm_RcvRrmmRelInd_PlmnSearch
 功能描述  : 搜网状态接收到连接释放消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年7月11日
   作    者   : s46746
   修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID Gmm_RcvRrmmRelInd_PlmnSearch()
{
    Gmm_TimerStop(GMM_TIMER_WAIT_CONNECT_REL);

    Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
}

/*******************************************************************************
  Module   : Gmm_RcvCoverLost_RegInit
  Function : 在GMM-DEREGISTERED-INITIATED状态下收到原语MMCGMM_COVERAGE_LOST_IND 的处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. s46746  2009.8.19  新规作成
    2.日    期  : 2012年08月24日
      作    者  : m00217266
      修改内容  : 修改Gmm_SndSmEstablishCnf接口，添加原因值
*******************************************************************************/
VOS_VOID Gmm_RcvCoverLost_RegInit(VOS_VOID)
{
    Gmm_TimerStop(GMM_TIMER_T3310);                                             /* 停T3310                                  */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* 停止T3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* 停止T3320                                */

    if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
    {                                                                           /* 需要上报给SM                             */
        Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_RRC_EST_FAIL);        /* 通知SM GMM注册失败                       */
        g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;                                 /* 清ucSmCnfFlg标志                         */
    }

    if ((NAS_MML_MS_MODE_CS_ONLY == NAS_MML_GetMsMode())
     && (VOS_FALSE == g_GmmGlobalCtrl.ucUserPsAttachFlag))
    {
        NAS_MML_SetPsAttachAllowFlg( VOS_FALSE );
    }

    g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg = GMM_FALSE;                         /* 清除标志                                 */
    g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg = GMM_FALSE;                        /* 清除标志                                 */

    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvCoverLost_DeregInit
  Function : 在GMM-DEREGISTERED-INITIATED状态下收到原语MMCGMM_COVERAGE_LOST_IND 的处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
  1. s46746  2009.8.19  新规作成
  2.日    期   : 2012年12月11日
    作    者   : l00167671
    修改内容   : DTS2012121802573, TQE清理
  3.日    期   : 2013年1月24日
    作    者   : w00176964
    修改内容   : DTS2013012408469:detach过程中丢网直接进行本地detach
  4.日    期   : 2013年8月7日
    作    者   : w00167002
    修改内容   : DTS2013080207367:在CS only时候，用户发起PDP激活，网络模式I时候，
                 会触发联合注册.用户发起PDP去激活，会导致PS域的去注册。收到网侧
                 的去注册成功后需要通知MM，否则MM当前在NORMAL SERVICE状态，不
                 触发T3212定时器的启动，长时间可能导致丢寻呼.
  5.日    期   : 2013年10月05日
    作    者   : l65478
    修改内容   : DTS2013092509860:GPRS detach过程被BG搜索终止后,GMM又自动发起了注册
*******************************************************************************/
VOS_VOID Gmm_RcvCoverLost_DeregInit()
{
    Gmm_TimerStop(GMM_TIMER_T3321);                                             /* 停T3321                                  */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* 停止T3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* 停止T3320                                */

    if ( VOS_OK !=
        Mm_StopRelTimer(WUEPS_PID_GMM, GMM_TIMER_PROTECT_FOR_RR_REL, &g_stGmmProtectRrRelTimer))
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_StopRelTimer:WARNING: Stop timer unsuccessfully");
    }
    g_GmmTimerMng.ulTimerRunMask &= ~(0x00000001 << GMM_TIMER_PROTECT_FOR_RR_REL);

    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                            /* 将流程清空                               */

    /* detach标记存在丢网时直接回复detach结果 */
    if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
    {
        if (GMM_WAIT_PS_DETACH == (g_GmmGlobalCtrl.stDetachInfo.enDetachType & GMM_WAIT_PS_DETACH))
        {
            NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);
        }
        NAS_GMM_SndMmcMmDetachInfo();
    }
    else
    {
        /* 收到网侧的去注册成功后需要通知MM，否则MM不启动T3212定时器 */
        NAS_GMM_SndMmGprsDetachComplete();
    }


    Gmm_ComStaChg(GMM_DEREGISTERED_NO_CELL_AVAILABLE);

    return;                                                                     /* 返回                                     */
}

/*****************************************************************************
 函 数 名  : NAS_GMM_ProcRauHoldProcedure_RcvCoverLost
 功能描述  : 路由区更新过程中出服务区，对缓存的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 消息类型
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期  : 2014年5月31日
    作    者  : s00246516
    修改内容 : 新生成函数
*****************************************************************************/
VOS_VOID NAS_GMM_ProcRauHoldProcedure_RcvCoverLost(VOS_VOID)
{

    /* MMC在发送Coverage lost后自行处理Detach或Attach结果 */
    switch (g_GmmGlobalCtrl.ucSpecProcHold)
    {                                                                       /* 保留的specific流程                       */
        case GMM_SERVICE_REQUEST_DATA_IDLE:
        case GMM_SERVICE_REQUEST_DATA_CONN:
            Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);             /* 通知RABM结果                             */
            break;

        case GMM_DETACH_COMBINED:

            if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
            {
                if (GMM_WAIT_PS_DETACH == (g_GmmGlobalCtrl.stDetachInfo.enDetachType & GMM_WAIT_PS_DETACH))
                {
                    Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);
                    Gmm_TimerStop(GMM_TIMER_T3302);
                    Gmm_TimerStop(GMM_TIMER_T3311);
                    g_GmmRauCtrl.ucRauAttmptCnt = 0;
                    NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);
                }

                NAS_GMM_SndMmcMmDetachInfo();
            }
            break;

        case GMM_DETACH_NORMAL:
        case GMM_DETACH_NORMAL_NETMODE_CHANGE:
            if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
            {
                if (GMM_WAIT_PS_DETACH == (g_GmmGlobalCtrl.stDetachInfo.enDetachType & GMM_WAIT_PS_DETACH))
                {
                    Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);
                    Gmm_TimerStop(GMM_TIMER_T3302);
                    Gmm_TimerStop(GMM_TIMER_T3311);
                    g_GmmRauCtrl.ucRauAttmptCnt = 0;
                    NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);
                }

                NAS_GMM_SndMmcMmDetachInfo();
            }

            if ( VOS_FALSE == NAS_MML_GetPsAttachAllowFlg() )
            {
                NAS_GMM_SndMmGprsDetachComplete();
            }
            break;

        case GMM_DETACH_WITH_IMSI:

            if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
            {
                NAS_GMM_SndMmcMmDetachInfo();
            }
            break;

        default:
            break;
    }

    g_GmmGlobalCtrl.ucFollowOnFlg  = GMM_FALSE;                                 /* 清除followon标志                         */
    NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

    g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;                        /* 清除正在进行的specific过程标志           */

    return;
}


/*******************************************************************************
  Module   : Gmm_RcvCoverLost_RauInit
  Function : 在GMM-RAU-INITIATED状态下收到原语MMCGMM_COVERAGE_LOST_IND 的处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. s46746  2009.8.19  新规作成
    2. 日    期   : 2012年7月17日
       作    者   : z00161729
       修改内容   : DTS2012071606177:W(LAI1)-L(TAI2/LAI2 ISR激活CS LAI改变)-W(LAI1网络模式I)需要
                    发起联合rau
    3. 日    期   : 2013年3月30日
       作    者   : l00167671
       修改内容   : 主动上报AT命令控制下移至C核
    4. 日    期   : 2014年05月31日
       作    者   : s00246516
       修改内容   : 路由区更新过程中出服务区，如果有缓存的Detach，没有回复
    5. 日    期   : 2015年2月6日
       作    者   : h00313353
       修改内容   : USIMM卡接口调整
    6.日    期   : 2015年6月5日
      作    者   : z00161729
      修改内容   : 24008 23122 R11 CR升级项目修改
*******************************************************************************/
VOS_VOID Gmm_RcvCoverLost_RauInit()
{
    NAS_MML_RAI_STRU                           *pstLastSuccRai;
    GMM_RAI_STRU                                stRai;
    NAS_MML_ROUTING_UPDATE_STATUS_ENUM_UINT8    enPsUpdateStatus;

    pstLastSuccRai      = NAS_MML_GetPsLastSuccRai();
    NAS_GMM_ConvertPlmnIdToGmmFormat(&(pstLastSuccRai->stLai.stPlmnId), &stRai.Lai.PlmnId);
    stRai.Lai.aucLac[0] = pstLastSuccRai->stLai.aucLac[0];
    stRai.Lai.aucLac[1] = pstLastSuccRai->stLai.aucLac[1];
    stRai.ucRac         = pstLastSuccRai->ucRac;

    Gmm_TimerStop(GMM_TIMER_T3330);                                             /* 停T3330                                  */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* 停止T3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* 停止T3320                                */

    g_GmmRauCtrl.ucRauAttmptCnt++;                                              /* RAU Attempt Counter加1                   */

    if (5 > g_GmmRauCtrl.ucRauAttmptCnt)
    {                                                                           /* ucRauAttmptCnt小于5                      */
        enPsUpdateStatus = NAS_MML_GetPsUpdateStatus();

        if ((GMM_TRUE == Gmm_Com_CmpRai(&stRai, &g_GmmGlobalCtrl.SysInfo.Rai, g_GmmGlobalCtrl.ucNetMod))
         && (NAS_MML_ROUTING_UPDATE_STATUS_UPDATED == enPsUpdateStatus))
        {                                                                       /* RAI相等且更新状态是GU1                   */
        }
        else
        {                                                                       /* RAI不相等或者更新状态不是GU1             */
            NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED);
            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* 更新SIM卡信息                            */
            }
            else
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
            }
        }
        Gmm_TimerStart(GMM_TIMER_T3311);
    }
    else
    {                                                                           /* ucRauAttmptCnt大于等于5                  */
        NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED);     /* 置更新状态为GU2                          */

        /* 在U2状态，保存当前的RAI信息 */
        NAS_GMM_SetAttemptUpdateRaiInfo(NAS_MML_GetCurrCampPlmnInfo());

        g_GmmRauCtrl.ucT3312ExpiredFlg = GMM_FALSE;                             /* 流程结束，清除3312溢出标志               */
        g_GmmGlobalCtrl.ucGprsResumeFlg = GMM_FALSE;

        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* 更新SIM卡信息                            */
        }
        else
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
        }

        /* 24008_CR1904R1_(Rel-11)_C1-113602 Handling of timer T3302 24008 4.7.2.x章节描述如下:
        The MS shall apply this value in the routing area registered by the MS, until a new value is received.
        The default value of this timer is used in the following cases:
        -   ATTACH ACCEPT message, ROUTING AREA UPDATE ACCEPT message, ATTACH REJECT message, or ROUTING AREA UPDATE REJECT message is received without a value specified;
        -   In Iu mode, if the network provides a value in a non-integrity protected Iu mode GMM message and the MS is not attaching for emergency services or not attached for emergency services;
        -   the MS does not have a stored value for this timer; or
        -   a new PLMN which is not in the list of equivalent PLMNs has been entered, the routing area updating fails and the routing area updating attempt counter is equal to 5.
        注册失败达5次，且上次下发t3302定时器时长的网络同当前驻留网络不同，或接入技术不同，则t3302使用默认值。*/
        if (VOS_TRUE == NAS_GMM_IsNeedUseDefaultT3302ValueRauAttempCntMax())
        {
            g_GmmTimerMng.aTimerInf[GMM_TIMER_T3302].ulTimerVal = GMM_TIMER_T3302_VALUE;
        }

        Gmm_TimerStart(GMM_TIMER_T3302);

    }

    /* deleted by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */

    /* deleted by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

    NAS_GMM_ProcRauHoldProcedure_RcvCoverLost();

    if (GMM_RAU_FOR_NORMAL != gstGmmSuspendCtrl.ucRauCause)
    {
        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_HANDOVER, GMM_RABM_RAU_FAILURE);

        gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_NORMAL;

        GMM_BufferMsgDump();
    }
    else
    {
        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_FAILURE);
    }

    return;
}

/*******************************************************************************
  Module   : Gmm_RcvCoverLost_ServReqInit
  Function : 在GMM-SERVICE-REQUEST-INITIATED状态下收到原语MMCGMM_COVERAGE_LOST_IND 的处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. s46746  2009.8.19  新规作成
*******************************************************************************/
VOS_VOID Gmm_RcvCoverLost_ServReqInit()
{
    Gmm_TimerStop(GMM_TIMER_T3317);                                             /* 停T3317                                  */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* 停止T3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* 停止T3320                                */

    if ((GMM_SERVICE_REQUEST_DATA_IDLE   == g_GmmGlobalCtrl.ucSpecProc)
        || (GMM_SERVICE_REQUEST_DATA_CONN == g_GmmGlobalCtrl.ucSpecProc))
    {                                                                           /* 当前流程为SR_DATA                        */
        Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);                 /* 通知RABM结果                             */
    }

    if ((GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucServPreSta)
     || (GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM
                 == g_GmmGlobalCtrl.ucServPreSta))
    {                                                                           /* 状态是GMM-REGISTERED NORMAL-SERVICE      */
        if (GMM_TIMER_T3311_FLG
            == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3311_FLG))
        {                                                                       /* 存在被挂起的T3311                        */
            Gmm_TimerResume(GMM_TIMER_T3311);                                   /* 恢复T3311                                */
        }
        else if (GMM_TIMER_T3302_FLG
            == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3302_FLG))
        {                                                                       /* 存在被挂起的T3302                        */
            Gmm_TimerResume(GMM_TIMER_T3302);                                   /* 恢复T3302                                */
        }
        else
        {
#if (FEATURE_LTE == FEATURE_ON)
            if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
            {
                NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
            }
#endif
            Gmm_TimerStart(GMM_TIMER_T3312);
        }
    }

    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvCoverLost_RegNmlServ
  Function : 在GMM-REGISTER-NORMAL-SERVICE状态下收到原语MMCGMM_COVERAGE_LOST_IND 的处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. s46746  2009.8.19  新规作成
*******************************************************************************/
VOS_VOID Gmm_RcvCoverLost_RegNmlServ()
{
    if ((GMM_TRUE == GMM_IsCasGsmMode())
     || (GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg))
    {
        return;
    }
#if (FEATURE_LTE == FEATURE_ON)
    if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
    {
        NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
    }
#endif

    Gmm_TimerStart(GMM_TIMER_T3312);

    return;
}

/*******************************************************************************
  Module   : Gmm_RcvCoverLost_RegImsiDtchInit
  Function : 在GMM-REGISTER-IMSI-DETACH-INIT状态下收到原语MMCGMM_COVERAGE_LOST_IND 的处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. s46746  2009.8.19  新规作成
*******************************************************************************/
VOS_VOID Gmm_RcvCoverLost_RegImsiDtchInit()
{
    Gmm_TimerStop(GMM_TIMER_T3321);                                             /* 停T3321                                  */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* 停止T3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* 停止T3320                                */

    if (GMM_TIMER_T3311_FLG
        == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3311_FLG))
    {                                                                           /* 存在被挂起的T3311                        */
        Gmm_TimerResume(GMM_TIMER_T3311);                                       /* 恢复T3311                                */
    }
    else if (GMM_TIMER_T3302_FLG
        == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3302_FLG))
    {                                                                           /* 存在被挂起的T3302                        */
        Gmm_TimerResume(GMM_TIMER_T3302);                                       /* 恢复T3302                                */
    }
    else
    {
#if (FEATURE_LTE == FEATURE_ON)
        if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
        {
            NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
        }
#endif
        Gmm_TimerStart(GMM_TIMER_T3312);                                        /* 起T3312                                  */
    }

    return;
}

/*******************************************************************************
  Module   : Gmm_RcvCoverLost_SuspendWaitForSys
  Function : 在GMM-SUSPEND-WAIT-FOR-SYSINFO状态下收到原语MMCGMM_COVERAGE_LOST_IND 的处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. s46746  2009.8.19  新规作成
    2.日    期   : 2014年12月25日
      作    者   : w00167002
      修改内容   : DTS2014122201960:在L下SRVCC HO到G再HO到W,RABM触发重建，导致立即
                   触发RAU，后续收到系统消息又再次发起RAU,导致网络REL了链路，导致
                   掉话。修改为在HO后，启动保护定时器等系统消息。
*******************************************************************************/
VOS_VOID Gmm_RcvCoverLost_SuspendWaitForSys()
{
    Gmm_TimerStop(GMM_TIMER_SUSPENDED);

    Gmm_TimerStop(GMM_TIMER_HO_WAIT_SYSINFO);

    g_GmmRauCtrl.ucNpduCnt = 0x0;
    if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_HANDOVER, GMM_RABM_RAU_FAILURE);
    }
    else
    {
#if 0
        GMM_SndRabmGprsInfoInd(GMM_RABM_GPRS_SUPPORTED, GMM_RABM_PROC_HANDOVER,
                       GMM_RABM_IMMEDIATELY_RAU);
#endif

        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_HANDOVER, GMM_RABM_RAU_FAILURE);
    }

    GMM_BufferMsgDump();
}

/*******************************************************************************
  Module   : Gmm_RcvSmDataReq
  Function : 原语GMMSM_DATA_REQ的接收处理
  Input    : VOS_VOID       *pMsg   指向原语的指针
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2003.12.11  新规作成
    2.日    期   : 2007年08月14日
      作    者   : luojian id:60022475
      修改内容   : 根据问题单号：A32D12689
    3.日    期   : 2007年11月13日
      作    者   : hanlufeng 41410
      修改内容   : 根据问题单号：A32D12187
    4.日    期   : 2007年12月18日
      作    者   : l00107747
      修改内容   : 根据问题单号：A32D13917,GMM处理SM缓存和当前不能处理需要缓存需要区别处理，
                   否则会造成内存问题
    5.日    期   : 2008年7月23日
      作    者   : luojian id:107747
      修改内容   : 根据问题单：AT2D04627/AT2D04237

    6.日    期   : 2010年4月13日
      作    者   : o00132663
      修改内容   : AT2D18275, GMM发起了不期望的PDP去激活
    7.日    期   : 2011年05月12日
      作    者   : h44270
      修改内容   : 根据问题单号：DTS2011051104889，出服务区后，进入到不支持GPRS小区，再重选回原来注册的小区，服务不可用
    8.日    期   : 2012年2月15日
      作    者   : w00166186
      修改内容   : CSFB&PPAC&ETWS&ISR 开发
    8.日    期   : 2012年05月12日
      作    者   : l65478
      修改内容   : 根据问题单号：DTS2012041707074,在RAU过程中收到网络PDP去激活,去激活接受消息无法发给网络
    9.日    期  : 2012年08月24日
      作    者  : m00217266
      修改内容  : 修改GMM_SndSmServiceRej接口，添加原因值
    10.日    期   : 2012年8月15日
      作    者   : z00161729
      修改内容   : DCM定制需求和遗留问题修改
   11.日    期   : 2012年12月11日
      作    者   : w00176964
      修改内容   : NAS_MML_GetPsRestrictNormalServiceFlg修改函数名
   12.日    期   : 2013年08月16日
      作    者   : l65478
      修改内容   : DTS2013091003969,L handover to W后收到鉴权消息没有处理

   13.日    期   : 2014年11月19日
      作    者   : w00167002
      修改内容   : DTS2014111803732:在收到彩信时候，激活PDP慢。没有等到SMC后直接
                   发起了PS PDP激活。修改为缓存，待SMC后触发PDP激活。
*******************************************************************************/
VOS_VOID Gmm_RcvSmDataReq(
                      VOS_VOID       *pMsg                                          /* 指向原语的指针                           */
                      )
{
    /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
    if ((VOS_TRUE == NAS_MML_GetPsRestrictNormalServiceFlg())
    /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */
     && (VOS_FALSE == g_GmmGlobalCtrl.ucSigConFlg))
    {/* 当前PS域接入受限，回复SM失败 */
        GMM_SndSmServiceRej(GMM_SM_CAUSE_ACCESS_BARRED);

        return;
    }

    NAS_GMM_ClearBufferedSmDataReq();

    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* 根据状态进行不同处理                     */
    case GMM_DEREGISTERED_INITIATED:                                            /* GMM_DEREGISTERED_INITIATED状态           */
        break;

    case GMM_ROUTING_AREA_UPDATING_INITIATED:
        NAS_GMM_ProcSmDataReq_RAUInit(pMsg);
        break;
    case GMM_SERVICE_REQUEST_INITIATED:

        if (GMM_SERVICE_REQUEST_DATA_CONN == g_GmmGlobalCtrl.ucSpecProc)
        {
            if (GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
            {
                Gmm_SndRrmmDataReqForCm(RRC_NAS_MSG_PRIORTY_HIGH,
                                        &((GMMSM_DATA_REQ_STRU *)pMsg)->SmMsg); /* 发送 RRMM_DATA_REQ                       */
            }
            else
            {
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvSmDataReq:NORMAL:Gmm Buf SM Data Req.");
                Gmm_BufSmDataReqMsg(pMsg);
            }
        }
        else
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvSmDataReq:NORMAL:Gmm Buf SM Data Req.");
            Gmm_BufSmDataReqMsg(pMsg);
        }
        break;

    case GMM_REGISTERED_IMSI_DETACH_INITIATED:                                  /* GMM-REGISTERED.IMSI-DETACH-INITIATED     */
    case GMM_REGISTERED_NORMAL_SERVICE:                                         /* GMM-REGISTERED.NORMAL-SERVICE            */
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:                                /* GMM-REGISTERED.ATTEMPTING-TO-UPDATE-MM   */
        Gmm_RcvSmDataReq_RegNmlServ(pMsg);
        break;
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
        Gmm_RcvCmServReq_RegAtmpToUpdt(pMsg);
        break;
    case GMM_REGISTERED_PLMN_SEARCH:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvSmDataReq:NORMAL:Gmm Buf SM Data Req.");
        Gmm_BufSmDataReqMsg(pMsg);

        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-15, begin */
        Gmm_SndMmcGprsServiceInd(NAS_MMC_GMM_GPRS_SERVICE_PDPACT);
        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-15, end */

        g_GmmGlobalCtrl.enServReq = GMM_SERVICE_REQ_PDPACT;
        break;

    case GMM_REGISTERED_LIMITED_SERVICE:
        if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
        {
            GMM_SndSmServiceRej(GMM_SM_CAUSE_GPRS_NOT_SUPPORT);
        }
        else if (g_GmmGlobalCtrl.SysInfo.ucForbMask != MMCGMM_GSM_NO_FORBIDDEN)
        {
            GMM_SndSmServiceRej(GMM_SM_CAUSE_FORBID_LA);
        }
        else
        {
            GMM_SndSmServiceRej(GMM_SM_CAUSE_UNKNOWN);
        }
        break;

    case GMM_REGISTERED_UPDATE_NEEDED:
        if (MM_COM_SRVST_NORMAL_SERVICE == NAS_GMM_GetRegUptNeededPsSrvStatus())
        {
            /* 按照正常服务下处理 */
            Gmm_RcvSmDataReq_RegNmlServ(pMsg);
        }
        else
        {
            GMM_SndSmServiceRej(GMM_SM_CAUSE_ACCESS_BARRED);

        }
        break;
    case GMM_REGISTERED_NO_CELL_AVAILABLE:
        break;

    case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
        NAS_GMM_RcvSmDataReq_SuspendWaitForSysinfo(pMsg);
        break;

    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvSmDataReq:WARNING: g_GmmGlobalCtrl.ucState is Error");
        break;
    }

    return;                                                                     /* 返回                                     */
}


/*****************************************************************************
 函 数 名  : NAS_GMM_RcvSmDataReq_SuspendWaitForSysinfo
 功能描述  : 在SUSPEND WAIT FOR SYSINFO状态下收到SM消息的处理
 输入参数  : pMsg        - 收到消息
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年9月26日
    作    者   : l65478
    修改内容   : 新生成函数

  2.日    期   : 2014年12月25日
    作    者   : w00167002
    修改内容   : DTS2014122201960:在SUSPEND WAIT FOR SYSINFO时候，如果定时器在
                运行，则继续等系统消息。
*****************************************************************************/
VOS_VOID NAS_GMM_RcvSmDataReq_SuspendWaitForSysinfo(
    VOS_VOID                            *pMsg
)
{
    if (VOS_FALSE == NAS_MML_GetSimPsRegStatus())
    {
        return;
    }

    if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
    {
        return;
    }

    /* 在从G切换到W时,需要首先发起RAU恢复PS,然后处理缓冲的SM消息 */
    if ((NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
     && (MMC_SUSPEND_CAUSE_HANDOVER == gstGmmSuspendCtrl.ucSuspendCause)
     && (NAS_MML_NET_RAT_TYPE_GSM   == gstGmmSuspendCtrl.ucPreRat))
    {
        Gmm_BufSmDataReqMsg(pMsg);

        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        g_GmmGlobalCtrl.ucSpecProcHold = GMM_SERVICE_REQUEST_SIGNALLING;


        /* 如果等系统消息定时器在运行，则不下发RAU */
        if (NAS_GMM_TIMER_HO_WAIT_SYSINFO_FLG == (NAS_GMM_TIMER_HO_WAIT_SYSINFO_FLG & g_GmmTimerMng.ulTimerRunMask))
        {
            return;
        }

        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
    }

    return;
}

/*******************************************************************************
  Module   : Gmm_BufferSmDataReq
  Function : 缓存SM发来的DATA_REQ消息
  Input    : VOS_VOID       *pMsg   指向原语的指针
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 欧阳飞 2010.01.07  新规作成
*******************************************************************************/
VOS_VOID Gmm_BufferSmDataReq(VOS_VOID       *pMsg)
{
    GMMSM_DATA_REQ_STRU      *pGmmSmDataReq;                                         /* GMMSM_DATA_REQ_STRU类型指针              */
    GMMSM_DATA_REQ_STRU      *ptr;

    pGmmSmDataReq = (GMMSM_DATA_REQ_STRU *)pMsg;

    if (4 > pGmmSmDataReq->SmMsg.ulNasMsgSize)
    {
        ptr = (GMMSM_DATA_REQ_STRU *)Gmm_MemMalloc(sizeof(GMMSM_DATA_REQ_STRU));
    }
    else
    {
        ptr = (GMMSM_DATA_REQ_STRU *)Gmm_MemMalloc((sizeof(GMMSM_DATA_REQ_STRU)
               + pGmmSmDataReq->SmMsg.ulNasMsgSize) - 4);
    }
    if (VOS_NULL_PTR == ptr)
    {
          PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvSmDataReq_DeregInit:WARNING: VOS_NULL_PTR pointer in Gmm_RcvSmDataReq_DeregInit");
          return;
    }
    if (4 > pGmmSmDataReq->SmMsg.ulNasMsgSize)
    {
        Gmm_MemCpy(ptr, pMsg, sizeof(GMMSM_DATA_REQ_STRU));
    }
    else
    {
        Gmm_MemCpy(ptr, pMsg, ((sizeof(GMMSM_DATA_REQ_STRU)
            + pGmmSmDataReq->SmMsg.ulNasMsgSize) - 4));
    }
    NAS_NORMAL_LOG(WUEPS_PID_GMM, "Gmm_BufferSmDataReq(): Cache SM data Req");

    g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSm = (VOS_UINT32)ptr;               /* 保留SM消息                               */
    g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk  |= GMM_MSG_HOLD_FOR_SM;           /* 置SM消息缓存标志                         */

    return;
}
/*****************************************************************************
 函 数 名  : Gmm_RcvCmServReq_RegAtmpToUpdt
 功能描述  : GMM_REGISTERED_ATTEMPTING_TO_UPDATE状态下收到CM服务请求的处理

 3gpp 24.008 4.2.5.1.4 : GMM-REGISTERED ATTEMPTING-TO-UPDATE:
    The MS shall use request from CM layers to trigger the combined routing area
 update procedure, if the network operates in network operation mode I.
 Depending on which of the timers T3311 or T3302 is running the MS shall stop
 the relevant timer and act as if the stopped timer has expired.

 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年7月23日
    作    者   : luojian id:107747
    修改内容   : 根据问题单：AT2D04627/AT2D04237,新生成函数,
  2.日    期   : 2015年1月5日
    作    者   : z00161729
    修改内容   : AT&T 支持DAM特性修改
*****************************************************************************/
VOS_VOID Gmm_RcvCmServReq_RegAtmpToUpdt(VOS_VOID *pMsg)
{
    MSG_HEADER_STRU                    *pMsgHeader;

    VOS_UINT32                          ulIsPlmnInSupportDamPlmnInfo;

    ulIsPlmnInSupportDamPlmnInfo = NAS_MML_IsPlmnSupportDam(NAS_MML_GetCurrCampPlmnId());

    pMsgHeader                          = (MSG_HEADER_STRU *)pMsg;

    GMM_LOG_INFO("Gmm_RcvSmDataReq_RegAtmpToUpdt.");

    if ( (WUEPS_PID_SMS == pMsgHeader->ulSenderPid)
      && (PMMSMS_EST_REQ == pMsgHeader->ulMsgName))
    {
        /* GMM-DEREGISTERED ATTEMPTING-TO-ATTACH状态下，当前版本不支持SMS发起发起PS服务请求 */
        Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);
        return;
    }
    if ( (WUEPS_PID_SM == pMsgHeader->ulSenderPid)
      && (GMMSM_DATA_REQ == pMsgHeader->ulMsgName)
      && (VOS_FALSE == ulIsPlmnInSupportDamPlmnInfo))
    {
        /*
        3gpp 24.008 4.7.5 : The routing area updating attempt counter shall be
        reset when the MS is in substate ATTEMPTING-TO-UPDATE and
            - a new routing area is entered;
            - expiry of timer T3302; or
            - at request from registration function.
        */

        /* 停止Timer3302 */
        Gmm_TimerStop(GMM_TIMER_T3302);

        /* 停止Timer3311*/
        Gmm_TimerStop(GMM_TIMER_T3311);

        /*发起RAU过程*/
        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        g_GmmGlobalCtrl.ucSpecProcHold = GMM_SERVICE_REQUEST_SIGNALLING;
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);

        /*缓存SM消息*/
        Gmm_BufSmDataReqMsg(pMsg);
        g_GmmGlobalCtrl.ulEstCause = ((GMMSM_DATA_REQ_STRU *)pMsg)->ulEstCause;
        return;
    }

    GMM_SndSmServiceRej(GMM_SM_CAUSE_PS_DETACH);
    return;
}

/*****************************************************************************
 函 数 名  : Gmm_RcvCmServReq_DeregAtmpToAtch
 功能描述  : GMM_REGISTERED_ATTEMPTING_TO_UPDATE状态下收到CM服务请求的处理
 3gpp 24.008 4.2.4.2.2 : GMM-DEREGISTERED ATTEMPTING-TO-ATTACH:
    use requests from CM layers to trigger the combined GPRS attach procedure,
 if the network operates in network operation mode I. Depending on which of the
 timers T3311 or T3302 is running the MS shall stop the elevant timer and act
 as if the stopped timer has expired..

 输入参数  : VOS_VOID *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年7月23日
    作    者   : luojian id:107747
    修改内容   : 根据问题单：AT2D04627/AT2D04237,新生成函数,
  2.日    期   : 2012年8月15日
    作    者   : z00161729
    修改内容   : DCM定制需求和遗留问题修改
  3.日    期   : 2015年1月5日
    作    者   : z00161729
    修改内容   : AT&T 支持DAM特性修改
*****************************************************************************/
VOS_VOID Gmm_RcvCmServReq_DeregAtmpToAtch(VOS_VOID *pMsg)
{
    MSG_HEADER_STRU                    *pMsgHeader;

    VOS_UINT32                          ulIsPlmnInSupportDamPlmnInfo;

    ulIsPlmnInSupportDamPlmnInfo = NAS_MML_IsPlmnSupportDam(NAS_MML_GetCurrCampPlmnId());

    pMsgHeader                          = (MSG_HEADER_STRU *)pMsg;


    GMM_LOG_INFO("Gmm_RcvCmServReq_DeregAtmpToAtch.");

    if ( (WUEPS_PID_SMS == pMsgHeader->ulSenderPid)
      && (PMMSMS_EST_REQ == pMsgHeader->ulMsgName))
    {
        /* GMM-DEREGISTERED ATTEMPTING-TO-ATTACH状态下，当前版本不支持SMS发起发起PS服务请求 */
        Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);
        return;
    }

    if ( (WUEPS_PID_SM == pMsgHeader->ulSenderPid)
      && (GMMSM_ESTABLISH_REQ == pMsgHeader->ulMsgName)
      && (VOS_FALSE == ulIsPlmnInSupportDamPlmnInfo))
    {
        /*
        3gpp 24.008 4.7.3 : The GPRS attach attempt counter shall be reset when the
        MS is in substate ATTEMPTING-TO-ATTACH and
            - expiry of timer T3302;
            - a new routing area is entered; or
            - an attach is triggered by CM sublayer requests.
        */
        g_GmmAttachCtrl.ucAttachAttmptCnt = 0;

        /* 置给SM回EST_CNF标志为TRUE */
        g_GmmAttachCtrl.ucSmCnfFlg        = GMM_TRUE;

        /* 设置follow on 标志 */
        g_GmmGlobalCtrl.ucFollowOnFlg     = GMM_TRUE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        /* 停止Timer3302 */
        Gmm_TimerStop(GMM_TIMER_T3302);

        /* 停止Timer3311 */
        Gmm_TimerStop(GMM_TIMER_T3311);

        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-15, begin */
        Gmm_SndMmcGprsServiceInd(NAS_MMC_GMM_GPRS_SERVICE_ATTACH);
        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-15, end */

        /*发起ATTACH过程*/
        Gmm_AttachInitiate(GMM_NULL_PROCEDURE);
        return;
    }

    Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_PS_DETACH);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_GetGmmSmDataReqMsgType
 功能描述  : 获取SM发给GMM的DATA_REQ消息中的消息类型
 输入参数  : pstMsg - 消息内容
 输出参数  : 无
 返 回 值  : 消息类型
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期  : 2010年11月08日
    作    者  : z00161729
    修改内容 : 新生成函数
*****************************************************************************/
VOS_UINT8 NAS_GMM_GetGmmSmDataReqMsgType(NAS_MSG_STRU *pstMsg)
{
    VOS_UINT8                           ucMsgType;

    if (0x70 == (pstMsg->aucNasMsg[0] & 0x70))
    {
        /* 存在扩展TI时,消息类型取自aucNasMsg[2] */
        ucMsgType  = pstMsg->aucNasMsg[2];
    }
    else
    {
        /* 获取消息类型取自aucNasMsg[1] */
        ucMsgType  = pstMsg->aucNasMsg[1];
    }

    return ucMsgType;

}

/*****************************************************************************
 函 数 名  : NAS_GMM_IsNeedSndSmDataReqMsg_T3340Running
 功能描述  : T3340运行期间收到sm的data req根据消息类型判断是缓存还是发到网络
 输入参数  : enMsgType - SM和GMM通过GMMSM_DATA_REQ交互时具体的消息类型
 输出参数  : 无
 返 回 值  : VOS_TRUE  - 需要把sm data req请求发给网络
             VOS_FALSE - 不需要把sm data req请求发给网络缓存

 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期  : 2014年10月22日
    作    者  : z00161729
    修改内容 : 新生成函数
*****************************************************************************/
VOS_UINT8 NAS_GMM_IsNeedSndSmDataReqMsg_T3340Running(
    GMMSM_DATA_REQ_MSGTYPE_ENUM_UINT32                      enMsgType
)
{
    if ((SM_STATUS == enMsgType)
     || (SM_MOD_PDP_CONTEXT_ACC_M2N == enMsgType)
     || (SM_DEACT_PDP_CONTEXT_ACC == enMsgType))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;

}



/*******************************************************************************
  Module   : Gmm_RcvSmDataReq_RegNmlServ
  Function : REGISTERED_NORMAL_SERVICE状态下原语GMMSM_DATA_REQ的接收处理
  Input    : VOS_VOID       *pMsg   指向原语的指针
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2003.12.11  新规作成
    2.日    期   : 2006年2月17日
      作    者   : liuyang id:48197
      修改内容   : 问题单号：A32D01287，打印错误
    3.日    期   : 2007年11月16日
      作    者   : hanlufeng 41410
      修改内容   : 问题单号：A32D12187
    4.日    期   : 2009年07月23日
      作    者   : l65478
      修改内容   : 问题单号:AT2D13173,没有判断接入模式，在G下发送了SR
    5.日    期   : 2010年11月06日
      作    者   : z00161729
      修改内容   : 问题单号:DTS2010110600919:GCF 11.3.1/11.3.2不通过,去激活后GMM启动T3340等待链路释放,
                   收到网侧modify pdp请求,sm回status消息,GMM缓存未发给网侧,导致GCF失败
    6.日    期   : 2010年11月09日
      作    者   : w00166186
      修改内容   : 问题单号:DTS2010110900902,  增加对REL_IND CAUSE值为
                   RR_REL_CAUSE_DIRECTED_SINGNALING_CONNECTION_RE_ESTABLISHMENT的处理
    7.日    期   : 2011年3月2日
      作    者   : z00161729
      修改内容   : DTS2010071601574:RAU过程完成收到rau accept需要等待RABM或WRR回复后再发送RAU cmp消息期间,
                   缓存sm请求,等RAU结束再发起
    8.日    期   : 2011年3月3日
      作    者   : z00161729
      修改内容   : DTS2011021201997:PS、CS完整性保护是否开启由GMM和MM分开维护,MMC不再维护
    9.日    期   : 2012年4月20日
      作    者   : l65478
      修改内容   : DTS2012041707566:BVT测试时,在发起PDP去激活前GMM主动释放了信令连接
   10.日    期   : 2013年2月06日
      作    者   : w00176964
      修改内容   : DTS2013020601874:G2W CS语音切换过程中,电话挂断后GPRS RESUME FAILURE,
                   用户发起PS彩信,G下在进行重选，此时第一条彩信发送失败
   11.日    期   : 2013年11月18日
      作    者   : w00167002
      修改内容   : DTS2013112006986:控制在3G TDD模式下是否需要开启SMC验证标记:中国移动拉萨网络设备在
                   TD下不发起SMC流程。
   12.日    期   : 2014年10月23日
      作    者   : z00161729
      修改内容   : DTS2014102403468:rau accept网络没有带follow on proceed，需要启动T3340，T3340运行期间后续收到网络pdp modify请求或去激活请求需要正常回复
*******************************************************************************/
VOS_VOID Gmm_RcvSmDataReq_RegNmlServ(
                                 VOS_VOID       *pMsg                           /* 指向原语的指针                           */
)
{
    NAS_MSG_STRU                       *pNasMsg;                                /* 定义指针                                 */
    VOS_UINT32                          ulEstCause;                             /* RRC连接建立原因                          */
    GMMSM_DATA_REQ_MSGTYPE_ENUM_UINT32  ucMsgType;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    VOS_UINT8                           ucIsUtranSmcNeeded;

    ucIsUtranSmcNeeded = NAS_UTRANCTRL_IsUtranPsSmcNeeded();

    enCurRat  = NAS_MML_GetCurrNetRatType();
    pNasMsg   = VOS_NULL_PTR;                                                     /* 初始化指针                               */
    ucMsgType = NAS_GMM_GetGmmSmDataReqMsgType(&((GMMSM_DATA_REQ_STRU *)pMsg)->SmMsg);

    if (VOS_TRUE == gstGmmCasGlobalCtrl.ucRauCmpFlg)
    {
        Gmm_BufferSmDataReq(pMsg);
        return;
    }

    if ((GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
        && (!((NAS_MML_NET_RAT_TYPE_GSM == enCurRat)
            && (GMM_RAU_FOR_WAITSERVICE == gstGmmSuspendCtrl.ucRauCause)
            && (gstGmmCasGlobalCtrl.ucLastDataSender !=
                                    enCurRat))))
    {                                                                           /* 当前有信令连接                           */
        if (NAS_MML_NET_RAT_TYPE_GSM == enCurRat)
        {
            /* RESUME FAIL 需要做RAU时，先缓存SM的消息，RAU后再进行处理*/
            if (GMM_TRUE == g_GmmGlobalCtrl.ucGprsResumeFlg)
            {
                Gmm_BufSmDataReqMsg(pMsg);
            }
            else
            {
                Gmm_SndRrmmDataReqForCm(RRC_NAS_MSG_PRIORTY_HIGH,
                                        &((GMMSM_DATA_REQ_STRU *)pMsg)->SmMsg);     /* 发送 RRMM_DATA_REQ                       */
            }
        }


        /* FDD/TDD收到完整性保护或者TDD下不需要完整性保护，也可以发起业务 */
        else if ( ( (VOS_TRUE                              == ucIsUtranSmcNeeded)
                  && (NAS_MML_RRC_INTEGRITY_PROTECT_ACTIVE == g_MmSubLyrShare.GmmShare.ucPsIntegrityProtect) )
               || ( (NAS_MML_NET_RAT_TYPE_WCDMA            == enCurRat)
                 && (VOS_FALSE                             == ucIsUtranSmcNeeded) ) )

        {
            /*判断T3340 是否运行 */
            if ((VOS_FALSE == NAS_GMM_IsNeedSndSmDataReqMsg_T3340Running(ucMsgType))
             && (GMM_TIMER_T3340_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3340_FLG)))
            {
                Gmm_BufferSmDataReq(pMsg);
            }
            else
            {
                Gmm_SndRrmmDataReqForCm(RRC_NAS_MSG_PRIORTY_HIGH,
                                        &((GMMSM_DATA_REQ_STRU *)pMsg)->SmMsg);     /* 发送 RRMM_DATA_REQ                       */
            }
        }
        else
        {
            /*完整性保护未打开，需缓存SM消息。
              通过service request可以打开完整性保护
              在GMM_SERVICE_REQUEST_INITIATED状态下,
              收到RRMM_SECURITY_IND(RRC_SECURITY_PS_SMC_RCV)消息，置完整性保护标志位
              收到RRMM_SECURITY_IND(RRC_SECURITY_PS_SMC_CMPL)消息，处理缓存的SM消息*/
            g_GmmGlobalCtrl.ucServPreSta = g_GmmGlobalCtrl.ucState;

            GMM_CasFsmStateChangeTo(GMM_SERVICE_REQUEST_INITIATED);

            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvSmDataReq_RegNmlServ:NORMAL: STATUS IS GMM_SERVICE_REQUEST_INITIATED");

            g_GmmServiceCtrl.ucSmFlg        = GMM_TRUE;
            g_MmSubLyrShare.GmmShare.ucDeatchEnableFlg = GMM_DETACH_ABLE;
            g_GmmGlobalCtrl.ucSpecProc   = GMM_SERVICE_REQUEST_SIGNALLING;          /* 存储当前的流程                           */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvSmDataReq_RegNmlServ:INFO: SR(signaling) procedure started");

            Gmm_BufSmDataReqMsg(pMsg);
            /*Service request*/
            pNasMsg = Gmm_ServiceRequestMsgMake();                          /* 调用make函数                             */

            Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pNasMsg);

            Gmm_TimerStop(GMM_TIMER_T3340);
        }
    }
    else if ((GMM_RAU_FOR_WAITSERVICE == gstGmmSuspendCtrl.ucRauCause)
          && (gstGmmCasGlobalCtrl.ucLastDataSender != enCurRat)
#if (FEATURE_ON == FEATURE_LTE)
          && (gstGmmCasGlobalCtrl.ucLastDataSender != NAS_MML_NET_RAT_TYPE_LTE)
#endif
          )
    {
        GMM_LOG_INFO("Gmm_RcvSmDataReq_RegNmlServ:Inter System change, Exec select RAU.");

        /*GMM_BufferMsgReceive(pMsg);*/
        Gmm_BufSmDataReqMsg(pMsg);
        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        g_GmmGlobalCtrl.ucSpecProcHold = GMM_SERVICE_REQUEST_SIGNALLING;

        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
    }
    /* 如果此前GMM在建连接的过程中由于RAI改变而主动要求释放正在建立的连接，
       那么对于在等待接入层的连接释放指示以及连接释放指示之后上报的系统消息
       过程中收到的上层请求需要缓存*/
    else if ((GMM_TRUE == g_GmmGlobalCtrl.ucRaiChgRelFlg)
          || (RR_REL_CAUSE_DIRECTED_SINGNALING_CONNECTION_RE_ESTABLISHMENT ==
                                                    g_GmmGlobalCtrl.ucRelCause))
    {
        if (GMM_FALSE == g_GmmGlobalCtrl.ucFollowOnFlg)
        {
            g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

            g_GmmGlobalCtrl.ucSpecProcHold = GMM_SERVICE_REQUEST_SIGNALLING;
        }
        Gmm_BufSmDataReqMsg(pMsg);
    }
    else if (NAS_MML_NET_RAT_TYPE_GSM == enCurRat)
    {
        /* RESUME 需要做RAU时，先缓存SM的消息，RAU后再进行处理*/
        if (GMM_TRUE == g_GmmGlobalCtrl.ucGprsResumeFlg)
        {
            Gmm_BufSmDataReqMsg(pMsg);
        }
        else
        {
            Gmm_SndRrmmDataReqForCm(RRC_NAS_MSG_PRIORTY_HIGH,
                                    &((GMMSM_DATA_REQ_STRU *)pMsg)->SmMsg);     /* 发送 RRMM_DATA_REQ                       */

            g_GmmGlobalCtrl.ucSigConFlg = GMM_TRUE;
        }
    }
    else
    {                                                                           /* 当前没有信令连接                         */
        if (GMM_TIMER_T3302_FLG
            == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3302_FLG))
        {                                                                       /* Timer3302在运行中                        */
            Gmm_TimerPause(GMM_TIMER_T3302);                                    /* 挂起Timer3302                            */
        }
        else if (GMM_TIMER_T3311_FLG
            == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3311_FLG))
        {                                                                       /* Timer3311在运行中                        */
            Gmm_TimerPause(GMM_TIMER_T3311);                                    /* 挂起Timer3311                            */
        }
        else
        {
        }
        g_GmmGlobalCtrl.ucServPreSta = g_GmmGlobalCtrl.ucState;

        GMM_CasFsmStateChangeTo(GMM_SERVICE_REQUEST_INITIATED);

        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvSmDataReq_RegNmlServ:NORMAL: STATUS IS GMM_SERVICE_REQUEST_INITIATED");

        g_GmmServiceCtrl.ucSmFlg        = GMM_TRUE;
        g_MmSubLyrShare.GmmShare.ucDeatchEnableFlg = GMM_DETACH_ABLE;
        g_GmmGlobalCtrl.ucSpecProc   = GMM_SERVICE_REQUEST_SIGNALLING;          /* 存储当前的流程                           */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvSmDataReq_RegNmlServ:INFO: SR(signaling) procedure started");

        /*缓存SM消息*/
        Gmm_BufSmDataReqMsg(pMsg);

        pNasMsg = Gmm_ServiceRequestMsgMake();                                  /* 调用service request制作函数              */

        switch (((GMMSM_DATA_REQ_STRU *)pMsg)->ulEstCause)
        {                                                                       /* 转换原因值                               */
        case GMM_SM_RRC_EST_CAUSE_ORG_CONV_CALL:
            ulEstCause = RRC_EST_CAUSE_ORIGIN_CONVERSAT_CALL;
            break;
        case GMM_SM_RRC_EST_CAUSE_ORG_STM_CALL:
            ulEstCause = RRC_EST_CAUSE_ORIGIN_STREAM_CALL;
            break;
        case GMM_SM_RRC_EST_CAUSE_ORG_INTER_CALL:
            ulEstCause = RRC_EST_CAUSE_ORIGIN_INTERACT_CALL;
            break;
        case GMM_SM_RRC_EST_CAUSE_ORG_BG_CALL:
            ulEstCause = RRC_EST_CAUSE_ORIGIN_BACKGROUND_CALL;
            break;
        case GMM_SM_RRC_EST_CAUSE_ORG_ST_CALL:
            ulEstCause = RRC_EST_CAUSE_ORIGIN_SUBSCRIB_TRAFFIC_CALL;
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvSmDataReq_RegNmlServ():INFO: The RRC Connection Setup Cause is GMM_SM_RRC_EST_CAUSE_ORG_HP_SIGNAL");
            ulEstCause = RRC_EST_CAUSE_ORIGIN_HIGH_PRIORITY_SIGNAL;
            break;
        }

        g_GmmGlobalCtrl.ulEstCause = ulEstCause;
        Gmm_SndRrmmEstReq(ulEstCause, GMM_RRC_IDNNS_UNKNOWN, pNasMsg);          /* 进行service request(signalling)          */
        Gmm_TimerStart(GMM_TIMER_PROTECT_FOR_SIGNALING);
        NAS_EventReport(WUEPS_PID_GMM,
                        NAS_OM_EVENT_DATA_SERVICE_REQ,
                        VOS_NULL_PTR,
                        NAS_OM_EVENT_NO_PARA);
    }

    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvMmcSysInfoInd_RegInit
  Function : 在GMM_REGISTERED_INITIATED下MMCGMM_SYS_INFO_IND的处理
  Input    : VOS_VOID   *pMsg                     消息指针
             VOS_UINT8   ucRaiChgFlg              RAI变化标志
             VOS_UINT8   ucDrxLengthChgFlg        DRX length变化标志
             VOS_UINT8   ucLaiChgFlg              LAI变化标志
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
  1.张志勇  2003.12.11  新规作成
  2.日    期   : 2006年2月17日
    作    者   : l65478
    修改内容   : 问题单号：A32D01287
  3.日    期   : 2008年7月2日
    作    者   : l00107747
    修改内容   : 根据问题单号：AT2D03900,FOLLOW ON标志清除排查
  4.日    期   : 2011年7月14日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  5.日    期  : 2012年08月24日
    作    者  : m00217266
    修改内容  : 修改Gmm_SndSmEstablishCnf接口，添加原因值
  6.日    期   : 2013年2月4日
    作    者   : w00176964
    修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
*******************************************************************************/
VOS_VOID Gmm_RcvMmcSysInfoInd_RegInit(
                                  VOS_VOID    *pMsg,                                /* 消息指针                                 */
                                  VOS_UINT8   ucRaiChgFlg,                          /* RAI变化标志                              */
                                  VOS_UINT8   ucDrxLengthChgFlg,                    /* DRX length变化标志                       */
                                  VOS_UINT8   ucLaiChgFlg                           /* LAI变化标志                              */
                                  )
{
    MMCGMM_SYS_INFO_IND_STRU    *pSysInfo;                                      /* 定义指针                                 */
    pSysInfo = (MMCGMM_SYS_INFO_IND_STRU *)pMsg;                                /* 初始化指针                               */

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* 不支持GPRS                               */
        g_GmmReqCnfMng.ucCnfMask = 0;                                           /* 清除原语等待标志                         */
        Gmm_TimerStop(GMM_TIMER_ALL);                                           /* 停所有Timer                              */
        Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                        /* 调用状态的公共处理                       */
        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;                              /* 清除followon标志                         */
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

        if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
        {                                                                       /* ATTACH过程是由SM触发的                   */
            Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_GPRS_NOT_SUPPORT);       /* 通知SM GMM注册失败                       */
            g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;                             /* 清ucSmCnfFlg标志                         */
        }
        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* 清当前流程                               */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd_RegInit:INFO: specific procedure ended");

        if (((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
          && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
          && (GMM_FALSE == ucLaiChgFlg))
        {                                                                       /* LA没变,并且是A+I                         */
            NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);          /* 通知MM进行LU                             */
        }


        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);


    }
    else if (MMC_GMM_NO_FORBIDDEN != pSysInfo->ulForbiddenMask)
    {                                                                           /* 在forbidden列表中                        */
        Gmm_TimerStop(GMM_TIMER_T3310);                                         /* 停T3310                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */
        Gmm_TimerStop(GMM_TIMER_T3311);
        Gmm_TimerStop(GMM_TIMER_T3302);
        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;                              /* 清除followon标志                         */
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

        if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
        {                                                                       /* ATTACH过程是由SM触发的                   */
            Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_FORBID_LA);  /* 通知SM GMM注册失败                       */
            g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;                             /* 清ucSmCnfFlg标志                         */
        }
        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask
            & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* 等待鉴权响应                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* 停保护定时器                             */
            g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG; /* 清除原语等待标志                         */
        }
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenMask);                        /* 调用对禁止列表的操作                     */


        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenMask);


    }
    else if ((GMM_TRUE == ucRaiChgFlg)
        || (VOS_TRUE == g_GmmAttachCtrl.ucRetryAttachForRelCtrlFlg))
    {                                                                           /* RA改变                                   */
        Gmm_TimerStop(GMM_TIMER_T3310);                                         /* 停T3310                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */
        Gmm_TimerStop(GMM_TIMER_T3311);
        Gmm_TimerStop(GMM_TIMER_T3302);

        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask
            & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* 等待鉴权响应                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* 停保护定时器                             */
            g_GmmReqCnfMng.ucCnfMask
                &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;                      /* 清除原语等待标志                         */
        }
        Gmm_AttachInitiate(GMM_NULL_PROCEDURE);                                                   /* 进行Attach                               */
    }
    else if (GMM_TRUE == ucDrxLengthChgFlg)
    {                                                                           /* DRX改变                                  */
        g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg = GMM_TRUE;                      /* 流程结束之后进行RAU                      */
        g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg = GMM_FALSE;                    /* 标记GMM不能进行RAU时不需要触发MM的LU过程 */
    }
    else
    {
    }
    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvMmcSysInfoInd_DeregInit
  Function : 在GMM-DEREGISTERED.NORMAL-SERVICE下MMCGMM_SYS_INFO_IND的处理
  Input    : VOS_VOID   *pMsg                     消息指针
             VOS_UINT8   ucRaiChgFlg              RAI变化标志
             VOS_UINT8   ucDrxLengthChgFlg        DRX length变化标志
             VOS_UINT8   ucLaiChgFlg              LAI变化标志
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2003.12.11  新规作成
    2. 日    期   : 2006年11月1日
       作    者   : s46746
       修改内容   : 根据问题单号：A32D06572
    3. 日    期   : 2011年07月13日
       作    者   : w00166186
       修改内容   : V7R1 PHASE II ATTACH/DETACH调整
    4.日    期   : 2013年10月05日
      作    者   : l65478
      修改内容   : DTS2013092509860:GPRS detach过程被BG搜索终止后,GMM又自动发起了注册
*******************************************************************************/
VOS_VOID Gmm_RcvMmcSysInfoInd_DeregInit(
                                    VOS_VOID    *pMsg,                              /* 消息指针                                 */
                                    VOS_UINT8   ucRaiChgFlg,                        /* RAI变化标志                              */
                                    VOS_UINT8   ucDrxLengthChgFlg,                  /* DRX length变化标志                       */
                                    VOS_UINT8   ucLaiChgFlg                         /* LAI变化标志                              */
                                    )
{
    VOS_UINT8                           ucDetachType;
    MMCGMM_SYS_INFO_IND_STRU            *pSysInfo;                                      /* 定义指针                                 */

    pSysInfo = (MMCGMM_SYS_INFO_IND_STRU *)pMsg;                                /* 初始化指针                               */

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* 不支持GPRS                               */
        Gmm_TimerStop(GMM_TIMER_T3321);                                         /* 停T3321                                  */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* 停保护定时器                             */

        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */

        g_GmmReqCnfMng.ucCnfMask = 0;                                           /* 清除原语等待标志                         */
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                          /* 调用状态的公共处理                       */
        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* 清当前流程                               */

        /* 判断等待标志是否存在，如果存在则向MMC,MM发送DETACH信息 */
        if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
        {
            NAS_GMM_SndMmcMmDetachInfo();

            if (GMM_WAIT_PS_DETACH == (g_GmmGlobalCtrl.stDetachInfo.enDetachType & GMM_WAIT_PS_DETACH) )
            {
                NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);
                Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);
            }
        }
        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);

        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd_DeregInit:INFO: specific procedure ended");
    }
    else if (MMC_GMM_NO_FORBIDDEN != pSysInfo->ulForbiddenMask)
    {                                                                           /* 在forbidden列表中                        */
        Gmm_TimerStop(GMM_TIMER_T3321);                                         /* 停T3321                                  */

        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */

        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask
            & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* 等待鉴权响应                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* 停保护定时器                             */
            g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG; /* 清除原语等待标志                         */
        }
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenMask);                        /* 调用对禁止列表的操作                     */


        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenMask);


    }
    else if (RR_REL_CAUSE_DIRECTED_SINGNALING_CONNECTION_RE_ESTABLISHMENT
        == g_GmmGlobalCtrl.ucRelCause)
    {
        Gmm_RoutingAreaUpdateInitiateWithReEstRR();
    }
    else if (((GMM_TRUE == ucRaiChgFlg) || (GMM_TRUE == ucDrxLengthChgFlg))
        && (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta))
    {                                                                           /* RA改变或者DRX改变                        */
        Gmm_TimerStop(GMM_TIMER_T3321);                                         /* 停T3321                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */

        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask
            & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* 等待鉴权响应                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* 停保护定时器                             */
            g_GmmReqCnfMng.ucCnfMask
                &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;                      /* 清除原语等待标志                         */
        }
        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        g_GmmGlobalCtrl.ucSpecProcHold = g_GmmGlobalCtrl.ucSpecProc;
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* 进行RAU                                  */
    }
    else if (VOS_TRUE == g_GmmDetachCtrl.ucRetryDetachForRelCtrlFlg)
    {
        ucDetachType = NAS_GMM_GetDetachTypeFromProcName(g_GmmDetachCtrl.ucDetachProc);
        if (GMM_INVALID_DETACH_TYPE != ucDetachType)
        {
            Gmm_MsInitNormalDetach(ucDetachType);
        }
    }
    else
    {
    }
    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvMmcSysInfoInd_RauInit
  Function : 在GMM-ROUTING_AREA_UPDATING_INITIATED下MMCGMM_SYS_INFO_IND的处理
  Input    : VOS_VOID   *pMsg                     消息指针
             VOS_UINT8   ucRaiChgFlg              RAI变化标志
             VOS_UINT8   ucDrxLengthChgFlg        DRX length变化标志
             VOS_UINT8   ucLaiChgFlg              LAI变化标志
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2003.12.11  新规作成
    2. 日    期   : 2008年7月2日
       作    者   : l00107747
       修改内容   : 根据问题单号：AT2D03900,FOLLOW ON标志清除排查
    3. 日    期   : 2011年4月6日
       作    者   : c00173809
       修改内容   : 根据问题单号：DTS2011032900575,NMO1周期性RAU丢网到NMO1不支持
                    GPRS的小区中，T3312超时没有发起周期性LAU
*******************************************************************************/
VOS_VOID Gmm_RcvMmcSysInfoInd_RauInit(
                                  VOS_VOID    *pMsg,                                /* 消息指针                                 */
                                  VOS_UINT8   ucRaiChgFlg,                          /* RAI变化标志                              */
                                  VOS_UINT8   ucDrxLengthChgFlg,                    /* DRX length变化标志                       */
                                  VOS_UINT8   ucLaiChgFlg                           /* LAI变化标志                              */
                                  )
{
    MMCGMM_SYS_INFO_IND_STRU    *pSysInfo;                                      /* 定义指针                                 */

    pSysInfo = (MMCGMM_SYS_INFO_IND_STRU *)pMsg;                                /* 强制类型转换                             */

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* 不支持GPRS                               */
        /* 当前驻留的位置区与之前驻留的位置区LAI没改变,并且在网络模式I,并且T3312超时 */
        if ((GMM_FALSE == ucLaiChgFlg)
         && (VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg))
        {
            if (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
            {
                NAS_GMM_SndMmLuInitiation(GMMMM_T3312_EXPIRED);                        /* 通知MM进行LU                             */
            }
            else
            {
                NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);
            }
        }
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                          /* 调用状态的公共处理                       */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* 停保护定时器                             */
        g_GmmReqCnfMng.ucCnfMask = 0;                                           /* 清除原语等待标志                         */
        Gmm_TimerStop(GMM_TIMER_T3330);                                         /* 停T3330                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */
        Gmm_ComCnfHandle();

        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);

        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* 清当前流程                               */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd_RauInit:INFO: specific procedure ended");
    }
    else if (MMC_GMM_NO_FORBIDDEN != pSysInfo->ulForbiddenMask)
    {                                                                           /* 在forbidden列表中                        */
        Gmm_TimerStop(GMM_TIMER_T3330);                                         /* 停T3330                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */
        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask
            & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* 等待鉴权响应                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* 停保护定时器                             */
            g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG; /* 清除原语等待标志                         */
        }
        NAS_NORMAL_LOG(WUEPS_PID_GMM, "Gmm_RcvMmcSysInfoInd_RauInit(): call Gmm_ComCnfHandle to clear msg buffer");

        Gmm_ComCnfHandle();
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenMask);                        /* 调用对禁止列表的操作                     */

        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenMask);


    }
    else if (RR_REL_CAUSE_DIRECTED_SINGNALING_CONNECTION_RE_ESTABLISHMENT
             == g_GmmGlobalCtrl.ucRelCause)
    {
        Gmm_RoutingAreaUpdateInitiateWithReEstRR();
    }
    else if ((GMM_TRUE == ucRaiChgFlg)
        ||(VOS_TRUE == g_GmmRauCtrl.ucRetryRauForRelCtrlFlg))
    {                                                                           /* RA改变                                   */
        Gmm_TimerStop(GMM_TIMER_T3330);                                         /* 停T3330                                  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */

        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask
            & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* 等待鉴权响应                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* 停保护定时器                             */
            g_GmmReqCnfMng.ucCnfMask
                &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;                      /* 清除原语等待标志                         */
        }
        NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED);                                    /* 更新状态设为GU2                          */
        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* 更新SIM卡信息                            */
        }
        else
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
        }
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* 进行RAU                                  */
    }
    else if (GMM_TRUE == ucDrxLengthChgFlg)
    {                                                                           /* DRX改变                                  */
        g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg = GMM_TRUE;                      /* 流程结束之后进行RAU                      */
        g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg = GMM_TRUE;                     /* 标记GMM不能进行RAU时要触发MM的LU过程     */
    }
    else
    {
    }

    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvMmcSysInfoInd_ServReqInit
  Function : 在GMM-ROUTING_AREA_UPDATING_INITIATED下MMCGMM_SYS_INFO_IND的处理
  Input    : VOS_VOID   *pMsg                     消息指针
             VOS_UINT8   ucRaiChgFlg              RAI变化标志
             VOS_UINT8   ucDrxLengthChgFlg        DRX length变化标志
             VOS_UINT8   ucLaiChgFlg              LAI变化标志
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2003.12.11  新规作成
    2.日    期   : 2011年11月8日
      作    者   : s46746
      修改内容   : V7R1 PhaseII阶段解决关机慢问题
    3.日    期   : 2012年1月18日
      作    者   : s46746
      修改内容   : 问题单号：DTS2012011601544,网络模式I 联合注册仅PS成功,紧急呼叫后CS指示正常服务
*******************************************************************************/
VOS_VOID Gmm_RcvMmcSysInfoInd_ServReqInit(
                                      VOS_VOID    *pMsg,                            /* 消息指针                                 */
                                      VOS_UINT8   ucRaiChgFlg,                      /* RAI变化标志                              */
                                      VOS_UINT8   ucDrxLengthChgFlg,                /* DRX length变化标志                       */
                                      VOS_UINT8   ucLaiChgFlg                       /* LAI变化标志                              */
                                      )
{
    MMCGMM_SYS_INFO_IND_STRU    *pSysInfo;                                      /* 定义指针                                 */

    pSysInfo = (MMCGMM_SYS_INFO_IND_STRU *)pMsg;                                /* 强制类型转换                             */

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* 不支持GPRS                               */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */
        Gmm_TimerStop(GMM_TIMER_T3317);                                         /* 停T3317                                  */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* 停保护定时器                             */

        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */

        g_GmmReqCnfMng.ucCnfMask = 0;                                           /* 清除原语等待标志                         */
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                          /* 调用状态的公共处理                       */
        Gmm_ComCnfHandle();
        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* 清当前流程                               */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd_ServReqInit:INFO: specific procedure ended");
        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);

    }
    else if (MMC_GMM_NO_FORBIDDEN != pSysInfo->ulForbiddenMask)
    {                                                                           /* 在forbidden列表中                        */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */
        Gmm_TimerStop(GMM_TIMER_T3317);                                         /* 停T3317                                  */

        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */

        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask
            & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* 等待鉴权响应                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* 停保护定时器                             */
            g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG; /* 清除原语等待标志                         */
        }
        Gmm_ComCnfHandle();
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenMask);                        /* 调用对禁止列表的操作                     */
    }
    else if ((GMM_TRUE == ucRaiChgFlg) || (GMM_TRUE == ucDrxLengthChgFlg))
    {                                                                           /* RA改变或者DRX改变                        */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */
        Gmm_TimerStop(GMM_TIMER_T3317);                                         /* 停T3317                                  */

        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */

        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask
            & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* 等待鉴权响应                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* 停保护定时器                             */
            g_GmmReqCnfMng.ucCnfMask
                &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;                      /* 清除原语等待标志                         */
        }

        if (GMM_TRUE == ucRaiChgFlg)
        {
            g_GmmGlobalCtrl.ucFollowOnFlg  = GMM_TRUE;
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

            g_GmmGlobalCtrl.ucSpecProcHold = g_GmmGlobalCtrl.ucSpecProc;        /* 保留被中断的SR流程                       */
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        }
    }
    else
    {
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                     GMM_MMC_ACTION_RESULT_SUCCESS,
                                     NAS_MML_REG_FAIL_CAUSE_NULL);

        if ( (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
          && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
        {
            NAS_GMM_NotifyMmUnrealCombinedRauResult();
        }

    }

    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvMmcSysInfoInd_DeregNmlServ
  Function : 在GMM_DEREGISTERED_NORMAL_SERVICE下MMCGMM_SYS_INFO_IND的处理
  Input    : VOS_VOID   *pMsg                     消息指针
             VOS_UINT8   ucLaiChgFlg              LAI变化标志
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
  1.张志勇  2003.12.11  新规作成
  2.日    期   : 2010年9月9日
    作    者   : s46746
    修改内容   : 根据问题单号：DTS2010082301847，高优先级列表搜索时，CS ONLY下仍然需要能触发PS Attach
  3.日    期   : 2010年12月24日
    作    者   : s46746
    修改内容   : 根据问题单号：DTS2010121400435，五次联合注册失败后，只进行了一次CS注册
  4.日    期   : 2011年7月14日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  5.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  6.日    期   : 2011年07月29日
    作    者   : L65478
    修改内容   : 根据问题单号：DTS2011072503161,CS ONLY在重选过程中,发起PDP激活
  7.日    期   : 2011年04月02日
    作    者   : x00180552
    修改内容   : 根据问题单号：DTS2011040600327,CS ONLY紧急驻留下,发起PDP激活
  8.日    期  : 2012年08月24日
    作    者  : m00217266
    修改内容  : 修改NAS_GMM_CnfSmNotAttach接口，添加原因值
  9.日    期   : 2013年2月4日
    作    者   : w00176964
    修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
 10.日    期   : 2016年1月27日
    作    者   : z00359541
    修改内容   : DTS2016012302336:周期RAU被用户指定搜打断，后续搜到同一网络要能发起注册
*******************************************************************************/
VOS_VOID Gmm_RcvMmcSysInfoInd_DeregNmlServ(
                                       VOS_VOID    *pMsg,                           /* 消息指针                                 */
                                       VOS_UINT8   ucLaiChgFlg                      /* LAI变化标志                              */
                                       )
{
    MMCGMM_SYS_INFO_IND_STRU    *pSysInfo;                                      /* 定义指针                                 */

    pSysInfo = (MMCGMM_SYS_INFO_IND_STRU *)pMsg;                                /* 强制类型转换                             */

    if (VOS_TRUE != NAS_MML_GetSimPsRegStatus())
    {                                                                           /* 原来SIM无效                              */
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* 清除出覆盖区标志                         */

        GMM_CasFsmStateChangeTo(GMM_DEREGISTERED_NO_IMSI);

        g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

        /* 向MMC发送PS注册结果 */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                     GMM_MMC_ACTION_RESULT_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_SIM_INVALID);

        g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;

        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvMmcSysInfoInd_DeregNmlServ:NORMAL: STATUS IS GMM_DEREGISTERED_NO_IMSI");
        return;
    }
    if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
    {
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* 清除出覆盖区标志                         */
        if(MMC_GMM_NO_FORBIDDEN != pSysInfo->ulForbiddenMask)
        {
            Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                         /* 调用状态的公共处理                       */
        }
        else
        {
            Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);                         /* 调用状态的公共处理                       */
        }


        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);


        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcSysInfoInd_DeregNmlServ:WARNING: Not allow Attach");

        /* 此时可能有缓冲的SM注册请求消息 */
        GMM_BufferMsgResume();
        return;
    }
    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* 不支持GPRS                               */
        if ((GMM_DEREGISTERED_NO_CELL_AVAILABLE == g_GmmGlobalCtrl.ucState)
            && (GMM_FALSE == g_GmmGlobalCtrl.ucCvrgAreaLostFlg))
        {                                                                       /* 前一个小区也不支持GPRS                   */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcSysInfoInd_DeregNmlServ:WARNING: Not support GPRS and No cell available");
            return;
        }
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* 清除出覆盖区标志                         */
        Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                        /* 调用状态的公共处理                       */

        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
        {                                                                       /* A+I                                      */
            if (GMM_FALSE == ucLaiChgFlg)
            {                                                                   /* LA没变                                   */
                NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);          /* 通知MM进行LU                             */
            }
        }

        NAS_GMM_CnfSmNotAttach(GMM_SM_CAUSE_GPRS_NOT_SUPPORT);

        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);

    }
    else if (MMC_GMM_NO_FORBIDDEN != pSysInfo->ulForbiddenMask)
    {                                                                           /* 在forbidden列表中                        */
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* 清除出覆盖区标志                         */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenMask);                        /* 调用对禁止列表的操作                     */

        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenMask);

        NAS_GMM_CnfSmNotAttach(GMM_SM_CAUSE_FORBID_LA);
    }
    else
    {                                                                           /* 小区改变                                 */
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* 清除出覆盖区标志                         */
        NAS_GMM_HandleModeANOIWhenDeregister();
    }

    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvMmcSysInfoInd_DeregAtmpToAtch
  Function : 在GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH下MMCGMM_SYS_INFO_IND的处理
  Input    : VOS_VOID   *pMsg                     消息指针
             VOS_UINT8   ucRaiChgFlg              RAI变化标志
             VOS_UINT8   ucDrxLengthChgFlg        DRX length变化标志
             VOS_UINT8   ucLaiChgFlg              LAI变化标志
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
  1.张志勇  2003.12.11  新规作成
  2.日    期   : 2011年7月14日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  2.日    期   : 2011年05月13日
    作    者   : h44270
    修改内容   : 根据问题单号：DTS2011051203553，在ATTACH过程中发生重选，异系统RAi相同时，GMM状态不正确，导致业务不可用
  3.日    期   : 2011年11月8日
    作    者   : s46746
    修改内容   : V7R1 PhaseII阶段解决关机慢问题
  4.日    期   : 2011年11月15日
    作    者   : w00166186
    修改内容   : DTS201111402055,网络模式I下被17号原因值拒绝5次后，MM不停的发起注册
  5.日    期   : 2012年1月30日
    作    者   : l00130025
    修改内容   : DTS2012010500368,调用同步接口VOS_GetRelTmRemainTimehTimer时没有判断hTimer是否为0，与定时器异步消息冲突导致异常打印
  6.日    期   : 2013年2月4日
    作    者   : w00176964
    修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
  7.日    期   : 2013年9月29日
    作    者   : w00242748
    修改内容   : DTS2013092302598:手动搜网，L下成功驻留，CSFB到W下，位置区变化，LAU/RAU建联失败(5次)，
                 搜网回原小区，继续进行联合RAU失败，MM单独LAU失败，死循环，MM ATTEMPT COUNTER无限增加
  8.日    期   : 2014年04月08日
    作    者   : s00217060
    修改内容   : DTS2014040901544:PS域注册被拒#111,网络带的T3302定时器时长为0，链接释放再收到系统消息时，UE一直发起ATTACH
  9.日    期   : 2016年1月27日
    作    者   : z00359541
    修改内容   : DTS2016012302336:周期RAU被用户指定搜打断，后续搜到同一网络要能发起注册
*******************************************************************************/
VOS_VOID Gmm_RcvMmcSysInfoInd_DeregAtmpToAtch(
                                          VOS_VOID    *pMsg,                        /* 消息指针                                 */
                                          VOS_UINT8   ucRaiChgFlg,                  /* RAI变化标志                              */
                                          VOS_UINT8   ucDrxLengthChgFlg,            /* DRX length变化标志                       */
                                          VOS_UINT8   ucLaiChgFlg                   /* LAI变化标志                              */
                                          )
{
    MMCGMM_SYS_INFO_IND_STRU           *pSysInfo;                                      /* 定义指针                                 */

    pSysInfo = (MMCGMM_SYS_INFO_IND_STRU *)pMsg;                                /* 强制类型转换                             */

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* 不支持GPRS                               */
        if ((GMM_TRUE == ucRaiChgFlg)
        &&  (MMC_GMM_NO_FORBIDDEN == pSysInfo->ulForbiddenMask))
        {
            g_GmmAttachCtrl.ucAttachAttmptCnt = 0;                              /* attach attempt counter清0                */
        }
        Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                        /* 调用状态的公共处理                       */
        Gmm_TimerStop(GMM_TIMER_ALL);                                           /* 停所有Timer                              */

        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
        {                                                                       /* A+I                                      */
            if (GMM_FALSE == ucLaiChgFlg)
            {                                                                   /* LA没变                                   */
                NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);          /* 通知MM进行LU                             */
            }
        }


        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);

    }
    else if (MMC_GMM_NO_FORBIDDEN != pSysInfo->ulForbiddenMask)
    {                                                                           /* 在forbidden列表中                        */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */


        Gmm_ComForbiddenList(pSysInfo->ulForbiddenMask);                        /* 调用对禁止列表的操作                     */

        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenMask);


    }
    else if (GMM_TRUE == ucRaiChgFlg)
    {                                                                           /* RA改变                                   */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */
        g_GmmAttachCtrl.ucAttachAttmptCnt = 0;                                  /* Attach attempt counter清0                */
        Gmm_AttachInitiate(GMM_NULL_PROCEDURE);                                                   /* 进行Attach                               */
    }
    else if (GMM_TRUE == ucDrxLengthChgFlg)
    {                                                                           /* DRX改变                                  */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */
        Gmm_AttachInitiate(GMM_NULL_PROCEDURE);                                                   /* 进行Attach                               */
    }
    else
    {
        if ((GMM_TRUE == g_GmmAttachCtrl.ucRetryFlg)
          &&(GMM_TRUE == g_GmmGlobalCtrl.SysInfo.ucCellChgFlg))
        {                                                                       /* 换小区需要进行attach                     */
            Gmm_TimerStop(GMM_TIMER_T3311);                                     /* 停T3311                                  */
            Gmm_TimerStop(GMM_TIMER_T3302);                                     /* 停T3302                                  */
            Gmm_AttachInitiate(GMM_NULL_PROCEDURE);                                               /* 进行Attach                               */
            g_GmmGlobalCtrl.SysInfo.ucCellChgFlg = GMM_FALSE;
        }
        else
        {
            /* 网络带下来的T3302定时器时长为0时，不启T3302定时器，如果不加最后一个判断，UE会一直发起ATTACH */
            if ((GMM_TIMER_T3302_FLG
                != (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3302_FLG))
            && ((GMM_TIMER_T3311_FLG
                != (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3311_FLG)))
            && (0 != g_GmmTimerMng.aTimerInf[GMM_TIMER_T3302].ulTimerVal))
            {
                Gmm_AttachInitiate(GMM_NULL_PROCEDURE);
            }
            else
            {


                NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);


                if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
                 && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
                {
                    g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

                    NAS_GMM_SndMmCombinedAttachInitiation();
                    NAS_GMM_SndMmCombinedAttachRejected(NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE_REG_MAX_TIMES);
                    g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;
                }
            }
        }
    }

    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvMmcSysInfoInd_RegNmlServ
  Function : 在GMM-REGISTERED.NORMAL-SERVICE下MMCGMM_SYS_INFO_IND的处理
  Input    : VOS_VOID   *pMsg                     消息指针
             VOS_UINT8   ucRaiChgFlg              RAI变化标志
             VOS_UINT8   ucDrxLengthChgFlg        DRX length变化标志
             VOS_UINT8   ucLaiChgFlg              LAI变化标志
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
  1. 张志勇  2003.12.11  新规作成
  2.日    期   : 2007年1月26日
    作    者   : liurui id:40632
    修改内容   : 根据问题单号：A32D08577
  3.日    期   : 2007年3月22日
    作    者   : liurui id:40632
    修改内容   : 根据问题单号：A32D09593
  4.日    期   : 2007年4月5日
    作    者   : luojian id:60022475
    修改内容   : 根据问题单号：A32D10023
  5.日    期   : 2007年07月10日
    作    者   : luojian id:60022475
    修改内容   : 根据问题单A32D11966
  7.日    期   : 2007年7月14日
    作    者   : luojian id:60022475
    修改内容   : 根据问题单号：A32D12438
  8.日    期   : 2008年12月31日
    作    者   : l65478
    修改内容   : 根据问题单号：AT2D07251 RAU时如果有数据需要发送，置位follow on标志
  9.日    期   : 2009年3月31日
    作    者   : l00130025
    修改内容   : 问题单号：AT2D10231/AT2D10624 当RABM不能收到Dsflowrpt流量上报，
                 在PDP激活后W下丢网，涉及 W->G->W的切换时，数传不能恢复
  10.日    期   : 2009年8月19日
     作    者   : o00132663
     修改内容   : 问题单号：AT2D13895, 【NAS R6协议升级测试】驻留后系统消息改变，指示DSAC CS域被BAR，
                  之后仍然可以拨打普通电话
  11.日    期   : 2010年8月14日
     作    者   : s46746
     修改内容   : 问题单号：DTS2010081400611，GMM限制驻留FPLMN后用户指定搜网FPLMN不进行RAU流程
  12.日    期   : 2010年10月05日
     作    者   : o00132663
     修改内容   : 问题单号：DTS2010093000943，GCF12.4.1.5，GMM 5次RAU失败发起搜网，重回原小区后，
                  不应该发起RAU.
  13.日    期   : 2010年11月16日
     作    者   : z00161729
     修改内容  : 问题单DTS2010111502913：网络模式I+A,呼叫中做周期RAU，呼叫结束后不应发起联合RAU
  15. 日    期   : 2010年12月24日
      作    者   : s46746
      修改内容   : 根据问题单号：DTS2010121400435，五次联合注册失败后，只进行了一次CS注册
  16.日    期   : 2011年7月14日
     作    者   : h44270
     修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  17. 日    期   : 2011年05月31日
      作    者   : c00173809
      修改内容   : 根据问题单号：DTS2011051902988，GMM搜网状态下,指定搜到之前相同RAI,LAI的小区时,没做RAU.
  18. 日    期   : 2011年08月12日
      作    者   : c00173809
      修改内容   : 根据问题单号：DTS2011071802663，BVT用例失败，在PDP过程中，丢网，然后紧急驻留到其他小区，再回到
                    原来小区后做RAU。
  19. 日    期   : 2011年04月20日
      作    者   : s46746
      修改内容   : 根据问题单号：DTS2011040804149，【V3R1C31B027】【RAU】PS ONLY下，PMM_IDLE态W2G重选后，发起ping未进行RAU流程，无法进行数传
  20. 日    期   : 2011年03月18日
      作    者   : c00173809
      修改内容   : 根据问题单号：DTS2011031603952，CS卡无效后，网络模式I,GMM反复进行RAU
  21. 日    期   : 2011年11月19日
      作    者   : zhoujun 40661
      修改内容   : DTS2011111700165,网络模式I下,GMM回到原小区,未能通知MM进入正常服务
  22. 日    期   : 2011年12月23日
      作    者   : w00167002
      修改内容   : DTS2011111901055:假流程上报原因值由NAS_MML_REG_FAIL_CAUSE_NULL
                    修改为NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE.
                    修改原因:在ON PLMN状态，收到此假流程消息，若原因值小于
                    NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE，则可能发起搜网。
  23. 日    期   : 2012年1月18日
      作    者   : s46746
      修改内容   : 问题单号：DTS2012011601544,网络模式I 联合注册仅PS成功,紧急呼叫后CS指示正常服务
  24. 日    期   : 2012年2月14日
      作    者   : w00176964
      修改内容   : 问题单号：DTS2012021005606:UE在U模发起RAU无响应,T3311运行期间重传RAU
  25. 日    期   : 2012年3月28日
      作    者   : l65478
      修改内容   : 问题单号：DTS2012032002585:从W->L->W时，回到W后没有发起RAU
  26. 日    期   : 2012年2月15日
      作    者   : w00166186
      修改内容   : CSFB&PPAC&ETWS&ISR 开发
  27. 日    期   : 2012年8月13日
      作    者   : z00161729
      修改内容   : DCM定制需求和遗留问题修改
  28. 日    期   : 2013年6月18日
      作    者   : l65478
      修改内容   : 问题单号：DTS2013061406222,发起RAU时应该判断 CS的业务状态
  29. 日    期   : 2013年5月22日
      作    者   : w00167002
      修改内容   : DTS2013051408623:在W下46007上PS注册失败5次，搜网到L下的46002
                    上注册成功。用户拨打电话通过搜网方式回落到W下的46002网络上，
                    GMM发起RAU失败后没有再尝试RAU.
                    原因:在46007网络上注册失败5次后回落到W下的46002上后，没有
                    重置ATTEMPT COUNTER导致.
  30.日    期   : 2013年7月19日
     作    者   : w00167002
     修改内容   : DTS2013071900239:W下网络模式I,联合注册PS only成功，CS失败原因
                    #17,网络模式由I--->II,此时不应发起联合ATTACH.
                    如果此时依然是网络模式I,但用户设置为PS ONLY,则也不用发起
                    联合ATTACH.
  31.日    期   : 2013年08月16日
     作    者   : l65478
     修改内容   : DTS2013091003969,L handover to W后收到鉴权消息没有处理
  31.日    期   : 2013年9月29日
     作    者   : w00242748
     修改内容   : DTS2013092302598:手动搜网，L下成功驻留，CSFB到W下，位置区变化，LAU/RAU建联失败(5次)，
                  搜网回原小区，继续进行联合RAU失败，MM单独LAU失败，死循环，MM ATTEMPT COUNTER无限增加
  32.日    期   : 2013年11月1日
     作    者   : z00161729
     修改内容  : DTS2013110103529:L重建到gu，ISR激活位置区未改变，gmm未发起rau
  33.日    期   : 2014年04月08日
     作    者   : s00217060
     修改内容   : DTS2014040901544:PS域注册被拒#111,网络带的T3302定时器时长为0，链接释放再收到系统消息时，UE一直发起ATTACH
  34.日    期   : 2014年06月17日
     作    者   : s00217060
     修改内容   : DTS2014061003286:GMM_REGISTERED_PLMN_SEARCH状态单独提取出一个函数处理
  35.日    期   : 2015年2月12日
     作    者   : s00217060
     修改内容   : VOLTE SWITCH修改：voice domain变化时需要做RAU
*******************************************************************************/
VOS_VOID Gmm_RcvMmcSysInfoInd_RegNmlServ(
                                     VOS_VOID    *pMsg,                             /* 消息指针                                 */
                                     VOS_UINT8   ucRaiChgFlg,                       /* RAI变化标志                              */
                                     VOS_UINT8   ucDrxLengthChgFlg,                 /* DRX length变化标志                       */
                                     VOS_UINT8   ucLaiChgFlg                        /* LAI变化标志                              */
                                     )
{
    MMCGMM_SYS_INFO_IND_STRU           *pSysInfo;                                      /* 定义指针                                 */
    VOS_UINT8                           ucOldSpecProc;
    VOS_UINT8                           ucCsAttachAllow;
    VOS_UINT8                           ucCsRestrictionFlg;

    NAS_MML_RAI_STRU                   *pstLastSuccRai;
    GMM_RAI_STRU                        stGmmRai;

    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-20, begin */
    VOS_UINT32                          ulIsAModeAndNetworkIFlg;
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-20, end */

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulT3423StatuChgNeedRegFlg;

    ulT3423StatuChgNeedRegFlg = NAS_GMM_IsT3423StatusChangeNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                                NAS_MML_GetTinType(), NAS_MML_GetT3423Status());
#endif

    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-20, begin */
    ulIsAModeAndNetworkIFlg = NAS_GMM_IsAModeAndNetworkI();
    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-20, end */

    pstLastSuccRai    = NAS_MML_GetPsLastSuccRai();
    NAS_GMM_ConvertPlmnIdToGmmFormat(&(pstLastSuccRai->stLai.stPlmnId), &stGmmRai.Lai.PlmnId);

    ucCsRestrictionFlg      = NAS_MML_GetCsRestrictRegisterFlg();

    ucCsAttachAllow         = NAS_MML_GetCsAttachAllowFlg();
    stGmmRai.ucRac          = pstLastSuccRai->ucRac;
    stGmmRai.Lai.aucLac[0]  = pstLastSuccRai->stLai.aucLac[0];
    stGmmRai.Lai.aucLac[1]  = pstLastSuccRai->stLai.aucLac[1];

    pSysInfo = (MMCGMM_SYS_INFO_IND_STRU *)pMsg;                                /* 强制类型转换                             */

    /* GMM_REGISTERED_PLMN_SEARCH状态单独提取出一个函数处理 */

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* 不支持GPRS                               */
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                          /* 调用状态的公共处理                       */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */
        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_FAILURE);
        Gmm_ComCnfHandle();


        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);


    }
    else if (MMC_GMM_NO_FORBIDDEN != pSysInfo->ulForbiddenMask)
    {                                                                           /* 在forbidden列表中                        */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenMask);                        /* 调用对禁止列表的操作                     */
        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_FAILURE);
        Gmm_ComCnfHandle();

        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenMask);


    }
    else if (GMM_TRUE == ucDrxLengthChgFlg)
    {                                                                           /* DRX改变                                  */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* 进行RAU                                  */
    }
    else if (RR_REL_CAUSE_DIRECTED_SINGNALING_CONNECTION_RE_ESTABLISHMENT == g_GmmGlobalCtrl.ucRelCause)
    {
        if( VOS_TRUE == RABM_IsExistBufferUplinkData() )
        {
            g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

            g_GmmGlobalCtrl.ucSpecProcHold = GMM_SERVICE_REQUEST_DATA_IDLE;
        }
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_RoutingAreaUpdateInitiateWithReEstRR();
        g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_NORMAL_EVENT;
    }
#if (FEATURE_ON == FEATURE_LTE)
    /* 网络带下来的T3302定时器时长为0时，不启T3302定时器，如果不加最后时长是否为0的判断，UE会一直发起ATTACH */
    else if (((NAS_MML_TIN_TYPE_GUTI == NAS_MML_GetTinType())
            && (GMM_TIMER_T3311_FLG != (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3311_FLG))
            && (GMM_TIMER_T3302_FLG != (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3302_FLG))
            && (0 != g_GmmTimerMng.aTimerInf[GMM_TIMER_T3302].ulTimerVal))
          || (GMM_TRUE == ucRaiChgFlg))
#else
    else if (GMM_TRUE == ucRaiChgFlg)
#endif
    {                                                                           /* RA改变                                   */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);

        if (GMM_SERVICE_REQ_PDPACT == g_GmmGlobalCtrl.enServReq)
        {
            g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

            g_GmmGlobalCtrl.ucSpecProcHold = GMM_SERVICE_REQUEST_SIGNALLING;
        }

        /*4.2.5.1.7 Substate, ATTEMPTING-TO-UPDATE-MM
        - perform routing area update indicating "combined RA/LA updating with
        IMSI attach" when the routing area of the serving cell has changed and
        the location area this cell is belonging to is not in the list of forbidden LAs.*/

        if ( (VOS_TRUE == NAS_GMM_IsAllowedCombinedAttach_GmmRegisteredAttemptingToUpdateMm())
          && (GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM == g_GmmGlobalCtrl.ucState) )

        {
            Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
        }
        /* GMM_REGISTERED_PLMN_SEARCH状态单独提取出一个函数处理 */
        else
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        }
        g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
    }
#if (FEATURE_ON == FEATURE_LTE)
    else if (VOS_TRUE == ulT3423StatuChgNeedRegFlg)
    {
        NAS_GMM_RcvLmmTimerInfoNotify_RegNmlServ();
    }

    /* GMM_REGISTERED_PLMN_SEARCH状态单独提取出一个函数处理 */

    else if (VOS_TRUE == NAS_GMM_IsUeInfoChangeTriggerRau())
    {
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
    }

#endif
    else if (VOS_TRUE == g_GmmServiceCtrl.ucRetrySrForRelCtrlFlg)
    {
        /* 链路释放后，需要重新发起Service Request流程 */
        ucOldSpecProc = g_GmmGlobalCtrl.ucSpecProc;
        g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;
        g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

        /* 向MMC发送PS注册结果 */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                     GMM_MMC_ACTION_RESULT_SUCCESS,
                                     NAS_MML_REG_FAIL_CAUSE_NULL);


        if ( (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
          && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
        {
            NAS_GMM_NotifyMmUnrealCombinedRauResult();
        }

        g_GmmGlobalCtrl.ucSpecProc = ucOldSpecProc;
        g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;
        Gmm_DealWithBuffAfterProc();
    }

    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-20, begin */

    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-20, end */
    else if ((VOS_TRUE == NAS_MML_GetSimCsRegStatus())
          && (VOS_TRUE == ulIsAModeAndNetworkIFlg)
          && (VOS_TRUE == ucCsAttachAllow)
          && (VOS_FALSE == ucCsRestrictionFlg))
    {

        /* cs exist service, GMM should not originate RAU when RAI no change  */
        if (GMM_RAU_NORMAL == g_GmmGlobalCtrl.ucSpecProcInCsTrans)
        {                                                                   /* CS通信中的normal RAU(A+I)                */
            if (GMM_FALSE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg)
            {
                if (VOS_FALSE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
                {
                    Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALA_UPDATING);      /* 进行RAU过程                              */
                }
                g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
            }
        }
        else if (GMM_ATTACH_NORMAL == g_GmmGlobalCtrl.ucSpecProcInCsTrans)
        {                                                                   /* CS通信中的normal attach(A+I)             */
            if (GMM_FALSE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg)
            {
                Gmm_RoutingAreaUpdateInitiate(
                                            GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);   /* 进行RAU过程                              */
                g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
            }
        }
        else
        {
            NAS_GMM_HandleModeANOIWhenRAInotChange();

            if (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
            {
                g_GmmRauCtrl.ucT3312ExpiredFlg = GMM_FALSE;
            }
            else if (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
            {
                /* T3311不在运行时才发起RAU */
                if (VOS_FALSE == NAS_GMM_QryTimerStatus(GMM_TIMER_T3311))
                {
                    Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
                    g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
                }
            }
            /* <==A32D12438 */
            /*
            当Rau、Sr、Detach过程建立信令连接的时候发生RAI改变，此时状态迁移到
            GMM_REGISTERED_NORMAL_SERVICE，等待底层释放连接，并上报系统信息，
            如果上报的系统信息显示又回到最初的小区，那么此时不会发起Rau，但是
            需要将前面被中断的流程进行完
            */
            else if ((GMM_TRUE == g_GmmGlobalCtrl.ucFollowOnFlg)
                && (GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState))
            {
                g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;
                NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

                Gmm_RoutingAreaUpdateHandleFollowOn();
            }
            else if (GMM_SERVICE_REQ_NONE != g_GmmGlobalCtrl.enServReq)
            {
                if (GMM_SERVICE_REQ_PAGING == g_GmmGlobalCtrl.enServReq)
                {
                    /*W接入层暂不支持搜网下接收到寻呼*/
                }
                else
                {
                    Gmm_DealWithBuffAfterProc();
                }
            }
            else
            {
            }

            if (GMM_ROUTING_AREA_UPDATING_INITIATED != g_GmmGlobalCtrl.ucState)
            {
                GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_SUCCESS);
            }
        }
    }

    /* GMM_REGISTERED_PLMN_SEARCH状态单独提取出一个函数处理 */

    else
    {
        /*
        当Rau、Sr、Detach过程建立信令连接的时候发生RAI改变，此时状态迁移到
        GMM_REGISTERED_NORMAL_SERVICE，等待底层释放连接，并上报系统信息，
        如果上报的系统信息显示又回到最初的小区，那么此时不会发起Rau，但是
        需要将前面被中断的流程进行完
        */

        ucOldSpecProc = g_GmmGlobalCtrl.ucSpecProc;
        g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;
        g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

        /* 向MMC发送PS注册结果 */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                     GMM_MMC_ACTION_RESULT_SUCCESS,
                                     NAS_MML_REG_FAIL_CAUSE_NULL);

        if ( (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
          && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
        {
            if (VOS_FALSE == ucCsRestrictionFlg)
            {
                NAS_GMM_NotifyMmUnrealCombinedRauResult();
            }
            else
            {
                NAS_GMM_SndMmGmmActionResultInd(GMMMM_ACTION_SUCCESS,
                                                NAS_MML_REG_FAIL_CAUSE_NULL);                   /* 发送MMCGMM_GMM_ACTION_RESULT_IND给MMC    */

            }
        }


        g_GmmGlobalCtrl.ucSpecProc = ucOldSpecProc;
        g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;

        if ((GMM_TRUE == g_GmmGlobalCtrl.ucFollowOnFlg)
            && (GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState))
        {
            g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

            Gmm_RoutingAreaUpdateHandleFollowOn();
        }

        /* 原来T3312超时是在suspend wait for sysinfo状态处理的,因为L handover to W,
           状态迁到了register normal service状态,所以需要在此状态下处理T3312超时 */
        if ((VOS_FALSE == NAS_GMM_QryTimerStatus(GMM_TIMER_T3311))
         && (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
         && (GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState))
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
        }

    }

    if (GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
    {
        if (gstGmmCasGlobalCtrl.ucLastDataSender !=
                        NAS_MML_GetCurrNetRatType())
        {
            gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_WAITSERVICE;
        }
    }
    g_GmmGlobalCtrl.enServReq = GMM_SERVICE_REQ_NONE;

    NAS_GMM_ProcSavedMmT3211ExpiredNotify();

    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  函 数 名  : NAS_GMM_RcvMmcSysInfoInd_RegPlmnSrch
  功能描述  : GMM_REGISTERED_PLMN_SEARCH收到系统消息的处理
  输入参数  : VOS_VOID   *pMsg                     消息指针
              VOS_UINT8   ucRaiChgFlg              RAI变化标志
              VOS_UINT8   ucDrxLengthChgFlg        DRX length变化标志
              VOS_UINT8   ucLaiChgFlg              LAI变化标志
  输出参数  : 无
  返 回 值  : 无
  调用函数  :
  被调函数  :

  修改历史      :
   1.日    期   : 2014年06月12日
     作    者   : s00217060
     修改内容   : 新生成函数
   2.日    期   : 2014年08月02日
     作    者   : s00217060
     修改内容   : DTS2014073105516:REGISTERED_PLMN_SRCH状态T3311超时，之后收到系统消息，如果是网络模式I,需要做联合注册
   3.日    期   : 2015年2月12日
     作    者   : s00217060
     修改内容   : VOLTE SWITCH修改：voice domain变化时需要做RAU
   4.日    期   : 2016年1月27日
     作    者   : z00359541
     修改内容   : DTS2016012302336:周期RAU被用户指定搜打断，后续搜到同一网络要能发起注册
*******************************************************************************/
VOS_VOID NAS_GMM_RcvMmcSysInfoInd_RegPlmnSrch(
                                     VOS_VOID    *pMsg,                             /* 消息指针                                 */
                                     VOS_UINT8   ucRaiChgFlg,                       /* RAI变化标志                              */
                                     VOS_UINT8   ucDrxLengthChgFlg,                 /* DRX length变化标志                       */
                                     VOS_UINT8   ucLaiChgFlg                        /* LAI变化标志                              */
                                     )
{
    MMCGMM_SYS_INFO_IND_STRU           *pSysInfo;                                      /* 定义指针                                 */
    VOS_UINT8                           ucOldSpecProc;
    VOS_UINT8                           ucCsAttachAllow;
    VOS_UINT8                           ucCsRestrictionFlg;

    NAS_MML_RAI_STRU                   *pstLastSuccRai;
    GMM_RAI_STRU                        stGmmRai;

    VOS_UINT32                          ulIsAModeAndNetworkIFlg;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulT3423StatuChgNeedRegFlg;

    ulT3423StatuChgNeedRegFlg = NAS_GMM_IsT3423StatusChangeNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                                NAS_MML_GetTinType(), NAS_MML_GetT3423Status());
#endif

    ulIsAModeAndNetworkIFlg = NAS_GMM_IsAModeAndNetworkI();

    pstLastSuccRai    = NAS_MML_GetPsLastSuccRai();
    NAS_GMM_ConvertPlmnIdToGmmFormat(&(pstLastSuccRai->stLai.stPlmnId), &stGmmRai.Lai.PlmnId);

    ucCsRestrictionFlg      = NAS_MML_GetCsRestrictRegisterFlg();

    ucCsAttachAllow         = NAS_MML_GetCsAttachAllowFlg();
    stGmmRai.ucRac          = pstLastSuccRai->ucRac;
    stGmmRai.Lai.aucLac[0]  = pstLastSuccRai->stLai.aucLac[0];
    stGmmRai.Lai.aucLac[1]  = pstLastSuccRai->stLai.aucLac[1];

    pSysInfo = (MMCGMM_SYS_INFO_IND_STRU *)pMsg;                                /* 强制类型转换                             */

    if (GMM_TRUE == ucRaiChgFlg)
    {
        if ( (GMM_REGISTERED_NO_CELL_AVAILABLE    == g_GmmGlobalCtrl.ucPlmnSrchPreSta)
          || (GMM_REGISTERED_ATTEMPTING_TO_UPDATE == g_GmmGlobalCtrl.ucPlmnSrchPreSta))
        {
            /* 在由ATTEMPT TO UPDATE或者REGISTERED_NO_CELL_AVAILABLE状态经过
               搜网后收到系统消息，需要清除ATTEMPT COUNTER */
            if (MMC_GMM_NO_FORBIDDEN == pSysInfo->ulForbiddenMask)
            {
                g_GmmRauCtrl.ucRauAttmptCnt = 0;
            }
        }
    }

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* 不支持GPRS                               */
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                          /* 调用状态的公共处理                       */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */
        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_FAILURE);
        Gmm_ComCnfHandle();
        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);
    }
    /* RAU被用户指定搜打断，后续搜到同一个RAI网络需要停T3311定时器并发起注册 */
    else if ((VOS_TRUE == NAS_GMM_QryTimerStatus(GMM_TIMER_T3311))
          && (GMM_FALSE == ucRaiChgFlg)
          && (VOS_TRUE == pSysInfo->ulUserSrchFlg))
    {
        NAS_NORMAL_LOG(WUEPS_PID_GMM, "NAS_GMM_RcvMmcSysInfoInd_RegPlmnSrch: User NW Srch, need to stop T3311 and send RAU Req");
        /* 用户发起的指定搜网，强制发起注册 */
        Gmm_TimerStop(GMM_TIMER_T3311);
        Gmm_TimerStop(GMM_TIMER_T3302);

        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
    }
    else if (MMC_GMM_NO_FORBIDDEN != pSysInfo->ulForbiddenMask)
    {                                                                           /* 在forbidden列表中                        */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenMask);                        /* 调用对禁止列表的操作                     */
        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_FAILURE);
        Gmm_ComCnfHandle();
        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenMask);

    }
    else if (GMM_TRUE == ucDrxLengthChgFlg)
    {                                                                           /* DRX改变                                  */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* 进行RAU                                  */
    }
    else if (RR_REL_CAUSE_DIRECTED_SINGNALING_CONNECTION_RE_ESTABLISHMENT == g_GmmGlobalCtrl.ucRelCause)
    {
        if( VOS_TRUE == RABM_IsExistBufferUplinkData() )
        {
            g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

            g_GmmGlobalCtrl.ucSpecProcHold = GMM_SERVICE_REQUEST_DATA_IDLE;
        }
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_RoutingAreaUpdateInitiateWithReEstRR();
        g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_NORMAL_EVENT;
    }
#if (FEATURE_ON == FEATURE_LTE)
    /* 网络带下来的T3302定时器时长为0时，不启T3302定时器，如果不加最后时长是否为0的判断，UE会一直发起ATTACH */
    else if (((NAS_MML_TIN_TYPE_GUTI == NAS_MML_GetTinType())
            && (GMM_TIMER_T3311_FLG != (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3311_FLG))
            && (GMM_TIMER_T3302_FLG != (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3302_FLG))
            && (0 != g_GmmTimerMng.aTimerInf[GMM_TIMER_T3302].ulTimerVal))
          || (GMM_TRUE == ucRaiChgFlg))
#else
    else if (GMM_TRUE == ucRaiChgFlg)
#endif
    {                                                                           /* RA改变                                   */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);

        if (GMM_SERVICE_REQ_PDPACT == g_GmmGlobalCtrl.enServReq)
        {
            g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

            g_GmmGlobalCtrl.ucSpecProcHold = GMM_SERVICE_REQUEST_SIGNALLING;
        }

        if (VOS_TRUE == NAS_GMM_BackToOrgPlmnAfterCoverageLost(pMsg))
        {
            return;
        }

        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);

        g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
    }
#if (FEATURE_ON == FEATURE_LTE)
    else if (VOS_TRUE == ulT3423StatuChgNeedRegFlg)
    {
        NAS_GMM_RcvLmmTimerInfoNotify_RegNmlServ();
    }

    else if (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == NAS_MML_GetTinType())
    {
        NAS_GMM_IsrActiveRaiNoChg_InterSys();
    }

    else if (VOS_TRUE == NAS_GMM_IsUeInfoChangeTriggerRau())
    {
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
    }

#endif
    else if (VOS_TRUE == g_GmmServiceCtrl.ucRetrySrForRelCtrlFlg)
    {
        /* 链路释放后，需要重新发起Service Request流程 */
        ucOldSpecProc = g_GmmGlobalCtrl.ucSpecProc;
        g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;
        g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

        /* 向MMC发送PS注册结果 */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                     GMM_MMC_ACTION_RESULT_SUCCESS,
                                     NAS_MML_REG_FAIL_CAUSE_NULL);


        if ( (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
          && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
        {
            NAS_GMM_NotifyMmUnrealCombinedRauResult();
        }

        g_GmmGlobalCtrl.ucSpecProc = ucOldSpecProc;
        g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;
        Gmm_DealWithBuffAfterProc();
    }

    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-20, begin */

    /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-20, end */
    else if ((VOS_TRUE == NAS_MML_GetSimCsRegStatus())
          && (VOS_TRUE == ulIsAModeAndNetworkIFlg)
          && (VOS_TRUE == ucCsAttachAllow)
          && (VOS_FALSE == ucCsRestrictionFlg))
    {

        /* cs exist service, GMM should not originate RAU when RAI no change  */
        if (GMM_RAU_NORMAL == g_GmmGlobalCtrl.ucSpecProcInCsTrans)
        {                                                                   /* CS通信中的normal RAU(A+I)                */
            if (GMM_FALSE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg)
            {
                if (VOS_FALSE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
                {
                    Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALA_UPDATING);      /* 进行RAU过程                              */
                }
                g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
            }
        }
        else if (GMM_ATTACH_NORMAL == g_GmmGlobalCtrl.ucSpecProcInCsTrans)
        {                                                                   /* CS通信中的normal attach(A+I)             */
            if (GMM_FALSE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg)
            {
                Gmm_RoutingAreaUpdateInitiate(
                                            GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);   /* 进行RAU过程                              */
                g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
            }
        }
        else
        {
            NAS_GMM_HandleModeANOIWhenRAInotChange();

            if (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
            {
                /* T3311不在运行时才发起RAU */
                if (VOS_FALSE == NAS_GMM_QryTimerStatus(GMM_TIMER_T3311))
                {
                    Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
                    g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
                }
            }
            else if (GMM_TRUE == g_GmmRauCtrl.ucT3311ExpiredFlg)
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
                g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
            }
            /* <==A32D12438 */
            /*
            当Rau、Sr、Detach过程建立信令连接的时候发生RAI改变，此时状态迁移到
            GMM_REGISTERED_NORMAL_SERVICE，等待底层释放连接，并上报系统信息，
            如果上报的系统信息显示又回到最初的小区，那么此时不会发起Rau，但是
            需要将前面被中断的流程进行完
            */
            else if (GMM_SERVICE_REQ_NONE != g_GmmGlobalCtrl.enServReq)
            {
                if (GMM_SERVICE_REQ_PAGING == g_GmmGlobalCtrl.enServReq)
                {
                    /*W接入层暂不支持搜网下接收到寻呼*/
                }
                else
                {
                    Gmm_DealWithBuffAfterProc();
                }
            }
            else
            {
            }

            GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_SUCCESS);
        }
    }
    else
    {
        if (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
        }

        /* T3311未超时按如下流程处理 */
        else if (GMM_FALSE == g_GmmRauCtrl.ucT3311ExpiredFlg)
        {
            if (NAS_MML_ROUTING_UPDATE_STATUS_UPDATED == NAS_MML_GetPsUpdateStatus())
            {
                if (GMM_FALSE == Gmm_Compare_Rai(&g_GmmGlobalCtrl.SysInfo.Rai, &stGmmRai))
                {
                    Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
                    g_GmmRauCtrl.ucT3312ExpiredFlg = GMM_FALSE;
                }
                else
                {
                    Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);

                    ucOldSpecProc = g_GmmGlobalCtrl.ucSpecProc;
                    g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;
                    g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;


                    /* 向MMC发送PS注册结果 */
                    NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                                 GMM_MMC_ACTION_RESULT_SUCCESS,
                                                 NAS_MML_REG_FAIL_CAUSE_NULL);

                    if ( (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
                      && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
                    {
                        NAS_GMM_NotifyMmUnrealCombinedRauResult();
                    }



                    g_GmmGlobalCtrl.ucSpecProc = ucOldSpecProc;
                    g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;

                    if (GMM_TRUE == g_GmmGlobalCtrl.ucFollowOnFlg)
                    {
                        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;
                        NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

                        Gmm_RoutingAreaUpdateHandleFollowOn();
                    }
                }
            }
            else if (GMM_TRUE == g_GmmGlobalCtrl.ucFollowOnFlg)
            {
                /*
                3gpp 24.008 4.7.5 : The routing area updating attempt counter shall be
                reset when the MS is in substate ATTEMPTING-TO-UPDATE and
                    - a new routing area is entered;
                    - expiry of timer T3302; or
                    - at request from registration function.
                */
                g_GmmRauCtrl.ucRauAttmptCnt = 0;

                /* 停止Timer3302 */
                Gmm_TimerStop(GMM_TIMER_T3302);

                /* 停止Timer3311*/
                Gmm_TimerStop(GMM_TIMER_T3311);

                /* 发起RAU过程 */
                Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
            }
            else
            {
                if ((GMM_TIMER_T3311_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3311_FLG))
                 || (GMM_TIMER_T3302_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3302_FLG)))
                {
                    Gmm_ComStaChg(GMM_REGISTERED_ATTEMPTING_TO_UPDATE);

                    ucOldSpecProc = g_GmmGlobalCtrl.ucSpecProc;
                    g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;
                    g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

                    /* 向MMC发送PS注册结果 */
                    NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                             GMM_MMC_ACTION_RESULT_FAILURE,
                                             NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);

                    if ( (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
                      && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
                    {
                        NAS_GMM_NotifyMmUnrealCombinedRauResult();
                    }

                    g_GmmGlobalCtrl.ucSpecProc = ucOldSpecProc;
                    g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;
                }
                else
                {
                    Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
                }

            }

            if (GMM_SERVICE_REQ_PAGING == g_GmmGlobalCtrl.enServReq)
            {
                /*W接入层暂不支持搜网下接收到寻呼*/
            }
            else if (GMM_SERVICE_REQ_PDPACT == g_GmmGlobalCtrl.enServReq)
            {
                Gmm_DealWithBuffAfterProc();
            }
            else
            {
                GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_SUCCESS);
            }
        }
        /* T3311超时在REGISTERED_PLMN_SRCH状态需要发起RAU */
        else if (GMM_TRUE == g_GmmRauCtrl.ucT3311ExpiredFlg)
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        }
        else
        {
        }
    }

    g_GmmGlobalCtrl.enServReq = GMM_SERVICE_REQ_NONE;

    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvMmcSysInfoInd_RegUpdtNeed
  Function : 在GMM-REGISTERED.UPDATE-NEEDED下MMCGMM_SYS_INFO_IND的处理
  Input    : VOS_VOID   *pMsg                     消息指针
             VOS_UINT8   ucLaiChgFlg              LAI变化标志
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
  1.张志勇  2003.12.11  新规作成
 2.日    期   : 2011年7月14日
   作    者   : h44270
   修改内容   : V7R1 PhaseII阶段调整，注册结果简化
 3.日    期   : 2011年06月09日
   作    者   : c00173809
   修改内容   : 根据问题单号：DTS2011060705224，GMM在LIMITED SERVICE状态下，I+A模式收到不支持
                    GPRS相同LAI的小区时，不断做LAU。
 4.日    期   : 2011年08月12日
   作    者   : c00173809
   修改内容   : 根据问题单号：DTS2011071802663，BVT用例失败，在PDP过程中，丢网，然后紧急驻留到其他小区，再回到
                   原来小区后做RAU。
 5.日    期   : 2011年05月10日
   作    者   : c00173809
   修改内容   : 根据问题单号：DTS2011050402447，相同ra/la从支持GPRS重选到不支持GPRS的小区,再重选到原来小区要做联合RAU
 6.日    期   : 2012年2月15日
   作    者   : w00166186
   修改内容   : CSFB&PPAC&ETWS&ISR 开发
 7.日    期   : 2012年8月15日
   作    者   : z00161729
   修改内容   : DCM定制需求和遗留问题修改
 8.日    期   : 2015年2月12日
   作    者   : s00217060
   修改内容   : VOLTE SWITCH修改：voice domain变化时需要做RAU
 9.日    期   : 2016年1月27日
   作    者   : z00359541
   修改内容   : DTS2016012302336:周期RAU被用户指定搜打断，后续搜到同一网络要能发起注册
*******************************************************************************/
VOS_VOID Gmm_RcvMmcSysInfoInd_RegUpdtNeed(
                                        VOS_VOID    *pMsg,                          /* 消息指针                                 */
                                        VOS_UINT8   ucLaiChgFlg                     /* LAI变化标志                              */
                                        )
{
    MMCGMM_SYS_INFO_IND_STRU    *pSysInfo;                                      /* 定义指针                                 */
    VOS_UINT8                    ucCsRestrictionFlg;
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulT3423StatusChgNeedRegFlg;

    ulT3423StatusChgNeedRegFlg = NAS_GMM_IsT3423StatusChangeNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                                                 NAS_MML_GetTinType(), NAS_MML_GetT3423Status());
#endif

    pSysInfo = (MMCGMM_SYS_INFO_IND_STRU *)pMsg;                                /* 强制类型转换                             */

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* 不支持GPRS                               */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                          /* 调用状态的公共处理                       */

        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-20, begin */
        if (VOS_TRUE == NAS_GMM_IsAModeAndNetworkI())
        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-20, end */
        {                                                                       /* A+I                                      */
            if ((GMM_FALSE == ucLaiChgFlg)
             && (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
             && (VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg))
            {                                                                   /* LA没变                                   */
                NAS_GMM_SndMmLuInitiation(GMMMM_T3312_EXPIRED);          /* 通知MM进行LU                             */
            }
        }


        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);

    }
    else if (MMC_GMM_NO_FORBIDDEN != pSysInfo->ulForbiddenMask)
    {                                                                           /* 在forbidden列表中                        */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenMask);                        /* 调用对禁止列表的操作                     */

        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenMask);


    }
#if (FEATURE_ON == FEATURE_LTE)
    else if ((VOS_TRUE == ulT3423StatusChgNeedRegFlg)
          && (GMM_REGISTERED_LIMITED_SERVICE == g_GmmGlobalCtrl.ucState))
    {
        NAS_GMM_RcvLmmTimerInfoNotify_RegLimitServ();
    }
    else if (VOS_TRUE == NAS_GMM_IsUeInfoChangeTriggerRau())
    {
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
    }

#endif
    else
    {                                                                           /* 小区改变                                 */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */

        if (VOS_TRUE == NAS_GMM_BackToOrgPlmnAfterCoverageLost(pMsg))
        {
            return;
        }

        if ((GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
            &&(GMM_FALSE == gstGmmCasGlobalCtrl.ucSysRauFlg))
        {
            ucCsRestrictionFlg = NAS_MML_GetCsRestrictRegisterFlg();

            if (!((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
                && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)))
            {                                                                   /* 非A+I                                    */
                Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
            }
            else if ((VOS_FALSE == NAS_MML_GetSimCsRegStatus())
                  || (GMM_TRUE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg)
                  || (VOS_TRUE == ucCsRestrictionFlg))
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
            }
            else
            {                                                                   /* A+I                                      */
                Gmm_RoutingAreaUpdateInitiate(
                                    GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);       /* 调用RAU过程combined RAU with IMSI attach */
            }
            g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
        }
        else
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* 进行RAU                                  */
        }

    }

    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvMmcSysInfoInd_RegAtmpToUpdt
  Function : 在GMM-REGISTERED.ATTEMPTING-TO-UPDATE下MMCGMM_SYS_INFO_IND的处理
  Input    : VOS_VOID   *pMsg                     消息指针
             VOS_UINT8   ucRaiChgFlg              RAI变化标志
             VOS_UINT8   ucDrxLengthChgFlg        DRX length变化标志
             VOS_UINT8   ucLaiChgFlg              LAI变化标志
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
  1.张志勇  2003.12.10  新规作成
  2.日    期   : 2011年7月14日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  3.日    期   : 2011年11月8日
    作    者   : s46746
    修改内容   : V7R1 PhaseII阶段解决关机慢问题
  4.日    期   : 2011年11月15日
    作    者   : w00166186
    修改内容   : DTS201111402055,网络模式I下被17号原因值拒绝5次后，MM不停的发起注册
  5.日    期   : 2012年1月30日
    作    者   : l00130025
    修改内容   : DTS2012010500368,调用同步接口VOS_GetRelTmRemainTimehTimer时没有判断hTimer是否为0，与定时器异步消息冲突导致异常打印

  6.日    期   : 2013年2月4日
    作    者   : w00176964
    修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
  7.日    期   : 2013年9月29日
    作    者   : w00242748
    修改内容   : DTS2013092302598:手动搜网，L下成功驻留，CSFB到W下，位置区变化，LAU/RAU建联失败(5次)，
                 搜网回原小区，继续进行联合RAU失败，MM单独LAU失败，死循环，MM ATTEMPT COUNTER无限增加
  8.日    期   : 2016年1月27日
    作    者   : z00359541
    修改内容   : DTS2016012302336:周期RAU被用户指定搜打断，后续搜到同一网络要能发起注册
*******************************************************************************/
VOS_VOID Gmm_RcvMmcSysInfoInd_RegAtmpToUpdt(
                                        VOS_VOID    *pMsg,                          /* 消息指针                                 */
                                        VOS_UINT8   ucRaiChgFlg,                    /* RAI变化标志                              */
                                        VOS_UINT8   ucDrxLengthChgFlg,              /* DRX length变化标志                       */
                                        VOS_UINT8   ucLaiChgFlg                     /* LAI变化标志                              */
                                        )
{
    MMCGMM_SYS_INFO_IND_STRU           *pSysInfo;                                      /* 定义指针                                 */

    pSysInfo = (MMCGMM_SYS_INFO_IND_STRU *)pMsg;                                /* 强制类型转换                             */
    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* 不支持GPRS                               */
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                          /* 调用状态的公共处理                       */
        Gmm_TimerStop(GMM_TIMER_ALL);                                           /* 停所有Timer                              */
        if (GMM_TRUE == ucRaiChgFlg)
        {
            if (MMC_GMM_NO_FORBIDDEN == pSysInfo->ulForbiddenMask)
            {
                g_GmmRauCtrl.ucRauAttmptCnt = 0;                                    /* RAU attempt counter清0                   */
            }
        }
        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
        {                                                                       /* A+I                                      */
            if (GMM_FALSE == ucLaiChgFlg)
            {                                                                   /* LA没变                                   */
                NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);          /* 通知MM进行LU                             */
            }
        }


        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);

    }
    else if (MMC_GMM_NO_FORBIDDEN != pSysInfo->ulForbiddenMask)
    {                                                                           /* 在forbidden列表中                        */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */

        Gmm_ComForbiddenList(pSysInfo->ulForbiddenMask);                        /* 调用对禁止列表的操作                     */

        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenMask);


    }
    else if (GMM_TRUE == ucRaiChgFlg)
    {                                                                           /* RA改变                                   */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */
        g_GmmRauCtrl.ucRauAttmptCnt = 0;                                        /* RAU attempt counter清0                   */
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* 进行RAU                                  */
    }
    else if (GMM_TRUE == ucDrxLengthChgFlg)
    {                                                                           /* DRX改变                                  */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* 进行RAU                                  */
    }
    else
    {
        if ((GMM_TRUE == g_GmmRauCtrl.ucRetryFlg)
          &&(GMM_TRUE == g_GmmGlobalCtrl.SysInfo.ucCellChgFlg))
        {                                                                       /* 换小区需要进行RAU                        */
            Gmm_TimerStop(GMM_TIMER_T3311);                                     /* 停T3311                                  */
            Gmm_TimerStop(GMM_TIMER_T3302);                                     /* 停T3302                                  */
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);           /* 进行RAU                                  */
            g_GmmGlobalCtrl.SysInfo.ucCellChgFlg = GMM_FALSE;
        }

        else
        {
            NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE);

            if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
             && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
            {
                g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

                NAS_GMM_SndMmCombinedRauInitiation();
                NAS_GMM_SndMmCombinedRauRejected(NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE_REG_MAX_TIMES);
                g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;
            }

        }
    }

    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module   : Gmm_RcvMmcSysInfoInd_RegNoCell
  Function : 在GMM-REGISTERED.NO-CELL-AVAILABLE状态下MMCGMM_SYS_INFO_IND的处理
  Input    : VOS_VOID   *pMsg                     消息指针
             VOS_UINT8   ucRaiChgFlg              RAI变化标志
             VOS_UINT8   ucDrxLengthChgFlg        DRX length变化标志
             VOS_UINT8   ucLaiChgFlg              LAI变化标志
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
  1. 张志勇  2003.12.10  新规作成
  2.日    期   : 2007年05月11日
    作    者   : luojian id:60022475
    修改内容   : 问题单号:A32D10713
  3.日    期   : 2009年3月31日
    作    者   : l00130025
    修改内容   : 问题单号：AT2D10231/AT2D10624 当RABM不能收到Dsflowrpt流量上报，
                 在PDP激活后W下丢网，涉及 W->G->W的切换时，数传不能恢复
  4.日    期   : 2009年7月23日
    作    者   : l65478
    修改内容   : 问题单号: AT2D13173，在搜网结束后，立刻进行缓存的SM消息的处理
  5.日    期   : 2009年8月19日
    作    者   : o00132663
    修改内容   : 问题单号：AT2D13895, 【NAS R6协议升级测试】驻留后系统消息改变，指示DSAC CS域被BAR，
                 之后仍然可以拨打普通电话
  6.日    期   : 2009年8月25日
    作    者   : o00132663
    修改内容   : 问题单号：AT2D14050, CS有通话时T3312超时应发起周期性RAU
  7.日    期   : 2010年8月14日
    作    者   : s46746
    修改内容   : 问题单号：DTS2010081400611，GMM限制驻留FPLMN后用户指定搜网FPLMN不进行RAU流程
  8.日    期   : 2011年7月14日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  9.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
 10.日    期   : 2011年05月12日
    作    者   : h44270
    修改内容   : 根据问题单号：DTS2011051104889，出服务区后，进入到不支持GPRS小区，再重选回原来注册的小区，服务不可用
 11.日    期   : 2011年04月20日
    作    者   : s46746
    修改内容   : 根据问题单号：DTS2011040804149，【V3R1C31B027】【RAU】PS ONLY下，PMM_IDLE态W2G重选后，发起ping未进行RAU流程，无法进行数传
 12.日    期   : 2012年3月28日
    作    者   : l65478
    修改内容   : 问题单号：DTS2012032002585:从W->L->W时，回到W后没有发起RAU
 13.日    期   : 2012年2月15日
    作    者   : w00166186
    修改内容   : CSFB&PPAC&ETWS&ISR 开发
 14.日    期   : 2012年08月24日
    作    者   : m00217266
    修改内容   : 修改Gmm_SndSmEstablishCnf接口，添加原因值
 15.日    期   : 2013年2月4日
    作    者   : w00176964
    修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
 16.日    期   : 2013年11月1日
    作    者   : z00161729
    修改内容   : DTS2013110103529:L重建到gu，ISR激活位置区未改变，gmm未发起rau
 17.日    期   : 2014年06月17日
    作    者   : s00217060
    修改内容   : DTS2014061003286:收到系统消息时如果T3311超时发起RAU
*******************************************************************************/
VOS_VOID Gmm_RcvMmcSysInfoInd_RegNoCell(
                                    VOS_VOID    *pMsg,                              /* 消息指针                                 */
                                    VOS_UINT8   ucRaiChgFlg,                        /* RAI变化标志                              */
                                    VOS_UINT8   ucDrxLengthChgFlg,                  /* DRX length变化标志                       */
                                    VOS_UINT8   ucLaiChgFlg                         /* LAI变化标志                              */
                                    )
{
    MMCGMM_SYS_INFO_IND_STRU           *pSysInfo;                                      /* 定义指针                                 */
    VOS_UINT8                           ucCsAttachAllow;
    VOS_UINT8                           ucSimCsRegStatus;
    VOS_UINT8                           ucCsRestrictionFlg;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulT3423StatusChgNeedRegFlg;
#endif

    NAS_MML_RAI_STRU                       *pstLastSuccRai;
    GMM_RAI_STRU                            stGmmRai;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType;

    enTinType         = NAS_MML_GetTinType();
#endif

    pstLastSuccRai    = NAS_MML_GetPsLastSuccRai();
    NAS_GMM_ConvertPlmnIdToGmmFormat(&(pstLastSuccRai->stLai.stPlmnId), &stGmmRai.Lai.PlmnId);

    ucSimCsRegStatus        = NAS_MML_GetSimCsRegStatus();

    ucCsRestrictionFlg      = NAS_MML_GetCsRestrictRegisterFlg();

    ucCsAttachAllow         = NAS_MML_GetCsAttachAllowFlg();

    stGmmRai.ucRac          = pstLastSuccRai->ucRac;
    stGmmRai.Lai.aucLac[0]  = pstLastSuccRai->stLai.aucLac[0];
    stGmmRai.Lai.aucLac[1]  = pstLastSuccRai->stLai.aucLac[1];

#if (FEATURE_ON == FEATURE_LTE)
    ulT3423StatusChgNeedRegFlg = NAS_GMM_IsT3423StatusChangeNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                                 NAS_MML_GetTinType(), NAS_MML_GetT3423Status());
#endif

    pSysInfo = (MMCGMM_SYS_INFO_IND_STRU *)pMsg;                                /* 强制类型转换                             */

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* 不支持GPRS                               */
        if (GMM_TRUE == g_GmmGlobalCtrl.ucCvrgAreaLostFlg)
        {
            g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;

            if (GMM_FALSE == ucLaiChgFlg)
            {
                if (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
                {
                    NAS_GMM_SndMmLuInitiation(GMMMM_T3312_EXPIRED);             /* 通知MM进行LU                             */
                }
            }
        }

        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);


        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);
    }
    else if (MMC_GMM_NO_FORBIDDEN != pSysInfo->ulForbiddenMask)
    {                                                                           /* 在forbidden列表中                        */
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* 清除出覆盖区标志                         */
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenMask);                        /* 调用对禁止列表的操作                     */

        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenMask);


    }
#if (FEATURE_ON == FEATURE_LTE)
    else if ((VOS_TRUE == ulT3423StatusChgNeedRegFlg)
          && ((GMM_REGISTERED_NO_CELL_AVAILABLE == g_GmmGlobalCtrl.ucState)
           || (GMM_REGISTERED_UPDATE_NEEDED == g_GmmGlobalCtrl.ucState)))
    {
        NAS_GMM_RcvLmmTimerInfoNotify_RegNmlServ();
    }
#endif
#if (FEATURE_ON == FEATURE_LTE)
    else if ((GMM_TRUE == Gmm_Compare_Rai(&g_GmmGlobalCtrl.SysInfo.Rai, &stGmmRai))
           && (GMM_FALSE == ucRaiChgFlg) && (GMM_FALSE == ucDrxLengthChgFlg)
           && (NAS_MML_TIN_TYPE_GUTI != enTinType))
#else
    else if ((GMM_TRUE == Gmm_Compare_Rai(&g_GmmGlobalCtrl.SysInfo.Rai, &stGmmRai))
           && (GMM_FALSE == ucRaiChgFlg) && (GMM_FALSE == ucDrxLengthChgFlg))
#endif
    {                                                                           /* 回到原来的RA并且DRX参数没有改变          */
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* 清除出覆盖区标志                         */

#if (FEATURE_ON == FEATURE_LTE)
        if (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == NAS_MML_GetTinType())
        {
            NAS_GMM_IsrActiveRaiNoChg_InterSys();
            return;
        }
#endif

        if (GMM_FALSE == g_GmmRauCtrl.ucT3312ExpiredFlg)
        {                                                                       /* 出覆盖区时T3312未溢出                    */
            if (NAS_MML_ROUTING_UPDATE_STATUS_UPDATED
                == NAS_MML_GetPsUpdateStatus())
            {                                                                   /* 更新状态是GU1                            */

                /* T3311超时在REGISTERED_PLMN_SRCH状态需要发起RAU */
                if (GMM_TRUE == g_GmmRauCtrl.ucT3311ExpiredFlg)
                {
                    Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
                }
                else
                {
                    g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;            /* 设置假流程标志                           */

                    if ((VOS_TRUE != NAS_MML_GetCsAttachAllowFlg())
                     || (GMM_NET_MODE_I != g_GmmGlobalCtrl.ucNetMod)
                     || (VOS_TRUE == ucCsRestrictionFlg))
                    {                                                               /* 非A+I                                    */
                        Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);               /* 调用状态的公共处理                       */
#if (FEATURE_LTE == FEATURE_ON)
                        if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
                        {
                            NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
                        }

                        /* 如果之前出服务区，T3312超时，启动了T3323,后重进服务区，需要停止T3323*/
                        Gmm_TimerStop(GMM_TIMER_T3323);
#endif
                        Gmm_TimerStart(GMM_TIMER_T3312);                            /* 启动T3312                                */
                        g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;
                        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd_RegNoCell:INFO: normal RAU procedure started");


                        /* 向MMC发送PS注册结果 */
                        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                                     GMM_MMC_ACTION_RESULT_SUCCESS,
                                                     NAS_MML_REG_FAIL_CAUSE_NULL);

                        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_SUCCESS);
                        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;
                        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd_RegNoCell:INFO: specific procedure ended");
                        g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;              /* 设置真流程标志                           */
                    }
                    else
                    {                                                               /* A+I                                      */
                        if (  (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == NAS_MML_GetCsUpdateStatus())
                            &&(VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg))
                        {                                                           /* 更新状态是U1,并且Gs关联已存在            */
                            Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);           /* 调用状态的公共处理                       */
#if (FEATURE_LTE == FEATURE_ON)
                            if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
                            {
                                NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
                            }
#endif
                            Gmm_TimerStart(GMM_TIMER_T3312);                        /* 启动T3312                                */
                            if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
                            {                                                       /* 需要给SM回EST_CNF                        */
                                g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;
                                Gmm_SndSmEstablishCnf(GMM_SM_EST_SUCCESS, GMM_SM_CAUSE_SUCCESS);        /* 向SM回建立成功的响应                     */
                            }


                            /* 向MMC发送PS注册结果 */
                            NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                                         GMM_MMC_ACTION_RESULT_SUCCESS,
                                                         NAS_MML_REG_FAIL_CAUSE_NULL);

                            if (VOS_TRUE == ucCsAttachAllow)
                            {                                                       /* CS域允许注册                             */
                                NAS_GMM_SndMmCombinedRauInitiation();
                                NAS_GMM_SndMmCombinedRauAccept(GMMMM_RAU_RESULT_COMBINED,
                                                               NAS_MML_REG_FAIL_CAUSE_NULL,
                                                               VOS_NULL_PTR,
                                                               VOS_NULL_PTR);                                      /* 发送 MMCGMM_COMBINED_RAU_ACCEPTED        */

                                /*更新RAU记数器 */
                                if(5<=g_GmmRauCtrl.ucRauAttmptCnt)
                                {
                                    g_GmmRauCtrl.ucRauAttmptCnt = 0;
                                }
                            }
                            GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_SUCCESS);
                            g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;
                            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd_RegNoCell:INFO: specific procedure ended");
                            g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;              /* 设置真流程标志                           */
                        }
                        else
                        {                                                           /* 更新状态不是U1,或者Gs关联已经移除                           */
                            if ((VOS_TRUE != ucSimCsRegStatus)
                             || (VOS_FALSE == ucCsAttachAllow))
                            {                                                       /* sim无效或者CS域不允许注册                */
                                Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);       /* 调用状态的公共处理                       */
#if (FEATURE_LTE == FEATURE_ON)
                                if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
                                {
                                    NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
                                }
#endif
                                Gmm_TimerStart(GMM_TIMER_T3312);                    /* 启动T3312                                */
                                if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
                                {                                                   /* 需要给SM回EST_CNF                        */
                                    g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;
                                    Gmm_SndSmEstablishCnf(GMM_SM_EST_SUCCESS, GMM_SM_CAUSE_SUCCESS);        /* 向SM回建立成功的响应                     */
                                }
                                g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;
                                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd_RegNoCell:INFO: normal RAU procedure started");


                                /* 向MMC发送PS注册结果 */
                                NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                                             GMM_MMC_ACTION_RESULT_SUCCESS,
                                                             NAS_MML_REG_FAIL_CAUSE_NULL);

                                GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_SUCCESS);
                                g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;
                                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd_RegNoCell:INFO: specific procedure ended");
                                g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;              /* 设置真流程标志                           */
                            }
                            else
                            {
                                Gmm_RoutingAreaUpdateInitiate(
                                    GMM_UPDATING_TYPE_INVALID);                     /* 调用RAU                                  */
                            }
                        }
                    }
                }
            }
            else
            {                                                                   /* 更新状态不是GU1                          */
                Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);       /* 调用RAU                                  */
            }

            if(GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
            {
                if (gstGmmCasGlobalCtrl.ucLastDataSender !=
                        NAS_MML_GetCurrNetRatType())
                {
                    gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_WAITSERVICE;
                }
                if (GMM_SERVICE_REQ_PDPACT == g_GmmGlobalCtrl.enServReq)
                {
                    Gmm_DealWithBuffAfterProc();
                    g_GmmGlobalCtrl.enServReq = GMM_SERVICE_REQ_NONE;
                }
            }
        }
        else
        {                                                                       /* 出覆盖区时T3312溢出                      */
            g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                      /* 清除出覆盖区标志                         */
            if ((VOS_TRUE != NAS_MML_GetCsAttachAllowFlg())
             || (GMM_NET_MODE_I != g_GmmGlobalCtrl.ucNetMod))
            {                                                                   /* 非A+I                                    */
                Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
            }
            else if ((VOS_FALSE == NAS_MML_GetSimCsRegStatus())
                  || (VOS_TRUE == ucCsRestrictionFlg)
                  || (GMM_TRUE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg))
            {/* A+I 模式，但CS域被 BAR, 或者 当前 CS 通话中 */
                Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
            }
            else
            {                                                                   /* A+I                                      */
                Gmm_RoutingAreaUpdateInitiate(
                                    GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);       /* 调用RAU过程combined RAU with IMSI attach */
            }
        }
    }
    else
    {                                                                           /* RA改变或者DRX参数变化                    */
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* 清除出覆盖区标志                         */
        g_GmmRauCtrl.ucT3312ExpiredFlg    = GMM_FALSE;                          /* 清除T3312溢出标记                        */

        if ((VOS_TRUE != NAS_MML_GetCsAttachAllowFlg())
         || (GMM_NET_MODE_I != g_GmmGlobalCtrl.ucNetMod))
        {                                                                       /* 非A+I                                    */
            Gmm_RoutingAreaUpdateInitiate(GMM_RA_UPDATING);
        }
        else
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);           /* 调用RAU过程                              */
        }
    }

    return;                                                                     /* 返回                                     */
}


/*******************************************************************************
  Module   : Gmm_RcvMmcSysInfoInd_SuspWaitSys
  Function : 在GMM-SUSPENDED-WAIT-FOR-SYSINFO下MMCGMM_SYS_INFO_IND的处理
  Input    : VOS_VOID   *pMsg                     消息指针
             VOS_UINT8   ucRaiChgFlg              RAI变化标志
             VOS_UINT8   ucLaiChgFlg              LAI变化标志
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
  1.张志勇  2003.12.10  新规作成
  2.日    期   : 2006年10月9日
    作    者   : s46746
    修改内容   : 根据问题单号：A32D05744
  3.日    期   : 2011年2月14日
    作    者   : o00132663
    修改内容   : 问题单DTS2010122401824，G->W重选后，未发起周期性RAU.
  4.日    期   : 2011年7月14日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  5.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
 6. 日    期   : 2011年5月16日
    作    者   : c00173809
    修改内容   : 根据问题单号：问题单号:DTS2011050905176,从支持GPRS的小区异系统重选到不支持GPRS的
                    小区,异常停止了T3312定时器.
 7. 日    期   : 2011年05月16日
    作    者   : c00173809
    修改内容   : 根据问题单号：DTS2011051005812，网络模式I,相同RAI,T3312超时时,从支持GPRS的3G小区重选到不支持GPRS的2G小区再重选回原来的3G小区,做联合RAU.
 8. 日    期   : 2011年07月30日
    作    者   : f00179208
    修改内容   : 根据问题单号：DTS2011072901080，【V3R1C31B112W单模 GCF/PTCRB认证 协议测试】双模用例6.2.2.3失败
 9. 日    期   : 2011年04月25日
    作    者   : c00173809
    修改内容   : 根据问题单号：DTS2011042205602，相同RAI的,从不支持GPRS的2G小区重选到支持GPRS的3G小区,不做RAU.
10. 日    期   : 2011年04月26日
    作    者   : c00173809
    修改内容   : 根据问题单号：DTS2011042502289，在RAU过程中异系统重选到相同RAI的小区导致PS无法提供服务.
11. 日    期   : 2011年12月2日
    作    者   : s46746
    修改内容   : 从L异系统改变到GU后，没有指派加密密钥到GU接入层
12. 日    期   : 2012年1月18日
    作    者   : s46746
    修改内容   : 问题单号：DTS2012011601544,网络模式I 联合注册仅PS成功,紧急呼叫后CS指示正常服务
13. 日    期   : 2012年03月20日
    作    者   : l00130025
    修改内容   : DTS2012030105247,NAS只在网侧实际发起鉴权时,通知W SecurityKey，其它情况下由WAS调用对应接口获取
14. 日    期   : 2012年3月14日
    作    者   : z00161729
    修改内容   : 支持ISR修改
15. 日    期   : 2012年5月21日
    作    者   : l00171473
    修改内容   : DTS2012051501480, w->L->w的流程中, 回到w后不应将GMM状态恢复为GMM_REGISTERED_NO_CELL_AVAILABLE
16. 日    期   : 2012年8月18日
    作    者   : z00161729
    修改内容   : DCM定制需求和遗留问题修改
17. 日    期   : 2012年7月17日
    作    者   : z00161729
    修改内容   : DTS2012073106360:ISR激活CSFB重定向或CCO到GU,idle态位置区不变无需做RAU
18. 日    期   : 2012年09月08日
    作    者   : l65478
    修改内容   : DTS012090302087,L->GU时,RAI没有改变时,GMM发起了RAU
19 .日    期   : 2013年2月4日
    作    者   : w00176964
    修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
20. 日    期   : 2013年08月07日
    作    者   : l65478
    修改内容   : 修改问题单DTS2013080502397,在重选到G下进行LU后,然后GAS指示重定向到W原来的小区时，如果Gs口不存在,需要发起联合RAU
21.日    期   : 2013年9月29日
    作    者   : w00242748
    修改内容   : DTS2013092302598:手动搜网，L下成功驻留，CSFB到W下，位置区变化，LAU/RAU建联失败(5次)，
                 搜网回原小区，继续进行联合RAU失败，MM单独LAU失败，死循环，MM ATTEMPT COUNTER无限增加
22.日    期   : 2015年2月12日
   作    者   : s00217060
   修改内容   : VOLTE SWITCH修改：voice domain变化时需要做RAU
*******************************************************************************/
VOS_VOID Gmm_RcvMmcSysInfoInd_SuspWaitSys(VOS_VOID* pRcvMsg,VOS_UINT8 ucRaiChgFlg,VOS_UINT8 ucLaiChgFlg)
{
    MMCGMM_SYS_INFO_IND_STRU           *pSysInfo;                                      /* 定义指针                                 */
    VOS_VOID                           *pAddr;
    VOS_UINT8                           ucCsAttachAllow;

    VOS_UINT8                           ucSimCsRegStatus;
    NAS_MML_LAI_STRU                   *pstCsSuccLai = VOS_NULL_PTR;
    VOS_UINT8                           ucCsRestrictFlg;
    GMM_RAI_STRU                        stRai;


#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulT3423StatuChgNeedRegFlg;
    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus;

    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType;

    enTinType         = NAS_MML_GetTinType();

    pstConnStatus             = NAS_MML_GetConnStatus();
    ulT3423StatuChgNeedRegFlg = NAS_GMM_IsT3423StatusChangeNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                                    NAS_MML_GetTinType(), NAS_MML_GetT3423Status());
#endif

    ucCsAttachAllow = NAS_MML_GetCsAttachAllowFlg();
    pSysInfo = (MMCGMM_SYS_INFO_IND_STRU *)pRcvMsg;                             /* 强制类型转换                             */

    pstCsSuccLai     = NAS_MML_GetCsLastSuccLai( );
    stRai.ucRac = pstCsSuccLai->ucRac;
    /* 填写LAC */
    stRai.Lai.aucLac[0] = pstCsSuccLai->aucLac[0];
    stRai.Lai.aucLac[1] = pstCsSuccLai->aucLac[1];                       /* LAC */
    /* 填写PLMN */
    stRai.Lai.PlmnId.aucMccDigit[0] =
        (VOS_UINT8)(pstCsSuccLai->stPlmnId.ulMcc & 0x0F);                           /* MCC Digit 1                              */
    stRai.Lai.PlmnId.aucMccDigit[1] =
        (VOS_UINT8)((pstCsSuccLai->stPlmnId.ulMcc >> 8) & 0x0F);                    /* MCC Digit 2                              */
    stRai.Lai.PlmnId.aucMccDigit[2] =
        (VOS_UINT8)((pstCsSuccLai->stPlmnId.ulMcc >> 16) & 0x0F);                   /* MCC Digit 3                              */
    stRai.Lai.PlmnId.aucMncDigit[0] =
        (VOS_UINT8)(pstCsSuccLai->stPlmnId.ulMnc & 0x0F);                           /* MNC Digit 1                              */
    stRai.Lai.PlmnId.aucMncDigit[1] =
        (VOS_UINT8)((pstCsSuccLai->stPlmnId.ulMnc >> 8) & 0x0F);                    /* MNC Digit 2                              */
    stRai.Lai.PlmnId.aucMncDigit[2] =
        (VOS_UINT8)((pstCsSuccLai->stPlmnId.ulMnc >> 16) & 0x0F);                   /* MNC Digit 3                              */
    stRai.Lai.PlmnId.ucMncCnt = 3;                                          /* MNC Degit count                          */
    if (GMM_PLMNID_MNC3_INVALID == stRai.Lai.PlmnId.aucMncDigit[2])
    {
        stRai.Lai.PlmnId.ucMncCnt = 2;                                      /* MNC Degit count                          */
    }
    ucSimCsRegStatus = NAS_MML_GetSimCsRegStatus();
    ucCsRestrictFlg  = NAS_MML_GetCsRestrictRegisterFlg();

    Gmm_TimerStop(GMM_TIMER_SUSPENDED);

    if (VOS_TRUE != NAS_MML_GetSimPsRegStatus())
    {                                                                           /* 原来SIM无效                              */
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* 清除出覆盖区标志                         */

        GMM_CasFsmStateChangeTo(GMM_DEREGISTERED_NO_IMSI);

        g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

        /* 向MMC发送PS注册结果 */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                     GMM_MMC_ACTION_RESULT_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_SIM_INVALID);
        g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;

        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvMmcSysInfoInd_SuspWaitSys:NORMAL: STATUS IS GMM_DEREGISTERED_NO_IMSI");
        return;
    }
    if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
    {
        g_GmmGlobalCtrl.ucCvrgAreaLostFlg = GMM_FALSE;                          /* 清除出覆盖区标志                         */
        Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);                         /* 调用状态的公共处理                       */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcSysInfoInd_SuspWaitSys:WARNING: Not allow Attach");

        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);


        return;
    }

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {                                                                           /* 不支持GPRS                               */
        GMM_LOG_INFO("Gmm_RcvMmcSysInfoInd_SuspWaitSys:the cell not support GPRS.");
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                          /* 调用状态的公共处理                       */
        Gmm_TimerStop(GMM_REGSTER_AND_SHUTDOWN_TIMER);                                           /* 停所有Timer                              */

        /*异系统改变时通知RABM*/
        g_GmmRauCtrl.ucNpduCnt = 0x0;
        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_HANDOVER, GMM_RABM_RAU_FAILURE);

        if (GMM_TRUE == ucRaiChgFlg)
        {
            if (MMC_GMM_NO_FORBIDDEN == pSysInfo->ulForbiddenMask)
            {
                g_GmmRauCtrl.ucRauAttmptCnt = 0;                                    /* RAU attempt counter清0                   */
            }
        }

        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-20, begin */
        if (VOS_TRUE == NAS_GMM_IsAModeAndNetworkI())
        /* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-20, end */
        {                                                                       /* A+I                                      */
            if ((GMM_FALSE == ucLaiChgFlg)
             && (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
             && (VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg))
            {                                                                   /* LA没变                                   */
                NAS_GMM_SndMmLuInitiation(GMMMM_T3312_EXPIRED);                 /* 通知MM进行LU                             */
            }
        }


        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);

    }
    else if (MMC_GMM_NO_FORBIDDEN != pSysInfo->ulForbiddenMask)
    {                                                                           /* 在forbidden列表中                        */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */


        /*异系统改变时通知RABM*/
        g_GmmRauCtrl.ucNpduCnt = 0x0;
        GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_HANDOVER, GMM_RABM_RAU_FAILURE);
        Gmm_ComForbiddenList(pSysInfo->ulForbiddenMask);                        /* 调用对禁止列表的操作                     */
        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(pSysInfo->ulForbiddenMask);

    }
    else if (GMM_TRUE == ucRaiChgFlg)
    {/* 新的RA,处理网络模式变更 */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */
        Gmm_TimerStop(GMM_TIMER_T3330);
        Gmm_TimerStop(GMM_TIMER_T3318);
        Gmm_TimerStop(GMM_TIMER_T3320);
        g_GmmRauCtrl.ucRauAttmptCnt = 0;                                        /* RAU attempt counter清0                   */
        gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_INTERSYSTEM;

        if (GMM_NETMODE_CHG_NULL == gstGmmSuspendCtrl.ucNetModeChange)
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);           /* 进行RAU                                  */
        }
        else
        {
            GMM_ProcedureByNetMode(gstGmmSuspendCtrl.ucNetModeChange);
        }
    }
    else                                                                        /* RA 相同 */
    {
        /* reference to 23.401 10.5.1.3 L->GU handover时,RAI不改变不需要进行RAU; TIN指示为GUTI时需要进行RAU */






        if ((((GMM_IU_PMM_CONNECTED == gstGmmSuspendCtrl.ucPreSrvState)
           || (MMC_SUSPEND_CAUSE_HANDOVER == gstGmmSuspendCtrl.ucSuspendCause))
          && (NAS_MML_NET_RAT_TYPE_LTE != gstGmmSuspendCtrl.ucPreRat))
#if (FEATURE_ON == FEATURE_LTE)
         || (NAS_MML_TIN_TYPE_GUTI == enTinType)
#endif
         )

        {

            Gmm_TimerStop(GMM_TIMER_T3302);                                     /* 停T3302                                  */
            Gmm_TimerStop(GMM_TIMER_T3330);
            Gmm_TimerStop(GMM_TIMER_T3318);
            Gmm_TimerStop(GMM_TIMER_T3320);
            g_GmmRauCtrl.ucRauAttmptCnt = 0;                                    /* RAU attempt counter清0                   */
            gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_INTERSYSTEM;
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);           /* 进行RAU                                  */

        }
        else if (gstGmmCasGlobalCtrl.ucLastDataSender != NAS_MML_GetCurrNetRatType())
        {
            /*异系统改变时通知RABM*/
            g_GmmRauCtrl.ucNpduCnt = 0x0;
            GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_HANDOVER, GMM_RABM_RAU_SUCCESS);

            /* G->W,G下不支持GPRS,到W下后,如果RAI不改变,重新调用下GMM_REGISTERED_UPDATE_NEEDED
               状态下接收到系统消息的处理函数. */
            if ((GMM_REGISTERED_UPDATE_NEEDED == gstGmmSuspendCtrl.ucPreState)
             || (GMM_REGISTERED_LIMITED_SERVICE== gstGmmSuspendCtrl.ucPreState)
             || (GMM_ROUTING_AREA_UPDATING_INITIATED== gstGmmSuspendCtrl.ucPreState))
            {
                Gmm_RcvMmcSysInfoInd_RegNoCell(pRcvMsg,
                                               ucRaiChgFlg,
                                               GMM_FALSE,
                                               ucLaiChgFlg);
            }
#if (FEATURE_ON == FEATURE_LTE)
                /* L重选到G,路由区未改变，ISR激活，无需做RAU时需要更新状态，
                  否则为register no cell available，后续无法做业务 */
            else if ((NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == NAS_MML_GetTinType())
                 && (NAS_MML_NET_RAT_TYPE_LTE == gstGmmSuspendCtrl.ucPreRat))

            {
                NAS_GMM_IsrActiveRaiNoChg_InterSys();
            }
#endif
            else
            {
                Gmm_ComStaChg(gstGmmSuspendCtrl.ucPreState);
                gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_WAITSERVICE;
                if (GMM_T3312_TIMEOUT == gstGmmSuspendCtrl.ucT3312State)
                {
                    Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
                    gstGmmSuspendCtrl.ucT3312State = GMM_T3312_NOT_TIMEOUT;
                }
                else
                {
                    if (GMM_TRUE == g_GmmGlobalCtrl.ucFollowOnFlg)
                    {
                        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
                    }
                    GMM_BufferMsgResume();
                }
            }
        }
        /* NMO1下,不通过手机模式判断是否需要进行联合注册 */
        else if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
              && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)
              && (VOS_TRUE == ucCsAttachAllow)
              && (GMM_RAU_NORMAL_CS_UPDATED == g_GmmGlobalCtrl.ucSpecProcInCsTrans)
              && (VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg))
        {
            gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_WAITSERVICE;
            Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALA_UPDATING);
            g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
        }
        else if (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
        {
            GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_HANDOVER, GMM_RABM_RAU_SUCCESS);
            /* NMO1下,不通过手机模式判断是否需要进行联合注册 */
            if ((VOS_TRUE == NAS_MML_GetPsAttachAllowFlg())
             && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)
             && (VOS_FALSE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
             && (VOS_TRUE == ucCsAttachAllow))
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
            }
            else
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
            }
        }
#if (FEATURE_ON == FEATURE_LTE)
        else if (VOS_TRUE == ulT3423StatuChgNeedRegFlg)
        {
            NAS_GMM_RcvLmmTimerInfoNotify_RegNmlServ();
        }
        else if (VOS_TRUE == NAS_GMM_IsUeInfoChangeTriggerRau())
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        }

#endif
        else
        {
            /*异系统改变时通知RABM*/
            g_GmmRauCtrl.ucNpduCnt = 0x0;
            GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_HANDOVER, GMM_RABM_RAU_SUCCESS);

            /* G->W, G下接入禁止或者不支持GPRS，到W下后，如果RAC不改变，重新调用下GMM_REGISTERED_UPDATE_NEEDED
               状态下的系统消息处理函数 */
            if ((GMM_REGISTERED_UPDATE_NEEDED == gstGmmSuspendCtrl.ucPreState)
             || (GMM_REGISTERED_LIMITED_SERVICE == gstGmmSuspendCtrl.ucPreState))
            {

                if (MMC_SUSPEND_CAUSE_CELLRESELECT == gstGmmSuspendCtrl.ucSuspendCause)
                {
                    gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_INTERSYSTEM;
                }

                Gmm_RcvMmcSysInfoInd_RegNoCell(pRcvMsg,
                                               ucRaiChgFlg,
                                               GMM_FALSE,
                                               ucLaiChgFlg);

                gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_NORMAL;

            }
            else
            {
                /* 在网络模式I下，Gs口不存在,并且接入不受限时,需要发起联合的RAU重建Gs口 */
                /* PS access bar已经在预处理中判断,所以此处不用判断PS接入禁止 */
                if ((VOS_FALSE                            == Gmm_Compare_Rai(&stRai, &(g_GmmGlobalCtrl.SysInfo.Rai)))
                 && (VOS_TRUE                             == ucCsAttachAllow)
                 && (GMM_NET_MODE_I                       == g_GmmGlobalCtrl.ucNetMod)
                 && (VOS_TRUE                             == ucSimCsRegStatus)
                 && (VOS_FALSE                            == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
                 && (VOS_FALSE                            == ucCsRestrictFlg))
                {
                    Gmm_TimerStop(GMM_TIMER_T3311);                                             /* 停T3311                                  */
                    Gmm_TimerStop(GMM_TIMER_T3302);                                             /* 停T3302                                  */

                    Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
                    return;
                }

                Gmm_ComStaChg(gstGmmSuspendCtrl.ucPreState);
                GMM_ResumeSuccess();

#if (FEATURE_ON == FEATURE_LTE)
                /* L重选到G,路由区未改变，ISR激活，无需做RAU时需要更新状态，
                  否则为register no cell available，后续无法做业务 */
                if ((NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == NAS_MML_GetTinType())
                 && (NAS_MML_NET_RAT_TYPE_LTE == gstGmmSuspendCtrl.ucPreRat)
                 && (VOS_FALSE == pstConnStatus->ucPsSigConnStatusFlg))
                {
                    NAS_GMM_IsrActiveRaiNoChg_InterSys();
                }
                else
#endif
                {
                    g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;
                    /* 向MMC发送PS注册结果 */
                    NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                                 GMM_MMC_ACTION_RESULT_SUCCESS,
                                                 NAS_MML_REG_FAIL_CAUSE_NULL);
                    g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;

                    if ( (VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
                      && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
                    {
                        NAS_GMM_NotifyMmUnrealCombinedRauResult();
                    }

                }


                if (GMM_TRUE == g_GmmGlobalCtrl.ucFollowOnFlg)
                {
                    g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;
                    NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

                    switch (g_GmmGlobalCtrl.ucSpecProcHold)
                    {                                                               /* 保留的specific流程                       */
                    case GMM_SERVICE_REQUEST_DATA_IDLE:
                    case GMM_SERVICE_REQUEST_DATA_CONN:
                        Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);     /* 发送GMMRABM_REESTABLISH_CNF(fail)        */
                        break;
                    case GMM_SERVICE_REQUEST_SIGNALLING:
                        if (GMM_TRUE == g_GmmServiceCtrl.ucSmsFlg)
                        {
                            Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);              /* 发送PMMSMS_ERROR_IND                     */
                        }
                        if (GMM_MSG_HOLD_FOR_SM
                            ==(g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &
                                                    GMM_MSG_HOLD_FOR_SM))
                        {                                                           /* 如果有保留的SmDataReq原语                */
                            NAS_NORMAL_LOG(WUEPS_PID_GMM, "Gmm_RcvMmcSysInfoInd_SuspWaitSys(): Clear cached SM data Req");

                            g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &=
                                ~GMM_MSG_HOLD_FOR_SM;                               /* 清除保留标志                             */
                            pAddr =
                                (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSm; /* 读取SmDataReq原语地址                    */
                            Gmm_MemFree(pAddr);                                     /* 释放保存的SM消息                         */
                        }
                        break;
                    default:
                        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd_SuspWaitSys:INFO: No Hold Procedure");
                        break;
                    }
                    g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;
                }
            }
        }
    }

    return;
}


/*******************************************************************************
  Module   : Gmm_ComCmpLai
  Function : LAI的比较
  Input    : GMM_LAI_STRU   *pMsg       指向LAI的指针
  Output   : 无
  NOTE     : 无
  Return   : GMM_TRUE    相同
             GMM_FALSE   不同
  History  :
    1. 张志勇  2003.12.10  新规作成
*******************************************************************************/
VOS_UINT8 Gmm_ComCmpLai(
                    GMM_LAI_STRU *pMsg                                          /* 指向LAI的指针                            */
                    )
{
    VOS_UINT8 ucRet;                                                                /* 定义返回值                               */

    ucRet = GMM_FALSE;                                                          /* 初始化                                   */

    if (GMM_TRUE == Gmm_Com_CmpPlmnid(&pMsg->PlmnId))
    {                                                                           /* PLMN相同                                 */
        if ((pMsg->aucLac[0]
            == g_GmmGlobalCtrl.SysInfo.Rai.Lai.aucLac[0])
            &&(pMsg->aucLac[1]
            == g_GmmGlobalCtrl.SysInfo.Rai.Lai.aucLac[1]))
        {                                                                       /* LAC相同                                  */
            ucRet = GMM_TRUE;                                                   /* 赋返回值                                 */
        }
    }

    return ucRet;                                                               /* 返回                                     */
}

/***********************************************************************
  Module   : NAS_GMM_RcvMmAuthenticationFailureInd
  Function : 原语MMGMM_AUTHENTICATON_FAILURE_IND的接收处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
  1. 张志勇  2003.12.11  新版作成
  2.日    期   : 2006年9月9日
    作    者   : sunxibo id:46746
    修改内容   : 根据问题单号：A32D05604
  3.日    期   : 2008年7月2日
    作    者   : l00107747
    修改内容   : 根据问题单号：AT2D03900,FOLLOW ON标志清除排查
  4.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  5.日    期   : 2012年4月20日
    作    者   : l00130025
    修改内容   : DTS2012031502528，GMM GPRS Suspension状态没有处理LuRsltInd，
                 W->G Rej 11->W原小区时,没有做Attach，导致后续SM业务失败
  6.日    期   : 2012年8月10日
    作    者   : L00171473
    修改内容   : DTS2012082204471, TQE清理
  7.日    期   : 2012年08月24日
    作    者   : m00217266
    修改内容   : 修改Gmm_SndSmEstablishCnf接口，添加原因值
  8.日    期   : 2013年10月05日
    作    者   : l65478
    修改内容   : DTS2013092509860:GPRS detach过程被BG搜索终止后,GMM又自动发起了注册

  9.日    期   : 2013年12月09日
    作    者   : z00234330
    修改内容   : DTS2013120907910:MM鉴权被网络拒绝后,gmm状态存在问题。
************************************************************************/
VOS_VOID NAS_GMM_RcvMmAuthenticationFailureInd(VOS_VOID)
{
    VOS_UINT8                           ucGmmPreState;
    /* 判断等待标志是否存在，如果存在则向MMC,MM发送DETACH信息 */
    if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
    {
        if (GMM_WAIT_PS_DETACH == (g_GmmGlobalCtrl.stDetachInfo.enDetachType & GMM_WAIT_PS_DETACH))
        {
            NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);
        }
        NAS_GMM_SndMmcMmDetachInfo();
    }

    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* 判断当前状态                             */
        case GMM_REGISTERED_INITIATED:
        case GMM_DEREGISTERED_INITIATED:
        case GMM_ROUTING_AREA_UPDATING_INITIATED:
        case GMM_SERVICE_REQUEST_INITIATED:
        case GMM_DEREGISTERED_NORMAL_SERVICE:
        case GMM_DEREGISTERED_LIMITED_SERVICE:
        case GMM_DEREGISTERED_ATTACH_NEEDED:
        case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
        case GMM_DEREGISTERED_NO_IMSI:
        case GMM_DEREGISTERED_NO_CELL_AVAILABLE:
        case GMM_REGISTERED_NORMAL_SERVICE:
        case GMM_REGISTERED_UPDATE_NEEDED:
        case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
        case GMM_REGISTERED_LIMITED_SERVICE:
        case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
        case GMM_REGISTERED_IMSI_DETACH_INITIATED:
        case GMM_REGISTERED_NO_CELL_AVAILABLE:
        case GMM_GPRS_SUSPENSION:
        case GMM_SUSPENDED_GPRS_SUSPENSION:
        case GMM_REGISTERED_PLMN_SEARCH:
        case GMM_DEREGISTERED_PLMN_SEARCH:

            Gmm_TimerStop(GMM_TIMER_ALL);                                           /* 停所有Timer                              */
            g_GmmReqCnfMng.ucCnfMask = 0;                                           /* 清除原语等待标志                         */
            g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;                              /* 清除followon标志                         */
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

            if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
            {                                                                       /* 需要向SM回响应                           */
                Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_AUTHENTICATION_FAIL); /* 通知SM GMM注册失败                       */
                g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;
            }
            if (GMM_TRUE == g_GmmServiceCtrl.ucSmsFlg)
            {                                                                       /* SMS在等待响应                            */
                Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);                          /* 发送PMMSMS_ERROR_IND                     */
                g_GmmServiceCtrl.ucSmsFlg = GMM_FALSE;
            }
            if ((GMM_SERVICE_REQUEST_DATA_IDLE == g_GmmGlobalCtrl.ucSpecProc)
                || (GMM_SERVICE_REQUEST_DATA_CONN == g_GmmGlobalCtrl.ucSpecProc))
            {                                                                       /* 需要向RABM回响应                         */
                Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);             /* 发送GMMRABM_REESTABLISH_CNF(failure)     */
            }
            g_GmmGlobalCtrl.ucSpecProc     = GMM_NULL_PROCEDURE;                    /* 清除当前流程                             */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcAuthenticationFailureInd:INFO: specific procedure ended");
            g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;                    /* 清除保留流程                             */

            Gmm_HoldBufferFree();                                                   /* 清除保留消息                             */

            gstGmmSuspendCtrl.ucPreState = GMM_DEREGISTERED_NO_IMSI;
            ucGmmPreState = g_GmmGlobalCtrl.ucState;
            Gmm_ComStaChg(GMM_DEREGISTERED_NO_IMSI);                                /* 调用状态的公共处理                       */

            if (GMM_REGISTERED_INITIATED == ucGmmPreState)
            {
                NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                             GMM_MMC_ACTION_RESULT_FAILURE,
                                             NAS_MML_REG_FAIL_CAUSE_AUTH_REJ);
            }
            else if (GMM_ROUTING_AREA_UPDATING_INITIATED == ucGmmPreState)
            {
                NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                             GMM_MMC_ACTION_RESULT_FAILURE,
                                             NAS_MML_REG_FAIL_CAUSE_AUTH_REJ);
            }
            else if (GMM_SERVICE_REQUEST_INITIATED == ucGmmPreState)
            {
                NAS_GMM_SndMmcServiceRequestResultInd(GMM_MMC_ACTION_RESULT_FAILURE,
                                                      NAS_MML_REG_FAIL_CAUSE_AUTH_REJ);
            }

            else if (GMM_GPRS_SUSPENSION == ucGmmPreState)
            {
                Gmm_ComStaChg(GMM_GPRS_SUSPENSION);                                /* 调用状态的公共处理                       */
            }
            else if (GMM_SUSPENDED_GPRS_SUSPENSION == ucGmmPreState)
            {
                Gmm_ComStaChg(GMM_SUSPENDED_GPRS_SUSPENSION);                                /* 调用状态的公共处理                       */
            }
            else
            {
            }

            /* 清除相关标志 */
            NAS_GMM_ClearIMSIOfUeID();

            NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_PLMN_NOT_ALLOWED);  /* 更新状态更新为GU3 ROAMING NOT ALLOWED    */
            Gmm_DelPsLocInfoUpdateUsim();                                           /* 调用函数删除PS LOC INFO                  */
            break;                                                                  /* 跳出                                     */

        case GMM_NULL:
        case GMM_SUSPENDED_NORMAL_SERVICE:
        case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
            NAS_MML_SetSimPsRegStatus(VOS_FALSE);
            NAS_MML_SetPsUpdateStatus(NAS_MML_ROUTING_UPDATE_STATUS_PLMN_NOT_ALLOWED);  /* 更新状态更新为GU3 ROAMING NOT ALLOWED    */
            Gmm_DelPsLocInfoUpdateUsim();                                           /* 调用函数删除PS LOC INFO                  */

        default:                                                                    /* 其他情况                                 */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcAuthenticationFailureInd:WARNING: g_GmmGlobalCtrl.ucState is Error");
            break;                                                                  /* 跳出                                     */
    }
}

/*******************************************************************************
  Module   : NAS_GMM_RcvMmCsConnectInd
  Function : 原语MMCGMM_CM_SERVICE_IND的接收处理
  Input    : VOS_VOID  * pRcvMsg                指向原语的指针
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
     1. 张志勇  2003.12.11  新版作成
     2.日    期   : 2006年2月17日
       作    者   : liuyang id:48197
       修改内容   : 问题单号：A32D01287，打印错误
     3.日    期   : 2008年08月1日
       作    者   : luojian id:00107747
       修改内容   : 根据问题单AT2D04486/AT2D04822
     4.日    期   : 2010年11月1日
       作    者   : z00161729
       修改内容  : 问题单DTS2010111502913:通话过程中,T3312超时,GMM发起period_updating RAU成功,呼叫结束后又发起combined ralau with imsi attach,标杆不会发起
     5.日    期   : 2012年12月5日
       作    者   : t00212959
       修改内容   : DTS2012120504420:CSFB，rau被#10拒绝，ATTACH成功，CS结束，不发RAU
     6.日    期   : 2011年12月28日
       作    者   : l00167671
       修改内容   : 修改问题单DTS2012122001075,问题单场景如下:
                    PS建链过程中发生RA改变，该场景中如果CS域有业务则PS域做RAU
                    会被不确定的推迟到CS连接释放时才做，修改此场景中的操作如下:
                    若CS域有业务则给WAS发送RRMM_REL_REQ请求，请WAS释放连接，
                    并保存系统消息。在收到WAS的RRMM_REL_IND时用保存的系统消息做RAU
     7.日    期   : 2013年2月4日
       作    者   : w00176964
       修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
     8.日    期   : 2013年10月29日
       作    者   : w00176964
       修改内容   : VoLTE_PhaseII 项目修改:MM是否处于业务过程中的逻辑放在该消息的预处理中
     9.日    期   : 2015年1月5日
       作    者   : z00161729
       修改内容   : AT&T 支持DAM特性修改
******************************************************************************/
VOS_VOID NAS_GMM_RcvMmCsConnectInd(
    VOS_VOID                           *pstRcvMsg                               /* 接收消息使用的头地址定义                 */
)
{
    MMGMM_CS_CONNECT_IND_STRU          *pstMmCmServiceInd;                      /* 定义原语类型指针                         */

    pstMmCmServiceInd = (MMGMM_CS_CONNECT_IND_STRU *)pstRcvMsg;                   /* 强制类型转换                             */

    /* Modified by w00176964 for VoLTE_PhaseII 项目, 2013-10-29, begin */
    if (MMGMM_CS_CONNECT_ESTING == pstMmCmServiceInd->enCsConnectStatus)
    {

    }
    else if (MMGMM_CS_CONNECT_EXIST == pstMmCmServiceInd->enCsConnectStatus)
    {
        NAS_GMM_FreeGsmSysInfo();
    }
    else
    {
        NAS_GMM_ProcSavedGsmSysInfo();

        NAS_GMM_ProcSavedMmT3211ExpiredNotify();

        NAS_GMM_FreeWasSysInfo();
    }
    /* Modified by w00176964 for VoLTE_PhaseII 项目, 2013-10-29, end */

    if ((VOS_TRUE != NAS_MML_GetCsAttachAllowFlg())
     || (GMM_NET_MODE_I     != g_GmmGlobalCtrl.ucNetMod))
    {                                                                           /* 不是用户模式A且网络模式I                 */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvMmcCmServiceInd:NORMAL: It is not A+I(Gmm_RcvMmcCmServiceInd)");
        return;
    }

    if (GMM_FALSE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg)
    {                                                                           /* 标记CS不在通信中                         */
        /* g_GmmRauCtrl.ucCsSpringRauFlg标识是否为CS触发的RAU。
           只有在CM SERVICE REJECT原因值为4时，
           g_GmmRauCtrl.ucCsSpringRauFlg置为TRUE。
        */
        /*CSFB过程中RAU被#10拒，发Attach，状态为GMM_ATTACH_NORMAL*/
        if( ( GMM_TRUE == g_GmmRauCtrl.ucCsSpringRauFlg )
            || ((VOS_FALSE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
             && ((GMM_RAU_NORMAL == g_GmmGlobalCtrl.ucSpecProcInCsTrans)
             || (GMM_ATTACH_NORMAL == g_GmmGlobalCtrl.ucSpecProcInCsTrans))))
        {                                                                       /* CS触发RAU                                */
             switch (g_GmmGlobalCtrl.ucState)
             {                                                                  /* 根据状态分发                             */
             case GMM_REGISTERED_INITIATED:
             case GMM_ROUTING_AREA_UPDATING_INITIATED:
             case GMM_SERVICE_REQUEST_INITIATED:
                 NAS_GMM_RcvMmCsConnectInd_InProc(pstRcvMsg);                   /* 调用RAU/SR过程中的处理                   */
                 break;
             case GMM_REGISTERED_NORMAL_SERVICE:
             case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
             case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
                 NAS_GMM_RcvMmCsConnectInd_RegNmlServ();                        /* 调用该状态下的处理                       */
                 break;
             default:
                 PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcCmServiceInd:WARNING: g_GmmGlobalCtrl.ucState is Error");
                 break;
             }
             g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;               /* 清除当前进行的specific 流程标志          */
        }

        /*CSFB过程中RAU被#10拒，发Attach，状态为GMM_ATTACH_NORMAL*/
        if (((GMM_RAU_NORMAL == g_GmmGlobalCtrl.ucSpecProcInCsTrans)
          || (GMM_ATTACH_NORMAL == g_GmmGlobalCtrl.ucSpecProcInCsTrans))
         && (VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg))
        {
            g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;           /* 清除当前进行的specific 流程标志          */
        }
    }
    return;                                                                     /* 返回                                     */
}

/*******************************************************************************
  Module   : Gmm_Compare_Plmnid
  Function : 比较两个PLMN ID 是否相同
  Input    : GMM_PLMN_ID_STRU *pPlmnId1
             GMM_PLMN_ID_STRU *pPlmnId2
  Output   : 无
  NOTE     : 无
  Return   : GMM_TRUE   相同
             GMM_FALSE  不同
  History  :
    1. 欧阳飞  2009.02.12  新规作成
*******************************************************************************/
VOS_UINT8 Gmm_Compare_Plmnid(GMM_PLMN_ID_STRU *pPlmnId1,
                             GMM_PLMN_ID_STRU *pPlmnId2 )
{
    VOS_UINT8           i;                                                      /* 定义临时变量                             */

    for (i=0; i<3; i++)
    {                                                                           /* 在MCC个数内判断                          */
        if (pPlmnId1->aucMccDigit[i] != pPlmnId2->aucMccDigit[i])
        {                                                                       /* MCC不相同                                */
            return GMM_FALSE;                                                   /* 返回GMM_FALSE                            */
        }
    }

    if (pPlmnId1->ucMncCnt != pPlmnId2->ucMncCnt)
    {                                                                           /* MNC个数不相同                            */
        return GMM_FALSE;                                                       /* 返回GMM_FALSE                            */
    }

    for (i=0; i<pPlmnId1->ucMncCnt; i++)
    {                                                                           /* 在MNC个数内判断                          */
        if (pPlmnId1->aucMncDigit[i] != pPlmnId2->aucMncDigit[i])
        {                                                                       /* MNC不相同                                */
            return GMM_FALSE;                                                   /* 返回GMM_FALSE                            */
        }
    }

    return GMM_TRUE;                                                            /* 返回GMM_TRUE                             */
}

/*******************************************************************************
  Module   : Gmm_Compare_Lai
  Function : LAI的比较
  Input    : GMM_LAI_STRU   *pLAI1
             GMM_LAI_STRU   *pLAI2
  Output   : 无
  NOTE     : 无
  Return   : GMM_TRUE    相同
             GMM_FALSE   不同
  History  :
    1. 欧阳飞  2009.02.12  新规作成
*******************************************************************************/
VOS_UINT8 Gmm_Compare_Lai(GMM_LAI_STRU *pLAI1,
                          GMM_LAI_STRU *pLAI2)
{
    VOS_UINT8 ucRet;                                                            /* 定义返回值                               */

    ucRet = GMM_FALSE;                                                          /* 初始化                                   */

    if (GMM_TRUE == Gmm_Compare_Plmnid(&pLAI1->PlmnId, &pLAI2->PlmnId))
    {                                                                           /* PLMN相同                                 */
        if (  (pLAI1->aucLac[0] == pLAI2->aucLac[0])
            &&(pLAI1->aucLac[1] == pLAI2->aucLac[1]))
        {                                                                       /* LAC相同                                  */
            ucRet = GMM_TRUE;                                                   /* 赋返回值                                 */
        }
    }

    return ucRet;
}

/*******************************************************************************
  Module   : Gmm_Com_CmpRai
  Function : RAI的比较
  Input    : GMM_RAI_STRU   *pRAI1
             GMM_RAI_STRU   *pRAI2
  Output   : 无
  NOTE     : 无
  Return   : GMM_TRUE    相同
             GMM_FALSE   不同
  History  :
    1. 欧阳飞  2009.02.12  新规作成
*******************************************************************************/
VOS_UINT8 Gmm_Compare_Rai(GMM_RAI_STRU  *pRAI1,
                          GMM_RAI_STRU  *pRAI2)
{
    VOS_UINT8 ucRet = GMM_FALSE;                                                /* 定义返回值                               */

    if (GMM_TRUE == Gmm_Compare_Lai(&pRAI1->Lai, &pRAI2->Lai))
    {                                                                           /* LAI一致                                  */
        if (pRAI1->ucRac == pRAI2->ucRac)
        {                                                                       /* RAC一致                                  */
            ucRet = GMM_TRUE;                                                   /* 赋返回值                                 */
        }
    }

    return ucRet;
}

/*******************************************************************************
  Module   : Gmm_Get_Location_info
  Function : 获取小区信息变更情况。
  Input    : VOS_VOID  * pRai1               小区信息 1
             VOS_VOID  * pRai2               小区信息 2
  Output   : VOS_UINT8 * pucLaiChgFlg        LAI是否改变标志
             VOS_UINT8 * pucRaiChgFlg        RAI是否改变标志
  NOTE     : 无
  Return   : 无
  History  :
     1. 欧阳飞  2009.02.11  新版作成
                问题单号：AT2D08906，smartone UE没有处于attach状态, 就发起了业务请求
     2. 日    期   : 2012年3月22日
        作    者   : z00161729
        修改内容   : 支持ISR特性修改
     3. 日    期   : 2012年7月17日
        作    者   : z00161729
        修改内容   : DTS2012071606177:W(LAI1)-L(TAI2/LAI2 ISR激活CS LAI改变)-W(LAI1网络模式I)需要
                     发起联合rau
     4. 日    期   : 2012年7月17日
        作    者   : z00161729
        修改内容   : DTS2012073106360:ISR激活CSFB重定向或CCO到GU,idle态位置区不变无需做RAU
     5. 日    期   : 2012年09月08日
        作    者   : l65478
        修改内容   : DTS012090302087,L->GU时,RAI没有改变时,GMM发起了RAU
     6.日    期   : 2015年1月5日
       作    者   : z00161729
       修改内容   : AT&T 支持DAM特性修改
******************************************************************************/
 VOS_VOID Gmm_Get_Location_Change_info(
    GMM_RAI_STRU                       *pRai1,
    GMM_RAI_STRU                       *pRai2,
    VOS_UINT8                          *pucLaiChgFlg,
    VOS_UINT8                          *pucRaiChgFlg,
    VOS_UINT8                           ucNetMod
)
{
    VOS_UINT32                          ulIsPlmnInSupportDamPlmnInfo;
    VOS_UINT32                          ulT3302Status;

    ulIsPlmnInSupportDamPlmnInfo = NAS_MML_IsPlmnSupportDam(NAS_MML_GetCurrCampPlmnId());
    ulT3302Status                = NAS_GMM_QryTimerStatus(GMM_TIMER_T3302);

    if (GMM_FALSE == Gmm_Compare_Rai(pRai1, pRai2))
    {                                                                           /* 设置RAI是否变化标志                      */
        *pucRaiChgFlg = GMM_TRUE;
    }
    else
    {
        *pucRaiChgFlg = GMM_FALSE;
    }

#if (FEATURE_ON == FEATURE_LTE)
    if (NAS_MML_NET_RAT_TYPE_LTE == gstGmmSuspendCtrl.ucPreRat)
    {
        /* 3GPP 23401 4.3.5.6   Idle mode signalling reduction function:
           The Idle mode Signalling Reduction (ISR) function provides a
           mechanism to limit signalling during inter-RAT cell-reselection
           in idle mode (ECM-IDLE, PMM-IDLE, GPRS STANDBY states).
        */
        /* AT&T LTE-BTR-1-1824、LTE-BTR-1-1826和LTE-BTR-1-1828用例要求
           GMM在GU下attach无响应或被拒达最大次数启动T3302定时器，后续异系统
           或搜网到L下后无需停止，L下注册失败满足disable lte条件到GU下搜网
           回原失败小区时，等T3302超时后再做ps attach */
        if ((NAS_MML_TIN_TYPE_RAT_RELATED_TMSI != NAS_MML_GetTinType())
         && ((VOS_FALSE == ulIsPlmnInSupportDamPlmnInfo)
          || (VOS_FALSE == ulT3302Status)))

        {
            *pucRaiChgFlg = GMM_TRUE;
        }

        /* 如果网络模式I,从L异系统到GU,需要判断CS 的LAI是否改变，如果改变需要发起联合rau */
        if (GMM_TRUE == NAS_GMM_IsCsLaiChangeNeedRegister(ucNetMod))
        {
            *pucRaiChgFlg = GMM_TRUE;
        }
    }

#endif

    if (GMM_FALSE == Gmm_Compare_Lai(&(pRai1->Lai), &(pRai2->Lai)))
    {                                                                           /* 设置LAI是否变化标志                      */
        *pucLaiChgFlg = GMM_TRUE;
    }
    else
    {
        *pucLaiChgFlg = GMM_FALSE;
    }

    return;
}

/***********************************************************************
 *  MODULE   : Gmm_RcvMmcSysInfoInd_PS_BAR
 *  FUNCTION : Gmm_RcvMmcSysInfoInd函数降复杂度: PS BAR的处理
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1.  欧阳飞   2009.06.11  新版作成
     2.日    期   : 2012年2月15日
       作    者   : w00166186
       修改内容   : CSFB&PPAC&ETWS&ISR 开发
    3. 日    期   : 2012年12月11日
       作    者   : w00176964
       修改内容   : NAS_MML_GetPsRestrictNormalServiceFlg修改函数名
     4.日    期   : 2013年2月4日
       作    者   : w00176964
       修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
 ************************************************************************/
VOS_UINT8 Gmm_RcvMmcSysInfoInd_PS_BAR(
    VOS_UINT8                           ucLaiChgFlg
)
{
    VOS_UINT8                    ucRst = GMM_TRUE;

    if (VOS_TRUE == NAS_MML_GetPsRestrictRegisterFlg())
    {
        if  ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
          && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)
          && (GMM_FALSE == ucLaiChgFlg))
        {
            if ( ( GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState )
              || ( GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState )
              || ( GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH == g_GmmGlobalCtrl.ucState ))
            {
                NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);          /* 通知MM进行LU                             */
            }

        }

        if (GMM_DEREGISTERED_NO_IMSI == g_GmmGlobalCtrl.ucState)
        {

            g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;

            /* 向MMC发送PS注册结果 */
            NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                         GMM_MMC_ACTION_RESULT_FAILURE,
                                         NAS_MML_REG_FAIL_CAUSE_SIM_INVALID);

            g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;
            return ucRst;
        }
        else if(GMM_NULL == g_GmmGlobalCtrl.ucState)
        {
            ucRst = GMM_FALSE;
        }
        else if ((GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
            || (0x10 == (g_GmmGlobalCtrl.ucState & 0xF0)))
        {
            Gmm_ComStaChg(GMM_DEREGISTERED_ATTACH_NEEDED);
            ucRst = GMM_FALSE;
        }
        else
        {
            Gmm_ComStaChg(GMM_REGISTERED_UPDATE_NEEDED);
            ucRst = GMM_FALSE;
        }

        /* 如果当前业务受限，则清除缓存 */
        /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
        if (VOS_TRUE == NAS_MML_GetPsRestrictNormalServiceFlg())
        /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */
        {
            Gmm_ComCnfHandle();
            GMM_BufferMsgDump();
        }
        else
        {
            GMM_BufferMsgResume();
        }

        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;
    }

    return ucRst;
}

/***********************************************************************
 *  MODULE   : Gmm_RcvMmcSysInfoIndRelEstingLink
 *  FUNCTION : Gmm_RcvMmcSysInfoInd函数降复杂度: ucRaiChgFlg的处理
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1.  欧阳飞   2009.06.11  新版作成
    2. 日    期   : 2010年10月28日
       作    者   : h44270
       修改内容   : 问题单DTS2010091401278,网络模式改变后没有发起PDP重建，修改函数名
    3. 日    期   : 2010年10月28日
       作    者   : h44270
       修改内容   : 问题单DTS2011071503390,开始驻留在LAI1,重选到LAI2,在注册过程中
                    有重选回LAI1后,MM发起了注册,GMM没有发起注册
    4. 日    期   : 2013年03月07日
       作    者   : l00167671
       修改内容   : 问题单DTS2013030502525,在RAI1上做RAU建立链接成功之前路由区变更到RAI2
                          未发起RAU
 ************************************************************************/
VOS_UINT8 Gmm_RcvMmcSysInfoIndRelEstingLink(VOS_VOID)
{
    VOS_UINT8                    ucRst = GMM_TRUE;
    NAS_MML_RAI_STRU                       *pstLastSuccRai;
    GMM_RAI_STRU                            stGmmRai;

    pstLastSuccRai    = NAS_MML_GetPsLastSuccRai();
    NAS_GMM_ConvertPlmnIdToGmmFormat(&(pstLastSuccRai->stLai.stPlmnId), &stGmmRai.Lai.PlmnId);

    stGmmRai.ucRac          = pstLastSuccRai->ucRac;
    stGmmRai.Lai.aucLac[0]  = pstLastSuccRai->stLai.aucLac[0];
    stGmmRai.Lai.aucLac[1]  = pstLastSuccRai->stLai.aucLac[1];

    if (GMM_TIMER_T3340_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3340_FLG))
    {
        /* T3340正在运行中，等链路释放后再处理系统消息 */
        g_GmmGlobalCtrl.ucRaiChgRelFlg = GMM_TRUE;
        ucRst = GMM_FALSE;
    }

    if ((GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
        && (GMM_RRC_RRMM_EST_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)))
    {                                                                       /* 无信令且正在建立信令连接                 */
        if (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
        {                                                                   /* GMM_REGISTERED_INITIATED状态             */
            Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);
            Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);
            Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);
            g_GmmReqCnfMng.ucCnfMask  &= ~GMM_RRC_RRMM_EST_CNF_FLG;         /* 清除等待CNF标志                          */
            g_GmmGlobalCtrl.ucSpecProc =  GMM_NULL_PROCEDURE;               /* 清除当前进行的specific过程               */
            ucRst = GMM_FALSE;
        }
        else if (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
        {
            /*Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);*/

            /* GMM的更新状态在U1时,GMM为正常服务;否则GMM迁移到ATT-TO-UPDATE，启动3311进行尝试 */
            if (NAS_MML_ROUTING_UPDATE_STATUS_UPDATED == NAS_MML_GetPsUpdateStatus())
            {
                g_GmmGlobalCtrl.SysInfo.Rai = stGmmRai;
                Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);
            }
            else
            {
                Gmm_ComStaChg(GMM_REGISTERED_ATTEMPTING_TO_UPDATE);
                Gmm_TimerStart(GMM_TIMER_T3311);
            }
            Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);
            Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);
            g_GmmReqCnfMng.ucCnfMask  &= ~GMM_RRC_RRMM_EST_CNF_FLG;         /* 清除等待CNF标志                          */
            g_GmmGlobalCtrl.ucSpecProc =  GMM_NULL_PROCEDURE;               /* 清除当前进行的specific过程               */
            g_GmmGlobalCtrl.ucRaiChgRelFlg = GMM_TRUE;
            ucRst = GMM_FALSE;
        }
        else if (GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucState)
        {
            Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);
            Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);
            Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);
            g_GmmReqCnfMng.ucCnfMask &= ~GMM_RRC_RRMM_EST_CNF_FLG;          /* 清除等待CNF标志                          */

            g_GmmGlobalCtrl.ucFollowOnFlg  = GMM_TRUE;
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

            g_GmmGlobalCtrl.ucSpecProcHold = g_GmmGlobalCtrl.ucSpecProc;
            g_GmmGlobalCtrl.ucSpecProc     = GMM_NULL_PROCEDURE;            /* 清除当前进行的specific过程               */
            g_GmmGlobalCtrl.ucRaiChgRelFlg = GMM_TRUE;
            ucRst = GMM_FALSE;
        }
        else if (GMM_DEREGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
        {
            Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);
            Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);
            Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);
            g_GmmReqCnfMng.ucCnfMask &= ~GMM_RRC_RRMM_EST_CNF_FLG;

            g_GmmGlobalCtrl.ucFollowOnFlg  = GMM_TRUE;
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

            g_GmmGlobalCtrl.ucSpecProcHold = g_GmmGlobalCtrl.ucSpecProc;
            g_GmmGlobalCtrl.ucSpecProc     = GMM_NULL_PROCEDURE;
            g_GmmGlobalCtrl.ucRaiChgRelFlg = GMM_TRUE;
            ucRst = GMM_FALSE;
        }
        else if (GMM_REGISTERED_IMSI_DETACH_INITIATED == g_GmmGlobalCtrl.ucState)
        {
            Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);
            Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);
            Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);
            g_GmmReqCnfMng.ucCnfMask &= ~GMM_RRC_RRMM_EST_CNF_FLG;

            g_GmmGlobalCtrl.ucFollowOnFlg  = GMM_TRUE;
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

            g_GmmGlobalCtrl.ucSpecProcHold = g_GmmGlobalCtrl.ucSpecProc;
            g_GmmGlobalCtrl.ucSpecProc     = GMM_NULL_PROCEDURE;
            g_GmmGlobalCtrl.ucRaiChgRelFlg = GMM_TRUE;
            ucRst = GMM_FALSE;
        }
        else
        {
        }
    }

    return ucRst;
}

/***********************************************************************
 *  MODULE   : Gmm_RcvMmcSysInfoInd_Fill_pRaiTemp
 *  FUNCTION : Gmm_RcvMmcSysInfoInd函数降复杂度: pRaiTemp的赋值
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1.  欧阳飞   2009.06.11  新版作成
 ************************************************************************/
VOS_VOID Gmm_RcvMmcSysInfoInd_Fill_pRaiTemp(GMM_RAI_STRU         *pRaiTemp,
                                            VOS_VOID             *pRcvMsg
                                            )
{
    MMCGMM_SYS_INFO_IND_STRU    *pSysInfoInd;                                   /* 定义MMCGMM_SYS_INFO_IND_STRU类型指针     */

    Gmm_MemCpy(pRaiTemp, &g_GmmGlobalCtrl.SysInfo.Rai, sizeof(GMM_RAI_STRU));

    pSysInfoInd = (MMCGMM_SYS_INFO_IND_STRU *)pRcvMsg;                          /* 得到原语指针                             */

    if (0 != pSysInfoInd->ulCnCommonSize)
    {                                                                           /* CnCommonInfo不为空                       */
        pRaiTemp->Lai.aucLac[0] = pSysInfoInd->aucCnCommonInfo[0];
        pRaiTemp->Lai.aucLac[1] = pSysInfoInd->aucCnCommonInfo[1];              /* LAC                                      */
    }

    if (MMC_GMM_SYS_MSK_PLMN == (pSysInfoInd->ulMask & MMC_GMM_SYS_MSK_PLMN))
    {
        pRaiTemp->Lai.PlmnId.aucMccDigit[0] =
            (VOS_UINT8)(pSysInfoInd->PlmnId.ulMcc & 0x0F);                          /* MCC Digit 1                              */
        pRaiTemp->Lai.PlmnId.aucMccDigit[1] =
            (VOS_UINT8)((pSysInfoInd->PlmnId.ulMcc >> 8) & 0x0F);                   /* MCC Digit 2                              */
        pRaiTemp->Lai.PlmnId.aucMccDigit[2] =
            (VOS_UINT8)((pSysInfoInd->PlmnId.ulMcc >> 16) & 0x0F);                  /* MCC Digit 3                              */
        pRaiTemp->Lai.PlmnId.aucMncDigit[0] =
            (VOS_UINT8)(pSysInfoInd->PlmnId.ulMnc & 0x0F);                          /* MNC Digit 1                              */
        pRaiTemp->Lai.PlmnId.aucMncDigit[1] =
            (VOS_UINT8)((pSysInfoInd->PlmnId.ulMnc >> 8) & 0x0F);                   /* MNC Digit 2                              */
        pRaiTemp->Lai.PlmnId.aucMncDigit[2] =
            (VOS_UINT8)((pSysInfoInd->PlmnId.ulMnc >> 16) & 0x0F);                  /* MNC Digit 3                              */
        pRaiTemp->Lai.PlmnId.ucMncCnt = 3;                                      /* MNC Degit count                          */
        if (GMM_PLMNID_MNC3_INVALID == pRaiTemp->Lai.PlmnId.aucMncDigit[2])
        {
            pRaiTemp->Lai.PlmnId.ucMncCnt = 2;                                  /* MNC Degit count                          */
        }
    }
    if (MMC_GMM_SYS_MSK_CSPS_INFO
        == (pSysInfoInd->ulMask & MMC_GMM_SYS_MSK_CSPS_INFO))
    {
          if (0 != pSysInfoInd->ulPsInfoSize)
          {
              pRaiTemp->ucRac = (VOS_UINT8)pSysInfoInd->aulPsInfo[0];               /* RAC                                      */
          }
    }

    return;
}

/***********************************************************************
 *  MODULE   : Gmm_RcvMmcSysInfoInd_PreProcess_Handling
 *  FUNCTION : Gmm_RcvMmcSysInfoInd函数降复杂度: 消息分发前的预处理
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1.  欧阳飞   2009.06.11  新版作成
     2. 日    期   : 2009年08月01日
        作    者   : o00132663
        修改内容   : 问题单：AT2D13412, 对于GMM发起联合RAU重建Gs关联的场景，增加PS已注册的判定条件。
     3.日    期   : 2011年03月1日
       作    者   : w00176964
       修改内容   : 问题单号：DTS2011022503955, [正向质量活动-背景搜优化双模]背景搜快速指定搜过程中，发起
                    用户列表搜索，关机等操作，停止搜网后回RPLMN成功，但当前小区禁止或不支持CS/PS，缓存的用
                    户操作未立即处理，需要等待定时器超时进行异常处理
     4.日    期   : 2012年2月15日
       作    者   : w00166186
       修改内容   : CSFB&PPAC&ETWS&ISR 开发
     5.日    期   : 2012年8月14日
       作    者   : t00212959
       修改内容   : DCM定制需求和遗留问题
     6.日    期   : 2013年2月4日
       作    者   : w00176964
       修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
     7.日    期   : 2013年6月18日
       作    者   : l65478
       修改内容   : 问题单号：DTS2013061406222,发起RAU时应该判断 CS的业务状态
 ************************************************************************/
VOS_UINT8 Gmm_RcvMmcSysInfoInd_PreProcess_Handling(VOS_UINT8                    ucNetMod,
                                                   VOS_UINT8                    ucRaiChgFlg,
                                                   MMCGMM_SYS_INFO_IND_STRU    *pSysInfoInd,
                                                   VOS_UINT8                   *pucDrxLengthChgFlg
                                                )
{
    VOS_UINT8                           ucRst = GMM_TRUE;
    VOS_UINT8                           ucCsChanged2UnBarFlg;
    VOS_UINT8                           ucCsRestrictionFlg;
    VOS_UINT8                           ucPsRestrictionFlg;
    VOS_UINT8                           ucCsAttachAllow;
    VOS_UINT8                           ucPsAttachAllow;

    ucCsAttachAllow = NAS_MML_GetCsAttachAllowFlg();
    ucPsAttachAllow = NAS_MML_GetPsAttachAllowFlg();

    g_GmmGlobalCtrl.SysInfo.ucNetMod = ucNetMod;                                /* 网络模式                                 */
    if (g_GmmGlobalCtrl.ucNetMod != ucNetMod)
    {
        g_GmmGlobalCtrl.ucNetMod = ucNetMod;                                /* 网络模式                                 */
    }

    g_GmmGlobalCtrl.SysInfo.ucForbMask = (VOS_UINT8)pSysInfoInd->ulForbiddenMask;   /* PLMN是否禁止                             */
    g_GmmGlobalCtrl.SysInfo.ucSysValidFlg = GMM_TRUE;                           /* 置系统信息有效标志                       */
    if (GMM_TRUE == *pucDrxLengthChgFlg)
    {                                                                           /* 系统信息中带有DRX length信息             */
        /* Modified by t00212959 for DCM定制需求和遗留问题, 2012-8-16, begin */
        NAS_MML_SetWSysInfoDrxLen((VOS_UINT8)pSysInfoInd->ulPsDrxLength);       /* 存储DRX LENGTH                           */
        /* Modified by t00212959 for DCM定制需求和遗留问题, 2012-8-16, end */

        *pucDrxLengthChgFlg = GMM_FALSE;
    }

    ucCsChanged2UnBarFlg            =   pSysInfoInd->ucCsChanged2UnBarFlg;
    ucCsRestrictionFlg              =   NAS_MML_GetCsRestrictRegisterFlg();
    ucPsRestrictionFlg              =   NAS_MML_GetPsRestrictRegisterFlg();
    gstGmmCasGlobalCtrl.ucSysRauFlg = ucRaiChgFlg;
    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {
        gstGmmCasGlobalCtrl.ucSysRauFlg = GMM_FALSE;
        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);
    }
    else
    {
        /* PS已注册，CS域从bar到不bar, 且Gs关联未建立,此时GMM需要发起联合RAU重建Gs关联。 */
        if (   (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)
            && (MMC_GMM_NO_FORBIDDEN == g_GmmGlobalCtrl.SysInfo.ucForbMask)
            && (VOS_TRUE == ucCsAttachAllow)
            && (VOS_TRUE == ucPsAttachAllow)
            && (GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState))
        {
            if ( (VOS_FALSE == ucPsRestrictionFlg)
              && (VOS_FALSE == ucCsRestrictionFlg)
              && (VOS_TRUE == ucCsChanged2UnBarFlg)
              && (VOS_FALSE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
              && (GMM_FALSE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg))
            {
                Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
                ucRst = GMM_FALSE;
            }
        }
    }

    return ucRst;
}

/***********************************************************************
 *  MODULE   : Gmm_RcvMmcSysInfoInd_CSPS_INFO
 *  FUNCTION : Gmm_RcvMmcSysInfoInd函数降复杂度: CSPS_INFO的处理
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1.  欧阳飞   2009.06.11  新版作成
 ************************************************************************/
VOS_VOID Gmm_RcvMmcSysInfoInd_CSPS_INFO(MMCGMM_SYS_INFO_IND_STRU    *pSysInfoInd,
                                        VOS_UINT8                   *pucNetMod
                                            )
{
    if (MMC_GMM_SYS_MSK_CSPS_INFO
        == (pSysInfoInd->ulMask & MMC_GMM_SYS_MSK_CSPS_INFO))
    {
        if (0 != pSysInfoInd->ulPsInfoSize)
        {
            if (0 == (VOS_UINT8)(pSysInfoInd->aulPsInfo[0] >> 8))
            {
                *pucNetMod = GMM_NET_MODE_I;
            }
            else
            {
                *pucNetMod = GMM_NET_MODE_II;
            }
            g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs = GMM_SUPPORT_GPRS;
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd:INFO: MS camp on a cell that GPRS is supported");
        }
        else
        {
            g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs = GMM_NOT_SUPPORT_GPRS;  /* 设置当前小区不支持GPRS标志                */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd:INFO: MS camp on a cell that GPRS is not supported");
        }
    }
    else
    {
        g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs = GMM_NOT_SUPPORT_GPRS;  /* 设置当前小区不支持GPRS标志                */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_RcvMmcSysInfoInd:INFO: MS camp on a cell that GPRS is not supported");
    }

    return;
}

/***********************************************************************
 *  MODULE   : Gmm_RcvMmcSysInfoInd_ucNetModeChange_Handling
 *  FUNCTION : Gmm_RcvMmcSysInfoInd函数降复杂度: ucNetModeChange处理
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1. 欧阳飞   2009.06.11  新版作成
     2. 日    期   : 2010年10月28日
        作    者   : h44270
        修改内容   : 问题单DTS2010091401278,网络模式改变后没有发起PDP重建，修改函数名
     3. 日    期   : 2010年12月01日
        作    者   : z00161729
        修改内容  : DTS2010111903590:LAI、RAI、CELL均未变只是网络模式发生改变，UE发起RAU或LAU，标杆不会
     4. 日    期   : 2012年03月17日
        作    者   : s46746
        修改内容   : DTS2012030705720:RAI和网络模式发生改变,需要进行LAU流程
 ************************************************************************/
VOS_UINT8 Gmm_RcvMmcSysInfoInd_ucNetModeChange_Handling
(
    VOS_UINT8                           ucNetMod,
    MMCGMM_SYS_INFO_IND_STRU           *pSysInfoInd,
    VOS_UINT8                          *pucLaiChgFlg,
    VOS_UINT8                          *pucRaiChgFlg
)
{
    VOS_UINT8                    ucRst = GMM_TRUE;

    if ((g_GmmGlobalCtrl.SysInfo.ucNetMod != ucNetMod)
        && (0 != g_GmmGlobalCtrl.SysInfo.ucNetMod))
    {                                                                           /* 网络模式变更                             */
        if ((GMM_TRUE == *pucLaiChgFlg)
         || (GMM_TRUE == *pucRaiChgFlg))
        {
            g_GmmRauCtrl.ucT3330outCnt = 0;

            if ((NAS_MML_MS_MODE_PS_CS == NAS_MML_GetMsMode())
                && (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta)
                && (0x10 != g_GmmGlobalCtrl.ucState))
            {                                                                       /* 用户模式为A,并且已经注册                 */
                if (GMM_SUSPENDED_WAIT_FOR_SYSINFO != g_GmmGlobalCtrl.ucState)
                {/* 非异系统挂起过程等待小区系统消息状态 */
                    if ((GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
                     && (GMM_RRC_RRMM_EST_CNF_FLG == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)))
                    {
                        (VOS_VOID)Gmm_RcvMmcSysInfoIndRelEstingLink();
                        ucRst = GMM_FALSE;
                        return ucRst;
                    }
                    else
                    {
                        /* 非异系统挂起过程等待小区系统消息状态 */
                        /* 同系统的小区系统消息处理 */
                        Gmm_ComNetModeChange(pSysInfoInd);                              /* 调用网络模式变换的公共处理               */
                        ucRst = GMM_FALSE;
                        return ucRst;
                    }
                }
            }
        }
        gstGmmSuspendCtrl.ucNetModeChange = GMM_CasGetNetChgType(ucNetMod);
    }
    else
    {
        gstGmmSuspendCtrl.ucNetModeChange = GMM_NETMODE_CHG_NULL;
    }

    return ucRst;
}

/***********************************************************************
 *  MODULE   : Gmm_RcvMmcSysInfoInd_State_Distribute
 *  FUNCTION : Gmm_RcvMmcSysInfoInd函数降复杂度: 消息分状态处理
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
     1.  欧阳飞   2009.06.11  新版作成
     2. 日    期   : 2009年07月23日
        作    者   : L65478
        修改内容  : 问题单号:AT2D13173,GMM在收到系统信息后，给MMC发送了NO SERVICE，导致MMC启动了搜网定时器
    3. 日    期   : 2010年12月24日
       作    者   : s46746
       修改内容   : 根据问题单号：DTS2010121400435，五次联合注册失败后，只进行了一次CS注册
    4. 日    期   : 2011年10月31日
       作    者   : w00166186
       修改内容   : 列表搜过程，GMM没有上报系统消息，导致列表搜失败
    5. 日    期   : 2014年06月15日
       作    者   : s00217060
       修改内容   : DTS2014061003286:TD2G重选，G下RAU过程中，用户指定搜TD的网络，网络不回应数据业务accept
 ************************************************************************/
VOS_VOID Gmm_RcvMmcSysInfoInd_State_Distribute(
                                  VOS_VOID    *pRcvMsg,                                 /* 消息指针                                 */
                                  VOS_UINT8    ucRaiChgFlg,                          /* RAI变化标志                              */
                                  VOS_UINT8    ucDrxLengthChgFlg,                    /* DRX length变化标志                       */
                                  VOS_UINT8    ucLaiChgFlg                           /* LAI变化标志                              */
                                  )
{
    if ((GMM_REGISTERED_PLMN_SEARCH == g_GmmGlobalCtrl.ucState)
     && (GMM_TRUE == g_GmmGlobalCtrl.ucCvrgAreaLostFlg))
    {
        if(GMM_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
        {
            g_GmmGlobalCtrl.ucNeedChgServiceStatus = VOS_FALSE;
        }
        Gmm_ComStaChg(GMM_REGISTERED_NO_CELL_AVAILABLE);
        g_GmmGlobalCtrl.ucNeedChgServiceStatus = VOS_TRUE;
    }

    gstGmmCasGlobalCtrl.TempMsgPara.ucRaiChgFlg = ucRaiChgFlg;
    gstGmmCasGlobalCtrl.TempMsgPara.ucDrxLengthChgFlg = ucDrxLengthChgFlg;

    /* 将原语MMCGMM_SYS_INFO_IND按照状态分发 */
    switch (g_GmmGlobalCtrl.ucState)
    {
    case GMM_REGISTERED_INITIATED:
        Gmm_RcvMmcSysInfoInd_RegInit(pRcvMsg,
                                     ucRaiChgFlg,
                                     ucDrxLengthChgFlg,
                                     ucLaiChgFlg);
        break;
    case GMM_DEREGISTERED_INITIATED:
    case GMM_REGISTERED_IMSI_DETACH_INITIATED:
        Gmm_RcvMmcSysInfoInd_DeregInit(pRcvMsg,
                                       ucRaiChgFlg,
                                       ucDrxLengthChgFlg,
                                       ucLaiChgFlg);
        break;
    case GMM_ROUTING_AREA_UPDATING_INITIATED:
        Gmm_RcvMmcSysInfoInd_RauInit(pRcvMsg,
                                     ucRaiChgFlg,
                                     ucDrxLengthChgFlg,
                                     ucLaiChgFlg);
        break;
    case GMM_SERVICE_REQUEST_INITIATED:
        Gmm_RcvMmcSysInfoInd_ServReqInit(pRcvMsg,
                                         ucRaiChgFlg,
                                         ucDrxLengthChgFlg,
                                         ucLaiChgFlg);
        break;
    case GMM_DEREGISTERED_NO_CELL_AVAILABLE:
    case GMM_DEREGISTERED_NORMAL_SERVICE:
    case GMM_DEREGISTERED_LIMITED_SERVICE:
    case GMM_DEREGISTERED_ATTACH_NEEDED:
    case GMM_DEREGISTERED_PLMN_SEARCH:
        Gmm_RcvMmcSysInfoInd_DeregNmlServ(pRcvMsg, ucLaiChgFlg);
        break;
    case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
        Gmm_RcvMmcSysInfoInd_DeregAtmpToAtch(pRcvMsg,
                                             ucRaiChgFlg,
                                             ucDrxLengthChgFlg,
                                             ucLaiChgFlg);
        break;
    case GMM_REGISTERED_NORMAL_SERVICE:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:

        Gmm_RcvMmcSysInfoInd_RegNmlServ(pRcvMsg,
                                        ucRaiChgFlg,
                                        ucDrxLengthChgFlg,
                                        ucLaiChgFlg);
        break;

    case GMM_REGISTERED_PLMN_SEARCH:

        NAS_GMM_RcvMmcSysInfoInd_RegPlmnSrch(pRcvMsg,
                                        ucRaiChgFlg,
                                        ucDrxLengthChgFlg,
                                        ucLaiChgFlg);
        break;
    case GMM_REGISTERED_UPDATE_NEEDED:
        Gmm_RcvMmcSysInfoInd_RegNoCell(pRcvMsg,
                                       ucRaiChgFlg,
                                       ucDrxLengthChgFlg,
                                       ucLaiChgFlg);
        break;
    case GMM_REGISTERED_LIMITED_SERVICE:
        Gmm_RcvMmcSysInfoInd_RegUpdtNeed(pRcvMsg, ucLaiChgFlg);
        break;
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
        Gmm_RcvMmcSysInfoInd_RegAtmpToUpdt(pRcvMsg,
                                           ucRaiChgFlg,
                                           ucDrxLengthChgFlg,
                                           ucLaiChgFlg);
        break;
    case GMM_REGISTERED_NO_CELL_AVAILABLE:
        Gmm_RcvMmcSysInfoInd_RegNoCell(pRcvMsg,
                                       ucRaiChgFlg,
                                       ucDrxLengthChgFlg,
                                       ucLaiChgFlg);
        break;
    case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
        Gmm_RcvMmcSysInfoInd_SuspWaitSys(pRcvMsg,ucRaiChgFlg,ucLaiChgFlg);
        break;
    case GMM_DEREGISTERED_NO_IMSI:
        g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;
        /* 向MMC发送PS注册结果 */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                     GMM_MMC_ACTION_RESULT_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_SIM_INVALID);
        g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;
        break;
    default :
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcSysInfoInd:WARNING:g_GmmGlobalCtrl.ucState is Error");
        break;
    }

    return;
}

/*******************************************************************************
  Module   : Gmm_RcvMmcSysInfoInd
  Function : 原语MMCGMM_SYS_INFO_IND的接收处理
  Input    : VOS_VOID *pRcvMsg  接收消息使用的头地址定义
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2003.12.11  新规作成
    2.日    期   : 2006年9月9日
      作    者   : sunxibo id:46746
      修改内容   : 根据问题单号：A32D05653
    3.日    期   : 2006年10月9日
      作    者   : s46746
      修改内容   : 根据问题单号：A32D05744
    4.日    期   : 2006年11月20日
      作    者   : s46746
      修改内容   : 创建，根据问题单号：A32D07433
    5.日    期   : 2007年1月26日
      作    者   : liurui id:40632
      修改内容   : 根据问题单号：A32D08577
    6.日    期   : 2007年03月20日
      作    者   : x51137
      修改内容   : A32D09192
    6.日    期   : 2007年06月22日
      作    者   : l60022475
      修改内容   : A32D11911
    7.日    期   : 2007年10月26日
      作    者   : l39007
      修改内容   : A32D13207
    8.日    期   : 2007-10-26
      作    者   : hanlufeng
      修改内容   : A32D13172
    9.日    期   : 2007年12月15日
      作    者   : l00107747
      修改内容   : 问题单号:A32D13897
   10.日    期   : 2009年01月15日
      作    者   : l00130025
      修改内容   : 问题单号:AT2D07018,LAU或RAU过程中搜网和SYSCFG设置,发起底层释放链接的操作
   11.日    期   : 2009年03月18日
      作    者   : l65478
      修改内容   : 根据问题单号：AT2D08671,数传状态下，W出服务区后，切到G，数传恢复失败，因为GMM没有配置LL加密算法
   12.日    期   : 2009年9月03日
      作    者   : l65478
      修改内容   : created AT2D14239,detach完成后,再次发起ATTATCH REQ时,GAS使用旧的TLLI建立的TBF发送数据,没有及时使用新的TLLI,导致MS和仪器侧维护的TLLI不一致,从而导致GAS因为TLLI不匹配丢弃了建立下行TBF的指派命令,最终导致用例失败
   13.日    期   : 2010年8月14日
      作    者   : s46746
      修改内容   : DTS2010073001405,G2W异系统重选后，不向层2发送去指派而是挂起层2
   14.日    期   : 2010年10月28日
      作    者   : h44270
      修改内容   : 问题单DTS2010091401278,网络模式改变后没有发起PDP重建，修改函数名
   15.日    期   : 2011年02月21日
      作    者   : w00176964
      修改内容   : 问题单号: DTS2011021102016. [V3C02B020][BG搜]BG搜成功但指定搜失败后，会因保护定时器超时
                   再次启动BG搜
   16.日    期   : 2011年03月1日
      作    者   : w00176964
      修改内容   : 问题单号：DTS2011022503955, [正向质量活动-背景搜优化双模]背景搜快速指定搜过程中，发起
                   用户列表搜索，关机等操作，停止搜网后回RPLMN成功，但当前小区禁止或不支持CS/PS，缓存的用
                   户操作未立即处理，需要等待定时器超时进行异常处理
   17.日    期   : 2011年7月13日
      作    者   : w00176964
      修改内容   : V7R1 PhaseII阶段调整，向RABM指示RAB是否需要重建
   18.日    期   : 2011年7月13日
      作    者   : l00130025
      修改内容   : V7R1 PhaseII阶段调整，删除UserDelay标志，由MMC处理
   19.日    期   : 2011年5月20日
      作    者   : f00179208
      修改内容   : 根据问题单号：DTS20110517005731,出服务区后T3212超时，原先小区是NMO1，
                   UE回覆盖后的小区不支持GPRS，同LA，没有做周期性LAU
   20.日    期   : 2011年4月6日
      作    者   : c00173809
      修改内容   : 根据问题单号：DTS2011032900575,NMO1周期性RAU丢网到NMO1不支持
                   GPRS的小区中，T3312超时没有发起周期性LAU
   21.日    期   : 2011年12月2日
      作    者   : s46746
      修改内容   : 从L异系统改变到GU后，没有指派加密密钥到GU接入层
   22.日    期   : 2012年03月20日
      作    者   : l00130025
      修改内容   : DTS2012030105247,NAS只在网侧实际发起鉴权时,通知W SecurityKey，其它情况下由WAS调用对应接口获取
   23.日    期   : 2012年4月17日
      作    者   : z00161729
      修改内容  : DTS2012041402264：L小区下发起CS语音业务，通过重定向CS Fallback到W小区。激活PDP后释放CS语音，未上系统消息，UE不会发起联合RAU
   24.日    期   : 2012年7月17日
      作    者   : z00161729
      修改内容  : DTS2012071606177:W(LAI1)-L(TAI2/LAI2 ISR激活CS LAI改变)-W(LAI1网络模式I)需要
                    发起联合rau
   25.日    期   : 2012年8月14日
      作    者   : t00212959
      修改内容   : DCM定制需求和遗留问题
   26.日    期   : 2011年12月28日
      作    者  : l00167671
      修改内容  : 修改问题单DTS2012122001075,问题单场景如下:
                 PS建链过程中发生RA改变，该场景中如果CS域有业务则PS域做RAU
                 会被不确定的推迟到CS连接释放时才做，修改此场景中的操作如下:
                 若CS域有业务则给WAS发送RRMM_REL_REQ请求，请WAS释放连接，
                 并保存系统消息。在收到WAS的RRMM_REL_IND时用保存的系统消息做RAU
   27.日    期   : 2013年6月11日
      作    者   : z00234330
      修改内容   : DTS2013061152841,从bar的小区到不bar的小区,GMM通知wrr建链消息里面携带的plmn id为0
   28.日    期   : 2014年1月26日
      作    者   : w00242748
      修改内容   : DTS2014011800247:修正GMM在ACC BAR时，GMM给MMC发送的PS域注册原因值
   29.日    期   : 2014年10月22日
      作    者   : z00161729
      修改内容   : DTS2014102109190:勾gmm和mm的全局变量，增加可维可测信息
   30.日    期   : 2014年12月25日
      作    者   : w00167002
      修改内容   : DTS2014122201960:在L下SRVCC HO到G再HO到W,RABM触发重建，导致立即
                   触发RAU，后续收到系统消息又再次发起RAU,导致网络REL了链路，导致
                   掉话。修改为在HO后，启动保护定时器等系统消息。
   31.日    期   : 2015年1月15日
      作    者   : z00161729
      修改内容   : AT&T 支持DAM特性修改
   32.日    期   : 2015年6月5日
      作    者   : z00161729
      修改内容   : 24008 23122 R11 CR升级项目修改
*******************************************************************************/
VOS_VOID Gmm_RcvMmcSysInfoInd(
                          VOS_VOID *pRcvMsg                                     /* 接收消息使用的头地址定义                 */
                          )
{
    MMCGMM_SYS_INFO_IND_STRU    *pSysInfoInd;                                   /* 定义MMCGMM_SYS_INFO_IND_STRU类型指针     */
    VOS_UINT8                    ucRaiChgFlg = GMM_FALSE;
    VOS_UINT8                    ucLaiChgFlg = GMM_FALSE;
    VOS_UINT8                    ucDrxLengthChgFlg = GMM_FALSE;
    GMM_RAI_STRU                *pRaiTemp = VOS_NULL_PTR;
    VOS_UINT8                    ucNetMod = g_GmmGlobalCtrl.ucNetMod;
    VOS_UINT32                   ulNewCellId;
    VOS_UINT8                    ucRst = GMM_TRUE;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    GMM_RAI_STRU                 stAttempUpdateRaiInfo;
    GMM_RAI_STRU                 stOldRai;
    NAS_MML_RAI_STRU            *pstAttemptUpdateRaiInfo = VOS_NULL_PTR;

    VOS_UINT8                           ucSimPsRegStatus;
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulT3423StatuChgNeedRegFlg;
    VOS_UINT32                          ulIsNeedDeactiveIsrFlg;
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrNetType;

    pstRplmnCfgInfo           = NAS_MML_GetRplmnCfg();
    enCurrNetType             = NAS_MML_GetCurrNetRatType();
    ulT3423StatuChgNeedRegFlg = NAS_GMM_IsT3423StatusChangeNeedRegist(NAS_MML_GetLteCsServiceCfg(),
                                 NAS_MML_GetTinType(), NAS_MML_GetT3423Status());
#endif

    enCurRat = NAS_MML_GetCurrNetRatType();
    pSysInfoInd = (MMCGMM_SYS_INFO_IND_STRU *)pRcvMsg;                          /* 得到原语指针                             */

    NAS_GMM_LogGmmCtxInfo();

    Gmm_SndSmSysInfoInd(MMCGMM_SGSN_RELEASE99_ONWARDS);

    /* 收到W模系统消息, 指示RABM当前系统模式, 并恢复RABM */
    NAS_GMM_SndRabmSysSrvChgInd(enCurRat,
                                VOS_FALSE,
                                VOS_FALSE,
                                VOS_TRUE);

    /* 停HO等待系统消息定时器 */
    Gmm_TimerStop(GMM_TIMER_HO_WAIT_SYSINFO);

    g_GmmGlobalCtrl.ucRaiChgRelFlg = GMM_FALSE;

    NAS_GMM_SuspendLlcForInterSys();

    g_GmmGlobalCtrl.ulGmmAttachFlg = GMM_FALSE;

    Gmm_RcvMmcSysInfoInd_CSPS_INFO(pSysInfoInd, &ucNetMod);

    /* 在迁到W模式下是，需要清除加密指配标志，因为在指配加密时需要使用此标志 */
    if(NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat)
    {
        gstGmmCasGlobalCtrl.ucGprsCipherAssign = VOS_FALSE;
        gstGmmCasGlobalCtrl.ucGprsCipher = VOS_FALSE;

        NAS_GMM_SndMmcCipherInfoInd();
    }
    /* 之前有异常释放,收到系统消息后清除这个标志 */
    if (RR_REL_CAUSE_ABORT_RR_NORMAL == g_GmmGlobalCtrl.ucRelCause)
    {
        g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_NORMAL_EVENT;
    }

    pRaiTemp = (GMM_RAI_STRU *)Gmm_MemMalloc(sizeof(GMM_RAI_STRU));
    if (VOS_NULL_PTR == pRaiTemp)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR,
            "Gmm_RcvMmcSysInfoInd:ERROR: Alloc mem fail.");
        return;
    }

    Gmm_RcvMmcSysInfoInd_Fill_pRaiTemp(pRaiTemp, pRcvMsg);

    /*对于收到系统消息从G重选到W的情况，需要清除掉原来链接存在标记
 */
    /*此处处理需要在小区被BAR的处理之前，因为小区被BAR会返回
 */
    if((NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat)
       &&((GMM_REGISTERED_PLMN_SEARCH == g_GmmGlobalCtrl.ucState)
          ||(GMM_DEREGISTERED_PLMN_SEARCH == g_GmmGlobalCtrl.ucState)))
    {
        g_GmmGlobalCtrl.ucSigConFlg = GMM_FALSE;

        NAS_MML_SetPsSigConnStatusFlg(VOS_FALSE);
        NAS_GMM_DeleteRandAndResInfoInPmmIdleMode();

        Gmm_SndRrmmNasInfoChangeReq(RRC_NAS_MASK_PTMSI_RAI);
#if (FEATURE_ON == FEATURE_LTE)
        /* L下丢网，搜网到GU后，需要判断如果有ISR激活后激活的pdp上下文，需要去激活ISR*/
        ulIsNeedDeactiveIsrFlg = NAS_GMM_IsNeedDeactiveIsr_InterSys(gstGmmSuspendCtrl.ucPreRat, enCurrNetType, MMC_SUSPEND_CAUSE_BUTT);

        if (VOS_TRUE == ulIsNeedDeactiveIsrFlg)
        {
            NAS_GMM_WriteTinInfoNvim(NAS_MML_TIN_TYPE_GUTI, pstRplmnCfgInfo->aucLastImsi);

            /* ISR去激活，需要更新pdp激活是在ISR激活前激活的 */
            NAS_MML_UpdateAllPsBearIsrFlg(NAS_MML_PS_BEARER_EXIST_BEFORE_ISR_ACT);
        }
#endif
    }

    /* 重选到PS被BARRED的小区,在网络模式I,并且T3312超时 */
    if (VOS_TRUE == NAS_MML_GetPsRestrictRegisterFlg())
    {
        /*  suspend过程中收到T3312超时，若PS barred,不会再进入suspend的处理，转换为expiredFlag */
        if (GMM_T3312_TIMEOUT == gstGmmSuspendCtrl.ucT3312State)
        {
            g_GmmRauCtrl.ucT3312ExpiredFlg = GMM_TRUE;
            gstGmmSuspendCtrl.ucT3312State = GMM_T3312_NOT_TIMEOUT;
        }

        if ((VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
          && (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg))
        {
            NAS_GMM_SndMmLuInitiation(GMMMM_T3312_EXPIRED);
        }
#if (FEATURE_ON == FEATURE_LTE)
        else if ( (VOS_TRUE == ulT3423StatuChgNeedRegFlg)
               && (GMM_NET_MODE_I == ucNetMod))
        {
            NAS_GMM_SndMmLuInitiation(GMMMM_T3412OrT3423_EXPIRED);
        }
        else
        {
        }
#endif
    }

    PS_MEM_SET(&stAttempUpdateRaiInfo, 0, sizeof(stAttempUpdateRaiInfo));
    pstAttemptUpdateRaiInfo = NAS_GMM_GetAttemptUpdateRaiInfo();

    NAS_GMM_ConvertPlmnIdToGmmFormat(&pstAttemptUpdateRaiInfo->stLai.stPlmnId, &stAttempUpdateRaiInfo.Lai.PlmnId);
    stAttempUpdateRaiInfo.Lai.aucLac[0] = pstAttemptUpdateRaiInfo->stLai.aucLac[0];
    stAttempUpdateRaiInfo.Lai.aucLac[1] = pstAttemptUpdateRaiInfo->stLai.aucLac[1];
    stAttempUpdateRaiInfo.ucRac         = pstAttemptUpdateRaiInfo->ucRac;

    stOldRai = g_GmmGlobalCtrl.SysInfo.Rai;

    if (VOS_TRUE == NAS_GMM_IsNeedUseAttemptUpdateRaiInfo(pRaiTemp, &stAttempUpdateRaiInfo))
    {
        stOldRai = stAttempUpdateRaiInfo;
    }

    Gmm_Get_Location_Change_info(pRaiTemp, &stOldRai, &ucLaiChgFlg, &ucRaiChgFlg, ucNetMod);

    ucSimPsRegStatus = NAS_MML_GetSimPsRegStatus();

    if ( (VOS_TRUE == ucSimPsRegStatus)
      && (MMC_GMM_NO_FORBIDDEN == pSysInfoInd->ulForbiddenMask) )
    {
        ucRst = Gmm_RcvMmcSysInfoInd_PS_BAR(ucLaiChgFlg);
        if(GMM_FALSE == ucRst)
        {
            g_GmmGlobalCtrl.SysInfo.ucForbMask = (VOS_UINT8)pSysInfoInd->ulForbiddenMask;   /* PLMN是否禁止                             */
            g_GmmGlobalCtrl.SysInfo.ucSysValidFlg = GMM_TRUE;                           /* 置系统信息有效标志                       */

            NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_ACCESS_BARRED);

            Gmm_MemFree(pRaiTemp);
            return;
        }
    }


    ulNewCellId = pSysInfoInd->ulCellId;

    g_GmmGlobalCtrl.SysInfo.ucCellChgFlg = GMM_FALSE;

    if (ulNewCellId != g_GmmGlobalCtrl.SysInfo.ulCellId)
    {
        g_GmmGlobalCtrl.SysInfo.ulCellId = ulNewCellId;
        g_GmmGlobalCtrl.SysInfo.ucCellChgFlg = GMM_TRUE;
    }




    if (MMC_GMM_SYS_MSK_PS_DRX ==(pSysInfoInd->ulMask & MMC_GMM_SYS_MSK_PS_DRX))
    {
        /* Modified by t00212959 for DCM定制需求和遗留问题, 2012-8-16, begin */
        /* 系统信息中带有DRX length信息             */
        if (NAS_MML_GetWSysInfoDrxLen() != (VOS_UINT8)pSysInfoInd->ulPsDrxLength)
        {                                                                       /* DRX LENGTH改变                           */
            ucDrxLengthChgFlg = GMM_TRUE;                                       /* 设置DRX length变化标志                   */
        }
        /* Modified by t00212959 for DCM定制需求和遗留问题, 2012-8-16, end */
    }

    if (GMM_TRUE == ucRaiChgFlg)
    {                                                                           /* RA改变或者DRX改变                        */
        ucRst = Gmm_RcvMmcSysInfoIndRelEstingLink();
        if(GMM_FALSE == ucRst)
        {
            NAS_GMM_SaveWasSysInfo(pSysInfoInd);
            Gmm_MemFree(pRaiTemp);
            return;
        }
    }

    ucRst = Gmm_RcvMmcSysInfoInd_ucNetModeChange_Handling(ucNetMod, pSysInfoInd, &ucLaiChgFlg, &ucRaiChgFlg);
    if(GMM_FALSE == ucRst)
    {
        Gmm_MemFree(pRaiTemp);
        return;
    }
    if (GMM_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {
        Gmm_MemCpy(&g_GmmGlobalCtrl.SysInfo.Rai, pRaiTemp, sizeof(GMM_RAI_STRU));   /* 存储系统信息中的RAI                      */
    }
    else
    {
        /*  suspend过程中收到T3312超时，若GPRS NOT SUPPORT,不会再进入suspend的处理，转换为expiredFlag */
        if (GMM_T3312_TIMEOUT == gstGmmSuspendCtrl.ucT3312State)
        {
            g_GmmRauCtrl.ucT3312ExpiredFlg = GMM_TRUE;
            gstGmmSuspendCtrl.ucT3312State = GMM_T3312_NOT_TIMEOUT;
        }
    }

    ucRst = Gmm_RcvMmcSysInfoInd_PreProcess_Handling(ucNetMod, ucRaiChgFlg, pSysInfoInd, &ucDrxLengthChgFlg);
    if(GMM_FALSE == ucRst)
    {
        Gmm_MemFree(pRaiTemp);
        return;
    }

    Gmm_RcvMmcSysInfoInd_State_Distribute(pRcvMsg,
                                          ucRaiChgFlg,
                                          ucDrxLengthChgFlg,
                                          ucLaiChgFlg);

    Gmm_MemFree(pRaiTemp);

    /* 链路释放控制: 收到系统消息，在处理完毕后，清除各流程的Retry标志 */
    g_GmmAttachCtrl.ucRetryAttachForRelCtrlFlg = VOS_FALSE;
    g_GmmDetachCtrl.ucRetryDetachForRelCtrlFlg = VOS_FALSE;
    g_GmmRauCtrl.ucRetryRauForRelCtrlFlg = VOS_FALSE;
    g_GmmServiceCtrl.ucRetrySrForRelCtrlFlg = VOS_FALSE;

    return;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_GMM_RcvMmcLteSysInfoInd
 功能描述  : 处理ID_MMC_GMM_LTE_SYS_INFO_IND原语
 输入参数  : MMC_GMM_LTE_SYS_INFO_IND_STRU      *pstLteSysInfo
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年4月26日
    作    者   : A00165503
    修改内容   : 新生成函数
  2.日    期   : 2011年7月13日
    作    者   : w00176964
    修改内容   : V7R1 PhaseII阶段调整，向RABM指示RAB是否需要重建
  3.日    期   : 2011年12月2日
    作    者   : s46746
    修改内容   : 从L异系统改变到GU后，没有指派加密密钥到GU接入层
  4.日    期   : 2012年10月25日
    作    者   : t00212959
    修改内容   : DTS2012102403382,GU到L后,清除释放原因值,否则又回到GU后会多做RAU
  5.日    期   : 2015年11月4日
    作    者   : c00318887
    修改内容   : DTS2015110401863: w丢网并rabm重建，到L后，背景搜失败
*****************************************************************************/
VOS_VOID NAS_GMM_RcvMmcLteSysInfoInd(
    MMC_GMM_LTE_SYS_INFO_IND_STRU      *pstLteSysInfo
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    /* 在迁到L模式下，需要清除加密指配标志，因为在指配加密时需要使用此标志 */
    gstGmmCasGlobalCtrl.ucGprsCipherAssign = VOS_FALSE;
    gstGmmCasGlobalCtrl.ucGprsCipher       = VOS_FALSE;

    gstGmmSuspendCtrl.ucGetLteSecContext   = VOS_FALSE;

    enCurRat = NAS_MML_GetCurrNetRatType();
    /* 收到L模系统消息, 指示RABM当前系统模式, 并挂起RABM */
    NAS_GMM_SndRabmSysSrvChgInd(enCurRat,
                                VOS_FALSE,
                                VOS_TRUE,
                                VOS_TRUE);

    /* 清除释放原因值 */
    g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_NORMAL_EVENT;
    
    g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;
    NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);
    g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;  

}


/*****************************************************************************
 函 数 名  : NAS_GMM_RcvMmcLmmStatusInd
 功能描述  : 处理MMCGMM_LMM_STATUS_IND原语
 输入参数  : MMCGMM_LMM_STATUS_IND_STRU      *pstLmmStatusInd
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期: 2012年03月02日
    作    者: l00130025
    修改内容: DTS2012022102014:L->G->L->G后，没有重新分配TLLI,导致G下RAU被网侧ImplicityDetached
*****************************************************************************/
VOS_VOID NAS_GMM_RcvMmcLmmStatusInd(
    MMCGMM_LMM_STATUS_IND_STRU      *pstLmmStatusInd
)
{
    switch (pstLmmStatusInd->ulConnState)
    {
    case MMC_LMM_CONN_ESTING:
    case MMC_LMM_CONNECTED_SIG:
    case MMC_LMM_CONNECTED_DATA:

        gstGmmCasGlobalCtrl.ucLastDataSender = NAS_MML_NET_RAT_TYPE_LTE;

        break;

    default:
        NAS_INFO_LOG1(WUEPS_PID_GMM, "pstLmmStatusInd->ulConnState =",pstLmmStatusInd->ulConnState);
        break;

    }

}

/*****************************************************************************
 函 数 名  : NAS_GMM_IsCsLaiChangeNeedRegister
 功能描述  : 网络模式I,CS域LAI改变是否需要发起联合注册
 输入参数  : ucNetMod - 网络模式
 输出参数  : 无
 返 回 值  : VOS_TRUE-需要
             VOS_FALSE-不需要
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期: 2012年07月18日
   作    者: z00161729
   修改内容: DTS2012071606177:W(LAI1)-L(TAI2/LAI2 ISR激活CS LAI改变)-W(LAI1网络模式I)需要
             发起联合rau

*****************************************************************************/
VOS_UINT32 NAS_GMM_IsCsLaiChangeNeedRegister(
    VOS_UINT8                           ucNetMod
)
{
    NAS_MML_MS_MODE_ENUM_UINT8          ucMsMode;
    VOS_UINT8                           ucCsSimRegStatus;
    VOS_UINT8                           ucCsRestrictRegFlg;
    VOS_UINT8                           ucCsAttachAllowFlg;

    ucMsMode           = NAS_MML_GetMsMode();
    ucCsSimRegStatus   = NAS_MML_GetSimCsRegStatus();
    ucCsRestrictRegFlg = NAS_MML_GetCsRestrictRegisterFlg();
    ucCsAttachAllowFlg = NAS_MML_GetCsAttachAllowFlg();

    if ((VOS_TRUE == NAS_MML_IsCsLaiChanged())
     && (GMM_NET_MODE_I == ucNetMod)
     && (NAS_MML_MS_MODE_PS_CS == ucMsMode)
     && (VOS_TRUE == ucCsSimRegStatus)
     && (VOS_FALSE == ucCsRestrictRegFlg)
     && (VOS_TRUE == ucCsAttachAllowFlg))
    {
        return GMM_TRUE;
    }

    return GMM_FALSE;
}

#endif


/*****************************************************************************
 函 数 名  : NAS_GMM_StopReadyTimer_DeregStat
 功能描述  : 检查Gmm状态,在Deregister状态,停止ReadyTimer,通知
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年12月14日
   作    者   : l00130025
   修改内容   : 问题单DTS2011091906272,Dereg状态下没有停止ReadyTimer

 2.日    期   : 2013年08月16日
   作    者   : l65478
   修改内容   : DTS2013092202614,G CCO到W失败回退到G,在G下通知了GAS进入了REDAY态
*****************************************************************************/
VOS_VOID NAS_GMM_StopReadyTimer_DeregStat(VOS_VOID)
{

    if ((GMM_TRUE == GMM_IsCasGsmMode())
     && (g_GmmGlobalCtrl.ucState >= GMM_DEREGISTERED_NORMAL_SERVICE)
     && (g_GmmGlobalCtrl.ucState <= GMM_DEREGISTERED_NO_IMSI))
    {
        Gmm_TimerStop(GMM_TIMER_T3314);

        gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_IDLE;
        NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
    }

}

/*****************************************************************************
 函 数 名  : NAS_GMM_SetIdleSrvState_DeregStats
 功能描述  : 检查Gmm状态,在Deregister状态,将服务状态修改为Idle,通知GAS
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2011年12月14日
   作    者   : l00130025
   修改内容   : 问题单DTS2011091906272,Dereg状态下没有进入到Idle态

*****************************************************************************/
VOS_VOID NAS_GMM_SetIdleSrvState_DeregStat(VOS_VOID)
{

    if ((GMM_TRUE == GMM_IsCasGsmMode())
     && (g_GmmGlobalCtrl.ucState >= GMM_DEREGISTERED_NORMAL_SERVICE)
     && (g_GmmGlobalCtrl.ucState <= GMM_DEREGISTERED_NO_IMSI))
    {
        if (GMM_AGB_GPRS_IDLE != gstGmmCasGlobalCtrl.GmmSrvState)
        {
             gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_IDLE;
             NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
        }
    }

}

/*******************************************************************************
Module   : Gmm_ComStaChg
Function : 迁入非INITIATED状态的公共处理
Input    : VOS_UINT8 ucState 迁入状态
Output   : 无
NOTE     : 无
Return   : 无
History  :
1. 张志勇  2003.12.18  新规作成
2. 日    期   : 2006年9月9日
   作    者   : sunxibo id:46746
   修改内容   : 根据问题单号：A32D05604
3. 日    期   : 2009年07月23日
   作    者   : L65478
   修改内容  : 问题单号:AT2D13173,GMM在收到系统信息后，给MMC发送了NO SERVICE，导致MMC启动了搜网定时器
4.日    期   : 2011年7月25日
  作    者   : h44270
  修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
5.日    期   : 2011年12月14日
  作    者   : l00130025
  修改内容   : 问题单DTS2011091906272,Dereg状态下没有进入到Idle态,没有停止ReadyTimer
6.日    期   : 2012年2月18日
  作    者   : w00181244
  修改内容   : 问题单DTS2012021305344,cgreg不上报问题，调整服务状态上报和注册状态上报的顺序
7.日    期   : 2012年3月28日
  作    者   : z00161729
  修改内容   : ISR修改
8.日    期   : 2012年9月07日
  作    者   : l00171473
  修改内容   : DTS2012081701006, 添加GMM状态的可维可测消息
9.日    期   : 2013年3月30日
  作    者   : l00167671
  修改内容   : 主动上报AT命令控制下移至C核
10.日    期   : 2013年05月08日
   作    者   : s46746
   修改内容   : SS FDN&Call Control项目，更新CSPS注册状态
11.日    期   : 2014年05月22日
   作    者   : W00242748
   修改内容   : DTS2014050900899:将GMM的处理状态通知给WAS
12.日    期   : 2014年6月13日
   作    者   : w00242748
   修改内容   : DSDS 新特性
*******************************************************************************/
VOS_VOID Gmm_ComStaChg(VOS_UINT8 ucState)
{

    /* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, begin */
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    enCurRat = NAS_MML_GetCurrNetRatType();
    if ( (NAS_MML_NET_RAT_TYPE_GSM == enCurRat)
      || (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat) )
    {
        NAS_GMM_NotifyRrmmChgNonDrxMode(g_GmmGlobalCtrl.ucState, ucState);
    }
    /* Added by l00167671 for 主动上报AT命令控制下移至C核, 2013-3-30, end */

#if(FEATURE_ON == FEATURE_DSDS)
    NAS_GMM_NotifySessionAccordingStateChg(g_GmmGlobalCtrl.ucState, ucState);
#endif

    g_GmmGlobalCtrl.ucState = ucState;                                          /* 保存要迁入的状态                         */

    NAS_GMM_LogGmmStateInfo(g_GmmGlobalCtrl.ucState);

    GMM_PrintState();

    Gmm_SndSmStatusInd();

    Gmm_SndSmsServiceStatusInd();

    if(VOS_TRUE == g_GmmGlobalCtrl.ucNeedChgServiceStatus)
    {
        Gmm_Com_ServiceStatus_Handle();                                         /* 通知MMC服务状态                          */
    }
    /* 3GPP 24.008 4.7.2.2章节描述：
      If the periodic routeing area update timer expires and the MS is in state
      GMM-REGISTERED.NO-CELL-AVAILABLE, the MS shall start the GERAN/UTRAN Deactivate
      ISR timer T3323. The MS shall initiate the routeing area updating procedure
      and stop the timer T3323 when the MS enters the state GMM-REGISTERED.NORMAL-SERVICE
      before timer T3323 expires. */

    if (GMM_REGISTERED_NORMAL_SERVICE == ucState)
    {
        Gmm_TimerStop(GMM_TIMER_T3323);
    }


    if (GMM_DEREGISTERED_NO_IMSI == g_GmmGlobalCtrl.ucState)
    {                                                                           /* 状态迁入GMM_DEREGISTERED_NO_IMSI         */
        if (VOS_TRUE == NAS_MML_GetSimPsRegStatus())
        {                                                                       /* sim卡有效                                */
            NAS_MML_SetSimPsRegStatus(VOS_FALSE);
            g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_IMSI;
        }
    }

    if (GMM_STATUS_DETACHED == g_MmSubLyrShare.GmmShare.ucAttachSta)
    {
        Gmm_TimerStop(GMM_TIMER_T3319);                                         /* 停止3319                                 */
    }


    NAS_GMM_StopReadyTimer_DeregStat();

    NAS_GMM_SetIdleSrvState_DeregStat();


}

/*******************************************************************************
  Module   : Gmm_RcvMmRegisterInitiation
  Function : 原语MMGMM_REGISTER_INITIATION的接收处理
  Input    : VOS_VOID *pMsg  消息指针
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2004.02.03  新规作成
*******************************************************************************/
VOS_VOID Gmm_RcvMmRegisterInitiation(
    VOS_VOID                           *pMsg                                    /* 指向消息的指针                           */
)
{
    if (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)
    {                                                                           /* A+I                                      */
        switch (g_GmmGlobalCtrl.ucState)
        {                                                                       /* 调用不同状态下的处理                     */
        case GMM_SERVICE_REQUEST_INITIATED:
            Gmm_RcvMmcRegisterInitiation_ServReqInit(pMsg);
            break;
        case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
        case GMM_DEREGISTERED_NORMAL_SERVICE:
            Gmm_RcvMmcRegisterInitiation_DeregAtmpToAtch();
            break;
        case GMM_REGISTERED_NORMAL_SERVICE:
        case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
        case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
            Gmm_RcvMmcRegisterInitiation_RegAtmpToUpdt();
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcRegisterInitiation:WARNING: g_GmmGlobalCtrl.ucState is Error");
            break;
        }
    }
    else
    {
    }
    return;
}

/*******************************************************************************
  Module   : Gmm_RcvMmcRegisterInitiation_ServReqInit
  Function : 在GMM_SERVICE_REQUEST_INITIATED状态下
             收到原语MMCGMM_REGISTER_INITIATION的处理
  Input    : VOS_VOID *pMsg  消息指针
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2004.02.03  新规作成
    3. 日    期   : 2010年11月24日
       作    者   : 王毛 00166186
       修改内容   : 根据问题单号DTS2010112205253,DEFAULT分支，对缓存的业务进行判断，避免内存泄漏

*******************************************************************************/
VOS_VOID Gmm_RcvMmcRegisterInitiation_ServReqInit(
                                              VOS_VOID *pMsg                        /* 指向消息的指针                           */
                                              )
{
    MMCGMM_REGISTER_INITIATION_STRU   *ptr;

    if ((GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
        && (GMM_RRC_RRMM_EST_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)))
    {                                                                           /* 无信令且正在建立信令连接                 */
        ptr = (MMCGMM_REGISTER_INITIATION_STRU *)Gmm_MemMalloc(sizeof(MMCGMM_REGISTER_INITIATION_STRU));
        if (VOS_NULL_PTR == ptr)
        {
              PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_RcvMmcRegisterInitiation_ServReqInit:ERROR: Memory is not allocated");
              return;
        }
        Gmm_MemCpy(ptr, pMsg, sizeof(MMCGMM_REGISTER_INITIATION_STRU));

        if (GMM_MSG_HOLD_FOR_RAU ==
            (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_RAU))
        {
            Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForRau);
            g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_RAU;
        }

        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForRau = (VOS_UINT32)ptr;              /* 存储消息首地址到 ulMsgAddrForRau         */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_RAU;           /* 置消息保留标志                           */

        return;
    }
    Gmm_TimerStop(GMM_TIMER_T3317);                                             /* 停T3317                                  */
    Gmm_TimerStop(GMM_TIMER_T3311);                                             /* 停T3311                                  */

    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* 停止T3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* 停止T3320                                */

    if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask
        & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
    {                                                                           /* 等待鉴权响应                             */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* 停保护定时器                             */
        g_GmmReqCnfMng.ucCnfMask
            &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;                          /* 清除原语等待标志                         */
    }
    g_GmmGlobalCtrl.ucSpecProcHold = g_GmmGlobalCtrl.ucSpecProc;                /* 保留被中断的SR流程                       */
    g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;                                   /* 设置follow on标志                        */
    NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

    Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);                   /* 进行RAU                                  */
    return;
}

/*******************************************************************************
  Module   : Gmm_RcvMmcRegisterInitiation_DeregAtmpToAtch
  Function : 在GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH状态下
             收到原语MMCGMM_REGISTER_INITIATION的处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2004.02.03  新规作成
    2.日    期   : 2008年7月23日
      作    者   : luojian id:107747
      修改内容   : 根据问题单：AT2D04627/AT2D04237
*******************************************************************************/
VOS_VOID Gmm_RcvMmcRegisterInitiation_DeregAtmpToAtch(VOS_VOID)
{
    Gmm_TimerStop(GMM_TIMER_T3311);                                             /* 停T3311                                  */
    Gmm_TimerStop(GMM_TIMER_T3302);                                             /* 停T3302                                  */
    /*
    3gpp 24.008 4.7.3 : The GPRS attach attempt counter shall be reset when the
    MS is in substate ATTEMPTING-TO-ATTACH and
        - expiry of timer T3302;
        - a new routing area is entered; or
        - an attach is triggered by CM sublayer requests.
    */
    if ( GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH == g_GmmGlobalCtrl.ucState )
    {
        g_GmmAttachCtrl.ucAttachAttmptCnt = 0;
    }
    Gmm_AttachInitiate(GMM_ATTACH_COMBINED);                                                       /* 触发attach                               */
    return;
}

/*******************************************************************************
  Module   : Gmm_RcvMmcRegisterInitiation_RegAtmpToUpdt
  Function : 在GMM_REGISTERED_NORMAL_SERVICE/ATTEMPTING_TO_UPDATE_MM/
             ATTEMPTING_TO_UPDATE状态下收到原语MMCGMM_REGISTER_INITIATION的处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2004.02.03  新规作成
*******************************************************************************/
VOS_VOID Gmm_RcvMmcRegisterInitiation_RegAtmpToUpdt(VOS_VOID)
{
    Gmm_TimerStop(GMM_TIMER_T3311);                                             /* 停T3311                                  */
    Gmm_TimerStop(GMM_TIMER_T3302);                                             /* 停T3302                                  */
    if (GMM_REGISTERED_ATTEMPTING_TO_UPDATE == g_GmmGlobalCtrl.ucState)
    {
        g_GmmRauCtrl.ucRauAttmptCnt = 0;                                        /* RAU attempt counter 清0                  */
    }

    Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);

    return;
}

/*******************************************************************************
  Module   : Gmm_ComUnrealProc
  Function : 假流程的类型判断处理
  Input    : 无
  Output   : 无
  NOTE     : 无
  Return   : VOS_UINT8   ucGmmAction   假流程类型
  History  :
    1. 张志勇  2004.03.16  新规作成
*******************************************************************************/
VOS_UINT8 Gmm_ComUnrealProc(VOS_VOID)
{
    VOS_UINT8       ucGmmAction = 0;                                                /* 定义局部变量                             */

    switch (g_GmmGlobalCtrl.ucState)
    {
    case GMM_REGISTERED_INITIATED:
    case GMM_DEREGISTERED_NO_CELL_AVAILABLE:
    case GMM_DEREGISTERED_NORMAL_SERVICE:
    case GMM_DEREGISTERED_LIMITED_SERVICE:
    case GMM_DEREGISTERED_ATTACH_NEEDED:
    case GMM_DEREGISTERED_PLMN_SEARCH:
    case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
        ucGmmAction = GMM_ATTACH_NORMAL;
        break;
    case GMM_DEREGISTERED_INITIATED:
    case GMM_REGISTERED_IMSI_DETACH_INITIATED:
    case GMM_ROUTING_AREA_UPDATING_INITIATED:
    case GMM_SERVICE_REQUEST_INITIATED:
    case GMM_REGISTERED_NORMAL_SERVICE:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
    case GMM_REGISTERED_UPDATE_NEEDED:
    case GMM_REGISTERED_LIMITED_SERVICE:
    case GMM_REGISTERED_PLMN_SEARCH:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
    case GMM_REGISTERED_NO_CELL_AVAILABLE:
        ucGmmAction = GMM_RAU_NORMAL;
        break;
    case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
        if (GMM_STATUS_DETACHED == g_MmSubLyrShare.GmmShare.ucAttachSta)
        {
            ucGmmAction = GMM_ATTACH_NORMAL;
        }
        else
        {
            ucGmmAction = GMM_RAU_NORMAL;
        }
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_ComUnrealProc:WARNING: g_GmmGlobalCtrl.ucState is Error");
        break;
    }
    return ucGmmAction;
}
/*******************************************************************************
  Module   : Gmm_ComGetFollowOnFlg
  Function : 获取Gmm的FollowOn标志
  Input    : 无
  Output   : FollowOn标志
  NOTE     : 无
  Return   : VOS_UINT8   Gmm的FollowOn标志
  History  :
        1.  日    期   : 2008年11月15日
            作    者   : l00130025
            修改内容   : 问题单号：AT2D06602,添加GSM模式下对MMC缓存消息的处理
*******************************************************************************/
VOS_UINT8 Gmm_ComGetFollowOnFlg(VOS_VOID)
{
    return  g_GmmGlobalCtrl.ucFollowOnFlg;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_ExistBufferService
 功能描述  : 判断gmm是否有缓存业务
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_TRUE   表示有缓存业务
             VOS_FALSE  表示没有缓存业务
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年12月17日
    作    者   : w00167002
    修改内容   : 新生成函数
  2.日    期   : 2011年2月25日
    作    者   : z00161729
    修改内容   : DTS2011021604439:cs only场景bg搜成功快速指定搜过程中发起数传失败

*****************************************************************************/
VOS_BOOL NAS_GMM_IsExistBufferService(VOS_VOID)
{
    if ((GMM_MSG_HOLD_FOR_SM == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SM))
     || (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg))
    {
        return  VOS_TRUE;
    }

    if (GMM_MSG_HOLD_FOR_PAGING == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_PAGING))
    {
        return  VOS_TRUE;
    }

    if (GMM_MSG_HOLD_FOR_SERVICE == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SERVICE))
    {
        return  VOS_TRUE;
    }

    if ( VOS_TRUE == NAS_GMM_IsFollowOnPend() )
    {
        return  VOS_TRUE;
    }

    /* 还需判断是否有数据 */

    return  VOS_FALSE;

}
/*******************************************************************************
  Module   : Gmm_ComForbiddenList
  Function : 对上报系统信息在forbidden列表的处理
  Input    : VOS_UINT32   ulForbiddenMask    所在forbidden列表的类型
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2004.03.17  新规作成
    2. 张志勇  2005.02.21  MM_MT_BUG_003对应
    3. 日    期   : 2008年12月15日
       作    者   : l00130025
       修改内容  : 问题单号:AT2D07408,Gmm状态判定

    4.日    期   : 2010年11月27日
      作    者   : zhoujun /40661
      修改内容   : 锁网白名单发现GMM假流程问题,删除GMM假流程
*******************************************************************************/
VOS_VOID Gmm_ComForbiddenList(
                          VOS_UINT32   ulForbiddenMask                               /* 所在forbidden列表的类型                  */
                          )
{
    if (GMM_RRC_RRMM_EST_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG))
    {                                                                           /* 等待信令建立                             */
        Gmm_TimerStop(GMM_TIMER_PROTECT_FOR_SIGNALING);
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_RRC_RRMM_EST_CNF_FLG;                  /* 清除原语等待标志                         */
    }

    if (GMM_STATUS_DETACHED == g_MmSubLyrShare.GmmShare.ucAttachSta)
    {
        Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                    /* 调用状态的公共处理                       */
    }
    else
    {
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                      /* 调用状态的公共处理                       */
    }

    g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;                          /* 设置真流程标志                           */
    g_GmmGlobalCtrl.ucSpecProc   = GMM_NULL_PROCEDURE;
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_ComForbiddenList:INFO: specific procedure ended");
    return;
}

/*******************************************************************************
  Module   : Gmm_ComNetModeChange_NotSupportGprs_Handling
  Function : Gmm_ComNetModeChange 降复杂度: 不支持GPRS的处理
  Input    : VOS_UINT8   ucNetMod
             VOS_UINT8   ucLaiChgFlg
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
  1.欧阳飞 2009.06.11  新规作成
  2.日    期   : 2011年7月14日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  3.日    期   : 2013年08月16日
    作    者   : l65478
    修改内容   : DTS2013081400197,T3314超时后,不能终止当前的注册过程
*******************************************************************************/
VOS_VOID Gmm_ComNetModeChange_NotSupportGprs_Handling(
                                                            VOS_UINT8 ucNetMod,
                                                            VOS_UINT8 ucLaiChgFlg)
{
    Gmm_TimerStop(GMM_TIMER_T3310);                                             /* 停T3310                                  */
    Gmm_TimerStop(GMM_TIMER_T3317);                                             /* 停T3317                                  */
    Gmm_TimerStop(GMM_TIMER_T3321);                                             /* 停T3321                                  */
    Gmm_TimerStop(GMM_TIMER_T3330);                                             /* 停T3330                                  */
    Gmm_TimerStop(GMM_TIMER_PROTECT);                                           /* 停保护Timer                              */
    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* 停止T3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* 停止T3320                                */
    g_GmmReqCnfMng.ucCnfMask = 0;

    g_GmmGlobalCtrl.SysInfo.ucNetMod = ucNetMod;                                /* 网络模式                                 */
    g_GmmGlobalCtrl.ucNetMod = ucNetMod;                                        /* 网络模式                                 */
    Gmm_ComCnfHandle();
    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                            /* 清当前流程                               */

    if (GMM_NULL == g_GmmGlobalCtrl.ucState)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_ComNetModeChange_NotSupportGprs_Handling:WARNING: g_GmmGlobalCtrl.ucState is GMM_NULL");
        return;
    }

    if ((0x10 == (g_GmmGlobalCtrl.ucState & 0xF0))
        || (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState))
    {
        Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                        /* 调用状态的公共处理                       */
    }

    else
    {
        Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                          /* 调用状态的公共处理                       */
    }

    if (GMM_NET_MODE_II == g_GmmGlobalCtrl.ucNetMod)
    {
#if (FEATURE_LTE == FEATURE_ON)
        if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
        {
            NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
        }
#endif
        Gmm_TimerStop(GMM_TIMER_T3312);                                         /* 停T3312                                  */
    }

    else
    {
        if (GMM_TRUE == ucLaiChgFlg)
        {
#if (FEATURE_LTE == FEATURE_ON)
            if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
            {
                NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
            }
#endif
            Gmm_TimerStop(GMM_TIMER_T3312);                                     /* 停T3312                                  */
        }

        else
        {
            if (GMM_DEREGISTERED_NO_CELL_AVAILABLE
                == g_GmmGlobalCtrl.ucState)
            {
#if (FEATURE_LTE == FEATURE_ON)
                if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
                {
                    NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
                }
#endif
                Gmm_TimerStop(GMM_TIMER_T3312);                                 /* 停T3312                                  */
                NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);          /* 通知MM进行LU                             */
            }

            else
            {
                if (GMM_REGISTERED_LIMITED_SERVICE == g_GmmGlobalCtrl.ucState)
                {
#if (FEATURE_LTE == FEATURE_ON)
                    if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
                    {
                        NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
                    }
#endif
                    Gmm_TimerStart(GMM_TIMER_T3312);                                /* 起T3312                                  */
                }
            }
        }
    }

    return;

}

/*******************************************************************************
  Module   : Gmm_ComNetModeChange_Netmode_I2II_Handling
  Function : Gmm_ComNetModeChange 降复杂度: 网络模式 I => II 的处理
  Input    : VOS_UINT8  ucNetMod,
             VOS_UINT8  ucRaiChgFlg
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 欧阳飞 2009.06.11  新规作成
*******************************************************************************/
VOS_VOID Gmm_ComNetModeChange_Netmode_I2II_Handling(
                                                  VOS_UINT8 ucNetMod,
                                                  VOS_UINT8 ucRaiChgFlg)
{

    g_GmmGlobalCtrl.SysInfo.ucNetMod = ucNetMod;                                /* 网络模式                                 */
    g_GmmGlobalCtrl.ucNetMod = ucNetMod;                                        /* 网络模式                                 */

    switch (g_GmmGlobalCtrl.ucState)
    {
    case GMM_REGISTERED_NORMAL_SERVICE:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
    case GMM_REGISTERED_LIMITED_SERVICE:
    case GMM_REGISTERED_UPDATE_NEEDED:
    case GMM_REGISTERED_NO_CELL_AVAILABLE:
    case GMM_REGISTERED_PLMN_SEARCH:
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        break;
    case GMM_REGISTERED_IMSI_DETACH_INITIATED:
        /*
        Imsi Detach过程中从网络模式I变到网络模式II，终止该Detach，认为
        此次Detach失败。因为变化到网络模式II后，PS域不可能发起Imsi Detach
        */
        Gmm_TimerStop(GMM_TIMER_T3321);                                         /* 停T3321                                  */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* 停保护Timer                              */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        break;
    case GMM_DEREGISTERED_INITIATED:
        Gmm_TimerStop(GMM_TIMER_T3321);                                         /* 停T3321                                  */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* 停保护Timer                              */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */
        /*
        Combined GPRS/IMSI Detach过程中网络模式由I变化到II，
        记录被中断的流程为Ps Detach，因为网络模式II下不能发起
        Combined GPRS/IMSI Detach.
        */
        g_GmmGlobalCtrl.ucSpecProcHold = GMM_DETACH_NORMAL;                     /* 保留被中断的SR流程                       */
        g_GmmGlobalCtrl.ucSpecProc     = GMM_NULL_PROCEDURE;                    /* 清除当前进行的specific过程               */
        g_GmmGlobalCtrl.ucFollowOnFlg  = GMM_TRUE;                              /* 设置follow on标志                        */
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        break;
    case GMM_SERVICE_REQUEST_INITIATED:
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */
        Gmm_TimerStop(GMM_TIMER_T3317);                                         /* 停T3317                                  */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* 停保护Timer                              */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */

        g_GmmGlobalCtrl.ucSpecProcHold = g_GmmGlobalCtrl.ucSpecProc;            /* 保留被中断的SR流程                       */
        g_GmmGlobalCtrl.ucSpecProc     = GMM_NULL_PROCEDURE;                    /* 清除当前进行的specific过程               */
        g_GmmGlobalCtrl.ucFollowOnFlg  = GMM_TRUE;                              /* 设置follow on标志                        */
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        break;
    case GMM_ROUTING_AREA_UPDATING_INITIATED:
        if (GMM_TRUE == ucRaiChgFlg)
        {
            Gmm_TimerStop(GMM_TIMER_T3330);                                     /* 停T3330                                  */
            Gmm_TimerStop(GMM_TIMER_T3318);                                     /* 停止T3318                                */
            Gmm_TimerStop(GMM_TIMER_T3320);                                     /* 停止T3320                                */

            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        }
        else
        {
            g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg = GMM_TRUE;
        }
        break;
    case GMM_REGISTERED_INITIATED:
        if (GMM_TRUE == ucRaiChgFlg)
        {
            Gmm_TimerStop(GMM_TIMER_T3310);                                     /* 停T3310                                  */
            Gmm_TimerStop(GMM_TIMER_T3318);                                     /* 停止T3318                                */
            Gmm_TimerStop(GMM_TIMER_T3320);                                     /* 停止T3320                                */

            Gmm_AttachInitiate(GMM_NULL_PROCEDURE);
        }
        else
        {
            g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg = GMM_TRUE;
        }
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_ComNetModeChange_Netmode_I2II_Handling:WARNING: g_GmmGlobalCtrl.ucState is Error");
        break;
    }

    return;
}

/*******************************************************************************
  Module   : Gmm_ComNetModeChange_Netmode_II2I_Handling
  Function : Gmm_ComNetModeChange 降复杂度: 网络模式 II => I 的处理
  Input    : VOS_UINT8  ucNetMod,
             VOS_UINT8  ucRaiChgFlg
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
  1.欧阳飞 2009.06.11  新规作成
  2.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  3.日    期   : 2013年7月19日
    作    者   : w00167002
    修改内容   : DTS2013071900239:W下网络模式I,联合注册PS only成功，CS失败原因
                    #17,网络模式由I--->II,此时不应发起联合ATTACH.
                    如果此时依然是网络模式I,但用户设置为PS ONLY,则也不用发起
                    联合ATTACH.
*******************************************************************************/
VOS_VOID Gmm_ComNetModeChange_Netmode_II2I_Handling(
                                                            VOS_UINT8 ucNetMod,
                                                            VOS_UINT8 ucRaiChgFlg)
{

    g_GmmGlobalCtrl.SysInfo.ucNetMod = ucNetMod;                                /* 网络模式                                 */
    g_GmmGlobalCtrl.ucNetMod = ucNetMod;                                        /* 网络模式                                 */

    switch (g_GmmGlobalCtrl.ucState)
    {
    case GMM_REGISTERED_NORMAL_SERVICE:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
    case GMM_REGISTERED_LIMITED_SERVICE:
    case GMM_REGISTERED_UPDATE_NEEDED:
    case GMM_REGISTERED_NO_CELL_AVAILABLE:
    case GMM_REGISTERED_PLMN_SEARCH:
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */



        /* 增加CS禁止注册时候，不发联合ATTACH */
        if ( VOS_FALSE == NAS_GMM_IsAllowedCombinedAttach_GmmRegisteredAttemptingToUpdateMm() )

        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        }
        else
        {
            Gmm_RoutingAreaUpdateInitiate(
                                        GMM_COMBINED_RALAU_WITH_IMSI_ATTACH
                                          );
        }
        break;
    case GMM_DEREGISTERED_INITIATED:
        Gmm_TimerStop(GMM_TIMER_T3321);                                         /* 停T3321                                  */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* 停保护Timer                              */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */

        g_GmmGlobalCtrl.ucSpecProcHold = g_GmmGlobalCtrl.ucSpecProc;            /* 保留被中断的SR流程                       */
        g_GmmGlobalCtrl.ucSpecProc     = GMM_NULL_PROCEDURE;                    /* 清除当前进行的specific过程               */
        g_GmmGlobalCtrl.ucFollowOnFlg  = GMM_TRUE;                              /* 设置follow on标志                        */
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        break;
    case GMM_SERVICE_REQUEST_INITIATED:
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */
        Gmm_TimerStop(GMM_TIMER_T3317);                                         /* 停T3317                                  */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* 停保护Timer                              */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */

        g_GmmGlobalCtrl.ucSpecProcHold = g_GmmGlobalCtrl.ucSpecProc;            /* 保留被中断的SR流程                       */
        g_GmmGlobalCtrl.ucSpecProc     = GMM_NULL_PROCEDURE;                    /* 清除当前进行的specific过程               */
        g_GmmGlobalCtrl.ucFollowOnFlg  = GMM_TRUE;                              /* 设置follow on标志                        */
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);

        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        break;
    case GMM_ROUTING_AREA_UPDATING_INITIATED:
        if (GMM_TRUE == ucRaiChgFlg)
        {
            Gmm_TimerStop(GMM_TIMER_T3330);                                     /* 停T3330                                  */
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        }
        else
        {
            g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg = GMM_TRUE;
        }
        break;
    case GMM_REGISTERED_INITIATED:
        if (GMM_TRUE == ucRaiChgFlg)
        {
            Gmm_TimerStop(GMM_TIMER_T3310);                                     /* 停T3310                                  */
            Gmm_AttachInitiate(GMM_NULL_PROCEDURE);
        }
        else
        {
            g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg = GMM_TRUE;
        }
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_ComNetModeChange_Netmode_II2I_Handling:WARNING: g_GmmGlobalCtrl.ucState is Error");
        break;
    }

    return;

}

/*******************************************************************************
  Module   : Gmm_ComNetModeChange_Fill_Rai
  Function : Gmm_ComNetModeChange 降复杂度: 给指针pRaiTemp赋值
  Input    : GMM_RAI_STRU                *pRaiTemp,
             MMCGMM_SYS_INFO_IND_STRU    *pSysInfoInd
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 欧阳飞 2009.06.11  新规作成
*******************************************************************************/
VOS_VOID Gmm_ComNetModeChange_Fill_Rai(
                          GMM_RAI_STRU                *pRaiTemp,
                          MMCGMM_SYS_INFO_IND_STRU    *pSysInfoInd
                          )
{
    Gmm_MemCpy(pRaiTemp, &g_GmmGlobalCtrl.SysInfo.Rai, sizeof(GMM_RAI_STRU));

    if (0 != pSysInfoInd->ulCnCommonSize)
    {                                                                           /* CnCommonInfo不为空                       */
        pRaiTemp->Lai.aucLac[0] = pSysInfoInd->aucCnCommonInfo[0];
        pRaiTemp->Lai.aucLac[1] = pSysInfoInd->aucCnCommonInfo[1];              /* LAC                                      */
    }

    if (MMC_GMM_SYS_MSK_PLMN == (pSysInfoInd->ulMask & MMC_GMM_SYS_MSK_PLMN))
    {
        pRaiTemp->Lai.PlmnId.aucMccDigit[0] =
            (VOS_UINT8)(pSysInfoInd->PlmnId.ulMcc & 0x0F);                      /* MCC Digit 1                              */
        pRaiTemp->Lai.PlmnId.aucMccDigit[1] =
            (VOS_UINT8)((pSysInfoInd->PlmnId.ulMcc >> 8) & 0x0F);               /* MCC Digit 2                              */
        pRaiTemp->Lai.PlmnId.aucMccDigit[2] =
            (VOS_UINT8)((pSysInfoInd->PlmnId.ulMcc >> 16) & 0x0F);              /* MCC Digit 3                              */
        pRaiTemp->Lai.PlmnId.aucMncDigit[0] =
            (VOS_UINT8)(pSysInfoInd->PlmnId.ulMnc & 0x0F);                      /* MNC Digit 1                              */
        pRaiTemp->Lai.PlmnId.aucMncDigit[1] =
            (VOS_UINT8)((pSysInfoInd->PlmnId.ulMnc >> 8) & 0x0F);               /* MNC Digit 2                              */
        pRaiTemp->Lai.PlmnId.aucMncDigit[2] =
            (VOS_UINT8)((pSysInfoInd->PlmnId.ulMnc >> 16) & 0x0F);              /* MNC Digit 3                              */
        pRaiTemp->Lai.PlmnId.ucMncCnt = 3;                                      /* MNC Degit count                          */

        if (GMM_PLMNID_MNC3_INVALID == pRaiTemp->Lai.PlmnId.aucMncDigit[2])
        {
            pRaiTemp->Lai.PlmnId.ucMncCnt = 2;                                  /* MNC Degit count                          */
        }
    }

    if (MMC_GMM_SYS_MSK_CSPS_INFO
        == (pSysInfoInd->ulMask & MMC_GMM_SYS_MSK_CSPS_INFO))
    {
          if (0 != pSysInfoInd->ulPsInfoSize)
          {
            pRaiTemp->ucRac = (VOS_UINT8)pSysInfoInd->aulPsInfo[0];             /* RAC                                      */
          }
    }

    return;

}

/*******************************************************************************
  Module   : Gmm_ComNetModeChange
  Function : 对于网络模式变换的公共处理
  Input    : VOS_VOID  *pMsg                    指向消息的指针
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2004.03.17  新规作成
    2.日    期   : 2008年7月18日
      作    者   : luojian 00107747
      修改内容   : 根据问题单号：AT2D03887
    3.日    期   : 2010年8月14日
      作    者   : 欧阳飞
      修改内容   : DTS2010081203473,变化小区，RAU失败后启动的是T3302，而不是T-
                   3311定时器
    4. 日    期   : 2012年7月17日
       作    者   : z00161729
       修改内容   : DTS2012071606177:W(LAI1)-L(TAI2/LAI2 ISR激活CS LAI改变)-W(LAI1网络模式I)需要
                    发起联合rau
     5.日    期   : 2012年8月14日
       作    者   : t00212959
       修改内容   : DCM定制需求和遗留问题
*******************************************************************************/
VOS_VOID Gmm_ComNetModeChange(VOS_VOID  *pMsg)
{
    MMCGMM_SYS_INFO_IND_STRU    *pSysInfoInd;                                   /* 定义MMCGMM_SYS_INFO_IND_STRU类型指针     */
    VOS_UINT8                    ucRaiChgFlg = GMM_FALSE;
    VOS_UINT8                    ucLaiChgFlg = GMM_FALSE;
    GMM_RAI_STRU                *pRaiTemp    = VOS_NULL_PTR;
    VOS_UINT8                    ucNetMod;

    g_GmmGlobalCtrl.SysInfo.ucNtType = NAS_MML_GetCurrNetRatType();

    pSysInfoInd = (MMCGMM_SYS_INFO_IND_STRU *)pMsg;

    pRaiTemp = (GMM_RAI_STRU *)Gmm_MemMalloc(sizeof(GMM_RAI_STRU));

    if (VOS_NULL_PTR == pRaiTemp)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_ComNetModeChange:ERROR: alloc rai temp memory fail.");
        return;
    }

    Gmm_ComNetModeChange_Fill_Rai(pRaiTemp, pSysInfoInd);

    if (0 == (VOS_UINT8)(pSysInfoInd->aulPsInfo[0] >> 8))
    {
        ucNetMod = GMM_NET_MODE_I;
    }
    else
    {
        ucNetMod = GMM_NET_MODE_II;
    }

    if (GMM_FALSE == Gmm_Com_CmpRai(pRaiTemp, &g_GmmGlobalCtrl.SysInfo.Rai, ucNetMod))
    {                                                                           /* 设置RAI是否变化标志                      */
        ucRaiChgFlg                 = GMM_TRUE;
        g_GmmRauCtrl.ucRauAttmptCnt = 0;
    }
    if (GMM_FALSE == Gmm_ComCmpLai(&(pRaiTemp->Lai)))
    {                                                                           /* 设置LAI是否变化标志                      */
        ucLaiChgFlg = GMM_TRUE;
    }

    Gmm_MemCpy(&g_GmmGlobalCtrl.SysInfo.Rai, pRaiTemp, sizeof(GMM_RAI_STRU));   /* 存储系统信息中的RAI                      */
    g_GmmGlobalCtrl.SysInfo.ucForbMask = (VOS_UINT8)pSysInfoInd->ulForbiddenMask;   /* PLMN是否禁止                             */
    g_GmmGlobalCtrl.SysInfo.ucSysValidFlg = GMM_TRUE;                           /* 置系统信息有效标志                       */

    /* Modified by t00212959 for DCM定制需求和遗留问题, 2012-8-16, begin */
    if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        NAS_MML_SetWSysInfoDrxLen((VOS_UINT8)pSysInfoInd->ulPsDrxLength);       /* 存储DRX LENGTH                           */
    }
    /* Modified by t00212959 for DCM定制需求和遗留问题, 2012-8-16, end */

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {
        Gmm_ComNetModeChange_NotSupportGprs_Handling(ucNetMod, ucLaiChgFlg);

        NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(NAS_MML_REG_FAIL_CAUSE_SERVING_CELL_DOMAIN_NOT_SUPPORT);

        Gmm_MemFree(pRaiTemp);
        return;
    }
    if (0 != g_GmmGlobalCtrl.SysInfo.ucForbMask)
    {
        Gmm_TimerStop(GMM_TIMER_T3310);                                         /* 停T3310                                  */
        Gmm_TimerStop(GMM_TIMER_T3317);                                         /* 停T3317                                  */
        Gmm_TimerStop(GMM_TIMER_T3321);                                         /* 停T3321                                  */
        Gmm_TimerStop(GMM_TIMER_T3330);                                         /* 停T3330                                  */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* 停保护Timer                              */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */
        g_GmmReqCnfMng.ucCnfMask = 0;

        g_GmmGlobalCtrl.SysInfo.ucNetMod = ucNetMod;                            /* 网络模式                                 */
        g_GmmGlobalCtrl.ucNetMod = ucNetMod;                                    /* 网络模式                                 */
        Gmm_ComCnfHandle();
        Gmm_ComForbiddenList(g_GmmGlobalCtrl.SysInfo.ucForbMask);
        NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(g_GmmGlobalCtrl.SysInfo.ucForbMask);
        Gmm_MemFree(pRaiTemp);
        return;
    }

    if (RR_REL_CAUSE_DIRECTED_SINGNALING_CONNECTION_RE_ESTABLISHMENT
        == g_GmmGlobalCtrl.ucRelCause)
    {
        g_GmmReqCnfMng.ucCnfMask = 0;
        g_GmmGlobalCtrl.SysInfo.ucNetMod = ucNetMod;                            /* 网络模式                                 */
        g_GmmGlobalCtrl.ucNetMod = ucNetMod;                                    /* 网络模式                                 */
        Gmm_TimerStop(GMM_TIMER_T3311);                                         /* 停T3311                                  */
        Gmm_TimerStop(GMM_TIMER_T3302);                                         /* 停T3302                                  */
        Gmm_RoutingAreaUpdateInitiateWithReEstRR();
        Gmm_MemFree(pRaiTemp);
        return;
    }

    if ((GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)
        && (GMM_NET_MODE_I == g_GmmGlobalCtrl.SysInfo.ucNetMod)
        && (GMM_NET_MODE_II == ucNetMod))
    {                                                                           /* 网络模式变更 I->II                       */
        Gmm_ComNetModeChange_Netmode_I2II_Handling(ucNetMod, ucRaiChgFlg);
    }

    if ((GMM_NET_MODE_II == g_GmmGlobalCtrl.ucNetMod)
        && (GMM_NET_MODE_II == g_GmmGlobalCtrl.SysInfo.ucNetMod)
        && (GMM_NET_MODE_I == ucNetMod))
    {                                                                           /* 网络模式变更                             */
        Gmm_ComNetModeChange_Netmode_II2I_Handling(ucNetMod, ucRaiChgFlg);
    }

    Gmm_MemFree(pRaiTemp);
}

/*******************************************************************************
  Module   : Gmm_ComNetModeChange
  Function : 对于网络模式变换的公共处理
  Input    : VOS_VOID  *pMsg                    指向消息的指针
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
  1.张志勇       2004.03.17  新规作成
  2.日    期   : 2010年8月14日
    作    者   : 欧阳飞
    修改内容   : DTS2010081203473,变化小区，RAU失败后启动的是T3302，而不是T-
                 3311定时器
  3.日    期   : 2011年7月14日
    作    者   : h44270
    修改内容   : V7R1 PhaseII阶段调整，注册结果简化
  4. 日    期   : 2012年7月17日
     作    者   : z00161729
     修改内容   : DTS2012071606177:W(LAI1)-L(TAI2/LAI2 ISR激活CS LAI改变)-W(LAI1网络模式I)需要
                  发起联合rau
  5.日    期   : 2012年8月14日
    作    者   : t00212959
    修改内容   : DCM定制需求和遗留问题
  6.日    期   : 2013年08月16日
    作    者   : l65478
    修改内容   : DTS2013081400197,T3314超时后,不能终止当前的注册过程
*******************************************************************************/
VOS_VOID Gmm_ComNetModeChangeGsm(VOS_VOID  *pMsg)
{
    MMCGMM_GSM_SYS_INFO_IND_ST         *pSysInfoInd;
    VOS_UINT8                           ucRaiChgFlg = GMM_FALSE;
    VOS_UINT8                           ucLaiChgFlg = GMM_FALSE;
    GMM_RAI_STRU                       *pRaiTemp  = VOS_NULL_PTR;
    VOS_UINT8                           ucNetMod;
    MMCGMM_GSM_SYS_INFO_IND_ST         *ptr;

    g_GmmGlobalCtrl.SysInfo.ucNtType = NAS_MML_GetCurrNetRatType();

    pSysInfoInd = (MMCGMM_GSM_SYS_INFO_IND_ST *)pMsg;
    if (((GMM_REGISTERED_IMSI_DETACH_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState))
        &&(0 != (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)))
    {                                                                           /* 正在建信令                               */
        ptr = (MMCGMM_GSM_SYS_INFO_IND_ST *)Gmm_MemMalloc(sizeof(MMCGMM_GSM_SYS_INFO_IND_ST));
        if (VOS_NULL_PTR == ptr)
        {
              PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_ComNetModeChangeGsm:ERROR: Memory is not allocated");
              return;
        }
        Gmm_MemCpy(ptr, pMsg, sizeof(MMCGMM_GSM_SYS_INFO_IND_ST));
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForRau = (VOS_UINT32)ptr;              /* 存储消息首地址到 ulMsgAddrForRau         */

        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_RAU;           /* 置消息保留标志                           */
        return;
    }
    if ((GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
        &&(0 != (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG)))
    {
        ptr = (MMCGMM_GSM_SYS_INFO_IND_ST *)Gmm_MemMalloc(sizeof(MMCGMM_GSM_SYS_INFO_IND_ST));
        if (VOS_NULL_PTR == ptr)
        {
              PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_ComNetModeChange:ERROR: Memory is not allocated");
              return;
        }
        Gmm_MemCpy(ptr, pMsg, sizeof(MMCGMM_GSM_SYS_INFO_IND_ST));
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForAttach = (VOS_UINT32)ptr;                /* 存储消息首地址到 ulMsgAddrForAttach      */

        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_ATTACH;        /* 置消息保留标志                           */
        return;
    }

    pRaiTemp = (GMM_RAI_STRU *)Gmm_MemMalloc(sizeof(GMM_RAI_STRU));
    if (VOS_NULL_PTR == pRaiTemp)
    {
          PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_ComNetModeChangeGsm:ERROR: Memory is not allocated");
          return;
    }
    Gmm_MemCpy(pRaiTemp, &g_GmmGlobalCtrl.SysInfo.Rai, sizeof(GMM_RAI_STRU));

    /* 填写RAC */
    pRaiTemp->ucRac = pSysInfoInd->ucRac;
    /* 填写LAC */
    pRaiTemp->Lai.aucLac[1] = (VOS_UINT8)pSysInfoInd->usLac;       /* LAC */
    pRaiTemp->Lai.aucLac[0] = (VOS_UINT8)(pSysInfoInd->usLac >> 8);
    /* 填写PLMN */
    pRaiTemp->Lai.PlmnId.aucMccDigit[0] =
        (VOS_UINT8)(pSysInfoInd->stPlmnId.ulMcc & 0x0F);             /* MCC Digit 1                              */
    pRaiTemp->Lai.PlmnId.aucMccDigit[1] =
        (VOS_UINT8)((pSysInfoInd->stPlmnId.ulMcc >> 8) & 0x0F);      /* MCC Digit 2                              */
    pRaiTemp->Lai.PlmnId.aucMccDigit[2] =
        (VOS_UINT8)((pSysInfoInd->stPlmnId.ulMcc >> 16) & 0x0F);     /* MCC Digit 3                              */
    pRaiTemp->Lai.PlmnId.aucMncDigit[0] =
        (VOS_UINT8)(pSysInfoInd->stPlmnId.ulMnc & 0x0F);             /* MNC Digit 1                              */
    pRaiTemp->Lai.PlmnId.aucMncDigit[1] =
        (VOS_UINT8)((pSysInfoInd->stPlmnId.ulMnc >> 8) & 0x0F);      /* MNC Digit 2                              */
    pRaiTemp->Lai.PlmnId.aucMncDigit[2] =
        (VOS_UINT8)((pSysInfoInd->stPlmnId.ulMnc >> 16) & 0x0F);     /* MNC Digit 3                              */
    pRaiTemp->Lai.PlmnId.ucMncCnt = 3;                       /* MNC Degit count                          */
    if (GMM_PLMNID_MNC3_INVALID == pRaiTemp->Lai.PlmnId.aucMncDigit[2])
    {
        pRaiTemp->Lai.PlmnId.ucMncCnt = 2;                  /* MNC Degit count                          */
    }

    if (GMM_FALSE == Gmm_Com_CmpRai(pRaiTemp, &g_GmmGlobalCtrl.SysInfo.Rai, pSysInfoInd->ucNetworkOperationMode))
    {                                                                           /* 设置RAI是否变化标志                      */
        ucRaiChgFlg                 = GMM_TRUE;
        g_GmmRauCtrl.ucRauAttmptCnt = 0;
    }
    if (GMM_FALSE == Gmm_ComCmpLai(&(pRaiTemp->Lai)))
    {                                                                           /* 设置LAI是否变化标志                      */
        ucLaiChgFlg = GMM_TRUE;
    }

    ucNetMod = pSysInfoInd->ucNetworkOperationMode;

    Gmm_MemCpy(&g_GmmGlobalCtrl.SysInfo.Rai, pRaiTemp, sizeof(GMM_RAI_STRU));   /* 存储系统信息中的RAI                      */
    g_GmmGlobalCtrl.SysInfo.ucForbMask = (VOS_UINT8)pSysInfoInd->ulForbiddenFlg;   /* PLMN是否禁止                             */
    g_GmmGlobalCtrl.SysInfo.ucSysValidFlg = GMM_TRUE;                           /* 置系统信息有效标志                       */

    /* Modified by t00212959 for DCM定制需求和遗留问题, 2012-8-16, begin */
    /* G下系统消息不带DRX LENGTH ，删除*/
    /* Modified by t00212959 for DCM定制需求和遗留问题, 2012-8-16, end */

    if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
    {
        Gmm_TimerStop(GMM_TIMER_T3310);                                         /* 停T3310                                  */
        Gmm_TimerStop(GMM_TIMER_T3317);                                         /* 停T3317                                  */
        Gmm_TimerStop(GMM_TIMER_T3321);                                         /* 停T3321                                  */
        Gmm_TimerStop(GMM_TIMER_T3330);                                         /* 停T3330                                  */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* 停保护Timer                              */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */
        g_GmmReqCnfMng.ucCnfMask = 0;

        g_GmmGlobalCtrl.SysInfo.ucNetMod   = ucNetMod;                          /* 网络模式                                 */
        g_GmmGlobalCtrl.ucNetMod   = ucNetMod;                                  /* 网络模式                                 */
        if (GMM_NULL == g_GmmGlobalCtrl.ucState)
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_ComNetModeChangeGsm:WARNING: g_GmmGlobalCtrl.ucState is GMM_NULL");
            Gmm_MemFree(pRaiTemp);
            return;
        }
        if ((0x10 == (g_GmmGlobalCtrl.ucState & 0xF0))
            || (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState))
        {
            Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                    /* 调用状态的公共处理                       */
        }
        else
        {
            Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);                      /* 调用状态的公共处理                       */
        }
        if (GMM_NET_MODE_II == g_GmmGlobalCtrl.ucNetMod)
        {
#if (FEATURE_LTE == FEATURE_ON)
            if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
            {
                NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
            }
#endif
            Gmm_TimerStop(GMM_TIMER_T3312);                                     /* 停T3312                                  */
        }
        else
        {
            if (GMM_TRUE == ucLaiChgFlg)
            {
#if (FEATURE_LTE == FEATURE_ON)
                if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
                {
                    NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
                }
#endif
                Gmm_TimerStop(GMM_TIMER_T3312);                                 /* 停T3312                                  */
            }
            else
            {
                if (GMM_DEREGISTERED_NO_CELL_AVAILABLE
                    == g_GmmGlobalCtrl.ucState)
                {
#if (FEATURE_LTE == FEATURE_ON)
                    if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
                    {
                        NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
                    }
#endif
                    Gmm_TimerStop(GMM_TIMER_T3312);                             /* 停T3312                                  */

                    NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);          /* 通知MM进行LU                             */
                }
                else
                {
                    if (GMM_REGISTERED_LIMITED_SERVICE == g_GmmGlobalCtrl.ucState)
                    {
#if (FEATURE_LTE == FEATURE_ON)
                        if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
                        {
                            NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
                        }
#endif
                        Gmm_TimerStart(GMM_TIMER_T3312);                            /* 起T3312                                  */
                    }
                }
            }
        }
        Gmm_MemFree(pRaiTemp);
        return;
    }
    if (0 != g_GmmGlobalCtrl.SysInfo.ucForbMask)
    {
        Gmm_TimerStop(GMM_TIMER_T3310);                                         /* 停T3310                                  */
        Gmm_TimerStop(GMM_TIMER_T3317);                                         /* 停T3317                                  */
        Gmm_TimerStop(GMM_TIMER_T3321);                                         /* 停T3321                                  */
        Gmm_TimerStop(GMM_TIMER_T3330);                                         /* 停T3330                                  */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* 停保护Timer                              */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* 停止T3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* 停止T3320                                */
        g_GmmReqCnfMng.ucCnfMask = 0;

        g_GmmGlobalCtrl.SysInfo.ucNetMod   = ucNetMod;                          /* 网络模式                                 */
        g_GmmGlobalCtrl.ucNetMod   = ucNetMod;                                  /* 网络模式                                 */
        Gmm_ComForbiddenList(g_GmmGlobalCtrl.SysInfo.ucForbMask);
        Gmm_MemFree(pRaiTemp);
        return;
    }

    if ((GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)
        && (GMM_NET_MODE_I == g_GmmGlobalCtrl.SysInfo.ucNetMod)
        && (GMM_NET_MODE_II == ucNetMod))
    {                                                                           /* 网络模式变更 I->II                       */
        g_GmmGlobalCtrl.SysInfo.ucNetMod   = ucNetMod;                          /* 网络模式                                 */
        g_GmmGlobalCtrl.ucNetMod   = ucNetMod;                                  /* 网络模式                                 */
        GMM_CasNetModeChangeByRau(GMM_NETMODE_CHG_I_II, ucRaiChgFlg);
        Gmm_MemFree(pRaiTemp);
            return;
    }

    if ((GMM_NET_MODE_II == g_GmmGlobalCtrl.ucNetMod)
        && (GMM_NET_MODE_II == g_GmmGlobalCtrl.SysInfo.ucNetMod)
        && (GMM_NET_MODE_I == ucNetMod))
    {                                                                           /* 网络模式变更                             */
        g_GmmGlobalCtrl.SysInfo.ucNetMod   = ucNetMod;                          /* 网络模式                                 */
        g_GmmGlobalCtrl.ucNetMod   = ucNetMod;                                  /* 网络模式                                 */

        GMM_CasNetModeChangeByRau(GMM_NETMODE_CHG_II_I, ucRaiChgFlg);
        Gmm_MemFree(pRaiTemp);
        return;
    }
    if ((GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)
      &&(GMM_NET_MODE_I == g_GmmGlobalCtrl.SysInfo.ucNetMod)
      &&(GMM_NET_MODE_III == ucNetMod))
    {/* 网络模式GSM I改变到网络模式GSM III */
        g_GmmGlobalCtrl.SysInfo.ucNetMod   = ucNetMod;                          /* 网络模式                                 */
        g_GmmGlobalCtrl.ucNetMod   = ucNetMod;                                  /* 网络模式                                 */
        GMM_CasNetModeChangeByRau(GMM_NETMODE_CHG_I_III, ucRaiChgFlg);
        Gmm_MemFree(pRaiTemp);
        return;
    }

    if ((GMM_NET_MODE_II == g_GmmGlobalCtrl.ucNetMod)
      &&(GMM_NET_MODE_II == g_GmmGlobalCtrl.SysInfo.ucNetMod)
      &&(GMM_NET_MODE_III == ucNetMod))
    {/* 网络模式GSM II改变到网络模式GSM III */
        g_GmmGlobalCtrl.SysInfo.ucNetMod   = ucNetMod;                          /* 网络模式                                 */
        g_GmmGlobalCtrl.ucNetMod   = ucNetMod;                                  /* 网络模式                                 */
        GMM_CasNetModeChangeByRau(GMM_NETMODE_CHG_II_III, ucRaiChgFlg);
        Gmm_MemFree(pRaiTemp);
        return;
    }

    if ((GMM_NET_MODE_III == g_GmmGlobalCtrl.ucNetMod)
      &&(GMM_NET_MODE_III == g_GmmGlobalCtrl.SysInfo.ucNetMod)
      &&(GMM_NET_MODE_I == ucNetMod))
    {/* 网络模式GSM III改变到网络模式GSM I */
        g_GmmGlobalCtrl.SysInfo.ucNetMod   = ucNetMod;                          /* 网络模式                                 */
        g_GmmGlobalCtrl.ucNetMod   = ucNetMod;                                  /* 网络模式                                 */
        GMM_CasNetModeChangeByRau(GMM_NETMODE_CHG_III_I, ucRaiChgFlg);
        Gmm_MemFree(pRaiTemp);
        return;
    }

    if ((GMM_NET_MODE_III == g_GmmGlobalCtrl.ucNetMod)
      &&(GMM_NET_MODE_III == g_GmmGlobalCtrl.SysInfo.ucNetMod)
      &&(GMM_NET_MODE_II == ucNetMod))
    {/* 网络模式GSM III改变到网络模式GSM II */
        g_GmmGlobalCtrl.SysInfo.ucNetMod   = ucNetMod;                          /* 网络模式                                 */
        g_GmmGlobalCtrl.ucNetMod   = ucNetMod;                                  /* 网络模式                                 */
        GMM_CasNetModeChangeByRau(GMM_NETMODE_CHG_III_II, ucRaiChgFlg);
        Gmm_MemFree(pRaiTemp);
        return;
    }
    Gmm_MemFree(pRaiTemp);
    return;
}


/*******************************************************************************
  Module   : Gmm_RcvMmcGmmModeChangeReq
  Function : 收到原语MMCGMM_MODE_CHANGE_REQ的处理
  Input    : VOS_VOID   *pMsg                     消息指针
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
  1.张志勇  2004.03.11  新规作成
  2.日    期   : 2006年9月23日
    作    者   : sunxibo id:46746
    修改内容   : 根据问题单号：A32D06377
  3.日    期   : 2007年1月10日
    作    者   : x51137
    修改内容   : A32D08279
  4.日    期   : 2009年01月20日
    作    者   : l00130025
    修改内容   : 问题单号:AT2D08378,当服务域改变时,MM/GMM没有对UE的mode进行改变;GMM在RAU过程中收到Detach请求时,直接返回,没有处理
  5.日    期   : 2011年7月25日
    作    者   : h44270
    修改内容   : V7R1 PHASEII 重构: 数据结构，全局变量初始化，魔鬼数字的调整
  6.日    期   : 2012年11月02日
    作    者   : l65478
    修改内容   : DTS2012110104636:在禁止PLMN上进行了ATTACH
*******************************************************************************/
VOS_VOID Gmm_RcvMmcGmmModeChangeReq(
    VOS_VOID                           *pMsg                                   /* 消息指针                                 */
)
{
    MMCGMM_MODE_CHANGE_REQ_STRU        *pModeChg;                                   /* 定义指针                                 */

    pModeChg = (MMCGMM_MODE_CHANGE_REQ_STRU *)pMsg;                             /* 初始化指针                               */

    switch (pModeChg->enMsMode)
    {                                                                           /* 用户模式                                 */
    case NAS_MML_MS_MODE_NULL:
        if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
        {                                                                       /* PS域注册被禁止                           */
            /*Gmm_ComStaChg(GMM_NULL);*/                                            /* 状态迁移到GMM_NULL                       */
            Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);
        }
        else
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcGmmModeChangeReq:WARNING: MMCGMM_MODE_CHANGE_REQ is invalid");
        }
        break;
    case NAS_MML_MS_MODE_PS_CS:
        if ( (GMM_DEREGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
            || (GMM_DEREGISTERED_LIMITED_SERVICE == g_GmmGlobalCtrl.ucState)
            || (GMM_NULL == g_GmmGlobalCtrl.ucState) )
        {                                                                       /* GMM状态为NULL                            */
            if (GMM_TRUE == g_GmmGlobalCtrl.SysInfo.ucSysValidFlg)
            {                                                                   /* MS当前驻留在小区上                       */
                if (VOS_FALSE == NAS_MML_GetSimPresentStatus())
                {                                                               /* SIM不存在                                */
                    Gmm_ComStaChg(GMM_DEREGISTERED_NO_IMSI);
                    NAS_MML_SetSimPsRegStatus(VOS_FALSE);
                }
                else if (VOS_FALSE == NAS_MML_GetSimPsRegStatus())
                {                                                               /* SIM无效                                  */
                    Gmm_ComStaChg(GMM_DEREGISTERED_NO_IMSI);
                }
                else
                {                                                               /* SIM有效                                  */
                    if (MMC_GMM_NO_FORBIDDEN == g_GmmGlobalCtrl.SysInfo.ucForbMask)
                    {
                        Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);             /* 状态迁移                                 */
                    }
                    else
                    {
                        Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);
                    }
                }
            }
            else
            {                                                                   /* 没有小区驻留                             */
                Gmm_ComStaChg(GMM_DEREGISTERED_NO_CELL_AVAILABLE);              /* 状态迁移                                 */
            }
        }
        break;
    case NAS_MML_MS_MODE_PS_ONLY:
        if ( (GMM_DEREGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
            || (GMM_DEREGISTERED_LIMITED_SERVICE == g_GmmGlobalCtrl.ucState)
            || (GMM_NULL == g_GmmGlobalCtrl.ucState) )
        {                                                                       /* GMM状态为NULL                            */
            if (GMM_TRUE == g_GmmGlobalCtrl.SysInfo.ucSysValidFlg)
            {                                                                   /* MS当前驻留在小区上                       */
                if (VOS_FALSE == NAS_MML_GetSimPresentStatus())
                {                                                               /* SIM不存在                                */
                    Gmm_ComStaChg(GMM_DEREGISTERED_NO_IMSI);
                    NAS_MML_SetSimPsRegStatus(VOS_FALSE);
                }
                else if (VOS_FALSE == NAS_MML_GetSimPsRegStatus())
                {                                                               /* SIM无效                                  */
                    Gmm_ComStaChg(GMM_DEREGISTERED_NO_IMSI);
                }
                else
                {                                                               /* SIM有效                                  */
                    if (MMC_GMM_NO_FORBIDDEN == g_GmmGlobalCtrl.SysInfo.ucForbMask)
                    {
                        Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);             /* 状态迁移                                 */
                    }
                    else
                    {
                        Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);
                    }

                }
            }
            else
            {                                                                   /* 没有小区驻留                             */
                Gmm_ComStaChg(GMM_DEREGISTERED_NO_CELL_AVAILABLE);              /* 状态迁移                                 */
            }
        }
        break;
    case NAS_MML_MS_MODE_CS_ONLY:
        if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
        {                                                                       /* PS域注册被禁止                           */
            /*Gmm_ComStaChg(GMM_NULL);*/                                            /* 状态迁移到GMM_NULL                       */
            if (MMC_GMM_NO_FORBIDDEN == g_GmmGlobalCtrl.SysInfo.ucForbMask)
            {
                Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);             /* 状态迁移                                 */
            }
            else
            {
                Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);
            }
        }
        else
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcGmmModeChangeReq:WARNING: MMCGMM_MODE_CHANGE_REQ is invalid");
        }
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvMmcGmmModeChangeReq:WARNING: The MsMode is Abnormal");
        break;
    }
    return;
}

/*******************************************************************************
  Module   : Gmm_GmmStatusMsgMake
  Function : GMM STATUS消息的作成
  Input    : VOS_UINT8    ucRejectCause                     错误原因
  Output   : 无
  NOTE     : 无
  Return   : NAS_MSG_STRU *pGmmStatus  指向NAS_MSG_STRU结构的指针
  History  :
    1. 张志勇  2004.04.14  新规作成
*******************************************************************************/
NAS_MSG_STRU *Gmm_GmmStatusMsgMake(
                                   VOS_UINT8    ucRejectCause                       /* 错误原因                                 */
                                   )
{
    NAS_MSG_STRU *pGmmStatus = VOS_NULL_PTR;                                            /* 指向NAS_MSG_STRU结构的指针变量           */

    pGmmStatus = (NAS_MSG_STRU *)Gmm_MemMalloc(sizeof(NAS_MSG_STRU));           /* 申请内存空间                             */
    if (VOS_NULL_PTR == pGmmStatus)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_GmmStatusMsgMake:ERROR: Alloc mem fail.");
        return pGmmStatus;
    }
    Gmm_MemSet(pGmmStatus, 0, sizeof(NAS_MSG_STRU));                            /* 内存空间清0                              */

    /* 填写空口消息参数             */
    pGmmStatus->ulNasMsgSize = GMM_MSG_LEN_GMM_STATUS;                          /* 填写空口消息长度                         */
    pGmmStatus->aucNasMsg[0] = GMM_PD_GMM;                                      /* 填写Protocol discriminator               */
    pGmmStatus->aucNasMsg[1] = GMM_MSG_GMM_STATUS;                              /* 填写Attach complete message identity     */
    pGmmStatus->aucNasMsg[2] = ucRejectCause;                                   /* 填写GMM cause                            */

    return pGmmStatus;
}

/*******************************************************************************
  Module   : Gmm_RcvTcTestReq
  Function : 收到TCGMM_TEST_REQ原语的处理
  Input    : VOS_VOID *pMsg
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2004.06.18  新规作成
    2. 日    期   : 2009年02月09日
       作    者   : l65478
       修改内容   : 根据问题单号：AT2D08422在启动TC时，T3317需要进行停止
    3. 日    期   : 2011年10月11日
       作    者   : l00171473
       修改内容   : V7R1 phase II, TC环回调整，维护PS TC业务存在标志
*******************************************************************************/
VOS_VOID Gmm_RcvTcTestReq(
    VOS_VOID                           *pMsg                                    /* 指向原语的指针                           */
)
{
    TCGMM_TEST_REQ_STRU                *pTcTestReq = VOS_NULL_PTR;              /* 定义原语类型指针                         */

    pTcTestReq = (TCGMM_TEST_REQ_STRU *)pMsg;                                   /* 强制类型转换                             */

    if (TC_RB_TEST_ACTIVE == pTcTestReq->ulMode)
    {                                                                           /* TC激活                                   */
        g_GmmGlobalCtrl.ucTcPreSta = g_GmmGlobalCtrl.ucState;

        GMM_CasFsmStateChangeTo(GMM_TC_ACTIVE);

        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvTcTestReq:NORMAL: STATUS IS GMM_TC_ACTIVE");

        Gmm_TimerStop(GMM_TIMER_T3317);                                             /* 停T3317                                  */
        Gmm_TimerPauseForTc(GMM_TIMER_ALL);                                     /* 挂起所有运行中的Timer                    */


        /* 设置PS TC业务存在，以控制MMC不进行搜网等活动。
           通过PS域建立TC环回时，不会设置PS业务存在，故需在此处设置PS TC业务存在。

           通过CS域建立TC环回，收到接入层的PAGING消息时，即会设置CS业务存在，故
           TC环回建立时不需再单独设置CS业务存在。 */

        NAS_MML_SetPsTcServiceFlg(VOS_TRUE);

    }
    else if (TC_RB_TEST_DEACTIVE == pTcTestReq->ulMode)
    {                                                                           /* TC去激活                                 */
        GMM_CasFsmStateChangeTo(g_GmmGlobalCtrl.ucTcPreSta);

        PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_RcvTcTestReq:NORMAL: STATUS IS ",g_GmmGlobalCtrl.ucState);

        Gmm_TimerResumeForTc(GMM_TIMER_ALL);                                    /* 恢复所有被挂起的Timer                    */


        /* 设置PS TC业务不存在 */
        NAS_MML_SetPsTcServiceFlg(VOS_FALSE);


    }
    else
    {
    }
}

/*******************************************************************************
  Module   : Gmm_RcvTcDataReq
  Function : 收到TCGMM_DATA_REQ原语的处理
  Input    : VOS_VOID *pMsg
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. 张志勇  2004.06.18  新规作成
*******************************************************************************/
VOS_VOID Gmm_RcvTcDataReq(
                      VOS_VOID *pMsg                                            /* 指向原语的指针                           */
                      )
{

    TCGMM_DATA_REQ_STRU           *pTcDataReq;                                  /* 定义原语类型指针                         */
    NAS_MSG_STRU                  *pTcMsg;

    if (GMM_TC_ACTIVE != g_GmmGlobalCtrl.ucState)
    {                                                                           /* 当前状态不是GMM_TC_ACTIVE                */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvTcDataReq:WARNING: TCGMM_DATA_REQ is unexpected");
        return;
    }
    pTcDataReq = (TCGMM_DATA_REQ_STRU *)pMsg;                                   /* 强制类型转换                             */

    pTcMsg = (NAS_MSG_STRU *)(&pTcDataReq->SendTcMsg);

    if (GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
    {
        Gmm_SndRrmmDataReqForCm(RRC_NAS_MSG_PRIORTY_HIGH, pTcMsg);              /* 发送 RRMM_DATA_REQ                       */
    }
    return;
}
/*******************************************************************************
Module   : Gmm_RcvGmmStatusMsg
Function : 收到GMM STATUS消息的处理
Input    : NAS_MSG_STRU *pMsg
Output   : 无
NOTE     : 无
Return   : 无
History  :
    1. 张志勇  2005.01.25  新规作成(for agent)
*******************************************************************************/
VOS_VOID Gmm_RcvGmmStatusMsg(
                                          NAS_MSG_FOR_PCLINT_STRU *pMsg
                                         )
{
    NAS_MSG_STRU        *pGmmStatus;

    if (GMM_MSG_LEN_GMM_STATUS > pMsg->ulNasMsgSize)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_RcvGmmStatusMsg:WARNING: The length of GMM STATUS is invalid");
        pGmmStatus = Gmm_GmmStatusMsgMake(NAS_MML_REG_FAIL_CAUSE_INVALID_MANDATORY_INF);

        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pGmmStatus);
        return;
    }

    return;
}
/* 废弃代码删除 */

/*******************************************************************************
  Module   : GRM_Inform_Gmm
  Function : GRM inform GMM that a data be send on user plan
  Input    : none
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. x51137  2006.07.21  Init
	2.日    期   : 2013年7月8日
      作    者   : z00161729
      修改内容  : DTS2013062008818:g下开机搜网小概率出现搜网状态机退出结果消息和退状态机状态迁状态时序有问题，
                    导致搜网状态机退出结果消息未处理，mmc状态异常
      3.日    期   : 2013年8月27日
      作    者   : l00208543
      修改内容  :  DTS2013082608600
*******************************************************************************/
VOS_VOID GRM_Inform_Gmm()
{
    LL_DATA_INFORM_MSG                 *pMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    if ((VOS_TRUE == NAS_MML_GetPsTbfStatusFlg())
     && (NAS_MML_NET_RAT_TYPE_GSM == gstGmmCasGlobalCtrl.ucLastDataSender))
    {
        /* 状态不对，过滤无需给gmm 发ID_LL_DATA_INFORM消息 */
        if ((g_GmmGlobalCtrl.ucState >= GMM_DEREGISTERED_NORMAL_SERVICE)
         && (g_GmmGlobalCtrl.ucState <= GMM_DEREGISTERED_NO_IMSI))
        {
            return;
        }

        /* ready timer定时器时长为0，过滤无需给gmm 发ID_LL_DATA_INFORM消息 */
        if (0 == gstGmmCasGlobalCtrl.ulReadyTimerValue)
        {
            return;
        }

        /* ready timer定时器时长为0xffffffff且已为ready态过滤，无需给gmm 发ID_LL_DATA_INFORM消息 */
        if ((0xffffffff == gstGmmCasGlobalCtrl.ulReadyTimerValue)
         && (GMM_AGB_GPRS_READY == gstGmmCasGlobalCtrl.GmmSrvState))
        {
            return;
        }

        /* TC状态t3314已启动且已为ready态过滤，无需给gmm 发ID_LL_DATA_INFORM消息 */
        if ((GMM_TC_ACTIVE == g_GmmGlobalCtrl.ucState)
         && (0 != (g_GmmTimerMng.ulTimerRunMask & (0x00000001 << GMM_TIMER_T3314)))
         && (GMM_AGB_GPRS_READY == gstGmmCasGlobalCtrl.GmmSrvState))
        {
            return;
        }

        /* 非TC状态t3314已启动且已为ready态过滤，无需给gmm 发ID_LL_DATA_INFORM消息 */
        if ((GMM_TC_ACTIVE != g_GmmGlobalCtrl.ucState)
         && (0 != (g_GmmTimerMng.ulTimerRunMask & (0x00000001 << GMM_TIMER_T3314)))
         && (VOS_NULL_PTR != g_GmmTimerMng.aTimerInf[GMM_TIMER_T3314].hTimer)
         && (GMM_AGB_GPRS_READY == gstGmmCasGlobalCtrl.GmmSrvState))
        {
            Gmm_TimerStop(GMM_TIMER_T3314);
            Gmm_TimerStart(GMM_TIMER_T3314);

            return;
        }
    }

    pMsg = (LL_DATA_INFORM_MSG *)PS_ALLOC_MSG(UEPS_PID_LL,
                  sizeof(LL_DATA_INFORM_MSG) - VOS_MSG_HEAD_LENGTH );

    if (VOS_NULL_PTR == pMsg)
    {
        GMM_LOG_ERR("GRM_Inform_Gmm():Error: Failed in VOS_AllocMsg()");
        return;
    }

    /* 消息头固定的参数 */
    pMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pMsg->ulSenderPid     = UEPS_PID_LL;
    pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMsg->ulReceiverPid   = WUEPS_PID_GMM;

    /* 填写消息发送参数 */
    pMsg->ulMsgName = ID_LL_DATA_INFORM;

    ulRet = PS_SEND_MSG(UEPS_PID_LL, pMsg);

    if (VOS_OK != ulRet)
    {
        /* 打印错误信息 */
        GMM_LOG_ERR("GRM_Inform_Gmm():Error: Failed in VOS_SendMsg()");
    }


    return;
}
/******************************************************************************
 * 函数名称 ： WuepsGmmPidInit
 * 功能描述 ： WUEPS GMM PID的初始化函数
 * 参数说明 ： 无
 * 备    注 ：
 * 返 回 值 ： VOS_UINT32 初始化结果：
 *             0  : 成功
 *             非0: 失败
 *
 * 变更历史 ：
 *           No.  姓名      变更                                    日   期
 *           1    张志勇    新建                                   2005.02.24
 *****************************************************************************/
VOS_UINT32 WuepsGmmPidInit (enum VOS_INIT_PHASE_DEFINE ip)
{
    switch (ip)
    {
    case VOS_IP_LOAD_CONFIG:
    case VOS_IP_FARMALLOC:
    case VOS_IP_INITIAL:
    case VOS_IP_ENROLLMENT:
    case VOS_IP_LOAD_DATA:
    case VOS_IP_FETCH_DATA:
    case VOS_IP_STARTUP:
    case VOS_IP_RIVAL:
    case VOS_IP_KICKOFF:
    case VOS_IP_STANDBY:
    case VOS_IP_BROADCAST_STATE:
    case VOS_IP_RESTART:
    case VOS_IP_BUTT:
        break;
    default:
        break;
    }

    return VOS_OK;
}

/*******************************************************************************
  Module   : Gmm_RcvLLCInform
  Function : 收到ID_LL_DATA_INFORM原语的处理
  Input    : VOS_VOID *pMsg
  Output   : 无
  NOTE     : 无
  Return   : 无
  History  :
    1. x51137  2006.07.21  Init
    2. 日    期   : 2009年04月06日
       作    者   : l00130025
       修改内容   : 根据问题单号：AT2D10790/AT2D10804，Gmm调用VOS_RestartRelTimer时，传入空指针，导致单板复位
     3.日    期   : 2010年12月23日
       作    者   : s46746
       修改内容   : DTS2010122305821:GPRS数传过程中高优先级定时器超时会发起指定搜网
     4.日    期   : 2011年12月14日
       作    者   : l00130025
       修改内容   : 问题单DTS2011091906272,Dereg状态下没有进入到Idle态,没有停止ReadyTimer
     5.日    期   : 2013年8月27日
       作    者   : l00208543
       修改内容  :  DTS2013082608600

     6.日    期   : 2014年9月5日
       作    者   : w00167002
       修改内容   : GCF.9.2.3.1.6 失败修改，在收到 GAS的PAGING IND时候不启动T3314，待
                    收到LL下发的数据才启动。
*******************************************************************************/
VOS_VOID Gmm_RcvLLCInform( VOS_VOID *pMsg )
{
    /* 设置GSM模式下PS域存在业务或者在进行注册 */
    NAS_MML_SetPsTbfStatusFlg(VOS_TRUE);

    gstGmmCasGlobalCtrl.ucLastDataSender = NAS_MML_NET_RAT_TYPE_GSM;


    if ((g_GmmGlobalCtrl.ucState >= GMM_DEREGISTERED_NORMAL_SERVICE)
     && (g_GmmGlobalCtrl.ucState <= GMM_DEREGISTERED_NO_IMSI))
    {
        return;
    }


    if (0 != gstGmmCasGlobalCtrl.ulReadyTimerValue)
    {
        /*A32D12829==>*/
        if (0xffffffff == gstGmmCasGlobalCtrl.ulReadyTimerValue)
        {
            if (GMM_AGB_GPRS_READY != gstGmmCasGlobalCtrl.GmmSrvState)
            {
                /* 下面启动T3314，停止T3312 */
                if ( GMM_TIMER_T3312_FLG == (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask) )
                {
                    Gmm_TimerStop(GMM_TIMER_T3312);

#if (FEATURE_LTE == FEATURE_ON)
                     NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
#endif
                }
                gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_READY;

#if (FEATURE_LTE == FEATURE_ON)
                if (NAS_GMM_TIMER_T3323_FLG == (NAS_GMM_TIMER_T3323_FLG & g_GmmTimerMng.ulTimerRunMask))
                {
                    Gmm_TimerStop(GMM_TIMER_T3323);
                }
#endif
                NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
            }
            return;
        }
        g_GmmTimerMng.aTimerInf[GMM_TIMER_T3314].ulTimerVal
            = gstGmmCasGlobalCtrl.ulReadyTimerValue;
        if (GMM_TC_ACTIVE == g_GmmGlobalCtrl.ucState)
        {
            if (0 == (g_GmmTimerMng.ulTimerRunMask & (0x00000001 << GMM_TIMER_T3314)))
            {
                Gmm_TimerStart(GMM_TIMER_T3314);
                Gmm_TimerPauseForTc(GMM_TIMER_T3314);                               /* 挂起T3312                                */
            }
        }
        else
        {
            if (0 != (g_GmmTimerMng.ulTimerRunMask & (0x00000001 << GMM_TIMER_T3314)))
            {                                                                           /* 该timer已经启动                          */
               if(VOS_NULL_PTR != g_GmmTimerMng.aTimerInf[GMM_TIMER_T3314].hTimer)
               {

                   Gmm_TimerStop(GMM_TIMER_T3314);
                   Gmm_TimerStart(GMM_TIMER_T3314);
               }
               else
               {
                   g_GmmTimerMng.ulTimerRunMask &= ~(VOS_UINT32)(0x00000001 << GMM_TIMER_T3314);         /* 清Timer的启动标志                        */
                   g_GmmTimerMng.ulTimerValMask |= GMM_TIMER_T3314_FLG;
                   Gmm_TimerStart(GMM_TIMER_T3314);
               }
            }
            else
            {
                /*<==A32D12829*/
                g_GmmTimerMng.ulTimerValMask |= GMM_TIMER_T3314_FLG;
                Gmm_TimerStart(GMM_TIMER_T3314);
            }

        }
        if (GMM_AGB_GPRS_READY != gstGmmCasGlobalCtrl.GmmSrvState)
        {

            /* 下面启动T3314，停止T3312 */
            if ( GMM_TIMER_T3312_FLG == (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask) )
            {
                Gmm_TimerStop(GMM_TIMER_T3312);

#if (FEATURE_LTE == FEATURE_ON)
                 NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
#endif
            }
            gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_READY;

#if (FEATURE_LTE == FEATURE_ON)
            if (NAS_GMM_TIMER_T3323_FLG == (NAS_GMM_TIMER_T3323_FLG & g_GmmTimerMng.ulTimerRunMask))
            {
                Gmm_TimerStop(GMM_TIMER_T3323);
            }
#endif
            NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
        }
    }

    return;
}

/*****************************************************************************
 Prototype      : GMM_PrintState
 Description    : 打印GMM状态
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-10-17
    Author      : Roger Leo
    Modification: created
*****************************************************************************/
VOS_VOID GMM_PrintState(VOS_VOID)
{
    switch (g_GmmGlobalCtrl.ucState)
    {
        case GMM_NULL:
            GMM_LOG_INFO("GMM State is GMM_NULL.");
            break;
        case GMM_REGISTERED_INITIATED:
            GMM_LOG_INFO("GMM State is GMM_REGISTERED_INITIATED.");
            break;
        case GMM_DEREGISTERED_INITIATED:
            GMM_LOG_INFO("GMM State is GMM_DEREGISTERED_INITIATED.");
            break;
        case GMM_ROUTING_AREA_UPDATING_INITIATED:
            GMM_LOG_INFO("GMM State is GMM_ROUTING_AREA_UPDATING_INITIATED.");
            break;
        case GMM_SERVICE_REQUEST_INITIATED:
            GMM_LOG_INFO("GMM State is GMM_SERVICE_REQUEST_INITIATED.");
            break;
        case GMM_TC_ACTIVE:
            GMM_LOG_INFO("GMM State is GMM_TC_ACTIVE.");
            break;
        case GMM_GPRS_SUSPENSION:
            GMM_LOG_INFO("GMM State is GMM_GPRS_SUSPENSION.");
            break;
        case GMM_DEREGISTERED_NORMAL_SERVICE:
            GMM_LOG_INFO("GMM State is GMM_DEREGISTERED_NORMAL_SERVICE.");
            break;
        case GMM_DEREGISTERED_LIMITED_SERVICE:
            GMM_LOG_INFO("GMM State is GMM_DEREGISTERED_LIMITED_SERVICE.");
            break;
        case GMM_DEREGISTERED_ATTACH_NEEDED:
            GMM_LOG_INFO("GMM State is GMM_DEREGISTERED_ATTACH_NEEDED.");
            break;
        case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
            GMM_LOG_INFO("GMM State is GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH.");
            break;
        case GMM_DEREGISTERED_NO_CELL_AVAILABLE:
            GMM_LOG_INFO("GMM State is GMM_DEREGISTERED_NO_CELL_AVAILABLE.");
            break;
        case GMM_DEREGISTERED_PLMN_SEARCH:
            GMM_LOG_INFO("GMM State is GMM_DEREGISTERED_PLMN_SEARCH.");
            break;
        case GMM_DEREGISTERED_NO_IMSI:
            GMM_LOG_INFO("GMM State is GMM_DEREGISTERED_NO_IMSI.");
            break;
        case GMM_REGISTERED_NORMAL_SERVICE:
            GMM_LOG_INFO("GMM State is GMM_REGISTERED_NORMAL_SERVICE.");
            break;
        case GMM_REGISTERED_LIMITED_SERVICE:
            GMM_LOG_INFO("GMM State is GMM_REGISTERED_LIMITED_SERVICE.");
            break;
        case GMM_REGISTERED_UPDATE_NEEDED:
            GMM_LOG_INFO("GMM State is GMM_REGISTERED_UPDATE_NEEDED.");
            break;
        case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
            GMM_LOG_INFO("GMM State is GMM_REGISTERED_ATTEMPTING_TO_UPDATE.");
            break;
        case GMM_REGISTERED_NO_CELL_AVAILABLE:
            GMM_LOG_INFO("GMM State is GMM_REGISTERED_NO_CELL_AVAILABLE.");
            break;
        case GMM_REGISTERED_PLMN_SEARCH:
            GMM_LOG_INFO("GMM State is GMM_REGISTERED_PLMN_SEARCH.");
            break;
        case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
            GMM_LOG_INFO("GMM State is GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM.");
            break;
        case GMM_REGISTERED_IMSI_DETACH_INITIATED:
            GMM_LOG_INFO("GMM State is GMM_REGISTERED_IMSI_DETACH_INITIATED.");
            break;
        case GMM_SUSPENDED_NORMAL_SERVICE:
            GMM_LOG_INFO("GMM State is GMM_SUSPENDED_NORMAL_SERVICE.");
            break;
        case GMM_SUSPENDED_GPRS_SUSPENSION:
            GMM_LOG_INFO("GMM State is GMM_SUSPENDED_GPRS_SUSPENSION.");
            break;
        case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
            GMM_LOG_INFO("GMM State is GMM_SUSPENDED_WAIT_FOR_SYSINFO.");
            break;
        default:
            GMM_LOG_WARN("GMM State is Error.");
            break;
    }
    return;
}

/*****************************************************************************
 Prototype      : GMM_GetCurServiceStatus
 Description    : 得到GMM的当前的服务状态
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2007-06-29
    Author      : l65478
    Modification: created
  2.Date        : 2007-08-08
    Author      : l65478
    Modification: modified for A32D12663
  3.日    期   : 2009年01月15日
    作    者   : l00130025
    修改内容   : 问题单号:AT2D07018,LAU或RAU过程中搜网和SYSCFG设置,发起底层释放链接的操作
  4.日    期   : 2009年03月21日
    作    者   : l00130025
    修改内容   : 问题单号:AT2D09534,异系统切换后的建链失败过程中关机，Gmm/MM对关机消息没有处理，后续设置AT^CPAM超时，无响应
*****************************************************************************/
VOS_UINT8 GMM_GetSignalingStatus(VOS_VOID)
{
    VOS_UINT8      ucResult = MMC_GMM_SIGNALING_STATUS_ABSENT;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    enCurRat = NAS_MML_GetCurrNetRatType();

    if (((GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_DEREGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_REGISTERED_IMSI_DETACH_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucState))
        && (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat))
    {
        ucResult = MMC_GMM_SIGNALING_STATUS_PRESENT;
    }

    PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO,
                    "GMM_GetCurServiceStatus: g_GmmGlobalCtrl.ucState is ",(VOS_INT32)g_GmmGlobalCtrl.ucState);
    PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO,
                    "GMM_GetCurServiceStatus: ucResult is ",(VOS_INT32)ucResult);

    return ucResult;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_IsRegisteredOrRegistering
 功能描述  : 判断当前GMM是否在注册过程中
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年7月16日
    作    者   : l65478
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_GMM_IsRegisteredOrRegistering(VOS_VOID)
{
    if (  (GMM_REGISTERED_NORMAL_SERVICE            == g_GmmGlobalCtrl.ucState)
        || (GMM_REGISTERED_INITIATED                == g_GmmGlobalCtrl.ucState)
        || (GMM_ROUTING_AREA_UPDATING_INITIATED     == g_GmmGlobalCtrl.ucState)
        || (GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH   == g_GmmGlobalCtrl.ucState)
        || (GMM_REGISTERED_ATTEMPTING_TO_UPDATE     == g_GmmGlobalCtrl.ucState)
        || (GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM  == g_GmmGlobalCtrl.ucState)
        || (GMM_SERVICE_REQUEST_INITIATED           == g_GmmGlobalCtrl.ucState))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 Prototype      : GMM_IsServiceExist
 Description    : Gmm当前是否有业务存在
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2008-11-17
    Author      : l00130025
    Modification: created
  2.日    期   : 2012年3月6日
    作    者   : z00161729
    修改内容   : 支持ISR特性修改
*****************************************************************************/
VOS_UINT32 GMM_IsServiceExist(VOS_VOID)
{
    VOS_UINT32      ulResult;

    if((VOS_TRUE == NAS_MML_IsPsBearerExist())
    || (GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucState))
    {
        ulResult = GMM_TRUE;
    }
    else
    {
        ulResult = GMM_FALSE;
    }
    return ulResult;
}

/*****************************************************************************
 Prototype      : NAS_GMM_GetSignalingStatusInGsm
 Description    : 当前是否可能存在TBF
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.日    期   : 2009年09月25日
    作    者   : l00130025
    修改内容   : 问题单号:AT2D14675,RAU/Attach过程中，list搜网失败
*****************************************************************************/
VOS_UINT32 NAS_GMM_GetSignalingStatusInGsm(VOS_VOID)
{
    VOS_UINT32      ulResult = VOS_FALSE;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    enCurRat = NAS_MML_GetCurrNetRatType();

    if (( ( VOS_TRUE == NAS_MML_GetPsTbfStatusFlg() )
        || (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_DEREGISTERED_INITIATED == g_GmmGlobalCtrl.ucState))
        && (NAS_MML_NET_RAT_TYPE_GSM == enCurRat))
    {
        ulResult = VOS_TRUE;
    }

    PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO,
                    "GMM_IsAttatchingOrRauInGsm: g_GmmGlobalCtrl.ucState is ",(VOS_INT32)g_GmmGlobalCtrl.ucState);
    PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO,
                    "GMM_IsAttatchingOrRauInGsm: ucResult is ",(VOS_INT32)ulResult);

    return ulResult;
}

/*****************************************************************************
 函 数 名  : Gmm_BufSmDataReqMsg
 功能描述  : GMM当前状态无法处理SM的消息时,进行缓存
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   : 2007年11月16日
    作    者   : hanlufeng 41410
    修改内容   : 新生成函数
  2.日    期   : 2007年12月18日
    作    者   : l00107747
    修改内容   : 根据问题单号：A32D13917,GMM处理SM缓存和当前不能处理需要缓存需要区别处理，
                 否则会造成内存问题
*****************************************************************************/
VOS_VOID Gmm_BufSmDataReqMsg( VOS_VOID *pMsg )
{
    GMMSM_DATA_REQ_STRU                 *ptr;

    /*申请缓存消息的内存*/
    if (4 > ((GMMSM_DATA_REQ_STRU *)pMsg)->SmMsg.ulNasMsgSize)
    {
        ptr = (GMMSM_DATA_REQ_STRU *)Gmm_MemMalloc(sizeof(GMMSM_DATA_REQ_STRU));
    }
    else
    {
        ptr = (GMMSM_DATA_REQ_STRU *)Gmm_MemMalloc((sizeof(GMMSM_DATA_REQ_STRU)
               + ((GMMSM_DATA_REQ_STRU *)pMsg)->SmMsg.ulNasMsgSize) - 4);
    }
    if (VOS_NULL_PTR == ptr)
    {
          PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING,
            "Gmm_RcvSmDataReq_RegNmlServ:WARNING: Gmm_MemMalloc fail !! ");
          return;
    }

    /*把消息暂存到申请的内存中*/
    if (4 > ((GMMSM_DATA_REQ_STRU *)pMsg)->SmMsg.ulNasMsgSize)
    {
        Gmm_MemCpy(ptr, pMsg, sizeof(GMMSM_DATA_REQ_STRU));
    }
    else
    {
        Gmm_MemCpy(ptr, pMsg, ((sizeof(GMMSM_DATA_REQ_STRU)
            + ((GMMSM_DATA_REQ_STRU *)pMsg)->SmMsg.ulNasMsgSize) - 4));
    }
    /*该方法只缓存最新的一条消息,若以前有缓存消息,则释放掉*/
    if (GMM_MSG_HOLD_FOR_SM ==
        (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SM))
    {
        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSm);
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SM;
    }
    NAS_NORMAL_LOG(WUEPS_PID_GMM, "Gmm_BufferSmDataReq(): Cache SM data Req");

    g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSm = (VOS_UINT32)ptr;
    g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_SM;

    return;
}
/*****************************************************************************
 函 数 名  : Gmm_ComCnfHandle
 功能描述  : Rau、Service流程失败之后，对缓存消息、Follow On标志、给上层回复
             响应的公共处理。
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
 修改历史      :
  1.日    期   :
    作    者   :
    修改内容   :
  2.日    期   : 2008年9月18日
    作    者   : ouyangfei 00132663
    修改内容   : 根据问题单号：AT2D05816，在GMM过程中，来自CM层的SMS请求应该被缓存，等GMM过程结束再发起。
  3.日    期   : 2011年07月13日
    作    者   : w00166186
    修改内容   : V7R1 PHASE II ATTACH/DETACH调整
  4.日    期   : 2012年09月12日
    作    者   : Z40661
    修改内容   : DTS2012081608654
  5.日    期   : 2013年8月7日
    作    者   : w00167002
    修改内容   : DTS2013080207367:在CS only时候，用户发起PDP激活，网络模式I时候，
                 会触发联合注册.用户发起PDP去激活，会导致PS域的去注册。收到网侧
                 的去注册成功后需要通知MM，否则MM当前在NORMAL SERVICE状态，不
                 触发T3212定时器的启动，长时间可能导致丢寻呼.
  6.日    期   : 2013年10月05日
    作    者   : l65478
    修改内容   : DTS2013092509860:GPRS detach过程被BG搜索终止后,GMM又自动发起了注册
*****************************************************************************/
VOS_VOID Gmm_ComCnfHandle(VOS_VOID)
{
    if (GMM_TRUE == g_GmmServiceCtrl.ucSmsFlg)
    {
        Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);                              /* 发送PMMSMS_ERROR_IND                     */
        g_GmmServiceCtrl.ucSmsFlg = GMM_FALSE;
    }

    if ((GMM_SERVICE_REQUEST_DATA_IDLE   == g_GmmGlobalCtrl.ucSpecProc)
        || (GMM_SERVICE_REQUEST_DATA_CONN == g_GmmGlobalCtrl.ucSpecProc))
    {                                                                           /* 当前流程为SR_DATA                        */
        if (RR_REL_CAUSE_RRC_SNW == g_GmmGlobalCtrl.ucRelCause)
        {
            g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_NORMAL_EVENT;
            Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_OOS);                 /* 通知RABM结果                             */
        }
        else
        {
            Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);                 /* 通知RABM结果                             */
        }
    }


    if ((GMM_WAIT_PS_DETACH == g_GmmGlobalCtrl.stDetachInfo.enDetachType)
     || (GMM_WAIT_CS_PS_DETACH == g_GmmGlobalCtrl.stDetachInfo.enDetachType))
    {

        NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);
        NAS_GMM_SndMmcMmDetachInfo();
    }

    if (GMM_MSG_HOLD_FOR_DETACH
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_DETACH))
    {                                                                           /* 如果有保留的DETACH原语                   */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_DETACH;       /* 清除保留标志                             */
        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach);                                                     /* 将保留buffer中所有的消息释放             */
    }

    if (GMM_MSG_HOLD_FOR_SMS
        ==(g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SMS))
    {
        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSMS);
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SMS;
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSMS = (VOS_UINT32)VOS_NULL;
    }

    if (GMM_MSG_HOLD_FOR_SM
        ==(g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SM))
    {
        NAS_NORMAL_LOG(WUEPS_PID_GMM, "Gmm_ComCnfHandle(): Clear cached SM data Req");

        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSm);
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SM;
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSm = (VOS_UINT32)VOS_NULL;
    }

    if (GMM_MSG_HOLD_FOR_SERVICE
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SERVICE))
    {
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SERVICE;      /* 清除缓存标志                             */
        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForService);
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForService = (VOS_UINT32)VOS_NULL;
        Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);                 /* 通知RABM结果                             */
    }

    if (GMM_TRUE == g_GmmGlobalCtrl.ucFollowOnFlg)
    {
        switch (g_GmmGlobalCtrl.ucSpecProcHold)
        {                                                                       /* 保留的specific流程                       */
        case GMM_SERVICE_REQUEST_DATA_IDLE:
        case GMM_SERVICE_REQUEST_DATA_CONN:
            Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);             /* 通知RABM结果                             */
            break;

        case GMM_DETACH_COMBINED:
        case GMM_DETACH_NORMAL:
        case GMM_DETACH_WITH_IMSI:
        case GMM_DETACH_NORMAL_NETMODE_CHANGE:
            /* 判断等待标志是否存在，如果存在则向MMC,MM发送DETACH信息 */
            if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
            {
                NAS_GMM_SndMmcMmDetachInfo();
            }

            if ( VOS_FALSE == NAS_MML_GetPsAttachAllowFlg() )
            {
                /* 收到网侧的去注册成功后需要通知MM，否则MM不启动T3212定时器 */
                NAS_GMM_SndMmGprsDetachComplete();
            }

            break;

        default:
            break;
        }
        g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;                    /* 清除保留流程                             */
        g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;                              /* 清除followon标志                         */
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

    }
}
/*****************************************************************************
 函 数 名  : Gmm_GetState
 功能描述  :
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年5月7日
    作    者   : luojian id:107747
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 Gmm_GetState()
{
    return g_GmmGlobalCtrl.ucState;
}
/*****************************************************************************
 函 数 名  : Gmm_GetGprsState
 功能描述  :
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2008年5月7日
    作    者   : luojian id:107747
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 Gmm_GetGprsState()
{
    VOS_UINT32  ulGprsState;
    if ( NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        if ((0x10 == (g_GmmGlobalCtrl.ucState&0xf0))
            ||(GMM_NULL == g_GmmGlobalCtrl.ucState))
        {
            ulGprsState = GMM_IU_PMM_DETACHED;
        }
        else if (GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
        {
            ulGprsState = GMM_IU_PMM_CONNECTED;
        }
        else
        {
            ulGprsState = GMM_IU_PMM_IDLE;
        }
    }
    else
    {
        ulGprsState = gstGmmCasGlobalCtrl.GmmSrvState;
    }
    return ulGprsState;
}

/***********************************************************************
 *  MODULE   : Gmm_FillNasMmInfo_NetMod
 *  FUNCTION : Gmm_FillNasMmInfo函数降复杂度: NetMod的处理
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
 1.  欧阳飞   2009.06.11  新版作成
 2.日    期   : 2015年9月17日
   作    者   : zwx247453
   修改内容   : Dallas寄存器按原语上报及BBP采数项目
 ************************************************************************/
VOS_VOID Gmm_FillNasMmInfo_NetMod(NAS_OM_MM_IND_STRU       *pMsg)
{
    /* Modified by zwx247453 for 寄存器上报, 2015-09-17, begin */
    if (GMM_NET_MODE_I == g_GmmGlobalCtrl.SysInfo.ucNetMod)
    {
        pMsg->enNetMode = NET_OPERATE_MODE_1;
    }
    else if (GMM_NET_MODE_II == g_GmmGlobalCtrl.SysInfo.ucNetMod)
    {
        pMsg->enNetMode = NET_OPERATE_MODE_2;
    }
    else if (GMM_NET_MODE_III == g_GmmGlobalCtrl.SysInfo.ucNetMod)
    {
        pMsg->enNetMode = NET_OPERATE_MODE_3;
    }
    else
    {
        pMsg->enNetMode = NET_OPERATE_MODE_BUTT;
    }
    /* Modified by zwx247453 for 寄存器上报, 2015-09-17, end */

    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_FillNasGmmState
 功能描述  : 填充Gmm State和Substate 信息
 输入参数  : 无
 输出参数  : 填充完成后的Gmm State和Substate 信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2010年3月4日
   作    者   : o00132663
   修改内容   : 新生成函数

 2.日    期   : 2011年7月23日
   作    者   : zhoujun 40661
   修改内容   : 修改名称符合编程规范

 3.日    期   : 2012年11月06日
   作    者   : l00198894
   修改内容   : Probe路测工具对接项目增加GMM服务状态填写

 4.日    期   : 2015年9月17日
   作    者   : zwx247453
   修改内容   : Dallas寄存器按原语上报及BBP采数项目

*****************************************************************************/
VOS_VOID NAS_GMM_FillNasGmmState(
    NAS_OM_MM_IND_STRU                 *pstMsg
)
{
    /* Modified by zwx247453 for 寄存器上报, 2015-09-17, begin */
    pstMsg->enGmmSubState = GMM_SUB_STATE_BUTT;

    switch (g_GmmGlobalCtrl.ucState)
    {
        case GMM_NULL:
            pstMsg->enGmmState = STATE_GMM_NULL;
            break;
        case GMM_REGISTERED_INITIATED:
            pstMsg->enGmmState = REGISTERED_INITIATED;
            break;
        case GMM_DEREGISTERED_INITIATED:
            pstMsg->enGmmState = DEREGISTERED_INITIATED;
            break;
        case GMM_ROUTING_AREA_UPDATING_INITIATED:
            pstMsg->enGmmState = ROUTING_AREA_UPDATING_INITIATED;
            break;
        case GMM_SERVICE_REQUEST_INITIATED:
            pstMsg->enGmmState = SERVICE_REQUEST_INITIATED;
            break;
        case GMM_TC_ACTIVE:
            pstMsg->enGmmState = TC_ACTIVE;
            break;
        case GMM_GPRS_SUSPENSION:
            pstMsg->enGmmState = GPRS_SUSPENSION;
            break;
        case GMM_DEREGISTERED_NORMAL_SERVICE:
            pstMsg->enGmmState = DEREGISTERED;
            pstMsg->enGmmSubState = DEREGISTERED_NORMAL_SERVICE;
            break;
        case GMM_DEREGISTERED_LIMITED_SERVICE:
            pstMsg->enGmmState = DEREGISTERED;
            pstMsg->enGmmSubState = DEREGISTERED_LIMITED_SERVICE;
            break;
        case GMM_DEREGISTERED_ATTACH_NEEDED:
            pstMsg->enGmmState = DEREGISTERED;
            pstMsg->enGmmSubState = DEREGISTERED_ATTACH_NEEDED;
            break;
        case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
            pstMsg->enGmmState = DEREGISTERED;
            pstMsg->enGmmSubState = DEREGISTERED_ATTEMPTING_TO_ATTACH;
            break;
        case GMM_DEREGISTERED_NO_CELL_AVAILABLE:
            pstMsg->enGmmState = DEREGISTERED;
            pstMsg->enGmmSubState = DEREGISTERED_NO_CELL_AVAILABLE;
            break;
        case GMM_DEREGISTERED_PLMN_SEARCH:
            pstMsg->enGmmState = DEREGISTERED;
            pstMsg->enGmmSubState = DEREGISTERED_PLMN_SEARCH;
            break;
        case GMM_DEREGISTERED_NO_IMSI:
            pstMsg->enGmmState = DEREGISTERED;
            pstMsg->enGmmSubState = DEREGISTERED_NO_IMSI;
            break;
        case GMM_REGISTERED_NORMAL_SERVICE:
            pstMsg->enGmmState = REGISTERED;
            pstMsg->enGmmSubState = REGISTERED_NORMAL_SERVICE;
            break;
        case GMM_REGISTERED_LIMITED_SERVICE:
            pstMsg->enGmmState = REGISTERED;
            pstMsg->enGmmSubState = REGISTERED_LIMITED_SERVICE;
            break;
        case GMM_REGISTERED_UPDATE_NEEDED:
            pstMsg->enGmmState = REGISTERED;
            pstMsg->enGmmSubState = REGISTERED_UPDATE_NEEDED;
            break;
        case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
            pstMsg->enGmmState = REGISTERED;
            pstMsg->enGmmSubState = REGISTERED_ATTEMPTING_TO_UPDATE;
            break;
        case GMM_REGISTERED_NO_CELL_AVAILABLE:
            pstMsg->enGmmState = REGISTERED;
            pstMsg->enGmmSubState = REGISTERED_NO_CELL_AVAILABLE;
            break;
        case GMM_REGISTERED_PLMN_SEARCH:
            pstMsg->enGmmState = REGISTERED;
            pstMsg->enGmmSubState = REGISTERED_PLMN_SEARCH;
            break;
        case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
            pstMsg->enGmmState = REGISTERED;
            pstMsg->enGmmSubState = REGISTERED_ATTEMPTING_TO_UPDATE_MM;
            break;
        case GMM_REGISTERED_IMSI_DETACH_INITIATED:
            pstMsg->enGmmState = REGISTERED;
            pstMsg->enGmmSubState = REGISTERED_IMSI_DETACH_INITIATED;
            break;
        case GMM_SUSPENDED_NORMAL_SERVICE:
            pstMsg->enGmmState = SUSPENDED_NORMAL_SERVICE;
            break;
        case GMM_SUSPENDED_GPRS_SUSPENSION:
            pstMsg->enGmmState = SUSPENDED_GPRS_SUSPENSION;
            break;
        case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
            pstMsg->enGmmState = SUSPENDED_WAIT_FOR_SYSINFO;
            break;
        default:
            pstMsg->enGmmState = GMM_STATE_BUTT;
            NAS_WARNING_LOG(WUEPS_PID_GMM, "Gmm_FillNasMmInfo:WARNING: g_GmmGlobalCtrl.ucState is Error");
            break;
    }
    /* Modified by zwx247453 for 寄存器上报, 2015-09-17, end */

    NAS_GMM_FillNasGmmGprsState(pstMsg);

    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_FillNasGmmGprsState
 功能描述  : 填充Gmm GPRS State信息
 输入参数  : 无
 输出参数  : 填充完成后的Gmm GPRS State信息
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年11月06日
   作    者   : l00198894
   修改内容   : Probe路测工具对接项目新增函数
*****************************************************************************/
VOS_VOID NAS_GMM_FillNasGmmGprsState(
    NAS_OM_MM_IND_STRU                 *pstMsg
)
{
    pstMsg->enGmmGprsState              = NAS_OM_GMM_GPRS_STATE_BUTT;

    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        switch(gstGmmCasGlobalCtrl.GmmSrvState)
        {
            case GMM_AGB_GPRS_IDLE:
                pstMsg->enGmmGprsState  = NAS_OM_GMM_GPRS_IDLE;
                break;
            case GMM_AGB_GPRS_STANDBY:
                pstMsg->enGmmGprsState  = NAS_OM_GMM_GPRS_STANDBY;
                break;
            case GMM_AGB_GPRS_READY:
                pstMsg->enGmmGprsState  = NAS_OM_GMM_GPRS_READY;
                break;
            default:
                break;
        }
    }

    return;
}

/***********************************************************************
 *  MODULE   : Gmm_FillNasMmInfo_ucUpdateSta
 *  FUNCTION : Gmm_FillNasMmInfo函数降复杂度: ucUpdateSta的处理
 *  INPUT    : VOS_VOID
 *  OUTPUT   : VOS_VOID
 *  RETURN   : VOS_UINT8 ucEventID
 *  NOTE     :
 *  HISTORY  :
 1.  欧阳飞   2009.06.11  新版作成
 2.日    期   : 2015年9月17日
   作    者   : zwx247453
   修改内容   : Dallas寄存器按原语上报及BBP采数项目
 ************************************************************************/
VOS_VOID Gmm_FillNasMmInfo_ucUpdateSta(NAS_OM_MM_IND_STRU     *pMsg)
{
    /* Modified by zwx247453 for 寄存器上报, 2015-09-17, begin */
    switch (NAS_MML_GetPsUpdateStatus())
    {
    case NAS_MML_ROUTING_UPDATE_STATUS_UPDATED:
        pMsg->enGmmUpdateStatus = UPDATE_STATUS_GU1;
        break;
    case NAS_MML_ROUTING_UPDATE_STATUS_NOT_UPDATED:
        pMsg->enGmmUpdateStatus = UPDATE_STATUS_GU2;
        break;
    case NAS_MML_ROUTING_UPDATE_STATUS_PLMN_NOT_ALLOWED:
    case NAS_MML_ROUTING_UPDATE_STATUS_ROUTING_AREA_NOT_ALLOWED:
        pMsg->enGmmUpdateStatus = UPDATE_STATUS_GU3;
        break;
    default:
        pMsg->enGmmUpdateStatus = GMM_UPDATE_STATUS_BUTT;
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING,
            "Gmm_FillNasMmInfo:WARNING: PsUpdateStatus is Error");
    }
    /* Modified by zwx247453 for 寄存器上报, 2015-09-17, end */

    return;
}

/*******************************************************************************
Module   : Gmm_FillNasMmInfo
Function :
Input    : 无
Output   : 无
NOTE     : 无
Return   : 无
History  :

  1.日    期   : 2008年9月01日
    作    者   :
    修改内容   :
*******************************************************************************/

/***********************************************************************
 *  MODULE   : Gmm_Com_ServiceStatus_Handle
 *  FUNCTION : 获得当前服务状态的公共处理
 *  INPUT    : 无
 *  OUTPUT   : 无
 *  RETURN   : VOS_UINT8 ucServiceSts
 *  NOTE     : 无
 *  HISTORY  :
 *     1.     2009.02.10  新版作成
       2.日    期   : 2009年03月12日
         作    者   : ouyangfei id:00132663
         修改内容   : 问题单AT2D09683,丢网时，GMM上报服务状态异常导致MMC没有发起搜网。
       3.日    期   : 2011年08月12日
         作    者   : z00161729
         修改内容   : V7R1 PHASE II ST修改
       4.日    期   : 2014年4月3日
         作    者   : s00261364
         修改内容   : V3R360_eCall项目
 ************************************************************************/
VOS_VOID Gmm_Com_ServiceStatus_Handle(VOS_VOID)
{
    switch (g_GmmGlobalCtrl.ucState)
    {         /* 以下状态需要上报服务状态    */
    case GMM_NULL:
    case GMM_REGISTERED_NORMAL_SERVICE:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
    case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
    case GMM_REGISTERED_LIMITED_SERVICE:
    case GMM_REGISTERED_UPDATE_NEEDED:
    case GMM_DEREGISTERED_NORMAL_SERVICE:
    case GMM_DEREGISTERED_LIMITED_SERVICE:
    case GMM_DEREGISTERED_ATTACH_NEEDED:
    case GMM_DEREGISTERED_NO_IMSI:
    case GMM_REGISTERED_NO_CELL_AVAILABLE:
    case GMM_DEREGISTERED_NO_CELL_AVAILABLE:
        /* Deleted by s00261364 for V3R360_eCall项目, 2014-4-11, begin */

        /* Deleted by s00261364 for V3R360_eCall项目, 2014-4-11, end */

        /* 判断等待标志是否存在，如果存在则发送MMCGMM_ATTACH CNF */
        if (GMM_WAIT_PS_ATTACH == (g_GmmGlobalCtrl.stAttachInfo.enAttachType
                                 & GMM_WAIT_PS_ATTACH))
        {
            NAS_GMM_SndMmcAttachCnf();
        }
        g_GmmGlobalCtrl.stAttachInfo.enAttachType = GMM_WAIT_NULL_ATTACH;
        break;

    default:
        break;
    }

    PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_Com_ServiceStatus_Handle:INFO: g_GmmGlobalCtrl.ucState is :", (VOS_INT32)g_GmmGlobalCtrl.ucState);

    return;
}
/***********************************************************************
 *  MODULE   : Gmm_ComServiceSts
 *  FUNCTION : 获得当前服务状态的公共处理
 *  INPUT    : 无
 *  OUTPUT   : 无
 *  RETURN   : VOS_UINT8 ucServiceSts
 *  NOTE     : 无
 *  HISTORY  :
 *     1.     2009.02.10  新版作成
       2.日    期   : 2009年03月12日
         作    者   : ouyangfei id:00132663
         修改内容   : 问题单AT2D09683,丢网时，GMM上报服务状态异常导致MMC没有发起搜网。
       3.日    期   : 2009年08月13日
         作    者   : l65478
         修改内容   : 问题单号：AT2D13662,3G下上报了out of coverage后总是会接着上报PS_Service
       4.日    期   : 2012年2月15日
         作    者   : w00166186
         修改内容   : CSFB&PPAC&ETWS&ISR 开发
 ************************************************************************/
NAS_MM_COM_SERVICE_STATUS_ENUM_UINT8 Gmm_ComServiceSts(VOS_VOID)
{
    NAS_MM_COM_SERVICE_STATUS_ENUM_UINT8       ucServiceSts = MM_COM_SRVST_NO_CHANGE;                     /* 定义临时变量                             */

    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* 根据状态置服务状态                       */
    case GMM_REGISTERED_NORMAL_SERVICE:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
        ucServiceSts = MM_COM_SRVST_NORMAL_SERVICE;
        break;

    case GMM_REGISTERED_UPDATE_NEEDED:
        ucServiceSts = NAS_GMM_GetRegUptNeededPsSrvStatus();
        break;

    case GMM_REGISTERED_LIMITED_SERVICE:
    case GMM_DEREGISTERED_LIMITED_SERVICE:
    case GMM_DEREGISTERED_ATTACH_NEEDED:
    case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
        ucServiceSts = MM_COM_SRVST_LIMITED_SERVICE;

        if (GMM_TRUE == g_GmmGlobalCtrl.ucLaNotAllowFlg)
        {
            ucServiceSts = MM_COM_SRVST_LIMITED_SERVICE_REGION;
            g_GmmGlobalCtrl.ucLaNotAllowFlg = GMM_FALSE;
        }
        break;

    case GMM_DEREGISTERED_NO_IMSI:
        ucServiceSts = MM_COM_SRVST_NO_IMSI;
        break;

    case GMM_NULL:
    case GMM_REGISTERED_NO_CELL_AVAILABLE:
    case GMM_DEREGISTERED_NO_CELL_AVAILABLE:
    case GMM_DEREGISTERED_NORMAL_SERVICE:
        ucServiceSts = MM_COM_SRVST_NO_SERVICE;
        break;
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
        if (5 == g_GmmRauCtrl.ucRauAttmptCnt)
        {
            ucServiceSts = MM_COM_SRVST_LIMITED_SERVICE;
        }
        else
        {
            PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_ComServiceSts:WARNING: Unexpected g_GmmGlobalCtrl.ucState is :", (VOS_INT32)g_GmmGlobalCtrl.ucState);
        }
        break;
    default:
        PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_ComServiceSts:WARNING: Unexpected g_GmmGlobalCtrl.ucState is :", (VOS_INT32)g_GmmGlobalCtrl.ucState);
        break;
    }

    PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_ComServiceSts:INFO: g_GmmGlobalCtrl.ucState is :", (VOS_INT32)g_GmmGlobalCtrl.ucState);

    return ucServiceSts;
}
/*******************************************************************************
 *  MODULE   : Gmm_GetServiceStatusForSms
 *  FUNCTION : 获得当前服务状态的公共处理
 *  INPUT    : 无
 *  OUTPUT   : 无
 *  RETURN   : VOS_UINT8 ucServiceSts
 *  NOTE     : 无
 *  HISTORY  :
 *     1.     2009.06.30    x00115505    新版作成
 ******************************************************************************/
VOS_UINT32 Gmm_GetServiceStatusForSms(VOS_VOID)
{
    GMM_STATE_TYPE_UINT8    ucState;
    VOS_UINT32              ulServiceSts = GMM_SMS_NO_SERVICE;                  /* 定义临时变量                             */

    if ((GMM_GPRS_SUSPENSION == g_GmmGlobalCtrl.ucState)
     || (GMM_SUSPENDED_GPRS_SUSPENSION == g_GmmGlobalCtrl.ucState)
     || (GMM_SUSPENDED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
     || (GMM_SUSPENDED_WAIT_FOR_SYSINFO == g_GmmGlobalCtrl.ucState))
    {
        ucState = gstGmmSuspendCtrl.ucPreState;
    }
    else
    {
        ucState = g_GmmGlobalCtrl.ucState;
    }

    switch (ucState)
    {                                                                           /* 根据状态置服务状态                       */
    case GMM_REGISTERED_NORMAL_SERVICE:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
    case GMM_SERVICE_REQUEST_INITIATED:
    case GMM_ROUTING_AREA_UPDATING_INITIATED:
    case GMM_REGISTERED_IMSI_DETACH_INITIATED:
        ulServiceSts = GMM_SMS_NORMAL_SERVICE;
        break;
    default:
        break;
    }

    return ulServiceSts;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_RcvInterRatHandoverInfoCnf
 功能描述  : 收到WRR的RRMM_INTER_RAT_HANDOVER_INFO_CNF消息处理
 输入参数  : VOS_VOID *pMsg - 消息指针
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年3月17日
    作    者   : o00132663
    修改内容   : 新生成函数
  2.日    期  : 2012年08月24日
    作    者  : m00217266
    修改内容  : 修改Gmm_SndSmEstablishCnf接口，添加原因值
  3.日    期   : 2014年6月13日
    作    者   : w00242748
    修改内容   : DSDS 新特性
  4.日    期   : 2014年7月18日
    作    者   : b00269685
    修改内容   : DSDS IV修改

*****************************************************************************/
VOS_VOID NAS_GMM_RcvInterRatHandoverInfoCnf(VOS_VOID *pMsg)
{
    RRMM_INTER_RAT_HANDOVER_INFO_CNF_STRU   *pRrmmInterRatInfoMsg = VOS_NULL_PTR;
    NAS_MSG_STRU                            *pSendNasMsg = VOS_NULL_PTR;

    pRrmmInterRatInfoMsg = (RRMM_INTER_RAT_HANDOVER_INFO_CNF_STRU *)pMsg;

    Gmm_TimerStop(GMM_TIMER_INTERRAT_HANDOVER_INFO_CNF);

    g_GmmInterRatInfoCtrl.ucInterRatCnfMsgRcvdFlg   = VOS_TRUE;
    g_GmmInterRatInfoCtrl.ucDataLen                 = (VOS_UINT8)pRrmmInterRatInfoMsg->usDataLen;

    if (0 == pRrmmInterRatInfoMsg->usDataLen)
    {
        /* WRR生成InterRatHandover失败 */
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_RcvInterRatHandoverInfoCnf: Msg Len is 0.");
    }
    else
    {
        /* InterRatHandoverInfo 信息保存到全局变量中 */
        PS_MEM_CPY(g_GmmInterRatInfoCtrl.aucData, pRrmmInterRatInfoMsg->aucData, g_GmmInterRatInfoCtrl.ucDataLen);
    }

    if (VOS_TRUE == g_GmmInterRatInfoCtrl.ucAttachCmpWaitInterRatCnfMsg)
    {
        if (VOS_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
        {
            /* ATTACH过程是由SM触发的,通知SM GMM注册成功,并清ucSmCnfFlg标志 */
            Gmm_SndSmEstablishCnf(GMM_SM_EST_SUCCESS, GMM_SM_CAUSE_SUCCESS);
            g_GmmAttachCtrl.ucSmCnfFlg = VOS_FALSE;
        }

        /* 回复网络Attach Complete 消息 */
        pSendNasMsg = Gmm_AttachCompleteMsgMake();

        if (VOS_NULL_PTR == pSendNasMsg)
        {
            NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_RcvInterRatHandoverInfoCnf: Make Attach Complete Msg Fail!");
            return;
        }
        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pSendNasMsg);

    }
    else if (VOS_TRUE == g_GmmInterRatInfoCtrl.ucRauCmpWaitInterRatCnfMsg)
    {
        /* 不需要等待RABM的回复消息，或者已经收到RABM的回复消息，进行RAU流程结束的相应处理 */
        if (   (VOS_FALSE == gstGmmCasGlobalCtrl.ucWaitRabmRauRspFlg)
            || (VOS_TRUE == gstGmmCasGlobalCtrl.ucRabmRauRspRcvdFlg))
        {
            NAS_GMM_RauCompleteHandling();
        }
    }
    else
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_RcvInterRatHandoverInfoCnf: Not Expected Msg Received.");
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_IsInHandoverProcedure
 功能描述  : 判断当前GMM是否在重选或者切换过程中，如果是，不能进行BG搜索
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年4月23日
    作    者   : l65478
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_GMM_IsInHandoverProcedure(VOS_VOID)
{
    VOS_UINT32      ulResult = VOS_FALSE;

    if ((GMM_SUSPENDED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
        || (GMM_SUSPENDED_WAIT_FOR_SYSINFO == g_GmmGlobalCtrl.ucState))
    {
        ulResult = VOS_TRUE;
    }

    PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO,
                    "GMM_IsInHandoverProcedure: g_GmmGlobalCtrl.ucState is ",(VOS_INT32)g_GmmGlobalCtrl.ucState);

    return ulResult;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_IsInRegisterProcedure
 功能描述  : 判断当前是否在注册过程中
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2009年10月10日
    作    者   : l65478
    修改内容   : 新生成函数
  1.日    期   : 2012年8月3日
    作    者   : z60575
    修改内容   : DTS2012080301265, 增加状态判断
*****************************************************************************/
VOS_UINT32  NAS_GMM_IsInRegisterProcedure(VOS_VOID)
{
    /* 判断当前是否在注册过程中 */
    if((GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_DEREGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
        || (GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucState))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}

/*****************************************************************************
 函 数 名  : NAS_GMM_CnfSmNotAttach
 功能描述  : GMM Deregister状态高优先级列表搜索时接收到SM建立请求，驻留后在-
             GMM无法进行Attach时回复SM模块
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年8月23日
    作    者   : s46746
    修改内容   : 新生成函数
   2.日    期  : 2012年08月24日
   作    者    : m00217266
   修改内容    : 添加enCause入参，上报注册成功或失败原因值

*****************************************************************************/
VOS_VOID NAS_GMM_CnfSmNotAttach(
    GMM_SM_CAUSE_ENUM_UINT16            enCause                                 /* 注册失败原因值 */
)
{
    if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
    {
        Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, enCause);
        g_GmmAttachCtrl.ucSmCnfFlg            = GMM_FALSE;
        g_GmmGlobalCtrl.ucFollowOnFlg         = GMM_FALSE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

        if ((NAS_MML_MS_MODE_CS_ONLY == NAS_MML_GetMsMode())
         && (VOS_FALSE == g_GmmGlobalCtrl.ucUserPsAttachFlag))
        {
            NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);
        }
    }
}

/*****************************************************************************
 函 数 名  : NAS_GMM_IsInRegOrDeregProcedure
 功能描述  : 判断GMM当前是否在注册或者去注册过程中
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_TRUE  : 在注册过程中
             VOS_FALSE : 不在注册过程中
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年6月28日
    作    者   : l65478
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_GMM_IsInRegOrDeregProcedure(VOS_VOID)
{
    VOS_UINT8      ucResult;

    ucResult = VOS_FALSE;

    /* WCDMA模式下，当在进行注册/去注册，或者在业务过程中时，认为存在连接；
      GSM模式下，当TBF存在时，认为存在连接 */
    if ( (GMM_REGISTERED_INITIATED             == g_GmmGlobalCtrl.ucState)
      || (GMM_DEREGISTERED_INITIATED           == g_GmmGlobalCtrl.ucState)
      || (GMM_ROUTING_AREA_UPDATING_INITIATED  == g_GmmGlobalCtrl.ucState)
      || (GMM_REGISTERED_IMSI_DETACH_INITIATED == g_GmmGlobalCtrl.ucState))
    {
        ucResult = VOS_TRUE;
    }

    NAS_NORMAL_LOG1(WUEPS_PID_GMM, "NAS_GMM_IsInRegisterOrDeregisterProcedure: g_GmmGlobalCtrl.ucState is ",(VOS_INT32)g_GmmGlobalCtrl.ucState);

    return ucResult;
}

/*****************************************************************************
 函 数 名  : NAS_Gmm_IsInServiceProcedure
 功能描述  : 判断GMM当前是否在发起业务的过程中
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2010年12月31日
    作    者   : l65478
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_Gmm_IsInServiceProcedure(VOS_VOID)
{
    if (GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucState)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_MMC_GetGmmRegStateForInterPLmnList
 功能描述  : 获取GMM的状态是否能发起列表搜网,主要用于MM发起列表搜网时进行判断
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_OK:可以发起列表搜网
              VOS_ERR:不能发起列表搜网
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年1月21日
    作    者   : zhoujun /40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_MMC_GetGmmRegStateForInterPLmnList( VOS_VOID )
{
    VOS_UINT8                           ucTimerId;
    VOS_BOOL                            bTimerRunning;
    VOS_UINT32                          ulTimerRunMask;

    /* 小区被bar的情况 */
    if ( ( GMM_DEREGISTERED_ATTACH_NEEDED        == g_GmmGlobalCtrl.ucState)
      || ( GMM_REGISTERED_UPDATE_NEEDED          == g_GmmGlobalCtrl.ucState))
    {
        return VOS_OK;
    }

    ucTimerId   = GMM_TIMER_T3302;

    ulTimerRunMask = g_GmmTimerMng.ulTimerRunMask;

    /*lint -e701*/
    if (0 != ( ulTimerRunMask & ( 0x00000001 << ucTimerId )))
    /*lint +e701*/
    {
        bTimerRunning = VOS_TRUE;
    }
    else
    {
        bTimerRunning = VOS_FALSE;
    }

    if ( VOS_FALSE == bTimerRunning )
    {
        return VOS_ERR;
    }


    if ( ( GMM_REGISTERED_ATTEMPTING_TO_UPDATE   == g_GmmGlobalCtrl.ucState)
      || ( GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH == g_GmmGlobalCtrl.ucState))
    {
        return VOS_OK;
    }

    if ( ( GMM_DEREGISTERED_NO_IMSI   == g_GmmGlobalCtrl.ucState)
      || ( GMM_REGISTERED_LIMITED_SERVICE == g_GmmGlobalCtrl.ucState))
    {
        return VOS_OK;
    }

    return VOS_ERR;
}


/*****************************************************************************
 函 数 名  : NAS_GMM_ConvertPlmnIdToMmcFormat
 功能描述  : 将GMM的PLMNID格式转换为MMC格式的
 输入参数  : pstGmmPlmnId:GMM的PLMN ID格式
 输出参数  : pstMmcPlmnId:MMC的PLMN ID格式
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月28日
    作    者   : zhoujun 40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_GMM_ConvertPlmnIdToMmcFormat(
    GMM_PLMN_ID_STRU                    *pstGmmPlmnId,
    NAS_MML_PLMN_ID_STRU                *pstMmcPlmnId
)
{

    pstMmcPlmnId->ulMcc = pstGmmPlmnId->aucMccDigit[0]
                        | (pstGmmPlmnId->aucMccDigit[1] << 8)
                        | (pstGmmPlmnId->aucMccDigit[2] << 16);

    pstMmcPlmnId->ulMnc = pstGmmPlmnId->aucMncDigit[0]
                        | (pstGmmPlmnId->aucMncDigit[1] << 8)
                        | (pstGmmPlmnId->aucMncDigit[2] << 16);
}
/*****************************************************************************
 函 数 名  : NAS_GMM_ConvertPlmnIdToMmcFormat
 功能描述  : 将GMM的PLMNID格式转换为MMC格式的
 输入参数  : pstMmcPlmnId:
 输出参数  : pstGmmPlmnId
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年7月28日
    作    者   : zhoujun 40661
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_GMM_ConvertPlmnIdToGmmFormat(
    NAS_MML_PLMN_ID_STRU                *pstMmcPlmnId,
    GMM_PLMN_ID_STRU                    *pstGmmPlmnId
)
{
    pstGmmPlmnId->aucMccDigit[0] =
        (VOS_UINT8)(pstMmcPlmnId->ulMcc & 0x0F);

    pstGmmPlmnId->aucMccDigit[1] =
        (VOS_UINT8)((pstMmcPlmnId->ulMcc >> 8) & 0x0F);

    pstGmmPlmnId->aucMccDigit[2] =
        (VOS_UINT8)((pstMmcPlmnId->ulMcc >> 16) & 0x0F);

    pstGmmPlmnId->ucMncCnt = 3;

    pstGmmPlmnId->aucMncDigit[0] =
        (VOS_UINT8)(pstMmcPlmnId->ulMnc & 0x0F);

    pstGmmPlmnId->aucMncDigit[1] =
        (VOS_UINT8)((pstMmcPlmnId->ulMnc >> 8) & 0x0F);

    pstGmmPlmnId->aucMncDigit[2] =
        (VOS_UINT8)((pstMmcPlmnId->ulMnc >> 16) & 0x0F);

    if (GMM_PLMNID_MNC3_INVALID == pstGmmPlmnId->aucMncDigit[2])
    {
        pstGmmPlmnId->ucMncCnt = 2;                                      /* MNC Degit count                          */
    }

}




/*****************************************************************************
 函 数 名  : NAS_GMM_IsDeregisterState
 功能描述  : 判断状态是否为GMM未注册状态
 输入参数  : ucState
 输出参数  : 无
 返 回 值  : VOS_TRUE:未注册
             VOS_FALSE:已注册
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年1月21日
    作    者   : s46746
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_GMM_IsDeregisterState(
    GMM_STATE_TYPE_UINT8                ucState
)
{
    if ((GMM_REGISTERED_INITIATED == ucState)
     || (GMM_DEREGISTERED_NORMAL_SERVICE == ucState)
     || (GMM_DEREGISTERED_LIMITED_SERVICE == ucState)
     || (GMM_DEREGISTERED_ATTACH_NEEDED == ucState)
     || (GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH == ucState)
     || (GMM_DEREGISTERED_NO_CELL_AVAILABLE == ucState)
     || (GMM_DEREGISTERED_PLMN_SEARCH == ucState)
     || (GMM_DEREGISTERED_NO_IMSI == ucState))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : Gmm_FreeBufferMsgWithoutSm
 功能描述  : 释放不包括SM消息的其它缓存消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年05月04日
    作    者   : l65478
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID Gmm_FreeBufferMsgWithoutSm(VOS_VOID)
{
    VOS_VOID                *pAddr;                                             /* 定义指针                                 */

    if (GMM_MSG_HOLD_FOR_PAGING
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_PAGING))
    {                                                                           /* 如果有保留的paging(IMSI)原语             */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_PAGING;       /* 清除保留标志                             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPaging;         /* 读取paging(IMSI)原语地址                 */
        Gmm_MemFree(pAddr);                                                     /* 将保留buffer中所有的消息释放             */
    }

    if (GMM_MSG_HOLD_FOR_RAU
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_RAU))
    {                                                                           /* 如果有保留的RAU原语                      */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_RAU;          /* 清除缓存标志                             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForRau;            /* 读取RAU原语地址                          */
        Gmm_MemFree(pAddr);                                                     /* 将保留buffer中所有的消息释放             */
    }

    if (GMM_MSG_HOLD_FOR_DETACH
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_DETACH))
    {                                                                           /* 如果有保留的DETACH原语                   */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_DETACH;       /* 清除保留标志                             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForDetach;         /* 读取detach原语地址                       */
        Gmm_MemFree(pAddr);                                                     /* 将保留buffer中所有的消息释放             */
    }

    if (GMM_MSG_HOLD_FOR_ATTACH
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_ATTACH))
    {                                                                           /* 如果有保留的attach原语                   */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_ATTACH;       /* 清除保留标志                             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForAttach;         /* 读取attach原语地址                       */
        Gmm_MemFree(pAddr);                                                     /* 将保留buffer中所有的消息释放             */
    }

    if (GMM_MSG_HOLD_FOR_SERVICE
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &GMM_MSG_HOLD_FOR_SERVICE))
    {                                                                           /* 如果有保留的ServiceRequest原语           */
        Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);                 /* 通知RABM结果                             */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SERVICE;      /* 清除保留标志                             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForService;        /* 读取ServiceRequest原语地址               */
        Gmm_MemFree(pAddr);                                                     /* 将保留buffer中所有的消息释放             */
    }

    if ((0x0 == g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk)
     && (GMM_FALSE == g_GmmGlobalCtrl.ucFollowOnFlg))
    {
        g_GmmGlobalCtrl.ucSpecProcHold = GMM_NULL_PROCEDURE;
        NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_ProcCsAcChgRegisterNetRaiChg
 功能描述  : NAS_GMM_RcvMmcWasAcInfoChgInd_RegUptNeeded收到WasAcInfoChgInd的处理,RAI改变的处理
 输入参数  : pstMsg - 消息内容
 输出参数  : 无
 返 回 值  : 消息类型
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期  : 2012年2月15日
    作    者  : w00166186
    修改内容  : 新生成函数
  2.日    期   : 2013年2月4日
    作    者   : w00176964
    修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
*****************************************************************************/
VOS_VOID NAS_GMM_ProcPsAcChgRegisterNetRaiChg()
{
    g_GmmRauCtrl.ucT3312ExpiredFlg    = GMM_FALSE;                          /* 清除T3312溢出标记                        */

    if ((VOS_TRUE != NAS_MML_GetCsAttachAllowFlg())
     || (GMM_NET_MODE_I != g_GmmGlobalCtrl.ucNetMod))
    {                                                                       /* 非A+I                                    */
        Gmm_RoutingAreaUpdateInitiate(GMM_RA_UPDATING);
    }
    else
    {
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);           /* 调用RAU过程                              */
    }
}
/*****************************************************************************
 函 数 名  : NAS_GMM_ProcCsAcChgRegisterNetRaiNotChgT3312Expire
 功能描述  : NAS_GMM_RcvMmcWasAcInfoChgInd_RegUptNeeded收到WasAcInfoChgInd的处理,RAI改变的处理
 输入参数  : pstMsg - 消息内容
 输出参数  : 无
 返 回 值  : 消息类型
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期  : 2012年2月15日
    作    者  : w00166186
    修改内容 : 新生成函数
  2.日    期   : 2013年2月4日
    作    者   : w00176964
    修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
*****************************************************************************/
VOS_VOID NAS_GMM_ProcPsAcChgRegisterNetRaiNotChgT3312Expire()
{
    if ((VOS_TRUE != NAS_MML_GetCsAttachAllowFlg())
     || (GMM_NET_MODE_I != g_GmmGlobalCtrl.ucNetMod))
    {                                                                   /* 非A+I                                    */
        Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
    }
    else if ((VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
          || (GMM_TRUE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg))
    {
        Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
    }
    else
    {                                                                   /* A+I                                      */
        Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);       /* 调用RAU过程combined RAU with IMSI attach */
    }
}

/*****************************************************************************
 函 数 名  : NAS_GMM_ProcCsAcChgRegisterNetRaiNotChgT3312NotExpire
 功能描述  : NAS_GMM_RcvMmcWasAcInfoChgInd_RegUptNeeded收到WasAcInfoChgInd的处理,RAI不改变的处理
 输入参数  : pstMsg - 消息内容
 输出参数  : 无
 返 回 值  : 消息类型
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期  : 2012年2月15日
    作    者  : w00166186
    修改内容 : 新生成函数
  2.日    期  : 2012年08月24日
    作    者  : m00217266
    修改内容  : 修改Gmm_SndSmEstablishCnf接口，添加原因值
  3.日    期   : 2013年2月4日
    作    者   : w00176964
    修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
*****************************************************************************/
VOS_VOID NAS_GMM_ProcPsAcChgRegisterNetRaiNotChgT3312NotExpire()
{
    VOS_UINT8                           ucCsAttachAllow;

    ucCsAttachAllow = NAS_MML_GetCsAttachAllowFlg();

    /* 当前PS更新状态为U1 */
    if (NAS_MML_ROUTING_UPDATE_STATUS_UPDATED == NAS_MML_GetPsUpdateStatus())
    {
        /* 非网络模式I的处理 */
        if ((VOS_TRUE == NAS_MML_GetCsRestrictRegisterFlg())
         || (VOS_TRUE != ucCsAttachAllow)
         || (GMM_NET_MODE_I != g_GmmGlobalCtrl.ucNetMod))
        {
            Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);
            GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_SUCCESS);
        }
        else
        {
            /* CS更新状态为U1，且Gs连接存在 */
            if (  (NAS_MML_LOCATION_UPDATE_STATUS_UPDATED == NAS_MML_GetCsUpdateStatus())
                &&(VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg))
            {
                Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);
                if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
                {
                    g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;

                    Gmm_SndSmEstablishCnf(GMM_SM_EST_SUCCESS, GMM_SM_CAUSE_SUCCESS);
                }

                GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_SUCCESS);
            }
            else                                                                /* CS更新状态不是U1,或者Gs关联已经移除 */
            {
                /* sim无效或者CS域不允许注册 */
                if (VOS_TRUE != NAS_MML_GetSimCsRegStatus())
                {
                    Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);

                    if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
                    {
                        g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;

                        Gmm_SndSmEstablishCnf(GMM_SM_EST_SUCCESS, GMM_SM_CAUSE_SUCCESS);
                    }

                    GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_SUCCESS);
                }
                else
                {
                    Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);                     /* 调用RAU                                  */
                }
            }
        }
    }
    else
    {
        /* 更新状态不是GU1,发起RAU */
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
    }
}

/*****************************************************************************
 函 数 名  : NAS_GMM_ProcCsAcChgRegisterNetRaiNotChg
 功能描述  : GMM在GMM_REGISTERED_UPDATE_NEEDED状态收到WasAcInfoChgInd,RAI没有改变时的处理
 输入参数  : pstMsg - 消息内容
 输出参数  : 无
 返 回 值  : 消息类型
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期  : 2012年2月15日
    作    者  : w00166186
    修改内容 : 新生成函数
*****************************************************************************/
VOS_VOID  NAS_GMM_ProcPsAcChgRegisterNetRaiNotChg()
{
    if (GMM_FALSE == g_GmmRauCtrl.ucT3312ExpiredFlg)
    {
        /* T3312超时标志不存在　*/
        NAS_GMM_ProcPsAcChgRegisterNetRaiNotChgT3312NotExpire();
    }
    else
    {
        /* T3312超时标志存在　*/
        NAS_GMM_ProcPsAcChgRegisterNetRaiNotChgT3312Expire();
    }
}

/*****************************************************************************
 函 数 名  : NAS_GMM_PostAcInfoChgInd
 功能描述  : 收到MMC转发的WasAcInfoChgInd的后处理
 输入参数  : pstMsg - 消息内容
 输出参数  : 无
 返 回 值  : 消息类型
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期  : 2012年2月15日
    作    者  : w00166186
    修改内容 : 新生成函数
  2.日    期   : 2012年12月11日
    作    者   : w00176964
    修改内容   : NAS_MML_GetPsRestrictNormalServiceFlg修改函数名
*****************************************************************************/
VOS_VOID NAS_GMM_ComProcAcInfoChgInd(
    MMCGMM_W_AC_INFO_CHANGE_IND_STRU  *pstAcInfoChangeInd
)
{
    /* 重选到PS被BARRED的小区,在网络模式I,并且T3312超时 */
    if (NAS_MML_RESTRICTION_UNBAR_TO_BAR == pstAcInfoChangeInd->enPsRestrictRegisterChange)
    {
        if ((VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
         && (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg))
        {
            NAS_GMM_SndMmLuInitiation(GMMMM_T3312_EXPIRED);
        }
    }
    /* 当前业务受限，则清除业务缓存 */
    /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, begin */
    if (VOS_TRUE == NAS_MML_GetPsRestrictNormalServiceFlg())
    /* Modified by w00176964 for V7R1C50_DCM接入禁止小区信息上报, 2012-12-11, end */
    {
        /* 清除缓存 */
        Gmm_ComCnfHandle();
        GMM_BufferMsgDump();
    }
}

/*****************************************************************************
 函 数 名  : NAS_GMM_RcvMmcWasAcInfoChgInd_RegInit
 功能描述  : 在DEREG状态收到MMC转发的WasAcInfoChgInd的处理
 输入参数  : pstMsg - 消息内容
 输出参数  : 无
 返 回 值  : 消息类型
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期  : 2012年2月15日
    作    者  : w00166186
    修改内容 : 新生成函数
  2.日    期   : 2013年2月4日
    作    者   : w00176964
    修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册
*****************************************************************************/
VOS_VOID  NAS_GMM_RcvMmcWasAcInfoChgInd_Dereg(
    MMCGMM_W_AC_INFO_CHANGE_IND_STRU  *pstAcInfoChangeInd
)
{
    /* PS 注册从不受限到受限 */
    if (NAS_MML_RESTRICTION_UNBAR_TO_BAR == pstAcInfoChangeInd->enPsRestrictRegisterChange)
    {
        if (GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH == g_GmmGlobalCtrl.ucState)
        {
            /* 网络模式I */
            if  ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
              && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
            {
                NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);          /* 通知MM进行LU                             */
            }
        }

        /* 设置当前PS服务状态为限制服务 */
        Gmm_ComStaChg(GMM_DEREGISTERED_ATTACH_NEEDED);
    }
}

/*****************************************************************************
 函 数 名  : NAS_GMM_RcvMmcWasAcInfoChgInd_RegLimit
 功能描述  : REG LIMIT SERVICE状态收到MMC转发的WasAcInfoChgInd的处理
 输入参数  : pstMsg - 消息内容
 输出参数  : 无
 返 回 值  : 消息类型
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期  : 2012年2月15日
    作    者  : w00166186
    修改内容 : 新生成函数
*****************************************************************************/
VOS_VOID NAS_GMM_RcvMmcWasAcInfoChgInd_RegLimitServ(
    MMCGMM_W_AC_INFO_CHANGE_IND_STRU   *pstAcInfoChangeInd
)
{
    /* PS 注册受限 */
    if (NAS_MML_RESTRICTION_UNBAR_TO_BAR == pstAcInfoChangeInd->enPsRestrictRegisterChange)
    {
        /* 迁移当前GMM状态到GMM_REGISTERED_UPDATE_NEEDED */
        Gmm_ComStaChg(GMM_REGISTERED_UPDATE_NEEDED);
    }
}
/*****************************************************************************
 函 数 名  : NAS_GMM_RcvMmcWasAcInfoChgInd_DeregAttNeeded
 功能描述  : GMM_DEREGISTERED_ATTACH_NEEDED状态收到MMC转发的WasAcInfoChgInd的处理
 输入参数  : pstMsg - 消息内容
 输出参数  : 无
 返 回 值  : 消息类型
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期  : 2012年2月15日
    作    者  : w00166186
    修改内容 : 新生成函数

  2.日    期   : 2013年6月11日
    作    者   : z00234330
    修改内容   : DTS2013061152841,从bar的小区到不bar的小区,GMM通知wrr建链消息里面携带的plmn id为0
*****************************************************************************/
VOS_VOID  NAS_GMM_RcvMmcWasAcInfoChgInd_DeregAttNeeded(
    MMCGMM_W_AC_INFO_CHANGE_IND_STRU  *pstAcInfoChangeInd
)
{
    NAS_MML_NETWORK_INFO_STRU          *pstNetworkInfo;

    pstNetworkInfo = NAS_MML_GetNetworkInfo();

    /* PS 注册从受限到不受限 */
    if (NAS_MML_RESTRICTION_BAR_TO_UNBAR == pstAcInfoChangeInd->enPsRestrictRegisterChange)
    {
        g_GmmGlobalCtrl.SysInfo.ucSysValidFlg       = GMM_TRUE;
        g_GmmGlobalCtrl.SysInfo.ucNetMod            = pstNetworkInfo->stCampPlmnInfo.enNetworkMode;
        g_GmmGlobalCtrl.ucNetMod                    = g_GmmGlobalCtrl.SysInfo.ucNetMod;
        g_GmmGlobalCtrl.SysInfo.ucNtType            = NAS_MML_GetCurrNetRatType();
        g_GmmGlobalCtrl.SysInfo.ucPsDrxLen          = NAS_MML_GetWSysInfoDrxLen();
        if ( VOS_TRUE == pstNetworkInfo->stPsDomainInfo.ucPsSupportFlg )
        {
            g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs    = GMM_SUPPORT_GPRS;
        }
        else
        {
            g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs    = GMM_NOT_SUPPORT_GPRS;
        }

        g_GmmGlobalCtrl.SysInfo.Rai.ucRac = NAS_MML_GetCurrCampRac();
        g_GmmGlobalCtrl.SysInfo.Rai.Lai.aucLac[0] = pstNetworkInfo->stCampPlmnInfo.stLai.aucLac[0];
        g_GmmGlobalCtrl.SysInfo.Rai.Lai.aucLac[1] = pstNetworkInfo->stCampPlmnInfo.stLai.aucLac[1];
        g_GmmGlobalCtrl.SysInfo.ulCellId = pstNetworkInfo->stCampPlmnInfo.stCampCellInfo.astCellInfo[0].ulCellId;
        g_GmmGlobalCtrl.SysInfo.ucCellChgFlg = GMM_FALSE;
        NAS_GMM_ConvertPlmnIdToGmmFormat(&(pstNetworkInfo->stCampPlmnInfo.stLai.stPlmnId),&g_GmmGlobalCtrl.SysInfo.Rai.Lai.PlmnId);

        /* PS卡无效 */
        if (VOS_TRUE != NAS_MML_GetSimPsRegStatus())
        {                                                                           /* 原来SIM无效                              */
            GMM_CasFsmStateChangeTo(GMM_DEREGISTERED_NO_IMSI);
            return;
        }

        /* 当前用户设置不支持PS注册 */
        if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
        {
            Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                         /* 调用状态的公共处理                       */

            GMM_BufferMsgResume();
            return;
        }

        /* 当前网络不支持GPRS，或者网络在禁止列表 */
        if ((GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
         || (MMC_GMM_NO_FORBIDDEN != g_GmmGlobalCtrl.SysInfo.ucForbMask))
        {                                                                           /* 不支持GPRS                               */
            Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);                        /* 调用状态的公共处理                       */
        }
        else
        {                                                                           /* 小区改变                                 */
            g_GmmAttachCtrl.ucAttachAttmptCnt = 0;
            Gmm_AttachInitiate(GMM_NULL_PROCEDURE);
        }
    }


}

/*****************************************************************************
 函 数 名  : NAS_GMM_RcvMmcWasAcInfoChgInd_RegNmlServ
 功能描述  : GMM 在REG正常服务状态收到MMC转发的WasAcInfoChgInd的处理
 输入参数  : pstMsg - 消息内容
 输出参数  : 无
 返 回 值  : 消息类型
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期  : 2012年2月15日
    作    者  : w00166186
    修改内容 : 新生成函数
*****************************************************************************/
VOS_VOID NAS_GMM_RcvMmcWasAcInfoChgInd_RegNmlServ(
    MMCGMM_W_AC_INFO_CHANGE_IND_STRU   *pstAcInfoChangeInd
)
{
    VOS_UINT8                           ucCsAttachAllow;                        /* CS域是否允许注册,VOS_TRUE:允许CS域注册,VOS_FALSE:不允许CS域注册 */
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampInfo = VOS_NULL_PTR;

    pstCampInfo         = NAS_MML_GetCurrCampPlmnInfo();
    ucCsAttachAllow     = NAS_MML_GetCsAttachAllowFlg();

    /* PS 注册不受限到受限 */
    if (NAS_MML_RESTRICTION_UNBAR_TO_BAR == pstAcInfoChangeInd->enPsRestrictRegisterChange)
    {
        Gmm_ComStaChg(GMM_REGISTERED_UPDATE_NEEDED);

        if (GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM == g_GmmGlobalCtrl.ucState)
        {
            if (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
            {
                /* 通知MM进行LU */
                NAS_GMM_SndMmLuInitiation(GMMMM_T3312_EXPIRED);
            }
            else
            {
                 /* 通知MM进行LU */
                NAS_GMM_SndMmLuInitiation(GMMMM_NO_TIMER_EXPIRED);
            }
        }
    }
    else
    {
        /* 网络模式I,手机模式A,CS卡有效,Gs连接标志不存在，且当前CS信令不存在，
        CS注册从受限变为不受限时需要发起联合注册 */
        if ((VOS_TRUE == NAS_MML_GetSimCsRegStatus())
         && (NAS_MML_RESTRICTION_BAR_TO_UNBAR == pstAcInfoChangeInd->enCsRestrictRegisterChange)
         && (VOS_TRUE == ucCsAttachAllow)
         && (NAS_MML_NET_MODE_I == pstCampInfo->enNetworkMode)
         && (VOS_FALSE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg)
         && (GMM_FALSE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg))
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
        }
    }
}

/*****************************************************************************
 函 数 名  : NAS_GMM_RcvMmcWasAcInfoChgInd_RegUptNeeded
 功能描述  : 在GMM_REGISTERED_UPDATE_NEEDED状态收到MMC转发的WasAcInfoChgInd的处理
 输入参数  : pstMsg - 消息内容
 输出参数  : 无
 返 回 值  : 消息类型
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期  : 2012年2月15日
    作    者  : w00166186
    修改内容 : 新生成函数
  2.日    期   : 2013年6月11日
    作    者   : z00234330
    修改内容   : DTS2013061152841,从bar的小区到不bar的小区,GMM通知wrr建链消息里面携带的plmn id为0
*****************************************************************************/
VOS_VOID NAS_GMM_RcvMmcWasAcInfoChgInd_RegUptNeeded(
    MMCGMM_W_AC_INFO_CHANGE_IND_STRU   *pstAcInfoChangeInd
)
{
    NAS_MML_NETWORK_INFO_STRU          *pstNetworkInfo;

    pstNetworkInfo = NAS_MML_GetNetworkInfo();

    /* PS 注册从受限到不受限 */
    if (NAS_MML_RESTRICTION_BAR_TO_UNBAR == pstAcInfoChangeInd->enPsRestrictRegisterChange)
    {
        g_GmmGlobalCtrl.SysInfo.ucNetMod            = pstNetworkInfo->stCampPlmnInfo.enNetworkMode;
        g_GmmGlobalCtrl.ucNetMod                    = g_GmmGlobalCtrl.SysInfo.ucNetMod;
        g_GmmGlobalCtrl.SysInfo.ucNtType            = NAS_MML_GetCurrNetRatType();
        g_GmmGlobalCtrl.SysInfo.ucPsDrxLen          = NAS_MML_GetWSysInfoDrxLen();
        if ( VOS_TRUE == pstNetworkInfo->stPsDomainInfo.ucPsSupportFlg )
        {
            g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs    = GMM_SUPPORT_GPRS;
        }
        else
        {
            g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs    = GMM_NOT_SUPPORT_GPRS;
        }
        g_GmmGlobalCtrl.SysInfo.Rai.ucRac = NAS_MML_GetCurrCampRac();
        g_GmmGlobalCtrl.SysInfo.Rai.Lai.aucLac[0] = pstNetworkInfo->stCampPlmnInfo.stLai.aucLac[0];
        g_GmmGlobalCtrl.SysInfo.Rai.Lai.aucLac[1] = pstNetworkInfo->stCampPlmnInfo.stLai.aucLac[1];
        g_GmmGlobalCtrl.SysInfo.ulCellId = pstNetworkInfo->stCampPlmnInfo.stCampCellInfo.astCellInfo[0].ulCellId;
        g_GmmGlobalCtrl.SysInfo.ucCellChgFlg = GMM_FALSE;
        NAS_GMM_ConvertPlmnIdToGmmFormat(&(pstNetworkInfo->stCampPlmnInfo.stLai.stPlmnId),&g_GmmGlobalCtrl.SysInfo.Rai.Lai.PlmnId);
        if (VOS_FALSE ==  NAS_MML_GetPsAttachAllowFlg())
        {
            Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);
        }
        /* 当前网络不支持GPRS */
        else if (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
        {
            Gmm_ComStaChg(GMM_REGISTERED_LIMITED_SERVICE);
        }
        /* 当前网络在禁止列表 */
        else if (MMC_GMM_NO_FORBIDDEN != g_GmmGlobalCtrl.SysInfo.ucForbMask)
        {
            Gmm_ComForbiddenList(g_GmmGlobalCtrl.SysInfo.ucForbMask);
        }
        else if (VOS_FALSE == NAS_MML_IsRaiChanged())
        {
            /* RAI没有改变 */
            NAS_GMM_ProcPsAcChgRegisterNetRaiNotChg();
        }
        else
        {
            /* RAI改变 */
            NAS_GMM_ProcPsAcChgRegisterNetRaiChg();
        }
    }

}

/*****************************************************************************
 函 数 名  : NAS_GMM_RcvMmcWasAcInfoChgInd
 功能描述  : 收到MMC转发RRMM_W_INFO_CHANGE_IND
 输入参数  : pstMsg - 消息内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期  : 2012年2月15日
    作    者  : W00166186
    修改内容 : 新生成函数
*****************************************************************************/
VOS_VOID NAS_GMM_RcvMmcWasAcInfoChgInd(
    NAS_MSG_STRU                       *pstMsg
)
{
    MMCGMM_W_AC_INFO_CHANGE_IND_STRU   *pstAcInfoChangeInd = VOS_NULL_PTR;

    pstAcInfoChangeInd = (MMCGMM_W_AC_INFO_CHANGE_IND_STRU*)pstMsg;

    /* 将原语RRMM_W_INFO_CHANGE_IND按照状态分发 */
    switch (g_GmmGlobalCtrl.ucState)
    {
        /* DEREG状态收到RRMM_W_INFO_CHANGE_IND的处理 */
        case GMM_DEREGISTERED_NO_CELL_AVAILABLE:
        case GMM_DEREGISTERED_NORMAL_SERVICE:
        case GMM_DEREGISTERED_LIMITED_SERVICE:
        case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
            NAS_GMM_RcvMmcWasAcInfoChgInd_Dereg(pstAcInfoChangeInd);
            break;
        case GMM_DEREGISTERED_INITIATED:
        case GMM_REGISTERED_IMSI_DETACH_INITIATED:
        case GMM_ROUTING_AREA_UPDATING_INITIATED:
        case GMM_REGISTERED_INITIATED:
        case GMM_SERVICE_REQUEST_INITIATED:
            break;

        /* REG LIMITED SERVICE状态收到RRMM_W_INFO_CHANGE_IND的处理 */
        case GMM_REGISTERED_LIMITED_SERVICE:
        case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
        case GMM_REGISTERED_NO_CELL_AVAILABLE:
            NAS_GMM_RcvMmcWasAcInfoChgInd_RegLimitServ(pstAcInfoChangeInd);
            break;

        /* GMM_DEREGISTERED_ATTACH_NEEDED状态收到RRMM_W_INFO_CHANGE_IND的处理 */
        case GMM_DEREGISTERED_ATTACH_NEEDED:
            NAS_GMM_RcvMmcWasAcInfoChgInd_DeregAttNeeded(pstAcInfoChangeInd);
            break;

        /* REG NORMAL状态收到RRMM_W_INFO_CHANGE_IND的处理 */
        case GMM_REGISTERED_NORMAL_SERVICE:
        case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
            NAS_GMM_RcvMmcWasAcInfoChgInd_RegNmlServ(pstAcInfoChangeInd);
            break;

        /* GMM_REGISTERED_UPDATE_NEEDED状态收到RRMM_W_INFO_CHANGE_IND的处理 */
        case GMM_REGISTERED_UPDATE_NEEDED:
            NAS_GMM_RcvMmcWasAcInfoChgInd_RegUptNeeded(pstAcInfoChangeInd);
            break;
        default :
            NAS_WARNING_LOG(WUEPS_PID_GMM, "Gmm_RcvMmcSysInfoInd:WARNING:g_GmmGlobalCtrl.ucState is Error");
            break;
    }

    NAS_GMM_ComProcAcInfoChgInd(pstAcInfoChangeInd);

}
/*****************************************************************************
 函 数 名  : NAS_GMM_GetRegUptNeededPsSrvStatus
 功能描述  : 获取MM_IDLE_LOCATION_UPDATE_NEEDED状态时CS域服务状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8 PS域服务状态
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年2月15日
    作    者   : w00166186
    修改内容   : 新生成函数

*****************************************************************************/
NAS_MM_COM_SERVICE_STATUS_ENUM_UINT8 NAS_GMM_GetRegUptNeededPsSrvStatus()
{
    NAS_MML_ROUTING_UPDATE_STATUS_ENUM_UINT8    enPsUpdateStatus;

    enPsUpdateStatus = NAS_MML_GetPsUpdateStatus();

    /* 如果当前RAI和上次成功注册的RAI相同，UPDATE状态为U1，OTHER不受限为正常服务，否则为限制服务 */
    if ((VOS_FALSE == NAS_MML_IsRaiChanged())
     && (NAS_MML_ROUTING_UPDATE_STATUS_UPDATED == enPsUpdateStatus))
    {
        return MM_COM_SRVST_NORMAL_SERVICE;
    }
    else
    {
        if (GMM_TRUE == g_GmmGlobalCtrl.ucLaNotAllowFlg)
        {
            g_GmmGlobalCtrl.ucLaNotAllowFlg = GMM_FALSE;
            return MM_COM_SRVST_LIMITED_SERVICE_REGION;
        }
        else
        {
            return MM_COM_SRVST_LIMITED_SERVICE;
        }
    }
}

/*****************************************************************************
 函 数 名  : NAS_GMM_ProcSmDataReq_RAUInit
 功能描述  : 在RAU过程中收到SM消息的处理
 输入参数  : VOS_VOID                           *pMsg
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年05月04日
    作    者   : l65478
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID NAS_GMM_ProcSmDataReq_RAUInit(
    VOS_VOID                           *pSmDataReqMsg
)
{
    VOS_UINT8                           ucMsgType;

    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "NAS_GMM_ProcSmDataReq_RAUInit:NORMAL:Gmm receive SM Data Req.");

    /* 是去激活接受或者SM STATUS消息,有链接时立刻发给网络,没有链接时丢弃;
       否则缓存消息 */
    ucMsgType = NAS_GMM_GetGmmSmDataReqMsgType(&((GMMSM_DATA_REQ_STRU *)pSmDataReqMsg)->SmMsg);
    if ((SM_DEACT_PDP_CONTEXT_ACC == ucMsgType)
     || (SM_STATUS                == ucMsgType))
    {
        if (GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
        {
            Gmm_SndRrmmDataReqForCm(RRC_NAS_MSG_PRIORTY_HIGH,
                                    &((GMMSM_DATA_REQ_STRU *)pSmDataReqMsg)->SmMsg);
        }
    }
    else
    {
        Gmm_BufSmDataReqMsg(pSmDataReqMsg);
    }
}

#if (FEATURE_ON == FEATURE_LTE)

/*****************************************************************************
 函 数 名  : NAS_Gmm_IsPtmsiMappedFromGuti
 功能描述  : 判断当前PTMSI是否是GUTI转换而来
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月17日
    作    者   : w00166186
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_Gmm_IsPtmsiMappedFromGuti(VOS_VOID)
{
    VOS_UINT8                           ucUeIdMask;
    VOS_UINT32                          ulLocalPtmsiFlg;

    VOS_UINT32                          ulGetGutiRst;
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType;

    ucUeIdMask          = NAS_GMM_GetUeIdMask();

    /* 判断GUPTMSI是否有效，VOS_TRUE:有效;VOS_FALSE:无效; */
    if ( GMM_UEID_P_TMSI == (ucUeIdMask & GMM_UEID_P_TMSI) )
    {
        ulLocalPtmsiFlg = VOS_TRUE;
    }
    else
    {
        ulLocalPtmsiFlg = VOS_FALSE;
    }

    /* 获取当前的Tin值和Mapped P-Tmsi */
    ulGetGutiRst        = NAS_GMM_MapPtmsiFromGUTI();
    enTinType           = NAS_MML_GetTinType();

    if ((NAS_MML_TIN_TYPE_GUTI == enTinType)
     && (VOS_OK == ulGetGutiRst) )
    {
        return VOS_TRUE;
    }

    if ((NAS_MML_TIN_TYPE_INVALID == enTinType)
     && (VOS_FALSE == ulLocalPtmsiFlg)
     && (VOS_OK == ulGetGutiRst))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;

}
#endif



/*****************************************************************************
 函 数 名  : NAS_GMM_FreeBufferCmMsg
 功能描述  : 释放缓存的CM消息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年5月22日
    作    者   : l5478
    修改内容   : 新生成函数

*****************************************************************************/

VOS_VOID NAS_GMM_FreeBufferCmMsg(VOS_VOID)
{
    VOS_VOID                           *pAddr;                                              /* 定义指针                                 */

    if (GMM_MSG_HOLD_FOR_SERVICE
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &GMM_MSG_HOLD_FOR_SERVICE))
    {                                                                           /* 如果有保留的ServiceRequest原语           */
        Gmm_SndRabmReestablishCnf(GMM_RABM_SERVICEREQ_FAILURE);                 /* 通知RABM结果                             */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SERVICE;      /* 清除保留标志                             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForService;        /* 读取ServiceRequest原语地址               */
        Gmm_MemFree(pAddr);                                                     /* 将保留buffer中所有的消息释放             */
    }

    if (GMM_MSG_HOLD_FOR_SM
        == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SM))
    {                                                                           /* 如果有保留的SmDataReq原语                */
        NAS_NORMAL_LOG(WUEPS_PID_GMM, "NAS_GMM_FreeBufferCmMsg(): Clear cached SM data Req");

        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SM;           /* 清除保留标志                             */
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSm;             /* 读取SmDataReq原语地址                    */
        Gmm_MemFree(pAddr);                                                     /* 将保留buffer中所有的消息释放             */
    }
}

/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-30, begin */
/*****************************************************************************
 函 数 名  : NAS_GMM_IsNeedEnableLte_AttachPs
 功能描述  : Attach PS完成后判断是否需要enable LTE
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:需要enable LTE
             VOS_FALSE:不需要enable LTE
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2012年08月29日
   作    者   : z00161729
   修改内容   : 新生成函数
 2.日    期   : 2012年09月12日
   作    者   : z00161729
   修改内容   : DTS2012082702662：disable或enable lte不再判断当前syscfg是否支持L
 3.日    期   : 2012年11月10日
   作    者   : s00217060
   修改内容   : DTS2012102902559：USIM卡时，才需要Enable Lte;SIM卡时不需要
 4.日    期   : 2013年11月01日
   作    者   : l00208543
   修改内容   : 根据卡类型禁止网络制式

*****************************************************************************/
VOS_UINT32 NAS_GMM_IsNeedEnableLte_AttachPs(VOS_VOID)
{
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLteCapabilityStatus;

    /* 在满足如下条件后，MMC需要重新enable LTE：
    (1)本地disable LTE的标记为真
    (2)PS卡有效
    (3)USIM卡 */

    /* 获取LTE的使能状态 */
    enLteCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();

    /* 如果开机时已经根据en_NV_Item_Rat_Forbidden_List_Accord_Imsi_Config的配置禁止了LTE，则返回VOS_FALSE */
    if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE == NAS_MML_GetLteForbiddenStatusFlg())
    {
        return VOS_FALSE;
    }


    /* 如果之前未disable LTE,也不需要enable LTE */
    if ((NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS != enLteCapabilityStatus)
     && (NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS != enLteCapabilityStatus))
    {
        return VOS_FALSE;
    }

    /* 如果是SIM卡，不需要Enable Lte */
    if (NAS_MML_SIM_TYPE_SIM == NAS_MML_GetSimType())
    {
        return VOS_FALSE;
    }

    /* disable 或enable lte不再判断syscfg是否支持L */

    /* PS卡无效 */
    if (VOS_FALSE == NAS_MML_GetSimPsRegStatus())
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/* Modified by z00161729 for DCM定制需求和遗留问题, 2012-8-30, end */

/*****************************************************************************
 函 数 名  : NAS_GMM_GetAttachType
 功能描述  : 获取attach 类型
 输入参数  : 无
 输出参数  : 无
 返 回 值  : attach 类型
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2012年09月16日
   作    者   : z00161729
   修改内容   : 新生成函数DTS2012091707434
 2.日    期   : 2013年2月4日
   作    者   : w00176964
   修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册

*****************************************************************************/
VOS_UINT8 NAS_GMM_GetAttachType(VOS_VOID)
{
    VOS_UINT8                           ucCsRestrictRegister;

    ucCsRestrictRegister = NAS_MML_GetCsRestrictRegisterFlg();

    /* ps不允许attach，不能做注册 */
    if (VOS_FALSE == NAS_MML_GetPsAttachAllowFlg())
    {
        return GMM_NULL_PROCEDURE;
    }

    /* 存在CS信令链接时，进行NORMAL ATTACH */
    if ( VOS_TRUE == NAS_MML_GetCsSigConnStatusFlg() )
    {
        /* 网络模式I, 若PS域单独注册成功后，收到系统消息后，需要再次触发COMBINED ATTACH */
        if ( GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod )
        {
            NAS_GMM_SetSpecProcInCsTrans(GMM_ATTACH_NORMAL);
        }

        return GMM_ATTACH_NORMAL;
    }

    if (((VOS_TRUE != NAS_MML_GetCsAttachAllowFlg())
      || (GMM_NET_MODE_I != g_GmmGlobalCtrl.ucNetMod)))
    {
        return GMM_ATTACH_NORMAL;
    }

    if (VOS_TRUE == NAS_MML_GetSimCsRegStatus())
    {                                                                           /* CS域SIM有效                              */
        if (MM_STATUS_ATTACHED == g_MmSubLyrShare.MmShare.ucCsAttachState)
        {                                                                       /* CS域已经注册                             */
            if (GMM_TRUE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg)
            {
                g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;       /* 清除CS通信中的流程                       */
                return GMM_ATTACH_NORMAL_CS_TRANS;
            }

            return GMM_ATTACH_WHILE_IMSI_ATTACHED;
        }

        if ((VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
         || (VOS_TRUE == ucCsRestrictRegister))
        {
            /* CS域ATTACH被禁止 */
            return GMM_ATTACH_NORMAL;
        }

        /* CS域ATTACH没被禁止 */
        if (GMM_TRUE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg)
        {
            /* CS域在通信中*/
            g_GmmGlobalCtrl.ucSpecProcInCsTrans = GMM_NULL_PROCEDURE;
            return GMM_ATTACH_NORMAL_CS_TRANS;
        }

        /* CS域不在通信中 */
        return  GMM_ATTACH_COMBINED;

    }

    return GMM_ATTACH_NORMAL;

}

/*****************************************************************************
 函 数 名  : NAS_GMM_RcvMmCsConnectInd_RrcConnExist
 功能描述  : RRC连接存在时，收到MM的CsConnectInd的处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年4月7日
    作    者   : z00161729
    修改内容   : 新生成函数
  2.日    期   : 2012年10月30日
    作    者   : s00217060
    修改内容   : DTS2012050301830:修改函数名，收到MM的CsConnectInd时,如果RRC连接存在,立即发起RAU；
                 否则,收到接入层上报的系统消息后再做联合RAU.
  3.日    期   : 2013年2月4日
    作    者   : w00176964
    修改内容   : DTS2011022802215:CS ONLY,网络模式I下也进行联合注册

*****************************************************************************/
VOS_VOID NAS_GMM_RcvMmCsConnectInd_RrcConnExist(VOS_VOID)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrNetRatType;
    VOS_UINT8                           ucSimCsRegStatus;
    VOS_UINT8                           ucCsRestrictRegFlg;
    VOS_UINT8                           ucPsRestrictRegFlg;

    ucCsRestrictRegFlg = NAS_MML_GetCsRestrictRegisterFlg();
    ucPsRestrictRegFlg = NAS_MML_GetPsRestrictRegisterFlg();
    ucSimCsRegStatus   = NAS_MML_GetSimCsRegStatus();
    enCurrNetRatType   = NAS_MML_GetCurrNetRatType();

    if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
     && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod)
     && (GMM_FALSE == g_GmmGlobalCtrl.CsInfo.ucCsTransFlg)
     && (GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
     && (NAS_MML_NET_RAT_TYPE_LTE != enCurrNetRatType)
     && (VOS_FALSE == ucCsRestrictRegFlg)
     && (VOS_TRUE == ucSimCsRegStatus)
     && (VOS_FALSE == ucPsRestrictRegFlg))
    {
        Gmm_TimerStop(GMM_TIMER_T3311);
        Gmm_TimerStop(GMM_TIMER_T3302);
        g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_WITH_IMSI_ATTACH;
        Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
    }
    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_FreeWasSysInfo
 功能描述  : 释放缓存GSM系统消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年12月28日
   作    者  : l00167671
   修改内容  : 新生成函数，修改问题单DTS2012122001075,问题单场景如下:
                 PS建链过程中发生RA改变，该场景中如果CS域有业务则PS域做RAU
				 会被不确定的推迟到CS连接释放时才做，修改此场景中的操作如下:
				 若CS域有业务则给WAS发送RRMM_REL_REQ请求，请WAS释放连接，
				 并保存系统消息。在收到WAS的RRMM_REL_IND时用保存的系统消息做RAU
*****************************************************************************/
VOS_VOID NAS_GMM_FreeWasSysInfo(VOS_VOID)
{
    VOS_VOID                           *pAddr = VOS_NULL_PTR;

    if (GMM_MSG_HOLD_FOR_WAS_SYSINFO
        != (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_WAS_SYSINFO))
    {
        return;
    }

    /* 清除保留标志 */
    g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_WAS_SYSINFO;

    /* 将保留buffer中所有的消息释放 */
    if (VOS_NULL_PTR != g_GmmGlobalCtrl.MsgHold.ulMsgAddrForWasSysinfo)
    {
        pAddr = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForWasSysinfo;
        Gmm_MemFree(pAddr);
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForWasSysinfo = VOS_NULL_PTR;
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_SaveWasSysInfo
 功能描述  : 缓存W的系统消息
 输入参数  : pstGsmSysInfo
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年12月28日
   作    者  : l00167671
   修改内容  : 新生成函数，修改问题单DTS2012122001075,问题单场景如下:
                 PS建链过程中发生RA改变，该场景中如果CS域有业务则PS域做RAU
				 会被不确定的推迟到CS连接释放时才做，修改此场景中的操作如下:
				 若CS域有业务则给WAS发送RRMM_REL_REQ请求，请WAS释放连接，
				 并保存系统消息。在收到WAS的RRMM_REL_IND时用保存的系统消息做RAU
*****************************************************************************/
VOS_VOID NAS_GMM_SaveWasSysInfo(
    MMCGMM_SYS_INFO_IND_STRU         *pstSysInfo
)
{
    MMCGMM_SYS_INFO_IND_STRU         *pstHoldSysInfo = VOS_NULL_PTR;

    NAS_GMM_FreeWasSysInfo();

    pstHoldSysInfo = (MMCGMM_SYS_INFO_IND_STRU *)Gmm_MemMalloc(sizeof(MMCGMM_SYS_INFO_IND_STRU));
    if (VOS_NULL_PTR == pstHoldSysInfo)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_GMM_SaveWasSysInfo:WARNING: Mem alloc fail.");
        return;
    }

    /* 置缓存标志 */
    g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk |= GMM_MSG_HOLD_FOR_WAS_SYSINFO;

    /* 保存系统消息 */
    Gmm_MemCpy(pstHoldSysInfo, pstSysInfo, sizeof(MMCGMM_SYS_INFO_IND_STRU));
    g_GmmGlobalCtrl.MsgHold.ulMsgAddrForWasSysinfo = (VOS_UINT32)pstHoldSysInfo;

    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_ProcSavedWasSysInfo
 功能描述  : 处理缓存GSM系统消息
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2011年12月28日
   作    者  : l00167671
   修改内容  : 新生成函数，修改问题单DTS2012122001075,问题单场景如下:
                 PS建链过程中发生RA改变，该场景中如果CS域有业务则PS域做RAU
				 会被不确定的推迟到CS连接释放时才做，修改此场景中的操作如下:
				 若CS域有业务则给WAS发送RRMM_REL_REQ请求，请WAS释放连接，
				 并保存系统消息。在收到WAS的RRMM_REL_IND时用保存的系统消息做RAU
*****************************************************************************/
VOS_UINT32 NAS_GMM_ProcSavedWasSysInfo()
{
    if (GMM_MSG_HOLD_FOR_WAS_SYSINFO
        != (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_WAS_SYSINFO))
    {
        return VOS_FALSE;
    }

    if (VOS_NULL_PTR != g_GmmGlobalCtrl.MsgHold.ulMsgAddrForWasSysinfo)
    {
        Gmm_MsgDistribute((VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForWasSysinfo);
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 函 数 名  : Gmm_MsgDistribute_ProcMmcMsg_GmmNull
 功能描述  : GMM在GmmNULL状态处理MMC消息
 输入参数  : pMsg        - 收到消息
 输出参数  : 无
 返 回 值  : GMM_TRUE    - 当前消息继续处理
             MM_TRUE     - 当前消息处理完毕
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月17日
    作    者   : w00167002
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 Gmm_MsgDistribute_ProcMmcMsg_GmmNull(
    VOS_VOID                           *pRcvMsg                                 /* 接收消息使用的头地址定义                 */
)
{
    MSG_HEADER_STRU                    *pstNasMsgHeader  = VOS_NULL_PTR;        /* 定义MSG_HEADER_STRU类型指针              */
    VOS_UINT8                           ucRst;

    pstNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                               /* 得到消息头                               */
    ucRst = GMM_TRUE;

    switch ( pstNasMsgHeader->ulMsgName )
    {
        case MMCGMM_START_REQ :
            break;

        case MMCGMM_COVERAGE_LOST_IND :
            break;

        case MMCGMM_MODE_CHANGE_REQ :
            break;

        case MMCGMM_PLMN_SEARCH_INITIATED :
            break;

        case MMCGMM_SYS_INFO_IND :
            break;

        case MMCGMM_GSM_SYS_INFO_IND :
            break;

        case MMCGMM_POWER_OFF_REQ :
            break;

        /* 下面消息认为异常消息 */
        case MMCGMM_DETACH_REQ :
            NAS_GMM_SndMmcDetachCnf();
            ucRst = GMM_FALSE;

            break;

        case MMCGMM_ATTACH_REQ :
            NAS_GMM_SndMmcAttachCnf();
            ucRst = GMM_FALSE;

            break;

        default:
            ucRst = GMM_FALSE;
            break;
    }

    return ucRst;
}



/*****************************************************************************
 函 数 名  : NAS_Gmm_IsValidMmcMsg_GmmTcActive
 功能描述  : GMM在GmmTcActive状态判断MMC消息是否非法
 输入参数  : pMsg        - 收到消息
 输出参数  : 无
 返 回 值  : GMM_TRUE    - 当前消息和法，可以后续继续处理
             MM_TRUE     - 当前消息非法，处理完毕
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年6月17日
    作    者   : w00167002
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 NAS_Gmm_IsValidMmcMsg_GmmTcActive(
    VOS_VOID                           *pRcvMsg                                 /* 接收消息使用的头地址定义                 */
)
{
    MSG_HEADER_STRU                    *pstNasMsgHeader  = VOS_NULL_PTR;        /* 定义MSG_HEADER_STRU类型指针              */
    VOS_UINT8                           ucRst;

    pstNasMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;                               /* 得到消息头                               */
    ucRst = GMM_TRUE;

    switch ( pstNasMsgHeader->ulMsgName )
    {
        case MMCGMM_START_REQ :
            break;

        case MMCGMM_POWER_OFF_REQ :
            break;

        case MMCGMM_SUSPEND_IND :
            break;

        case MMCGMM_COVERAGE_LOST_IND :
            break;

        case MMCGMM_ATTACH_REQ :
            break;

        /* 否则认为消息非法，不处理 */
        default:
            ucRst = GMM_FALSE;
            NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_Gmm_IsInvalidMmcMsg_GmmTcActive:WARN:INVALID MSG");
            break;
    }

    return ucRst;
}


/*****************************************************************************
 函 数 名  : NAS_Gmm_ClearPendingPdpStatus
 功能描述  : 清除处于PENDING状态的PDP STATUS
 输入参数  : VOS_VOID
 输出参数  : VOS_VOID
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2013年12月10日
    作    者   : l65478
    修改内容   : 新生成函数
  2.日    期   : 2014年12月06日
    作    者   : A00165503
    修改内容   : DTS2014120207400: 连续去激活多个PDP, 网侧不释放RRC连接
*****************************************************************************/
VOS_VOID NAS_Gmm_ClearPendingPdpStatus(VOS_VOID)
{
    NAS_MML_PS_BEARER_CONTEXT_STRU     *pstPsBearCtx;
    VOS_UINT32                          i;

    pstPsBearCtx = NAS_MML_GetPsBearerCtx();

    /* 根据消息中pdp状态更新MML中全局变量 g_stNasMmlCtx.stNetworkInfo.astPsBearerContext*/
    for (i = 0; i < NAS_MML_MAX_PS_BEARER_NUM; i++)
    {
        if (VOS_TRUE == pstPsBearCtx[i].ucPsActPending)
        {
            pstPsBearCtx[i].ucPsActPending = VOS_FALSE;
        }

        if (VOS_TRUE == pstPsBearCtx[i].ucPsDeactPending)
        {
            pstPsBearCtx[i].ucPsDeactPending = VOS_FALSE;
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : NAS_GMM_ClearAuthInfo
 功能描述  : 清除鉴权相关信息
 输入参数  : VOS_VOID
 输出参数  : VOS_VOID
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年01月09日
    作    者   : l65478
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  NAS_GMM_ClearAuthInfo(VOS_VOID)
{
    g_GmmAuthenCtrl.ucLastFailCause = GMM_AUTHEN_REJ_CAUSE_INVALID;
    g_GmmAuthenCtrl.ucAuthenAttmptCnt = 0;

    /* 24.008 4.7.7.2
    The RAND and RES values stored in the mobile station shall be deleted and timer T3316, if running, shall be stopped:
    -   if the mobile station enters the GMM states GMM-DEREGISTERED or GMM-NULL.
    */
    g_GmmAuthenCtrl.ucResStoredFlg  = GMM_FALSE;                                /* 将"RES存在标志 "置为0                    */
    g_GmmAuthenCtrl.ucRandStoredFlg = GMM_FALSE;                                /* 将"RAND存在标志 "置为0                   */
    Gmm_TimerStop(GMM_TIMER_T3316);

    if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG == (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG & g_GmmReqCnfMng.ucCnfMask))
    {
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;
        Gmm_TimerStop(GMM_TIMER_PROTECT);
    }


    return;
}

/*lint -restore */

/*****************************************************************************
 函 数 名  : NAS_GMM_IsNeedProcRelInd
 功能描述  : 检查是否需要处理rel_ind消息
 输入参数  : RRMM_REL_IND_STRU:接入层的rel_ind消息
 输出参数  : VOS_VOID
 返 回 值  : VOS_TRUE:需要继续处理rel_ind消息
             VOS_FALSE:不需要继续处理rel_ind消息
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年07月09日
    作    者   : s00217060
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  NAS_GMM_IsNeedProcRelInd(
    RRMM_REL_IND_STRU       *pstRrRelInd
)
{

    /* 如果不是PS域,GMM不需要处理 */
    if (RRC_NAS_PS_DOMAIN != pstRrRelInd->ulCnDomainId)
    {
        return VOS_FALSE;
    }


    /* 如果是在以下几个状态等待est_cnf，并且rel cause为RRC_REL_CAUSE_NAS_DATA_ABSENT，丢弃不处理:
        GMM_REGISTERED_INITIATED:
        GMM_DEREGISTERED_INITIATED:
        GMM_ROUTING_AREA_UPDATING_INITIATED:
        GMM_SERVICE_REQUEST_INITIATED:
        GMM_REGISTERED_IMSI_DETACH_INITIATED:
    */

    /* 如果GMM没在等接入层的est_cnf，需要继续处理 */
    if (GMM_RRC_RRMM_EST_CNF_FLG !=
        (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG))
    {
        return VOS_TRUE;
    }

    /* 如果rel cause不是RRC_REL_CAUSE_NAS_DATA_ABSENT，需要继续处理 */
    if (RRC_REL_CAUSE_NAS_DATA_ABSENT != pstRrRelInd->ulRelCause)
    {
        return VOS_TRUE;
    }

    /* 状态不是init状态，需要继续处理 */
    if ( (GMM_REGISTERED_INITIATED != g_GmmGlobalCtrl.ucState)
      && (GMM_DEREGISTERED_INITIATED != g_GmmGlobalCtrl.ucState)
      && (GMM_ROUTING_AREA_UPDATING_INITIATED != g_GmmGlobalCtrl.ucState)
      && (GMM_SERVICE_REQUEST_INITIATED != g_GmmGlobalCtrl.ucState)
      && (GMM_REGISTERED_IMSI_DETACH_INITIATED != g_GmmGlobalCtrl.ucState) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_GMM_RcvMmcMsg_PreProc_GprsSuspension
 功能描述  : 在GMM_GPRS_SUSPENSION/GMM_SUSPENDED_GPRS_SUSPENSION状态收到MMC消息的预处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2014年12月15日
   作    者   : s00217060
   修改内容   : 新增函数
*****************************************************************************/
VOS_UINT32 NAS_GMM_RcvMmcMsg_PreProc_GprsSuspension(
    struct MsgCB                       *pstMsg,
    VOS_UINT8                          *pucFollowOn
)
{
    MSG_HEADER_STRU                    *pstNasMsgHeader  = VOS_NULL_PTR;

    pstNasMsgHeader = (MSG_HEADER_STRU*)pstMsg;

    if (MMCGMM_SUSPEND_IND == pstNasMsgHeader->ulMsgName)
    {
        GMM_LOG_INFO("NAS_GMM_RcvMmcMsg_PreProc_GprsSuspension:Receive MMCGMM_SUSPEND_IND in GMM_GPRS_SUSPENSION state.");
        *pucFollowOn = GMM_TRUE;
        return VOS_TRUE;
    }
    else if (MMCGMM_POWER_OFF_REQ == pstNasMsgHeader->ulMsgName)
    {
        GMM_BufferMsgDump();
        Gmm_TimerStop(GMM_TIMER_ALL);
        Gmm_TimerStart(GMM_TIMER_1S);
        gstGmmSuspendCtrl.ucPowerOff = GMM_POWER_OFF_RCV;
        g_GmmGlobalCtrl.stPowerOffCtrl.ucSndDetachCnt = 0;
        return VOS_TRUE;
    }
    else if ( MMCGMM_PLMN_SEARCH_INITIATED == pstNasMsgHeader->ulMsgName )
    {
        /* 进行后面的处理，迁移到搜网状态 */
        *pucFollowOn = GMM_TRUE;
        return VOS_TRUE;
    }
    else if ( MMCGMM_DETACH_REQ == pstNasMsgHeader->ulMsgName )
    {
        /* 进行后面的处理，迁移到搜网状态 */
        *pucFollowOn = GMM_TRUE;
        return VOS_TRUE;
    }


    /* 收到MMCGMM_ATTACH_REQ消息，则不进行缓存，而是直接回复Attach成功，
       待重新驻留可用网络后进行Attach */
    else if ( MMCGMM_ATTACH_REQ == pstNasMsgHeader->ulMsgName )
    {
        *pucFollowOn = GMM_TRUE;
        return VOS_TRUE;
    }

    else if (( MMCGMM_GSM_SYS_INFO_IND == pstNasMsgHeader->ulMsgName )
          || ( MMCGMM_SYS_INFO_IND == pstNasMsgHeader->ulMsgName ) )
    {
        /* 停HO等待系统消息定时器,缓存系统消息 */
        Gmm_TimerStop(GMM_TIMER_HO_WAIT_SYSINFO);
    }
    else
    {
    }

    return VOS_FALSE;
}


#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : NAS_GMM_RcvMmcVoiceDomainChangeNotify
 功能描述  : GMM收到MMC的MMCGMM_VOICE_DOMAIN_CHANGE_NOTIFY消息的处理
 输入参数  : pRcvMsg:消息
 输出参数  : VOS_VOID
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2014年07月09日
    作    者   : s00217060
    修改内容   : 新生成函数
  2.日    期   : 2015年8月13日
    作    者   : l00289540
    修改内容   : User_Exp_Improve修改

*****************************************************************************/
VOS_VOID  NAS_GMM_RcvMmcVoiceDomainChangeNotify(
    struct MsgCB                       *pRcvMsg
)
{
    /* 相关协议章节:
    3GPP 24008:
    4.7.5.1 Normal and periodic routing area updating procedure

    The normal routing area updating procedure is initiated:
    ......
    -    when the UE's usage setting or the voice domain preference for E-UTRAN change in the MS;
    ......
    */

    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus = VOS_NULL_PTR;

    VOS_INT8                            cVersion;

    cVersion        = NAS_Common_Get_Supported_3GPP_Version(MM_COM_SRVDOMAIN_PS);
    pstConnStatus   = NAS_MML_GetConnStatus();

    if (cVersion < PS_PTL_VER_R9)
    {
        return;
    }

    /* voice domain和上次发起注册时的相同，不需要再做RAU */
    if (g_GmmGlobalCtrl.UeInfo.enVoiceDomainFromRegReq == NAS_MML_GetVoiceDomainPreference())
    {
        return;
    }

    /* 当前已经运行时，重新启动 */
    if (VOS_TRUE == NAS_GMM_QryTimerStatus(GMM_TIMER_DELAY_VOICE_DOMAIN_TRIG_RAU))
    {
        Gmm_TimerStop(GMM_TIMER_DELAY_VOICE_DOMAIN_TRIG_RAU);
        Gmm_TimerStart(GMM_TIMER_DELAY_VOICE_DOMAIN_TRIG_RAU);
        return;
    }

    /* 如果存在CS业务则直接返回 */
    if (VOS_TRUE == pstConnStatus->ucCsServiceConnStatusFlg)
    {
        return;
    }

    /* 如果正在发起CS业务则启动定时器，业务发起失败依靠定时器触发RAU，
       业务发起成功定时器超时时会直接返回 */
    if ((VOS_TRUE == NAS_MML_GetCsServiceBufferStatusFlg())
     && (VOS_TRUE == pstConnStatus->ucCsSigConnStatusFlg))
    {
        Gmm_TimerStart(GMM_TIMER_DELAY_VOICE_DOMAIN_TRIG_RAU);

        return;
    }

    if ((GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
     || (GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM == g_GmmGlobalCtrl.ucState))
    {
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        return;
    }

    if ((GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
     || (GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucState)
     || (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
     || (GMM_REGISTERED_IMSI_DETACH_INITIATED == g_GmmGlobalCtrl.ucState))
    {
        Gmm_TimerStart(GMM_TIMER_DELAY_VOICE_DOMAIN_TRIG_RAU);
    }

    return;
}
#endif

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
