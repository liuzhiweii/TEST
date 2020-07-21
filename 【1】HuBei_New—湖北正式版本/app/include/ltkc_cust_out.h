
/*
 * Generated file - DO NOT EDIT
 *
 * This is the header file for the LLRP Tool Kit (LTK)
 * C++ (aka cpp) implementation. It is generated into a .inc file
 * that is included by a platform specific .h header file.
 * That .h file takes care of prerequisites needed by this file.
 */




/*
 * Message classes - forward decls
 */


/* Custom messages */

struct LLRP_SGET_READER_CAPABILITIES_EXT;
typedef struct LLRP_SGET_READER_CAPABILITIES_EXT
    LLRP_tSGET_READER_CAPABILITIES_EXT;

struct LLRP_SGET_READER_CAPABILITIES_EXT_RESPONSE;
typedef struct LLRP_SGET_READER_CAPABILITIES_EXT_RESPONSE
    LLRP_tSGET_READER_CAPABILITIES_EXT_RESPONSE;

struct LLRP_SGET_READER_COMM_CAPABILITIES;
typedef struct LLRP_SGET_READER_COMM_CAPABILITIES
    LLRP_tSGET_READER_COMM_CAPABILITIES;

struct LLRP_SGET_READER_COMM_CAPABILITIES_RESPONSE;
typedef struct LLRP_SGET_READER_COMM_CAPABILITIES_RESPONSE
    LLRP_tSGET_READER_COMM_CAPABILITIES_RESPONSE;

struct LLRP_SGET_READER_CONFIG_EXT;
typedef struct LLRP_SGET_READER_CONFIG_EXT
    LLRP_tSGET_READER_CONFIG_EXT;

struct LLRP_SGET_READER_CONFIG_EXT_RESPONSE;
typedef struct LLRP_SGET_READER_CONFIG_EXT_RESPONSE
    LLRP_tSGET_READER_CONFIG_EXT_RESPONSE;

struct LLRP_SSET_READER_CONFIG_EXT;
typedef struct LLRP_SSET_READER_CONFIG_EXT
    LLRP_tSSET_READER_CONFIG_EXT;

struct LLRP_SSET_READER_CONFIG_EXT_RESPONSE;
typedef struct LLRP_SSET_READER_CONFIG_EXT_RESPONSE
    LLRP_tSSET_READER_CONFIG_EXT_RESPONSE;

struct LLRP_SGET_READER_COMM_CONFIG;
typedef struct LLRP_SGET_READER_COMM_CONFIG
    LLRP_tSGET_READER_COMM_CONFIG;

struct LLRP_SGET_READER_COMM_CONFIG_RESPONSE;
typedef struct LLRP_SGET_READER_COMM_CONFIG_RESPONSE
    LLRP_tSGET_READER_COMM_CONFIG_RESPONSE;

struct LLRP_SSET_READER_COMM_CONFIG;
typedef struct LLRP_SSET_READER_COMM_CONFIG
    LLRP_tSSET_READER_COMM_CONFIG;

struct LLRP_SSET_READER_COMM_CONFIG_RESPONSE;
typedef struct LLRP_SSET_READER_COMM_CONFIG_RESPONSE
    LLRP_tSSET_READER_COMM_CONFIG_RESPONSE;

struct LLRP_SRESET_TO_FACTORY_DEFAULT;
typedef struct LLRP_SRESET_TO_FACTORY_DEFAULT
    LLRP_tSRESET_TO_FACTORY_DEFAULT;

struct LLRP_SRESET_READER;
typedef struct LLRP_SRESET_READER
    LLRP_tSRESET_READER;

struct LLRP_SRESET_TO_FACTORY_DEFAULT_RESPONSE;
typedef struct LLRP_SRESET_TO_FACTORY_DEFAULT_RESPONSE
    LLRP_tSRESET_TO_FACTORY_DEFAULT_RESPONSE;

struct LLRP_SRESET_READER_RESPONSE;
typedef struct LLRP_SRESET_READER_RESPONSE
    LLRP_tSRESET_READER_RESPONSE;

struct LLRP_SSET_PLT_DMP_TEST;
typedef struct LLRP_SSET_PLT_DMP_TEST
    LLRP_tSSET_PLT_DMP_TEST;

struct LLRP_SSET_PLT_DMP_TEST_RESPONSE;
typedef struct LLRP_SSET_PLT_DMP_TEST_RESPONSE
    LLRP_tSSET_PLT_DMP_TEST_RESPONSE;

struct LLRP_STB_TEST_REQUEST;
typedef struct LLRP_STB_TEST_REQUEST
    LLRP_tSTB_TEST_REQUEST;

struct LLRP_STB_TEST_REQUEST_RESPONSE;
typedef struct LLRP_STB_TEST_REQUEST_RESPONSE
    LLRP_tSTB_TEST_REQUEST_RESPONSE;

struct LLRP_SDEL_ALARM;
typedef struct LLRP_SDEL_ALARM
    LLRP_tSDEL_ALARM;

struct LLRP_SSYNC_ALARM;
typedef struct LLRP_SSYNC_ALARM
    LLRP_tSSYNC_ALARM;

struct LLRP_SALARM_REPORT;
typedef struct LLRP_SALARM_REPORT
    LLRP_tSALARM_REPORT;

struct LLRP_SALARM_RESTOREREPORT;
typedef struct LLRP_SALARM_RESTOREREPORT
    LLRP_tSALARM_RESTOREREPORT;

struct LLRP_SINFORM_ALARM_REPORT;
typedef struct LLRP_SINFORM_ALARM_REPORT
    LLRP_tSINFORM_ALARM_REPORT;

struct LLRP_SREFRESH_ALARM;
typedef struct LLRP_SREFRESH_ALARM
    LLRP_tSREFRESH_ALARM;

struct LLRP_SREADER_VERSION_ACTIVATE;
typedef struct LLRP_SREADER_VERSION_ACTIVATE
    LLRP_tSREADER_VERSION_ACTIVATE;

struct LLRP_SREADER_VERSION_ACTIVATE_RESPONS;
typedef struct LLRP_SREADER_VERSION_ACTIVATE_RESPONS
    LLRP_tSREADER_VERSION_ACTIVATE_RESPONS;

struct LLRP_SREADER_VERSION_UNACTIVATE;
typedef struct LLRP_SREADER_VERSION_UNACTIVATE
    LLRP_tSREADER_VERSION_UNACTIVATE;

struct LLRP_SREADER_VERSION_UNACTIVATE_RESPONS;
typedef struct LLRP_SREADER_VERSION_UNACTIVATE_RESPONS
    LLRP_tSREADER_VERSION_UNACTIVATE_RESPONS;

struct LLRP_SREADER_VERSION_QUERY;
typedef struct LLRP_SREADER_VERSION_QUERY
    LLRP_tSREADER_VERSION_QUERY;

struct LLRP_SREADER_VERSION_QUERY_RESPONSE;
typedef struct LLRP_SREADER_VERSION_QUERY_RESPONSE
    LLRP_tSREADER_VERSION_QUERY_RESPONSE;

struct LLRP_SREADER_VERSION_DOWNLOAD_REQUEST;
typedef struct LLRP_SREADER_VERSION_DOWNLOAD_REQUEST
    LLRP_tSREADER_VERSION_DOWNLOAD_REQUEST;

struct LLRP_SREADER_VERSION_DOWNLOAD_REQUEST_RESPONS;
typedef struct LLRP_SREADER_VERSION_DOWNLOAD_REQUEST_RESPONS
    LLRP_tSREADER_VERSION_DOWNLOAD_REQUEST_RESPONS;

struct LLRP_SREADER_VERSION_DOWNLOAD;
typedef struct LLRP_SREADER_VERSION_DOWNLOAD
    LLRP_tSREADER_VERSION_DOWNLOAD;

struct LLRP_SREADER_VERSION_DOWNLOAD_RESPONS;
typedef struct LLRP_SREADER_VERSION_DOWNLOAD_RESPONS
    LLRP_tSREADER_VERSION_DOWNLOAD_RESPONS;

struct LLRP_SREADER_UBOOTVERSION_QUERY;
typedef struct LLRP_SREADER_UBOOTVERSION_QUERY
    LLRP_tSREADER_UBOOTVERSION_QUERY;

struct LLRP_SREADER_UBOOTVERSION_QUERY_RESPONS;
typedef struct LLRP_SREADER_UBOOTVERSION_QUERY_RESPONS
    LLRP_tSREADER_UBOOTVERSION_QUERY_RESPONS;

struct LLRP_SREADER_UBOOTVERSION_UPDATE;
typedef struct LLRP_SREADER_UBOOTVERSION_UPDATE
    LLRP_tSREADER_UBOOTVERSION_UPDATE;

struct LLRP_SREADER_UBOOTVERSION_UPDATE_RESPONS;
typedef struct LLRP_SREADER_UBOOTVERSION_UPDATE_RESPONS
    LLRP_tSREADER_UBOOTVERSION_UPDATE_RESPONS;

struct LLRP_SSP_VERSION_QUERY;
typedef struct LLRP_SSP_VERSION_QUERY
    LLRP_tSSP_VERSION_QUERY;

struct LLRP_SSP_VERSION_QUERY_RESPONSE;
typedef struct LLRP_SSP_VERSION_QUERY_RESPONSE
    LLRP_tSSP_VERSION_QUERY_RESPONSE;

struct LLRP_SSP_VERSION_DOWNLOAD;
typedef struct LLRP_SSP_VERSION_DOWNLOAD
    LLRP_tSSP_VERSION_DOWNLOAD;

struct LLRP_SSP_VERSION_DOWNLOAD_RESPONSE;
typedef struct LLRP_SSP_VERSION_DOWNLOAD_RESPONSE
    LLRP_tSSP_VERSION_DOWNLOAD_RESPONSE;

struct LLRP_SSP_VERSION_DELETE;
typedef struct LLRP_SSP_VERSION_DELETE
    LLRP_tSSP_VERSION_DELETE;

struct LLRP_SSP_VERSION_DELETE_RESPONSE;
typedef struct LLRP_SSP_VERSION_DELETE_RESPONSE
    LLRP_tSSP_VERSION_DELETE_RESPONSE;

struct LLRP_SGET_READER_LOG;
typedef struct LLRP_SGET_READER_LOG
    LLRP_tSGET_READER_LOG;

struct LLRP_SGET_READER_LOG_RESPONSE;
typedef struct LLRP_SGET_READER_LOG_RESPONSE
    LLRP_tSGET_READER_LOG_RESPONSE;

struct LLRP_SGET_READER_LOG_RESPONSE_ACK;
typedef struct LLRP_SGET_READER_LOG_RESPONSE_ACK
    LLRP_tSGET_READER_LOG_RESPONSE_ACK;

struct LLRP_SGET_READER_EXCEPTION;
typedef struct LLRP_SGET_READER_EXCEPTION
    LLRP_tSGET_READER_EXCEPTION;

struct LLRP_SGET_READER_EXCEPTION_RESPONSE;
typedef struct LLRP_SGET_READER_EXCEPTION_RESPONSE
    LLRP_tSGET_READER_EXCEPTION_RESPONSE;

struct LLRP_SGET_READER_EXCEPTION_RESPONSE_ACK;
typedef struct LLRP_SGET_READER_EXCEPTION_RESPONSE_ACK
    LLRP_tSGET_READER_EXCEPTION_RESPONSE_ACK;

struct LLRP_SDELETE_TAG_MEMORY_DEF_TABLE;
typedef struct LLRP_SDELETE_TAG_MEMORY_DEF_TABLE
    LLRP_tSDELETE_TAG_MEMORY_DEF_TABLE;

struct LLRP_SDELETE_TAG_MEMORY_DEF_TABLE_RESPONSE;
typedef struct LLRP_SDELETE_TAG_MEMORY_DEF_TABLE_RESPONSE
    LLRP_tSDELETE_TAG_MEMORY_DEF_TABLE_RESPONSE;

struct LLRP_SHF_ENTRANCEGUARD_LOGIC_CARD;
typedef struct LLRP_SHF_ENTRANCEGUARD_LOGIC_CARD
    LLRP_tSHF_ENTRANCEGUARD_LOGIC_CARD;

struct LLRP_SHF_ENTRANCEGUARD_LOGIC_CARD_RESPONSE;
typedef struct LLRP_SHF_ENTRANCEGUARD_LOGIC_CARD_RESPONSE
    LLRP_tSHF_ENTRANCEGUARD_LOGIC_CARD_RESPONSE;

struct LLRP_SHF_ENTRANCEGUARD_CPU_CARD;
typedef struct LLRP_SHF_ENTRANCEGUARD_CPU_CARD
    LLRP_tSHF_ENTRANCEGUARD_CPU_CARD;

struct LLRP_SHF_ENTRANCEGUARD_CPU_CARD_RESPONSE;
typedef struct LLRP_SHF_ENTRANCEGUARD_CPU_CARD_RESPONSE
    LLRP_tSHF_ENTRANCEGUARD_CPU_CARD_RESPONSE;

struct LLRP_SHF_ENTRANCEGUARD_DEVICE;
typedef struct LLRP_SHF_ENTRANCEGUARD_DEVICE
    LLRP_tSHF_ENTRANCEGUARD_DEVICE;

struct LLRP_SHF_ENTRANCEGUARD_DEVICE_RESPONSE;
typedef struct LLRP_SHF_ENTRANCEGUARD_DEVICE_RESPONSE
    LLRP_tSHF_ENTRANCEGUARD_DEVICE_RESPONSE;

struct LLRP_SHF_ENTRANCEGUARD_RESET_CARD;
typedef struct LLRP_SHF_ENTRANCEGUARD_RESET_CARD
    LLRP_tSHF_ENTRANCEGUARD_RESET_CARD;

struct LLRP_SHF_ENTRANCEGUARD_RESET_CARD_RESPONSE;
typedef struct LLRP_SHF_ENTRANCEGUARD_RESET_CARD_RESPONSE
    LLRP_tSHF_ENTRANCEGUARD_RESET_CARD_RESPONSE;

struct LLRP_SHF_ENTRANCEGUARD_LOW_CMD;
typedef struct LLRP_SHF_ENTRANCEGUARD_LOW_CMD
    LLRP_tSHF_ENTRANCEGUARD_LOW_CMD;

struct LLRP_SHF_ENTRANCEGUARD_LOW_CMD_RESPONSE;
typedef struct LLRP_SHF_ENTRANCEGUARD_LOW_CMD_RESPONSE
    LLRP_tSHF_ENTRANCEGUARD_LOW_CMD_RESPONSE;

struct LLRP_SHF_ENTRANCEGUARD_BROADCAST_TIME_MSG;
typedef struct LLRP_SHF_ENTRANCEGUARD_BROADCAST_TIME_MSG
    LLRP_tSHF_ENTRANCEGUARD_BROADCAST_TIME_MSG;

struct LLRP_SHF_ENTRANCEGUARD_ALARM_MSG;
typedef struct LLRP_SHF_ENTRANCEGUARD_ALARM_MSG
    LLRP_tSHF_ENTRANCEGUARD_ALARM_MSG;

struct LLRP_SHF_ENTRANCEGUARD_ID_RESPONSE;
typedef struct LLRP_SHF_ENTRANCEGUARD_ID_RESPONSE
    LLRP_tSHF_ENTRANCEGUARD_ID_RESPONSE;

struct LLRP_SSET_READER_INITKEY;
typedef struct LLRP_SSET_READER_INITKEY
    LLRP_tSSET_READER_INITKEY;

struct LLRP_SSET_READER_INITKEY_RESPONSE;
typedef struct LLRP_SSET_READER_INITKEY_RESPONSE
    LLRP_tSSET_READER_INITKEY_RESPONSE;

struct LLRP_SBIND_READER_TWINS_PSAM;
typedef struct LLRP_SBIND_READER_TWINS_PSAM
    LLRP_tSBIND_READER_TWINS_PSAM;

struct LLRP_SBIND_READER_TWINS_PSAM_RESPONSE;
typedef struct LLRP_SBIND_READER_TWINS_PSAM_RESPONSE
    LLRP_tSBIND_READER_TWINS_PSAM_RESPONSE;

struct LLRP_SUNBIND_READER_TWINS_PSAM;
typedef struct LLRP_SUNBIND_READER_TWINS_PSAM
    LLRP_tSUNBIND_READER_TWINS_PSAM;

struct LLRP_SUNBIND_READER_TWINS_PSAM_RESPONSE;
typedef struct LLRP_SUNBIND_READER_TWINS_PSAM_RESPONSE
    LLRP_tSUNBIND_READER_TWINS_PSAM_RESPONSE;

struct LLRP_SHF_ENTRANCEGUARD_DEVICE_ARRAYMSG;
typedef struct LLRP_SHF_ENTRANCEGUARD_DEVICE_ARRAYMSG
    LLRP_tSHF_ENTRANCEGUARD_DEVICE_ARRAYMSG;

struct LLRP_SHF_ENTRANCEGUARD_DEVICE_ARRAYRESPONSE;
typedef struct LLRP_SHF_ENTRANCEGUARD_DEVICE_ARRAYRESPONSE
    LLRP_tSHF_ENTRANCEGUARD_DEVICE_ARRAYRESPONSE;

struct LLRP_SEC00_PC_6200PLT;
typedef struct LLRP_SEC00_PC_6200PLT
    LLRP_tSEC00_PC_6200PLT;

struct LLRP_SEC00_PC_6200PLT_RESPONSE;
typedef struct LLRP_SEC00_PC_6200PLT_RESPONSE
    LLRP_tSEC00_PC_6200PLT_RESPONSE;

struct LLRP_SADD_ZTE_ROSPEC;
typedef struct LLRP_SADD_ZTE_ROSPEC
    LLRP_tSADD_ZTE_ROSPEC;

struct LLRP_SADD_ZTE_ROSPEC_RESPONSE;
typedef struct LLRP_SADD_ZTE_ROSPEC_RESPONSE
    LLRP_tSADD_ZTE_ROSPEC_RESPONSE;

struct LLRP_SADD_ZTE_ACCESSSPEC;
typedef struct LLRP_SADD_ZTE_ACCESSSPEC
    LLRP_tSADD_ZTE_ACCESSSPEC;

struct LLRP_SADD_ZTE_ACCESSSPEC_RESPONSE;
typedef struct LLRP_SADD_ZTE_ACCESSSPEC_RESPONSE
    LLRP_tSADD_ZTE_ACCESSSPEC_RESPONSE;

struct LLRP_SSAVED_RO_ACCESS_REPORT;
typedef struct LLRP_SSAVED_RO_ACCESS_REPORT
    LLRP_tSSAVED_RO_ACCESS_REPORT;

struct LLRP_SSAVED_RO_ACCESS_REPORT_ACK;
typedef struct LLRP_SSAVED_RO_ACCESS_REPORT_ACK
    LLRP_tSSAVED_RO_ACCESS_REPORT_ACK;

struct LLRP_SREADER_TRACK_CTRL;
typedef struct LLRP_SREADER_TRACK_CTRL
    LLRP_tSREADER_TRACK_CTRL;

struct LLRP_SREADER_TRACK_CTRL_ACK;
typedef struct LLRP_SREADER_TRACK_CTRL_ACK
    LLRP_tSREADER_TRACK_CTRL_ACK;

struct LLRP_SREADER_RUNINFO_CTRL;
typedef struct LLRP_SREADER_RUNINFO_CTRL
    LLRP_tSREADER_RUNINFO_CTRL;

struct LLRP_SREADER_RUNINFO_CTRL_ACK;
typedef struct LLRP_SREADER_RUNINFO_CTRL_ACK
    LLRP_tSREADER_RUNINFO_CTRL_ACK;

struct LLRP_SDELETE_SAVED_RO_ACCESS_REPORT;
typedef struct LLRP_SDELETE_SAVED_RO_ACCESS_REPORT
    LLRP_tSDELETE_SAVED_RO_ACCESS_REPORT;

struct LLRP_SDELETE_SAVED_RO_ACCESS_REPORT_RESPONSE;
typedef struct LLRP_SDELETE_SAVED_RO_ACCESS_REPORT_RESPONSE
    LLRP_tSDELETE_SAVED_RO_ACCESS_REPORT_RESPONSE;

struct LLRP_SIPD_IPDISCOBVERY;
typedef struct LLRP_SIPD_IPDISCOBVERY
    LLRP_tSIPD_IPDISCOBVERY;

struct LLRP_SIPD_IPDISCOBVERY_ACK;
typedef struct LLRP_SIPD_IPDISCOBVERY_ACK
    LLRP_tSIPD_IPDISCOBVERY_ACK;

struct LLRP_SIPD_SETREADERCONFIG;
typedef struct LLRP_SIPD_SETREADERCONFIG
    LLRP_tSIPD_SETREADERCONFIG;

struct LLRP_SIPD_SETREADERCONFIG_RESPONSE;
typedef struct LLRP_SIPD_SETREADERCONFIG_RESPONSE
    LLRP_tSIPD_SETREADERCONFIG_RESPONSE;

struct LLRP_SIPD_RESETREADER;
typedef struct LLRP_SIPD_RESETREADER
    LLRP_tSIPD_RESETREADER;

struct LLRP_SIPD_RESETREADER_RESPONSE;
typedef struct LLRP_SIPD_RESETREADER_RESPONSE
    LLRP_tSIPD_RESETREADER_RESPONSE;

struct LLRP_SUHF_PRIVATE_CMD;
typedef struct LLRP_SUHF_PRIVATE_CMD
    LLRP_tSUHF_PRIVATE_CMD;

struct LLRP_SUHF_PRIVATE_CMD_RESPONSE;
typedef struct LLRP_SUHF_PRIVATE_CMD_RESPONSE
    LLRP_tSUHF_PRIVATE_CMD_RESPONSE;

struct LLRP_SUHF_PRIVATE_SETPASSWORD;
typedef struct LLRP_SUHF_PRIVATE_SETPASSWORD
    LLRP_tSUHF_PRIVATE_SETPASSWORD;

struct LLRP_SUHF_PRIVATE_SETPASSWORD_RESPONSE;
typedef struct LLRP_SUHF_PRIVATE_SETPASSWORD_RESPONSE
    LLRP_tSUHF_PRIVATE_SETPASSWORD_RESPONSE;

struct LLRP_SZIT_SET_TIME;
typedef struct LLRP_SZIT_SET_TIME
    LLRP_tSZIT_SET_TIME;

struct LLRP_SZIT_SET_TIME_RESPONSE;
typedef struct LLRP_SZIT_SET_TIME_RESPONSE
    LLRP_tSZIT_SET_TIME_RESPONSE;


/*
 * Parameter classes - forward decls
 */


/* Custom parameters */

struct LLRP_SExtRegulatoryCapabilities;
typedef struct LLRP_SExtRegulatoryCapabilities
    LLRP_tSExtRegulatoryCapabilities;

struct LLRP_SProtocolParaFor6C;
typedef struct LLRP_SProtocolParaFor6C
    LLRP_tSProtocolParaFor6C;

struct LLRP_SDataRateCapabilities;
typedef struct LLRP_SDataRateCapabilities
    LLRP_tSDataRateCapabilities;

struct LLRP_SM_valueCapabilities;
typedef struct LLRP_SM_valueCapabilities
    LLRP_tSM_valueCapabilities;

struct LLRP_SForward_link_modulationCapabilities;
typedef struct LLRP_SForward_link_modulationCapabilities
    LLRP_tSForward_link_modulationCapabilities;

struct LLRP_SModuleDepthEntry;
typedef struct LLRP_SModuleDepthEntry
    LLRP_tSModuleDepthEntry;

struct LLRP_SModuleDepthEntryFor6B;
typedef struct LLRP_SModuleDepthEntryFor6B
    LLRP_tSModuleDepthEntryFor6B;

struct LLRP_SPPPDialCapabilities;
typedef struct LLRP_SPPPDialCapabilities
    LLRP_tSPPPDialCapabilities;

struct LLRP_SSpecification;
typedef struct LLRP_SSpecification
    LLRP_tSSpecification;

struct LLRP_SCommunicationCapabilities;
typedef struct LLRP_SCommunicationCapabilities
    LLRP_tSCommunicationCapabilities;

struct LLRP_SRUPCommunicationCapabilities;
typedef struct LLRP_SRUPCommunicationCapabilities
    LLRP_tSRUPCommunicationCapabilities;

struct LLRP_SIPV4Support;
typedef struct LLRP_SIPV4Support
    LLRP_tSIPV4Support;

struct LLRP_SEthernetCards;
typedef struct LLRP_SEthernetCards
    LLRP_tSEthernetCards;

struct LLRP_SSerialPort232;
typedef struct LLRP_SSerialPort232
    LLRP_tSSerialPort232;

struct LLRP_SSerialPort485;
typedef struct LLRP_SSerialPort485
    LLRP_tSSerialPort485;

struct LLRP_SSerialAttribute;
typedef struct LLRP_SSerialAttribute
    LLRP_tSSerialAttribute;

struct LLRP_SNTPServerCapabilities;
typedef struct LLRP_SNTPServerCapabilities
    LLRP_tSNTPServerCapabilities;

struct LLRP_SETCExtRegulatoryCapabilities;
typedef struct LLRP_SETCExtRegulatoryCapabilities
    LLRP_tSETCExtRegulatoryCapabilities;

struct LLRP_SMPIExtRegulatoryCapabilities;
typedef struct LLRP_SMPIExtRegulatoryCapabilities
    LLRP_tSMPIExtRegulatoryCapabilities;

struct LLRP_SModuleDepthEtcEntry;
typedef struct LLRP_SModuleDepthEtcEntry
    LLRP_tSModuleDepthEtcEntry;

struct LLRP_SRSSIFilter;
typedef struct LLRP_SRSSIFilter
    LLRP_tSRSSIFilter;

struct LLRP_SRSSIFilterCtrl;
typedef struct LLRP_SRSSIFilterCtrl
    LLRP_tSRSSIFilterCtrl;

struct LLRP_SReaderName;
typedef struct LLRP_SReaderName
    LLRP_tSReaderName;

struct LLRP_SReaderBasicInfo;
typedef struct LLRP_SReaderBasicInfo
    LLRP_tSReaderBasicInfo;

struct LLRP_SDeviceID;
typedef struct LLRP_SDeviceID
    LLRP_tSDeviceID;

struct LLRP_SSaveReportSwitch;
typedef struct LLRP_SSaveReportSwitch
    LLRP_tSSaveReportSwitch;

struct LLRP_SAntennaExtConfiguration;
typedef struct LLRP_SAntennaExtConfiguration
    LLRP_tSAntennaExtConfiguration;

struct LLRP_SUHFAntennaExtConfiguration;
typedef struct LLRP_SUHFAntennaExtConfiguration
    LLRP_tSUHFAntennaExtConfiguration;

struct LLRP_SUHFFrequencyConfiguration;
typedef struct LLRP_SUHFFrequencyConfiguration
    LLRP_tSUHFFrequencyConfiguration;

struct LLRP_SUHFFrequencyConfiguration6B;
typedef struct LLRP_SUHFFrequencyConfiguration6B
    LLRP_tSUHFFrequencyConfiguration6B;

struct LLRP_SUHFFrequencyConfiguration6C;
typedef struct LLRP_SUHFFrequencyConfiguration6C
    LLRP_tSUHFFrequencyConfiguration6C;

struct LLRP_SUHFFrequencyConfigurationGB;
typedef struct LLRP_SUHFFrequencyConfigurationGB
    LLRP_tSUHFFrequencyConfigurationGB;

struct LLRP_SRUPAlarmThreshold;
typedef struct LLRP_SRUPAlarmThreshold
    LLRP_tSRUPAlarmThreshold;

struct LLRP_STemperatureThreshold;
typedef struct LLRP_STemperatureThreshold
    LLRP_tSTemperatureThreshold;

struct LLRP_SMemoryThreshold;
typedef struct LLRP_SMemoryThreshold
    LLRP_tSMemoryThreshold;

struct LLRP_SCPUUtilizationThreshold;
typedef struct LLRP_SCPUUtilizationThreshold
    LLRP_tSCPUUtilizationThreshold;

struct LLRP_SJffsFileThreshold;
typedef struct LLRP_SJffsFileThreshold
    LLRP_tSJffsFileThreshold;

struct LLRP_SLightningBoxThreshold;
typedef struct LLRP_SLightningBoxThreshold
    LLRP_tSLightningBoxThreshold;

struct LLRP_SPowerDifferenceThreshold;
typedef struct LLRP_SPowerDifferenceThreshold
    LLRP_tSPowerDifferenceThreshold;

struct LLRP_SRecvFilter;
typedef struct LLRP_SRecvFilter
    LLRP_tSRecvFilter;

struct LLRP_SLaneNum;
typedef struct LLRP_SLaneNum
    LLRP_tSLaneNum;

struct LLRP_STransmitPower;
typedef struct LLRP_STransmitPower
    LLRP_tSTransmitPower;

struct LLRP_SLBT;
typedef struct LLRP_SLBT
    LLRP_tSLBT;

struct LLRP_SFrequencyConfiguration;
typedef struct LLRP_SFrequencyConfiguration
    LLRP_tSFrequencyConfiguration;

struct LLRP_SFreqHopConfig;
typedef struct LLRP_SFreqHopConfig
    LLRP_tSFreqHopConfig;

struct LLRP_SFreqChannel;
typedef struct LLRP_SFreqChannel
    LLRP_tSFreqChannel;

struct LLRP_SAlarmMask;
typedef struct LLRP_SAlarmMask
    LLRP_tSAlarmMask;

struct LLRP_SModuleDepth;
typedef struct LLRP_SModuleDepth
    LLRP_tSModuleDepth;

struct LLRP_SIQConfig;
typedef struct LLRP_SIQConfig
    LLRP_tSIQConfig;

struct LLRP_SLocationConfiguration;
typedef struct LLRP_SLocationConfiguration
    LLRP_tSLocationConfiguration;

struct LLRP_SGPSLocation;
typedef struct LLRP_SGPSLocation
    LLRP_tSGPSLocation;

struct LLRP_SAntSwitchDelayCfg;
typedef struct LLRP_SAntSwitchDelayCfg
    LLRP_tSAntSwitchDelayCfg;

struct LLRP_STagReportFilter;
typedef struct LLRP_STagReportFilter
    LLRP_tSTagReportFilter;

struct LLRP_SAntCoopCfg;
typedef struct LLRP_SAntCoopCfg
    LLRP_tSAntCoopCfg;

struct LLRP_SAntCoopUDPCfg;
typedef struct LLRP_SAntCoopUDPCfg
    LLRP_tSAntCoopUDPCfg;

struct LLRP_SPerAntUDPCfg;
typedef struct LLRP_SPerAntUDPCfg
    LLRP_tSPerAntUDPCfg;

struct LLRP_SRSSISortCfg;
typedef struct LLRP_SRSSISortCfg
    LLRP_tSRSSISortCfg;

struct LLRP_SLeakCompensation;
typedef struct LLRP_SLeakCompensation
    LLRP_tSLeakCompensation;

struct LLRP_SRecvDATT;
typedef struct LLRP_SRecvDATT
    LLRP_tSRecvDATT;

struct LLRP_SAlarmThreshodCfg;
typedef struct LLRP_SAlarmThreshodCfg
    LLRP_tSAlarmThreshodCfg;

struct LLRP_SRUPCommunicationConfiguration;
typedef struct LLRP_SRUPCommunicationConfiguration
    LLRP_tSRUPCommunicationConfiguration;

struct LLRP_SCommLinkConfiguration;
typedef struct LLRP_SCommLinkConfiguration
    LLRP_tSCommLinkConfiguration;

struct LLRP_SEthernetConfiguration;
typedef struct LLRP_SEthernetConfiguration
    LLRP_tSEthernetConfiguration;

struct LLRP_SSerialPort232Configuration;
typedef struct LLRP_SSerialPort232Configuration
    LLRP_tSSerialPort232Configuration;

struct LLRP_SSerialPort485Configuration;
typedef struct LLRP_SSerialPort485Configuration
    LLRP_tSSerialPort485Configuration;

struct LLRP_SGPRSConfiguration;
typedef struct LLRP_SGPRSConfiguration
    LLRP_tSGPRSConfiguration;

struct LLRP_SCustomPrivateConfigData;
typedef struct LLRP_SCustomPrivateConfigData
    LLRP_tSCustomPrivateConfigData;

struct LLRP_SRFModePrivateCfg;
typedef struct LLRP_SRFModePrivateCfg
    LLRP_tSRFModePrivateCfg;

struct LLRP_SRFModeCfg;
typedef struct LLRP_SRFModeCfg
    LLRP_tSRFModeCfg;

struct LLRP_SETCConfig;
typedef struct LLRP_SETCConfig
    LLRP_tSETCConfig;

struct LLRP_SMPIAntennaConfiguration;
typedef struct LLRP_SMPIAntennaConfiguration
    LLRP_tSMPIAntennaConfiguration;

struct LLRP_SRFReceiverSettings;
typedef struct LLRP_SRFReceiverSettings
    LLRP_tSRFReceiverSettings;

struct LLRP_SRFTransmitterSettings;
typedef struct LLRP_SRFTransmitterSettings
    LLRP_tSRFTransmitterSettings;

struct LLRP_SMPIProperties;
typedef struct LLRP_SMPIProperties
    LLRP_tSMPIProperties;

struct LLRP_SMPIPsamWhiteList;
typedef struct LLRP_SMPIPsamWhiteList
    LLRP_tSMPIPsamWhiteList;

struct LLRP_SPSAMID;
typedef struct LLRP_SPSAMID
    LLRP_tSPSAMID;

struct LLRP_SMPISIMWhiteList;
typedef struct LLRP_SMPISIMWhiteList
    LLRP_tSMPISIMWhiteList;

struct LLRP_STelNo;
typedef struct LLRP_STelNo
    LLRP_tSTelNo;

struct LLRP_SMPIPsamAuthenticationFile;
typedef struct LLRP_SMPIPsamAuthenticationFile
    LLRP_tSMPIPsamAuthenticationFile;

struct LLRP_SMPISMSCenterNo;
typedef struct LLRP_SMPISMSCenterNo
    LLRP_tSMPISMSCenterNo;

struct LLRP_SPPPDialConfiguration;
typedef struct LLRP_SPPPDialConfiguration
    LLRP_tSPPPDialConfiguration;

struct LLRP_SDialNumber;
typedef struct LLRP_SDialNumber
    LLRP_tSDialNumber;

struct LLRP_SDialUser;
typedef struct LLRP_SDialUser
    LLRP_tSDialUser;

struct LLRP_SDialPass;
typedef struct LLRP_SDialPass
    LLRP_tSDialPass;

struct LLRP_STimePhase;
typedef struct LLRP_STimePhase
    LLRP_tSTimePhase;

struct LLRP_SCommunicationConfiguration;
typedef struct LLRP_SCommunicationConfiguration
    LLRP_tSCommunicationConfiguration;

struct LLRP_SModeConfiguration;
typedef struct LLRP_SModeConfiguration
    LLRP_tSModeConfiguration;

struct LLRP_SReaderAddressConfiguration;
typedef struct LLRP_SReaderAddressConfiguration
    LLRP_tSReaderAddressConfiguration;

struct LLRP_SIPVer4;
typedef struct LLRP_SIPVer4
    LLRP_tSIPVer4;

struct LLRP_SGateWay;
typedef struct LLRP_SGateWay
    LLRP_tSGateWay;

struct LLRP_SDNSAddr;
typedef struct LLRP_SDNSAddr
    LLRP_tSDNSAddr;

struct LLRP_SNTPConfiguration;
typedef struct LLRP_SNTPConfiguration
    LLRP_tSNTPConfiguration;

struct LLRP_SNtpPeriodTime;
typedef struct LLRP_SNtpPeriodTime
    LLRP_tSNtpPeriodTime;

struct LLRP_SIPAddress;
typedef struct LLRP_SIPAddress
    LLRP_tSIPAddress;

struct LLRP_SClientAddressConfiguration;
typedef struct LLRP_SClientAddressConfiguration
    LLRP_tSClientAddressConfiguration;

struct LLRP_SLinkConfiguration;
typedef struct LLRP_SLinkConfiguration
    LLRP_tSLinkConfiguration;

struct LLRP_SCommMode;
typedef struct LLRP_SCommMode
    LLRP_tSCommMode;

struct LLRP_SIsSingleton;
typedef struct LLRP_SIsSingleton
    LLRP_tSIsSingleton;

struct LLRP_SHostPortConfiguration;
typedef struct LLRP_SHostPortConfiguration
    LLRP_tSHostPortConfiguration;

struct LLRP_SLinkStateInfo;
typedef struct LLRP_SLinkStateInfo
    LLRP_tSLinkStateInfo;

struct LLRP_SSerialPortConfiguration;
typedef struct LLRP_SSerialPortConfiguration
    LLRP_tSSerialPortConfiguration;

struct LLRP_STestItem;
typedef struct LLRP_STestItem
    LLRP_tSTestItem;

struct LLRP_STestItemACK;
typedef struct LLRP_STestItemACK
    LLRP_tSTestItemACK;

struct LLRP_SGetK0ValueTestAck;
typedef struct LLRP_SGetK0ValueTestAck
    LLRP_tSGetK0ValueTestAck;

struct LLRP_SGetDATTTestAck;
typedef struct LLRP_SGetDATTTestAck
    LLRP_tSGetDATTTestAck;

struct LLRP_SPSAMTest;
typedef struct LLRP_SPSAMTest
    LLRP_tSPSAMTest;

struct LLRP_SPSAMTestAck;
typedef struct LLRP_SPSAMTestAck
    LLRP_tSPSAMTestAck;

struct LLRP_SFPGARWTestACK;
typedef struct LLRP_SFPGARWTestACK
    LLRP_tSFPGARWTestACK;

struct LLRP_SGPRSCommTest;
typedef struct LLRP_SGPRSCommTest
    LLRP_tSGPRSCommTest;

struct LLRP_SGPRSCommTestAck;
typedef struct LLRP_SGPRSCommTestAck
    LLRP_tSGPRSCommTestAck;

struct LLRP_STemperatureQueryTest;
typedef struct LLRP_STemperatureQueryTest
    LLRP_tSTemperatureQueryTest;

struct LLRP_STemperatureQueryTestAck;
typedef struct LLRP_STemperatureQueryTestAck
    LLRP_tSTemperatureQueryTestAck;

struct LLRP_SHardwareVersionQueryTest;
typedef struct LLRP_SHardwareVersionQueryTest
    LLRP_tSHardwareVersionQueryTest;

struct LLRP_SHardwareVersionQueryTestAck;
typedef struct LLRP_SHardwareVersionQueryTestAck
    LLRP_tSHardwareVersionQueryTestAck;

struct LLRP_SQueryLinkStatus;
typedef struct LLRP_SQueryLinkStatus
    LLRP_tSQueryLinkStatus;

struct LLRP_SQueryLinkStatusReqAck;
typedef struct LLRP_SQueryLinkStatusReqAck
    LLRP_tSQueryLinkStatusReqAck;

struct LLRP_SRUPHardwareVersionQueryTestACK;
typedef struct LLRP_SRUPHardwareVersionQueryTestACK
    LLRP_tSRUPHardwareVersionQueryTestACK;

struct LLRP_SRUPBoradInfo;
typedef struct LLRP_SRUPBoradInfo
    LLRP_tSRUPBoradInfo;

struct LLRP_SRUPQueryLinkStatusReqAck;
typedef struct LLRP_SRUPQueryLinkStatusReqAck
    LLRP_tSRUPQueryLinkStatusReqAck;

struct LLRP_SCommLinkStatus;
typedef struct LLRP_SCommLinkStatus
    LLRP_tSCommLinkStatus;

struct LLRP_SCommLinkDesc;
typedef struct LLRP_SCommLinkDesc
    LLRP_tSCommLinkDesc;

struct LLRP_SPsamStatusReadAck;
typedef struct LLRP_SPsamStatusReadAck
    LLRP_tSPsamStatusReadAck;

struct LLRP_SGPRSmoduleTest;
typedef struct LLRP_SGPRSmoduleTest
    LLRP_tSGPRSmoduleTest;

struct LLRP_SGPRSSignalQualityTest;
typedef struct LLRP_SGPRSSignalQualityTest
    LLRP_tSGPRSSignalQualityTest;

struct LLRP_SC0ReadAck;
typedef struct LLRP_SC0ReadAck
    LLRP_tSC0ReadAck;

struct LLRP_SSignalStatus433MHz;
typedef struct LLRP_SSignalStatus433MHz
    LLRP_tSSignalStatus433MHz;

struct LLRP_SCC1101Test;
typedef struct LLRP_SCC1101Test
    LLRP_tSCC1101Test;

struct LLRP_SCommSocket;
typedef struct LLRP_SCommSocket
    LLRP_tSCommSocket;

struct LLRP_SCommSerialPort;
typedef struct LLRP_SCommSerialPort
    LLRP_tSCommSerialPort;

struct LLRP_SCommWiegand;
typedef struct LLRP_SCommWiegand
    LLRP_tSCommWiegand;

struct LLRP_SCommGprs;
typedef struct LLRP_SCommGprs
    LLRP_tSCommGprs;

struct LLRP_SGpioWriteTest;
typedef struct LLRP_SGpioWriteTest
    LLRP_tSGpioWriteTest;

struct LLRP_SSendAndReceiveRFTest;
typedef struct LLRP_SSendAndReceiveRFTest
    LLRP_tSSendAndReceiveRFTest;

struct LLRP_SReverseSensitivityTest;
typedef struct LLRP_SReverseSensitivityTest
    LLRP_tSReverseSensitivityTest;

struct LLRP_SACParamReadWrite;
typedef struct LLRP_SACParamReadWrite
    LLRP_tSACParamReadWrite;

struct LLRP_SPowerTable;
typedef struct LLRP_SPowerTable
    LLRP_tSPowerTable;

struct LLRP_SACVoltageQuery;
typedef struct LLRP_SACVoltageQuery
    LLRP_tSACVoltageQuery;

struct LLRP_SSetAndGetK0;
typedef struct LLRP_SSetAndGetK0
    LLRP_tSSetAndGetK0;

struct LLRP_SPACtr;
typedef struct LLRP_SPACtr
    LLRP_tSPACtr;

struct LLRP_SAutoCalibrite;
typedef struct LLRP_SAutoCalibrite
    LLRP_tSAutoCalibrite;

struct LLRP_SMACAndSerail;
typedef struct LLRP_SMACAndSerail
    LLRP_tSMACAndSerail;

struct LLRP_SMAC;
typedef struct LLRP_SMAC
    LLRP_tSMAC;

struct LLRP_SSerailNumber;
typedef struct LLRP_SSerailNumber
    LLRP_tSSerailNumber;

struct LLRP_SSetVoltage;
typedef struct LLRP_SSetVoltage
    LLRP_tSSetVoltage;

struct LLRP_SZXRIS6601PowerTable;
typedef struct LLRP_SZXRIS6601PowerTable
    LLRP_tSZXRIS6601PowerTable;

struct LLRP_SSetDATTValue;
typedef struct LLRP_SSetDATTValue
    LLRP_tSSetDATTValue;

struct LLRP_SPowerTemplate;
typedef struct LLRP_SPowerTemplate
    LLRP_tSPowerTemplate;

struct LLRP_SBroadInf;
typedef struct LLRP_SBroadInf
    LLRP_tSBroadInf;

struct LLRP_SRTCTime;
typedef struct LLRP_SRTCTime
    LLRP_tSRTCTime;

struct LLRP_STestStartOrStop;
typedef struct LLRP_STestStartOrStop
    LLRP_tSTestStartOrStop;

struct LLRP_SNvramContent;
typedef struct LLRP_SNvramContent
    LLRP_tSNvramContent;

struct LLRP_SAntennaLinkStatusTest;
typedef struct LLRP_SAntennaLinkStatusTest
    LLRP_tSAntennaLinkStatusTest;

struct LLRP_SVSWRQueryTestACK;
typedef struct LLRP_SVSWRQueryTestACK
    LLRP_tSVSWRQueryTestACK;

struct LLRP_SReverseSensitivityDataACK;
typedef struct LLRP_SReverseSensitivityDataACK
    LLRP_tSReverseSensitivityDataACK;

struct LLRP_SGpioReadTestACK;
typedef struct LLRP_SGpioReadTestACK
    LLRP_tSGpioReadTestACK;

struct LLRP_SEpldRegValueACK;
typedef struct LLRP_SEpldRegValueACK
    LLRP_tSEpldRegValueACK;

struct LLRP_SFpgaValueACK;
typedef struct LLRP_SFpgaValueACK
    LLRP_tSFpgaValueACK;

struct LLRP_SEpldRWTestACK;
typedef struct LLRP_SEpldRWTestACK
    LLRP_tSEpldRWTestACK;

struct LLRP_SACVoltageQueryAck;
typedef struct LLRP_SACVoltageQueryAck
    LLRP_tSACVoltageQueryAck;

struct LLRP_SSetAndGetK0Ack;
typedef struct LLRP_SSetAndGetK0Ack
    LLRP_tSSetAndGetK0Ack;

struct LLRP_SAntQueryPowerAck;
typedef struct LLRP_SAntQueryPowerAck
    LLRP_tSAntQueryPowerAck;

struct LLRP_SAntPower;
typedef struct LLRP_SAntPower
    LLRP_tSAntPower;

struct LLRP_SAutoCalibrateAck;
typedef struct LLRP_SAutoCalibrateAck
    LLRP_tSAutoCalibrateAck;

struct LLRP_SAutoCalibrateResult;
typedef struct LLRP_SAutoCalibrateResult
    LLRP_tSAutoCalibrateResult;

struct LLRP_SNetDelayTimeTestACK;
typedef struct LLRP_SNetDelayTimeTestACK
    LLRP_tSNetDelayTimeTestACK;

struct LLRP_SPllTestACK;
typedef struct LLRP_SPllTestACK
    LLRP_tSPllTestACK;

struct LLRP_STempSensorTestACK;
typedef struct LLRP_STempSensorTestACK
    LLRP_tSTempSensorTestACK;

struct LLRP_SPowerIDReadTestACK;
typedef struct LLRP_SPowerIDReadTestACK
    LLRP_tSPowerIDReadTestACK;

struct LLRP_SProtoclArmVersionTestACK;
typedef struct LLRP_SProtoclArmVersionTestACK
    LLRP_tSProtoclArmVersionTestACK;

struct LLRP_SZXRIS6601ReportPwrTblAck;
typedef struct LLRP_SZXRIS6601ReportPwrTblAck
    LLRP_tSZXRIS6601ReportPwrTblAck;

struct LLRP_STestKeyboardAck;
typedef struct LLRP_STestKeyboardAck
    LLRP_tSTestKeyboardAck;

struct LLRP_STestTouchScrAck;
typedef struct LLRP_STestTouchScrAck
    LLRP_tSTestTouchScrAck;

struct LLRP_STbTestItem;
typedef struct LLRP_STbTestItem
    LLRP_tSTbTestItem;

struct LLRP_STbTestItemACK;
typedef struct LLRP_STbTestItemACK
    LLRP_tSTbTestItemACK;

struct LLRP_SSetDeviceType;
typedef struct LLRP_SSetDeviceType
    LLRP_tSSetDeviceType;

struct LLRP_SVersionDwn;
typedef struct LLRP_SVersionDwn
    LLRP_tSVersionDwn;

struct LLRP_SRs485Test;
typedef struct LLRP_SRs485Test
    LLRP_tSRs485Test;

struct LLRP_SGpioTest;
typedef struct LLRP_SGpioTest
    LLRP_tSGpioTest;

struct LLRP_SAntSelect;
typedef struct LLRP_SAntSelect
    LLRP_tSAntSelect;

struct LLRP_SAntInPositon;
typedef struct LLRP_SAntInPositon
    LLRP_tSAntInPositon;

struct LLRP_SSetDeviceTypeAck;
typedef struct LLRP_SSetDeviceTypeAck
    LLRP_tSSetDeviceTypeAck;

struct LLRP_SVersionDwnStart;
typedef struct LLRP_SVersionDwnStart
    LLRP_tSVersionDwnStart;

struct LLRP_SVersionDwnHeartbeatAck;
typedef struct LLRP_SVersionDwnHeartbeatAck
    LLRP_tSVersionDwnHeartbeatAck;

struct LLRP_SVersionDwnChipMsgAck;
typedef struct LLRP_SVersionDwnChipMsgAck
    LLRP_tSVersionDwnChipMsgAck;

struct LLRP_SVersionDwnAck;
typedef struct LLRP_SVersionDwnAck
    LLRP_tSVersionDwnAck;

struct LLRP_SRs485TestAck;
typedef struct LLRP_SRs485TestAck
    LLRP_tSRs485TestAck;

struct LLRP_SGpioTestAck;
typedef struct LLRP_SGpioTestAck
    LLRP_tSGpioTestAck;

struct LLRP_SAntSelectAck;
typedef struct LLRP_SAntSelectAck
    LLRP_tSAntSelectAck;

struct LLRP_SAntInPositonAck;
typedef struct LLRP_SAntInPositonAck
    LLRP_tSAntInPositonAck;

struct LLRP_SDelAlarmInfo;
typedef struct LLRP_SDelAlarmInfo
    LLRP_tSDelAlarmInfo;

struct LLRP_SDelAlarmAid;
typedef struct LLRP_SDelAlarmAid
    LLRP_tSDelAlarmAid;

struct LLRP_SSyncInfo;
typedef struct LLRP_SSyncInfo
    LLRP_tSSyncInfo;

struct LLRP_SSynAid;
typedef struct LLRP_SSynAid
    LLRP_tSSynAid;

struct LLRP_SAlarmReportInfo;
typedef struct LLRP_SAlarmReportInfo
    LLRP_tSAlarmReportInfo;

struct LLRP_SAlarmToBckgrd;
typedef struct LLRP_SAlarmToBckgrd
    LLRP_tSAlarmToBckgrd;

struct LLRP_SAlarmPID;
typedef struct LLRP_SAlarmPID
    LLRP_tSAlarmPID;

struct LLRP_SAlarmStruct;
typedef struct LLRP_SAlarmStruct
    LLRP_tSAlarmStruct;

struct LLRP_SAlarmSrcInfo;
typedef struct LLRP_SAlarmSrcInfo
    LLRP_tSAlarmSrcInfo;

struct LLRP_SSysSoftClock;
typedef struct LLRP_SSysSoftClock
    LLRP_tSSysSoftClock;

struct LLRP_SAlarmRestoreReportInfo;
typedef struct LLRP_SAlarmRestoreReportInfo
    LLRP_tSAlarmRestoreReportInfo;

struct LLRP_SRestoreToBckgrd;
typedef struct LLRP_SRestoreToBckgrd
    LLRP_tSRestoreToBckgrd;

struct LLRP_SInformReportInfo;
typedef struct LLRP_SInformReportInfo
    LLRP_tSInformReportInfo;

struct LLRP_SInformToUp;
typedef struct LLRP_SInformToUp
    LLRP_tSInformToUp;

struct LLRP_SReaderVerActivateAck;
typedef struct LLRP_SReaderVerActivateAck
    LLRP_tSReaderVerActivateAck;

struct LLRP_SVerInfoQueryAck;
typedef struct LLRP_SVerInfoQueryAck
    LLRP_tSVerInfoQueryAck;

struct LLRP_SVerInfo;
typedef struct LLRP_SVerInfo
    LLRP_tSVerInfo;

struct LLRP_SVersionDownloadRequest;
typedef struct LLRP_SVersionDownloadRequest
    LLRP_tSVersionDownloadRequest;

struct LLRP_SSubVersionInfo;
typedef struct LLRP_SSubVersionInfo
    LLRP_tSSubVersionInfo;

struct LLRP_SVersionDownloadRequestAck;
typedef struct LLRP_SVersionDownloadRequestAck
    LLRP_tSVersionDownloadRequestAck;

struct LLRP_SBasicVerInfo;
typedef struct LLRP_SBasicVerInfo
    LLRP_tSBasicVerInfo;

struct LLRP_SBasicVerInfoSelect;
typedef struct LLRP_SBasicVerInfoSelect
    LLRP_tSBasicVerInfoSelect;

struct LLRP_SReaderVerDownload;
typedef struct LLRP_SReaderVerDownload
    LLRP_tSReaderVerDownload;

struct LLRP_SReaderVerDownloadFile;
typedef struct LLRP_SReaderVerDownloadFile
    LLRP_tSReaderVerDownloadFile;

struct LLRP_SVersionDownloadAck;
typedef struct LLRP_SVersionDownloadAck
    LLRP_tSVersionDownloadAck;

struct LLRP_SSPVerInfoQueryResponse;
typedef struct LLRP_SSPVerInfoQueryResponse
    LLRP_tSSPVerInfoQueryResponse;

struct LLRP_SSPVerInfo;
typedef struct LLRP_SSPVerInfo
    LLRP_tSSPVerInfo;

struct LLRP_SReaderRunLog;
typedef struct LLRP_SReaderRunLog
    LLRP_tSReaderRunLog;

struct LLRP_SReaderRunException;
typedef struct LLRP_SReaderRunException
    LLRP_tSReaderRunException;

struct LLRP_SRUPReaderRunLog;
typedef struct LLRP_SRUPReaderRunLog
    LLRP_tSRUPReaderRunLog;

struct LLRP_SRUPReaderRunException;
typedef struct LLRP_SRUPReaderRunException
    LLRP_tSRUPReaderRunException;

struct LLRP_SLogicCardCmd;
typedef struct LLRP_SLogicCardCmd
    LLRP_tSLogicCardCmd;

struct LLRP_SLogicCardRsp;
typedef struct LLRP_SLogicCardRsp
    LLRP_tSLogicCardRsp;

struct LLRP_SCpuCardCmd;
typedef struct LLRP_SCpuCardCmd
    LLRP_tSCpuCardCmd;

struct LLRP_SDeviceCmd;
typedef struct LLRP_SDeviceCmd
    LLRP_tSDeviceCmd;

struct LLRP_SCardResetCmd;
typedef struct LLRP_SCardResetCmd
    LLRP_tSCardResetCmd;

struct LLRP_SCardResetRsp;
typedef struct LLRP_SCardResetRsp
    LLRP_tSCardResetRsp;

struct LLRP_SLowLevelCmd;
typedef struct LLRP_SLowLevelCmd
    LLRP_tSLowLevelCmd;

struct LLRP_SLowLevelRsp;
typedef struct LLRP_SLowLevelRsp
    LLRP_tSLowLevelRsp;

struct LLRP_SBroadCastTimeCmd;
typedef struct LLRP_SBroadCastTimeCmd
    LLRP_tSBroadCastTimeCmd;

struct LLRP_SAlarmCmd;
typedef struct LLRP_SAlarmCmd
    LLRP_tSAlarmCmd;

struct LLRP_SIDRsp;
typedef struct LLRP_SIDRsp
    LLRP_tSIDRsp;

struct LLRP_SInitKey;
typedef struct LLRP_SInitKey
    LLRP_tSInitKey;

struct LLRP_SInitKeyAck;
typedef struct LLRP_SInitKeyAck
    LLRP_tSInitKeyAck;

struct LLRP_SDeviceCmdArray;
typedef struct LLRP_SDeviceCmdArray
    LLRP_tSDeviceCmdArray;

struct LLRP_SWiegandPLTCmd;
typedef struct LLRP_SWiegandPLTCmd
    LLRP_tSWiegandPLTCmd;

struct LLRP_SWiegandPLTResultCmd;
typedef struct LLRP_SWiegandPLTResultCmd
    LLRP_tSWiegandPLTResultCmd;

struct LLRP_STagSimpleTestReport;
typedef struct LLRP_STagSimpleTestReport
    LLRP_tSTagSimpleTestReport;

struct LLRP_SOnceInventoryStat;
typedef struct LLRP_SOnceInventoryStat
    LLRP_tSOnceInventoryStat;

struct LLRP_SSimpleC1G2ReadParameter;
typedef struct LLRP_SSimpleC1G2ReadParameter
    LLRP_tSSimpleC1G2ReadParameter;

struct LLRP_SSimpleISO6BReadParameter;
typedef struct LLRP_SSimpleISO6BReadParameter
    LLRP_tSSimpleISO6BReadParameter;

struct LLRP_SSimpleC1G2WriteParameter;
typedef struct LLRP_SSimpleC1G2WriteParameter
    LLRP_tSSimpleC1G2WriteParameter;

struct LLRP_SSimpleISO6BWriteParameter;
typedef struct LLRP_SSimpleISO6BWriteParameter
    LLRP_tSSimpleISO6BWriteParameter;

struct LLRP_STrackConfig;
typedef struct LLRP_STrackConfig
    LLRP_tSTrackConfig;

struct LLRP_SRunInfoConfig;
typedef struct LLRP_SRunInfoConfig
    LLRP_tSRunInfoConfig;

struct LLRP_SPwdIndexPara;
typedef struct LLRP_SPwdIndexPara
    LLRP_tSPwdIndexPara;


/*
 * Vendor descriptor declarations.
 */

extern const LLRP_tSVendorDescriptor
LLRP_vdesczte;


/*
 * Namespace descriptor declarations.
 */

extern const LLRP_tSNamespaceDescriptor
LLRP_nsdesczte;


/*
 * Enumeration definitions and declarations of
 * enumeration string tables.
 */


enum LLRP_EExtCapbilitiesType
{

    LLRP_ExtCapbilitiesType_All = 0,
    LLRP_ExtCapbilitiesType_General_Device_Capabilities = 1,
    LLRP_ExtCapbilitiesType_LLRP_Capabilities = 2,
    LLRP_ExtCapbilitiesType_Regulatory_Capabilities = 3,
    LLRP_ExtCapbilitiesType_Air_Protocol_LLRP_Capabilities = 4,
    LLRP_ExtCapbilitiesType_ExtRegulatory_Capabilities = 5,
    LLRP_ExtCapbilitiesType_ISO6BLLRP_Capabilities = 6,
    LLRP_ExtCapbilitiesType_Specification = 7,
    LLRP_ExtCapbilitiesType_ETCExtRegulatory = 61,
    LLRP_ExtCapbilitiesType_MPIExtRegulatory = 81,
};

typedef enum LLRP_EExtCapbilitiesType
    LLRP_tEExtCapbilitiesType;

extern const LLRP_tSEnumTableEntry
LLRP_estExtCapbilitiesType[];


enum LLRP_ECommCapbilitiesType
{

    LLRP_CommCapbilitiesType_All = 0,
    LLRP_CommCapbilitiesType_CommunicationCapabilities = 1,
    LLRP_CommCapbilitiesType_NTPServerCapabilities = 2,
    LLRP_CommCapbilitiesType_ReaderBasicInfo = 3,
};

typedef enum LLRP_ECommCapbilitiesType
    LLRP_tECommCapbilitiesType;

extern const LLRP_tSEnumTableEntry
LLRP_estCommCapbilitiesType[];


enum LLRP_EExtConfigType
{

    LLRP_ExtConfigType_All = 0,
    LLRP_ExtConfigType_Identification = 1,
    LLRP_ExtConfigType_AntennaProperties = 2,
    LLRP_ExtConfigType_AntennaConfiguration = 3,
    LLRP_ExtConfigType_ROReportSpec = 4,
    LLRP_ExtConfigType_ReaderEventNotificationSpec = 5,
    LLRP_ExtConfigType_AccessReportSpec = 6,
    LLRP_ExtConfigType_LLRPConfigurationStateValue = 7,
    LLRP_ExtConfigType_KeepaliveSpec = 8,
    LLRP_ExtConfigType_GPIPortCurrentState = 9,
    LLRP_ExtConfigType_GPOWriteData = 10,
    LLRP_ExtConfigType_EventsAndReports = 11,
    LLRP_ExtConfigType_UHFAntennaExtConfiguration = 12,
    LLRP_ExtConfigType_AlarmMask = 13,
    LLRP_ExtConfigType_ModuleDepth = 14,
    LLRP_ExtConfigType_IQConfig = 15,
    LLRP_ExtConfigType_LocationConfiguration = 16,
    LLRP_ExtConfigType_AntSwitchDelayCfg  = 18,
    LLRP_ExtConfigType_TagReportFilter = 19,
    LLRP_ExtConfigType_AntCoopCfg = 20,
    LLRP_ExtConfigType_RSSISortCfg = 21,
    LLRP_ExtConfigType_LeakCompensation = 22,
    LLRP_ExtConfigType_RecvDATT = 23,
    LLRP_ExtConfigType_LaneNum = 24,
    LLRP_ExtConfigType_RUPAlarmThreshold = 25,
    LLRP_ExtConfigType_ETCConfig = 61,
    LLRP_ExtConfigType_MPIAntennaConfiguration = 81,
    LLRP_ExtConfigType_MPIProperties = 82,
    LLRP_ExtConfigType_MPIPsamWhiteList = 83,
    LLRP_ExtConfigType_MPISIMWhiteList = 84,
    LLRP_ExtConfigType_MPIPsamAuthenticationFile = 85,
    LLRP_ExtConfigType_MPISMSCenterNo = 86,
};

typedef enum LLRP_EExtConfigType
    LLRP_tEExtConfigType;

extern const LLRP_tSEnumTableEntry
LLRP_estExtConfigType[];


enum LLRP_ECommConfigType
{

    LLRP_CommConfigType_All = 0,
    LLRP_CommConfigType_ReaderName = 1,
    LLRP_CommConfigType_RUPCommunicationConfiguration = 2,
    LLRP_CommConfigType_NTPConfiguration = 3,
    LLRP_CommConfigType_DeviceID = 4,
    LLRP_CommConfigType_LinkStateInfo = 5,
    LLRP_CommConfigType_SaveReportSwitch = 6,
};

typedef enum LLRP_ECommConfigType
    LLRP_tECommConfigType;

extern const LLRP_tSEnumTableEntry
LLRP_estCommConfigType[];


enum LLRP_EForandRevConfigType
{

    LLRP_ForandRevConfigType_Receive = 0,
    LLRP_ForandRevConfigType_Send = 1,
    LLRP_ForandRevConfigType_All_in_one = 2,
};

typedef enum LLRP_EForandRevConfigType
    LLRP_tEForandRevConfigType;

extern const LLRP_tSEnumTableEntry
LLRP_estForandRevConfigType[];


enum LLRP_EFreqHopType
{

    LLRP_FreqHopType_Sequence = 0,
    LLRP_FreqHopType_Random = 1,
    LLRP_FreqHopType_Step = 2,
};

typedef enum LLRP_EFreqHopType
    LLRP_tEFreqHopType;

extern const LLRP_tSEnumTableEntry
LLRP_estFreqHopType[];


enum LLRP_ELocationType
{

    LLRP_LocationType_Costom = 0,
    LLRP_LocationType_Gps = 1,
};

typedef enum LLRP_ELocationType
    LLRP_tELocationType;

extern const LLRP_tSEnumTableEntry
LLRP_estLocationType[];


enum LLRP_ELinkPhyType
{

    LLRP_LinkPhyType_ethernet = 0,
    LLRP_LinkPhyType_RS232 = 1,
    LLRP_LinkPhyType_RS485 = 2,
    LLRP_LinkPhyType_GPRS = 3,
    LLRP_LinkPhyType_Wlan = 4,
};

typedef enum LLRP_ELinkPhyType
    LLRP_tELinkPhyType;

extern const LLRP_tSEnumTableEntry
LLRP_estLinkPhyType[];


enum LLRP_EM_value_Type
{

    LLRP_M_value_Type_FM0 = 0,
    LLRP_M_value_Type_Miller = 1,
    LLRP_M_value_Type_Miller4 = 2,
    LLRP_M_value_Type_Miller8 = 3,
};

typedef enum LLRP_EM_value_Type
    LLRP_tEM_value_Type;

extern const LLRP_tSEnumTableEntry
LLRP_estM_value_Type[];


enum LLRP_EForward_link_Type
{

    LLRP_Forward_link_Type_PR_ASK = 0,
    LLRP_Forward_link_Type_SSB_ASK = 1,
    LLRP_Forward_link_Type_DSB_ASK = 2,
};

typedef enum LLRP_EForward_link_Type
    LLRP_tEForward_link_Type;

extern const LLRP_tSEnumTableEntry
LLRP_estForward_link_Type[];


enum LLRP_EConnWaysType
{

    LLRP_ConnWaysType_Auto = 0,
    LLRP_ConnWaysType_By_hand = 1,
    LLRP_ConnWaysType_On_data = 2,
    LLRP_ConnWaysType_Section = 3,
};

typedef enum LLRP_EConnWaysType
    LLRP_tEConnWaysType;

extern const LLRP_tSEnumTableEntry
LLRP_estConnWaysType[];


  
struct LLRP_SGET_READER_CAPABILITIES_EXT
{
    LLRP_tSMessage hdr;
  
    LLRP_tEExtCapbilitiesType eRequestedData;

  
    LLRP_tSParameter * listCustom;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdGET_READER_CAPABILITIES_EXT;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdGET_READER_CAPABILITIES_EXT[];

extern LLRP_tSGET_READER_CAPABILITIES_EXT *
LLRP_GET_READER_CAPABILITIES_EXT_construct (void);

extern void
LLRP_GET_READER_CAPABILITIES_EXT_destruct (
 LLRP_tSGET_READER_CAPABILITIES_EXT * pThis);

extern void
LLRP_GET_READER_CAPABILITIES_EXT_decodeFields (
 LLRP_tSGET_READER_CAPABILITIES_EXT * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_GET_READER_CAPABILITIES_EXT_assimilateSubParameters (
 LLRP_tSGET_READER_CAPABILITIES_EXT * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_GET_READER_CAPABILITIES_EXT_encode (
  const LLRP_tSGET_READER_CAPABILITIES_EXT *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdGET_READER_CAPABILITIES_EXT_RequestedData;

extern LLRP_tEExtCapbilitiesType
LLRP_GET_READER_CAPABILITIES_EXT_getRequestedData (
  LLRP_tSGET_READER_CAPABILITIES_EXT *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_CAPABILITIES_EXT_setRequestedData (
  LLRP_tSGET_READER_CAPABILITIES_EXT *pThis,
  LLRP_tEExtCapbilitiesType Value);

  
extern LLRP_tSParameter *
LLRP_GET_READER_CAPABILITIES_EXT_beginCustom (
  LLRP_tSGET_READER_CAPABILITIES_EXT *pThis);

extern LLRP_tSParameter *
LLRP_GET_READER_CAPABILITIES_EXT_nextCustom (
  LLRP_tSParameter *pCurrent);

extern void
LLRP_GET_READER_CAPABILITIES_EXT_clearCustom (
  LLRP_tSGET_READER_CAPABILITIES_EXT *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_CAPABILITIES_EXT_addCustom (
  LLRP_tSGET_READER_CAPABILITIES_EXT *pThis,
  LLRP_tSParameter *pValue);




  
struct LLRP_SGET_READER_CAPABILITIES_EXT_RESPONSE
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSLLRPStatus * pLLRPStatus;

    LLRP_tSGeneralDeviceCapabilities * pGeneralDeviceCapabilities;

    LLRP_tSLLRPCapabilities * pLLRPCapabilities;

    LLRP_tSRegulatoryCapabilities * pRegulatoryCapabilities;

    LLRP_tSParameter * pAirProtocolLLRPCapabilities;

    LLRP_tSExtRegulatoryCapabilities * pExtRegulatoryCapabilities;

    LLRP_tSISO6BLLRPCapabilities * pISO6BLLRPCapabilities;

    LLRP_tSSpecification * pSpecification;

    LLRP_tSETCExtRegulatoryCapabilities * pETCExtRegulatoryCapabilities;

    LLRP_tSMPIExtRegulatoryCapabilities * pMPIExtRegulatoryCapabilities;

    LLRP_tSParameter * listCustom;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdGET_READER_CAPABILITIES_EXT_RESPONSE;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdGET_READER_CAPABILITIES_EXT_RESPONSE[];

extern LLRP_tSGET_READER_CAPABILITIES_EXT_RESPONSE *
LLRP_GET_READER_CAPABILITIES_EXT_RESPONSE_construct (void);

extern void
LLRP_GET_READER_CAPABILITIES_EXT_RESPONSE_destruct (
 LLRP_tSGET_READER_CAPABILITIES_EXT_RESPONSE * pThis);

extern void
LLRP_GET_READER_CAPABILITIES_EXT_RESPONSE_decodeFields (
 LLRP_tSGET_READER_CAPABILITIES_EXT_RESPONSE * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_GET_READER_CAPABILITIES_EXT_RESPONSE_assimilateSubParameters (
 LLRP_tSGET_READER_CAPABILITIES_EXT_RESPONSE * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_GET_READER_CAPABILITIES_EXT_RESPONSE_encode (
  const LLRP_tSGET_READER_CAPABILITIES_EXT_RESPONSE *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSLLRPStatus *
LLRP_GET_READER_CAPABILITIES_EXT_RESPONSE_getLLRPStatus (
  LLRP_tSGET_READER_CAPABILITIES_EXT_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_CAPABILITIES_EXT_RESPONSE_setLLRPStatus (
  LLRP_tSGET_READER_CAPABILITIES_EXT_RESPONSE *pThis,
  LLRP_tSLLRPStatus *pValue);

extern LLRP_tSGeneralDeviceCapabilities *
LLRP_GET_READER_CAPABILITIES_EXT_RESPONSE_getGeneralDeviceCapabilities (
  LLRP_tSGET_READER_CAPABILITIES_EXT_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_CAPABILITIES_EXT_RESPONSE_setGeneralDeviceCapabilities (
  LLRP_tSGET_READER_CAPABILITIES_EXT_RESPONSE *pThis,
  LLRP_tSGeneralDeviceCapabilities *pValue);

extern LLRP_tSLLRPCapabilities *
LLRP_GET_READER_CAPABILITIES_EXT_RESPONSE_getLLRPCapabilities (
  LLRP_tSGET_READER_CAPABILITIES_EXT_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_CAPABILITIES_EXT_RESPONSE_setLLRPCapabilities (
  LLRP_tSGET_READER_CAPABILITIES_EXT_RESPONSE *pThis,
  LLRP_tSLLRPCapabilities *pValue);

extern LLRP_tSRegulatoryCapabilities *
LLRP_GET_READER_CAPABILITIES_EXT_RESPONSE_getRegulatoryCapabilities (
  LLRP_tSGET_READER_CAPABILITIES_EXT_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_CAPABILITIES_EXT_RESPONSE_setRegulatoryCapabilities (
  LLRP_tSGET_READER_CAPABILITIES_EXT_RESPONSE *pThis,
  LLRP_tSRegulatoryCapabilities *pValue);

extern LLRP_tSParameter *
LLRP_GET_READER_CAPABILITIES_EXT_RESPONSE_getAirProtocolLLRPCapabilities (
  LLRP_tSGET_READER_CAPABILITIES_EXT_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_CAPABILITIES_EXT_RESPONSE_setAirProtocolLLRPCapabilities (
  LLRP_tSGET_READER_CAPABILITIES_EXT_RESPONSE *pThis,
  LLRP_tSParameter *pValue);

extern LLRP_tSExtRegulatoryCapabilities *
LLRP_GET_READER_CAPABILITIES_EXT_RESPONSE_getExtRegulatoryCapabilities (
  LLRP_tSGET_READER_CAPABILITIES_EXT_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_CAPABILITIES_EXT_RESPONSE_setExtRegulatoryCapabilities (
  LLRP_tSGET_READER_CAPABILITIES_EXT_RESPONSE *pThis,
  LLRP_tSExtRegulatoryCapabilities *pValue);

extern LLRP_tSISO6BLLRPCapabilities *
LLRP_GET_READER_CAPABILITIES_EXT_RESPONSE_getISO6BLLRPCapabilities (
  LLRP_tSGET_READER_CAPABILITIES_EXT_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_CAPABILITIES_EXT_RESPONSE_setISO6BLLRPCapabilities (
  LLRP_tSGET_READER_CAPABILITIES_EXT_RESPONSE *pThis,
  LLRP_tSISO6BLLRPCapabilities *pValue);

extern LLRP_tSSpecification *
LLRP_GET_READER_CAPABILITIES_EXT_RESPONSE_getSpecification (
  LLRP_tSGET_READER_CAPABILITIES_EXT_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_CAPABILITIES_EXT_RESPONSE_setSpecification (
  LLRP_tSGET_READER_CAPABILITIES_EXT_RESPONSE *pThis,
  LLRP_tSSpecification *pValue);

extern LLRP_tSETCExtRegulatoryCapabilities *
LLRP_GET_READER_CAPABILITIES_EXT_RESPONSE_getETCExtRegulatoryCapabilities (
  LLRP_tSGET_READER_CAPABILITIES_EXT_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_CAPABILITIES_EXT_RESPONSE_setETCExtRegulatoryCapabilities (
  LLRP_tSGET_READER_CAPABILITIES_EXT_RESPONSE *pThis,
  LLRP_tSETCExtRegulatoryCapabilities *pValue);

extern LLRP_tSMPIExtRegulatoryCapabilities *
LLRP_GET_READER_CAPABILITIES_EXT_RESPONSE_getMPIExtRegulatoryCapabilities (
  LLRP_tSGET_READER_CAPABILITIES_EXT_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_CAPABILITIES_EXT_RESPONSE_setMPIExtRegulatoryCapabilities (
  LLRP_tSGET_READER_CAPABILITIES_EXT_RESPONSE *pThis,
  LLRP_tSMPIExtRegulatoryCapabilities *pValue);

extern LLRP_tSParameter *
LLRP_GET_READER_CAPABILITIES_EXT_RESPONSE_beginCustom (
  LLRP_tSGET_READER_CAPABILITIES_EXT_RESPONSE *pThis);

extern LLRP_tSParameter *
LLRP_GET_READER_CAPABILITIES_EXT_RESPONSE_nextCustom (
  LLRP_tSParameter *pCurrent);

extern void
LLRP_GET_READER_CAPABILITIES_EXT_RESPONSE_clearCustom (
  LLRP_tSGET_READER_CAPABILITIES_EXT_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_CAPABILITIES_EXT_RESPONSE_addCustom (
  LLRP_tSGET_READER_CAPABILITIES_EXT_RESPONSE *pThis,
  LLRP_tSParameter *pValue);




  
struct LLRP_SGET_READER_COMM_CAPABILITIES
{
    LLRP_tSMessage hdr;
  
    LLRP_tECommCapbilitiesType eRequestedData;

  
    LLRP_tSParameter * listCustom;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdGET_READER_COMM_CAPABILITIES;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdGET_READER_COMM_CAPABILITIES[];

extern LLRP_tSGET_READER_COMM_CAPABILITIES *
LLRP_GET_READER_COMM_CAPABILITIES_construct (void);

extern void
LLRP_GET_READER_COMM_CAPABILITIES_destruct (
 LLRP_tSGET_READER_COMM_CAPABILITIES * pThis);

extern void
LLRP_GET_READER_COMM_CAPABILITIES_decodeFields (
 LLRP_tSGET_READER_COMM_CAPABILITIES * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_GET_READER_COMM_CAPABILITIES_assimilateSubParameters (
 LLRP_tSGET_READER_COMM_CAPABILITIES * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_GET_READER_COMM_CAPABILITIES_encode (
  const LLRP_tSGET_READER_COMM_CAPABILITIES *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdGET_READER_COMM_CAPABILITIES_RequestedData;

extern LLRP_tECommCapbilitiesType
LLRP_GET_READER_COMM_CAPABILITIES_getRequestedData (
  LLRP_tSGET_READER_COMM_CAPABILITIES *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_COMM_CAPABILITIES_setRequestedData (
  LLRP_tSGET_READER_COMM_CAPABILITIES *pThis,
  LLRP_tECommCapbilitiesType Value);

  
extern LLRP_tSParameter *
LLRP_GET_READER_COMM_CAPABILITIES_beginCustom (
  LLRP_tSGET_READER_COMM_CAPABILITIES *pThis);

extern LLRP_tSParameter *
LLRP_GET_READER_COMM_CAPABILITIES_nextCustom (
  LLRP_tSParameter *pCurrent);

extern void
LLRP_GET_READER_COMM_CAPABILITIES_clearCustom (
  LLRP_tSGET_READER_COMM_CAPABILITIES *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_COMM_CAPABILITIES_addCustom (
  LLRP_tSGET_READER_COMM_CAPABILITIES *pThis,
  LLRP_tSParameter *pValue);




  
struct LLRP_SGET_READER_COMM_CAPABILITIES_RESPONSE
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSLLRPStatus * pLLRPStatus;

    LLRP_tSCommunicationCapabilities * pCommunicationCapabilities;

    LLRP_tSRUPCommunicationCapabilities * pRUPCommunicationCapabilities;

    LLRP_tSNTPServerCapabilities * pNTPServerCapabilities;

    LLRP_tSReaderBasicInfo * pReaderBasicInfo;

    LLRP_tSParameter * listCustom;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdGET_READER_COMM_CAPABILITIES_RESPONSE;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdGET_READER_COMM_CAPABILITIES_RESPONSE[];

extern LLRP_tSGET_READER_COMM_CAPABILITIES_RESPONSE *
LLRP_GET_READER_COMM_CAPABILITIES_RESPONSE_construct (void);

extern void
LLRP_GET_READER_COMM_CAPABILITIES_RESPONSE_destruct (
 LLRP_tSGET_READER_COMM_CAPABILITIES_RESPONSE * pThis);

extern void
LLRP_GET_READER_COMM_CAPABILITIES_RESPONSE_decodeFields (
 LLRP_tSGET_READER_COMM_CAPABILITIES_RESPONSE * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_GET_READER_COMM_CAPABILITIES_RESPONSE_assimilateSubParameters (
 LLRP_tSGET_READER_COMM_CAPABILITIES_RESPONSE * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_GET_READER_COMM_CAPABILITIES_RESPONSE_encode (
  const LLRP_tSGET_READER_COMM_CAPABILITIES_RESPONSE *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSLLRPStatus *
LLRP_GET_READER_COMM_CAPABILITIES_RESPONSE_getLLRPStatus (
  LLRP_tSGET_READER_COMM_CAPABILITIES_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_COMM_CAPABILITIES_RESPONSE_setLLRPStatus (
  LLRP_tSGET_READER_COMM_CAPABILITIES_RESPONSE *pThis,
  LLRP_tSLLRPStatus *pValue);

extern LLRP_tSCommunicationCapabilities *
LLRP_GET_READER_COMM_CAPABILITIES_RESPONSE_getCommunicationCapabilities (
  LLRP_tSGET_READER_COMM_CAPABILITIES_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_COMM_CAPABILITIES_RESPONSE_setCommunicationCapabilities (
  LLRP_tSGET_READER_COMM_CAPABILITIES_RESPONSE *pThis,
  LLRP_tSCommunicationCapabilities *pValue);

extern LLRP_tSRUPCommunicationCapabilities *
LLRP_GET_READER_COMM_CAPABILITIES_RESPONSE_getRUPCommunicationCapabilities (
  LLRP_tSGET_READER_COMM_CAPABILITIES_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_COMM_CAPABILITIES_RESPONSE_setRUPCommunicationCapabilities (
  LLRP_tSGET_READER_COMM_CAPABILITIES_RESPONSE *pThis,
  LLRP_tSRUPCommunicationCapabilities *pValue);

extern LLRP_tSNTPServerCapabilities *
LLRP_GET_READER_COMM_CAPABILITIES_RESPONSE_getNTPServerCapabilities (
  LLRP_tSGET_READER_COMM_CAPABILITIES_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_COMM_CAPABILITIES_RESPONSE_setNTPServerCapabilities (
  LLRP_tSGET_READER_COMM_CAPABILITIES_RESPONSE *pThis,
  LLRP_tSNTPServerCapabilities *pValue);

extern LLRP_tSReaderBasicInfo *
LLRP_GET_READER_COMM_CAPABILITIES_RESPONSE_getReaderBasicInfo (
  LLRP_tSGET_READER_COMM_CAPABILITIES_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_COMM_CAPABILITIES_RESPONSE_setReaderBasicInfo (
  LLRP_tSGET_READER_COMM_CAPABILITIES_RESPONSE *pThis,
  LLRP_tSReaderBasicInfo *pValue);

extern LLRP_tSParameter *
LLRP_GET_READER_COMM_CAPABILITIES_RESPONSE_beginCustom (
  LLRP_tSGET_READER_COMM_CAPABILITIES_RESPONSE *pThis);

extern LLRP_tSParameter *
LLRP_GET_READER_COMM_CAPABILITIES_RESPONSE_nextCustom (
  LLRP_tSParameter *pCurrent);

extern void
LLRP_GET_READER_COMM_CAPABILITIES_RESPONSE_clearCustom (
  LLRP_tSGET_READER_COMM_CAPABILITIES_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_COMM_CAPABILITIES_RESPONSE_addCustom (
  LLRP_tSGET_READER_COMM_CAPABILITIES_RESPONSE *pThis,
  LLRP_tSParameter *pValue);




  
struct LLRP_SGET_READER_CONFIG_EXT
{
    LLRP_tSMessage hdr;
  
    LLRP_tEExtConfigType eRequestedData;

    llrp_u16_t AntennaID;

    llrp_u16_t GPIPortNum;

    llrp_u16_t GPOPortNum;

  
    LLRP_tSParameter * listCustom;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdGET_READER_CONFIG_EXT;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdGET_READER_CONFIG_EXT[];

extern LLRP_tSGET_READER_CONFIG_EXT *
LLRP_GET_READER_CONFIG_EXT_construct (void);

extern void
LLRP_GET_READER_CONFIG_EXT_destruct (
 LLRP_tSGET_READER_CONFIG_EXT * pThis);

extern void
LLRP_GET_READER_CONFIG_EXT_decodeFields (
 LLRP_tSGET_READER_CONFIG_EXT * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_GET_READER_CONFIG_EXT_assimilateSubParameters (
 LLRP_tSGET_READER_CONFIG_EXT * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_GET_READER_CONFIG_EXT_encode (
  const LLRP_tSGET_READER_CONFIG_EXT *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdGET_READER_CONFIG_EXT_RequestedData;

extern LLRP_tEExtConfigType
LLRP_GET_READER_CONFIG_EXT_getRequestedData (
  LLRP_tSGET_READER_CONFIG_EXT *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_CONFIG_EXT_setRequestedData (
  LLRP_tSGET_READER_CONFIG_EXT *pThis,
  LLRP_tEExtConfigType Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdGET_READER_CONFIG_EXT_AntennaID;

extern llrp_u16_t
LLRP_GET_READER_CONFIG_EXT_getAntennaID (
  LLRP_tSGET_READER_CONFIG_EXT *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_CONFIG_EXT_setAntennaID (
  LLRP_tSGET_READER_CONFIG_EXT *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdGET_READER_CONFIG_EXT_GPIPortNum;

extern llrp_u16_t
LLRP_GET_READER_CONFIG_EXT_getGPIPortNum (
  LLRP_tSGET_READER_CONFIG_EXT *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_CONFIG_EXT_setGPIPortNum (
  LLRP_tSGET_READER_CONFIG_EXT *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdGET_READER_CONFIG_EXT_GPOPortNum;

extern llrp_u16_t
LLRP_GET_READER_CONFIG_EXT_getGPOPortNum (
  LLRP_tSGET_READER_CONFIG_EXT *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_CONFIG_EXT_setGPOPortNum (
  LLRP_tSGET_READER_CONFIG_EXT *pThis,
  llrp_u16_t Value);

  
extern LLRP_tSParameter *
LLRP_GET_READER_CONFIG_EXT_beginCustom (
  LLRP_tSGET_READER_CONFIG_EXT *pThis);

extern LLRP_tSParameter *
LLRP_GET_READER_CONFIG_EXT_nextCustom (
  LLRP_tSParameter *pCurrent);

extern void
LLRP_GET_READER_CONFIG_EXT_clearCustom (
  LLRP_tSGET_READER_CONFIG_EXT *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_CONFIG_EXT_addCustom (
  LLRP_tSGET_READER_CONFIG_EXT *pThis,
  LLRP_tSParameter *pValue);




  
struct LLRP_SGET_READER_CONFIG_EXT_RESPONSE
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSLLRPStatus * pLLRPStatus;

    LLRP_tSLLRPConfigurationStateValue * pLLRPConfigurationStateValue;

    LLRP_tSReaderEventNotificationSpec * pReaderEventNotificationSpec;

    LLRP_tSAntennaProperties * listAntennaProperties;

    LLRP_tSAntennaConfiguration * listAntennaConfiguration;

    LLRP_tSUHFAntennaExtConfiguration * listUHFAntennaExtConfiguration;

    LLRP_tSROReportSpec * pROReportSpec;

    LLRP_tSAccessReportSpec * pAccessReportSpec;

    LLRP_tSIdentification * pIdentification;

    LLRP_tSKeepaliveSpec * pKeepaliveSpec;

    LLRP_tSGPIPortCurrentState * listGPIPortCurrentState;

    LLRP_tSGPOWriteData * listGPOWriteData;

    LLRP_tSEventsAndReports * pEventsAndReports;

    LLRP_tSAntennaExtConfiguration * listAntennaExtConfiguration;

    LLRP_tSAlarmMask * pAlarmMask;

    LLRP_tSModuleDepth * pModuleDepth;

    LLRP_tSIQConfig * pIQConfig;

    LLRP_tSLocationConfiguration * pLocationConfiguration;

    LLRP_tSCustomPrivateConfigData * pCustomPrivateConfigData;

    LLRP_tSAntSwitchDelayCfg * pAntSwitchDelayCfg;

    LLRP_tSTagReportFilter * pTagReportFilter;

    LLRP_tSAntCoopCfg * pAntCoopCfg;

    LLRP_tSRSSISortCfg * pRSSISortCfg;

    LLRP_tSLeakCompensation * pLeakCompensation;

    LLRP_tSRecvDATT * pRecvDATT;

    LLRP_tSLaneNum * pLaneNum;

    LLRP_tSAlarmThreshodCfg * pAlarmThreshodCfg;

    LLRP_tSRUPAlarmThreshold * pRUPAlarmThreshold;

    LLRP_tSETCConfig * pETCConfig;

    LLRP_tSMPIAntennaConfiguration * listMPIAntennaConfiguration;

    LLRP_tSMPIProperties * pMPIProperties;

    LLRP_tSMPIPsamWhiteList * pMPIPsamWhiteList;

    LLRP_tSMPISIMWhiteList * pMPISIMWhiteList;

    LLRP_tSMPIPsamAuthenticationFile * pMPIPsamAuthenticationFile;

    LLRP_tSMPISMSCenterNo * pMPISMSCenterNo;

    LLRP_tSParameter * listCustom;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdGET_READER_CONFIG_EXT_RESPONSE;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdGET_READER_CONFIG_EXT_RESPONSE[];

extern LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *
LLRP_GET_READER_CONFIG_EXT_RESPONSE_construct (void);

extern void
LLRP_GET_READER_CONFIG_EXT_RESPONSE_destruct (
 LLRP_tSGET_READER_CONFIG_EXT_RESPONSE * pThis);

extern void
LLRP_GET_READER_CONFIG_EXT_RESPONSE_decodeFields (
 LLRP_tSGET_READER_CONFIG_EXT_RESPONSE * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_GET_READER_CONFIG_EXT_RESPONSE_assimilateSubParameters (
 LLRP_tSGET_READER_CONFIG_EXT_RESPONSE * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_GET_READER_CONFIG_EXT_RESPONSE_encode (
  const LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSLLRPStatus *
LLRP_GET_READER_CONFIG_EXT_RESPONSE_getLLRPStatus (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_CONFIG_EXT_RESPONSE_setLLRPStatus (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis,
  LLRP_tSLLRPStatus *pValue);

extern LLRP_tSLLRPConfigurationStateValue *
LLRP_GET_READER_CONFIG_EXT_RESPONSE_getLLRPConfigurationStateValue (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_CONFIG_EXT_RESPONSE_setLLRPConfigurationStateValue (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis,
  LLRP_tSLLRPConfigurationStateValue *pValue);

extern LLRP_tSReaderEventNotificationSpec *
LLRP_GET_READER_CONFIG_EXT_RESPONSE_getReaderEventNotificationSpec (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_CONFIG_EXT_RESPONSE_setReaderEventNotificationSpec (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis,
  LLRP_tSReaderEventNotificationSpec *pValue);

extern LLRP_tSAntennaProperties *
LLRP_GET_READER_CONFIG_EXT_RESPONSE_beginAntennaProperties (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis);

extern LLRP_tSAntennaProperties *
LLRP_GET_READER_CONFIG_EXT_RESPONSE_nextAntennaProperties (
  LLRP_tSAntennaProperties *pCurrent);

extern void
LLRP_GET_READER_CONFIG_EXT_RESPONSE_clearAntennaProperties (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_CONFIG_EXT_RESPONSE_addAntennaProperties (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis,
  LLRP_tSAntennaProperties *pValue);


extern LLRP_tSAntennaConfiguration *
LLRP_GET_READER_CONFIG_EXT_RESPONSE_beginAntennaConfiguration (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis);

extern LLRP_tSAntennaConfiguration *
LLRP_GET_READER_CONFIG_EXT_RESPONSE_nextAntennaConfiguration (
  LLRP_tSAntennaConfiguration *pCurrent);

extern void
LLRP_GET_READER_CONFIG_EXT_RESPONSE_clearAntennaConfiguration (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_CONFIG_EXT_RESPONSE_addAntennaConfiguration (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis,
  LLRP_tSAntennaConfiguration *pValue);


extern LLRP_tSUHFAntennaExtConfiguration *
LLRP_GET_READER_CONFIG_EXT_RESPONSE_beginUHFAntennaExtConfiguration (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis);

extern LLRP_tSUHFAntennaExtConfiguration *
LLRP_GET_READER_CONFIG_EXT_RESPONSE_nextUHFAntennaExtConfiguration (
  LLRP_tSUHFAntennaExtConfiguration *pCurrent);

extern void
LLRP_GET_READER_CONFIG_EXT_RESPONSE_clearUHFAntennaExtConfiguration (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_CONFIG_EXT_RESPONSE_addUHFAntennaExtConfiguration (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis,
  LLRP_tSUHFAntennaExtConfiguration *pValue);


extern LLRP_tSROReportSpec *
LLRP_GET_READER_CONFIG_EXT_RESPONSE_getROReportSpec (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_CONFIG_EXT_RESPONSE_setROReportSpec (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis,
  LLRP_tSROReportSpec *pValue);

extern LLRP_tSAccessReportSpec *
LLRP_GET_READER_CONFIG_EXT_RESPONSE_getAccessReportSpec (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_CONFIG_EXT_RESPONSE_setAccessReportSpec (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis,
  LLRP_tSAccessReportSpec *pValue);

extern LLRP_tSIdentification *
LLRP_GET_READER_CONFIG_EXT_RESPONSE_getIdentification (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_CONFIG_EXT_RESPONSE_setIdentification (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis,
  LLRP_tSIdentification *pValue);

extern LLRP_tSKeepaliveSpec *
LLRP_GET_READER_CONFIG_EXT_RESPONSE_getKeepaliveSpec (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_CONFIG_EXT_RESPONSE_setKeepaliveSpec (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis,
  LLRP_tSKeepaliveSpec *pValue);

extern LLRP_tSGPIPortCurrentState *
LLRP_GET_READER_CONFIG_EXT_RESPONSE_beginGPIPortCurrentState (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis);

extern LLRP_tSGPIPortCurrentState *
LLRP_GET_READER_CONFIG_EXT_RESPONSE_nextGPIPortCurrentState (
  LLRP_tSGPIPortCurrentState *pCurrent);

extern void
LLRP_GET_READER_CONFIG_EXT_RESPONSE_clearGPIPortCurrentState (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_CONFIG_EXT_RESPONSE_addGPIPortCurrentState (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis,
  LLRP_tSGPIPortCurrentState *pValue);


extern LLRP_tSGPOWriteData *
LLRP_GET_READER_CONFIG_EXT_RESPONSE_beginGPOWriteData (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis);

extern LLRP_tSGPOWriteData *
LLRP_GET_READER_CONFIG_EXT_RESPONSE_nextGPOWriteData (
  LLRP_tSGPOWriteData *pCurrent);

extern void
LLRP_GET_READER_CONFIG_EXT_RESPONSE_clearGPOWriteData (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_CONFIG_EXT_RESPONSE_addGPOWriteData (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis,
  LLRP_tSGPOWriteData *pValue);


extern LLRP_tSEventsAndReports *
LLRP_GET_READER_CONFIG_EXT_RESPONSE_getEventsAndReports (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_CONFIG_EXT_RESPONSE_setEventsAndReports (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis,
  LLRP_tSEventsAndReports *pValue);

extern LLRP_tSAntennaExtConfiguration *
LLRP_GET_READER_CONFIG_EXT_RESPONSE_beginAntennaExtConfiguration (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis);

extern LLRP_tSAntennaExtConfiguration *
LLRP_GET_READER_CONFIG_EXT_RESPONSE_nextAntennaExtConfiguration (
  LLRP_tSAntennaExtConfiguration *pCurrent);

extern void
LLRP_GET_READER_CONFIG_EXT_RESPONSE_clearAntennaExtConfiguration (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_CONFIG_EXT_RESPONSE_addAntennaExtConfiguration (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis,
  LLRP_tSAntennaExtConfiguration *pValue);


extern LLRP_tSAlarmMask *
LLRP_GET_READER_CONFIG_EXT_RESPONSE_getAlarmMask (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_CONFIG_EXT_RESPONSE_setAlarmMask (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis,
  LLRP_tSAlarmMask *pValue);

extern LLRP_tSModuleDepth *
LLRP_GET_READER_CONFIG_EXT_RESPONSE_getModuleDepth (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_CONFIG_EXT_RESPONSE_setModuleDepth (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis,
  LLRP_tSModuleDepth *pValue);

extern LLRP_tSIQConfig *
LLRP_GET_READER_CONFIG_EXT_RESPONSE_getIQConfig (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_CONFIG_EXT_RESPONSE_setIQConfig (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis,
  LLRP_tSIQConfig *pValue);

extern LLRP_tSLocationConfiguration *
LLRP_GET_READER_CONFIG_EXT_RESPONSE_getLocationConfiguration (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_CONFIG_EXT_RESPONSE_setLocationConfiguration (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis,
  LLRP_tSLocationConfiguration *pValue);

extern LLRP_tSCustomPrivateConfigData *
LLRP_GET_READER_CONFIG_EXT_RESPONSE_getCustomPrivateConfigData (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_CONFIG_EXT_RESPONSE_setCustomPrivateConfigData (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis,
  LLRP_tSCustomPrivateConfigData *pValue);

extern LLRP_tSAntSwitchDelayCfg *
LLRP_GET_READER_CONFIG_EXT_RESPONSE_getAntSwitchDelayCfg (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_CONFIG_EXT_RESPONSE_setAntSwitchDelayCfg (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis,
  LLRP_tSAntSwitchDelayCfg *pValue);

extern LLRP_tSTagReportFilter *
LLRP_GET_READER_CONFIG_EXT_RESPONSE_getTagReportFilter (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_CONFIG_EXT_RESPONSE_setTagReportFilter (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis,
  LLRP_tSTagReportFilter *pValue);

extern LLRP_tSAntCoopCfg *
LLRP_GET_READER_CONFIG_EXT_RESPONSE_getAntCoopCfg (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_CONFIG_EXT_RESPONSE_setAntCoopCfg (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis,
  LLRP_tSAntCoopCfg *pValue);

extern LLRP_tSRSSISortCfg *
LLRP_GET_READER_CONFIG_EXT_RESPONSE_getRSSISortCfg (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_CONFIG_EXT_RESPONSE_setRSSISortCfg (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis,
  LLRP_tSRSSISortCfg *pValue);

extern LLRP_tSLeakCompensation *
LLRP_GET_READER_CONFIG_EXT_RESPONSE_getLeakCompensation (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_CONFIG_EXT_RESPONSE_setLeakCompensation (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis,
  LLRP_tSLeakCompensation *pValue);

extern LLRP_tSRecvDATT *
LLRP_GET_READER_CONFIG_EXT_RESPONSE_getRecvDATT (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_CONFIG_EXT_RESPONSE_setRecvDATT (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis,
  LLRP_tSRecvDATT *pValue);

extern LLRP_tSLaneNum *
LLRP_GET_READER_CONFIG_EXT_RESPONSE_getLaneNum (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_CONFIG_EXT_RESPONSE_setLaneNum (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis,
  LLRP_tSLaneNum *pValue);

extern LLRP_tSAlarmThreshodCfg *
LLRP_GET_READER_CONFIG_EXT_RESPONSE_getAlarmThreshodCfg (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_CONFIG_EXT_RESPONSE_setAlarmThreshodCfg (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis,
  LLRP_tSAlarmThreshodCfg *pValue);

extern LLRP_tSRUPAlarmThreshold *
LLRP_GET_READER_CONFIG_EXT_RESPONSE_getRUPAlarmThreshold (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_CONFIG_EXT_RESPONSE_setRUPAlarmThreshold (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis,
  LLRP_tSRUPAlarmThreshold *pValue);

extern LLRP_tSETCConfig *
LLRP_GET_READER_CONFIG_EXT_RESPONSE_getETCConfig (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_CONFIG_EXT_RESPONSE_setETCConfig (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis,
  LLRP_tSETCConfig *pValue);

extern LLRP_tSMPIAntennaConfiguration *
LLRP_GET_READER_CONFIG_EXT_RESPONSE_beginMPIAntennaConfiguration (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis);

extern LLRP_tSMPIAntennaConfiguration *
LLRP_GET_READER_CONFIG_EXT_RESPONSE_nextMPIAntennaConfiguration (
  LLRP_tSMPIAntennaConfiguration *pCurrent);

extern void
LLRP_GET_READER_CONFIG_EXT_RESPONSE_clearMPIAntennaConfiguration (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_CONFIG_EXT_RESPONSE_addMPIAntennaConfiguration (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis,
  LLRP_tSMPIAntennaConfiguration *pValue);


extern LLRP_tSMPIProperties *
LLRP_GET_READER_CONFIG_EXT_RESPONSE_getMPIProperties (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_CONFIG_EXT_RESPONSE_setMPIProperties (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis,
  LLRP_tSMPIProperties *pValue);

extern LLRP_tSMPIPsamWhiteList *
LLRP_GET_READER_CONFIG_EXT_RESPONSE_getMPIPsamWhiteList (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_CONFIG_EXT_RESPONSE_setMPIPsamWhiteList (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis,
  LLRP_tSMPIPsamWhiteList *pValue);

extern LLRP_tSMPISIMWhiteList *
LLRP_GET_READER_CONFIG_EXT_RESPONSE_getMPISIMWhiteList (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_CONFIG_EXT_RESPONSE_setMPISIMWhiteList (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis,
  LLRP_tSMPISIMWhiteList *pValue);

extern LLRP_tSMPIPsamAuthenticationFile *
LLRP_GET_READER_CONFIG_EXT_RESPONSE_getMPIPsamAuthenticationFile (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_CONFIG_EXT_RESPONSE_setMPIPsamAuthenticationFile (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis,
  LLRP_tSMPIPsamAuthenticationFile *pValue);

extern LLRP_tSMPISMSCenterNo *
LLRP_GET_READER_CONFIG_EXT_RESPONSE_getMPISMSCenterNo (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_CONFIG_EXT_RESPONSE_setMPISMSCenterNo (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis,
  LLRP_tSMPISMSCenterNo *pValue);

extern LLRP_tSParameter *
LLRP_GET_READER_CONFIG_EXT_RESPONSE_beginCustom (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis);

extern LLRP_tSParameter *
LLRP_GET_READER_CONFIG_EXT_RESPONSE_nextCustom (
  LLRP_tSParameter *pCurrent);

extern void
LLRP_GET_READER_CONFIG_EXT_RESPONSE_clearCustom (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_CONFIG_EXT_RESPONSE_addCustom (
  LLRP_tSGET_READER_CONFIG_EXT_RESPONSE *pThis,
  LLRP_tSParameter *pValue);




  
struct LLRP_SSET_READER_CONFIG_EXT
{
    LLRP_tSMessage hdr;
  
    llrp_u1_t ResetToFactoryDefault;

  
    LLRP_tSLLRPConfigurationStateValue * pLLRPConfigurationStateValue;

    LLRP_tSReaderEventNotificationSpec * pReaderEventNotificationSpec;

    LLRP_tSAntennaProperties * listAntennaProperties;

    LLRP_tSAntennaConfiguration * listAntennaConfiguration;

    LLRP_tSROReportSpec * pROReportSpec;

    LLRP_tSAccessReportSpec * pAccessReportSpec;

    LLRP_tSIdentification * pIdentification;

    LLRP_tSKeepaliveSpec * pKeepaliveSpec;

    LLRP_tSGPIPortCurrentState * listGPIPortCurrentState;

    LLRP_tSGPOWriteData * listGPOWriteData;

    LLRP_tSEventsAndReports * pEventsAndReports;

    LLRP_tSAntennaExtConfiguration * listAntennaExtConfiguration;

    LLRP_tSUHFAntennaExtConfiguration * listUHFAntennaExtConfiguration;

    LLRP_tSAlarmMask * pAlarmMask;

    LLRP_tSModuleDepth * pModuleDepth;

    LLRP_tSIQConfig * pIQConfig;

    LLRP_tSLocationConfiguration * pLocationConfiguration;

    LLRP_tSCustomPrivateConfigData * pCustomPrivateConfigData;

    LLRP_tSAntSwitchDelayCfg * pAntSwitchDelayCfg;

    LLRP_tSTagReportFilter * pTagReportFilter;

    LLRP_tSAntCoopCfg * pAntCoopCfg;

    LLRP_tSRSSISortCfg * pRSSISortCfg;

    LLRP_tSLeakCompensation * pLeakCompensation;

    LLRP_tSRecvDATT * pRecvDATT;

    LLRP_tSLaneNum * pLaneNum;

    LLRP_tSAlarmThreshodCfg * pAlarmThreshodCfg;

    LLRP_tSRUPAlarmThreshold * pRUPAlarmThreshold;

    LLRP_tSETCConfig * pETCConfig;

    LLRP_tSMPIAntennaConfiguration * listMPIAntennaConfiguration;

    LLRP_tSMPIProperties * pMPIProperties;

    LLRP_tSMPIPsamWhiteList * pMPIPsamWhiteList;

    LLRP_tSMPISIMWhiteList * pMPISIMWhiteList;

    LLRP_tSMPIPsamAuthenticationFile * pMPIPsamAuthenticationFile;

    LLRP_tSMPISMSCenterNo * pMPISMSCenterNo;

    LLRP_tSParameter * listCustom;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdSET_READER_CONFIG_EXT;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSET_READER_CONFIG_EXT[];

extern LLRP_tSSET_READER_CONFIG_EXT *
LLRP_SET_READER_CONFIG_EXT_construct (void);

extern void
LLRP_SET_READER_CONFIG_EXT_destruct (
 LLRP_tSSET_READER_CONFIG_EXT * pThis);

extern void
LLRP_SET_READER_CONFIG_EXT_decodeFields (
 LLRP_tSSET_READER_CONFIG_EXT * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SET_READER_CONFIG_EXT_assimilateSubParameters (
 LLRP_tSSET_READER_CONFIG_EXT * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SET_READER_CONFIG_EXT_encode (
  const LLRP_tSSET_READER_CONFIG_EXT *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdSET_READER_CONFIG_EXT_ResetToFactoryDefault;

extern llrp_u1_t
LLRP_SET_READER_CONFIG_EXT_getResetToFactoryDefault (
  LLRP_tSSET_READER_CONFIG_EXT *pThis);

extern LLRP_tResultCode
LLRP_SET_READER_CONFIG_EXT_setResetToFactoryDefault (
  LLRP_tSSET_READER_CONFIG_EXT *pThis,
  llrp_u1_t Value);

  
extern LLRP_tSLLRPConfigurationStateValue *
LLRP_SET_READER_CONFIG_EXT_getLLRPConfigurationStateValue (
  LLRP_tSSET_READER_CONFIG_EXT *pThis);

extern LLRP_tResultCode
LLRP_SET_READER_CONFIG_EXT_setLLRPConfigurationStateValue (
  LLRP_tSSET_READER_CONFIG_EXT *pThis,
  LLRP_tSLLRPConfigurationStateValue *pValue);

extern LLRP_tSReaderEventNotificationSpec *
LLRP_SET_READER_CONFIG_EXT_getReaderEventNotificationSpec (
  LLRP_tSSET_READER_CONFIG_EXT *pThis);

extern LLRP_tResultCode
LLRP_SET_READER_CONFIG_EXT_setReaderEventNotificationSpec (
  LLRP_tSSET_READER_CONFIG_EXT *pThis,
  LLRP_tSReaderEventNotificationSpec *pValue);

extern LLRP_tSAntennaProperties *
LLRP_SET_READER_CONFIG_EXT_beginAntennaProperties (
  LLRP_tSSET_READER_CONFIG_EXT *pThis);

extern LLRP_tSAntennaProperties *
LLRP_SET_READER_CONFIG_EXT_nextAntennaProperties (
  LLRP_tSAntennaProperties *pCurrent);

extern void
LLRP_SET_READER_CONFIG_EXT_clearAntennaProperties (
  LLRP_tSSET_READER_CONFIG_EXT *pThis);

extern LLRP_tResultCode
LLRP_SET_READER_CONFIG_EXT_addAntennaProperties (
  LLRP_tSSET_READER_CONFIG_EXT *pThis,
  LLRP_tSAntennaProperties *pValue);


extern LLRP_tSAntennaConfiguration *
LLRP_SET_READER_CONFIG_EXT_beginAntennaConfiguration (
  LLRP_tSSET_READER_CONFIG_EXT *pThis);

extern LLRP_tSAntennaConfiguration *
LLRP_SET_READER_CONFIG_EXT_nextAntennaConfiguration (
  LLRP_tSAntennaConfiguration *pCurrent);

extern void
LLRP_SET_READER_CONFIG_EXT_clearAntennaConfiguration (
  LLRP_tSSET_READER_CONFIG_EXT *pThis);

extern LLRP_tResultCode
LLRP_SET_READER_CONFIG_EXT_addAntennaConfiguration (
  LLRP_tSSET_READER_CONFIG_EXT *pThis,
  LLRP_tSAntennaConfiguration *pValue);


extern LLRP_tSROReportSpec *
LLRP_SET_READER_CONFIG_EXT_getROReportSpec (
  LLRP_tSSET_READER_CONFIG_EXT *pThis);

extern LLRP_tResultCode
LLRP_SET_READER_CONFIG_EXT_setROReportSpec (
  LLRP_tSSET_READER_CONFIG_EXT *pThis,
  LLRP_tSROReportSpec *pValue);

extern LLRP_tSAccessReportSpec *
LLRP_SET_READER_CONFIG_EXT_getAccessReportSpec (
  LLRP_tSSET_READER_CONFIG_EXT *pThis);

extern LLRP_tResultCode
LLRP_SET_READER_CONFIG_EXT_setAccessReportSpec (
  LLRP_tSSET_READER_CONFIG_EXT *pThis,
  LLRP_tSAccessReportSpec *pValue);

extern LLRP_tSIdentification *
LLRP_SET_READER_CONFIG_EXT_getIdentification (
  LLRP_tSSET_READER_CONFIG_EXT *pThis);

extern LLRP_tResultCode
LLRP_SET_READER_CONFIG_EXT_setIdentification (
  LLRP_tSSET_READER_CONFIG_EXT *pThis,
  LLRP_tSIdentification *pValue);

extern LLRP_tSKeepaliveSpec *
LLRP_SET_READER_CONFIG_EXT_getKeepaliveSpec (
  LLRP_tSSET_READER_CONFIG_EXT *pThis);

extern LLRP_tResultCode
LLRP_SET_READER_CONFIG_EXT_setKeepaliveSpec (
  LLRP_tSSET_READER_CONFIG_EXT *pThis,
  LLRP_tSKeepaliveSpec *pValue);

extern LLRP_tSGPIPortCurrentState *
LLRP_SET_READER_CONFIG_EXT_beginGPIPortCurrentState (
  LLRP_tSSET_READER_CONFIG_EXT *pThis);

extern LLRP_tSGPIPortCurrentState *
LLRP_SET_READER_CONFIG_EXT_nextGPIPortCurrentState (
  LLRP_tSGPIPortCurrentState *pCurrent);

extern void
LLRP_SET_READER_CONFIG_EXT_clearGPIPortCurrentState (
  LLRP_tSSET_READER_CONFIG_EXT *pThis);

extern LLRP_tResultCode
LLRP_SET_READER_CONFIG_EXT_addGPIPortCurrentState (
  LLRP_tSSET_READER_CONFIG_EXT *pThis,
  LLRP_tSGPIPortCurrentState *pValue);


extern LLRP_tSGPOWriteData *
LLRP_SET_READER_CONFIG_EXT_beginGPOWriteData (
  LLRP_tSSET_READER_CONFIG_EXT *pThis);

extern LLRP_tSGPOWriteData *
LLRP_SET_READER_CONFIG_EXT_nextGPOWriteData (
  LLRP_tSGPOWriteData *pCurrent);

extern void
LLRP_SET_READER_CONFIG_EXT_clearGPOWriteData (
  LLRP_tSSET_READER_CONFIG_EXT *pThis);

extern LLRP_tResultCode
LLRP_SET_READER_CONFIG_EXT_addGPOWriteData (
  LLRP_tSSET_READER_CONFIG_EXT *pThis,
  LLRP_tSGPOWriteData *pValue);


extern LLRP_tSEventsAndReports *
LLRP_SET_READER_CONFIG_EXT_getEventsAndReports (
  LLRP_tSSET_READER_CONFIG_EXT *pThis);

extern LLRP_tResultCode
LLRP_SET_READER_CONFIG_EXT_setEventsAndReports (
  LLRP_tSSET_READER_CONFIG_EXT *pThis,
  LLRP_tSEventsAndReports *pValue);

extern LLRP_tSAntennaExtConfiguration *
LLRP_SET_READER_CONFIG_EXT_beginAntennaExtConfiguration (
  LLRP_tSSET_READER_CONFIG_EXT *pThis);

extern LLRP_tSAntennaExtConfiguration *
LLRP_SET_READER_CONFIG_EXT_nextAntennaExtConfiguration (
  LLRP_tSAntennaExtConfiguration *pCurrent);

extern void
LLRP_SET_READER_CONFIG_EXT_clearAntennaExtConfiguration (
  LLRP_tSSET_READER_CONFIG_EXT *pThis);

extern LLRP_tResultCode
LLRP_SET_READER_CONFIG_EXT_addAntennaExtConfiguration (
  LLRP_tSSET_READER_CONFIG_EXT *pThis,
  LLRP_tSAntennaExtConfiguration *pValue);


extern LLRP_tSUHFAntennaExtConfiguration *
LLRP_SET_READER_CONFIG_EXT_beginUHFAntennaExtConfiguration (
  LLRP_tSSET_READER_CONFIG_EXT *pThis);

extern LLRP_tSUHFAntennaExtConfiguration *
LLRP_SET_READER_CONFIG_EXT_nextUHFAntennaExtConfiguration (
  LLRP_tSUHFAntennaExtConfiguration *pCurrent);

extern void
LLRP_SET_READER_CONFIG_EXT_clearUHFAntennaExtConfiguration (
  LLRP_tSSET_READER_CONFIG_EXT *pThis);

extern LLRP_tResultCode
LLRP_SET_READER_CONFIG_EXT_addUHFAntennaExtConfiguration (
  LLRP_tSSET_READER_CONFIG_EXT *pThis,
  LLRP_tSUHFAntennaExtConfiguration *pValue);


extern LLRP_tSAlarmMask *
LLRP_SET_READER_CONFIG_EXT_getAlarmMask (
  LLRP_tSSET_READER_CONFIG_EXT *pThis);

extern LLRP_tResultCode
LLRP_SET_READER_CONFIG_EXT_setAlarmMask (
  LLRP_tSSET_READER_CONFIG_EXT *pThis,
  LLRP_tSAlarmMask *pValue);

extern LLRP_tSModuleDepth *
LLRP_SET_READER_CONFIG_EXT_getModuleDepth (
  LLRP_tSSET_READER_CONFIG_EXT *pThis);

extern LLRP_tResultCode
LLRP_SET_READER_CONFIG_EXT_setModuleDepth (
  LLRP_tSSET_READER_CONFIG_EXT *pThis,
  LLRP_tSModuleDepth *pValue);

extern LLRP_tSIQConfig *
LLRP_SET_READER_CONFIG_EXT_getIQConfig (
  LLRP_tSSET_READER_CONFIG_EXT *pThis);

extern LLRP_tResultCode
LLRP_SET_READER_CONFIG_EXT_setIQConfig (
  LLRP_tSSET_READER_CONFIG_EXT *pThis,
  LLRP_tSIQConfig *pValue);

extern LLRP_tSLocationConfiguration *
LLRP_SET_READER_CONFIG_EXT_getLocationConfiguration (
  LLRP_tSSET_READER_CONFIG_EXT *pThis);

extern LLRP_tResultCode
LLRP_SET_READER_CONFIG_EXT_setLocationConfiguration (
  LLRP_tSSET_READER_CONFIG_EXT *pThis,
  LLRP_tSLocationConfiguration *pValue);

extern LLRP_tSCustomPrivateConfigData *
LLRP_SET_READER_CONFIG_EXT_getCustomPrivateConfigData (
  LLRP_tSSET_READER_CONFIG_EXT *pThis);

extern LLRP_tResultCode
LLRP_SET_READER_CONFIG_EXT_setCustomPrivateConfigData (
  LLRP_tSSET_READER_CONFIG_EXT *pThis,
  LLRP_tSCustomPrivateConfigData *pValue);

extern LLRP_tSAntSwitchDelayCfg *
LLRP_SET_READER_CONFIG_EXT_getAntSwitchDelayCfg (
  LLRP_tSSET_READER_CONFIG_EXT *pThis);

extern LLRP_tResultCode
LLRP_SET_READER_CONFIG_EXT_setAntSwitchDelayCfg (
  LLRP_tSSET_READER_CONFIG_EXT *pThis,
  LLRP_tSAntSwitchDelayCfg *pValue);

extern LLRP_tSTagReportFilter *
LLRP_SET_READER_CONFIG_EXT_getTagReportFilter (
  LLRP_tSSET_READER_CONFIG_EXT *pThis);

extern LLRP_tResultCode
LLRP_SET_READER_CONFIG_EXT_setTagReportFilter (
  LLRP_tSSET_READER_CONFIG_EXT *pThis,
  LLRP_tSTagReportFilter *pValue);

extern LLRP_tSAntCoopCfg *
LLRP_SET_READER_CONFIG_EXT_getAntCoopCfg (
  LLRP_tSSET_READER_CONFIG_EXT *pThis);

extern LLRP_tResultCode
LLRP_SET_READER_CONFIG_EXT_setAntCoopCfg (
  LLRP_tSSET_READER_CONFIG_EXT *pThis,
  LLRP_tSAntCoopCfg *pValue);

extern LLRP_tSRSSISortCfg *
LLRP_SET_READER_CONFIG_EXT_getRSSISortCfg (
  LLRP_tSSET_READER_CONFIG_EXT *pThis);

extern LLRP_tResultCode
LLRP_SET_READER_CONFIG_EXT_setRSSISortCfg (
  LLRP_tSSET_READER_CONFIG_EXT *pThis,
  LLRP_tSRSSISortCfg *pValue);

extern LLRP_tSLeakCompensation *
LLRP_SET_READER_CONFIG_EXT_getLeakCompensation (
  LLRP_tSSET_READER_CONFIG_EXT *pThis);

extern LLRP_tResultCode
LLRP_SET_READER_CONFIG_EXT_setLeakCompensation (
  LLRP_tSSET_READER_CONFIG_EXT *pThis,
  LLRP_tSLeakCompensation *pValue);

extern LLRP_tSRecvDATT *
LLRP_SET_READER_CONFIG_EXT_getRecvDATT (
  LLRP_tSSET_READER_CONFIG_EXT *pThis);

extern LLRP_tResultCode
LLRP_SET_READER_CONFIG_EXT_setRecvDATT (
  LLRP_tSSET_READER_CONFIG_EXT *pThis,
  LLRP_tSRecvDATT *pValue);

extern LLRP_tSLaneNum *
LLRP_SET_READER_CONFIG_EXT_getLaneNum (
  LLRP_tSSET_READER_CONFIG_EXT *pThis);

extern LLRP_tResultCode
LLRP_SET_READER_CONFIG_EXT_setLaneNum (
  LLRP_tSSET_READER_CONFIG_EXT *pThis,
  LLRP_tSLaneNum *pValue);

extern LLRP_tSAlarmThreshodCfg *
LLRP_SET_READER_CONFIG_EXT_getAlarmThreshodCfg (
  LLRP_tSSET_READER_CONFIG_EXT *pThis);

extern LLRP_tResultCode
LLRP_SET_READER_CONFIG_EXT_setAlarmThreshodCfg (
  LLRP_tSSET_READER_CONFIG_EXT *pThis,
  LLRP_tSAlarmThreshodCfg *pValue);

extern LLRP_tSRUPAlarmThreshold *
LLRP_SET_READER_CONFIG_EXT_getRUPAlarmThreshold (
  LLRP_tSSET_READER_CONFIG_EXT *pThis);

extern LLRP_tResultCode
LLRP_SET_READER_CONFIG_EXT_setRUPAlarmThreshold (
  LLRP_tSSET_READER_CONFIG_EXT *pThis,
  LLRP_tSRUPAlarmThreshold *pValue);

extern LLRP_tSETCConfig *
LLRP_SET_READER_CONFIG_EXT_getETCConfig (
  LLRP_tSSET_READER_CONFIG_EXT *pThis);

extern LLRP_tResultCode
LLRP_SET_READER_CONFIG_EXT_setETCConfig (
  LLRP_tSSET_READER_CONFIG_EXT *pThis,
  LLRP_tSETCConfig *pValue);

extern LLRP_tSMPIAntennaConfiguration *
LLRP_SET_READER_CONFIG_EXT_beginMPIAntennaConfiguration (
  LLRP_tSSET_READER_CONFIG_EXT *pThis);

extern LLRP_tSMPIAntennaConfiguration *
LLRP_SET_READER_CONFIG_EXT_nextMPIAntennaConfiguration (
  LLRP_tSMPIAntennaConfiguration *pCurrent);

extern void
LLRP_SET_READER_CONFIG_EXT_clearMPIAntennaConfiguration (
  LLRP_tSSET_READER_CONFIG_EXT *pThis);

extern LLRP_tResultCode
LLRP_SET_READER_CONFIG_EXT_addMPIAntennaConfiguration (
  LLRP_tSSET_READER_CONFIG_EXT *pThis,
  LLRP_tSMPIAntennaConfiguration *pValue);


extern LLRP_tSMPIProperties *
LLRP_SET_READER_CONFIG_EXT_getMPIProperties (
  LLRP_tSSET_READER_CONFIG_EXT *pThis);

extern LLRP_tResultCode
LLRP_SET_READER_CONFIG_EXT_setMPIProperties (
  LLRP_tSSET_READER_CONFIG_EXT *pThis,
  LLRP_tSMPIProperties *pValue);

extern LLRP_tSMPIPsamWhiteList *
LLRP_SET_READER_CONFIG_EXT_getMPIPsamWhiteList (
  LLRP_tSSET_READER_CONFIG_EXT *pThis);

extern LLRP_tResultCode
LLRP_SET_READER_CONFIG_EXT_setMPIPsamWhiteList (
  LLRP_tSSET_READER_CONFIG_EXT *pThis,
  LLRP_tSMPIPsamWhiteList *pValue);

extern LLRP_tSMPISIMWhiteList *
LLRP_SET_READER_CONFIG_EXT_getMPISIMWhiteList (
  LLRP_tSSET_READER_CONFIG_EXT *pThis);

extern LLRP_tResultCode
LLRP_SET_READER_CONFIG_EXT_setMPISIMWhiteList (
  LLRP_tSSET_READER_CONFIG_EXT *pThis,
  LLRP_tSMPISIMWhiteList *pValue);

extern LLRP_tSMPIPsamAuthenticationFile *
LLRP_SET_READER_CONFIG_EXT_getMPIPsamAuthenticationFile (
  LLRP_tSSET_READER_CONFIG_EXT *pThis);

extern LLRP_tResultCode
LLRP_SET_READER_CONFIG_EXT_setMPIPsamAuthenticationFile (
  LLRP_tSSET_READER_CONFIG_EXT *pThis,
  LLRP_tSMPIPsamAuthenticationFile *pValue);

extern LLRP_tSMPISMSCenterNo *
LLRP_SET_READER_CONFIG_EXT_getMPISMSCenterNo (
  LLRP_tSSET_READER_CONFIG_EXT *pThis);

extern LLRP_tResultCode
LLRP_SET_READER_CONFIG_EXT_setMPISMSCenterNo (
  LLRP_tSSET_READER_CONFIG_EXT *pThis,
  LLRP_tSMPISMSCenterNo *pValue);

extern LLRP_tSParameter *
LLRP_SET_READER_CONFIG_EXT_beginCustom (
  LLRP_tSSET_READER_CONFIG_EXT *pThis);

extern LLRP_tSParameter *
LLRP_SET_READER_CONFIG_EXT_nextCustom (
  LLRP_tSParameter *pCurrent);

extern void
LLRP_SET_READER_CONFIG_EXT_clearCustom (
  LLRP_tSSET_READER_CONFIG_EXT *pThis);

extern LLRP_tResultCode
LLRP_SET_READER_CONFIG_EXT_addCustom (
  LLRP_tSSET_READER_CONFIG_EXT *pThis,
  LLRP_tSParameter *pValue);




  
struct LLRP_SSET_READER_CONFIG_EXT_RESPONSE
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSLLRPStatus * pLLRPStatus;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdSET_READER_CONFIG_EXT_RESPONSE;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSET_READER_CONFIG_EXT_RESPONSE[];

extern LLRP_tSSET_READER_CONFIG_EXT_RESPONSE *
LLRP_SET_READER_CONFIG_EXT_RESPONSE_construct (void);

extern void
LLRP_SET_READER_CONFIG_EXT_RESPONSE_destruct (
 LLRP_tSSET_READER_CONFIG_EXT_RESPONSE * pThis);

extern void
LLRP_SET_READER_CONFIG_EXT_RESPONSE_decodeFields (
 LLRP_tSSET_READER_CONFIG_EXT_RESPONSE * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SET_READER_CONFIG_EXT_RESPONSE_assimilateSubParameters (
 LLRP_tSSET_READER_CONFIG_EXT_RESPONSE * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SET_READER_CONFIG_EXT_RESPONSE_encode (
  const LLRP_tSSET_READER_CONFIG_EXT_RESPONSE *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSLLRPStatus *
LLRP_SET_READER_CONFIG_EXT_RESPONSE_getLLRPStatus (
  LLRP_tSSET_READER_CONFIG_EXT_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_SET_READER_CONFIG_EXT_RESPONSE_setLLRPStatus (
  LLRP_tSSET_READER_CONFIG_EXT_RESPONSE *pThis,
  LLRP_tSLLRPStatus *pValue);



  
struct LLRP_SGET_READER_COMM_CONFIG
{
    LLRP_tSMessage hdr;
  
    LLRP_tECommConfigType eRequestedData;

  
    LLRP_tSParameter * listCustom;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdGET_READER_COMM_CONFIG;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdGET_READER_COMM_CONFIG[];

extern LLRP_tSGET_READER_COMM_CONFIG *
LLRP_GET_READER_COMM_CONFIG_construct (void);

extern void
LLRP_GET_READER_COMM_CONFIG_destruct (
 LLRP_tSGET_READER_COMM_CONFIG * pThis);

extern void
LLRP_GET_READER_COMM_CONFIG_decodeFields (
 LLRP_tSGET_READER_COMM_CONFIG * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_GET_READER_COMM_CONFIG_assimilateSubParameters (
 LLRP_tSGET_READER_COMM_CONFIG * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_GET_READER_COMM_CONFIG_encode (
  const LLRP_tSGET_READER_COMM_CONFIG *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdGET_READER_COMM_CONFIG_RequestedData;

extern LLRP_tECommConfigType
LLRP_GET_READER_COMM_CONFIG_getRequestedData (
  LLRP_tSGET_READER_COMM_CONFIG *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_COMM_CONFIG_setRequestedData (
  LLRP_tSGET_READER_COMM_CONFIG *pThis,
  LLRP_tECommConfigType Value);

  
extern LLRP_tSParameter *
LLRP_GET_READER_COMM_CONFIG_beginCustom (
  LLRP_tSGET_READER_COMM_CONFIG *pThis);

extern LLRP_tSParameter *
LLRP_GET_READER_COMM_CONFIG_nextCustom (
  LLRP_tSParameter *pCurrent);

extern void
LLRP_GET_READER_COMM_CONFIG_clearCustom (
  LLRP_tSGET_READER_COMM_CONFIG *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_COMM_CONFIG_addCustom (
  LLRP_tSGET_READER_COMM_CONFIG *pThis,
  LLRP_tSParameter *pValue);




  
struct LLRP_SGET_READER_COMM_CONFIG_RESPONSE
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSLLRPStatus * pLLRPStatus;

    LLRP_tSReaderName * pReaderName;

    LLRP_tSCommunicationConfiguration * pCommunicationConfiguration;

    LLRP_tSRUPCommunicationConfiguration * pRUPCommunicationConfiguration;

    LLRP_tSNTPConfiguration * pNTPConfiguration;

    LLRP_tSDeviceID * preaderID;

    LLRP_tSLinkStateInfo * listLinkStateInfo;

    LLRP_tSSaveReportSwitch * pSaveReportSwitch;

    LLRP_tSParameter * listCustom;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdGET_READER_COMM_CONFIG_RESPONSE;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdGET_READER_COMM_CONFIG_RESPONSE[];

extern LLRP_tSGET_READER_COMM_CONFIG_RESPONSE *
LLRP_GET_READER_COMM_CONFIG_RESPONSE_construct (void);

extern void
LLRP_GET_READER_COMM_CONFIG_RESPONSE_destruct (
 LLRP_tSGET_READER_COMM_CONFIG_RESPONSE * pThis);

extern void
LLRP_GET_READER_COMM_CONFIG_RESPONSE_decodeFields (
 LLRP_tSGET_READER_COMM_CONFIG_RESPONSE * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_GET_READER_COMM_CONFIG_RESPONSE_assimilateSubParameters (
 LLRP_tSGET_READER_COMM_CONFIG_RESPONSE * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_GET_READER_COMM_CONFIG_RESPONSE_encode (
  const LLRP_tSGET_READER_COMM_CONFIG_RESPONSE *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSLLRPStatus *
LLRP_GET_READER_COMM_CONFIG_RESPONSE_getLLRPStatus (
  LLRP_tSGET_READER_COMM_CONFIG_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_COMM_CONFIG_RESPONSE_setLLRPStatus (
  LLRP_tSGET_READER_COMM_CONFIG_RESPONSE *pThis,
  LLRP_tSLLRPStatus *pValue);

extern LLRP_tSReaderName *
LLRP_GET_READER_COMM_CONFIG_RESPONSE_getReaderName (
  LLRP_tSGET_READER_COMM_CONFIG_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_COMM_CONFIG_RESPONSE_setReaderName (
  LLRP_tSGET_READER_COMM_CONFIG_RESPONSE *pThis,
  LLRP_tSReaderName *pValue);

extern LLRP_tSCommunicationConfiguration *
LLRP_GET_READER_COMM_CONFIG_RESPONSE_getCommunicationConfiguration (
  LLRP_tSGET_READER_COMM_CONFIG_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_COMM_CONFIG_RESPONSE_setCommunicationConfiguration (
  LLRP_tSGET_READER_COMM_CONFIG_RESPONSE *pThis,
  LLRP_tSCommunicationConfiguration *pValue);

extern LLRP_tSRUPCommunicationConfiguration *
LLRP_GET_READER_COMM_CONFIG_RESPONSE_getRUPCommunicationConfiguration (
  LLRP_tSGET_READER_COMM_CONFIG_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_COMM_CONFIG_RESPONSE_setRUPCommunicationConfiguration (
  LLRP_tSGET_READER_COMM_CONFIG_RESPONSE *pThis,
  LLRP_tSRUPCommunicationConfiguration *pValue);

extern LLRP_tSNTPConfiguration *
LLRP_GET_READER_COMM_CONFIG_RESPONSE_getNTPConfiguration (
  LLRP_tSGET_READER_COMM_CONFIG_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_COMM_CONFIG_RESPONSE_setNTPConfiguration (
  LLRP_tSGET_READER_COMM_CONFIG_RESPONSE *pThis,
  LLRP_tSNTPConfiguration *pValue);

extern LLRP_tSDeviceID *
LLRP_GET_READER_COMM_CONFIG_RESPONSE_getreaderID (
  LLRP_tSGET_READER_COMM_CONFIG_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_COMM_CONFIG_RESPONSE_setreaderID (
  LLRP_tSGET_READER_COMM_CONFIG_RESPONSE *pThis,
  LLRP_tSDeviceID *pValue);

extern LLRP_tSLinkStateInfo *
LLRP_GET_READER_COMM_CONFIG_RESPONSE_beginLinkStateInfo (
  LLRP_tSGET_READER_COMM_CONFIG_RESPONSE *pThis);

extern LLRP_tSLinkStateInfo *
LLRP_GET_READER_COMM_CONFIG_RESPONSE_nextLinkStateInfo (
  LLRP_tSLinkStateInfo *pCurrent);

extern void
LLRP_GET_READER_COMM_CONFIG_RESPONSE_clearLinkStateInfo (
  LLRP_tSGET_READER_COMM_CONFIG_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_COMM_CONFIG_RESPONSE_addLinkStateInfo (
  LLRP_tSGET_READER_COMM_CONFIG_RESPONSE *pThis,
  LLRP_tSLinkStateInfo *pValue);


extern LLRP_tSSaveReportSwitch *
LLRP_GET_READER_COMM_CONFIG_RESPONSE_getSaveReportSwitch (
  LLRP_tSGET_READER_COMM_CONFIG_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_COMM_CONFIG_RESPONSE_setSaveReportSwitch (
  LLRP_tSGET_READER_COMM_CONFIG_RESPONSE *pThis,
  LLRP_tSSaveReportSwitch *pValue);

extern LLRP_tSParameter *
LLRP_GET_READER_COMM_CONFIG_RESPONSE_beginCustom (
  LLRP_tSGET_READER_COMM_CONFIG_RESPONSE *pThis);

extern LLRP_tSParameter *
LLRP_GET_READER_COMM_CONFIG_RESPONSE_nextCustom (
  LLRP_tSParameter *pCurrent);

extern void
LLRP_GET_READER_COMM_CONFIG_RESPONSE_clearCustom (
  LLRP_tSGET_READER_COMM_CONFIG_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_COMM_CONFIG_RESPONSE_addCustom (
  LLRP_tSGET_READER_COMM_CONFIG_RESPONSE *pThis,
  LLRP_tSParameter *pValue);




  
struct LLRP_SSET_READER_COMM_CONFIG
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSReaderName * pReaderName;

    LLRP_tSCommunicationConfiguration * pCommunicationConfiguration;

    LLRP_tSRUPCommunicationConfiguration * pRUPCommunicationConfiguration;

    LLRP_tSNTPConfiguration * pNTPConfiguration;

    LLRP_tSDeviceID * preaderID;

    LLRP_tSSaveReportSwitch * pSaveReportSwitch;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdSET_READER_COMM_CONFIG;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSET_READER_COMM_CONFIG[];

extern LLRP_tSSET_READER_COMM_CONFIG *
LLRP_SET_READER_COMM_CONFIG_construct (void);

extern void
LLRP_SET_READER_COMM_CONFIG_destruct (
 LLRP_tSSET_READER_COMM_CONFIG * pThis);

extern void
LLRP_SET_READER_COMM_CONFIG_decodeFields (
 LLRP_tSSET_READER_COMM_CONFIG * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SET_READER_COMM_CONFIG_assimilateSubParameters (
 LLRP_tSSET_READER_COMM_CONFIG * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SET_READER_COMM_CONFIG_encode (
  const LLRP_tSSET_READER_COMM_CONFIG *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSReaderName *
LLRP_SET_READER_COMM_CONFIG_getReaderName (
  LLRP_tSSET_READER_COMM_CONFIG *pThis);

extern LLRP_tResultCode
LLRP_SET_READER_COMM_CONFIG_setReaderName (
  LLRP_tSSET_READER_COMM_CONFIG *pThis,
  LLRP_tSReaderName *pValue);

extern LLRP_tSCommunicationConfiguration *
LLRP_SET_READER_COMM_CONFIG_getCommunicationConfiguration (
  LLRP_tSSET_READER_COMM_CONFIG *pThis);

extern LLRP_tResultCode
LLRP_SET_READER_COMM_CONFIG_setCommunicationConfiguration (
  LLRP_tSSET_READER_COMM_CONFIG *pThis,
  LLRP_tSCommunicationConfiguration *pValue);

extern LLRP_tSRUPCommunicationConfiguration *
LLRP_SET_READER_COMM_CONFIG_getRUPCommunicationConfiguration (
  LLRP_tSSET_READER_COMM_CONFIG *pThis);

extern LLRP_tResultCode
LLRP_SET_READER_COMM_CONFIG_setRUPCommunicationConfiguration (
  LLRP_tSSET_READER_COMM_CONFIG *pThis,
  LLRP_tSRUPCommunicationConfiguration *pValue);

extern LLRP_tSNTPConfiguration *
LLRP_SET_READER_COMM_CONFIG_getNTPConfiguration (
  LLRP_tSSET_READER_COMM_CONFIG *pThis);

extern LLRP_tResultCode
LLRP_SET_READER_COMM_CONFIG_setNTPConfiguration (
  LLRP_tSSET_READER_COMM_CONFIG *pThis,
  LLRP_tSNTPConfiguration *pValue);

extern LLRP_tSDeviceID *
LLRP_SET_READER_COMM_CONFIG_getreaderID (
  LLRP_tSSET_READER_COMM_CONFIG *pThis);

extern LLRP_tResultCode
LLRP_SET_READER_COMM_CONFIG_setreaderID (
  LLRP_tSSET_READER_COMM_CONFIG *pThis,
  LLRP_tSDeviceID *pValue);

extern LLRP_tSSaveReportSwitch *
LLRP_SET_READER_COMM_CONFIG_getSaveReportSwitch (
  LLRP_tSSET_READER_COMM_CONFIG *pThis);

extern LLRP_tResultCode
LLRP_SET_READER_COMM_CONFIG_setSaveReportSwitch (
  LLRP_tSSET_READER_COMM_CONFIG *pThis,
  LLRP_tSSaveReportSwitch *pValue);



  
struct LLRP_SSET_READER_COMM_CONFIG_RESPONSE
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSLLRPStatus * pLLRPStatus;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdSET_READER_COMM_CONFIG_RESPONSE;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSET_READER_COMM_CONFIG_RESPONSE[];

extern LLRP_tSSET_READER_COMM_CONFIG_RESPONSE *
LLRP_SET_READER_COMM_CONFIG_RESPONSE_construct (void);

extern void
LLRP_SET_READER_COMM_CONFIG_RESPONSE_destruct (
 LLRP_tSSET_READER_COMM_CONFIG_RESPONSE * pThis);

extern void
LLRP_SET_READER_COMM_CONFIG_RESPONSE_decodeFields (
 LLRP_tSSET_READER_COMM_CONFIG_RESPONSE * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SET_READER_COMM_CONFIG_RESPONSE_assimilateSubParameters (
 LLRP_tSSET_READER_COMM_CONFIG_RESPONSE * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SET_READER_COMM_CONFIG_RESPONSE_encode (
  const LLRP_tSSET_READER_COMM_CONFIG_RESPONSE *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSLLRPStatus *
LLRP_SET_READER_COMM_CONFIG_RESPONSE_getLLRPStatus (
  LLRP_tSSET_READER_COMM_CONFIG_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_SET_READER_COMM_CONFIG_RESPONSE_setLLRPStatus (
  LLRP_tSSET_READER_COMM_CONFIG_RESPONSE *pThis,
  LLRP_tSLLRPStatus *pValue);



  
struct LLRP_SRESET_TO_FACTORY_DEFAULT
{
    LLRP_tSMessage hdr;
  
  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdRESET_TO_FACTORY_DEFAULT;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdRESET_TO_FACTORY_DEFAULT[];

extern LLRP_tSRESET_TO_FACTORY_DEFAULT *
LLRP_RESET_TO_FACTORY_DEFAULT_construct (void);

extern void
LLRP_RESET_TO_FACTORY_DEFAULT_destruct (
 LLRP_tSRESET_TO_FACTORY_DEFAULT * pThis);

extern void
LLRP_RESET_TO_FACTORY_DEFAULT_decodeFields (
 LLRP_tSRESET_TO_FACTORY_DEFAULT * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_RESET_TO_FACTORY_DEFAULT_assimilateSubParameters (
 LLRP_tSRESET_TO_FACTORY_DEFAULT * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_RESET_TO_FACTORY_DEFAULT_encode (
  const LLRP_tSRESET_TO_FACTORY_DEFAULT *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  


  
struct LLRP_SRESET_READER
{
    LLRP_tSMessage hdr;
  
  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdRESET_READER;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdRESET_READER[];

extern LLRP_tSRESET_READER *
LLRP_RESET_READER_construct (void);

extern void
LLRP_RESET_READER_destruct (
 LLRP_tSRESET_READER * pThis);

extern void
LLRP_RESET_READER_decodeFields (
 LLRP_tSRESET_READER * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_RESET_READER_assimilateSubParameters (
 LLRP_tSRESET_READER * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_RESET_READER_encode (
  const LLRP_tSRESET_READER *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  


  
struct LLRP_SRESET_TO_FACTORY_DEFAULT_RESPONSE
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSLLRPStatus * pLLRPStatus;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdRESET_TO_FACTORY_DEFAULT_RESPONSE;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdRESET_TO_FACTORY_DEFAULT_RESPONSE[];

extern LLRP_tSRESET_TO_FACTORY_DEFAULT_RESPONSE *
LLRP_RESET_TO_FACTORY_DEFAULT_RESPONSE_construct (void);

extern void
LLRP_RESET_TO_FACTORY_DEFAULT_RESPONSE_destruct (
 LLRP_tSRESET_TO_FACTORY_DEFAULT_RESPONSE * pThis);

extern void
LLRP_RESET_TO_FACTORY_DEFAULT_RESPONSE_decodeFields (
 LLRP_tSRESET_TO_FACTORY_DEFAULT_RESPONSE * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_RESET_TO_FACTORY_DEFAULT_RESPONSE_assimilateSubParameters (
 LLRP_tSRESET_TO_FACTORY_DEFAULT_RESPONSE * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_RESET_TO_FACTORY_DEFAULT_RESPONSE_encode (
  const LLRP_tSRESET_TO_FACTORY_DEFAULT_RESPONSE *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSLLRPStatus *
LLRP_RESET_TO_FACTORY_DEFAULT_RESPONSE_getLLRPStatus (
  LLRP_tSRESET_TO_FACTORY_DEFAULT_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_RESET_TO_FACTORY_DEFAULT_RESPONSE_setLLRPStatus (
  LLRP_tSRESET_TO_FACTORY_DEFAULT_RESPONSE *pThis,
  LLRP_tSLLRPStatus *pValue);



  
struct LLRP_SRESET_READER_RESPONSE
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSLLRPStatus * pLLRPStatus;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdRESET_READER_RESPONSE;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdRESET_READER_RESPONSE[];

extern LLRP_tSRESET_READER_RESPONSE *
LLRP_RESET_READER_RESPONSE_construct (void);

extern void
LLRP_RESET_READER_RESPONSE_destruct (
 LLRP_tSRESET_READER_RESPONSE * pThis);

extern void
LLRP_RESET_READER_RESPONSE_decodeFields (
 LLRP_tSRESET_READER_RESPONSE * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_RESET_READER_RESPONSE_assimilateSubParameters (
 LLRP_tSRESET_READER_RESPONSE * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_RESET_READER_RESPONSE_encode (
  const LLRP_tSRESET_READER_RESPONSE *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSLLRPStatus *
LLRP_RESET_READER_RESPONSE_getLLRPStatus (
  LLRP_tSRESET_READER_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_RESET_READER_RESPONSE_setLLRPStatus (
  LLRP_tSRESET_READER_RESPONSE *pThis,
  LLRP_tSLLRPStatus *pValue);



  
struct LLRP_SSET_PLT_DMP_TEST
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSTestItem * listTestItem;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdSET_PLT_DMP_TEST;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSET_PLT_DMP_TEST[];

extern LLRP_tSSET_PLT_DMP_TEST *
LLRP_SET_PLT_DMP_TEST_construct (void);

extern void
LLRP_SET_PLT_DMP_TEST_destruct (
 LLRP_tSSET_PLT_DMP_TEST * pThis);

extern void
LLRP_SET_PLT_DMP_TEST_decodeFields (
 LLRP_tSSET_PLT_DMP_TEST * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SET_PLT_DMP_TEST_assimilateSubParameters (
 LLRP_tSSET_PLT_DMP_TEST * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SET_PLT_DMP_TEST_encode (
  const LLRP_tSSET_PLT_DMP_TEST *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSTestItem *
LLRP_SET_PLT_DMP_TEST_beginTestItem (
  LLRP_tSSET_PLT_DMP_TEST *pThis);

extern LLRP_tSTestItem *
LLRP_SET_PLT_DMP_TEST_nextTestItem (
  LLRP_tSTestItem *pCurrent);

extern void
LLRP_SET_PLT_DMP_TEST_clearTestItem (
  LLRP_tSSET_PLT_DMP_TEST *pThis);

extern LLRP_tResultCode
LLRP_SET_PLT_DMP_TEST_addTestItem (
  LLRP_tSSET_PLT_DMP_TEST *pThis,
  LLRP_tSTestItem *pValue);




  
struct LLRP_SSET_PLT_DMP_TEST_RESPONSE
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSLLRPStatus * pLLRPStatus;

    LLRP_tSTestItemACK * listTestItemACK;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdSET_PLT_DMP_TEST_RESPONSE;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSET_PLT_DMP_TEST_RESPONSE[];

extern LLRP_tSSET_PLT_DMP_TEST_RESPONSE *
LLRP_SET_PLT_DMP_TEST_RESPONSE_construct (void);

extern void
LLRP_SET_PLT_DMP_TEST_RESPONSE_destruct (
 LLRP_tSSET_PLT_DMP_TEST_RESPONSE * pThis);

extern void
LLRP_SET_PLT_DMP_TEST_RESPONSE_decodeFields (
 LLRP_tSSET_PLT_DMP_TEST_RESPONSE * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SET_PLT_DMP_TEST_RESPONSE_assimilateSubParameters (
 LLRP_tSSET_PLT_DMP_TEST_RESPONSE * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SET_PLT_DMP_TEST_RESPONSE_encode (
  const LLRP_tSSET_PLT_DMP_TEST_RESPONSE *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSLLRPStatus *
LLRP_SET_PLT_DMP_TEST_RESPONSE_getLLRPStatus (
  LLRP_tSSET_PLT_DMP_TEST_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_SET_PLT_DMP_TEST_RESPONSE_setLLRPStatus (
  LLRP_tSSET_PLT_DMP_TEST_RESPONSE *pThis,
  LLRP_tSLLRPStatus *pValue);

extern LLRP_tSTestItemACK *
LLRP_SET_PLT_DMP_TEST_RESPONSE_beginTestItemACK (
  LLRP_tSSET_PLT_DMP_TEST_RESPONSE *pThis);

extern LLRP_tSTestItemACK *
LLRP_SET_PLT_DMP_TEST_RESPONSE_nextTestItemACK (
  LLRP_tSTestItemACK *pCurrent);

extern void
LLRP_SET_PLT_DMP_TEST_RESPONSE_clearTestItemACK (
  LLRP_tSSET_PLT_DMP_TEST_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_SET_PLT_DMP_TEST_RESPONSE_addTestItemACK (
  LLRP_tSSET_PLT_DMP_TEST_RESPONSE *pThis,
  LLRP_tSTestItemACK *pValue);




  
struct LLRP_STB_TEST_REQUEST
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSTbTestItem * listTbTestItem;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdTB_TEST_REQUEST;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdTB_TEST_REQUEST[];

extern LLRP_tSTB_TEST_REQUEST *
LLRP_TB_TEST_REQUEST_construct (void);

extern void
LLRP_TB_TEST_REQUEST_destruct (
 LLRP_tSTB_TEST_REQUEST * pThis);

extern void
LLRP_TB_TEST_REQUEST_decodeFields (
 LLRP_tSTB_TEST_REQUEST * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_TB_TEST_REQUEST_assimilateSubParameters (
 LLRP_tSTB_TEST_REQUEST * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_TB_TEST_REQUEST_encode (
  const LLRP_tSTB_TEST_REQUEST *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSTbTestItem *
LLRP_TB_TEST_REQUEST_beginTbTestItem (
  LLRP_tSTB_TEST_REQUEST *pThis);

extern LLRP_tSTbTestItem *
LLRP_TB_TEST_REQUEST_nextTbTestItem (
  LLRP_tSTbTestItem *pCurrent);

extern void
LLRP_TB_TEST_REQUEST_clearTbTestItem (
  LLRP_tSTB_TEST_REQUEST *pThis);

extern LLRP_tResultCode
LLRP_TB_TEST_REQUEST_addTbTestItem (
  LLRP_tSTB_TEST_REQUEST *pThis,
  LLRP_tSTbTestItem *pValue);




  
struct LLRP_STB_TEST_REQUEST_RESPONSE
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSLLRPStatus * pLLRPStatus;

    LLRP_tSTbTestItemACK * listTbTestItemACK;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdTB_TEST_REQUEST_RESPONSE;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdTB_TEST_REQUEST_RESPONSE[];

extern LLRP_tSTB_TEST_REQUEST_RESPONSE *
LLRP_TB_TEST_REQUEST_RESPONSE_construct (void);

extern void
LLRP_TB_TEST_REQUEST_RESPONSE_destruct (
 LLRP_tSTB_TEST_REQUEST_RESPONSE * pThis);

extern void
LLRP_TB_TEST_REQUEST_RESPONSE_decodeFields (
 LLRP_tSTB_TEST_REQUEST_RESPONSE * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_TB_TEST_REQUEST_RESPONSE_assimilateSubParameters (
 LLRP_tSTB_TEST_REQUEST_RESPONSE * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_TB_TEST_REQUEST_RESPONSE_encode (
  const LLRP_tSTB_TEST_REQUEST_RESPONSE *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSLLRPStatus *
LLRP_TB_TEST_REQUEST_RESPONSE_getLLRPStatus (
  LLRP_tSTB_TEST_REQUEST_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_TB_TEST_REQUEST_RESPONSE_setLLRPStatus (
  LLRP_tSTB_TEST_REQUEST_RESPONSE *pThis,
  LLRP_tSLLRPStatus *pValue);

extern LLRP_tSTbTestItemACK *
LLRP_TB_TEST_REQUEST_RESPONSE_beginTbTestItemACK (
  LLRP_tSTB_TEST_REQUEST_RESPONSE *pThis);

extern LLRP_tSTbTestItemACK *
LLRP_TB_TEST_REQUEST_RESPONSE_nextTbTestItemACK (
  LLRP_tSTbTestItemACK *pCurrent);

extern void
LLRP_TB_TEST_REQUEST_RESPONSE_clearTbTestItemACK (
  LLRP_tSTB_TEST_REQUEST_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_TB_TEST_REQUEST_RESPONSE_addTbTestItemACK (
  LLRP_tSTB_TEST_REQUEST_RESPONSE *pThis,
  LLRP_tSTbTestItemACK *pValue);




  
struct LLRP_SDEL_ALARM
{
    LLRP_tSMessage hdr;
  
    llrp_u32_t Function;

    llrp_u32_t DataLength;

  
    LLRP_tSDelAlarmInfo * pDelAlarmInfo;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdDEL_ALARM;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdDEL_ALARM[];

extern LLRP_tSDEL_ALARM *
LLRP_DEL_ALARM_construct (void);

extern void
LLRP_DEL_ALARM_destruct (
 LLRP_tSDEL_ALARM * pThis);

extern void
LLRP_DEL_ALARM_decodeFields (
 LLRP_tSDEL_ALARM * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_DEL_ALARM_assimilateSubParameters (
 LLRP_tSDEL_ALARM * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_DEL_ALARM_encode (
  const LLRP_tSDEL_ALARM *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdDEL_ALARM_Function;

extern llrp_u32_t
LLRP_DEL_ALARM_getFunction (
  LLRP_tSDEL_ALARM *pThis);

extern LLRP_tResultCode
LLRP_DEL_ALARM_setFunction (
  LLRP_tSDEL_ALARM *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdDEL_ALARM_DataLength;

extern llrp_u32_t
LLRP_DEL_ALARM_getDataLength (
  LLRP_tSDEL_ALARM *pThis);

extern LLRP_tResultCode
LLRP_DEL_ALARM_setDataLength (
  LLRP_tSDEL_ALARM *pThis,
  llrp_u32_t Value);

  
extern LLRP_tSDelAlarmInfo *
LLRP_DEL_ALARM_getDelAlarmInfo (
  LLRP_tSDEL_ALARM *pThis);

extern LLRP_tResultCode
LLRP_DEL_ALARM_setDelAlarmInfo (
  LLRP_tSDEL_ALARM *pThis,
  LLRP_tSDelAlarmInfo *pValue);



  
struct LLRP_SSYNC_ALARM
{
    LLRP_tSMessage hdr;
  
    llrp_u32_t Function;

    llrp_u32_t DataLength;

  
    LLRP_tSSyncInfo * pSyncInfo;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdSYNC_ALARM;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSYNC_ALARM[];

extern LLRP_tSSYNC_ALARM *
LLRP_SYNC_ALARM_construct (void);

extern void
LLRP_SYNC_ALARM_destruct (
 LLRP_tSSYNC_ALARM * pThis);

extern void
LLRP_SYNC_ALARM_decodeFields (
 LLRP_tSSYNC_ALARM * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SYNC_ALARM_assimilateSubParameters (
 LLRP_tSSYNC_ALARM * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SYNC_ALARM_encode (
  const LLRP_tSSYNC_ALARM *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdSYNC_ALARM_Function;

extern llrp_u32_t
LLRP_SYNC_ALARM_getFunction (
  LLRP_tSSYNC_ALARM *pThis);

extern LLRP_tResultCode
LLRP_SYNC_ALARM_setFunction (
  LLRP_tSSYNC_ALARM *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSYNC_ALARM_DataLength;

extern llrp_u32_t
LLRP_SYNC_ALARM_getDataLength (
  LLRP_tSSYNC_ALARM *pThis);

extern LLRP_tResultCode
LLRP_SYNC_ALARM_setDataLength (
  LLRP_tSSYNC_ALARM *pThis,
  llrp_u32_t Value);

  
extern LLRP_tSSyncInfo *
LLRP_SYNC_ALARM_getSyncInfo (
  LLRP_tSSYNC_ALARM *pThis);

extern LLRP_tResultCode
LLRP_SYNC_ALARM_setSyncInfo (
  LLRP_tSSYNC_ALARM *pThis,
  LLRP_tSSyncInfo *pValue);



  
struct LLRP_SALARM_REPORT
{
    LLRP_tSMessage hdr;
  
    llrp_u32_t Function;

    llrp_u32_t DataLength;

  
    LLRP_tSAlarmReportInfo * pAlarmReportInfo;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdALARM_REPORT;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdALARM_REPORT[];

extern LLRP_tSALARM_REPORT *
LLRP_ALARM_REPORT_construct (void);

extern void
LLRP_ALARM_REPORT_destruct (
 LLRP_tSALARM_REPORT * pThis);

extern void
LLRP_ALARM_REPORT_decodeFields (
 LLRP_tSALARM_REPORT * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_ALARM_REPORT_assimilateSubParameters (
 LLRP_tSALARM_REPORT * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_ALARM_REPORT_encode (
  const LLRP_tSALARM_REPORT *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdALARM_REPORT_Function;

extern llrp_u32_t
LLRP_ALARM_REPORT_getFunction (
  LLRP_tSALARM_REPORT *pThis);

extern LLRP_tResultCode
LLRP_ALARM_REPORT_setFunction (
  LLRP_tSALARM_REPORT *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdALARM_REPORT_DataLength;

extern llrp_u32_t
LLRP_ALARM_REPORT_getDataLength (
  LLRP_tSALARM_REPORT *pThis);

extern LLRP_tResultCode
LLRP_ALARM_REPORT_setDataLength (
  LLRP_tSALARM_REPORT *pThis,
  llrp_u32_t Value);

  
extern LLRP_tSAlarmReportInfo *
LLRP_ALARM_REPORT_getAlarmReportInfo (
  LLRP_tSALARM_REPORT *pThis);

extern LLRP_tResultCode
LLRP_ALARM_REPORT_setAlarmReportInfo (
  LLRP_tSALARM_REPORT *pThis,
  LLRP_tSAlarmReportInfo *pValue);



  
struct LLRP_SALARM_RESTOREREPORT
{
    LLRP_tSMessage hdr;
  
    llrp_u32_t Function;

    llrp_u32_t DataLength;

  
    LLRP_tSAlarmRestoreReportInfo * pAlarmRestoreReportInfo;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdALARM_RESTOREREPORT;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdALARM_RESTOREREPORT[];

extern LLRP_tSALARM_RESTOREREPORT *
LLRP_ALARM_RESTOREREPORT_construct (void);

extern void
LLRP_ALARM_RESTOREREPORT_destruct (
 LLRP_tSALARM_RESTOREREPORT * pThis);

extern void
LLRP_ALARM_RESTOREREPORT_decodeFields (
 LLRP_tSALARM_RESTOREREPORT * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_ALARM_RESTOREREPORT_assimilateSubParameters (
 LLRP_tSALARM_RESTOREREPORT * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_ALARM_RESTOREREPORT_encode (
  const LLRP_tSALARM_RESTOREREPORT *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdALARM_RESTOREREPORT_Function;

extern llrp_u32_t
LLRP_ALARM_RESTOREREPORT_getFunction (
  LLRP_tSALARM_RESTOREREPORT *pThis);

extern LLRP_tResultCode
LLRP_ALARM_RESTOREREPORT_setFunction (
  LLRP_tSALARM_RESTOREREPORT *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdALARM_RESTOREREPORT_DataLength;

extern llrp_u32_t
LLRP_ALARM_RESTOREREPORT_getDataLength (
  LLRP_tSALARM_RESTOREREPORT *pThis);

extern LLRP_tResultCode
LLRP_ALARM_RESTOREREPORT_setDataLength (
  LLRP_tSALARM_RESTOREREPORT *pThis,
  llrp_u32_t Value);

  
extern LLRP_tSAlarmRestoreReportInfo *
LLRP_ALARM_RESTOREREPORT_getAlarmRestoreReportInfo (
  LLRP_tSALARM_RESTOREREPORT *pThis);

extern LLRP_tResultCode
LLRP_ALARM_RESTOREREPORT_setAlarmRestoreReportInfo (
  LLRP_tSALARM_RESTOREREPORT *pThis,
  LLRP_tSAlarmRestoreReportInfo *pValue);



  
struct LLRP_SINFORM_ALARM_REPORT
{
    LLRP_tSMessage hdr;
  
    llrp_u32_t Function;

    llrp_u32_t DataLength;

  
    LLRP_tSInformReportInfo * pInformReportInfo;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdINFORM_ALARM_REPORT;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdINFORM_ALARM_REPORT[];

extern LLRP_tSINFORM_ALARM_REPORT *
LLRP_INFORM_ALARM_REPORT_construct (void);

extern void
LLRP_INFORM_ALARM_REPORT_destruct (
 LLRP_tSINFORM_ALARM_REPORT * pThis);

extern void
LLRP_INFORM_ALARM_REPORT_decodeFields (
 LLRP_tSINFORM_ALARM_REPORT * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_INFORM_ALARM_REPORT_assimilateSubParameters (
 LLRP_tSINFORM_ALARM_REPORT * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_INFORM_ALARM_REPORT_encode (
  const LLRP_tSINFORM_ALARM_REPORT *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdINFORM_ALARM_REPORT_Function;

extern llrp_u32_t
LLRP_INFORM_ALARM_REPORT_getFunction (
  LLRP_tSINFORM_ALARM_REPORT *pThis);

extern LLRP_tResultCode
LLRP_INFORM_ALARM_REPORT_setFunction (
  LLRP_tSINFORM_ALARM_REPORT *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdINFORM_ALARM_REPORT_DataLength;

extern llrp_u32_t
LLRP_INFORM_ALARM_REPORT_getDataLength (
  LLRP_tSINFORM_ALARM_REPORT *pThis);

extern LLRP_tResultCode
LLRP_INFORM_ALARM_REPORT_setDataLength (
  LLRP_tSINFORM_ALARM_REPORT *pThis,
  llrp_u32_t Value);

  
extern LLRP_tSInformReportInfo *
LLRP_INFORM_ALARM_REPORT_getInformReportInfo (
  LLRP_tSINFORM_ALARM_REPORT *pThis);

extern LLRP_tResultCode
LLRP_INFORM_ALARM_REPORT_setInformReportInfo (
  LLRP_tSINFORM_ALARM_REPORT *pThis,
  LLRP_tSInformReportInfo *pValue);



  
struct LLRP_SREFRESH_ALARM
{
    LLRP_tSMessage hdr;
  
    llrp_u32_t Function;

    llrp_u32_t DataLength;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdREFRESH_ALARM;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdREFRESH_ALARM[];

extern LLRP_tSREFRESH_ALARM *
LLRP_REFRESH_ALARM_construct (void);

extern void
LLRP_REFRESH_ALARM_destruct (
 LLRP_tSREFRESH_ALARM * pThis);

extern void
LLRP_REFRESH_ALARM_decodeFields (
 LLRP_tSREFRESH_ALARM * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_REFRESH_ALARM_assimilateSubParameters (
 LLRP_tSREFRESH_ALARM * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_REFRESH_ALARM_encode (
  const LLRP_tSREFRESH_ALARM *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdREFRESH_ALARM_Function;

extern llrp_u32_t
LLRP_REFRESH_ALARM_getFunction (
  LLRP_tSREFRESH_ALARM *pThis);

extern LLRP_tResultCode
LLRP_REFRESH_ALARM_setFunction (
  LLRP_tSREFRESH_ALARM *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdREFRESH_ALARM_DataLength;

extern llrp_u32_t
LLRP_REFRESH_ALARM_getDataLength (
  LLRP_tSREFRESH_ALARM *pThis);

extern LLRP_tResultCode
LLRP_REFRESH_ALARM_setDataLength (
  LLRP_tSREFRESH_ALARM *pThis,
  llrp_u32_t Value);

  


  
struct LLRP_SREADER_VERSION_ACTIVATE
{
    LLRP_tSMessage hdr;
  
  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdREADER_VERSION_ACTIVATE;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdREADER_VERSION_ACTIVATE[];

extern LLRP_tSREADER_VERSION_ACTIVATE *
LLRP_READER_VERSION_ACTIVATE_construct (void);

extern void
LLRP_READER_VERSION_ACTIVATE_destruct (
 LLRP_tSREADER_VERSION_ACTIVATE * pThis);

extern void
LLRP_READER_VERSION_ACTIVATE_decodeFields (
 LLRP_tSREADER_VERSION_ACTIVATE * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_READER_VERSION_ACTIVATE_assimilateSubParameters (
 LLRP_tSREADER_VERSION_ACTIVATE * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_READER_VERSION_ACTIVATE_encode (
  const LLRP_tSREADER_VERSION_ACTIVATE *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  


  
struct LLRP_SREADER_VERSION_ACTIVATE_RESPONS
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSLLRPStatus * pLLRPStatus;

    LLRP_tSReaderVerActivateAck * pReaderVerActivateAck;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdREADER_VERSION_ACTIVATE_RESPONS;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdREADER_VERSION_ACTIVATE_RESPONS[];

extern LLRP_tSREADER_VERSION_ACTIVATE_RESPONS *
LLRP_READER_VERSION_ACTIVATE_RESPONS_construct (void);

extern void
LLRP_READER_VERSION_ACTIVATE_RESPONS_destruct (
 LLRP_tSREADER_VERSION_ACTIVATE_RESPONS * pThis);

extern void
LLRP_READER_VERSION_ACTIVATE_RESPONS_decodeFields (
 LLRP_tSREADER_VERSION_ACTIVATE_RESPONS * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_READER_VERSION_ACTIVATE_RESPONS_assimilateSubParameters (
 LLRP_tSREADER_VERSION_ACTIVATE_RESPONS * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_READER_VERSION_ACTIVATE_RESPONS_encode (
  const LLRP_tSREADER_VERSION_ACTIVATE_RESPONS *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSLLRPStatus *
LLRP_READER_VERSION_ACTIVATE_RESPONS_getLLRPStatus (
  LLRP_tSREADER_VERSION_ACTIVATE_RESPONS *pThis);

extern LLRP_tResultCode
LLRP_READER_VERSION_ACTIVATE_RESPONS_setLLRPStatus (
  LLRP_tSREADER_VERSION_ACTIVATE_RESPONS *pThis,
  LLRP_tSLLRPStatus *pValue);

extern LLRP_tSReaderVerActivateAck *
LLRP_READER_VERSION_ACTIVATE_RESPONS_getReaderVerActivateAck (
  LLRP_tSREADER_VERSION_ACTIVATE_RESPONS *pThis);

extern LLRP_tResultCode
LLRP_READER_VERSION_ACTIVATE_RESPONS_setReaderVerActivateAck (
  LLRP_tSREADER_VERSION_ACTIVATE_RESPONS *pThis,
  LLRP_tSReaderVerActivateAck *pValue);



  
struct LLRP_SREADER_VERSION_UNACTIVATE
{
    LLRP_tSMessage hdr;
  
  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdREADER_VERSION_UNACTIVATE;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdREADER_VERSION_UNACTIVATE[];

extern LLRP_tSREADER_VERSION_UNACTIVATE *
LLRP_READER_VERSION_UNACTIVATE_construct (void);

extern void
LLRP_READER_VERSION_UNACTIVATE_destruct (
 LLRP_tSREADER_VERSION_UNACTIVATE * pThis);

extern void
LLRP_READER_VERSION_UNACTIVATE_decodeFields (
 LLRP_tSREADER_VERSION_UNACTIVATE * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_READER_VERSION_UNACTIVATE_assimilateSubParameters (
 LLRP_tSREADER_VERSION_UNACTIVATE * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_READER_VERSION_UNACTIVATE_encode (
  const LLRP_tSREADER_VERSION_UNACTIVATE *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  


  
struct LLRP_SREADER_VERSION_UNACTIVATE_RESPONS
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSLLRPStatus * pLLRPStatus;

    LLRP_tSReaderVerActivateAck * pReaderVerActivateAck;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdREADER_VERSION_UNACTIVATE_RESPONS;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdREADER_VERSION_UNACTIVATE_RESPONS[];

extern LLRP_tSREADER_VERSION_UNACTIVATE_RESPONS *
LLRP_READER_VERSION_UNACTIVATE_RESPONS_construct (void);

extern void
LLRP_READER_VERSION_UNACTIVATE_RESPONS_destruct (
 LLRP_tSREADER_VERSION_UNACTIVATE_RESPONS * pThis);

extern void
LLRP_READER_VERSION_UNACTIVATE_RESPONS_decodeFields (
 LLRP_tSREADER_VERSION_UNACTIVATE_RESPONS * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_READER_VERSION_UNACTIVATE_RESPONS_assimilateSubParameters (
 LLRP_tSREADER_VERSION_UNACTIVATE_RESPONS * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_READER_VERSION_UNACTIVATE_RESPONS_encode (
  const LLRP_tSREADER_VERSION_UNACTIVATE_RESPONS *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSLLRPStatus *
LLRP_READER_VERSION_UNACTIVATE_RESPONS_getLLRPStatus (
  LLRP_tSREADER_VERSION_UNACTIVATE_RESPONS *pThis);

extern LLRP_tResultCode
LLRP_READER_VERSION_UNACTIVATE_RESPONS_setLLRPStatus (
  LLRP_tSREADER_VERSION_UNACTIVATE_RESPONS *pThis,
  LLRP_tSLLRPStatus *pValue);

extern LLRP_tSReaderVerActivateAck *
LLRP_READER_VERSION_UNACTIVATE_RESPONS_getReaderVerActivateAck (
  LLRP_tSREADER_VERSION_UNACTIVATE_RESPONS *pThis);

extern LLRP_tResultCode
LLRP_READER_VERSION_UNACTIVATE_RESPONS_setReaderVerActivateAck (
  LLRP_tSREADER_VERSION_UNACTIVATE_RESPONS *pThis,
  LLRP_tSReaderVerActivateAck *pValue);



  
struct LLRP_SREADER_VERSION_QUERY
{
    LLRP_tSMessage hdr;
  
  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdREADER_VERSION_QUERY;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdREADER_VERSION_QUERY[];

extern LLRP_tSREADER_VERSION_QUERY *
LLRP_READER_VERSION_QUERY_construct (void);

extern void
LLRP_READER_VERSION_QUERY_destruct (
 LLRP_tSREADER_VERSION_QUERY * pThis);

extern void
LLRP_READER_VERSION_QUERY_decodeFields (
 LLRP_tSREADER_VERSION_QUERY * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_READER_VERSION_QUERY_assimilateSubParameters (
 LLRP_tSREADER_VERSION_QUERY * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_READER_VERSION_QUERY_encode (
  const LLRP_tSREADER_VERSION_QUERY *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  


  
struct LLRP_SREADER_VERSION_QUERY_RESPONSE
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSLLRPStatus * pLLRPStatus;

    LLRP_tSVerInfoQueryAck * pVerInfoQueryAck;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdREADER_VERSION_QUERY_RESPONSE;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdREADER_VERSION_QUERY_RESPONSE[];

extern LLRP_tSREADER_VERSION_QUERY_RESPONSE *
LLRP_READER_VERSION_QUERY_RESPONSE_construct (void);

extern void
LLRP_READER_VERSION_QUERY_RESPONSE_destruct (
 LLRP_tSREADER_VERSION_QUERY_RESPONSE * pThis);

extern void
LLRP_READER_VERSION_QUERY_RESPONSE_decodeFields (
 LLRP_tSREADER_VERSION_QUERY_RESPONSE * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_READER_VERSION_QUERY_RESPONSE_assimilateSubParameters (
 LLRP_tSREADER_VERSION_QUERY_RESPONSE * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_READER_VERSION_QUERY_RESPONSE_encode (
  const LLRP_tSREADER_VERSION_QUERY_RESPONSE *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSLLRPStatus *
LLRP_READER_VERSION_QUERY_RESPONSE_getLLRPStatus (
  LLRP_tSREADER_VERSION_QUERY_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_READER_VERSION_QUERY_RESPONSE_setLLRPStatus (
  LLRP_tSREADER_VERSION_QUERY_RESPONSE *pThis,
  LLRP_tSLLRPStatus *pValue);

extern LLRP_tSVerInfoQueryAck *
LLRP_READER_VERSION_QUERY_RESPONSE_getVerInfoQueryAck (
  LLRP_tSREADER_VERSION_QUERY_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_READER_VERSION_QUERY_RESPONSE_setVerInfoQueryAck (
  LLRP_tSREADER_VERSION_QUERY_RESPONSE *pThis,
  LLRP_tSVerInfoQueryAck *pValue);



  
struct LLRP_SREADER_VERSION_DOWNLOAD_REQUEST
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSVersionDownloadRequest * pVersionDownloadRequest;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdREADER_VERSION_DOWNLOAD_REQUEST;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdREADER_VERSION_DOWNLOAD_REQUEST[];

extern LLRP_tSREADER_VERSION_DOWNLOAD_REQUEST *
LLRP_READER_VERSION_DOWNLOAD_REQUEST_construct (void);

extern void
LLRP_READER_VERSION_DOWNLOAD_REQUEST_destruct (
 LLRP_tSREADER_VERSION_DOWNLOAD_REQUEST * pThis);

extern void
LLRP_READER_VERSION_DOWNLOAD_REQUEST_decodeFields (
 LLRP_tSREADER_VERSION_DOWNLOAD_REQUEST * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_READER_VERSION_DOWNLOAD_REQUEST_assimilateSubParameters (
 LLRP_tSREADER_VERSION_DOWNLOAD_REQUEST * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_READER_VERSION_DOWNLOAD_REQUEST_encode (
  const LLRP_tSREADER_VERSION_DOWNLOAD_REQUEST *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSVersionDownloadRequest *
LLRP_READER_VERSION_DOWNLOAD_REQUEST_getVersionDownloadRequest (
  LLRP_tSREADER_VERSION_DOWNLOAD_REQUEST *pThis);

extern LLRP_tResultCode
LLRP_READER_VERSION_DOWNLOAD_REQUEST_setVersionDownloadRequest (
  LLRP_tSREADER_VERSION_DOWNLOAD_REQUEST *pThis,
  LLRP_tSVersionDownloadRequest *pValue);



  
struct LLRP_SREADER_VERSION_DOWNLOAD_REQUEST_RESPONS
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSLLRPStatus * pLLRPStatus;

    LLRP_tSVersionDownloadRequestAck * pVersionDownloadRequestAck;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdREADER_VERSION_DOWNLOAD_REQUEST_RESPONS;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdREADER_VERSION_DOWNLOAD_REQUEST_RESPONS[];

extern LLRP_tSREADER_VERSION_DOWNLOAD_REQUEST_RESPONS *
LLRP_READER_VERSION_DOWNLOAD_REQUEST_RESPONS_construct (void);

extern void
LLRP_READER_VERSION_DOWNLOAD_REQUEST_RESPONS_destruct (
 LLRP_tSREADER_VERSION_DOWNLOAD_REQUEST_RESPONS * pThis);

extern void
LLRP_READER_VERSION_DOWNLOAD_REQUEST_RESPONS_decodeFields (
 LLRP_tSREADER_VERSION_DOWNLOAD_REQUEST_RESPONS * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_READER_VERSION_DOWNLOAD_REQUEST_RESPONS_assimilateSubParameters (
 LLRP_tSREADER_VERSION_DOWNLOAD_REQUEST_RESPONS * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_READER_VERSION_DOWNLOAD_REQUEST_RESPONS_encode (
  const LLRP_tSREADER_VERSION_DOWNLOAD_REQUEST_RESPONS *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSLLRPStatus *
LLRP_READER_VERSION_DOWNLOAD_REQUEST_RESPONS_getLLRPStatus (
  LLRP_tSREADER_VERSION_DOWNLOAD_REQUEST_RESPONS *pThis);

extern LLRP_tResultCode
LLRP_READER_VERSION_DOWNLOAD_REQUEST_RESPONS_setLLRPStatus (
  LLRP_tSREADER_VERSION_DOWNLOAD_REQUEST_RESPONS *pThis,
  LLRP_tSLLRPStatus *pValue);

extern LLRP_tSVersionDownloadRequestAck *
LLRP_READER_VERSION_DOWNLOAD_REQUEST_RESPONS_getVersionDownloadRequestAck (
  LLRP_tSREADER_VERSION_DOWNLOAD_REQUEST_RESPONS *pThis);

extern LLRP_tResultCode
LLRP_READER_VERSION_DOWNLOAD_REQUEST_RESPONS_setVersionDownloadRequestAck (
  LLRP_tSREADER_VERSION_DOWNLOAD_REQUEST_RESPONS *pThis,
  LLRP_tSVersionDownloadRequestAck *pValue);



  
struct LLRP_SREADER_VERSION_DOWNLOAD
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSReaderVerDownload * pReaderVerDownload;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdREADER_VERSION_DOWNLOAD;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdREADER_VERSION_DOWNLOAD[];

extern LLRP_tSREADER_VERSION_DOWNLOAD *
LLRP_READER_VERSION_DOWNLOAD_construct (void);

extern void
LLRP_READER_VERSION_DOWNLOAD_destruct (
 LLRP_tSREADER_VERSION_DOWNLOAD * pThis);

extern void
LLRP_READER_VERSION_DOWNLOAD_decodeFields (
 LLRP_tSREADER_VERSION_DOWNLOAD * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_READER_VERSION_DOWNLOAD_assimilateSubParameters (
 LLRP_tSREADER_VERSION_DOWNLOAD * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_READER_VERSION_DOWNLOAD_encode (
  const LLRP_tSREADER_VERSION_DOWNLOAD *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSReaderVerDownload *
LLRP_READER_VERSION_DOWNLOAD_getReaderVerDownload (
  LLRP_tSREADER_VERSION_DOWNLOAD *pThis);

extern LLRP_tResultCode
LLRP_READER_VERSION_DOWNLOAD_setReaderVerDownload (
  LLRP_tSREADER_VERSION_DOWNLOAD *pThis,
  LLRP_tSReaderVerDownload *pValue);



  
struct LLRP_SREADER_VERSION_DOWNLOAD_RESPONS
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSLLRPStatus * pLLRPStatus;

    LLRP_tSVersionDownloadAck * pVersionDownloadAck;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdREADER_VERSION_DOWNLOAD_RESPONS;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdREADER_VERSION_DOWNLOAD_RESPONS[];

extern LLRP_tSREADER_VERSION_DOWNLOAD_RESPONS *
LLRP_READER_VERSION_DOWNLOAD_RESPONS_construct (void);

extern void
LLRP_READER_VERSION_DOWNLOAD_RESPONS_destruct (
 LLRP_tSREADER_VERSION_DOWNLOAD_RESPONS * pThis);

extern void
LLRP_READER_VERSION_DOWNLOAD_RESPONS_decodeFields (
 LLRP_tSREADER_VERSION_DOWNLOAD_RESPONS * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_READER_VERSION_DOWNLOAD_RESPONS_assimilateSubParameters (
 LLRP_tSREADER_VERSION_DOWNLOAD_RESPONS * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_READER_VERSION_DOWNLOAD_RESPONS_encode (
  const LLRP_tSREADER_VERSION_DOWNLOAD_RESPONS *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSLLRPStatus *
LLRP_READER_VERSION_DOWNLOAD_RESPONS_getLLRPStatus (
  LLRP_tSREADER_VERSION_DOWNLOAD_RESPONS *pThis);

extern LLRP_tResultCode
LLRP_READER_VERSION_DOWNLOAD_RESPONS_setLLRPStatus (
  LLRP_tSREADER_VERSION_DOWNLOAD_RESPONS *pThis,
  LLRP_tSLLRPStatus *pValue);

extern LLRP_tSVersionDownloadAck *
LLRP_READER_VERSION_DOWNLOAD_RESPONS_getVersionDownloadAck (
  LLRP_tSREADER_VERSION_DOWNLOAD_RESPONS *pThis);

extern LLRP_tResultCode
LLRP_READER_VERSION_DOWNLOAD_RESPONS_setVersionDownloadAck (
  LLRP_tSREADER_VERSION_DOWNLOAD_RESPONS *pThis,
  LLRP_tSVersionDownloadAck *pValue);



  
struct LLRP_SREADER_UBOOTVERSION_QUERY
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSBasicVerInfoSelect * pBasicVerInfoSelect;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdREADER_UBOOTVERSION_QUERY;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdREADER_UBOOTVERSION_QUERY[];

extern LLRP_tSREADER_UBOOTVERSION_QUERY *
LLRP_READER_UBOOTVERSION_QUERY_construct (void);

extern void
LLRP_READER_UBOOTVERSION_QUERY_destruct (
 LLRP_tSREADER_UBOOTVERSION_QUERY * pThis);

extern void
LLRP_READER_UBOOTVERSION_QUERY_decodeFields (
 LLRP_tSREADER_UBOOTVERSION_QUERY * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_READER_UBOOTVERSION_QUERY_assimilateSubParameters (
 LLRP_tSREADER_UBOOTVERSION_QUERY * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_READER_UBOOTVERSION_QUERY_encode (
  const LLRP_tSREADER_UBOOTVERSION_QUERY *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSBasicVerInfoSelect *
LLRP_READER_UBOOTVERSION_QUERY_getBasicVerInfoSelect (
  LLRP_tSREADER_UBOOTVERSION_QUERY *pThis);

extern LLRP_tResultCode
LLRP_READER_UBOOTVERSION_QUERY_setBasicVerInfoSelect (
  LLRP_tSREADER_UBOOTVERSION_QUERY *pThis,
  LLRP_tSBasicVerInfoSelect *pValue);



  
struct LLRP_SREADER_UBOOTVERSION_QUERY_RESPONS
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSLLRPStatus * pLLRPStatus;

    LLRP_tSVerInfoQueryAck * pVerInfoQueryAck;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdREADER_UBOOTVERSION_QUERY_RESPONS;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdREADER_UBOOTVERSION_QUERY_RESPONS[];

extern LLRP_tSREADER_UBOOTVERSION_QUERY_RESPONS *
LLRP_READER_UBOOTVERSION_QUERY_RESPONS_construct (void);

extern void
LLRP_READER_UBOOTVERSION_QUERY_RESPONS_destruct (
 LLRP_tSREADER_UBOOTVERSION_QUERY_RESPONS * pThis);

extern void
LLRP_READER_UBOOTVERSION_QUERY_RESPONS_decodeFields (
 LLRP_tSREADER_UBOOTVERSION_QUERY_RESPONS * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_READER_UBOOTVERSION_QUERY_RESPONS_assimilateSubParameters (
 LLRP_tSREADER_UBOOTVERSION_QUERY_RESPONS * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_READER_UBOOTVERSION_QUERY_RESPONS_encode (
  const LLRP_tSREADER_UBOOTVERSION_QUERY_RESPONS *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSLLRPStatus *
LLRP_READER_UBOOTVERSION_QUERY_RESPONS_getLLRPStatus (
  LLRP_tSREADER_UBOOTVERSION_QUERY_RESPONS *pThis);

extern LLRP_tResultCode
LLRP_READER_UBOOTVERSION_QUERY_RESPONS_setLLRPStatus (
  LLRP_tSREADER_UBOOTVERSION_QUERY_RESPONS *pThis,
  LLRP_tSLLRPStatus *pValue);

extern LLRP_tSVerInfoQueryAck *
LLRP_READER_UBOOTVERSION_QUERY_RESPONS_getVerInfoQueryAck (
  LLRP_tSREADER_UBOOTVERSION_QUERY_RESPONS *pThis);

extern LLRP_tResultCode
LLRP_READER_UBOOTVERSION_QUERY_RESPONS_setVerInfoQueryAck (
  LLRP_tSREADER_UBOOTVERSION_QUERY_RESPONS *pThis,
  LLRP_tSVerInfoQueryAck *pValue);



  
struct LLRP_SREADER_UBOOTVERSION_UPDATE
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSReaderVerDownload * pReaderVerDownload;

    LLRP_tSBasicVerInfoSelect * pBasicVerInfoSelect;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdREADER_UBOOTVERSION_UPDATE;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdREADER_UBOOTVERSION_UPDATE[];

extern LLRP_tSREADER_UBOOTVERSION_UPDATE *
LLRP_READER_UBOOTVERSION_UPDATE_construct (void);

extern void
LLRP_READER_UBOOTVERSION_UPDATE_destruct (
 LLRP_tSREADER_UBOOTVERSION_UPDATE * pThis);

extern void
LLRP_READER_UBOOTVERSION_UPDATE_decodeFields (
 LLRP_tSREADER_UBOOTVERSION_UPDATE * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_READER_UBOOTVERSION_UPDATE_assimilateSubParameters (
 LLRP_tSREADER_UBOOTVERSION_UPDATE * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_READER_UBOOTVERSION_UPDATE_encode (
  const LLRP_tSREADER_UBOOTVERSION_UPDATE *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSReaderVerDownload *
LLRP_READER_UBOOTVERSION_UPDATE_getReaderVerDownload (
  LLRP_tSREADER_UBOOTVERSION_UPDATE *pThis);

extern LLRP_tResultCode
LLRP_READER_UBOOTVERSION_UPDATE_setReaderVerDownload (
  LLRP_tSREADER_UBOOTVERSION_UPDATE *pThis,
  LLRP_tSReaderVerDownload *pValue);

extern LLRP_tSBasicVerInfoSelect *
LLRP_READER_UBOOTVERSION_UPDATE_getBasicVerInfoSelect (
  LLRP_tSREADER_UBOOTVERSION_UPDATE *pThis);

extern LLRP_tResultCode
LLRP_READER_UBOOTVERSION_UPDATE_setBasicVerInfoSelect (
  LLRP_tSREADER_UBOOTVERSION_UPDATE *pThis,
  LLRP_tSBasicVerInfoSelect *pValue);



  
struct LLRP_SREADER_UBOOTVERSION_UPDATE_RESPONS
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSLLRPStatus * pLLRPStatus;

    LLRP_tSVersionDownloadAck * pVersionDownloadAck;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdREADER_UBOOTVERSION_UPDATE_RESPONS;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdREADER_UBOOTVERSION_UPDATE_RESPONS[];

extern LLRP_tSREADER_UBOOTVERSION_UPDATE_RESPONS *
LLRP_READER_UBOOTVERSION_UPDATE_RESPONS_construct (void);

extern void
LLRP_READER_UBOOTVERSION_UPDATE_RESPONS_destruct (
 LLRP_tSREADER_UBOOTVERSION_UPDATE_RESPONS * pThis);

extern void
LLRP_READER_UBOOTVERSION_UPDATE_RESPONS_decodeFields (
 LLRP_tSREADER_UBOOTVERSION_UPDATE_RESPONS * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_READER_UBOOTVERSION_UPDATE_RESPONS_assimilateSubParameters (
 LLRP_tSREADER_UBOOTVERSION_UPDATE_RESPONS * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_READER_UBOOTVERSION_UPDATE_RESPONS_encode (
  const LLRP_tSREADER_UBOOTVERSION_UPDATE_RESPONS *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSLLRPStatus *
LLRP_READER_UBOOTVERSION_UPDATE_RESPONS_getLLRPStatus (
  LLRP_tSREADER_UBOOTVERSION_UPDATE_RESPONS *pThis);

extern LLRP_tResultCode
LLRP_READER_UBOOTVERSION_UPDATE_RESPONS_setLLRPStatus (
  LLRP_tSREADER_UBOOTVERSION_UPDATE_RESPONS *pThis,
  LLRP_tSLLRPStatus *pValue);

extern LLRP_tSVersionDownloadAck *
LLRP_READER_UBOOTVERSION_UPDATE_RESPONS_getVersionDownloadAck (
  LLRP_tSREADER_UBOOTVERSION_UPDATE_RESPONS *pThis);

extern LLRP_tResultCode
LLRP_READER_UBOOTVERSION_UPDATE_RESPONS_setVersionDownloadAck (
  LLRP_tSREADER_UBOOTVERSION_UPDATE_RESPONS *pThis,
  LLRP_tSVersionDownloadAck *pValue);



  
struct LLRP_SSP_VERSION_QUERY
{
    LLRP_tSMessage hdr;
  
  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdSP_VERSION_QUERY;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSP_VERSION_QUERY[];

extern LLRP_tSSP_VERSION_QUERY *
LLRP_SP_VERSION_QUERY_construct (void);

extern void
LLRP_SP_VERSION_QUERY_destruct (
 LLRP_tSSP_VERSION_QUERY * pThis);

extern void
LLRP_SP_VERSION_QUERY_decodeFields (
 LLRP_tSSP_VERSION_QUERY * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SP_VERSION_QUERY_assimilateSubParameters (
 LLRP_tSSP_VERSION_QUERY * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SP_VERSION_QUERY_encode (
  const LLRP_tSSP_VERSION_QUERY *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  


  
struct LLRP_SSP_VERSION_QUERY_RESPONSE
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSLLRPStatus * pLLRPStatus;

    LLRP_tSSPVerInfoQueryResponse * pSPVerInfoQueryResponse;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdSP_VERSION_QUERY_RESPONSE;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSP_VERSION_QUERY_RESPONSE[];

extern LLRP_tSSP_VERSION_QUERY_RESPONSE *
LLRP_SP_VERSION_QUERY_RESPONSE_construct (void);

extern void
LLRP_SP_VERSION_QUERY_RESPONSE_destruct (
 LLRP_tSSP_VERSION_QUERY_RESPONSE * pThis);

extern void
LLRP_SP_VERSION_QUERY_RESPONSE_decodeFields (
 LLRP_tSSP_VERSION_QUERY_RESPONSE * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SP_VERSION_QUERY_RESPONSE_assimilateSubParameters (
 LLRP_tSSP_VERSION_QUERY_RESPONSE * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SP_VERSION_QUERY_RESPONSE_encode (
  const LLRP_tSSP_VERSION_QUERY_RESPONSE *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSLLRPStatus *
LLRP_SP_VERSION_QUERY_RESPONSE_getLLRPStatus (
  LLRP_tSSP_VERSION_QUERY_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_SP_VERSION_QUERY_RESPONSE_setLLRPStatus (
  LLRP_tSSP_VERSION_QUERY_RESPONSE *pThis,
  LLRP_tSLLRPStatus *pValue);

extern LLRP_tSSPVerInfoQueryResponse *
LLRP_SP_VERSION_QUERY_RESPONSE_getSPVerInfoQueryResponse (
  LLRP_tSSP_VERSION_QUERY_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_SP_VERSION_QUERY_RESPONSE_setSPVerInfoQueryResponse (
  LLRP_tSSP_VERSION_QUERY_RESPONSE *pThis,
  LLRP_tSSPVerInfoQueryResponse *pValue);



  
struct LLRP_SSP_VERSION_DOWNLOAD
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSReaderVerDownload * pReaderVerDownload;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdSP_VERSION_DOWNLOAD;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSP_VERSION_DOWNLOAD[];

extern LLRP_tSSP_VERSION_DOWNLOAD *
LLRP_SP_VERSION_DOWNLOAD_construct (void);

extern void
LLRP_SP_VERSION_DOWNLOAD_destruct (
 LLRP_tSSP_VERSION_DOWNLOAD * pThis);

extern void
LLRP_SP_VERSION_DOWNLOAD_decodeFields (
 LLRP_tSSP_VERSION_DOWNLOAD * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SP_VERSION_DOWNLOAD_assimilateSubParameters (
 LLRP_tSSP_VERSION_DOWNLOAD * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SP_VERSION_DOWNLOAD_encode (
  const LLRP_tSSP_VERSION_DOWNLOAD *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSReaderVerDownload *
LLRP_SP_VERSION_DOWNLOAD_getReaderVerDownload (
  LLRP_tSSP_VERSION_DOWNLOAD *pThis);

extern LLRP_tResultCode
LLRP_SP_VERSION_DOWNLOAD_setReaderVerDownload (
  LLRP_tSSP_VERSION_DOWNLOAD *pThis,
  LLRP_tSReaderVerDownload *pValue);



  
struct LLRP_SSP_VERSION_DOWNLOAD_RESPONSE
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSLLRPStatus * pLLRPStatus;

    LLRP_tSVersionDownloadAck * pVersionDownloadAck;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdSP_VERSION_DOWNLOAD_RESPONSE;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSP_VERSION_DOWNLOAD_RESPONSE[];

extern LLRP_tSSP_VERSION_DOWNLOAD_RESPONSE *
LLRP_SP_VERSION_DOWNLOAD_RESPONSE_construct (void);

extern void
LLRP_SP_VERSION_DOWNLOAD_RESPONSE_destruct (
 LLRP_tSSP_VERSION_DOWNLOAD_RESPONSE * pThis);

extern void
LLRP_SP_VERSION_DOWNLOAD_RESPONSE_decodeFields (
 LLRP_tSSP_VERSION_DOWNLOAD_RESPONSE * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SP_VERSION_DOWNLOAD_RESPONSE_assimilateSubParameters (
 LLRP_tSSP_VERSION_DOWNLOAD_RESPONSE * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SP_VERSION_DOWNLOAD_RESPONSE_encode (
  const LLRP_tSSP_VERSION_DOWNLOAD_RESPONSE *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSLLRPStatus *
LLRP_SP_VERSION_DOWNLOAD_RESPONSE_getLLRPStatus (
  LLRP_tSSP_VERSION_DOWNLOAD_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_SP_VERSION_DOWNLOAD_RESPONSE_setLLRPStatus (
  LLRP_tSSP_VERSION_DOWNLOAD_RESPONSE *pThis,
  LLRP_tSLLRPStatus *pValue);

extern LLRP_tSVersionDownloadAck *
LLRP_SP_VERSION_DOWNLOAD_RESPONSE_getVersionDownloadAck (
  LLRP_tSSP_VERSION_DOWNLOAD_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_SP_VERSION_DOWNLOAD_RESPONSE_setVersionDownloadAck (
  LLRP_tSSP_VERSION_DOWNLOAD_RESPONSE *pThis,
  LLRP_tSVersionDownloadAck *pValue);



  
struct LLRP_SSP_VERSION_DELETE
{
    LLRP_tSMessage hdr;
  
  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdSP_VERSION_DELETE;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSP_VERSION_DELETE[];

extern LLRP_tSSP_VERSION_DELETE *
LLRP_SP_VERSION_DELETE_construct (void);

extern void
LLRP_SP_VERSION_DELETE_destruct (
 LLRP_tSSP_VERSION_DELETE * pThis);

extern void
LLRP_SP_VERSION_DELETE_decodeFields (
 LLRP_tSSP_VERSION_DELETE * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SP_VERSION_DELETE_assimilateSubParameters (
 LLRP_tSSP_VERSION_DELETE * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SP_VERSION_DELETE_encode (
  const LLRP_tSSP_VERSION_DELETE *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  


  
struct LLRP_SSP_VERSION_DELETE_RESPONSE
{
    LLRP_tSMessage hdr;
  
    llrp_u32_t dwResult;

  
    LLRP_tSLLRPStatus * pLLRPStatus;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdSP_VERSION_DELETE_RESPONSE;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSP_VERSION_DELETE_RESPONSE[];

extern LLRP_tSSP_VERSION_DELETE_RESPONSE *
LLRP_SP_VERSION_DELETE_RESPONSE_construct (void);

extern void
LLRP_SP_VERSION_DELETE_RESPONSE_destruct (
 LLRP_tSSP_VERSION_DELETE_RESPONSE * pThis);

extern void
LLRP_SP_VERSION_DELETE_RESPONSE_decodeFields (
 LLRP_tSSP_VERSION_DELETE_RESPONSE * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SP_VERSION_DELETE_RESPONSE_assimilateSubParameters (
 LLRP_tSSP_VERSION_DELETE_RESPONSE * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SP_VERSION_DELETE_RESPONSE_encode (
  const LLRP_tSSP_VERSION_DELETE_RESPONSE *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdSP_VERSION_DELETE_RESPONSE_dwResult;

extern llrp_u32_t
LLRP_SP_VERSION_DELETE_RESPONSE_getdwResult (
  LLRP_tSSP_VERSION_DELETE_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_SP_VERSION_DELETE_RESPONSE_setdwResult (
  LLRP_tSSP_VERSION_DELETE_RESPONSE *pThis,
  llrp_u32_t Value);

  
extern LLRP_tSLLRPStatus *
LLRP_SP_VERSION_DELETE_RESPONSE_getLLRPStatus (
  LLRP_tSSP_VERSION_DELETE_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_SP_VERSION_DELETE_RESPONSE_setLLRPStatus (
  LLRP_tSSP_VERSION_DELETE_RESPONSE *pThis,
  LLRP_tSLLRPStatus *pValue);



  
struct LLRP_SGET_READER_LOG
{
    LLRP_tSMessage hdr;
  
  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdGET_READER_LOG;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdGET_READER_LOG[];

extern LLRP_tSGET_READER_LOG *
LLRP_GET_READER_LOG_construct (void);

extern void
LLRP_GET_READER_LOG_destruct (
 LLRP_tSGET_READER_LOG * pThis);

extern void
LLRP_GET_READER_LOG_decodeFields (
 LLRP_tSGET_READER_LOG * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_GET_READER_LOG_assimilateSubParameters (
 LLRP_tSGET_READER_LOG * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_GET_READER_LOG_encode (
  const LLRP_tSGET_READER_LOG *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  


  
struct LLRP_SGET_READER_LOG_RESPONSE
{
    LLRP_tSMessage hdr;
  
    llrp_u16_t SequenceId;

    llrp_u8_t IsLastedFrame;

  
    LLRP_tSReaderRunLog * listReaderRunLog;

    LLRP_tSRUPReaderRunLog * listRUPReaderRunLog;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdGET_READER_LOG_RESPONSE;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdGET_READER_LOG_RESPONSE[];

extern LLRP_tSGET_READER_LOG_RESPONSE *
LLRP_GET_READER_LOG_RESPONSE_construct (void);

extern void
LLRP_GET_READER_LOG_RESPONSE_destruct (
 LLRP_tSGET_READER_LOG_RESPONSE * pThis);

extern void
LLRP_GET_READER_LOG_RESPONSE_decodeFields (
 LLRP_tSGET_READER_LOG_RESPONSE * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_GET_READER_LOG_RESPONSE_assimilateSubParameters (
 LLRP_tSGET_READER_LOG_RESPONSE * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_GET_READER_LOG_RESPONSE_encode (
  const LLRP_tSGET_READER_LOG_RESPONSE *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdGET_READER_LOG_RESPONSE_SequenceId;

extern llrp_u16_t
LLRP_GET_READER_LOG_RESPONSE_getSequenceId (
  LLRP_tSGET_READER_LOG_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_LOG_RESPONSE_setSequenceId (
  LLRP_tSGET_READER_LOG_RESPONSE *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdGET_READER_LOG_RESPONSE_IsLastedFrame;

extern llrp_u8_t
LLRP_GET_READER_LOG_RESPONSE_getIsLastedFrame (
  LLRP_tSGET_READER_LOG_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_LOG_RESPONSE_setIsLastedFrame (
  LLRP_tSGET_READER_LOG_RESPONSE *pThis,
  llrp_u8_t Value);

  
extern LLRP_tSReaderRunLog *
LLRP_GET_READER_LOG_RESPONSE_beginReaderRunLog (
  LLRP_tSGET_READER_LOG_RESPONSE *pThis);

extern LLRP_tSReaderRunLog *
LLRP_GET_READER_LOG_RESPONSE_nextReaderRunLog (
  LLRP_tSReaderRunLog *pCurrent);

extern void
LLRP_GET_READER_LOG_RESPONSE_clearReaderRunLog (
  LLRP_tSGET_READER_LOG_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_LOG_RESPONSE_addReaderRunLog (
  LLRP_tSGET_READER_LOG_RESPONSE *pThis,
  LLRP_tSReaderRunLog *pValue);


extern LLRP_tSRUPReaderRunLog *
LLRP_GET_READER_LOG_RESPONSE_beginRUPReaderRunLog (
  LLRP_tSGET_READER_LOG_RESPONSE *pThis);

extern LLRP_tSRUPReaderRunLog *
LLRP_GET_READER_LOG_RESPONSE_nextRUPReaderRunLog (
  LLRP_tSRUPReaderRunLog *pCurrent);

extern void
LLRP_GET_READER_LOG_RESPONSE_clearRUPReaderRunLog (
  LLRP_tSGET_READER_LOG_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_LOG_RESPONSE_addRUPReaderRunLog (
  LLRP_tSGET_READER_LOG_RESPONSE *pThis,
  LLRP_tSRUPReaderRunLog *pValue);




  
struct LLRP_SGET_READER_LOG_RESPONSE_ACK
{
    LLRP_tSMessage hdr;
  
    llrp_u16_t SequenceId;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdGET_READER_LOG_RESPONSE_ACK;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdGET_READER_LOG_RESPONSE_ACK[];

extern LLRP_tSGET_READER_LOG_RESPONSE_ACK *
LLRP_GET_READER_LOG_RESPONSE_ACK_construct (void);

extern void
LLRP_GET_READER_LOG_RESPONSE_ACK_destruct (
 LLRP_tSGET_READER_LOG_RESPONSE_ACK * pThis);

extern void
LLRP_GET_READER_LOG_RESPONSE_ACK_decodeFields (
 LLRP_tSGET_READER_LOG_RESPONSE_ACK * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_GET_READER_LOG_RESPONSE_ACK_assimilateSubParameters (
 LLRP_tSGET_READER_LOG_RESPONSE_ACK * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_GET_READER_LOG_RESPONSE_ACK_encode (
  const LLRP_tSGET_READER_LOG_RESPONSE_ACK *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdGET_READER_LOG_RESPONSE_ACK_SequenceId;

extern llrp_u16_t
LLRP_GET_READER_LOG_RESPONSE_ACK_getSequenceId (
  LLRP_tSGET_READER_LOG_RESPONSE_ACK *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_LOG_RESPONSE_ACK_setSequenceId (
  LLRP_tSGET_READER_LOG_RESPONSE_ACK *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_SGET_READER_EXCEPTION
{
    LLRP_tSMessage hdr;
  
  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdGET_READER_EXCEPTION;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdGET_READER_EXCEPTION[];

extern LLRP_tSGET_READER_EXCEPTION *
LLRP_GET_READER_EXCEPTION_construct (void);

extern void
LLRP_GET_READER_EXCEPTION_destruct (
 LLRP_tSGET_READER_EXCEPTION * pThis);

extern void
LLRP_GET_READER_EXCEPTION_decodeFields (
 LLRP_tSGET_READER_EXCEPTION * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_GET_READER_EXCEPTION_assimilateSubParameters (
 LLRP_tSGET_READER_EXCEPTION * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_GET_READER_EXCEPTION_encode (
  const LLRP_tSGET_READER_EXCEPTION *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  


  
struct LLRP_SGET_READER_EXCEPTION_RESPONSE
{
    LLRP_tSMessage hdr;
  
    llrp_u16_t SequenceId;

    llrp_u8_t IsLastedFrame;

  
    LLRP_tSReaderRunException * listReaderRunException;

    LLRP_tSRUPReaderRunException * listRUPReaderRunException;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdGET_READER_EXCEPTION_RESPONSE;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdGET_READER_EXCEPTION_RESPONSE[];

extern LLRP_tSGET_READER_EXCEPTION_RESPONSE *
LLRP_GET_READER_EXCEPTION_RESPONSE_construct (void);

extern void
LLRP_GET_READER_EXCEPTION_RESPONSE_destruct (
 LLRP_tSGET_READER_EXCEPTION_RESPONSE * pThis);

extern void
LLRP_GET_READER_EXCEPTION_RESPONSE_decodeFields (
 LLRP_tSGET_READER_EXCEPTION_RESPONSE * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_GET_READER_EXCEPTION_RESPONSE_assimilateSubParameters (
 LLRP_tSGET_READER_EXCEPTION_RESPONSE * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_GET_READER_EXCEPTION_RESPONSE_encode (
  const LLRP_tSGET_READER_EXCEPTION_RESPONSE *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdGET_READER_EXCEPTION_RESPONSE_SequenceId;

extern llrp_u16_t
LLRP_GET_READER_EXCEPTION_RESPONSE_getSequenceId (
  LLRP_tSGET_READER_EXCEPTION_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_EXCEPTION_RESPONSE_setSequenceId (
  LLRP_tSGET_READER_EXCEPTION_RESPONSE *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdGET_READER_EXCEPTION_RESPONSE_IsLastedFrame;

extern llrp_u8_t
LLRP_GET_READER_EXCEPTION_RESPONSE_getIsLastedFrame (
  LLRP_tSGET_READER_EXCEPTION_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_EXCEPTION_RESPONSE_setIsLastedFrame (
  LLRP_tSGET_READER_EXCEPTION_RESPONSE *pThis,
  llrp_u8_t Value);

  
extern LLRP_tSReaderRunException *
LLRP_GET_READER_EXCEPTION_RESPONSE_beginReaderRunException (
  LLRP_tSGET_READER_EXCEPTION_RESPONSE *pThis);

extern LLRP_tSReaderRunException *
LLRP_GET_READER_EXCEPTION_RESPONSE_nextReaderRunException (
  LLRP_tSReaderRunException *pCurrent);

extern void
LLRP_GET_READER_EXCEPTION_RESPONSE_clearReaderRunException (
  LLRP_tSGET_READER_EXCEPTION_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_EXCEPTION_RESPONSE_addReaderRunException (
  LLRP_tSGET_READER_EXCEPTION_RESPONSE *pThis,
  LLRP_tSReaderRunException *pValue);


extern LLRP_tSRUPReaderRunException *
LLRP_GET_READER_EXCEPTION_RESPONSE_beginRUPReaderRunException (
  LLRP_tSGET_READER_EXCEPTION_RESPONSE *pThis);

extern LLRP_tSRUPReaderRunException *
LLRP_GET_READER_EXCEPTION_RESPONSE_nextRUPReaderRunException (
  LLRP_tSRUPReaderRunException *pCurrent);

extern void
LLRP_GET_READER_EXCEPTION_RESPONSE_clearRUPReaderRunException (
  LLRP_tSGET_READER_EXCEPTION_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_EXCEPTION_RESPONSE_addRUPReaderRunException (
  LLRP_tSGET_READER_EXCEPTION_RESPONSE *pThis,
  LLRP_tSRUPReaderRunException *pValue);




  
struct LLRP_SGET_READER_EXCEPTION_RESPONSE_ACK
{
    LLRP_tSMessage hdr;
  
    llrp_u16_t SequenceId;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdGET_READER_EXCEPTION_RESPONSE_ACK;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdGET_READER_EXCEPTION_RESPONSE_ACK[];

extern LLRP_tSGET_READER_EXCEPTION_RESPONSE_ACK *
LLRP_GET_READER_EXCEPTION_RESPONSE_ACK_construct (void);

extern void
LLRP_GET_READER_EXCEPTION_RESPONSE_ACK_destruct (
 LLRP_tSGET_READER_EXCEPTION_RESPONSE_ACK * pThis);

extern void
LLRP_GET_READER_EXCEPTION_RESPONSE_ACK_decodeFields (
 LLRP_tSGET_READER_EXCEPTION_RESPONSE_ACK * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_GET_READER_EXCEPTION_RESPONSE_ACK_assimilateSubParameters (
 LLRP_tSGET_READER_EXCEPTION_RESPONSE_ACK * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_GET_READER_EXCEPTION_RESPONSE_ACK_encode (
  const LLRP_tSGET_READER_EXCEPTION_RESPONSE_ACK *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdGET_READER_EXCEPTION_RESPONSE_ACK_SequenceId;

extern llrp_u16_t
LLRP_GET_READER_EXCEPTION_RESPONSE_ACK_getSequenceId (
  LLRP_tSGET_READER_EXCEPTION_RESPONSE_ACK *pThis);

extern LLRP_tResultCode
LLRP_GET_READER_EXCEPTION_RESPONSE_ACK_setSequenceId (
  LLRP_tSGET_READER_EXCEPTION_RESPONSE_ACK *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_SDELETE_TAG_MEMORY_DEF_TABLE
{
    LLRP_tSMessage hdr;
  
    llrp_u16_t TableID;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdDELETE_TAG_MEMORY_DEF_TABLE;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdDELETE_TAG_MEMORY_DEF_TABLE[];

extern LLRP_tSDELETE_TAG_MEMORY_DEF_TABLE *
LLRP_DELETE_TAG_MEMORY_DEF_TABLE_construct (void);

extern void
LLRP_DELETE_TAG_MEMORY_DEF_TABLE_destruct (
 LLRP_tSDELETE_TAG_MEMORY_DEF_TABLE * pThis);

extern void
LLRP_DELETE_TAG_MEMORY_DEF_TABLE_decodeFields (
 LLRP_tSDELETE_TAG_MEMORY_DEF_TABLE * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_DELETE_TAG_MEMORY_DEF_TABLE_assimilateSubParameters (
 LLRP_tSDELETE_TAG_MEMORY_DEF_TABLE * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_DELETE_TAG_MEMORY_DEF_TABLE_encode (
  const LLRP_tSDELETE_TAG_MEMORY_DEF_TABLE *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdDELETE_TAG_MEMORY_DEF_TABLE_TableID;

extern llrp_u16_t
LLRP_DELETE_TAG_MEMORY_DEF_TABLE_getTableID (
  LLRP_tSDELETE_TAG_MEMORY_DEF_TABLE *pThis);

extern LLRP_tResultCode
LLRP_DELETE_TAG_MEMORY_DEF_TABLE_setTableID (
  LLRP_tSDELETE_TAG_MEMORY_DEF_TABLE *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_SDELETE_TAG_MEMORY_DEF_TABLE_RESPONSE
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSLLRPStatus * pLLRPStatus;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdDELETE_TAG_MEMORY_DEF_TABLE_RESPONSE;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdDELETE_TAG_MEMORY_DEF_TABLE_RESPONSE[];

extern LLRP_tSDELETE_TAG_MEMORY_DEF_TABLE_RESPONSE *
LLRP_DELETE_TAG_MEMORY_DEF_TABLE_RESPONSE_construct (void);

extern void
LLRP_DELETE_TAG_MEMORY_DEF_TABLE_RESPONSE_destruct (
 LLRP_tSDELETE_TAG_MEMORY_DEF_TABLE_RESPONSE * pThis);

extern void
LLRP_DELETE_TAG_MEMORY_DEF_TABLE_RESPONSE_decodeFields (
 LLRP_tSDELETE_TAG_MEMORY_DEF_TABLE_RESPONSE * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_DELETE_TAG_MEMORY_DEF_TABLE_RESPONSE_assimilateSubParameters (
 LLRP_tSDELETE_TAG_MEMORY_DEF_TABLE_RESPONSE * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_DELETE_TAG_MEMORY_DEF_TABLE_RESPONSE_encode (
  const LLRP_tSDELETE_TAG_MEMORY_DEF_TABLE_RESPONSE *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSLLRPStatus *
LLRP_DELETE_TAG_MEMORY_DEF_TABLE_RESPONSE_getLLRPStatus (
  LLRP_tSDELETE_TAG_MEMORY_DEF_TABLE_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_DELETE_TAG_MEMORY_DEF_TABLE_RESPONSE_setLLRPStatus (
  LLRP_tSDELETE_TAG_MEMORY_DEF_TABLE_RESPONSE *pThis,
  LLRP_tSLLRPStatus *pValue);



  
struct LLRP_SHF_ENTRANCEGUARD_LOGIC_CARD
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSLogicCardCmd * pLogicCardCmd;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdHF_ENTRANCEGUARD_LOGIC_CARD;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdHF_ENTRANCEGUARD_LOGIC_CARD[];

extern LLRP_tSHF_ENTRANCEGUARD_LOGIC_CARD *
LLRP_HF_ENTRANCEGUARD_LOGIC_CARD_construct (void);

extern void
LLRP_HF_ENTRANCEGUARD_LOGIC_CARD_destruct (
 LLRP_tSHF_ENTRANCEGUARD_LOGIC_CARD * pThis);

extern void
LLRP_HF_ENTRANCEGUARD_LOGIC_CARD_decodeFields (
 LLRP_tSHF_ENTRANCEGUARD_LOGIC_CARD * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_HF_ENTRANCEGUARD_LOGIC_CARD_assimilateSubParameters (
 LLRP_tSHF_ENTRANCEGUARD_LOGIC_CARD * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_HF_ENTRANCEGUARD_LOGIC_CARD_encode (
  const LLRP_tSHF_ENTRANCEGUARD_LOGIC_CARD *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSLogicCardCmd *
LLRP_HF_ENTRANCEGUARD_LOGIC_CARD_getLogicCardCmd (
  LLRP_tSHF_ENTRANCEGUARD_LOGIC_CARD *pThis);

extern LLRP_tResultCode
LLRP_HF_ENTRANCEGUARD_LOGIC_CARD_setLogicCardCmd (
  LLRP_tSHF_ENTRANCEGUARD_LOGIC_CARD *pThis,
  LLRP_tSLogicCardCmd *pValue);



  
struct LLRP_SHF_ENTRANCEGUARD_LOGIC_CARD_RESPONSE
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSLLRPStatus * pLLRPStatus;

    LLRP_tSLogicCardRsp * pLogicCardRsp;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdHF_ENTRANCEGUARD_LOGIC_CARD_RESPONSE;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdHF_ENTRANCEGUARD_LOGIC_CARD_RESPONSE[];

extern LLRP_tSHF_ENTRANCEGUARD_LOGIC_CARD_RESPONSE *
LLRP_HF_ENTRANCEGUARD_LOGIC_CARD_RESPONSE_construct (void);

extern void
LLRP_HF_ENTRANCEGUARD_LOGIC_CARD_RESPONSE_destruct (
 LLRP_tSHF_ENTRANCEGUARD_LOGIC_CARD_RESPONSE * pThis);

extern void
LLRP_HF_ENTRANCEGUARD_LOGIC_CARD_RESPONSE_decodeFields (
 LLRP_tSHF_ENTRANCEGUARD_LOGIC_CARD_RESPONSE * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_HF_ENTRANCEGUARD_LOGIC_CARD_RESPONSE_assimilateSubParameters (
 LLRP_tSHF_ENTRANCEGUARD_LOGIC_CARD_RESPONSE * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_HF_ENTRANCEGUARD_LOGIC_CARD_RESPONSE_encode (
  const LLRP_tSHF_ENTRANCEGUARD_LOGIC_CARD_RESPONSE *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSLLRPStatus *
LLRP_HF_ENTRANCEGUARD_LOGIC_CARD_RESPONSE_getLLRPStatus (
  LLRP_tSHF_ENTRANCEGUARD_LOGIC_CARD_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_HF_ENTRANCEGUARD_LOGIC_CARD_RESPONSE_setLLRPStatus (
  LLRP_tSHF_ENTRANCEGUARD_LOGIC_CARD_RESPONSE *pThis,
  LLRP_tSLLRPStatus *pValue);

extern LLRP_tSLogicCardRsp *
LLRP_HF_ENTRANCEGUARD_LOGIC_CARD_RESPONSE_getLogicCardRsp (
  LLRP_tSHF_ENTRANCEGUARD_LOGIC_CARD_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_HF_ENTRANCEGUARD_LOGIC_CARD_RESPONSE_setLogicCardRsp (
  LLRP_tSHF_ENTRANCEGUARD_LOGIC_CARD_RESPONSE *pThis,
  LLRP_tSLogicCardRsp *pValue);



  
struct LLRP_SHF_ENTRANCEGUARD_CPU_CARD
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSCpuCardCmd * pCpuCardCmd;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdHF_ENTRANCEGUARD_CPU_CARD;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdHF_ENTRANCEGUARD_CPU_CARD[];

extern LLRP_tSHF_ENTRANCEGUARD_CPU_CARD *
LLRP_HF_ENTRANCEGUARD_CPU_CARD_construct (void);

extern void
LLRP_HF_ENTRANCEGUARD_CPU_CARD_destruct (
 LLRP_tSHF_ENTRANCEGUARD_CPU_CARD * pThis);

extern void
LLRP_HF_ENTRANCEGUARD_CPU_CARD_decodeFields (
 LLRP_tSHF_ENTRANCEGUARD_CPU_CARD * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_HF_ENTRANCEGUARD_CPU_CARD_assimilateSubParameters (
 LLRP_tSHF_ENTRANCEGUARD_CPU_CARD * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_HF_ENTRANCEGUARD_CPU_CARD_encode (
  const LLRP_tSHF_ENTRANCEGUARD_CPU_CARD *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSCpuCardCmd *
LLRP_HF_ENTRANCEGUARD_CPU_CARD_getCpuCardCmd (
  LLRP_tSHF_ENTRANCEGUARD_CPU_CARD *pThis);

extern LLRP_tResultCode
LLRP_HF_ENTRANCEGUARD_CPU_CARD_setCpuCardCmd (
  LLRP_tSHF_ENTRANCEGUARD_CPU_CARD *pThis,
  LLRP_tSCpuCardCmd *pValue);



  
struct LLRP_SHF_ENTRANCEGUARD_CPU_CARD_RESPONSE
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSLLRPStatus * pLLRPStatus;

    LLRP_tSCpuCardCmd * pCpuCardCmd;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdHF_ENTRANCEGUARD_CPU_CARD_RESPONSE;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdHF_ENTRANCEGUARD_CPU_CARD_RESPONSE[];

extern LLRP_tSHF_ENTRANCEGUARD_CPU_CARD_RESPONSE *
LLRP_HF_ENTRANCEGUARD_CPU_CARD_RESPONSE_construct (void);

extern void
LLRP_HF_ENTRANCEGUARD_CPU_CARD_RESPONSE_destruct (
 LLRP_tSHF_ENTRANCEGUARD_CPU_CARD_RESPONSE * pThis);

extern void
LLRP_HF_ENTRANCEGUARD_CPU_CARD_RESPONSE_decodeFields (
 LLRP_tSHF_ENTRANCEGUARD_CPU_CARD_RESPONSE * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_HF_ENTRANCEGUARD_CPU_CARD_RESPONSE_assimilateSubParameters (
 LLRP_tSHF_ENTRANCEGUARD_CPU_CARD_RESPONSE * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_HF_ENTRANCEGUARD_CPU_CARD_RESPONSE_encode (
  const LLRP_tSHF_ENTRANCEGUARD_CPU_CARD_RESPONSE *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSLLRPStatus *
LLRP_HF_ENTRANCEGUARD_CPU_CARD_RESPONSE_getLLRPStatus (
  LLRP_tSHF_ENTRANCEGUARD_CPU_CARD_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_HF_ENTRANCEGUARD_CPU_CARD_RESPONSE_setLLRPStatus (
  LLRP_tSHF_ENTRANCEGUARD_CPU_CARD_RESPONSE *pThis,
  LLRP_tSLLRPStatus *pValue);

extern LLRP_tSCpuCardCmd *
LLRP_HF_ENTRANCEGUARD_CPU_CARD_RESPONSE_getCpuCardCmd (
  LLRP_tSHF_ENTRANCEGUARD_CPU_CARD_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_HF_ENTRANCEGUARD_CPU_CARD_RESPONSE_setCpuCardCmd (
  LLRP_tSHF_ENTRANCEGUARD_CPU_CARD_RESPONSE *pThis,
  LLRP_tSCpuCardCmd *pValue);



  
struct LLRP_SHF_ENTRANCEGUARD_DEVICE
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSDeviceCmd * pDeviceCmd;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdHF_ENTRANCEGUARD_DEVICE;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdHF_ENTRANCEGUARD_DEVICE[];

extern LLRP_tSHF_ENTRANCEGUARD_DEVICE *
LLRP_HF_ENTRANCEGUARD_DEVICE_construct (void);

extern void
LLRP_HF_ENTRANCEGUARD_DEVICE_destruct (
 LLRP_tSHF_ENTRANCEGUARD_DEVICE * pThis);

extern void
LLRP_HF_ENTRANCEGUARD_DEVICE_decodeFields (
 LLRP_tSHF_ENTRANCEGUARD_DEVICE * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_HF_ENTRANCEGUARD_DEVICE_assimilateSubParameters (
 LLRP_tSHF_ENTRANCEGUARD_DEVICE * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_HF_ENTRANCEGUARD_DEVICE_encode (
  const LLRP_tSHF_ENTRANCEGUARD_DEVICE *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSDeviceCmd *
LLRP_HF_ENTRANCEGUARD_DEVICE_getDeviceCmd (
  LLRP_tSHF_ENTRANCEGUARD_DEVICE *pThis);

extern LLRP_tResultCode
LLRP_HF_ENTRANCEGUARD_DEVICE_setDeviceCmd (
  LLRP_tSHF_ENTRANCEGUARD_DEVICE *pThis,
  LLRP_tSDeviceCmd *pValue);



  
struct LLRP_SHF_ENTRANCEGUARD_DEVICE_RESPONSE
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSLLRPStatus * pLLRPStatus;

    LLRP_tSDeviceCmd * pDeviceCmd;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdHF_ENTRANCEGUARD_DEVICE_RESPONSE;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdHF_ENTRANCEGUARD_DEVICE_RESPONSE[];

extern LLRP_tSHF_ENTRANCEGUARD_DEVICE_RESPONSE *
LLRP_HF_ENTRANCEGUARD_DEVICE_RESPONSE_construct (void);

extern void
LLRP_HF_ENTRANCEGUARD_DEVICE_RESPONSE_destruct (
 LLRP_tSHF_ENTRANCEGUARD_DEVICE_RESPONSE * pThis);

extern void
LLRP_HF_ENTRANCEGUARD_DEVICE_RESPONSE_decodeFields (
 LLRP_tSHF_ENTRANCEGUARD_DEVICE_RESPONSE * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_HF_ENTRANCEGUARD_DEVICE_RESPONSE_assimilateSubParameters (
 LLRP_tSHF_ENTRANCEGUARD_DEVICE_RESPONSE * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_HF_ENTRANCEGUARD_DEVICE_RESPONSE_encode (
  const LLRP_tSHF_ENTRANCEGUARD_DEVICE_RESPONSE *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSLLRPStatus *
LLRP_HF_ENTRANCEGUARD_DEVICE_RESPONSE_getLLRPStatus (
  LLRP_tSHF_ENTRANCEGUARD_DEVICE_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_HF_ENTRANCEGUARD_DEVICE_RESPONSE_setLLRPStatus (
  LLRP_tSHF_ENTRANCEGUARD_DEVICE_RESPONSE *pThis,
  LLRP_tSLLRPStatus *pValue);

extern LLRP_tSDeviceCmd *
LLRP_HF_ENTRANCEGUARD_DEVICE_RESPONSE_getDeviceCmd (
  LLRP_tSHF_ENTRANCEGUARD_DEVICE_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_HF_ENTRANCEGUARD_DEVICE_RESPONSE_setDeviceCmd (
  LLRP_tSHF_ENTRANCEGUARD_DEVICE_RESPONSE *pThis,
  LLRP_tSDeviceCmd *pValue);



  
struct LLRP_SHF_ENTRANCEGUARD_RESET_CARD
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSCardResetCmd * pCardResetCmd;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdHF_ENTRANCEGUARD_RESET_CARD;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdHF_ENTRANCEGUARD_RESET_CARD[];

extern LLRP_tSHF_ENTRANCEGUARD_RESET_CARD *
LLRP_HF_ENTRANCEGUARD_RESET_CARD_construct (void);

extern void
LLRP_HF_ENTRANCEGUARD_RESET_CARD_destruct (
 LLRP_tSHF_ENTRANCEGUARD_RESET_CARD * pThis);

extern void
LLRP_HF_ENTRANCEGUARD_RESET_CARD_decodeFields (
 LLRP_tSHF_ENTRANCEGUARD_RESET_CARD * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_HF_ENTRANCEGUARD_RESET_CARD_assimilateSubParameters (
 LLRP_tSHF_ENTRANCEGUARD_RESET_CARD * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_HF_ENTRANCEGUARD_RESET_CARD_encode (
  const LLRP_tSHF_ENTRANCEGUARD_RESET_CARD *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSCardResetCmd *
LLRP_HF_ENTRANCEGUARD_RESET_CARD_getCardResetCmd (
  LLRP_tSHF_ENTRANCEGUARD_RESET_CARD *pThis);

extern LLRP_tResultCode
LLRP_HF_ENTRANCEGUARD_RESET_CARD_setCardResetCmd (
  LLRP_tSHF_ENTRANCEGUARD_RESET_CARD *pThis,
  LLRP_tSCardResetCmd *pValue);



  
struct LLRP_SHF_ENTRANCEGUARD_RESET_CARD_RESPONSE
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSLLRPStatus * pLLRPStatus;

    LLRP_tSCardResetRsp * pCardResetRsp;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdHF_ENTRANCEGUARD_RESET_CARD_RESPONSE;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdHF_ENTRANCEGUARD_RESET_CARD_RESPONSE[];

extern LLRP_tSHF_ENTRANCEGUARD_RESET_CARD_RESPONSE *
LLRP_HF_ENTRANCEGUARD_RESET_CARD_RESPONSE_construct (void);

extern void
LLRP_HF_ENTRANCEGUARD_RESET_CARD_RESPONSE_destruct (
 LLRP_tSHF_ENTRANCEGUARD_RESET_CARD_RESPONSE * pThis);

extern void
LLRP_HF_ENTRANCEGUARD_RESET_CARD_RESPONSE_decodeFields (
 LLRP_tSHF_ENTRANCEGUARD_RESET_CARD_RESPONSE * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_HF_ENTRANCEGUARD_RESET_CARD_RESPONSE_assimilateSubParameters (
 LLRP_tSHF_ENTRANCEGUARD_RESET_CARD_RESPONSE * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_HF_ENTRANCEGUARD_RESET_CARD_RESPONSE_encode (
  const LLRP_tSHF_ENTRANCEGUARD_RESET_CARD_RESPONSE *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSLLRPStatus *
LLRP_HF_ENTRANCEGUARD_RESET_CARD_RESPONSE_getLLRPStatus (
  LLRP_tSHF_ENTRANCEGUARD_RESET_CARD_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_HF_ENTRANCEGUARD_RESET_CARD_RESPONSE_setLLRPStatus (
  LLRP_tSHF_ENTRANCEGUARD_RESET_CARD_RESPONSE *pThis,
  LLRP_tSLLRPStatus *pValue);

extern LLRP_tSCardResetRsp *
LLRP_HF_ENTRANCEGUARD_RESET_CARD_RESPONSE_getCardResetRsp (
  LLRP_tSHF_ENTRANCEGUARD_RESET_CARD_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_HF_ENTRANCEGUARD_RESET_CARD_RESPONSE_setCardResetRsp (
  LLRP_tSHF_ENTRANCEGUARD_RESET_CARD_RESPONSE *pThis,
  LLRP_tSCardResetRsp *pValue);



  
struct LLRP_SHF_ENTRANCEGUARD_LOW_CMD
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSLowLevelCmd * pLowLevelCmd;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdHF_ENTRANCEGUARD_LOW_CMD;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdHF_ENTRANCEGUARD_LOW_CMD[];

extern LLRP_tSHF_ENTRANCEGUARD_LOW_CMD *
LLRP_HF_ENTRANCEGUARD_LOW_CMD_construct (void);

extern void
LLRP_HF_ENTRANCEGUARD_LOW_CMD_destruct (
 LLRP_tSHF_ENTRANCEGUARD_LOW_CMD * pThis);

extern void
LLRP_HF_ENTRANCEGUARD_LOW_CMD_decodeFields (
 LLRP_tSHF_ENTRANCEGUARD_LOW_CMD * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_HF_ENTRANCEGUARD_LOW_CMD_assimilateSubParameters (
 LLRP_tSHF_ENTRANCEGUARD_LOW_CMD * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_HF_ENTRANCEGUARD_LOW_CMD_encode (
  const LLRP_tSHF_ENTRANCEGUARD_LOW_CMD *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSLowLevelCmd *
LLRP_HF_ENTRANCEGUARD_LOW_CMD_getLowLevelCmd (
  LLRP_tSHF_ENTRANCEGUARD_LOW_CMD *pThis);

extern LLRP_tResultCode
LLRP_HF_ENTRANCEGUARD_LOW_CMD_setLowLevelCmd (
  LLRP_tSHF_ENTRANCEGUARD_LOW_CMD *pThis,
  LLRP_tSLowLevelCmd *pValue);



  
struct LLRP_SHF_ENTRANCEGUARD_LOW_CMD_RESPONSE
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSLLRPStatus * pLLRPStatus;

    LLRP_tSLowLevelRsp * pLowLevelRsp;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdHF_ENTRANCEGUARD_LOW_CMD_RESPONSE;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdHF_ENTRANCEGUARD_LOW_CMD_RESPONSE[];

extern LLRP_tSHF_ENTRANCEGUARD_LOW_CMD_RESPONSE *
LLRP_HF_ENTRANCEGUARD_LOW_CMD_RESPONSE_construct (void);

extern void
LLRP_HF_ENTRANCEGUARD_LOW_CMD_RESPONSE_destruct (
 LLRP_tSHF_ENTRANCEGUARD_LOW_CMD_RESPONSE * pThis);

extern void
LLRP_HF_ENTRANCEGUARD_LOW_CMD_RESPONSE_decodeFields (
 LLRP_tSHF_ENTRANCEGUARD_LOW_CMD_RESPONSE * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_HF_ENTRANCEGUARD_LOW_CMD_RESPONSE_assimilateSubParameters (
 LLRP_tSHF_ENTRANCEGUARD_LOW_CMD_RESPONSE * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_HF_ENTRANCEGUARD_LOW_CMD_RESPONSE_encode (
  const LLRP_tSHF_ENTRANCEGUARD_LOW_CMD_RESPONSE *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSLLRPStatus *
LLRP_HF_ENTRANCEGUARD_LOW_CMD_RESPONSE_getLLRPStatus (
  LLRP_tSHF_ENTRANCEGUARD_LOW_CMD_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_HF_ENTRANCEGUARD_LOW_CMD_RESPONSE_setLLRPStatus (
  LLRP_tSHF_ENTRANCEGUARD_LOW_CMD_RESPONSE *pThis,
  LLRP_tSLLRPStatus *pValue);

extern LLRP_tSLowLevelRsp *
LLRP_HF_ENTRANCEGUARD_LOW_CMD_RESPONSE_getLowLevelRsp (
  LLRP_tSHF_ENTRANCEGUARD_LOW_CMD_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_HF_ENTRANCEGUARD_LOW_CMD_RESPONSE_setLowLevelRsp (
  LLRP_tSHF_ENTRANCEGUARD_LOW_CMD_RESPONSE *pThis,
  LLRP_tSLowLevelRsp *pValue);



  
struct LLRP_SHF_ENTRANCEGUARD_BROADCAST_TIME_MSG
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSBroadCastTimeCmd * pBroadCastTimeCmd;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdHF_ENTRANCEGUARD_BROADCAST_TIME_MSG;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdHF_ENTRANCEGUARD_BROADCAST_TIME_MSG[];

extern LLRP_tSHF_ENTRANCEGUARD_BROADCAST_TIME_MSG *
LLRP_HF_ENTRANCEGUARD_BROADCAST_TIME_MSG_construct (void);

extern void
LLRP_HF_ENTRANCEGUARD_BROADCAST_TIME_MSG_destruct (
 LLRP_tSHF_ENTRANCEGUARD_BROADCAST_TIME_MSG * pThis);

extern void
LLRP_HF_ENTRANCEGUARD_BROADCAST_TIME_MSG_decodeFields (
 LLRP_tSHF_ENTRANCEGUARD_BROADCAST_TIME_MSG * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_HF_ENTRANCEGUARD_BROADCAST_TIME_MSG_assimilateSubParameters (
 LLRP_tSHF_ENTRANCEGUARD_BROADCAST_TIME_MSG * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_HF_ENTRANCEGUARD_BROADCAST_TIME_MSG_encode (
  const LLRP_tSHF_ENTRANCEGUARD_BROADCAST_TIME_MSG *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSBroadCastTimeCmd *
LLRP_HF_ENTRANCEGUARD_BROADCAST_TIME_MSG_getBroadCastTimeCmd (
  LLRP_tSHF_ENTRANCEGUARD_BROADCAST_TIME_MSG *pThis);

extern LLRP_tResultCode
LLRP_HF_ENTRANCEGUARD_BROADCAST_TIME_MSG_setBroadCastTimeCmd (
  LLRP_tSHF_ENTRANCEGUARD_BROADCAST_TIME_MSG *pThis,
  LLRP_tSBroadCastTimeCmd *pValue);



  
struct LLRP_SHF_ENTRANCEGUARD_ALARM_MSG
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSAlarmCmd * pAlarmCmd;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdHF_ENTRANCEGUARD_ALARM_MSG;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdHF_ENTRANCEGUARD_ALARM_MSG[];

extern LLRP_tSHF_ENTRANCEGUARD_ALARM_MSG *
LLRP_HF_ENTRANCEGUARD_ALARM_MSG_construct (void);

extern void
LLRP_HF_ENTRANCEGUARD_ALARM_MSG_destruct (
 LLRP_tSHF_ENTRANCEGUARD_ALARM_MSG * pThis);

extern void
LLRP_HF_ENTRANCEGUARD_ALARM_MSG_decodeFields (
 LLRP_tSHF_ENTRANCEGUARD_ALARM_MSG * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_HF_ENTRANCEGUARD_ALARM_MSG_assimilateSubParameters (
 LLRP_tSHF_ENTRANCEGUARD_ALARM_MSG * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_HF_ENTRANCEGUARD_ALARM_MSG_encode (
  const LLRP_tSHF_ENTRANCEGUARD_ALARM_MSG *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSAlarmCmd *
LLRP_HF_ENTRANCEGUARD_ALARM_MSG_getAlarmCmd (
  LLRP_tSHF_ENTRANCEGUARD_ALARM_MSG *pThis);

extern LLRP_tResultCode
LLRP_HF_ENTRANCEGUARD_ALARM_MSG_setAlarmCmd (
  LLRP_tSHF_ENTRANCEGUARD_ALARM_MSG *pThis,
  LLRP_tSAlarmCmd *pValue);



  
struct LLRP_SHF_ENTRANCEGUARD_ID_RESPONSE
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSIDRsp * pIDRsp;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdHF_ENTRANCEGUARD_ID_RESPONSE;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdHF_ENTRANCEGUARD_ID_RESPONSE[];

extern LLRP_tSHF_ENTRANCEGUARD_ID_RESPONSE *
LLRP_HF_ENTRANCEGUARD_ID_RESPONSE_construct (void);

extern void
LLRP_HF_ENTRANCEGUARD_ID_RESPONSE_destruct (
 LLRP_tSHF_ENTRANCEGUARD_ID_RESPONSE * pThis);

extern void
LLRP_HF_ENTRANCEGUARD_ID_RESPONSE_decodeFields (
 LLRP_tSHF_ENTRANCEGUARD_ID_RESPONSE * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_HF_ENTRANCEGUARD_ID_RESPONSE_assimilateSubParameters (
 LLRP_tSHF_ENTRANCEGUARD_ID_RESPONSE * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_HF_ENTRANCEGUARD_ID_RESPONSE_encode (
  const LLRP_tSHF_ENTRANCEGUARD_ID_RESPONSE *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSIDRsp *
LLRP_HF_ENTRANCEGUARD_ID_RESPONSE_getIDRsp (
  LLRP_tSHF_ENTRANCEGUARD_ID_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_HF_ENTRANCEGUARD_ID_RESPONSE_setIDRsp (
  LLRP_tSHF_ENTRANCEGUARD_ID_RESPONSE *pThis,
  LLRP_tSIDRsp *pValue);



  
struct LLRP_SSET_READER_INITKEY
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSInitKey * pInitKey;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdSET_READER_INITKEY;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSET_READER_INITKEY[];

extern LLRP_tSSET_READER_INITKEY *
LLRP_SET_READER_INITKEY_construct (void);

extern void
LLRP_SET_READER_INITKEY_destruct (
 LLRP_tSSET_READER_INITKEY * pThis);

extern void
LLRP_SET_READER_INITKEY_decodeFields (
 LLRP_tSSET_READER_INITKEY * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SET_READER_INITKEY_assimilateSubParameters (
 LLRP_tSSET_READER_INITKEY * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SET_READER_INITKEY_encode (
  const LLRP_tSSET_READER_INITKEY *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSInitKey *
LLRP_SET_READER_INITKEY_getInitKey (
  LLRP_tSSET_READER_INITKEY *pThis);

extern LLRP_tResultCode
LLRP_SET_READER_INITKEY_setInitKey (
  LLRP_tSSET_READER_INITKEY *pThis,
  LLRP_tSInitKey *pValue);



  
struct LLRP_SSET_READER_INITKEY_RESPONSE
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSLLRPStatus * pLLRPStatus;

    LLRP_tSInitKeyAck * pInitKeyAck;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdSET_READER_INITKEY_RESPONSE;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSET_READER_INITKEY_RESPONSE[];

extern LLRP_tSSET_READER_INITKEY_RESPONSE *
LLRP_SET_READER_INITKEY_RESPONSE_construct (void);

extern void
LLRP_SET_READER_INITKEY_RESPONSE_destruct (
 LLRP_tSSET_READER_INITKEY_RESPONSE * pThis);

extern void
LLRP_SET_READER_INITKEY_RESPONSE_decodeFields (
 LLRP_tSSET_READER_INITKEY_RESPONSE * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SET_READER_INITKEY_RESPONSE_assimilateSubParameters (
 LLRP_tSSET_READER_INITKEY_RESPONSE * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SET_READER_INITKEY_RESPONSE_encode (
  const LLRP_tSSET_READER_INITKEY_RESPONSE *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSLLRPStatus *
LLRP_SET_READER_INITKEY_RESPONSE_getLLRPStatus (
  LLRP_tSSET_READER_INITKEY_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_SET_READER_INITKEY_RESPONSE_setLLRPStatus (
  LLRP_tSSET_READER_INITKEY_RESPONSE *pThis,
  LLRP_tSLLRPStatus *pValue);

extern LLRP_tSInitKeyAck *
LLRP_SET_READER_INITKEY_RESPONSE_getInitKeyAck (
  LLRP_tSSET_READER_INITKEY_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_SET_READER_INITKEY_RESPONSE_setInitKeyAck (
  LLRP_tSSET_READER_INITKEY_RESPONSE *pThis,
  LLRP_tSInitKeyAck *pValue);



  
struct LLRP_SBIND_READER_TWINS_PSAM
{
    LLRP_tSMessage hdr;
  
    llrp_u8v_t PSAMKey;

    llrp_u8_t PsamType;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdBIND_READER_TWINS_PSAM;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdBIND_READER_TWINS_PSAM[];

extern LLRP_tSBIND_READER_TWINS_PSAM *
LLRP_BIND_READER_TWINS_PSAM_construct (void);

extern void
LLRP_BIND_READER_TWINS_PSAM_destruct (
 LLRP_tSBIND_READER_TWINS_PSAM * pThis);

extern void
LLRP_BIND_READER_TWINS_PSAM_decodeFields (
 LLRP_tSBIND_READER_TWINS_PSAM * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_BIND_READER_TWINS_PSAM_assimilateSubParameters (
 LLRP_tSBIND_READER_TWINS_PSAM * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_BIND_READER_TWINS_PSAM_encode (
  const LLRP_tSBIND_READER_TWINS_PSAM *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdBIND_READER_TWINS_PSAM_PSAMKey;

extern llrp_u8v_t
LLRP_BIND_READER_TWINS_PSAM_getPSAMKey (
  LLRP_tSBIND_READER_TWINS_PSAM *pThis);

extern LLRP_tResultCode
LLRP_BIND_READER_TWINS_PSAM_setPSAMKey (
  LLRP_tSBIND_READER_TWINS_PSAM *pThis,
  llrp_u8v_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdBIND_READER_TWINS_PSAM_PsamType;

extern llrp_u8_t
LLRP_BIND_READER_TWINS_PSAM_getPsamType (
  LLRP_tSBIND_READER_TWINS_PSAM *pThis);

extern LLRP_tResultCode
LLRP_BIND_READER_TWINS_PSAM_setPsamType (
  LLRP_tSBIND_READER_TWINS_PSAM *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SBIND_READER_TWINS_PSAM_RESPONSE
{
    LLRP_tSMessage hdr;
  
    llrp_u8_t ErrorCode;

    llrp_u8v_t ReaderSerial;

    llrp_u8v_t PsamNum;

  
    LLRP_tSLLRPStatus * pLLRPStatus;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdBIND_READER_TWINS_PSAM_RESPONSE;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdBIND_READER_TWINS_PSAM_RESPONSE[];

extern LLRP_tSBIND_READER_TWINS_PSAM_RESPONSE *
LLRP_BIND_READER_TWINS_PSAM_RESPONSE_construct (void);

extern void
LLRP_BIND_READER_TWINS_PSAM_RESPONSE_destruct (
 LLRP_tSBIND_READER_TWINS_PSAM_RESPONSE * pThis);

extern void
LLRP_BIND_READER_TWINS_PSAM_RESPONSE_decodeFields (
 LLRP_tSBIND_READER_TWINS_PSAM_RESPONSE * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_BIND_READER_TWINS_PSAM_RESPONSE_assimilateSubParameters (
 LLRP_tSBIND_READER_TWINS_PSAM_RESPONSE * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_BIND_READER_TWINS_PSAM_RESPONSE_encode (
  const LLRP_tSBIND_READER_TWINS_PSAM_RESPONSE *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdBIND_READER_TWINS_PSAM_RESPONSE_ErrorCode;

extern llrp_u8_t
LLRP_BIND_READER_TWINS_PSAM_RESPONSE_getErrorCode (
  LLRP_tSBIND_READER_TWINS_PSAM_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_BIND_READER_TWINS_PSAM_RESPONSE_setErrorCode (
  LLRP_tSBIND_READER_TWINS_PSAM_RESPONSE *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdBIND_READER_TWINS_PSAM_RESPONSE_ReaderSerial;

extern llrp_u8v_t
LLRP_BIND_READER_TWINS_PSAM_RESPONSE_getReaderSerial (
  LLRP_tSBIND_READER_TWINS_PSAM_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_BIND_READER_TWINS_PSAM_RESPONSE_setReaderSerial (
  LLRP_tSBIND_READER_TWINS_PSAM_RESPONSE *pThis,
  llrp_u8v_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdBIND_READER_TWINS_PSAM_RESPONSE_PsamNum;

extern llrp_u8v_t
LLRP_BIND_READER_TWINS_PSAM_RESPONSE_getPsamNum (
  LLRP_tSBIND_READER_TWINS_PSAM_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_BIND_READER_TWINS_PSAM_RESPONSE_setPsamNum (
  LLRP_tSBIND_READER_TWINS_PSAM_RESPONSE *pThis,
  llrp_u8v_t Value);

  
extern LLRP_tSLLRPStatus *
LLRP_BIND_READER_TWINS_PSAM_RESPONSE_getLLRPStatus (
  LLRP_tSBIND_READER_TWINS_PSAM_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_BIND_READER_TWINS_PSAM_RESPONSE_setLLRPStatus (
  LLRP_tSBIND_READER_TWINS_PSAM_RESPONSE *pThis,
  LLRP_tSLLRPStatus *pValue);



  
struct LLRP_SUNBIND_READER_TWINS_PSAM
{
    LLRP_tSMessage hdr;
  
    llrp_u8v_t PSAMKey;

    llrp_u8_t PsamType;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdUNBIND_READER_TWINS_PSAM;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdUNBIND_READER_TWINS_PSAM[];

extern LLRP_tSUNBIND_READER_TWINS_PSAM *
LLRP_UNBIND_READER_TWINS_PSAM_construct (void);

extern void
LLRP_UNBIND_READER_TWINS_PSAM_destruct (
 LLRP_tSUNBIND_READER_TWINS_PSAM * pThis);

extern void
LLRP_UNBIND_READER_TWINS_PSAM_decodeFields (
 LLRP_tSUNBIND_READER_TWINS_PSAM * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_UNBIND_READER_TWINS_PSAM_assimilateSubParameters (
 LLRP_tSUNBIND_READER_TWINS_PSAM * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_UNBIND_READER_TWINS_PSAM_encode (
  const LLRP_tSUNBIND_READER_TWINS_PSAM *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdUNBIND_READER_TWINS_PSAM_PSAMKey;

extern llrp_u8v_t
LLRP_UNBIND_READER_TWINS_PSAM_getPSAMKey (
  LLRP_tSUNBIND_READER_TWINS_PSAM *pThis);

extern LLRP_tResultCode
LLRP_UNBIND_READER_TWINS_PSAM_setPSAMKey (
  LLRP_tSUNBIND_READER_TWINS_PSAM *pThis,
  llrp_u8v_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdUNBIND_READER_TWINS_PSAM_PsamType;

extern llrp_u8_t
LLRP_UNBIND_READER_TWINS_PSAM_getPsamType (
  LLRP_tSUNBIND_READER_TWINS_PSAM *pThis);

extern LLRP_tResultCode
LLRP_UNBIND_READER_TWINS_PSAM_setPsamType (
  LLRP_tSUNBIND_READER_TWINS_PSAM *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SUNBIND_READER_TWINS_PSAM_RESPONSE
{
    LLRP_tSMessage hdr;
  
    llrp_u8_t ErrorCode;

    llrp_u8v_t ReaderSerial;

    llrp_u8v_t PsamNum;

  
    LLRP_tSLLRPStatus * pLLRPStatus;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdUNBIND_READER_TWINS_PSAM_RESPONSE;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdUNBIND_READER_TWINS_PSAM_RESPONSE[];

extern LLRP_tSUNBIND_READER_TWINS_PSAM_RESPONSE *
LLRP_UNBIND_READER_TWINS_PSAM_RESPONSE_construct (void);

extern void
LLRP_UNBIND_READER_TWINS_PSAM_RESPONSE_destruct (
 LLRP_tSUNBIND_READER_TWINS_PSAM_RESPONSE * pThis);

extern void
LLRP_UNBIND_READER_TWINS_PSAM_RESPONSE_decodeFields (
 LLRP_tSUNBIND_READER_TWINS_PSAM_RESPONSE * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_UNBIND_READER_TWINS_PSAM_RESPONSE_assimilateSubParameters (
 LLRP_tSUNBIND_READER_TWINS_PSAM_RESPONSE * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_UNBIND_READER_TWINS_PSAM_RESPONSE_encode (
  const LLRP_tSUNBIND_READER_TWINS_PSAM_RESPONSE *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdUNBIND_READER_TWINS_PSAM_RESPONSE_ErrorCode;

extern llrp_u8_t
LLRP_UNBIND_READER_TWINS_PSAM_RESPONSE_getErrorCode (
  LLRP_tSUNBIND_READER_TWINS_PSAM_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_UNBIND_READER_TWINS_PSAM_RESPONSE_setErrorCode (
  LLRP_tSUNBIND_READER_TWINS_PSAM_RESPONSE *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdUNBIND_READER_TWINS_PSAM_RESPONSE_ReaderSerial;

extern llrp_u8v_t
LLRP_UNBIND_READER_TWINS_PSAM_RESPONSE_getReaderSerial (
  LLRP_tSUNBIND_READER_TWINS_PSAM_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_UNBIND_READER_TWINS_PSAM_RESPONSE_setReaderSerial (
  LLRP_tSUNBIND_READER_TWINS_PSAM_RESPONSE *pThis,
  llrp_u8v_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdUNBIND_READER_TWINS_PSAM_RESPONSE_PsamNum;

extern llrp_u8v_t
LLRP_UNBIND_READER_TWINS_PSAM_RESPONSE_getPsamNum (
  LLRP_tSUNBIND_READER_TWINS_PSAM_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_UNBIND_READER_TWINS_PSAM_RESPONSE_setPsamNum (
  LLRP_tSUNBIND_READER_TWINS_PSAM_RESPONSE *pThis,
  llrp_u8v_t Value);

  
extern LLRP_tSLLRPStatus *
LLRP_UNBIND_READER_TWINS_PSAM_RESPONSE_getLLRPStatus (
  LLRP_tSUNBIND_READER_TWINS_PSAM_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_UNBIND_READER_TWINS_PSAM_RESPONSE_setLLRPStatus (
  LLRP_tSUNBIND_READER_TWINS_PSAM_RESPONSE *pThis,
  LLRP_tSLLRPStatus *pValue);



  
struct LLRP_SHF_ENTRANCEGUARD_DEVICE_ARRAYMSG
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSDeviceCmdArray * pDeviceCmdArray;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdHF_ENTRANCEGUARD_DEVICE_ARRAYMSG;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdHF_ENTRANCEGUARD_DEVICE_ARRAYMSG[];

extern LLRP_tSHF_ENTRANCEGUARD_DEVICE_ARRAYMSG *
LLRP_HF_ENTRANCEGUARD_DEVICE_ARRAYMSG_construct (void);

extern void
LLRP_HF_ENTRANCEGUARD_DEVICE_ARRAYMSG_destruct (
 LLRP_tSHF_ENTRANCEGUARD_DEVICE_ARRAYMSG * pThis);

extern void
LLRP_HF_ENTRANCEGUARD_DEVICE_ARRAYMSG_decodeFields (
 LLRP_tSHF_ENTRANCEGUARD_DEVICE_ARRAYMSG * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_HF_ENTRANCEGUARD_DEVICE_ARRAYMSG_assimilateSubParameters (
 LLRP_tSHF_ENTRANCEGUARD_DEVICE_ARRAYMSG * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_HF_ENTRANCEGUARD_DEVICE_ARRAYMSG_encode (
  const LLRP_tSHF_ENTRANCEGUARD_DEVICE_ARRAYMSG *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSDeviceCmdArray *
LLRP_HF_ENTRANCEGUARD_DEVICE_ARRAYMSG_getDeviceCmdArray (
  LLRP_tSHF_ENTRANCEGUARD_DEVICE_ARRAYMSG *pThis);

extern LLRP_tResultCode
LLRP_HF_ENTRANCEGUARD_DEVICE_ARRAYMSG_setDeviceCmdArray (
  LLRP_tSHF_ENTRANCEGUARD_DEVICE_ARRAYMSG *pThis,
  LLRP_tSDeviceCmdArray *pValue);



  
struct LLRP_SHF_ENTRANCEGUARD_DEVICE_ARRAYRESPONSE
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSLLRPStatus * pLLRPStatus;

    LLRP_tSDeviceCmdArray * pDeviceCmdArray;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdHF_ENTRANCEGUARD_DEVICE_ARRAYRESPONSE;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdHF_ENTRANCEGUARD_DEVICE_ARRAYRESPONSE[];

extern LLRP_tSHF_ENTRANCEGUARD_DEVICE_ARRAYRESPONSE *
LLRP_HF_ENTRANCEGUARD_DEVICE_ARRAYRESPONSE_construct (void);

extern void
LLRP_HF_ENTRANCEGUARD_DEVICE_ARRAYRESPONSE_destruct (
 LLRP_tSHF_ENTRANCEGUARD_DEVICE_ARRAYRESPONSE * pThis);

extern void
LLRP_HF_ENTRANCEGUARD_DEVICE_ARRAYRESPONSE_decodeFields (
 LLRP_tSHF_ENTRANCEGUARD_DEVICE_ARRAYRESPONSE * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_HF_ENTRANCEGUARD_DEVICE_ARRAYRESPONSE_assimilateSubParameters (
 LLRP_tSHF_ENTRANCEGUARD_DEVICE_ARRAYRESPONSE * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_HF_ENTRANCEGUARD_DEVICE_ARRAYRESPONSE_encode (
  const LLRP_tSHF_ENTRANCEGUARD_DEVICE_ARRAYRESPONSE *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSLLRPStatus *
LLRP_HF_ENTRANCEGUARD_DEVICE_ARRAYRESPONSE_getLLRPStatus (
  LLRP_tSHF_ENTRANCEGUARD_DEVICE_ARRAYRESPONSE *pThis);

extern LLRP_tResultCode
LLRP_HF_ENTRANCEGUARD_DEVICE_ARRAYRESPONSE_setLLRPStatus (
  LLRP_tSHF_ENTRANCEGUARD_DEVICE_ARRAYRESPONSE *pThis,
  LLRP_tSLLRPStatus *pValue);

extern LLRP_tSDeviceCmdArray *
LLRP_HF_ENTRANCEGUARD_DEVICE_ARRAYRESPONSE_getDeviceCmdArray (
  LLRP_tSHF_ENTRANCEGUARD_DEVICE_ARRAYRESPONSE *pThis);

extern LLRP_tResultCode
LLRP_HF_ENTRANCEGUARD_DEVICE_ARRAYRESPONSE_setDeviceCmdArray (
  LLRP_tSHF_ENTRANCEGUARD_DEVICE_ARRAYRESPONSE *pThis,
  LLRP_tSDeviceCmdArray *pValue);



  
struct LLRP_SEC00_PC_6200PLT
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSWiegandPLTCmd * pWiegandPLTCmd;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdEC00_PC_6200PLT;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdEC00_PC_6200PLT[];

extern LLRP_tSEC00_PC_6200PLT *
LLRP_EC00_PC_6200PLT_construct (void);

extern void
LLRP_EC00_PC_6200PLT_destruct (
 LLRP_tSEC00_PC_6200PLT * pThis);

extern void
LLRP_EC00_PC_6200PLT_decodeFields (
 LLRP_tSEC00_PC_6200PLT * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_EC00_PC_6200PLT_assimilateSubParameters (
 LLRP_tSEC00_PC_6200PLT * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_EC00_PC_6200PLT_encode (
  const LLRP_tSEC00_PC_6200PLT *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSWiegandPLTCmd *
LLRP_EC00_PC_6200PLT_getWiegandPLTCmd (
  LLRP_tSEC00_PC_6200PLT *pThis);

extern LLRP_tResultCode
LLRP_EC00_PC_6200PLT_setWiegandPLTCmd (
  LLRP_tSEC00_PC_6200PLT *pThis,
  LLRP_tSWiegandPLTCmd *pValue);



  
struct LLRP_SEC00_PC_6200PLT_RESPONSE
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSLLRPStatus * pLLRPStatus;

    LLRP_tSWiegandPLTResultCmd * pWiegandPLTResultCmd;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdEC00_PC_6200PLT_RESPONSE;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdEC00_PC_6200PLT_RESPONSE[];

extern LLRP_tSEC00_PC_6200PLT_RESPONSE *
LLRP_EC00_PC_6200PLT_RESPONSE_construct (void);

extern void
LLRP_EC00_PC_6200PLT_RESPONSE_destruct (
 LLRP_tSEC00_PC_6200PLT_RESPONSE * pThis);

extern void
LLRP_EC00_PC_6200PLT_RESPONSE_decodeFields (
 LLRP_tSEC00_PC_6200PLT_RESPONSE * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_EC00_PC_6200PLT_RESPONSE_assimilateSubParameters (
 LLRP_tSEC00_PC_6200PLT_RESPONSE * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_EC00_PC_6200PLT_RESPONSE_encode (
  const LLRP_tSEC00_PC_6200PLT_RESPONSE *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSLLRPStatus *
LLRP_EC00_PC_6200PLT_RESPONSE_getLLRPStatus (
  LLRP_tSEC00_PC_6200PLT_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_EC00_PC_6200PLT_RESPONSE_setLLRPStatus (
  LLRP_tSEC00_PC_6200PLT_RESPONSE *pThis,
  LLRP_tSLLRPStatus *pValue);

extern LLRP_tSWiegandPLTResultCmd *
LLRP_EC00_PC_6200PLT_RESPONSE_getWiegandPLTResultCmd (
  LLRP_tSEC00_PC_6200PLT_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_EC00_PC_6200PLT_RESPONSE_setWiegandPLTResultCmd (
  LLRP_tSEC00_PC_6200PLT_RESPONSE *pThis,
  LLRP_tSWiegandPLTResultCmd *pValue);



  
struct LLRP_SADD_ZTE_ROSPEC
{
    LLRP_tSMessage hdr;
  
    llrp_u8_t SpecSaveFlag;

    llrp_u8_t StartROAccumulated;

    llrp_u8_t GPIAccumulated;

    llrp_u8_t PeriodAccumulated;

  
    LLRP_tSROSpec * pROSpec;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdADD_ZTE_ROSPEC;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdADD_ZTE_ROSPEC[];

extern LLRP_tSADD_ZTE_ROSPEC *
LLRP_ADD_ZTE_ROSPEC_construct (void);

extern void
LLRP_ADD_ZTE_ROSPEC_destruct (
 LLRP_tSADD_ZTE_ROSPEC * pThis);

extern void
LLRP_ADD_ZTE_ROSPEC_decodeFields (
 LLRP_tSADD_ZTE_ROSPEC * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_ADD_ZTE_ROSPEC_assimilateSubParameters (
 LLRP_tSADD_ZTE_ROSPEC * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_ADD_ZTE_ROSPEC_encode (
  const LLRP_tSADD_ZTE_ROSPEC *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdADD_ZTE_ROSPEC_SpecSaveFlag;

extern llrp_u8_t
LLRP_ADD_ZTE_ROSPEC_getSpecSaveFlag (
  LLRP_tSADD_ZTE_ROSPEC *pThis);

extern LLRP_tResultCode
LLRP_ADD_ZTE_ROSPEC_setSpecSaveFlag (
  LLRP_tSADD_ZTE_ROSPEC *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdADD_ZTE_ROSPEC_StartROAccumulated;

extern llrp_u8_t
LLRP_ADD_ZTE_ROSPEC_getStartROAccumulated (
  LLRP_tSADD_ZTE_ROSPEC *pThis);

extern LLRP_tResultCode
LLRP_ADD_ZTE_ROSPEC_setStartROAccumulated (
  LLRP_tSADD_ZTE_ROSPEC *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdADD_ZTE_ROSPEC_GPIAccumulated;

extern llrp_u8_t
LLRP_ADD_ZTE_ROSPEC_getGPIAccumulated (
  LLRP_tSADD_ZTE_ROSPEC *pThis);

extern LLRP_tResultCode
LLRP_ADD_ZTE_ROSPEC_setGPIAccumulated (
  LLRP_tSADD_ZTE_ROSPEC *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdADD_ZTE_ROSPEC_PeriodAccumulated;

extern llrp_u8_t
LLRP_ADD_ZTE_ROSPEC_getPeriodAccumulated (
  LLRP_tSADD_ZTE_ROSPEC *pThis);

extern LLRP_tResultCode
LLRP_ADD_ZTE_ROSPEC_setPeriodAccumulated (
  LLRP_tSADD_ZTE_ROSPEC *pThis,
  llrp_u8_t Value);

  
extern LLRP_tSROSpec *
LLRP_ADD_ZTE_ROSPEC_getROSpec (
  LLRP_tSADD_ZTE_ROSPEC *pThis);

extern LLRP_tResultCode
LLRP_ADD_ZTE_ROSPEC_setROSpec (
  LLRP_tSADD_ZTE_ROSPEC *pThis,
  LLRP_tSROSpec *pValue);



  
struct LLRP_SADD_ZTE_ROSPEC_RESPONSE
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSLLRPStatus * pLLRPStatus;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdADD_ZTE_ROSPEC_RESPONSE;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdADD_ZTE_ROSPEC_RESPONSE[];

extern LLRP_tSADD_ZTE_ROSPEC_RESPONSE *
LLRP_ADD_ZTE_ROSPEC_RESPONSE_construct (void);

extern void
LLRP_ADD_ZTE_ROSPEC_RESPONSE_destruct (
 LLRP_tSADD_ZTE_ROSPEC_RESPONSE * pThis);

extern void
LLRP_ADD_ZTE_ROSPEC_RESPONSE_decodeFields (
 LLRP_tSADD_ZTE_ROSPEC_RESPONSE * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_ADD_ZTE_ROSPEC_RESPONSE_assimilateSubParameters (
 LLRP_tSADD_ZTE_ROSPEC_RESPONSE * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_ADD_ZTE_ROSPEC_RESPONSE_encode (
  const LLRP_tSADD_ZTE_ROSPEC_RESPONSE *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSLLRPStatus *
LLRP_ADD_ZTE_ROSPEC_RESPONSE_getLLRPStatus (
  LLRP_tSADD_ZTE_ROSPEC_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_ADD_ZTE_ROSPEC_RESPONSE_setLLRPStatus (
  LLRP_tSADD_ZTE_ROSPEC_RESPONSE *pThis,
  LLRP_tSLLRPStatus *pValue);



  
struct LLRP_SADD_ZTE_ACCESSSPEC
{
    LLRP_tSMessage hdr;
  
    llrp_u8_t SpecSaveFlag;

  
    LLRP_tSAccessSpec * pAccessSpec;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdADD_ZTE_ACCESSSPEC;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdADD_ZTE_ACCESSSPEC[];

extern LLRP_tSADD_ZTE_ACCESSSPEC *
LLRP_ADD_ZTE_ACCESSSPEC_construct (void);

extern void
LLRP_ADD_ZTE_ACCESSSPEC_destruct (
 LLRP_tSADD_ZTE_ACCESSSPEC * pThis);

extern void
LLRP_ADD_ZTE_ACCESSSPEC_decodeFields (
 LLRP_tSADD_ZTE_ACCESSSPEC * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_ADD_ZTE_ACCESSSPEC_assimilateSubParameters (
 LLRP_tSADD_ZTE_ACCESSSPEC * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_ADD_ZTE_ACCESSSPEC_encode (
  const LLRP_tSADD_ZTE_ACCESSSPEC *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdADD_ZTE_ACCESSSPEC_SpecSaveFlag;

extern llrp_u8_t
LLRP_ADD_ZTE_ACCESSSPEC_getSpecSaveFlag (
  LLRP_tSADD_ZTE_ACCESSSPEC *pThis);

extern LLRP_tResultCode
LLRP_ADD_ZTE_ACCESSSPEC_setSpecSaveFlag (
  LLRP_tSADD_ZTE_ACCESSSPEC *pThis,
  llrp_u8_t Value);

  
extern LLRP_tSAccessSpec *
LLRP_ADD_ZTE_ACCESSSPEC_getAccessSpec (
  LLRP_tSADD_ZTE_ACCESSSPEC *pThis);

extern LLRP_tResultCode
LLRP_ADD_ZTE_ACCESSSPEC_setAccessSpec (
  LLRP_tSADD_ZTE_ACCESSSPEC *pThis,
  LLRP_tSAccessSpec *pValue);



  
struct LLRP_SADD_ZTE_ACCESSSPEC_RESPONSE
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSLLRPStatus * pLLRPStatus;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdADD_ZTE_ACCESSSPEC_RESPONSE;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdADD_ZTE_ACCESSSPEC_RESPONSE[];

extern LLRP_tSADD_ZTE_ACCESSSPEC_RESPONSE *
LLRP_ADD_ZTE_ACCESSSPEC_RESPONSE_construct (void);

extern void
LLRP_ADD_ZTE_ACCESSSPEC_RESPONSE_destruct (
 LLRP_tSADD_ZTE_ACCESSSPEC_RESPONSE * pThis);

extern void
LLRP_ADD_ZTE_ACCESSSPEC_RESPONSE_decodeFields (
 LLRP_tSADD_ZTE_ACCESSSPEC_RESPONSE * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_ADD_ZTE_ACCESSSPEC_RESPONSE_assimilateSubParameters (
 LLRP_tSADD_ZTE_ACCESSSPEC_RESPONSE * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_ADD_ZTE_ACCESSSPEC_RESPONSE_encode (
  const LLRP_tSADD_ZTE_ACCESSSPEC_RESPONSE *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSLLRPStatus *
LLRP_ADD_ZTE_ACCESSSPEC_RESPONSE_getLLRPStatus (
  LLRP_tSADD_ZTE_ACCESSSPEC_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_ADD_ZTE_ACCESSSPEC_RESPONSE_setLLRPStatus (
  LLRP_tSADD_ZTE_ACCESSSPEC_RESPONSE *pThis,
  LLRP_tSLLRPStatus *pValue);



  
struct LLRP_SSAVED_RO_ACCESS_REPORT
{
    LLRP_tSMessage hdr;
  
    llrp_u16_t SequenceID;

    llrp_u8_t IsLastedFrame;

    llrp_u8v_t Data;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdSAVED_RO_ACCESS_REPORT;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSAVED_RO_ACCESS_REPORT[];

extern LLRP_tSSAVED_RO_ACCESS_REPORT *
LLRP_SAVED_RO_ACCESS_REPORT_construct (void);

extern void
LLRP_SAVED_RO_ACCESS_REPORT_destruct (
 LLRP_tSSAVED_RO_ACCESS_REPORT * pThis);

extern void
LLRP_SAVED_RO_ACCESS_REPORT_decodeFields (
 LLRP_tSSAVED_RO_ACCESS_REPORT * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SAVED_RO_ACCESS_REPORT_assimilateSubParameters (
 LLRP_tSSAVED_RO_ACCESS_REPORT * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SAVED_RO_ACCESS_REPORT_encode (
  const LLRP_tSSAVED_RO_ACCESS_REPORT *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdSAVED_RO_ACCESS_REPORT_SequenceID;

extern llrp_u16_t
LLRP_SAVED_RO_ACCESS_REPORT_getSequenceID (
  LLRP_tSSAVED_RO_ACCESS_REPORT *pThis);

extern LLRP_tResultCode
LLRP_SAVED_RO_ACCESS_REPORT_setSequenceID (
  LLRP_tSSAVED_RO_ACCESS_REPORT *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSAVED_RO_ACCESS_REPORT_IsLastedFrame;

extern llrp_u8_t
LLRP_SAVED_RO_ACCESS_REPORT_getIsLastedFrame (
  LLRP_tSSAVED_RO_ACCESS_REPORT *pThis);

extern LLRP_tResultCode
LLRP_SAVED_RO_ACCESS_REPORT_setIsLastedFrame (
  LLRP_tSSAVED_RO_ACCESS_REPORT *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSAVED_RO_ACCESS_REPORT_Data;

extern llrp_u8v_t
LLRP_SAVED_RO_ACCESS_REPORT_getData (
  LLRP_tSSAVED_RO_ACCESS_REPORT *pThis);

extern LLRP_tResultCode
LLRP_SAVED_RO_ACCESS_REPORT_setData (
  LLRP_tSSAVED_RO_ACCESS_REPORT *pThis,
  llrp_u8v_t Value);

  


  
struct LLRP_SSAVED_RO_ACCESS_REPORT_ACK
{
    LLRP_tSMessage hdr;
  
    llrp_u16_t SequenceID;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdSAVED_RO_ACCESS_REPORT_ACK;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSAVED_RO_ACCESS_REPORT_ACK[];

extern LLRP_tSSAVED_RO_ACCESS_REPORT_ACK *
LLRP_SAVED_RO_ACCESS_REPORT_ACK_construct (void);

extern void
LLRP_SAVED_RO_ACCESS_REPORT_ACK_destruct (
 LLRP_tSSAVED_RO_ACCESS_REPORT_ACK * pThis);

extern void
LLRP_SAVED_RO_ACCESS_REPORT_ACK_decodeFields (
 LLRP_tSSAVED_RO_ACCESS_REPORT_ACK * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SAVED_RO_ACCESS_REPORT_ACK_assimilateSubParameters (
 LLRP_tSSAVED_RO_ACCESS_REPORT_ACK * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SAVED_RO_ACCESS_REPORT_ACK_encode (
  const LLRP_tSSAVED_RO_ACCESS_REPORT_ACK *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdSAVED_RO_ACCESS_REPORT_ACK_SequenceID;

extern llrp_u16_t
LLRP_SAVED_RO_ACCESS_REPORT_ACK_getSequenceID (
  LLRP_tSSAVED_RO_ACCESS_REPORT_ACK *pThis);

extern LLRP_tResultCode
LLRP_SAVED_RO_ACCESS_REPORT_ACK_setSequenceID (
  LLRP_tSSAVED_RO_ACCESS_REPORT_ACK *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_SREADER_TRACK_CTRL
{
    LLRP_tSMessage hdr;
  
    llrp_u8_t TrackSwitch;

  
    LLRP_tSTrackConfig * pTrackConfig;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdREADER_TRACK_CTRL;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdREADER_TRACK_CTRL[];

extern LLRP_tSREADER_TRACK_CTRL *
LLRP_READER_TRACK_CTRL_construct (void);

extern void
LLRP_READER_TRACK_CTRL_destruct (
 LLRP_tSREADER_TRACK_CTRL * pThis);

extern void
LLRP_READER_TRACK_CTRL_decodeFields (
 LLRP_tSREADER_TRACK_CTRL * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_READER_TRACK_CTRL_assimilateSubParameters (
 LLRP_tSREADER_TRACK_CTRL * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_READER_TRACK_CTRL_encode (
  const LLRP_tSREADER_TRACK_CTRL *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdREADER_TRACK_CTRL_TrackSwitch;

extern llrp_u8_t
LLRP_READER_TRACK_CTRL_getTrackSwitch (
  LLRP_tSREADER_TRACK_CTRL *pThis);

extern LLRP_tResultCode
LLRP_READER_TRACK_CTRL_setTrackSwitch (
  LLRP_tSREADER_TRACK_CTRL *pThis,
  llrp_u8_t Value);

  
extern LLRP_tSTrackConfig *
LLRP_READER_TRACK_CTRL_getTrackConfig (
  LLRP_tSREADER_TRACK_CTRL *pThis);

extern LLRP_tResultCode
LLRP_READER_TRACK_CTRL_setTrackConfig (
  LLRP_tSREADER_TRACK_CTRL *pThis,
  LLRP_tSTrackConfig *pValue);



  
struct LLRP_SREADER_TRACK_CTRL_ACK
{
    LLRP_tSMessage hdr;
  
    llrp_u8_t Result;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdREADER_TRACK_CTRL_ACK;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdREADER_TRACK_CTRL_ACK[];

extern LLRP_tSREADER_TRACK_CTRL_ACK *
LLRP_READER_TRACK_CTRL_ACK_construct (void);

extern void
LLRP_READER_TRACK_CTRL_ACK_destruct (
 LLRP_tSREADER_TRACK_CTRL_ACK * pThis);

extern void
LLRP_READER_TRACK_CTRL_ACK_decodeFields (
 LLRP_tSREADER_TRACK_CTRL_ACK * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_READER_TRACK_CTRL_ACK_assimilateSubParameters (
 LLRP_tSREADER_TRACK_CTRL_ACK * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_READER_TRACK_CTRL_ACK_encode (
  const LLRP_tSREADER_TRACK_CTRL_ACK *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdREADER_TRACK_CTRL_ACK_Result;

extern llrp_u8_t
LLRP_READER_TRACK_CTRL_ACK_getResult (
  LLRP_tSREADER_TRACK_CTRL_ACK *pThis);

extern LLRP_tResultCode
LLRP_READER_TRACK_CTRL_ACK_setResult (
  LLRP_tSREADER_TRACK_CTRL_ACK *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SREADER_RUNINFO_CTRL
{
    LLRP_tSMessage hdr;
  
    llrp_u8_t RunInfoSwitch;

  
    LLRP_tSRunInfoConfig * pRunInfoConfig;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdREADER_RUNINFO_CTRL;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdREADER_RUNINFO_CTRL[];

extern LLRP_tSREADER_RUNINFO_CTRL *
LLRP_READER_RUNINFO_CTRL_construct (void);

extern void
LLRP_READER_RUNINFO_CTRL_destruct (
 LLRP_tSREADER_RUNINFO_CTRL * pThis);

extern void
LLRP_READER_RUNINFO_CTRL_decodeFields (
 LLRP_tSREADER_RUNINFO_CTRL * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_READER_RUNINFO_CTRL_assimilateSubParameters (
 LLRP_tSREADER_RUNINFO_CTRL * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_READER_RUNINFO_CTRL_encode (
  const LLRP_tSREADER_RUNINFO_CTRL *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdREADER_RUNINFO_CTRL_RunInfoSwitch;

extern llrp_u8_t
LLRP_READER_RUNINFO_CTRL_getRunInfoSwitch (
  LLRP_tSREADER_RUNINFO_CTRL *pThis);

extern LLRP_tResultCode
LLRP_READER_RUNINFO_CTRL_setRunInfoSwitch (
  LLRP_tSREADER_RUNINFO_CTRL *pThis,
  llrp_u8_t Value);

  
extern LLRP_tSRunInfoConfig *
LLRP_READER_RUNINFO_CTRL_getRunInfoConfig (
  LLRP_tSREADER_RUNINFO_CTRL *pThis);

extern LLRP_tResultCode
LLRP_READER_RUNINFO_CTRL_setRunInfoConfig (
  LLRP_tSREADER_RUNINFO_CTRL *pThis,
  LLRP_tSRunInfoConfig *pValue);



  
struct LLRP_SREADER_RUNINFO_CTRL_ACK
{
    LLRP_tSMessage hdr;
  
    llrp_u8_t Result;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdREADER_RUNINFO_CTRL_ACK;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdREADER_RUNINFO_CTRL_ACK[];

extern LLRP_tSREADER_RUNINFO_CTRL_ACK *
LLRP_READER_RUNINFO_CTRL_ACK_construct (void);

extern void
LLRP_READER_RUNINFO_CTRL_ACK_destruct (
 LLRP_tSREADER_RUNINFO_CTRL_ACK * pThis);

extern void
LLRP_READER_RUNINFO_CTRL_ACK_decodeFields (
 LLRP_tSREADER_RUNINFO_CTRL_ACK * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_READER_RUNINFO_CTRL_ACK_assimilateSubParameters (
 LLRP_tSREADER_RUNINFO_CTRL_ACK * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_READER_RUNINFO_CTRL_ACK_encode (
  const LLRP_tSREADER_RUNINFO_CTRL_ACK *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdREADER_RUNINFO_CTRL_ACK_Result;

extern llrp_u8_t
LLRP_READER_RUNINFO_CTRL_ACK_getResult (
  LLRP_tSREADER_RUNINFO_CTRL_ACK *pThis);

extern LLRP_tResultCode
LLRP_READER_RUNINFO_CTRL_ACK_setResult (
  LLRP_tSREADER_RUNINFO_CTRL_ACK *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SDELETE_SAVED_RO_ACCESS_REPORT
{
    LLRP_tSMessage hdr;
  
  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdDELETE_SAVED_RO_ACCESS_REPORT;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdDELETE_SAVED_RO_ACCESS_REPORT[];

extern LLRP_tSDELETE_SAVED_RO_ACCESS_REPORT *
LLRP_DELETE_SAVED_RO_ACCESS_REPORT_construct (void);

extern void
LLRP_DELETE_SAVED_RO_ACCESS_REPORT_destruct (
 LLRP_tSDELETE_SAVED_RO_ACCESS_REPORT * pThis);

extern void
LLRP_DELETE_SAVED_RO_ACCESS_REPORT_decodeFields (
 LLRP_tSDELETE_SAVED_RO_ACCESS_REPORT * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_DELETE_SAVED_RO_ACCESS_REPORT_assimilateSubParameters (
 LLRP_tSDELETE_SAVED_RO_ACCESS_REPORT * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_DELETE_SAVED_RO_ACCESS_REPORT_encode (
  const LLRP_tSDELETE_SAVED_RO_ACCESS_REPORT *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  


  
struct LLRP_SDELETE_SAVED_RO_ACCESS_REPORT_RESPONSE
{
    LLRP_tSMessage hdr;
  
    llrp_u8_t Result;

  
    LLRP_tSLLRPStatus * pLLRPStatus;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdDELETE_SAVED_RO_ACCESS_REPORT_RESPONSE;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdDELETE_SAVED_RO_ACCESS_REPORT_RESPONSE[];

extern LLRP_tSDELETE_SAVED_RO_ACCESS_REPORT_RESPONSE *
LLRP_DELETE_SAVED_RO_ACCESS_REPORT_RESPONSE_construct (void);

extern void
LLRP_DELETE_SAVED_RO_ACCESS_REPORT_RESPONSE_destruct (
 LLRP_tSDELETE_SAVED_RO_ACCESS_REPORT_RESPONSE * pThis);

extern void
LLRP_DELETE_SAVED_RO_ACCESS_REPORT_RESPONSE_decodeFields (
 LLRP_tSDELETE_SAVED_RO_ACCESS_REPORT_RESPONSE * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_DELETE_SAVED_RO_ACCESS_REPORT_RESPONSE_assimilateSubParameters (
 LLRP_tSDELETE_SAVED_RO_ACCESS_REPORT_RESPONSE * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_DELETE_SAVED_RO_ACCESS_REPORT_RESPONSE_encode (
  const LLRP_tSDELETE_SAVED_RO_ACCESS_REPORT_RESPONSE *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdDELETE_SAVED_RO_ACCESS_REPORT_RESPONSE_Result;

extern llrp_u8_t
LLRP_DELETE_SAVED_RO_ACCESS_REPORT_RESPONSE_getResult (
  LLRP_tSDELETE_SAVED_RO_ACCESS_REPORT_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_DELETE_SAVED_RO_ACCESS_REPORT_RESPONSE_setResult (
  LLRP_tSDELETE_SAVED_RO_ACCESS_REPORT_RESPONSE *pThis,
  llrp_u8_t Value);

  
extern LLRP_tSLLRPStatus *
LLRP_DELETE_SAVED_RO_ACCESS_REPORT_RESPONSE_getLLRPStatus (
  LLRP_tSDELETE_SAVED_RO_ACCESS_REPORT_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_DELETE_SAVED_RO_ACCESS_REPORT_RESPONSE_setLLRPStatus (
  LLRP_tSDELETE_SAVED_RO_ACCESS_REPORT_RESPONSE *pThis,
  LLRP_tSLLRPStatus *pValue);



  
struct LLRP_SIPD_IPDISCOBVERY
{
    LLRP_tSMessage hdr;
  
    llrp_u32_t IPAddr;

    llrp_u32_t NetMask;

    llrp_u8v_t MacAddr;

    llrp_u32_t CheckWord;

    llrp_u32_t IPDMsgType;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdIPD_IPDISCOBVERY;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdIPD_IPDISCOBVERY[];

extern LLRP_tSIPD_IPDISCOBVERY *
LLRP_IPD_IPDISCOBVERY_construct (void);

extern void
LLRP_IPD_IPDISCOBVERY_destruct (
 LLRP_tSIPD_IPDISCOBVERY * pThis);

extern void
LLRP_IPD_IPDISCOBVERY_decodeFields (
 LLRP_tSIPD_IPDISCOBVERY * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_IPD_IPDISCOBVERY_assimilateSubParameters (
 LLRP_tSIPD_IPDISCOBVERY * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_IPD_IPDISCOBVERY_encode (
  const LLRP_tSIPD_IPDISCOBVERY *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdIPD_IPDISCOBVERY_IPAddr;

extern llrp_u32_t
LLRP_IPD_IPDISCOBVERY_getIPAddr (
  LLRP_tSIPD_IPDISCOBVERY *pThis);

extern LLRP_tResultCode
LLRP_IPD_IPDISCOBVERY_setIPAddr (
  LLRP_tSIPD_IPDISCOBVERY *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdIPD_IPDISCOBVERY_NetMask;

extern llrp_u32_t
LLRP_IPD_IPDISCOBVERY_getNetMask (
  LLRP_tSIPD_IPDISCOBVERY *pThis);

extern LLRP_tResultCode
LLRP_IPD_IPDISCOBVERY_setNetMask (
  LLRP_tSIPD_IPDISCOBVERY *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdIPD_IPDISCOBVERY_MacAddr;

extern llrp_u8v_t
LLRP_IPD_IPDISCOBVERY_getMacAddr (
  LLRP_tSIPD_IPDISCOBVERY *pThis);

extern LLRP_tResultCode
LLRP_IPD_IPDISCOBVERY_setMacAddr (
  LLRP_tSIPD_IPDISCOBVERY *pThis,
  llrp_u8v_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdIPD_IPDISCOBVERY_CheckWord;

extern llrp_u32_t
LLRP_IPD_IPDISCOBVERY_getCheckWord (
  LLRP_tSIPD_IPDISCOBVERY *pThis);

extern LLRP_tResultCode
LLRP_IPD_IPDISCOBVERY_setCheckWord (
  LLRP_tSIPD_IPDISCOBVERY *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdIPD_IPDISCOBVERY_IPDMsgType;

extern llrp_u32_t
LLRP_IPD_IPDISCOBVERY_getIPDMsgType (
  LLRP_tSIPD_IPDISCOBVERY *pThis);

extern LLRP_tResultCode
LLRP_IPD_IPDISCOBVERY_setIPDMsgType (
  LLRP_tSIPD_IPDISCOBVERY *pThis,
  llrp_u32_t Value);

  


  
struct LLRP_SIPD_IPDISCOBVERY_ACK
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSDeviceID * preaderID;

    LLRP_tSReaderBasicInfo * pReaderBasicInfo;

    LLRP_tSRUPCommunicationConfiguration * pRUPCommunicationConfiguration;

    LLRP_tSRUPCommunicationCapabilities * pRUPCommunicationCapabilities;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdIPD_IPDISCOBVERY_ACK;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdIPD_IPDISCOBVERY_ACK[];

extern LLRP_tSIPD_IPDISCOBVERY_ACK *
LLRP_IPD_IPDISCOBVERY_ACK_construct (void);

extern void
LLRP_IPD_IPDISCOBVERY_ACK_destruct (
 LLRP_tSIPD_IPDISCOBVERY_ACK * pThis);

extern void
LLRP_IPD_IPDISCOBVERY_ACK_decodeFields (
 LLRP_tSIPD_IPDISCOBVERY_ACK * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_IPD_IPDISCOBVERY_ACK_assimilateSubParameters (
 LLRP_tSIPD_IPDISCOBVERY_ACK * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_IPD_IPDISCOBVERY_ACK_encode (
  const LLRP_tSIPD_IPDISCOBVERY_ACK *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSDeviceID *
LLRP_IPD_IPDISCOBVERY_ACK_getreaderID (
  LLRP_tSIPD_IPDISCOBVERY_ACK *pThis);

extern LLRP_tResultCode
LLRP_IPD_IPDISCOBVERY_ACK_setreaderID (
  LLRP_tSIPD_IPDISCOBVERY_ACK *pThis,
  LLRP_tSDeviceID *pValue);

extern LLRP_tSReaderBasicInfo *
LLRP_IPD_IPDISCOBVERY_ACK_getReaderBasicInfo (
  LLRP_tSIPD_IPDISCOBVERY_ACK *pThis);

extern LLRP_tResultCode
LLRP_IPD_IPDISCOBVERY_ACK_setReaderBasicInfo (
  LLRP_tSIPD_IPDISCOBVERY_ACK *pThis,
  LLRP_tSReaderBasicInfo *pValue);

extern LLRP_tSRUPCommunicationConfiguration *
LLRP_IPD_IPDISCOBVERY_ACK_getRUPCommunicationConfiguration (
  LLRP_tSIPD_IPDISCOBVERY_ACK *pThis);

extern LLRP_tResultCode
LLRP_IPD_IPDISCOBVERY_ACK_setRUPCommunicationConfiguration (
  LLRP_tSIPD_IPDISCOBVERY_ACK *pThis,
  LLRP_tSRUPCommunicationConfiguration *pValue);

extern LLRP_tSRUPCommunicationCapabilities *
LLRP_IPD_IPDISCOBVERY_ACK_getRUPCommunicationCapabilities (
  LLRP_tSIPD_IPDISCOBVERY_ACK *pThis);

extern LLRP_tResultCode
LLRP_IPD_IPDISCOBVERY_ACK_setRUPCommunicationCapabilities (
  LLRP_tSIPD_IPDISCOBVERY_ACK *pThis,
  LLRP_tSRUPCommunicationCapabilities *pValue);



  
struct LLRP_SIPD_SETREADERCONFIG
{
    LLRP_tSMessage hdr;
  
    llrp_u8v_t ReadSerial;

  
    LLRP_tSDeviceID * preaderID;

    LLRP_tSRUPCommunicationConfiguration * pRUPCommunicationConfiguration;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdIPD_SETREADERCONFIG;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdIPD_SETREADERCONFIG[];

extern LLRP_tSIPD_SETREADERCONFIG *
LLRP_IPD_SETREADERCONFIG_construct (void);

extern void
LLRP_IPD_SETREADERCONFIG_destruct (
 LLRP_tSIPD_SETREADERCONFIG * pThis);

extern void
LLRP_IPD_SETREADERCONFIG_decodeFields (
 LLRP_tSIPD_SETREADERCONFIG * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_IPD_SETREADERCONFIG_assimilateSubParameters (
 LLRP_tSIPD_SETREADERCONFIG * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_IPD_SETREADERCONFIG_encode (
  const LLRP_tSIPD_SETREADERCONFIG *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdIPD_SETREADERCONFIG_ReadSerial;

extern llrp_u8v_t
LLRP_IPD_SETREADERCONFIG_getReadSerial (
  LLRP_tSIPD_SETREADERCONFIG *pThis);

extern LLRP_tResultCode
LLRP_IPD_SETREADERCONFIG_setReadSerial (
  LLRP_tSIPD_SETREADERCONFIG *pThis,
  llrp_u8v_t Value);

  
extern LLRP_tSDeviceID *
LLRP_IPD_SETREADERCONFIG_getreaderID (
  LLRP_tSIPD_SETREADERCONFIG *pThis);

extern LLRP_tResultCode
LLRP_IPD_SETREADERCONFIG_setreaderID (
  LLRP_tSIPD_SETREADERCONFIG *pThis,
  LLRP_tSDeviceID *pValue);

extern LLRP_tSRUPCommunicationConfiguration *
LLRP_IPD_SETREADERCONFIG_getRUPCommunicationConfiguration (
  LLRP_tSIPD_SETREADERCONFIG *pThis);

extern LLRP_tResultCode
LLRP_IPD_SETREADERCONFIG_setRUPCommunicationConfiguration (
  LLRP_tSIPD_SETREADERCONFIG *pThis,
  LLRP_tSRUPCommunicationConfiguration *pValue);



  
struct LLRP_SIPD_SETREADERCONFIG_RESPONSE
{
    LLRP_tSMessage hdr;
  
    llrp_u8v_t ReadSerial;

    llrp_u32_t Result;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdIPD_SETREADERCONFIG_RESPONSE;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdIPD_SETREADERCONFIG_RESPONSE[];

extern LLRP_tSIPD_SETREADERCONFIG_RESPONSE *
LLRP_IPD_SETREADERCONFIG_RESPONSE_construct (void);

extern void
LLRP_IPD_SETREADERCONFIG_RESPONSE_destruct (
 LLRP_tSIPD_SETREADERCONFIG_RESPONSE * pThis);

extern void
LLRP_IPD_SETREADERCONFIG_RESPONSE_decodeFields (
 LLRP_tSIPD_SETREADERCONFIG_RESPONSE * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_IPD_SETREADERCONFIG_RESPONSE_assimilateSubParameters (
 LLRP_tSIPD_SETREADERCONFIG_RESPONSE * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_IPD_SETREADERCONFIG_RESPONSE_encode (
  const LLRP_tSIPD_SETREADERCONFIG_RESPONSE *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdIPD_SETREADERCONFIG_RESPONSE_ReadSerial;

extern llrp_u8v_t
LLRP_IPD_SETREADERCONFIG_RESPONSE_getReadSerial (
  LLRP_tSIPD_SETREADERCONFIG_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_IPD_SETREADERCONFIG_RESPONSE_setReadSerial (
  LLRP_tSIPD_SETREADERCONFIG_RESPONSE *pThis,
  llrp_u8v_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdIPD_SETREADERCONFIG_RESPONSE_Result;

extern llrp_u32_t
LLRP_IPD_SETREADERCONFIG_RESPONSE_getResult (
  LLRP_tSIPD_SETREADERCONFIG_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_IPD_SETREADERCONFIG_RESPONSE_setResult (
  LLRP_tSIPD_SETREADERCONFIG_RESPONSE *pThis,
  llrp_u32_t Value);

  


  
struct LLRP_SIPD_RESETREADER
{
    LLRP_tSMessage hdr;
  
    llrp_u8v_t ReadSerial;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdIPD_RESETREADER;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdIPD_RESETREADER[];

extern LLRP_tSIPD_RESETREADER *
LLRP_IPD_RESETREADER_construct (void);

extern void
LLRP_IPD_RESETREADER_destruct (
 LLRP_tSIPD_RESETREADER * pThis);

extern void
LLRP_IPD_RESETREADER_decodeFields (
 LLRP_tSIPD_RESETREADER * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_IPD_RESETREADER_assimilateSubParameters (
 LLRP_tSIPD_RESETREADER * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_IPD_RESETREADER_encode (
  const LLRP_tSIPD_RESETREADER *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdIPD_RESETREADER_ReadSerial;

extern llrp_u8v_t
LLRP_IPD_RESETREADER_getReadSerial (
  LLRP_tSIPD_RESETREADER *pThis);

extern LLRP_tResultCode
LLRP_IPD_RESETREADER_setReadSerial (
  LLRP_tSIPD_RESETREADER *pThis,
  llrp_u8v_t Value);

  


  
struct LLRP_SIPD_RESETREADER_RESPONSE
{
    LLRP_tSMessage hdr;
  
    llrp_u8v_t ReadSerial;

    llrp_u32_t Result;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdIPD_RESETREADER_RESPONSE;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdIPD_RESETREADER_RESPONSE[];

extern LLRP_tSIPD_RESETREADER_RESPONSE *
LLRP_IPD_RESETREADER_RESPONSE_construct (void);

extern void
LLRP_IPD_RESETREADER_RESPONSE_destruct (
 LLRP_tSIPD_RESETREADER_RESPONSE * pThis);

extern void
LLRP_IPD_RESETREADER_RESPONSE_decodeFields (
 LLRP_tSIPD_RESETREADER_RESPONSE * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_IPD_RESETREADER_RESPONSE_assimilateSubParameters (
 LLRP_tSIPD_RESETREADER_RESPONSE * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_IPD_RESETREADER_RESPONSE_encode (
  const LLRP_tSIPD_RESETREADER_RESPONSE *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdIPD_RESETREADER_RESPONSE_ReadSerial;

extern llrp_u8v_t
LLRP_IPD_RESETREADER_RESPONSE_getReadSerial (
  LLRP_tSIPD_RESETREADER_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_IPD_RESETREADER_RESPONSE_setReadSerial (
  LLRP_tSIPD_RESETREADER_RESPONSE *pThis,
  llrp_u8v_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdIPD_RESETREADER_RESPONSE_Result;

extern llrp_u32_t
LLRP_IPD_RESETREADER_RESPONSE_getResult (
  LLRP_tSIPD_RESETREADER_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_IPD_RESETREADER_RESPONSE_setResult (
  LLRP_tSIPD_RESETREADER_RESPONSE *pThis,
  llrp_u32_t Value);

  


  
struct LLRP_SUHF_PRIVATE_CMD
{
    LLRP_tSMessage hdr;
  
    llrp_u32_t CmdID;

    llrp_u8v_t CmdPara;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdUHF_PRIVATE_CMD;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdUHF_PRIVATE_CMD[];

extern LLRP_tSUHF_PRIVATE_CMD *
LLRP_UHF_PRIVATE_CMD_construct (void);

extern void
LLRP_UHF_PRIVATE_CMD_destruct (
 LLRP_tSUHF_PRIVATE_CMD * pThis);

extern void
LLRP_UHF_PRIVATE_CMD_decodeFields (
 LLRP_tSUHF_PRIVATE_CMD * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_UHF_PRIVATE_CMD_assimilateSubParameters (
 LLRP_tSUHF_PRIVATE_CMD * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_UHF_PRIVATE_CMD_encode (
  const LLRP_tSUHF_PRIVATE_CMD *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdUHF_PRIVATE_CMD_CmdID;

extern llrp_u32_t
LLRP_UHF_PRIVATE_CMD_getCmdID (
  LLRP_tSUHF_PRIVATE_CMD *pThis);

extern LLRP_tResultCode
LLRP_UHF_PRIVATE_CMD_setCmdID (
  LLRP_tSUHF_PRIVATE_CMD *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdUHF_PRIVATE_CMD_CmdPara;

extern llrp_u8v_t
LLRP_UHF_PRIVATE_CMD_getCmdPara (
  LLRP_tSUHF_PRIVATE_CMD *pThis);

extern LLRP_tResultCode
LLRP_UHF_PRIVATE_CMD_setCmdPara (
  LLRP_tSUHF_PRIVATE_CMD *pThis,
  llrp_u8v_t Value);

  


  
struct LLRP_SUHF_PRIVATE_CMD_RESPONSE
{
    LLRP_tSMessage hdr;
  
    llrp_u32_t CmdID;

    llrp_u8v_t CmdAckPara;

  
    LLRP_tSLLRPStatus * pLLRPStatus;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdUHF_PRIVATE_CMD_RESPONSE;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdUHF_PRIVATE_CMD_RESPONSE[];

extern LLRP_tSUHF_PRIVATE_CMD_RESPONSE *
LLRP_UHF_PRIVATE_CMD_RESPONSE_construct (void);

extern void
LLRP_UHF_PRIVATE_CMD_RESPONSE_destruct (
 LLRP_tSUHF_PRIVATE_CMD_RESPONSE * pThis);

extern void
LLRP_UHF_PRIVATE_CMD_RESPONSE_decodeFields (
 LLRP_tSUHF_PRIVATE_CMD_RESPONSE * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_UHF_PRIVATE_CMD_RESPONSE_assimilateSubParameters (
 LLRP_tSUHF_PRIVATE_CMD_RESPONSE * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_UHF_PRIVATE_CMD_RESPONSE_encode (
  const LLRP_tSUHF_PRIVATE_CMD_RESPONSE *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdUHF_PRIVATE_CMD_RESPONSE_CmdID;

extern llrp_u32_t
LLRP_UHF_PRIVATE_CMD_RESPONSE_getCmdID (
  LLRP_tSUHF_PRIVATE_CMD_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_UHF_PRIVATE_CMD_RESPONSE_setCmdID (
  LLRP_tSUHF_PRIVATE_CMD_RESPONSE *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdUHF_PRIVATE_CMD_RESPONSE_CmdAckPara;

extern llrp_u8v_t
LLRP_UHF_PRIVATE_CMD_RESPONSE_getCmdAckPara (
  LLRP_tSUHF_PRIVATE_CMD_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_UHF_PRIVATE_CMD_RESPONSE_setCmdAckPara (
  LLRP_tSUHF_PRIVATE_CMD_RESPONSE *pThis,
  llrp_u8v_t Value);

  
extern LLRP_tSLLRPStatus *
LLRP_UHF_PRIVATE_CMD_RESPONSE_getLLRPStatus (
  LLRP_tSUHF_PRIVATE_CMD_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_UHF_PRIVATE_CMD_RESPONSE_setLLRPStatus (
  LLRP_tSUHF_PRIVATE_CMD_RESPONSE *pThis,
  LLRP_tSLLRPStatus *pValue);



  
struct LLRP_SUHF_PRIVATE_SETPASSWORD
{
    LLRP_tSMessage hdr;
  
  
    LLRP_tSPwdIndexPara * listPwdIndexPara;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdUHF_PRIVATE_SETPASSWORD;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdUHF_PRIVATE_SETPASSWORD[];

extern LLRP_tSUHF_PRIVATE_SETPASSWORD *
LLRP_UHF_PRIVATE_SETPASSWORD_construct (void);

extern void
LLRP_UHF_PRIVATE_SETPASSWORD_destruct (
 LLRP_tSUHF_PRIVATE_SETPASSWORD * pThis);

extern void
LLRP_UHF_PRIVATE_SETPASSWORD_decodeFields (
 LLRP_tSUHF_PRIVATE_SETPASSWORD * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_UHF_PRIVATE_SETPASSWORD_assimilateSubParameters (
 LLRP_tSUHF_PRIVATE_SETPASSWORD * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_UHF_PRIVATE_SETPASSWORD_encode (
  const LLRP_tSUHF_PRIVATE_SETPASSWORD *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
  
extern LLRP_tSPwdIndexPara *
LLRP_UHF_PRIVATE_SETPASSWORD_beginPwdIndexPara (
  LLRP_tSUHF_PRIVATE_SETPASSWORD *pThis);

extern LLRP_tSPwdIndexPara *
LLRP_UHF_PRIVATE_SETPASSWORD_nextPwdIndexPara (
  LLRP_tSPwdIndexPara *pCurrent);

extern void
LLRP_UHF_PRIVATE_SETPASSWORD_clearPwdIndexPara (
  LLRP_tSUHF_PRIVATE_SETPASSWORD *pThis);

extern LLRP_tResultCode
LLRP_UHF_PRIVATE_SETPASSWORD_addPwdIndexPara (
  LLRP_tSUHF_PRIVATE_SETPASSWORD *pThis,
  LLRP_tSPwdIndexPara *pValue);




  
struct LLRP_SUHF_PRIVATE_SETPASSWORD_RESPONSE
{
    LLRP_tSMessage hdr;
  
    llrp_u32_t Result;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdUHF_PRIVATE_SETPASSWORD_RESPONSE;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdUHF_PRIVATE_SETPASSWORD_RESPONSE[];

extern LLRP_tSUHF_PRIVATE_SETPASSWORD_RESPONSE *
LLRP_UHF_PRIVATE_SETPASSWORD_RESPONSE_construct (void);

extern void
LLRP_UHF_PRIVATE_SETPASSWORD_RESPONSE_destruct (
 LLRP_tSUHF_PRIVATE_SETPASSWORD_RESPONSE * pThis);

extern void
LLRP_UHF_PRIVATE_SETPASSWORD_RESPONSE_decodeFields (
 LLRP_tSUHF_PRIVATE_SETPASSWORD_RESPONSE * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_UHF_PRIVATE_SETPASSWORD_RESPONSE_assimilateSubParameters (
 LLRP_tSUHF_PRIVATE_SETPASSWORD_RESPONSE * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_UHF_PRIVATE_SETPASSWORD_RESPONSE_encode (
  const LLRP_tSUHF_PRIVATE_SETPASSWORD_RESPONSE *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdUHF_PRIVATE_SETPASSWORD_RESPONSE_Result;

extern llrp_u32_t
LLRP_UHF_PRIVATE_SETPASSWORD_RESPONSE_getResult (
  LLRP_tSUHF_PRIVATE_SETPASSWORD_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_UHF_PRIVATE_SETPASSWORD_RESPONSE_setResult (
  LLRP_tSUHF_PRIVATE_SETPASSWORD_RESPONSE *pThis,
  llrp_u32_t Value);

  


  
struct LLRP_SZIT_SET_TIME
{
    LLRP_tSMessage hdr;
  
    llrp_u32_t time;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdZIT_SET_TIME;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdZIT_SET_TIME[];

extern LLRP_tSZIT_SET_TIME *
LLRP_ZIT_SET_TIME_construct (void);

extern void
LLRP_ZIT_SET_TIME_destruct (
 LLRP_tSZIT_SET_TIME * pThis);

extern void
LLRP_ZIT_SET_TIME_decodeFields (
 LLRP_tSZIT_SET_TIME * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_ZIT_SET_TIME_assimilateSubParameters (
 LLRP_tSZIT_SET_TIME * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_ZIT_SET_TIME_encode (
  const LLRP_tSZIT_SET_TIME *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdZIT_SET_TIME_time;

extern llrp_u32_t
LLRP_ZIT_SET_TIME_gettime (
  LLRP_tSZIT_SET_TIME *pThis);

extern LLRP_tResultCode
LLRP_ZIT_SET_TIME_settime (
  LLRP_tSZIT_SET_TIME *pThis,
  llrp_u32_t Value);

  


  
struct LLRP_SZIT_SET_TIME_RESPONSE
{
    LLRP_tSMessage hdr;
  
    llrp_u32_t Result;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdZIT_SET_TIME_RESPONSE;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdZIT_SET_TIME_RESPONSE[];

extern LLRP_tSZIT_SET_TIME_RESPONSE *
LLRP_ZIT_SET_TIME_RESPONSE_construct (void);

extern void
LLRP_ZIT_SET_TIME_RESPONSE_destruct (
 LLRP_tSZIT_SET_TIME_RESPONSE * pThis);

extern void
LLRP_ZIT_SET_TIME_RESPONSE_decodeFields (
 LLRP_tSZIT_SET_TIME_RESPONSE * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_ZIT_SET_TIME_RESPONSE_assimilateSubParameters (
 LLRP_tSZIT_SET_TIME_RESPONSE * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_ZIT_SET_TIME_RESPONSE_encode (
  const LLRP_tSZIT_SET_TIME_RESPONSE *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdZIT_SET_TIME_RESPONSE_Result;

extern llrp_u32_t
LLRP_ZIT_SET_TIME_RESPONSE_getResult (
  LLRP_tSZIT_SET_TIME_RESPONSE *pThis);

extern LLRP_tResultCode
LLRP_ZIT_SET_TIME_RESPONSE_setResult (
  LLRP_tSZIT_SET_TIME_RESPONSE *pThis,
  llrp_u32_t Value);

  


  
struct LLRP_SExtRegulatoryCapabilities
{
    LLRP_tSParameter hdr;
  
    llrp_u1_t SupportsForandRev;

    llrp_u1_t SupportsIQ;

    llrp_u1_t SupportsUBOOT;

  
    LLRP_tSModuleDepthEntry * listModuleDepthEntry;

    LLRP_tSModuleDepthEntryFor6B * listModuleDepthEntryFor6B;

    LLRP_tSProtocolParaFor6C * pProtocolParaFor6C;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdExtRegulatoryCapabilities;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdExtRegulatoryCapabilities[];

extern LLRP_tSExtRegulatoryCapabilities *
LLRP_ExtRegulatoryCapabilities_construct (void);

extern void
LLRP_ExtRegulatoryCapabilities_destruct (
 LLRP_tSExtRegulatoryCapabilities * pThis);

extern void
LLRP_ExtRegulatoryCapabilities_decodeFields (
 LLRP_tSExtRegulatoryCapabilities * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_ExtRegulatoryCapabilities_assimilateSubParameters (
 LLRP_tSExtRegulatoryCapabilities * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_ExtRegulatoryCapabilities_encode (
  const LLRP_tSExtRegulatoryCapabilities *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_ExtRegulatoryCapabilities_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdExtRegulatoryCapabilities_SupportsForandRev;

extern llrp_u1_t
LLRP_ExtRegulatoryCapabilities_getSupportsForandRev (
  LLRP_tSExtRegulatoryCapabilities *pThis);

extern LLRP_tResultCode
LLRP_ExtRegulatoryCapabilities_setSupportsForandRev (
  LLRP_tSExtRegulatoryCapabilities *pThis,
  llrp_u1_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdExtRegulatoryCapabilities_SupportsIQ;

extern llrp_u1_t
LLRP_ExtRegulatoryCapabilities_getSupportsIQ (
  LLRP_tSExtRegulatoryCapabilities *pThis);

extern LLRP_tResultCode
LLRP_ExtRegulatoryCapabilities_setSupportsIQ (
  LLRP_tSExtRegulatoryCapabilities *pThis,
  llrp_u1_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdExtRegulatoryCapabilities_SupportsUBOOT;

extern llrp_u1_t
LLRP_ExtRegulatoryCapabilities_getSupportsUBOOT (
  LLRP_tSExtRegulatoryCapabilities *pThis);

extern LLRP_tResultCode
LLRP_ExtRegulatoryCapabilities_setSupportsUBOOT (
  LLRP_tSExtRegulatoryCapabilities *pThis,
  llrp_u1_t Value);

  
extern LLRP_tSModuleDepthEntry *
LLRP_ExtRegulatoryCapabilities_beginModuleDepthEntry (
  LLRP_tSExtRegulatoryCapabilities *pThis);

extern LLRP_tSModuleDepthEntry *
LLRP_ExtRegulatoryCapabilities_nextModuleDepthEntry (
  LLRP_tSModuleDepthEntry *pCurrent);

extern void
LLRP_ExtRegulatoryCapabilities_clearModuleDepthEntry (
  LLRP_tSExtRegulatoryCapabilities *pThis);

extern LLRP_tResultCode
LLRP_ExtRegulatoryCapabilities_addModuleDepthEntry (
  LLRP_tSExtRegulatoryCapabilities *pThis,
  LLRP_tSModuleDepthEntry *pValue);


extern LLRP_tSModuleDepthEntryFor6B *
LLRP_ExtRegulatoryCapabilities_beginModuleDepthEntryFor6B (
  LLRP_tSExtRegulatoryCapabilities *pThis);

extern LLRP_tSModuleDepthEntryFor6B *
LLRP_ExtRegulatoryCapabilities_nextModuleDepthEntryFor6B (
  LLRP_tSModuleDepthEntryFor6B *pCurrent);

extern void
LLRP_ExtRegulatoryCapabilities_clearModuleDepthEntryFor6B (
  LLRP_tSExtRegulatoryCapabilities *pThis);

extern LLRP_tResultCode
LLRP_ExtRegulatoryCapabilities_addModuleDepthEntryFor6B (
  LLRP_tSExtRegulatoryCapabilities *pThis,
  LLRP_tSModuleDepthEntryFor6B *pValue);


extern LLRP_tSProtocolParaFor6C *
LLRP_ExtRegulatoryCapabilities_getProtocolParaFor6C (
  LLRP_tSExtRegulatoryCapabilities *pThis);

extern LLRP_tResultCode
LLRP_ExtRegulatoryCapabilities_setProtocolParaFor6C (
  LLRP_tSExtRegulatoryCapabilities *pThis,
  LLRP_tSProtocolParaFor6C *pValue);



  
struct LLRP_SProtocolParaFor6C
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t PIE_Value;

  
    LLRP_tSDataRateCapabilities * listDataRateCapabilities;

    LLRP_tSM_valueCapabilities * listM_valueCapabilities;

    LLRP_tSForward_link_modulationCapabilities * listForward_link_modulationCapabilities;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdProtocolParaFor6C;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdProtocolParaFor6C[];

extern LLRP_tSProtocolParaFor6C *
LLRP_ProtocolParaFor6C_construct (void);

extern void
LLRP_ProtocolParaFor6C_destruct (
 LLRP_tSProtocolParaFor6C * pThis);

extern void
LLRP_ProtocolParaFor6C_decodeFields (
 LLRP_tSProtocolParaFor6C * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_ProtocolParaFor6C_assimilateSubParameters (
 LLRP_tSProtocolParaFor6C * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_ProtocolParaFor6C_encode (
  const LLRP_tSProtocolParaFor6C *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_ProtocolParaFor6C_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdProtocolParaFor6C_PIE_Value;

extern llrp_u16_t
LLRP_ProtocolParaFor6C_getPIE_Value (
  LLRP_tSProtocolParaFor6C *pThis);

extern LLRP_tResultCode
LLRP_ProtocolParaFor6C_setPIE_Value (
  LLRP_tSProtocolParaFor6C *pThis,
  llrp_u16_t Value);

  
extern LLRP_tSDataRateCapabilities *
LLRP_ProtocolParaFor6C_beginDataRateCapabilities (
  LLRP_tSProtocolParaFor6C *pThis);

extern LLRP_tSDataRateCapabilities *
LLRP_ProtocolParaFor6C_nextDataRateCapabilities (
  LLRP_tSDataRateCapabilities *pCurrent);

extern void
LLRP_ProtocolParaFor6C_clearDataRateCapabilities (
  LLRP_tSProtocolParaFor6C *pThis);

extern LLRP_tResultCode
LLRP_ProtocolParaFor6C_addDataRateCapabilities (
  LLRP_tSProtocolParaFor6C *pThis,
  LLRP_tSDataRateCapabilities *pValue);


extern LLRP_tSM_valueCapabilities *
LLRP_ProtocolParaFor6C_beginM_valueCapabilities (
  LLRP_tSProtocolParaFor6C *pThis);

extern LLRP_tSM_valueCapabilities *
LLRP_ProtocolParaFor6C_nextM_valueCapabilities (
  LLRP_tSM_valueCapabilities *pCurrent);

extern void
LLRP_ProtocolParaFor6C_clearM_valueCapabilities (
  LLRP_tSProtocolParaFor6C *pThis);

extern LLRP_tResultCode
LLRP_ProtocolParaFor6C_addM_valueCapabilities (
  LLRP_tSProtocolParaFor6C *pThis,
  LLRP_tSM_valueCapabilities *pValue);


extern LLRP_tSForward_link_modulationCapabilities *
LLRP_ProtocolParaFor6C_beginForward_link_modulationCapabilities (
  LLRP_tSProtocolParaFor6C *pThis);

extern LLRP_tSForward_link_modulationCapabilities *
LLRP_ProtocolParaFor6C_nextForward_link_modulationCapabilities (
  LLRP_tSForward_link_modulationCapabilities *pCurrent);

extern void
LLRP_ProtocolParaFor6C_clearForward_link_modulationCapabilities (
  LLRP_tSProtocolParaFor6C *pThis);

extern LLRP_tResultCode
LLRP_ProtocolParaFor6C_addForward_link_modulationCapabilities (
  LLRP_tSProtocolParaFor6C *pThis,
  LLRP_tSForward_link_modulationCapabilities *pValue);




  
struct LLRP_SDataRateCapabilities
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t ForDataRate;

    llrp_u16_t RevDataRate;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdDataRateCapabilities;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdDataRateCapabilities[];

extern LLRP_tSDataRateCapabilities *
LLRP_DataRateCapabilities_construct (void);

extern void
LLRP_DataRateCapabilities_destruct (
 LLRP_tSDataRateCapabilities * pThis);

extern void
LLRP_DataRateCapabilities_decodeFields (
 LLRP_tSDataRateCapabilities * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_DataRateCapabilities_assimilateSubParameters (
 LLRP_tSDataRateCapabilities * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_DataRateCapabilities_encode (
  const LLRP_tSDataRateCapabilities *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_DataRateCapabilities_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdDataRateCapabilities_ForDataRate;

extern llrp_u16_t
LLRP_DataRateCapabilities_getForDataRate (
  LLRP_tSDataRateCapabilities *pThis);

extern LLRP_tResultCode
LLRP_DataRateCapabilities_setForDataRate (
  LLRP_tSDataRateCapabilities *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdDataRateCapabilities_RevDataRate;

extern llrp_u16_t
LLRP_DataRateCapabilities_getRevDataRate (
  LLRP_tSDataRateCapabilities *pThis);

extern LLRP_tResultCode
LLRP_DataRateCapabilities_setRevDataRate (
  LLRP_tSDataRateCapabilities *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_SM_valueCapabilities
{
    LLRP_tSParameter hdr;
  
    LLRP_tEM_value_Type eM_value;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdM_valueCapabilities;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdM_valueCapabilities[];

extern LLRP_tSM_valueCapabilities *
LLRP_M_valueCapabilities_construct (void);

extern void
LLRP_M_valueCapabilities_destruct (
 LLRP_tSM_valueCapabilities * pThis);

extern void
LLRP_M_valueCapabilities_decodeFields (
 LLRP_tSM_valueCapabilities * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_M_valueCapabilities_assimilateSubParameters (
 LLRP_tSM_valueCapabilities * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_M_valueCapabilities_encode (
  const LLRP_tSM_valueCapabilities *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_M_valueCapabilities_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdM_valueCapabilities_M_value;

extern LLRP_tEM_value_Type
LLRP_M_valueCapabilities_getM_value (
  LLRP_tSM_valueCapabilities *pThis);

extern LLRP_tResultCode
LLRP_M_valueCapabilities_setM_value (
  LLRP_tSM_valueCapabilities *pThis,
  LLRP_tEM_value_Type Value);

  


  
struct LLRP_SForward_link_modulationCapabilities
{
    LLRP_tSParameter hdr;
  
    LLRP_tEForward_link_Type eForward_link_modulation;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdForward_link_modulationCapabilities;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdForward_link_modulationCapabilities[];

extern LLRP_tSForward_link_modulationCapabilities *
LLRP_Forward_link_modulationCapabilities_construct (void);

extern void
LLRP_Forward_link_modulationCapabilities_destruct (
 LLRP_tSForward_link_modulationCapabilities * pThis);

extern void
LLRP_Forward_link_modulationCapabilities_decodeFields (
 LLRP_tSForward_link_modulationCapabilities * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_Forward_link_modulationCapabilities_assimilateSubParameters (
 LLRP_tSForward_link_modulationCapabilities * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_Forward_link_modulationCapabilities_encode (
  const LLRP_tSForward_link_modulationCapabilities *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_Forward_link_modulationCapabilities_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdForward_link_modulationCapabilities_Forward_link_modulation;

extern LLRP_tEForward_link_Type
LLRP_Forward_link_modulationCapabilities_getForward_link_modulation (
  LLRP_tSForward_link_modulationCapabilities *pThis);

extern LLRP_tResultCode
LLRP_Forward_link_modulationCapabilities_setForward_link_modulation (
  LLRP_tSForward_link_modulationCapabilities *pThis,
  LLRP_tEForward_link_Type Value);

  


  
struct LLRP_SModuleDepthEntry
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t Index;

    llrp_u16_t ModuleDepthEntry;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdModuleDepthEntry;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdModuleDepthEntry[];

extern LLRP_tSModuleDepthEntry *
LLRP_ModuleDepthEntry_construct (void);

extern void
LLRP_ModuleDepthEntry_destruct (
 LLRP_tSModuleDepthEntry * pThis);

extern void
LLRP_ModuleDepthEntry_decodeFields (
 LLRP_tSModuleDepthEntry * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_ModuleDepthEntry_assimilateSubParameters (
 LLRP_tSModuleDepthEntry * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_ModuleDepthEntry_encode (
  const LLRP_tSModuleDepthEntry *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_ModuleDepthEntry_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdModuleDepthEntry_Index;

extern llrp_u8_t
LLRP_ModuleDepthEntry_getIndex (
  LLRP_tSModuleDepthEntry *pThis);

extern LLRP_tResultCode
LLRP_ModuleDepthEntry_setIndex (
  LLRP_tSModuleDepthEntry *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdModuleDepthEntry_ModuleDepthEntry;

extern llrp_u16_t
LLRP_ModuleDepthEntry_getModuleDepthEntry (
  LLRP_tSModuleDepthEntry *pThis);

extern LLRP_tResultCode
LLRP_ModuleDepthEntry_setModuleDepthEntry (
  LLRP_tSModuleDepthEntry *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_SModuleDepthEntryFor6B
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t Index;

    llrp_u16_t ModuleDepthEntry;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdModuleDepthEntryFor6B;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdModuleDepthEntryFor6B[];

extern LLRP_tSModuleDepthEntryFor6B *
LLRP_ModuleDepthEntryFor6B_construct (void);

extern void
LLRP_ModuleDepthEntryFor6B_destruct (
 LLRP_tSModuleDepthEntryFor6B * pThis);

extern void
LLRP_ModuleDepthEntryFor6B_decodeFields (
 LLRP_tSModuleDepthEntryFor6B * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_ModuleDepthEntryFor6B_assimilateSubParameters (
 LLRP_tSModuleDepthEntryFor6B * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_ModuleDepthEntryFor6B_encode (
  const LLRP_tSModuleDepthEntryFor6B *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_ModuleDepthEntryFor6B_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdModuleDepthEntryFor6B_Index;

extern llrp_u8_t
LLRP_ModuleDepthEntryFor6B_getIndex (
  LLRP_tSModuleDepthEntryFor6B *pThis);

extern LLRP_tResultCode
LLRP_ModuleDepthEntryFor6B_setIndex (
  LLRP_tSModuleDepthEntryFor6B *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdModuleDepthEntryFor6B_ModuleDepthEntry;

extern llrp_u16_t
LLRP_ModuleDepthEntryFor6B_getModuleDepthEntry (
  LLRP_tSModuleDepthEntryFor6B *pThis);

extern LLRP_tResultCode
LLRP_ModuleDepthEntryFor6B_setModuleDepthEntry (
  LLRP_tSModuleDepthEntryFor6B *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_SPPPDialCapabilities
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t TimePhaseNums;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdPPPDialCapabilities;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdPPPDialCapabilities[];

extern LLRP_tSPPPDialCapabilities *
LLRP_PPPDialCapabilities_construct (void);

extern void
LLRP_PPPDialCapabilities_destruct (
 LLRP_tSPPPDialCapabilities * pThis);

extern void
LLRP_PPPDialCapabilities_decodeFields (
 LLRP_tSPPPDialCapabilities * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_PPPDialCapabilities_assimilateSubParameters (
 LLRP_tSPPPDialCapabilities * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_PPPDialCapabilities_encode (
  const LLRP_tSPPPDialCapabilities *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_PPPDialCapabilities_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdPPPDialCapabilities_TimePhaseNums;

extern llrp_u16_t
LLRP_PPPDialCapabilities_getTimePhaseNums (
  LLRP_tSPPPDialCapabilities *pThis);

extern LLRP_tResultCode
LLRP_PPPDialCapabilities_setTimePhaseNums (
  LLRP_tSPPPDialCapabilities *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_SSpecification
{
    LLRP_tSParameter hdr;
  
    llrp_u32_t Specification;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdSpecification;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSpecification[];

extern LLRP_tSSpecification *
LLRP_Specification_construct (void);

extern void
LLRP_Specification_destruct (
 LLRP_tSSpecification * pThis);

extern void
LLRP_Specification_decodeFields (
 LLRP_tSSpecification * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_Specification_assimilateSubParameters (
 LLRP_tSSpecification * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_Specification_encode (
  const LLRP_tSSpecification *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_Specification_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdSpecification_Specification;

extern llrp_u32_t
LLRP_Specification_getSpecification (
  LLRP_tSSpecification *pThis);

extern LLRP_tResultCode
LLRP_Specification_setSpecification (
  LLRP_tSSpecification *pThis,
  llrp_u32_t Value);

  


  
struct LLRP_SCommunicationCapabilities
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t SupportEthernet;

    llrp_u8_t SupportPPPDial;

    llrp_u8_t SupportGPRS;

    llrp_u8_t SupportUSB;

  
    LLRP_tSIPV4Support * pIPV4Support;

    LLRP_tSSerialPort232 * pSerialPort232;

    LLRP_tSSerialPort485 * pSerialPort485;

    LLRP_tSPPPDialCapabilities * pPPPDialCapabilities;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdCommunicationCapabilities;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdCommunicationCapabilities[];

extern LLRP_tSCommunicationCapabilities *
LLRP_CommunicationCapabilities_construct (void);

extern void
LLRP_CommunicationCapabilities_destruct (
 LLRP_tSCommunicationCapabilities * pThis);

extern void
LLRP_CommunicationCapabilities_decodeFields (
 LLRP_tSCommunicationCapabilities * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_CommunicationCapabilities_assimilateSubParameters (
 LLRP_tSCommunicationCapabilities * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_CommunicationCapabilities_encode (
  const LLRP_tSCommunicationCapabilities *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_CommunicationCapabilities_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdCommunicationCapabilities_SupportEthernet;

extern llrp_u8_t
LLRP_CommunicationCapabilities_getSupportEthernet (
  LLRP_tSCommunicationCapabilities *pThis);

extern LLRP_tResultCode
LLRP_CommunicationCapabilities_setSupportEthernet (
  LLRP_tSCommunicationCapabilities *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdCommunicationCapabilities_SupportPPPDial;

extern llrp_u8_t
LLRP_CommunicationCapabilities_getSupportPPPDial (
  LLRP_tSCommunicationCapabilities *pThis);

extern LLRP_tResultCode
LLRP_CommunicationCapabilities_setSupportPPPDial (
  LLRP_tSCommunicationCapabilities *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdCommunicationCapabilities_SupportGPRS;

extern llrp_u8_t
LLRP_CommunicationCapabilities_getSupportGPRS (
  LLRP_tSCommunicationCapabilities *pThis);

extern LLRP_tResultCode
LLRP_CommunicationCapabilities_setSupportGPRS (
  LLRP_tSCommunicationCapabilities *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdCommunicationCapabilities_SupportUSB;

extern llrp_u8_t
LLRP_CommunicationCapabilities_getSupportUSB (
  LLRP_tSCommunicationCapabilities *pThis);

extern LLRP_tResultCode
LLRP_CommunicationCapabilities_setSupportUSB (
  LLRP_tSCommunicationCapabilities *pThis,
  llrp_u8_t Value);

  
extern LLRP_tSIPV4Support *
LLRP_CommunicationCapabilities_getIPV4Support (
  LLRP_tSCommunicationCapabilities *pThis);

extern LLRP_tResultCode
LLRP_CommunicationCapabilities_setIPV4Support (
  LLRP_tSCommunicationCapabilities *pThis,
  LLRP_tSIPV4Support *pValue);

extern LLRP_tSSerialPort232 *
LLRP_CommunicationCapabilities_getSerialPort232 (
  LLRP_tSCommunicationCapabilities *pThis);

extern LLRP_tResultCode
LLRP_CommunicationCapabilities_setSerialPort232 (
  LLRP_tSCommunicationCapabilities *pThis,
  LLRP_tSSerialPort232 *pValue);

extern LLRP_tSSerialPort485 *
LLRP_CommunicationCapabilities_getSerialPort485 (
  LLRP_tSCommunicationCapabilities *pThis);

extern LLRP_tResultCode
LLRP_CommunicationCapabilities_setSerialPort485 (
  LLRP_tSCommunicationCapabilities *pThis,
  LLRP_tSSerialPort485 *pValue);

extern LLRP_tSPPPDialCapabilities *
LLRP_CommunicationCapabilities_getPPPDialCapabilities (
  LLRP_tSCommunicationCapabilities *pThis);

extern LLRP_tResultCode
LLRP_CommunicationCapabilities_setPPPDialCapabilities (
  LLRP_tSCommunicationCapabilities *pThis,
  LLRP_tSPPPDialCapabilities *pValue);



  
struct LLRP_SRUPCommunicationCapabilities
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t SupportEthernet;

    llrp_u8_t SupportWlan;

    llrp_u8_t SupportGPRS;

    llrp_u8_t SupportUSB;

    llrp_u8_t SupportTDSCDMA;

    llrp_u8_t SupportWCDMA;

    llrp_u8_t SupportCDMA2000;

    llrp_u8_t SupportPSAM;

  
    LLRP_tSIPV4Support * pIPV4Support;

    LLRP_tSSerialPort232 * pSerialPort232;

    LLRP_tSSerialPort485 * pSerialPort485;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdRUPCommunicationCapabilities;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdRUPCommunicationCapabilities[];

extern LLRP_tSRUPCommunicationCapabilities *
LLRP_RUPCommunicationCapabilities_construct (void);

extern void
LLRP_RUPCommunicationCapabilities_destruct (
 LLRP_tSRUPCommunicationCapabilities * pThis);

extern void
LLRP_RUPCommunicationCapabilities_decodeFields (
 LLRP_tSRUPCommunicationCapabilities * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_RUPCommunicationCapabilities_assimilateSubParameters (
 LLRP_tSRUPCommunicationCapabilities * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_RUPCommunicationCapabilities_encode (
  const LLRP_tSRUPCommunicationCapabilities *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_RUPCommunicationCapabilities_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdRUPCommunicationCapabilities_SupportEthernet;

extern llrp_u8_t
LLRP_RUPCommunicationCapabilities_getSupportEthernet (
  LLRP_tSRUPCommunicationCapabilities *pThis);

extern LLRP_tResultCode
LLRP_RUPCommunicationCapabilities_setSupportEthernet (
  LLRP_tSRUPCommunicationCapabilities *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdRUPCommunicationCapabilities_SupportWlan;

extern llrp_u8_t
LLRP_RUPCommunicationCapabilities_getSupportWlan (
  LLRP_tSRUPCommunicationCapabilities *pThis);

extern LLRP_tResultCode
LLRP_RUPCommunicationCapabilities_setSupportWlan (
  LLRP_tSRUPCommunicationCapabilities *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdRUPCommunicationCapabilities_SupportGPRS;

extern llrp_u8_t
LLRP_RUPCommunicationCapabilities_getSupportGPRS (
  LLRP_tSRUPCommunicationCapabilities *pThis);

extern LLRP_tResultCode
LLRP_RUPCommunicationCapabilities_setSupportGPRS (
  LLRP_tSRUPCommunicationCapabilities *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdRUPCommunicationCapabilities_SupportUSB;

extern llrp_u8_t
LLRP_RUPCommunicationCapabilities_getSupportUSB (
  LLRP_tSRUPCommunicationCapabilities *pThis);

extern LLRP_tResultCode
LLRP_RUPCommunicationCapabilities_setSupportUSB (
  LLRP_tSRUPCommunicationCapabilities *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdRUPCommunicationCapabilities_SupportTDSCDMA;

extern llrp_u8_t
LLRP_RUPCommunicationCapabilities_getSupportTDSCDMA (
  LLRP_tSRUPCommunicationCapabilities *pThis);

extern LLRP_tResultCode
LLRP_RUPCommunicationCapabilities_setSupportTDSCDMA (
  LLRP_tSRUPCommunicationCapabilities *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdRUPCommunicationCapabilities_SupportWCDMA;

extern llrp_u8_t
LLRP_RUPCommunicationCapabilities_getSupportWCDMA (
  LLRP_tSRUPCommunicationCapabilities *pThis);

extern LLRP_tResultCode
LLRP_RUPCommunicationCapabilities_setSupportWCDMA (
  LLRP_tSRUPCommunicationCapabilities *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdRUPCommunicationCapabilities_SupportCDMA2000;

extern llrp_u8_t
LLRP_RUPCommunicationCapabilities_getSupportCDMA2000 (
  LLRP_tSRUPCommunicationCapabilities *pThis);

extern LLRP_tResultCode
LLRP_RUPCommunicationCapabilities_setSupportCDMA2000 (
  LLRP_tSRUPCommunicationCapabilities *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdRUPCommunicationCapabilities_SupportPSAM;

extern llrp_u8_t
LLRP_RUPCommunicationCapabilities_getSupportPSAM (
  LLRP_tSRUPCommunicationCapabilities *pThis);

extern LLRP_tResultCode
LLRP_RUPCommunicationCapabilities_setSupportPSAM (
  LLRP_tSRUPCommunicationCapabilities *pThis,
  llrp_u8_t Value);

  
extern LLRP_tSIPV4Support *
LLRP_RUPCommunicationCapabilities_getIPV4Support (
  LLRP_tSRUPCommunicationCapabilities *pThis);

extern LLRP_tResultCode
LLRP_RUPCommunicationCapabilities_setIPV4Support (
  LLRP_tSRUPCommunicationCapabilities *pThis,
  LLRP_tSIPV4Support *pValue);

extern LLRP_tSSerialPort232 *
LLRP_RUPCommunicationCapabilities_getSerialPort232 (
  LLRP_tSRUPCommunicationCapabilities *pThis);

extern LLRP_tResultCode
LLRP_RUPCommunicationCapabilities_setSerialPort232 (
  LLRP_tSRUPCommunicationCapabilities *pThis,
  LLRP_tSSerialPort232 *pValue);

extern LLRP_tSSerialPort485 *
LLRP_RUPCommunicationCapabilities_getSerialPort485 (
  LLRP_tSRUPCommunicationCapabilities *pThis);

extern LLRP_tResultCode
LLRP_RUPCommunicationCapabilities_setSerialPort485 (
  LLRP_tSRUPCommunicationCapabilities *pThis,
  LLRP_tSSerialPort485 *pValue);



  
struct LLRP_SIPV4Support
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t GateWayNums;

    llrp_u16_t DNSAddrNums;

  
    LLRP_tSEthernetCards * pEthernetCards;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdIPV4Support;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdIPV4Support[];

extern LLRP_tSIPV4Support *
LLRP_IPV4Support_construct (void);

extern void
LLRP_IPV4Support_destruct (
 LLRP_tSIPV4Support * pThis);

extern void
LLRP_IPV4Support_decodeFields (
 LLRP_tSIPV4Support * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_IPV4Support_assimilateSubParameters (
 LLRP_tSIPV4Support * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_IPV4Support_encode (
  const LLRP_tSIPV4Support *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_IPV4Support_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdIPV4Support_GateWayNums;

extern llrp_u16_t
LLRP_IPV4Support_getGateWayNums (
  LLRP_tSIPV4Support *pThis);

extern LLRP_tResultCode
LLRP_IPV4Support_setGateWayNums (
  LLRP_tSIPV4Support *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdIPV4Support_DNSAddrNums;

extern llrp_u16_t
LLRP_IPV4Support_getDNSAddrNums (
  LLRP_tSIPV4Support *pThis);

extern LLRP_tResultCode
LLRP_IPV4Support_setDNSAddrNums (
  LLRP_tSIPV4Support *pThis,
  llrp_u16_t Value);

  
extern LLRP_tSEthernetCards *
LLRP_IPV4Support_getEthernetCards (
  LLRP_tSIPV4Support *pThis);

extern LLRP_tResultCode
LLRP_IPV4Support_setEthernetCards (
  LLRP_tSIPV4Support *pThis,
  LLRP_tSEthernetCards *pValue);



  
struct LLRP_SEthernetCards
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t EthernetCardNums;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdEthernetCards;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdEthernetCards[];

extern LLRP_tSEthernetCards *
LLRP_EthernetCards_construct (void);

extern void
LLRP_EthernetCards_destruct (
 LLRP_tSEthernetCards * pThis);

extern void
LLRP_EthernetCards_decodeFields (
 LLRP_tSEthernetCards * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_EthernetCards_assimilateSubParameters (
 LLRP_tSEthernetCards * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_EthernetCards_encode (
  const LLRP_tSEthernetCards *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_EthernetCards_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdEthernetCards_EthernetCardNums;

extern llrp_u16_t
LLRP_EthernetCards_getEthernetCardNums (
  LLRP_tSEthernetCards *pThis);

extern LLRP_tResultCode
LLRP_EthernetCards_setEthernetCardNums (
  LLRP_tSEthernetCards *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_SSerialPort232
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t PortNum;

  
    LLRP_tSSerialAttribute * listSerialAttribute;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdSerialPort232;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSerialPort232[];

extern LLRP_tSSerialPort232 *
LLRP_SerialPort232_construct (void);

extern void
LLRP_SerialPort232_destruct (
 LLRP_tSSerialPort232 * pThis);

extern void
LLRP_SerialPort232_decodeFields (
 LLRP_tSSerialPort232 * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SerialPort232_assimilateSubParameters (
 LLRP_tSSerialPort232 * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SerialPort232_encode (
  const LLRP_tSSerialPort232 *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_SerialPort232_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdSerialPort232_PortNum;

extern llrp_u16_t
LLRP_SerialPort232_getPortNum (
  LLRP_tSSerialPort232 *pThis);

extern LLRP_tResultCode
LLRP_SerialPort232_setPortNum (
  LLRP_tSSerialPort232 *pThis,
  llrp_u16_t Value);

  
extern LLRP_tSSerialAttribute *
LLRP_SerialPort232_beginSerialAttribute (
  LLRP_tSSerialPort232 *pThis);

extern LLRP_tSSerialAttribute *
LLRP_SerialPort232_nextSerialAttribute (
  LLRP_tSSerialAttribute *pCurrent);

extern void
LLRP_SerialPort232_clearSerialAttribute (
  LLRP_tSSerialPort232 *pThis);

extern LLRP_tResultCode
LLRP_SerialPort232_addSerialAttribute (
  LLRP_tSSerialPort232 *pThis,
  LLRP_tSSerialAttribute *pValue);




  
struct LLRP_SSerialPort485
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t PortNum;

  
    LLRP_tSSerialAttribute * listSerialAttribute;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdSerialPort485;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSerialPort485[];

extern LLRP_tSSerialPort485 *
LLRP_SerialPort485_construct (void);

extern void
LLRP_SerialPort485_destruct (
 LLRP_tSSerialPort485 * pThis);

extern void
LLRP_SerialPort485_decodeFields (
 LLRP_tSSerialPort485 * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SerialPort485_assimilateSubParameters (
 LLRP_tSSerialPort485 * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SerialPort485_encode (
  const LLRP_tSSerialPort485 *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_SerialPort485_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdSerialPort485_PortNum;

extern llrp_u16_t
LLRP_SerialPort485_getPortNum (
  LLRP_tSSerialPort485 *pThis);

extern LLRP_tResultCode
LLRP_SerialPort485_setPortNum (
  LLRP_tSSerialPort485 *pThis,
  llrp_u16_t Value);

  
extern LLRP_tSSerialAttribute *
LLRP_SerialPort485_beginSerialAttribute (
  LLRP_tSSerialPort485 *pThis);

extern LLRP_tSSerialAttribute *
LLRP_SerialPort485_nextSerialAttribute (
  LLRP_tSSerialAttribute *pCurrent);

extern void
LLRP_SerialPort485_clearSerialAttribute (
  LLRP_tSSerialPort485 *pThis);

extern LLRP_tResultCode
LLRP_SerialPort485_addSerialAttribute (
  LLRP_tSSerialPort485 *pThis,
  LLRP_tSSerialAttribute *pValue);




  
struct LLRP_SSerialAttribute
{
    LLRP_tSParameter hdr;
  
    llrp_u32_t BaudRate;

    llrp_u8_t DataBit;

    llrp_u8_t StopBit;

    llrp_u8_t Parity;

    llrp_u8_t FlowControl;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdSerialAttribute;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSerialAttribute[];

extern LLRP_tSSerialAttribute *
LLRP_SerialAttribute_construct (void);

extern void
LLRP_SerialAttribute_destruct (
 LLRP_tSSerialAttribute * pThis);

extern void
LLRP_SerialAttribute_decodeFields (
 LLRP_tSSerialAttribute * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SerialAttribute_assimilateSubParameters (
 LLRP_tSSerialAttribute * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SerialAttribute_encode (
  const LLRP_tSSerialAttribute *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_SerialAttribute_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdSerialAttribute_BaudRate;

extern llrp_u32_t
LLRP_SerialAttribute_getBaudRate (
  LLRP_tSSerialAttribute *pThis);

extern LLRP_tResultCode
LLRP_SerialAttribute_setBaudRate (
  LLRP_tSSerialAttribute *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSerialAttribute_DataBit;

extern llrp_u8_t
LLRP_SerialAttribute_getDataBit (
  LLRP_tSSerialAttribute *pThis);

extern LLRP_tResultCode
LLRP_SerialAttribute_setDataBit (
  LLRP_tSSerialAttribute *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSerialAttribute_StopBit;

extern llrp_u8_t
LLRP_SerialAttribute_getStopBit (
  LLRP_tSSerialAttribute *pThis);

extern LLRP_tResultCode
LLRP_SerialAttribute_setStopBit (
  LLRP_tSSerialAttribute *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSerialAttribute_Parity;

extern llrp_u8_t
LLRP_SerialAttribute_getParity (
  LLRP_tSSerialAttribute *pThis);

extern LLRP_tResultCode
LLRP_SerialAttribute_setParity (
  LLRP_tSSerialAttribute *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSerialAttribute_FlowControl;

extern llrp_u8_t
LLRP_SerialAttribute_getFlowControl (
  LLRP_tSSerialAttribute *pThis);

extern LLRP_tResultCode
LLRP_SerialAttribute_setFlowControl (
  LLRP_tSSerialAttribute *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SNTPServerCapabilities
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t NTPServerAddrNums;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdNTPServerCapabilities;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdNTPServerCapabilities[];

extern LLRP_tSNTPServerCapabilities *
LLRP_NTPServerCapabilities_construct (void);

extern void
LLRP_NTPServerCapabilities_destruct (
 LLRP_tSNTPServerCapabilities * pThis);

extern void
LLRP_NTPServerCapabilities_decodeFields (
 LLRP_tSNTPServerCapabilities * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_NTPServerCapabilities_assimilateSubParameters (
 LLRP_tSNTPServerCapabilities * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_NTPServerCapabilities_encode (
  const LLRP_tSNTPServerCapabilities *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_NTPServerCapabilities_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdNTPServerCapabilities_NTPServerAddrNums;

extern llrp_u16_t
LLRP_NTPServerCapabilities_getNTPServerAddrNums (
  LLRP_tSNTPServerCapabilities *pThis);

extern LLRP_tResultCode
LLRP_NTPServerCapabilities_setNTPServerAddrNums (
  LLRP_tSNTPServerCapabilities *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_SETCExtRegulatoryCapabilities
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t SupportsUBOOT;

  
    LLRP_tSModuleDepthEtcEntry * listModuleDepthEtcEntry;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdETCExtRegulatoryCapabilities;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdETCExtRegulatoryCapabilities[];

extern LLRP_tSETCExtRegulatoryCapabilities *
LLRP_ETCExtRegulatoryCapabilities_construct (void);

extern void
LLRP_ETCExtRegulatoryCapabilities_destruct (
 LLRP_tSETCExtRegulatoryCapabilities * pThis);

extern void
LLRP_ETCExtRegulatoryCapabilities_decodeFields (
 LLRP_tSETCExtRegulatoryCapabilities * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_ETCExtRegulatoryCapabilities_assimilateSubParameters (
 LLRP_tSETCExtRegulatoryCapabilities * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_ETCExtRegulatoryCapabilities_encode (
  const LLRP_tSETCExtRegulatoryCapabilities *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_ETCExtRegulatoryCapabilities_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdETCExtRegulatoryCapabilities_SupportsUBOOT;

extern llrp_u8_t
LLRP_ETCExtRegulatoryCapabilities_getSupportsUBOOT (
  LLRP_tSETCExtRegulatoryCapabilities *pThis);

extern LLRP_tResultCode
LLRP_ETCExtRegulatoryCapabilities_setSupportsUBOOT (
  LLRP_tSETCExtRegulatoryCapabilities *pThis,
  llrp_u8_t Value);

  
extern LLRP_tSModuleDepthEtcEntry *
LLRP_ETCExtRegulatoryCapabilities_beginModuleDepthEtcEntry (
  LLRP_tSETCExtRegulatoryCapabilities *pThis);

extern LLRP_tSModuleDepthEtcEntry *
LLRP_ETCExtRegulatoryCapabilities_nextModuleDepthEtcEntry (
  LLRP_tSModuleDepthEtcEntry *pCurrent);

extern void
LLRP_ETCExtRegulatoryCapabilities_clearModuleDepthEtcEntry (
  LLRP_tSETCExtRegulatoryCapabilities *pThis);

extern LLRP_tResultCode
LLRP_ETCExtRegulatoryCapabilities_addModuleDepthEtcEntry (
  LLRP_tSETCExtRegulatoryCapabilities *pThis,
  LLRP_tSModuleDepthEtcEntry *pValue);




  
struct LLRP_SMPIExtRegulatoryCapabilities
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t numPSAMWhiteList;

    llrp_u16_t numSIMWhiteList;

    llrp_u8_t SupportsUBOOT;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdMPIExtRegulatoryCapabilities;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdMPIExtRegulatoryCapabilities[];

extern LLRP_tSMPIExtRegulatoryCapabilities *
LLRP_MPIExtRegulatoryCapabilities_construct (void);

extern void
LLRP_MPIExtRegulatoryCapabilities_destruct (
 LLRP_tSMPIExtRegulatoryCapabilities * pThis);

extern void
LLRP_MPIExtRegulatoryCapabilities_decodeFields (
 LLRP_tSMPIExtRegulatoryCapabilities * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_MPIExtRegulatoryCapabilities_assimilateSubParameters (
 LLRP_tSMPIExtRegulatoryCapabilities * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_MPIExtRegulatoryCapabilities_encode (
  const LLRP_tSMPIExtRegulatoryCapabilities *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_MPIExtRegulatoryCapabilities_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdMPIExtRegulatoryCapabilities_numPSAMWhiteList;

extern llrp_u16_t
LLRP_MPIExtRegulatoryCapabilities_getnumPSAMWhiteList (
  LLRP_tSMPIExtRegulatoryCapabilities *pThis);

extern LLRP_tResultCode
LLRP_MPIExtRegulatoryCapabilities_setnumPSAMWhiteList (
  LLRP_tSMPIExtRegulatoryCapabilities *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdMPIExtRegulatoryCapabilities_numSIMWhiteList;

extern llrp_u16_t
LLRP_MPIExtRegulatoryCapabilities_getnumSIMWhiteList (
  LLRP_tSMPIExtRegulatoryCapabilities *pThis);

extern LLRP_tResultCode
LLRP_MPIExtRegulatoryCapabilities_setnumSIMWhiteList (
  LLRP_tSMPIExtRegulatoryCapabilities *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdMPIExtRegulatoryCapabilities_SupportsUBOOT;

extern llrp_u8_t
LLRP_MPIExtRegulatoryCapabilities_getSupportsUBOOT (
  LLRP_tSMPIExtRegulatoryCapabilities *pThis);

extern LLRP_tResultCode
LLRP_MPIExtRegulatoryCapabilities_setSupportsUBOOT (
  LLRP_tSMPIExtRegulatoryCapabilities *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SModuleDepthEtcEntry
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t Index;

    llrp_u16_t ModuleDepthEntry;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdModuleDepthEtcEntry;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdModuleDepthEtcEntry[];

extern LLRP_tSModuleDepthEtcEntry *
LLRP_ModuleDepthEtcEntry_construct (void);

extern void
LLRP_ModuleDepthEtcEntry_destruct (
 LLRP_tSModuleDepthEtcEntry * pThis);

extern void
LLRP_ModuleDepthEtcEntry_decodeFields (
 LLRP_tSModuleDepthEtcEntry * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_ModuleDepthEtcEntry_assimilateSubParameters (
 LLRP_tSModuleDepthEtcEntry * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_ModuleDepthEtcEntry_encode (
  const LLRP_tSModuleDepthEtcEntry *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_ModuleDepthEtcEntry_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdModuleDepthEtcEntry_Index;

extern llrp_u8_t
LLRP_ModuleDepthEtcEntry_getIndex (
  LLRP_tSModuleDepthEtcEntry *pThis);

extern LLRP_tResultCode
LLRP_ModuleDepthEtcEntry_setIndex (
  LLRP_tSModuleDepthEtcEntry *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdModuleDepthEtcEntry_ModuleDepthEntry;

extern llrp_u16_t
LLRP_ModuleDepthEtcEntry_getModuleDepthEntry (
  LLRP_tSModuleDepthEtcEntry *pThis);

extern LLRP_tResultCode
LLRP_ModuleDepthEtcEntry_setModuleDepthEntry (
  LLRP_tSModuleDepthEtcEntry *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_SRSSIFilter
{
    LLRP_tSParameter hdr;
  
  
    LLRP_tSRSSIFilterCtrl * listRSSIFilterCtrl;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdRSSIFilter;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdRSSIFilter[];

extern LLRP_tSRSSIFilter *
LLRP_RSSIFilter_construct (void);

extern void
LLRP_RSSIFilter_destruct (
 LLRP_tSRSSIFilter * pThis);

extern void
LLRP_RSSIFilter_decodeFields (
 LLRP_tSRSSIFilter * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_RSSIFilter_assimilateSubParameters (
 LLRP_tSRSSIFilter * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_RSSIFilter_encode (
  const LLRP_tSRSSIFilter *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_RSSIFilter_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
  
extern LLRP_tSRSSIFilterCtrl *
LLRP_RSSIFilter_beginRSSIFilterCtrl (
  LLRP_tSRSSIFilter *pThis);

extern LLRP_tSRSSIFilterCtrl *
LLRP_RSSIFilter_nextRSSIFilterCtrl (
  LLRP_tSRSSIFilterCtrl *pCurrent);

extern void
LLRP_RSSIFilter_clearRSSIFilterCtrl (
  LLRP_tSRSSIFilter *pThis);

extern LLRP_tResultCode
LLRP_RSSIFilter_addRSSIFilterCtrl (
  LLRP_tSRSSIFilter *pThis,
  LLRP_tSRSSIFilterCtrl *pValue);




  
struct LLRP_SRSSIFilterCtrl
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t TurnOnReadFilter;

    llrp_u16_t MaxReadRSSI;

    llrp_u8_t RSSIReadFilterThreshold;

    llrp_u8_t TurnOnWriteFilter;

    llrp_u16_t MaxWriteRSSI;

    llrp_u8_t RSSIWriteFilterThreshold;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdRSSIFilterCtrl;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdRSSIFilterCtrl[];

extern LLRP_tSRSSIFilterCtrl *
LLRP_RSSIFilterCtrl_construct (void);

extern void
LLRP_RSSIFilterCtrl_destruct (
 LLRP_tSRSSIFilterCtrl * pThis);

extern void
LLRP_RSSIFilterCtrl_decodeFields (
 LLRP_tSRSSIFilterCtrl * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_RSSIFilterCtrl_assimilateSubParameters (
 LLRP_tSRSSIFilterCtrl * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_RSSIFilterCtrl_encode (
  const LLRP_tSRSSIFilterCtrl *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_RSSIFilterCtrl_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdRSSIFilterCtrl_TurnOnReadFilter;

extern llrp_u8_t
LLRP_RSSIFilterCtrl_getTurnOnReadFilter (
  LLRP_tSRSSIFilterCtrl *pThis);

extern LLRP_tResultCode
LLRP_RSSIFilterCtrl_setTurnOnReadFilter (
  LLRP_tSRSSIFilterCtrl *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdRSSIFilterCtrl_MaxReadRSSI;

extern llrp_u16_t
LLRP_RSSIFilterCtrl_getMaxReadRSSI (
  LLRP_tSRSSIFilterCtrl *pThis);

extern LLRP_tResultCode
LLRP_RSSIFilterCtrl_setMaxReadRSSI (
  LLRP_tSRSSIFilterCtrl *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdRSSIFilterCtrl_RSSIReadFilterThreshold;

extern llrp_u8_t
LLRP_RSSIFilterCtrl_getRSSIReadFilterThreshold (
  LLRP_tSRSSIFilterCtrl *pThis);

extern LLRP_tResultCode
LLRP_RSSIFilterCtrl_setRSSIReadFilterThreshold (
  LLRP_tSRSSIFilterCtrl *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdRSSIFilterCtrl_TurnOnWriteFilter;

extern llrp_u8_t
LLRP_RSSIFilterCtrl_getTurnOnWriteFilter (
  LLRP_tSRSSIFilterCtrl *pThis);

extern LLRP_tResultCode
LLRP_RSSIFilterCtrl_setTurnOnWriteFilter (
  LLRP_tSRSSIFilterCtrl *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdRSSIFilterCtrl_MaxWriteRSSI;

extern llrp_u16_t
LLRP_RSSIFilterCtrl_getMaxWriteRSSI (
  LLRP_tSRSSIFilterCtrl *pThis);

extern LLRP_tResultCode
LLRP_RSSIFilterCtrl_setMaxWriteRSSI (
  LLRP_tSRSSIFilterCtrl *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdRSSIFilterCtrl_RSSIWriteFilterThreshold;

extern llrp_u8_t
LLRP_RSSIFilterCtrl_getRSSIWriteFilterThreshold (
  LLRP_tSRSSIFilterCtrl *pThis);

extern LLRP_tResultCode
LLRP_RSSIFilterCtrl_setRSSIWriteFilterThreshold (
  LLRP_tSRSSIFilterCtrl *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SReaderName
{
    LLRP_tSParameter hdr;
  
    llrp_utf8v_t ReaderName;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdReaderName;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdReaderName[];

extern LLRP_tSReaderName *
LLRP_ReaderName_construct (void);

extern void
LLRP_ReaderName_destruct (
 LLRP_tSReaderName * pThis);

extern void
LLRP_ReaderName_decodeFields (
 LLRP_tSReaderName * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_ReaderName_assimilateSubParameters (
 LLRP_tSReaderName * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_ReaderName_encode (
  const LLRP_tSReaderName *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_ReaderName_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdReaderName_ReaderName;

extern llrp_utf8v_t
LLRP_ReaderName_getReaderName (
  LLRP_tSReaderName *pThis);

extern LLRP_tResultCode
LLRP_ReaderName_setReaderName (
  LLRP_tSReaderName *pThis,
  llrp_utf8v_t Value);

  


  
struct LLRP_SReaderBasicInfo
{
    LLRP_tSParameter hdr;
  
    llrp_u32_t Device_manufacturer_name;

    llrp_u32_t Model_name;

    llrp_u32_t Specification;

    llrp_utf8v_t Version;

    llrp_u8v_t DeviceSerialNum;

  
    LLRP_tSIdentification * pIdentification;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdReaderBasicInfo;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdReaderBasicInfo[];

extern LLRP_tSReaderBasicInfo *
LLRP_ReaderBasicInfo_construct (void);

extern void
LLRP_ReaderBasicInfo_destruct (
 LLRP_tSReaderBasicInfo * pThis);

extern void
LLRP_ReaderBasicInfo_decodeFields (
 LLRP_tSReaderBasicInfo * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_ReaderBasicInfo_assimilateSubParameters (
 LLRP_tSReaderBasicInfo * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_ReaderBasicInfo_encode (
  const LLRP_tSReaderBasicInfo *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_ReaderBasicInfo_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdReaderBasicInfo_Device_manufacturer_name;

extern llrp_u32_t
LLRP_ReaderBasicInfo_getDevice_manufacturer_name (
  LLRP_tSReaderBasicInfo *pThis);

extern LLRP_tResultCode
LLRP_ReaderBasicInfo_setDevice_manufacturer_name (
  LLRP_tSReaderBasicInfo *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdReaderBasicInfo_Model_name;

extern llrp_u32_t
LLRP_ReaderBasicInfo_getModel_name (
  LLRP_tSReaderBasicInfo *pThis);

extern LLRP_tResultCode
LLRP_ReaderBasicInfo_setModel_name (
  LLRP_tSReaderBasicInfo *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdReaderBasicInfo_Specification;

extern llrp_u32_t
LLRP_ReaderBasicInfo_getSpecification (
  LLRP_tSReaderBasicInfo *pThis);

extern LLRP_tResultCode
LLRP_ReaderBasicInfo_setSpecification (
  LLRP_tSReaderBasicInfo *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdReaderBasicInfo_Version;

extern llrp_utf8v_t
LLRP_ReaderBasicInfo_getVersion (
  LLRP_tSReaderBasicInfo *pThis);

extern LLRP_tResultCode
LLRP_ReaderBasicInfo_setVersion (
  LLRP_tSReaderBasicInfo *pThis,
  llrp_utf8v_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdReaderBasicInfo_DeviceSerialNum;

extern llrp_u8v_t
LLRP_ReaderBasicInfo_getDeviceSerialNum (
  LLRP_tSReaderBasicInfo *pThis);

extern LLRP_tResultCode
LLRP_ReaderBasicInfo_setDeviceSerialNum (
  LLRP_tSReaderBasicInfo *pThis,
  llrp_u8v_t Value);

  
extern LLRP_tSIdentification *
LLRP_ReaderBasicInfo_getIdentification (
  LLRP_tSReaderBasicInfo *pThis);

extern LLRP_tResultCode
LLRP_ReaderBasicInfo_setIdentification (
  LLRP_tSReaderBasicInfo *pThis,
  LLRP_tSIdentification *pValue);



  
struct LLRP_SDeviceID
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t DeviceID;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdDeviceID;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdDeviceID[];

extern LLRP_tSDeviceID *
LLRP_DeviceID_construct (void);

extern void
LLRP_DeviceID_destruct (
 LLRP_tSDeviceID * pThis);

extern void
LLRP_DeviceID_decodeFields (
 LLRP_tSDeviceID * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_DeviceID_assimilateSubParameters (
 LLRP_tSDeviceID * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_DeviceID_encode (
  const LLRP_tSDeviceID *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_DeviceID_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdDeviceID_DeviceID;

extern llrp_u16_t
LLRP_DeviceID_getDeviceID (
  LLRP_tSDeviceID *pThis);

extern LLRP_tResultCode
LLRP_DeviceID_setDeviceID (
  LLRP_tSDeviceID *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_SSaveReportSwitch
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t ReportSwitch;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdSaveReportSwitch;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSaveReportSwitch[];

extern LLRP_tSSaveReportSwitch *
LLRP_SaveReportSwitch_construct (void);

extern void
LLRP_SaveReportSwitch_destruct (
 LLRP_tSSaveReportSwitch * pThis);

extern void
LLRP_SaveReportSwitch_decodeFields (
 LLRP_tSSaveReportSwitch * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SaveReportSwitch_assimilateSubParameters (
 LLRP_tSSaveReportSwitch * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SaveReportSwitch_encode (
  const LLRP_tSSaveReportSwitch *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_SaveReportSwitch_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdSaveReportSwitch_ReportSwitch;

extern llrp_u8_t
LLRP_SaveReportSwitch_getReportSwitch (
  LLRP_tSSaveReportSwitch *pThis);

extern LLRP_tResultCode
LLRP_SaveReportSwitch_setReportSwitch (
  LLRP_tSSaveReportSwitch *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SAntennaExtConfiguration
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t AntennaID;

    LLRP_tEForandRevConfigType eForandRevConfig;

    llrp_u8_t SupportCheckStatus;

  
    LLRP_tSLBT * pLBT;

    LLRP_tSFrequencyConfiguration * pFrequencyConfiguration;

    LLRP_tSRSSIFilter * pRSSIFilter;

    LLRP_tSRecvFilter * pRecvFilter;

    LLRP_tSTransmitPower * pTransmitPower;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdAntennaExtConfiguration;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdAntennaExtConfiguration[];

extern LLRP_tSAntennaExtConfiguration *
LLRP_AntennaExtConfiguration_construct (void);

extern void
LLRP_AntennaExtConfiguration_destruct (
 LLRP_tSAntennaExtConfiguration * pThis);

extern void
LLRP_AntennaExtConfiguration_decodeFields (
 LLRP_tSAntennaExtConfiguration * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_AntennaExtConfiguration_assimilateSubParameters (
 LLRP_tSAntennaExtConfiguration * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_AntennaExtConfiguration_encode (
  const LLRP_tSAntennaExtConfiguration *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_AntennaExtConfiguration_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdAntennaExtConfiguration_AntennaID;

extern llrp_u16_t
LLRP_AntennaExtConfiguration_getAntennaID (
  LLRP_tSAntennaExtConfiguration *pThis);

extern LLRP_tResultCode
LLRP_AntennaExtConfiguration_setAntennaID (
  LLRP_tSAntennaExtConfiguration *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdAntennaExtConfiguration_ForandRevConfig;

extern LLRP_tEForandRevConfigType
LLRP_AntennaExtConfiguration_getForandRevConfig (
  LLRP_tSAntennaExtConfiguration *pThis);

extern LLRP_tResultCode
LLRP_AntennaExtConfiguration_setForandRevConfig (
  LLRP_tSAntennaExtConfiguration *pThis,
  LLRP_tEForandRevConfigType Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdAntennaExtConfiguration_SupportCheckStatus;

extern llrp_u8_t
LLRP_AntennaExtConfiguration_getSupportCheckStatus (
  LLRP_tSAntennaExtConfiguration *pThis);

extern LLRP_tResultCode
LLRP_AntennaExtConfiguration_setSupportCheckStatus (
  LLRP_tSAntennaExtConfiguration *pThis,
  llrp_u8_t Value);

  
extern LLRP_tSLBT *
LLRP_AntennaExtConfiguration_getLBT (
  LLRP_tSAntennaExtConfiguration *pThis);

extern LLRP_tResultCode
LLRP_AntennaExtConfiguration_setLBT (
  LLRP_tSAntennaExtConfiguration *pThis,
  LLRP_tSLBT *pValue);

extern LLRP_tSFrequencyConfiguration *
LLRP_AntennaExtConfiguration_getFrequencyConfiguration (
  LLRP_tSAntennaExtConfiguration *pThis);

extern LLRP_tResultCode
LLRP_AntennaExtConfiguration_setFrequencyConfiguration (
  LLRP_tSAntennaExtConfiguration *pThis,
  LLRP_tSFrequencyConfiguration *pValue);

extern LLRP_tSRSSIFilter *
LLRP_AntennaExtConfiguration_getRSSIFilter (
  LLRP_tSAntennaExtConfiguration *pThis);

extern LLRP_tResultCode
LLRP_AntennaExtConfiguration_setRSSIFilter (
  LLRP_tSAntennaExtConfiguration *pThis,
  LLRP_tSRSSIFilter *pValue);

extern LLRP_tSRecvFilter *
LLRP_AntennaExtConfiguration_getRecvFilter (
  LLRP_tSAntennaExtConfiguration *pThis);

extern LLRP_tResultCode
LLRP_AntennaExtConfiguration_setRecvFilter (
  LLRP_tSAntennaExtConfiguration *pThis,
  LLRP_tSRecvFilter *pValue);

extern LLRP_tSTransmitPower *
LLRP_AntennaExtConfiguration_getTransmitPower (
  LLRP_tSAntennaExtConfiguration *pThis);

extern LLRP_tResultCode
LLRP_AntennaExtConfiguration_setTransmitPower (
  LLRP_tSAntennaExtConfiguration *pThis,
  LLRP_tSTransmitPower *pValue);



  
struct LLRP_SUHFAntennaExtConfiguration
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t AntennaID;

    LLRP_tEForandRevConfigType eForandRevConfig;

    llrp_u8_t SupportCheckStatus;

  
    LLRP_tSLBT * pLBT;

    LLRP_tSUHFFrequencyConfiguration * pUHFFrequencyConfiguration;

    LLRP_tSRSSIFilter * pRSSIFilter;

    LLRP_tSRecvFilter * pRecvFilter;

    LLRP_tSTransmitPower * pTransmitPower;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdUHFAntennaExtConfiguration;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdUHFAntennaExtConfiguration[];

extern LLRP_tSUHFAntennaExtConfiguration *
LLRP_UHFAntennaExtConfiguration_construct (void);

extern void
LLRP_UHFAntennaExtConfiguration_destruct (
 LLRP_tSUHFAntennaExtConfiguration * pThis);

extern void
LLRP_UHFAntennaExtConfiguration_decodeFields (
 LLRP_tSUHFAntennaExtConfiguration * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_UHFAntennaExtConfiguration_assimilateSubParameters (
 LLRP_tSUHFAntennaExtConfiguration * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_UHFAntennaExtConfiguration_encode (
  const LLRP_tSUHFAntennaExtConfiguration *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_UHFAntennaExtConfiguration_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdUHFAntennaExtConfiguration_AntennaID;

extern llrp_u16_t
LLRP_UHFAntennaExtConfiguration_getAntennaID (
  LLRP_tSUHFAntennaExtConfiguration *pThis);

extern LLRP_tResultCode
LLRP_UHFAntennaExtConfiguration_setAntennaID (
  LLRP_tSUHFAntennaExtConfiguration *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdUHFAntennaExtConfiguration_ForandRevConfig;

extern LLRP_tEForandRevConfigType
LLRP_UHFAntennaExtConfiguration_getForandRevConfig (
  LLRP_tSUHFAntennaExtConfiguration *pThis);

extern LLRP_tResultCode
LLRP_UHFAntennaExtConfiguration_setForandRevConfig (
  LLRP_tSUHFAntennaExtConfiguration *pThis,
  LLRP_tEForandRevConfigType Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdUHFAntennaExtConfiguration_SupportCheckStatus;

extern llrp_u8_t
LLRP_UHFAntennaExtConfiguration_getSupportCheckStatus (
  LLRP_tSUHFAntennaExtConfiguration *pThis);

extern LLRP_tResultCode
LLRP_UHFAntennaExtConfiguration_setSupportCheckStatus (
  LLRP_tSUHFAntennaExtConfiguration *pThis,
  llrp_u8_t Value);

  
extern LLRP_tSLBT *
LLRP_UHFAntennaExtConfiguration_getLBT (
  LLRP_tSUHFAntennaExtConfiguration *pThis);

extern LLRP_tResultCode
LLRP_UHFAntennaExtConfiguration_setLBT (
  LLRP_tSUHFAntennaExtConfiguration *pThis,
  LLRP_tSLBT *pValue);

extern LLRP_tSUHFFrequencyConfiguration *
LLRP_UHFAntennaExtConfiguration_getUHFFrequencyConfiguration (
  LLRP_tSUHFAntennaExtConfiguration *pThis);

extern LLRP_tResultCode
LLRP_UHFAntennaExtConfiguration_setUHFFrequencyConfiguration (
  LLRP_tSUHFAntennaExtConfiguration *pThis,
  LLRP_tSUHFFrequencyConfiguration *pValue);

extern LLRP_tSRSSIFilter *
LLRP_UHFAntennaExtConfiguration_getRSSIFilter (
  LLRP_tSUHFAntennaExtConfiguration *pThis);

extern LLRP_tResultCode
LLRP_UHFAntennaExtConfiguration_setRSSIFilter (
  LLRP_tSUHFAntennaExtConfiguration *pThis,
  LLRP_tSRSSIFilter *pValue);

extern LLRP_tSRecvFilter *
LLRP_UHFAntennaExtConfiguration_getRecvFilter (
  LLRP_tSUHFAntennaExtConfiguration *pThis);

extern LLRP_tResultCode
LLRP_UHFAntennaExtConfiguration_setRecvFilter (
  LLRP_tSUHFAntennaExtConfiguration *pThis,
  LLRP_tSRecvFilter *pValue);

extern LLRP_tSTransmitPower *
LLRP_UHFAntennaExtConfiguration_getTransmitPower (
  LLRP_tSUHFAntennaExtConfiguration *pThis);

extern LLRP_tResultCode
LLRP_UHFAntennaExtConfiguration_setTransmitPower (
  LLRP_tSUHFAntennaExtConfiguration *pThis,
  LLRP_tSTransmitPower *pValue);



  
struct LLRP_SUHFFrequencyConfiguration
{
    LLRP_tSParameter hdr;
  
  
    LLRP_tSUHFFrequencyConfiguration6B * pUHFFrequencyConfiguration6B;

    LLRP_tSUHFFrequencyConfiguration6C * pUHFFrequencyConfiguration6C;

    LLRP_tSUHFFrequencyConfigurationGB * pUHFFrequencyConfigurationGB;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdUHFFrequencyConfiguration;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdUHFFrequencyConfiguration[];

extern LLRP_tSUHFFrequencyConfiguration *
LLRP_UHFFrequencyConfiguration_construct (void);

extern void
LLRP_UHFFrequencyConfiguration_destruct (
 LLRP_tSUHFFrequencyConfiguration * pThis);

extern void
LLRP_UHFFrequencyConfiguration_decodeFields (
 LLRP_tSUHFFrequencyConfiguration * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_UHFFrequencyConfiguration_assimilateSubParameters (
 LLRP_tSUHFFrequencyConfiguration * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_UHFFrequencyConfiguration_encode (
  const LLRP_tSUHFFrequencyConfiguration *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_UHFFrequencyConfiguration_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
  
extern LLRP_tSUHFFrequencyConfiguration6B *
LLRP_UHFFrequencyConfiguration_getUHFFrequencyConfiguration6B (
  LLRP_tSUHFFrequencyConfiguration *pThis);

extern LLRP_tResultCode
LLRP_UHFFrequencyConfiguration_setUHFFrequencyConfiguration6B (
  LLRP_tSUHFFrequencyConfiguration *pThis,
  LLRP_tSUHFFrequencyConfiguration6B *pValue);

extern LLRP_tSUHFFrequencyConfiguration6C *
LLRP_UHFFrequencyConfiguration_getUHFFrequencyConfiguration6C (
  LLRP_tSUHFFrequencyConfiguration *pThis);

extern LLRP_tResultCode
LLRP_UHFFrequencyConfiguration_setUHFFrequencyConfiguration6C (
  LLRP_tSUHFFrequencyConfiguration *pThis,
  LLRP_tSUHFFrequencyConfiguration6C *pValue);

extern LLRP_tSUHFFrequencyConfigurationGB *
LLRP_UHFFrequencyConfiguration_getUHFFrequencyConfigurationGB (
  LLRP_tSUHFFrequencyConfiguration *pThis);

extern LLRP_tResultCode
LLRP_UHFFrequencyConfiguration_setUHFFrequencyConfigurationGB (
  LLRP_tSUHFFrequencyConfiguration *pThis,
  LLRP_tSUHFFrequencyConfigurationGB *pValue);



  
struct LLRP_SUHFFrequencyConfiguration6B
{
    LLRP_tSParameter hdr;
  
  
    LLRP_tSFrequencyConfiguration * pFrequencyConfiguration;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdUHFFrequencyConfiguration6B;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdUHFFrequencyConfiguration6B[];

extern LLRP_tSUHFFrequencyConfiguration6B *
LLRP_UHFFrequencyConfiguration6B_construct (void);

extern void
LLRP_UHFFrequencyConfiguration6B_destruct (
 LLRP_tSUHFFrequencyConfiguration6B * pThis);

extern void
LLRP_UHFFrequencyConfiguration6B_decodeFields (
 LLRP_tSUHFFrequencyConfiguration6B * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_UHFFrequencyConfiguration6B_assimilateSubParameters (
 LLRP_tSUHFFrequencyConfiguration6B * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_UHFFrequencyConfiguration6B_encode (
  const LLRP_tSUHFFrequencyConfiguration6B *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_UHFFrequencyConfiguration6B_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
  
extern LLRP_tSFrequencyConfiguration *
LLRP_UHFFrequencyConfiguration6B_getFrequencyConfiguration (
  LLRP_tSUHFFrequencyConfiguration6B *pThis);

extern LLRP_tResultCode
LLRP_UHFFrequencyConfiguration6B_setFrequencyConfiguration (
  LLRP_tSUHFFrequencyConfiguration6B *pThis,
  LLRP_tSFrequencyConfiguration *pValue);



  
struct LLRP_SUHFFrequencyConfiguration6C
{
    LLRP_tSParameter hdr;
  
  
    LLRP_tSFrequencyConfiguration * pFrequencyConfiguration;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdUHFFrequencyConfiguration6C;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdUHFFrequencyConfiguration6C[];

extern LLRP_tSUHFFrequencyConfiguration6C *
LLRP_UHFFrequencyConfiguration6C_construct (void);

extern void
LLRP_UHFFrequencyConfiguration6C_destruct (
 LLRP_tSUHFFrequencyConfiguration6C * pThis);

extern void
LLRP_UHFFrequencyConfiguration6C_decodeFields (
 LLRP_tSUHFFrequencyConfiguration6C * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_UHFFrequencyConfiguration6C_assimilateSubParameters (
 LLRP_tSUHFFrequencyConfiguration6C * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_UHFFrequencyConfiguration6C_encode (
  const LLRP_tSUHFFrequencyConfiguration6C *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_UHFFrequencyConfiguration6C_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
  
extern LLRP_tSFrequencyConfiguration *
LLRP_UHFFrequencyConfiguration6C_getFrequencyConfiguration (
  LLRP_tSUHFFrequencyConfiguration6C *pThis);

extern LLRP_tResultCode
LLRP_UHFFrequencyConfiguration6C_setFrequencyConfiguration (
  LLRP_tSUHFFrequencyConfiguration6C *pThis,
  LLRP_tSFrequencyConfiguration *pValue);



  
struct LLRP_SUHFFrequencyConfigurationGB
{
    LLRP_tSParameter hdr;
  
  
    LLRP_tSFrequencyConfiguration * pFrequencyConfiguration;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdUHFFrequencyConfigurationGB;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdUHFFrequencyConfigurationGB[];

extern LLRP_tSUHFFrequencyConfigurationGB *
LLRP_UHFFrequencyConfigurationGB_construct (void);

extern void
LLRP_UHFFrequencyConfigurationGB_destruct (
 LLRP_tSUHFFrequencyConfigurationGB * pThis);

extern void
LLRP_UHFFrequencyConfigurationGB_decodeFields (
 LLRP_tSUHFFrequencyConfigurationGB * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_UHFFrequencyConfigurationGB_assimilateSubParameters (
 LLRP_tSUHFFrequencyConfigurationGB * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_UHFFrequencyConfigurationGB_encode (
  const LLRP_tSUHFFrequencyConfigurationGB *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_UHFFrequencyConfigurationGB_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
  
extern LLRP_tSFrequencyConfiguration *
LLRP_UHFFrequencyConfigurationGB_getFrequencyConfiguration (
  LLRP_tSUHFFrequencyConfigurationGB *pThis);

extern LLRP_tResultCode
LLRP_UHFFrequencyConfigurationGB_setFrequencyConfiguration (
  LLRP_tSUHFFrequencyConfigurationGB *pThis,
  LLRP_tSFrequencyConfiguration *pValue);



  
struct LLRP_SRUPAlarmThreshold
{
    LLRP_tSParameter hdr;
  
  
    LLRP_tSTemperatureThreshold * pTemperatureThreshold;

    LLRP_tSMemoryThreshold * pMemoryThreshold;

    LLRP_tSCPUUtilizationThreshold * pCPUUtilizationThreshold;

    LLRP_tSJffsFileThreshold * pJffsFileThreshold;

    LLRP_tSLightningBoxThreshold * pLightningBoxThreshold;

    LLRP_tSPowerDifferenceThreshold * pPowerDifferenceThreshold;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdRUPAlarmThreshold;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdRUPAlarmThreshold[];

extern LLRP_tSRUPAlarmThreshold *
LLRP_RUPAlarmThreshold_construct (void);

extern void
LLRP_RUPAlarmThreshold_destruct (
 LLRP_tSRUPAlarmThreshold * pThis);

extern void
LLRP_RUPAlarmThreshold_decodeFields (
 LLRP_tSRUPAlarmThreshold * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_RUPAlarmThreshold_assimilateSubParameters (
 LLRP_tSRUPAlarmThreshold * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_RUPAlarmThreshold_encode (
  const LLRP_tSRUPAlarmThreshold *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_RUPAlarmThreshold_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
  
extern LLRP_tSTemperatureThreshold *
LLRP_RUPAlarmThreshold_getTemperatureThreshold (
  LLRP_tSRUPAlarmThreshold *pThis);

extern LLRP_tResultCode
LLRP_RUPAlarmThreshold_setTemperatureThreshold (
  LLRP_tSRUPAlarmThreshold *pThis,
  LLRP_tSTemperatureThreshold *pValue);

extern LLRP_tSMemoryThreshold *
LLRP_RUPAlarmThreshold_getMemoryThreshold (
  LLRP_tSRUPAlarmThreshold *pThis);

extern LLRP_tResultCode
LLRP_RUPAlarmThreshold_setMemoryThreshold (
  LLRP_tSRUPAlarmThreshold *pThis,
  LLRP_tSMemoryThreshold *pValue);

extern LLRP_tSCPUUtilizationThreshold *
LLRP_RUPAlarmThreshold_getCPUUtilizationThreshold (
  LLRP_tSRUPAlarmThreshold *pThis);

extern LLRP_tResultCode
LLRP_RUPAlarmThreshold_setCPUUtilizationThreshold (
  LLRP_tSRUPAlarmThreshold *pThis,
  LLRP_tSCPUUtilizationThreshold *pValue);

extern LLRP_tSJffsFileThreshold *
LLRP_RUPAlarmThreshold_getJffsFileThreshold (
  LLRP_tSRUPAlarmThreshold *pThis);

extern LLRP_tResultCode
LLRP_RUPAlarmThreshold_setJffsFileThreshold (
  LLRP_tSRUPAlarmThreshold *pThis,
  LLRP_tSJffsFileThreshold *pValue);

extern LLRP_tSLightningBoxThreshold *
LLRP_RUPAlarmThreshold_getLightningBoxThreshold (
  LLRP_tSRUPAlarmThreshold *pThis);

extern LLRP_tResultCode
LLRP_RUPAlarmThreshold_setLightningBoxThreshold (
  LLRP_tSRUPAlarmThreshold *pThis,
  LLRP_tSLightningBoxThreshold *pValue);

extern LLRP_tSPowerDifferenceThreshold *
LLRP_RUPAlarmThreshold_getPowerDifferenceThreshold (
  LLRP_tSRUPAlarmThreshold *pThis);

extern LLRP_tResultCode
LLRP_RUPAlarmThreshold_setPowerDifferenceThreshold (
  LLRP_tSRUPAlarmThreshold *pThis,
  LLRP_tSPowerDifferenceThreshold *pValue);



  
struct LLRP_STemperatureThreshold
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t TemperatureMaxValue;

    llrp_s8_t TemperatureMinValue;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdTemperatureThreshold;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdTemperatureThreshold[];

extern LLRP_tSTemperatureThreshold *
LLRP_TemperatureThreshold_construct (void);

extern void
LLRP_TemperatureThreshold_destruct (
 LLRP_tSTemperatureThreshold * pThis);

extern void
LLRP_TemperatureThreshold_decodeFields (
 LLRP_tSTemperatureThreshold * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_TemperatureThreshold_assimilateSubParameters (
 LLRP_tSTemperatureThreshold * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_TemperatureThreshold_encode (
  const LLRP_tSTemperatureThreshold *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_TemperatureThreshold_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdTemperatureThreshold_TemperatureMaxValue;

extern llrp_u8_t
LLRP_TemperatureThreshold_getTemperatureMaxValue (
  LLRP_tSTemperatureThreshold *pThis);

extern LLRP_tResultCode
LLRP_TemperatureThreshold_setTemperatureMaxValue (
  LLRP_tSTemperatureThreshold *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdTemperatureThreshold_TemperatureMinValue;

extern llrp_s8_t
LLRP_TemperatureThreshold_getTemperatureMinValue (
  LLRP_tSTemperatureThreshold *pThis);

extern LLRP_tResultCode
LLRP_TemperatureThreshold_setTemperatureMinValue (
  LLRP_tSTemperatureThreshold *pThis,
  llrp_s8_t Value);

  


  
struct LLRP_SMemoryThreshold
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t MemoryMaxValue;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdMemoryThreshold;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdMemoryThreshold[];

extern LLRP_tSMemoryThreshold *
LLRP_MemoryThreshold_construct (void);

extern void
LLRP_MemoryThreshold_destruct (
 LLRP_tSMemoryThreshold * pThis);

extern void
LLRP_MemoryThreshold_decodeFields (
 LLRP_tSMemoryThreshold * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_MemoryThreshold_assimilateSubParameters (
 LLRP_tSMemoryThreshold * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_MemoryThreshold_encode (
  const LLRP_tSMemoryThreshold *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_MemoryThreshold_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdMemoryThreshold_MemoryMaxValue;

extern llrp_u8_t
LLRP_MemoryThreshold_getMemoryMaxValue (
  LLRP_tSMemoryThreshold *pThis);

extern LLRP_tResultCode
LLRP_MemoryThreshold_setMemoryMaxValue (
  LLRP_tSMemoryThreshold *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SCPUUtilizationThreshold
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t CPUUtilizationThresholdMaxValue;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdCPUUtilizationThreshold;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdCPUUtilizationThreshold[];

extern LLRP_tSCPUUtilizationThreshold *
LLRP_CPUUtilizationThreshold_construct (void);

extern void
LLRP_CPUUtilizationThreshold_destruct (
 LLRP_tSCPUUtilizationThreshold * pThis);

extern void
LLRP_CPUUtilizationThreshold_decodeFields (
 LLRP_tSCPUUtilizationThreshold * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_CPUUtilizationThreshold_assimilateSubParameters (
 LLRP_tSCPUUtilizationThreshold * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_CPUUtilizationThreshold_encode (
  const LLRP_tSCPUUtilizationThreshold *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_CPUUtilizationThreshold_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdCPUUtilizationThreshold_CPUUtilizationThresholdMaxValue;

extern llrp_u8_t
LLRP_CPUUtilizationThreshold_getCPUUtilizationThresholdMaxValue (
  LLRP_tSCPUUtilizationThreshold *pThis);

extern LLRP_tResultCode
LLRP_CPUUtilizationThreshold_setCPUUtilizationThresholdMaxValue (
  LLRP_tSCPUUtilizationThreshold *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SJffsFileThreshold
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t JffsFileMaxValue;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdJffsFileThreshold;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdJffsFileThreshold[];

extern LLRP_tSJffsFileThreshold *
LLRP_JffsFileThreshold_construct (void);

extern void
LLRP_JffsFileThreshold_destruct (
 LLRP_tSJffsFileThreshold * pThis);

extern void
LLRP_JffsFileThreshold_decodeFields (
 LLRP_tSJffsFileThreshold * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_JffsFileThreshold_assimilateSubParameters (
 LLRP_tSJffsFileThreshold * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_JffsFileThreshold_encode (
  const LLRP_tSJffsFileThreshold *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_JffsFileThreshold_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdJffsFileThreshold_JffsFileMaxValue;

extern llrp_u8_t
LLRP_JffsFileThreshold_getJffsFileMaxValue (
  LLRP_tSJffsFileThreshold *pThis);

extern LLRP_tResultCode
LLRP_JffsFileThreshold_setJffsFileMaxValue (
  LLRP_tSJffsFileThreshold *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SLightningBoxThreshold
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t LightningBoxFlag;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdLightningBoxThreshold;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdLightningBoxThreshold[];

extern LLRP_tSLightningBoxThreshold *
LLRP_LightningBoxThreshold_construct (void);

extern void
LLRP_LightningBoxThreshold_destruct (
 LLRP_tSLightningBoxThreshold * pThis);

extern void
LLRP_LightningBoxThreshold_decodeFields (
 LLRP_tSLightningBoxThreshold * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_LightningBoxThreshold_assimilateSubParameters (
 LLRP_tSLightningBoxThreshold * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_LightningBoxThreshold_encode (
  const LLRP_tSLightningBoxThreshold *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_LightningBoxThreshold_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdLightningBoxThreshold_LightningBoxFlag;

extern llrp_u8_t
LLRP_LightningBoxThreshold_getLightningBoxFlag (
  LLRP_tSLightningBoxThreshold *pThis);

extern LLRP_tResultCode
LLRP_LightningBoxThreshold_setLightningBoxFlag (
  LLRP_tSLightningBoxThreshold *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SPowerDifferenceThreshold
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t PowerDifferenceThreshold;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdPowerDifferenceThreshold;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdPowerDifferenceThreshold[];

extern LLRP_tSPowerDifferenceThreshold *
LLRP_PowerDifferenceThreshold_construct (void);

extern void
LLRP_PowerDifferenceThreshold_destruct (
 LLRP_tSPowerDifferenceThreshold * pThis);

extern void
LLRP_PowerDifferenceThreshold_decodeFields (
 LLRP_tSPowerDifferenceThreshold * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_PowerDifferenceThreshold_assimilateSubParameters (
 LLRP_tSPowerDifferenceThreshold * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_PowerDifferenceThreshold_encode (
  const LLRP_tSPowerDifferenceThreshold *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_PowerDifferenceThreshold_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdPowerDifferenceThreshold_PowerDifferenceThreshold;

extern llrp_u8_t
LLRP_PowerDifferenceThreshold_getPowerDifferenceThreshold (
  LLRP_tSPowerDifferenceThreshold *pThis);

extern LLRP_tResultCode
LLRP_PowerDifferenceThreshold_setPowerDifferenceThreshold (
  LLRP_tSPowerDifferenceThreshold *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SRecvFilter
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t RecvFilter;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdRecvFilter;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdRecvFilter[];

extern LLRP_tSRecvFilter *
LLRP_RecvFilter_construct (void);

extern void
LLRP_RecvFilter_destruct (
 LLRP_tSRecvFilter * pThis);

extern void
LLRP_RecvFilter_decodeFields (
 LLRP_tSRecvFilter * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_RecvFilter_assimilateSubParameters (
 LLRP_tSRecvFilter * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_RecvFilter_encode (
  const LLRP_tSRecvFilter *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_RecvFilter_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdRecvFilter_RecvFilter;

extern llrp_u8_t
LLRP_RecvFilter_getRecvFilter (
  LLRP_tSRecvFilter *pThis);

extern LLRP_tResultCode
LLRP_RecvFilter_setRecvFilter (
  LLRP_tSRecvFilter *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SLaneNum
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t Ant1st;

    llrp_u8_t Ant2nd;

    llrp_u8_t Ant3rd;

    llrp_u8_t Ant4th;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdLaneNum;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdLaneNum[];

extern LLRP_tSLaneNum *
LLRP_LaneNum_construct (void);

extern void
LLRP_LaneNum_destruct (
 LLRP_tSLaneNum * pThis);

extern void
LLRP_LaneNum_decodeFields (
 LLRP_tSLaneNum * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_LaneNum_assimilateSubParameters (
 LLRP_tSLaneNum * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_LaneNum_encode (
  const LLRP_tSLaneNum *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_LaneNum_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdLaneNum_Ant1st;

extern llrp_u8_t
LLRP_LaneNum_getAnt1st (
  LLRP_tSLaneNum *pThis);

extern LLRP_tResultCode
LLRP_LaneNum_setAnt1st (
  LLRP_tSLaneNum *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdLaneNum_Ant2nd;

extern llrp_u8_t
LLRP_LaneNum_getAnt2nd (
  LLRP_tSLaneNum *pThis);

extern LLRP_tResultCode
LLRP_LaneNum_setAnt2nd (
  LLRP_tSLaneNum *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdLaneNum_Ant3rd;

extern llrp_u8_t
LLRP_LaneNum_getAnt3rd (
  LLRP_tSLaneNum *pThis);

extern LLRP_tResultCode
LLRP_LaneNum_setAnt3rd (
  LLRP_tSLaneNum *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdLaneNum_Ant4th;

extern llrp_u8_t
LLRP_LaneNum_getAnt4th (
  LLRP_tSLaneNum *pThis);

extern LLRP_tResultCode
LLRP_LaneNum_setAnt4th (
  LLRP_tSLaneNum *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_STransmitPower
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t TransmitPower6B;

    llrp_u16_t TransmitPower6C;

    llrp_u16_t TransmitPowerGB;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdTransmitPower;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdTransmitPower[];

extern LLRP_tSTransmitPower *
LLRP_TransmitPower_construct (void);

extern void
LLRP_TransmitPower_destruct (
 LLRP_tSTransmitPower * pThis);

extern void
LLRP_TransmitPower_decodeFields (
 LLRP_tSTransmitPower * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_TransmitPower_assimilateSubParameters (
 LLRP_tSTransmitPower * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_TransmitPower_encode (
  const LLRP_tSTransmitPower *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_TransmitPower_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdTransmitPower_TransmitPower6B;

extern llrp_u16_t
LLRP_TransmitPower_getTransmitPower6B (
  LLRP_tSTransmitPower *pThis);

extern LLRP_tResultCode
LLRP_TransmitPower_setTransmitPower6B (
  LLRP_tSTransmitPower *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdTransmitPower_TransmitPower6C;

extern llrp_u16_t
LLRP_TransmitPower_getTransmitPower6C (
  LLRP_tSTransmitPower *pThis);

extern LLRP_tResultCode
LLRP_TransmitPower_setTransmitPower6C (
  LLRP_tSTransmitPower *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdTransmitPower_TransmitPowerGB;

extern llrp_u16_t
LLRP_TransmitPower_getTransmitPowerGB (
  LLRP_tSTransmitPower *pThis);

extern LLRP_tResultCode
LLRP_TransmitPower_setTransmitPowerGB (
  LLRP_tSTransmitPower *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_SLBT
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t LBTSettings;

    llrp_u16_t DattValue;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdLBT;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdLBT[];

extern LLRP_tSLBT *
LLRP_LBT_construct (void);

extern void
LLRP_LBT_destruct (
 LLRP_tSLBT * pThis);

extern void
LLRP_LBT_decodeFields (
 LLRP_tSLBT * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_LBT_assimilateSubParameters (
 LLRP_tSLBT * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_LBT_encode (
  const LLRP_tSLBT *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_LBT_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdLBT_LBTSettings;

extern llrp_u8_t
LLRP_LBT_getLBTSettings (
  LLRP_tSLBT *pThis);

extern LLRP_tResultCode
LLRP_LBT_setLBTSettings (
  LLRP_tSLBT *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdLBT_DattValue;

extern llrp_u16_t
LLRP_LBT_getDattValue (
  LLRP_tSLBT *pThis);

extern LLRP_tResultCode
LLRP_LBT_setDattValue (
  LLRP_tSLBT *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_SFrequencyConfiguration
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t FreqSettings;

    llrp_u16_t HopTableID;

    llrp_u16_t ChannelIndex;

  
    LLRP_tSFreqHopConfig * pFreqHopConfig;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdFrequencyConfiguration;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdFrequencyConfiguration[];

extern LLRP_tSFrequencyConfiguration *
LLRP_FrequencyConfiguration_construct (void);

extern void
LLRP_FrequencyConfiguration_destruct (
 LLRP_tSFrequencyConfiguration * pThis);

extern void
LLRP_FrequencyConfiguration_decodeFields (
 LLRP_tSFrequencyConfiguration * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_FrequencyConfiguration_assimilateSubParameters (
 LLRP_tSFrequencyConfiguration * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_FrequencyConfiguration_encode (
  const LLRP_tSFrequencyConfiguration *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_FrequencyConfiguration_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdFrequencyConfiguration_FreqSettings;

extern llrp_u8_t
LLRP_FrequencyConfiguration_getFreqSettings (
  LLRP_tSFrequencyConfiguration *pThis);

extern LLRP_tResultCode
LLRP_FrequencyConfiguration_setFreqSettings (
  LLRP_tSFrequencyConfiguration *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdFrequencyConfiguration_HopTableID;

extern llrp_u16_t
LLRP_FrequencyConfiguration_getHopTableID (
  LLRP_tSFrequencyConfiguration *pThis);

extern LLRP_tResultCode
LLRP_FrequencyConfiguration_setHopTableID (
  LLRP_tSFrequencyConfiguration *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdFrequencyConfiguration_ChannelIndex;

extern llrp_u16_t
LLRP_FrequencyConfiguration_getChannelIndex (
  LLRP_tSFrequencyConfiguration *pThis);

extern LLRP_tResultCode
LLRP_FrequencyConfiguration_setChannelIndex (
  LLRP_tSFrequencyConfiguration *pThis,
  llrp_u16_t Value);

  
extern LLRP_tSFreqHopConfig *
LLRP_FrequencyConfiguration_getFreqHopConfig (
  LLRP_tSFrequencyConfiguration *pThis);

extern LLRP_tResultCode
LLRP_FrequencyConfiguration_setFreqHopConfig (
  LLRP_tSFrequencyConfiguration *pThis,
  LLRP_tSFreqHopConfig *pValue);



  
struct LLRP_SFreqHopConfig
{
    LLRP_tSParameter hdr;
  
    LLRP_tEFreqHopType eFreqHopType;

    llrp_u16_t HopTimer;

  
    LLRP_tSFreqChannel * listFreqChannel;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdFreqHopConfig;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdFreqHopConfig[];

extern LLRP_tSFreqHopConfig *
LLRP_FreqHopConfig_construct (void);

extern void
LLRP_FreqHopConfig_destruct (
 LLRP_tSFreqHopConfig * pThis);

extern void
LLRP_FreqHopConfig_decodeFields (
 LLRP_tSFreqHopConfig * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_FreqHopConfig_assimilateSubParameters (
 LLRP_tSFreqHopConfig * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_FreqHopConfig_encode (
  const LLRP_tSFreqHopConfig *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_FreqHopConfig_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdFreqHopConfig_FreqHopType;

extern LLRP_tEFreqHopType
LLRP_FreqHopConfig_getFreqHopType (
  LLRP_tSFreqHopConfig *pThis);

extern LLRP_tResultCode
LLRP_FreqHopConfig_setFreqHopType (
  LLRP_tSFreqHopConfig *pThis,
  LLRP_tEFreqHopType Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdFreqHopConfig_HopTimer;

extern llrp_u16_t
LLRP_FreqHopConfig_getHopTimer (
  LLRP_tSFreqHopConfig *pThis);

extern LLRP_tResultCode
LLRP_FreqHopConfig_setHopTimer (
  LLRP_tSFreqHopConfig *pThis,
  llrp_u16_t Value);

  
extern LLRP_tSFreqChannel *
LLRP_FreqHopConfig_beginFreqChannel (
  LLRP_tSFreqHopConfig *pThis);

extern LLRP_tSFreqChannel *
LLRP_FreqHopConfig_nextFreqChannel (
  LLRP_tSFreqChannel *pCurrent);

extern void
LLRP_FreqHopConfig_clearFreqChannel (
  LLRP_tSFreqHopConfig *pThis);

extern LLRP_tResultCode
LLRP_FreqHopConfig_addFreqChannel (
  LLRP_tSFreqHopConfig *pThis,
  LLRP_tSFreqChannel *pValue);




  
struct LLRP_SFreqChannel
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t FreqChannel;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdFreqChannel;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdFreqChannel[];

extern LLRP_tSFreqChannel *
LLRP_FreqChannel_construct (void);

extern void
LLRP_FreqChannel_destruct (
 LLRP_tSFreqChannel * pThis);

extern void
LLRP_FreqChannel_decodeFields (
 LLRP_tSFreqChannel * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_FreqChannel_assimilateSubParameters (
 LLRP_tSFreqChannel * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_FreqChannel_encode (
  const LLRP_tSFreqChannel *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_FreqChannel_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdFreqChannel_FreqChannel;

extern llrp_u16_t
LLRP_FreqChannel_getFreqChannel (
  LLRP_tSFreqChannel *pThis);

extern LLRP_tResultCode
LLRP_FreqChannel_setFreqChannel (
  LLRP_tSFreqChannel *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_SAlarmMask
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t AlarmMask;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdAlarmMask;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdAlarmMask[];

extern LLRP_tSAlarmMask *
LLRP_AlarmMask_construct (void);

extern void
LLRP_AlarmMask_destruct (
 LLRP_tSAlarmMask * pThis);

extern void
LLRP_AlarmMask_decodeFields (
 LLRP_tSAlarmMask * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_AlarmMask_assimilateSubParameters (
 LLRP_tSAlarmMask * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_AlarmMask_encode (
  const LLRP_tSAlarmMask *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_AlarmMask_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdAlarmMask_AlarmMask;

extern llrp_u8_t
LLRP_AlarmMask_getAlarmMask (
  LLRP_tSAlarmMask *pThis);

extern LLRP_tResultCode
LLRP_AlarmMask_setAlarmMask (
  LLRP_tSAlarmMask *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SModuleDepth
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t DepthIndex;

    llrp_u16_t DepthIndexFor6B;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdModuleDepth;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdModuleDepth[];

extern LLRP_tSModuleDepth *
LLRP_ModuleDepth_construct (void);

extern void
LLRP_ModuleDepth_destruct (
 LLRP_tSModuleDepth * pThis);

extern void
LLRP_ModuleDepth_decodeFields (
 LLRP_tSModuleDepth * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_ModuleDepth_assimilateSubParameters (
 LLRP_tSModuleDepth * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_ModuleDepth_encode (
  const LLRP_tSModuleDepth *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_ModuleDepth_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdModuleDepth_DepthIndex;

extern llrp_u16_t
LLRP_ModuleDepth_getDepthIndex (
  LLRP_tSModuleDepth *pThis);

extern LLRP_tResultCode
LLRP_ModuleDepth_setDepthIndex (
  LLRP_tSModuleDepth *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdModuleDepth_DepthIndexFor6B;

extern llrp_u16_t
LLRP_ModuleDepth_getDepthIndexFor6B (
  LLRP_tSModuleDepth *pThis);

extern LLRP_tResultCode
LLRP_ModuleDepth_setDepthIndexFor6B (
  LLRP_tSModuleDepth *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_SIQConfig
{
    LLRP_tSParameter hdr;
  
    llrp_u1_t IQConfig;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdIQConfig;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdIQConfig[];

extern LLRP_tSIQConfig *
LLRP_IQConfig_construct (void);

extern void
LLRP_IQConfig_destruct (
 LLRP_tSIQConfig * pThis);

extern void
LLRP_IQConfig_decodeFields (
 LLRP_tSIQConfig * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_IQConfig_assimilateSubParameters (
 LLRP_tSIQConfig * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_IQConfig_encode (
  const LLRP_tSIQConfig *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_IQConfig_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdIQConfig_IQConfig;

extern llrp_u1_t
LLRP_IQConfig_getIQConfig (
  LLRP_tSIQConfig *pThis);

extern LLRP_tResultCode
LLRP_IQConfig_setIQConfig (
  LLRP_tSIQConfig *pThis,
  llrp_u1_t Value);

  


  
struct LLRP_SLocationConfiguration
{
    LLRP_tSParameter hdr;
  
    LLRP_tELocationType eLocationType;

  
    LLRP_tSGPSLocation * pGPSLocation;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdLocationConfiguration;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdLocationConfiguration[];

extern LLRP_tSLocationConfiguration *
LLRP_LocationConfiguration_construct (void);

extern void
LLRP_LocationConfiguration_destruct (
 LLRP_tSLocationConfiguration * pThis);

extern void
LLRP_LocationConfiguration_decodeFields (
 LLRP_tSLocationConfiguration * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_LocationConfiguration_assimilateSubParameters (
 LLRP_tSLocationConfiguration * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_LocationConfiguration_encode (
  const LLRP_tSLocationConfiguration *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_LocationConfiguration_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdLocationConfiguration_LocationType;

extern LLRP_tELocationType
LLRP_LocationConfiguration_getLocationType (
  LLRP_tSLocationConfiguration *pThis);

extern LLRP_tResultCode
LLRP_LocationConfiguration_setLocationType (
  LLRP_tSLocationConfiguration *pThis,
  LLRP_tELocationType Value);

  
extern LLRP_tSGPSLocation *
LLRP_LocationConfiguration_getGPSLocation (
  LLRP_tSLocationConfiguration *pThis);

extern LLRP_tResultCode
LLRP_LocationConfiguration_setGPSLocation (
  LLRP_tSLocationConfiguration *pThis,
  LLRP_tSGPSLocation *pValue);



  
struct LLRP_SGPSLocation
{
    LLRP_tSParameter hdr;
  
    llrp_u1_t LatitudeType;

    llrp_u1_t LongitudeType;

    llrp_u8_t LatitudeDegree;

    llrp_u8_t LongitudeDegree;

    llrp_u32_t LatitudeMinute;

    llrp_u32_t LongitudeMinute;

    llrp_s32_t Altitude;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdGPSLocation;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdGPSLocation[];

extern LLRP_tSGPSLocation *
LLRP_GPSLocation_construct (void);

extern void
LLRP_GPSLocation_destruct (
 LLRP_tSGPSLocation * pThis);

extern void
LLRP_GPSLocation_decodeFields (
 LLRP_tSGPSLocation * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_GPSLocation_assimilateSubParameters (
 LLRP_tSGPSLocation * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_GPSLocation_encode (
  const LLRP_tSGPSLocation *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_GPSLocation_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdGPSLocation_LatitudeType;

extern llrp_u1_t
LLRP_GPSLocation_getLatitudeType (
  LLRP_tSGPSLocation *pThis);

extern LLRP_tResultCode
LLRP_GPSLocation_setLatitudeType (
  LLRP_tSGPSLocation *pThis,
  llrp_u1_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdGPSLocation_LongitudeType;

extern llrp_u1_t
LLRP_GPSLocation_getLongitudeType (
  LLRP_tSGPSLocation *pThis);

extern LLRP_tResultCode
LLRP_GPSLocation_setLongitudeType (
  LLRP_tSGPSLocation *pThis,
  llrp_u1_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdGPSLocation_LatitudeDegree;

extern llrp_u8_t
LLRP_GPSLocation_getLatitudeDegree (
  LLRP_tSGPSLocation *pThis);

extern LLRP_tResultCode
LLRP_GPSLocation_setLatitudeDegree (
  LLRP_tSGPSLocation *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdGPSLocation_LongitudeDegree;

extern llrp_u8_t
LLRP_GPSLocation_getLongitudeDegree (
  LLRP_tSGPSLocation *pThis);

extern LLRP_tResultCode
LLRP_GPSLocation_setLongitudeDegree (
  LLRP_tSGPSLocation *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdGPSLocation_LatitudeMinute;

extern llrp_u32_t
LLRP_GPSLocation_getLatitudeMinute (
  LLRP_tSGPSLocation *pThis);

extern LLRP_tResultCode
LLRP_GPSLocation_setLatitudeMinute (
  LLRP_tSGPSLocation *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdGPSLocation_LongitudeMinute;

extern llrp_u32_t
LLRP_GPSLocation_getLongitudeMinute (
  LLRP_tSGPSLocation *pThis);

extern LLRP_tResultCode
LLRP_GPSLocation_setLongitudeMinute (
  LLRP_tSGPSLocation *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdGPSLocation_Altitude;

extern llrp_s32_t
LLRP_GPSLocation_getAltitude (
  LLRP_tSGPSLocation *pThis);

extern LLRP_tResultCode
LLRP_GPSLocation_setAltitude (
  LLRP_tSGPSLocation *pThis,
  llrp_s32_t Value);

  


  
struct LLRP_SAntSwitchDelayCfg
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t TurnOnDelay;

    llrp_u16_t DelayTime;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdAntSwitchDelayCfg;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdAntSwitchDelayCfg[];

extern LLRP_tSAntSwitchDelayCfg *
LLRP_AntSwitchDelayCfg_construct (void);

extern void
LLRP_AntSwitchDelayCfg_destruct (
 LLRP_tSAntSwitchDelayCfg * pThis);

extern void
LLRP_AntSwitchDelayCfg_decodeFields (
 LLRP_tSAntSwitchDelayCfg * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_AntSwitchDelayCfg_assimilateSubParameters (
 LLRP_tSAntSwitchDelayCfg * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_AntSwitchDelayCfg_encode (
  const LLRP_tSAntSwitchDelayCfg *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_AntSwitchDelayCfg_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdAntSwitchDelayCfg_TurnOnDelay;

extern llrp_u8_t
LLRP_AntSwitchDelayCfg_getTurnOnDelay (
  LLRP_tSAntSwitchDelayCfg *pThis);

extern LLRP_tResultCode
LLRP_AntSwitchDelayCfg_setTurnOnDelay (
  LLRP_tSAntSwitchDelayCfg *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdAntSwitchDelayCfg_DelayTime;

extern llrp_u16_t
LLRP_AntSwitchDelayCfg_getDelayTime (
  LLRP_tSAntSwitchDelayCfg *pThis);

extern LLRP_tResultCode
LLRP_AntSwitchDelayCfg_setDelayTime (
  LLRP_tSAntSwitchDelayCfg *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_STagReportFilter
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t TurnOnOPFilter;

    llrp_u8_t TurnOnRFFilter;

    llrp_u8_t OPKeepaliveTime;

    llrp_u8_t RFKeepaliveTime;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdTagReportFilter;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdTagReportFilter[];

extern LLRP_tSTagReportFilter *
LLRP_TagReportFilter_construct (void);

extern void
LLRP_TagReportFilter_destruct (
 LLRP_tSTagReportFilter * pThis);

extern void
LLRP_TagReportFilter_decodeFields (
 LLRP_tSTagReportFilter * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_TagReportFilter_assimilateSubParameters (
 LLRP_tSTagReportFilter * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_TagReportFilter_encode (
  const LLRP_tSTagReportFilter *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_TagReportFilter_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdTagReportFilter_TurnOnOPFilter;

extern llrp_u8_t
LLRP_TagReportFilter_getTurnOnOPFilter (
  LLRP_tSTagReportFilter *pThis);

extern LLRP_tResultCode
LLRP_TagReportFilter_setTurnOnOPFilter (
  LLRP_tSTagReportFilter *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdTagReportFilter_TurnOnRFFilter;

extern llrp_u8_t
LLRP_TagReportFilter_getTurnOnRFFilter (
  LLRP_tSTagReportFilter *pThis);

extern LLRP_tResultCode
LLRP_TagReportFilter_setTurnOnRFFilter (
  LLRP_tSTagReportFilter *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdTagReportFilter_OPKeepaliveTime;

extern llrp_u8_t
LLRP_TagReportFilter_getOPKeepaliveTime (
  LLRP_tSTagReportFilter *pThis);

extern LLRP_tResultCode
LLRP_TagReportFilter_setOPKeepaliveTime (
  LLRP_tSTagReportFilter *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdTagReportFilter_RFKeepaliveTime;

extern llrp_u8_t
LLRP_TagReportFilter_getRFKeepaliveTime (
  LLRP_tSTagReportFilter *pThis);

extern LLRP_tResultCode
LLRP_TagReportFilter_setRFKeepaliveTime (
  LLRP_tSTagReportFilter *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SAntCoopCfg
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t TurnOnAntCoop;

  
    LLRP_tSAntCoopUDPCfg * pAntCoopUDPCfg;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdAntCoopCfg;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdAntCoopCfg[];

extern LLRP_tSAntCoopCfg *
LLRP_AntCoopCfg_construct (void);

extern void
LLRP_AntCoopCfg_destruct (
 LLRP_tSAntCoopCfg * pThis);

extern void
LLRP_AntCoopCfg_decodeFields (
 LLRP_tSAntCoopCfg * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_AntCoopCfg_assimilateSubParameters (
 LLRP_tSAntCoopCfg * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_AntCoopCfg_encode (
  const LLRP_tSAntCoopCfg *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_AntCoopCfg_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdAntCoopCfg_TurnOnAntCoop;

extern llrp_u8_t
LLRP_AntCoopCfg_getTurnOnAntCoop (
  LLRP_tSAntCoopCfg *pThis);

extern LLRP_tResultCode
LLRP_AntCoopCfg_setTurnOnAntCoop (
  LLRP_tSAntCoopCfg *pThis,
  llrp_u8_t Value);

  
extern LLRP_tSAntCoopUDPCfg *
LLRP_AntCoopCfg_getAntCoopUDPCfg (
  LLRP_tSAntCoopCfg *pThis);

extern LLRP_tResultCode
LLRP_AntCoopCfg_setAntCoopUDPCfg (
  LLRP_tSAntCoopCfg *pThis,
  LLRP_tSAntCoopUDPCfg *pValue);



  
struct LLRP_SAntCoopUDPCfg
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t AntNum;

  
    LLRP_tSPerAntUDPCfg * listPerAntUDPCfg;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdAntCoopUDPCfg;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdAntCoopUDPCfg[];

extern LLRP_tSAntCoopUDPCfg *
LLRP_AntCoopUDPCfg_construct (void);

extern void
LLRP_AntCoopUDPCfg_destruct (
 LLRP_tSAntCoopUDPCfg * pThis);

extern void
LLRP_AntCoopUDPCfg_decodeFields (
 LLRP_tSAntCoopUDPCfg * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_AntCoopUDPCfg_assimilateSubParameters (
 LLRP_tSAntCoopUDPCfg * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_AntCoopUDPCfg_encode (
  const LLRP_tSAntCoopUDPCfg *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_AntCoopUDPCfg_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdAntCoopUDPCfg_AntNum;

extern llrp_u8_t
LLRP_AntCoopUDPCfg_getAntNum (
  LLRP_tSAntCoopUDPCfg *pThis);

extern LLRP_tResultCode
LLRP_AntCoopUDPCfg_setAntNum (
  LLRP_tSAntCoopUDPCfg *pThis,
  llrp_u8_t Value);

  
extern LLRP_tSPerAntUDPCfg *
LLRP_AntCoopUDPCfg_beginPerAntUDPCfg (
  LLRP_tSAntCoopUDPCfg *pThis);

extern LLRP_tSPerAntUDPCfg *
LLRP_AntCoopUDPCfg_nextPerAntUDPCfg (
  LLRP_tSPerAntUDPCfg *pCurrent);

extern void
LLRP_AntCoopUDPCfg_clearPerAntUDPCfg (
  LLRP_tSAntCoopUDPCfg *pThis);

extern LLRP_tResultCode
LLRP_AntCoopUDPCfg_addPerAntUDPCfg (
  LLRP_tSAntCoopUDPCfg *pThis,
  LLRP_tSPerAntUDPCfg *pValue);




  
struct LLRP_SPerAntUDPCfg
{
    LLRP_tSParameter hdr;
  
    llrp_u32_t ReaderIP;

    llrp_u8_t AntIndex;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdPerAntUDPCfg;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdPerAntUDPCfg[];

extern LLRP_tSPerAntUDPCfg *
LLRP_PerAntUDPCfg_construct (void);

extern void
LLRP_PerAntUDPCfg_destruct (
 LLRP_tSPerAntUDPCfg * pThis);

extern void
LLRP_PerAntUDPCfg_decodeFields (
 LLRP_tSPerAntUDPCfg * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_PerAntUDPCfg_assimilateSubParameters (
 LLRP_tSPerAntUDPCfg * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_PerAntUDPCfg_encode (
  const LLRP_tSPerAntUDPCfg *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_PerAntUDPCfg_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdPerAntUDPCfg_ReaderIP;

extern llrp_u32_t
LLRP_PerAntUDPCfg_getReaderIP (
  LLRP_tSPerAntUDPCfg *pThis);

extern LLRP_tResultCode
LLRP_PerAntUDPCfg_setReaderIP (
  LLRP_tSPerAntUDPCfg *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdPerAntUDPCfg_AntIndex;

extern llrp_u8_t
LLRP_PerAntUDPCfg_getAntIndex (
  LLRP_tSPerAntUDPCfg *pThis);

extern LLRP_tResultCode
LLRP_PerAntUDPCfg_setAntIndex (
  LLRP_tSPerAntUDPCfg *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SRSSISortCfg
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t TurnOnSort;

    llrp_u16_t OTTime;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdRSSISortCfg;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdRSSISortCfg[];

extern LLRP_tSRSSISortCfg *
LLRP_RSSISortCfg_construct (void);

extern void
LLRP_RSSISortCfg_destruct (
 LLRP_tSRSSISortCfg * pThis);

extern void
LLRP_RSSISortCfg_decodeFields (
 LLRP_tSRSSISortCfg * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_RSSISortCfg_assimilateSubParameters (
 LLRP_tSRSSISortCfg * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_RSSISortCfg_encode (
  const LLRP_tSRSSISortCfg *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_RSSISortCfg_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdRSSISortCfg_TurnOnSort;

extern llrp_u8_t
LLRP_RSSISortCfg_getTurnOnSort (
  LLRP_tSRSSISortCfg *pThis);

extern LLRP_tResultCode
LLRP_RSSISortCfg_setTurnOnSort (
  LLRP_tSRSSISortCfg *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdRSSISortCfg_OTTime;

extern llrp_u16_t
LLRP_RSSISortCfg_getOTTime (
  LLRP_tSRSSISortCfg *pThis);

extern LLRP_tResultCode
LLRP_RSSISortCfg_setOTTime (
  LLRP_tSRSSISortCfg *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_SLeakCompensation
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t TurnOnLC;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdLeakCompensation;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdLeakCompensation[];

extern LLRP_tSLeakCompensation *
LLRP_LeakCompensation_construct (void);

extern void
LLRP_LeakCompensation_destruct (
 LLRP_tSLeakCompensation * pThis);

extern void
LLRP_LeakCompensation_decodeFields (
 LLRP_tSLeakCompensation * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_LeakCompensation_assimilateSubParameters (
 LLRP_tSLeakCompensation * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_LeakCompensation_encode (
  const LLRP_tSLeakCompensation *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_LeakCompensation_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdLeakCompensation_TurnOnLC;

extern llrp_u8_t
LLRP_LeakCompensation_getTurnOnLC (
  LLRP_tSLeakCompensation *pThis);

extern LLRP_tResultCode
LLRP_LeakCompensation_setTurnOnLC (
  LLRP_tSLeakCompensation *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SRecvDATT
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t RecvDATT;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdRecvDATT;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdRecvDATT[];

extern LLRP_tSRecvDATT *
LLRP_RecvDATT_construct (void);

extern void
LLRP_RecvDATT_destruct (
 LLRP_tSRecvDATT * pThis);

extern void
LLRP_RecvDATT_decodeFields (
 LLRP_tSRecvDATT * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_RecvDATT_assimilateSubParameters (
 LLRP_tSRecvDATT * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_RecvDATT_encode (
  const LLRP_tSRecvDATT *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_RecvDATT_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdRecvDATT_RecvDATT;

extern llrp_u8_t
LLRP_RecvDATT_getRecvDATT (
  LLRP_tSRecvDATT *pThis);

extern LLRP_tResultCode
LLRP_RecvDATT_setRecvDATT (
  LLRP_tSRecvDATT *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SAlarmThreshodCfg
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t TemperatureMaxValue;

    llrp_s8_t TemperatureMinValue;

    llrp_u8_t MemoryMaxValue;

    llrp_u8_t CPUMaxValue;

    llrp_u8_t JffsFileMaxValue;

    llrp_u8_t ThunderFlag;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdAlarmThreshodCfg;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdAlarmThreshodCfg[];

extern LLRP_tSAlarmThreshodCfg *
LLRP_AlarmThreshodCfg_construct (void);

extern void
LLRP_AlarmThreshodCfg_destruct (
 LLRP_tSAlarmThreshodCfg * pThis);

extern void
LLRP_AlarmThreshodCfg_decodeFields (
 LLRP_tSAlarmThreshodCfg * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_AlarmThreshodCfg_assimilateSubParameters (
 LLRP_tSAlarmThreshodCfg * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_AlarmThreshodCfg_encode (
  const LLRP_tSAlarmThreshodCfg *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_AlarmThreshodCfg_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdAlarmThreshodCfg_TemperatureMaxValue;

extern llrp_u8_t
LLRP_AlarmThreshodCfg_getTemperatureMaxValue (
  LLRP_tSAlarmThreshodCfg *pThis);

extern LLRP_tResultCode
LLRP_AlarmThreshodCfg_setTemperatureMaxValue (
  LLRP_tSAlarmThreshodCfg *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdAlarmThreshodCfg_TemperatureMinValue;

extern llrp_s8_t
LLRP_AlarmThreshodCfg_getTemperatureMinValue (
  LLRP_tSAlarmThreshodCfg *pThis);

extern LLRP_tResultCode
LLRP_AlarmThreshodCfg_setTemperatureMinValue (
  LLRP_tSAlarmThreshodCfg *pThis,
  llrp_s8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdAlarmThreshodCfg_MemoryMaxValue;

extern llrp_u8_t
LLRP_AlarmThreshodCfg_getMemoryMaxValue (
  LLRP_tSAlarmThreshodCfg *pThis);

extern LLRP_tResultCode
LLRP_AlarmThreshodCfg_setMemoryMaxValue (
  LLRP_tSAlarmThreshodCfg *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdAlarmThreshodCfg_CPUMaxValue;

extern llrp_u8_t
LLRP_AlarmThreshodCfg_getCPUMaxValue (
  LLRP_tSAlarmThreshodCfg *pThis);

extern LLRP_tResultCode
LLRP_AlarmThreshodCfg_setCPUMaxValue (
  LLRP_tSAlarmThreshodCfg *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdAlarmThreshodCfg_JffsFileMaxValue;

extern llrp_u8_t
LLRP_AlarmThreshodCfg_getJffsFileMaxValue (
  LLRP_tSAlarmThreshodCfg *pThis);

extern LLRP_tResultCode
LLRP_AlarmThreshodCfg_setJffsFileMaxValue (
  LLRP_tSAlarmThreshodCfg *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdAlarmThreshodCfg_ThunderFlag;

extern llrp_u8_t
LLRP_AlarmThreshodCfg_getThunderFlag (
  LLRP_tSAlarmThreshodCfg *pThis);

extern LLRP_tResultCode
LLRP_AlarmThreshodCfg_setThunderFlag (
  LLRP_tSAlarmThreshodCfg *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SRUPCommunicationConfiguration
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t CommLinkMap;

  
    LLRP_tSReaderAddressConfiguration * pReaderAddressConfiguration;

    LLRP_tSCommLinkConfiguration * listCommLinkConfiguration;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdRUPCommunicationConfiguration;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdRUPCommunicationConfiguration[];

extern LLRP_tSRUPCommunicationConfiguration *
LLRP_RUPCommunicationConfiguration_construct (void);

extern void
LLRP_RUPCommunicationConfiguration_destruct (
 LLRP_tSRUPCommunicationConfiguration * pThis);

extern void
LLRP_RUPCommunicationConfiguration_decodeFields (
 LLRP_tSRUPCommunicationConfiguration * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_RUPCommunicationConfiguration_assimilateSubParameters (
 LLRP_tSRUPCommunicationConfiguration * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_RUPCommunicationConfiguration_encode (
  const LLRP_tSRUPCommunicationConfiguration *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_RUPCommunicationConfiguration_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdRUPCommunicationConfiguration_CommLinkMap;

extern llrp_u16_t
LLRP_RUPCommunicationConfiguration_getCommLinkMap (
  LLRP_tSRUPCommunicationConfiguration *pThis);

extern LLRP_tResultCode
LLRP_RUPCommunicationConfiguration_setCommLinkMap (
  LLRP_tSRUPCommunicationConfiguration *pThis,
  llrp_u16_t Value);

  
extern LLRP_tSReaderAddressConfiguration *
LLRP_RUPCommunicationConfiguration_getReaderAddressConfiguration (
  LLRP_tSRUPCommunicationConfiguration *pThis);

extern LLRP_tResultCode
LLRP_RUPCommunicationConfiguration_setReaderAddressConfiguration (
  LLRP_tSRUPCommunicationConfiguration *pThis,
  LLRP_tSReaderAddressConfiguration *pValue);

extern LLRP_tSCommLinkConfiguration *
LLRP_RUPCommunicationConfiguration_beginCommLinkConfiguration (
  LLRP_tSRUPCommunicationConfiguration *pThis);

extern LLRP_tSCommLinkConfiguration *
LLRP_RUPCommunicationConfiguration_nextCommLinkConfiguration (
  LLRP_tSCommLinkConfiguration *pCurrent);

extern void
LLRP_RUPCommunicationConfiguration_clearCommLinkConfiguration (
  LLRP_tSRUPCommunicationConfiguration *pThis);

extern LLRP_tResultCode
LLRP_RUPCommunicationConfiguration_addCommLinkConfiguration (
  LLRP_tSRUPCommunicationConfiguration *pThis,
  LLRP_tSCommLinkConfiguration *pValue);




  
struct LLRP_SCommLinkConfiguration
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t LinkID;

    LLRP_tELinkPhyType eLinkPhyType;

  
    LLRP_tSEthernetConfiguration * pEthernetConfiguration;

    LLRP_tSSerialPort232Configuration * pSerialPort232Configuration;

    LLRP_tSSerialPort485Configuration * pSerialPort485Configuration;

    LLRP_tSGPRSConfiguration * pGPRSConfiguration;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdCommLinkConfiguration;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdCommLinkConfiguration[];

extern LLRP_tSCommLinkConfiguration *
LLRP_CommLinkConfiguration_construct (void);

extern void
LLRP_CommLinkConfiguration_destruct (
 LLRP_tSCommLinkConfiguration * pThis);

extern void
LLRP_CommLinkConfiguration_decodeFields (
 LLRP_tSCommLinkConfiguration * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_CommLinkConfiguration_assimilateSubParameters (
 LLRP_tSCommLinkConfiguration * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_CommLinkConfiguration_encode (
  const LLRP_tSCommLinkConfiguration *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_CommLinkConfiguration_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdCommLinkConfiguration_LinkID;

extern llrp_u8_t
LLRP_CommLinkConfiguration_getLinkID (
  LLRP_tSCommLinkConfiguration *pThis);

extern LLRP_tResultCode
LLRP_CommLinkConfiguration_setLinkID (
  LLRP_tSCommLinkConfiguration *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdCommLinkConfiguration_LinkPhyType;

extern LLRP_tELinkPhyType
LLRP_CommLinkConfiguration_getLinkPhyType (
  LLRP_tSCommLinkConfiguration *pThis);

extern LLRP_tResultCode
LLRP_CommLinkConfiguration_setLinkPhyType (
  LLRP_tSCommLinkConfiguration *pThis,
  LLRP_tELinkPhyType Value);

  
extern LLRP_tSEthernetConfiguration *
LLRP_CommLinkConfiguration_getEthernetConfiguration (
  LLRP_tSCommLinkConfiguration *pThis);

extern LLRP_tResultCode
LLRP_CommLinkConfiguration_setEthernetConfiguration (
  LLRP_tSCommLinkConfiguration *pThis,
  LLRP_tSEthernetConfiguration *pValue);

extern LLRP_tSSerialPort232Configuration *
LLRP_CommLinkConfiguration_getSerialPort232Configuration (
  LLRP_tSCommLinkConfiguration *pThis);

extern LLRP_tResultCode
LLRP_CommLinkConfiguration_setSerialPort232Configuration (
  LLRP_tSCommLinkConfiguration *pThis,
  LLRP_tSSerialPort232Configuration *pValue);

extern LLRP_tSSerialPort485Configuration *
LLRP_CommLinkConfiguration_getSerialPort485Configuration (
  LLRP_tSCommLinkConfiguration *pThis);

extern LLRP_tResultCode
LLRP_CommLinkConfiguration_setSerialPort485Configuration (
  LLRP_tSCommLinkConfiguration *pThis,
  LLRP_tSSerialPort485Configuration *pValue);

extern LLRP_tSGPRSConfiguration *
LLRP_CommLinkConfiguration_getGPRSConfiguration (
  LLRP_tSCommLinkConfiguration *pThis);

extern LLRP_tResultCode
LLRP_CommLinkConfiguration_setGPRSConfiguration (
  LLRP_tSCommLinkConfiguration *pThis,
  LLRP_tSGPRSConfiguration *pValue);



  
struct LLRP_SEthernetConfiguration
{
    LLRP_tSParameter hdr;
  
  
    LLRP_tSCommMode * pCommMode;

    LLRP_tSKeepaliveSpec * pKeepaliveSpec;

    LLRP_tSSaveReportSwitch * pSaveReportSwitch;

    LLRP_tSClientAddressConfiguration * pClientAddressConfiguration;

    LLRP_tSHostPortConfiguration * pHostPortConfiguration;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdEthernetConfiguration;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdEthernetConfiguration[];

extern LLRP_tSEthernetConfiguration *
LLRP_EthernetConfiguration_construct (void);

extern void
LLRP_EthernetConfiguration_destruct (
 LLRP_tSEthernetConfiguration * pThis);

extern void
LLRP_EthernetConfiguration_decodeFields (
 LLRP_tSEthernetConfiguration * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_EthernetConfiguration_assimilateSubParameters (
 LLRP_tSEthernetConfiguration * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_EthernetConfiguration_encode (
  const LLRP_tSEthernetConfiguration *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_EthernetConfiguration_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
  
extern LLRP_tSCommMode *
LLRP_EthernetConfiguration_getCommMode (
  LLRP_tSEthernetConfiguration *pThis);

extern LLRP_tResultCode
LLRP_EthernetConfiguration_setCommMode (
  LLRP_tSEthernetConfiguration *pThis,
  LLRP_tSCommMode *pValue);

extern LLRP_tSKeepaliveSpec *
LLRP_EthernetConfiguration_getKeepaliveSpec (
  LLRP_tSEthernetConfiguration *pThis);

extern LLRP_tResultCode
LLRP_EthernetConfiguration_setKeepaliveSpec (
  LLRP_tSEthernetConfiguration *pThis,
  LLRP_tSKeepaliveSpec *pValue);

extern LLRP_tSSaveReportSwitch *
LLRP_EthernetConfiguration_getSaveReportSwitch (
  LLRP_tSEthernetConfiguration *pThis);

extern LLRP_tResultCode
LLRP_EthernetConfiguration_setSaveReportSwitch (
  LLRP_tSEthernetConfiguration *pThis,
  LLRP_tSSaveReportSwitch *pValue);

extern LLRP_tSClientAddressConfiguration *
LLRP_EthernetConfiguration_getClientAddressConfiguration (
  LLRP_tSEthernetConfiguration *pThis);

extern LLRP_tResultCode
LLRP_EthernetConfiguration_setClientAddressConfiguration (
  LLRP_tSEthernetConfiguration *pThis,
  LLRP_tSClientAddressConfiguration *pValue);

extern LLRP_tSHostPortConfiguration *
LLRP_EthernetConfiguration_getHostPortConfiguration (
  LLRP_tSEthernetConfiguration *pThis);

extern LLRP_tResultCode
LLRP_EthernetConfiguration_setHostPortConfiguration (
  LLRP_tSEthernetConfiguration *pThis,
  LLRP_tSHostPortConfiguration *pValue);



  
struct LLRP_SSerialPort232Configuration
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t SerialPortIndex;

    llrp_u16_t SerialAttributeIndex;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdSerialPort232Configuration;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSerialPort232Configuration[];

extern LLRP_tSSerialPort232Configuration *
LLRP_SerialPort232Configuration_construct (void);

extern void
LLRP_SerialPort232Configuration_destruct (
 LLRP_tSSerialPort232Configuration * pThis);

extern void
LLRP_SerialPort232Configuration_decodeFields (
 LLRP_tSSerialPort232Configuration * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SerialPort232Configuration_assimilateSubParameters (
 LLRP_tSSerialPort232Configuration * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SerialPort232Configuration_encode (
  const LLRP_tSSerialPort232Configuration *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_SerialPort232Configuration_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdSerialPort232Configuration_SerialPortIndex;

extern llrp_u16_t
LLRP_SerialPort232Configuration_getSerialPortIndex (
  LLRP_tSSerialPort232Configuration *pThis);

extern LLRP_tResultCode
LLRP_SerialPort232Configuration_setSerialPortIndex (
  LLRP_tSSerialPort232Configuration *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSerialPort232Configuration_SerialAttributeIndex;

extern llrp_u16_t
LLRP_SerialPort232Configuration_getSerialAttributeIndex (
  LLRP_tSSerialPort232Configuration *pThis);

extern LLRP_tResultCode
LLRP_SerialPort232Configuration_setSerialAttributeIndex (
  LLRP_tSSerialPort232Configuration *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_SSerialPort485Configuration
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t SerialPortIndex;

    llrp_u16_t SerialAttributeIndex;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdSerialPort485Configuration;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSerialPort485Configuration[];

extern LLRP_tSSerialPort485Configuration *
LLRP_SerialPort485Configuration_construct (void);

extern void
LLRP_SerialPort485Configuration_destruct (
 LLRP_tSSerialPort485Configuration * pThis);

extern void
LLRP_SerialPort485Configuration_decodeFields (
 LLRP_tSSerialPort485Configuration * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SerialPort485Configuration_assimilateSubParameters (
 LLRP_tSSerialPort485Configuration * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SerialPort485Configuration_encode (
  const LLRP_tSSerialPort485Configuration *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_SerialPort485Configuration_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdSerialPort485Configuration_SerialPortIndex;

extern llrp_u16_t
LLRP_SerialPort485Configuration_getSerialPortIndex (
  LLRP_tSSerialPort485Configuration *pThis);

extern LLRP_tResultCode
LLRP_SerialPort485Configuration_setSerialPortIndex (
  LLRP_tSSerialPort485Configuration *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSerialPort485Configuration_SerialAttributeIndex;

extern llrp_u16_t
LLRP_SerialPort485Configuration_getSerialAttributeIndex (
  LLRP_tSSerialPort485Configuration *pThis);

extern LLRP_tResultCode
LLRP_SerialPort485Configuration_setSerialAttributeIndex (
  LLRP_tSSerialPort485Configuration *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_SGPRSConfiguration
{
    LLRP_tSParameter hdr;
  
    llrp_utf8v_t APNConfig;

  
    LLRP_tSDialUser * pDialUser;

    LLRP_tSDialPass * pDialPass;

    LLRP_tSClientAddressConfiguration * pClientAddressConfiguration;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdGPRSConfiguration;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdGPRSConfiguration[];

extern LLRP_tSGPRSConfiguration *
LLRP_GPRSConfiguration_construct (void);

extern void
LLRP_GPRSConfiguration_destruct (
 LLRP_tSGPRSConfiguration * pThis);

extern void
LLRP_GPRSConfiguration_decodeFields (
 LLRP_tSGPRSConfiguration * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_GPRSConfiguration_assimilateSubParameters (
 LLRP_tSGPRSConfiguration * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_GPRSConfiguration_encode (
  const LLRP_tSGPRSConfiguration *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_GPRSConfiguration_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdGPRSConfiguration_APNConfig;

extern llrp_utf8v_t
LLRP_GPRSConfiguration_getAPNConfig (
  LLRP_tSGPRSConfiguration *pThis);

extern LLRP_tResultCode
LLRP_GPRSConfiguration_setAPNConfig (
  LLRP_tSGPRSConfiguration *pThis,
  llrp_utf8v_t Value);

  
extern LLRP_tSDialUser *
LLRP_GPRSConfiguration_getDialUser (
  LLRP_tSGPRSConfiguration *pThis);

extern LLRP_tResultCode
LLRP_GPRSConfiguration_setDialUser (
  LLRP_tSGPRSConfiguration *pThis,
  LLRP_tSDialUser *pValue);

extern LLRP_tSDialPass *
LLRP_GPRSConfiguration_getDialPass (
  LLRP_tSGPRSConfiguration *pThis);

extern LLRP_tResultCode
LLRP_GPRSConfiguration_setDialPass (
  LLRP_tSGPRSConfiguration *pThis,
  LLRP_tSDialPass *pValue);

extern LLRP_tSClientAddressConfiguration *
LLRP_GPRSConfiguration_getClientAddressConfiguration (
  LLRP_tSGPRSConfiguration *pThis);

extern LLRP_tResultCode
LLRP_GPRSConfiguration_setClientAddressConfiguration (
  LLRP_tSGPRSConfiguration *pThis,
  LLRP_tSClientAddressConfiguration *pValue);



  
struct LLRP_SCustomPrivateConfigData
{
    LLRP_tSParameter hdr;
  
  
    LLRP_tSRFModePrivateCfg * pRFModePrivateCfg;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdCustomPrivateConfigData;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdCustomPrivateConfigData[];

extern LLRP_tSCustomPrivateConfigData *
LLRP_CustomPrivateConfigData_construct (void);

extern void
LLRP_CustomPrivateConfigData_destruct (
 LLRP_tSCustomPrivateConfigData * pThis);

extern void
LLRP_CustomPrivateConfigData_decodeFields (
 LLRP_tSCustomPrivateConfigData * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_CustomPrivateConfigData_assimilateSubParameters (
 LLRP_tSCustomPrivateConfigData * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_CustomPrivateConfigData_encode (
  const LLRP_tSCustomPrivateConfigData *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_CustomPrivateConfigData_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
  
extern LLRP_tSRFModePrivateCfg *
LLRP_CustomPrivateConfigData_getRFModePrivateCfg (
  LLRP_tSCustomPrivateConfigData *pThis);

extern LLRP_tResultCode
LLRP_CustomPrivateConfigData_setRFModePrivateCfg (
  LLRP_tSCustomPrivateConfigData *pThis,
  LLRP_tSRFModePrivateCfg *pValue);



  
struct LLRP_SRFModePrivateCfg
{
    LLRP_tSParameter hdr;
  
  
    LLRP_tSRFModeCfg * listRFModeCfg;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdRFModePrivateCfg;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdRFModePrivateCfg[];

extern LLRP_tSRFModePrivateCfg *
LLRP_RFModePrivateCfg_construct (void);

extern void
LLRP_RFModePrivateCfg_destruct (
 LLRP_tSRFModePrivateCfg * pThis);

extern void
LLRP_RFModePrivateCfg_decodeFields (
 LLRP_tSRFModePrivateCfg * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_RFModePrivateCfg_assimilateSubParameters (
 LLRP_tSRFModePrivateCfg * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_RFModePrivateCfg_encode (
  const LLRP_tSRFModePrivateCfg *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_RFModePrivateCfg_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
  
extern LLRP_tSRFModeCfg *
LLRP_RFModePrivateCfg_beginRFModeCfg (
  LLRP_tSRFModePrivateCfg *pThis);

extern LLRP_tSRFModeCfg *
LLRP_RFModePrivateCfg_nextRFModeCfg (
  LLRP_tSRFModeCfg *pCurrent);

extern void
LLRP_RFModePrivateCfg_clearRFModeCfg (
  LLRP_tSRFModePrivateCfg *pThis);

extern LLRP_tResultCode
LLRP_RFModePrivateCfg_addRFModeCfg (
  LLRP_tSRFModePrivateCfg *pThis,
  LLRP_tSRFModeCfg *pValue);




  
struct LLRP_SRFModeCfg
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t AntennaID;

    llrp_u16_t ForDataRate;

    llrp_u16_t RevDataRate;

    LLRP_tEM_value_Type eM_value;

    LLRP_tEForward_link_Type eForward_link_modulation;

    llrp_u16_t PIE_Value;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdRFModeCfg;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdRFModeCfg[];

extern LLRP_tSRFModeCfg *
LLRP_RFModeCfg_construct (void);

extern void
LLRP_RFModeCfg_destruct (
 LLRP_tSRFModeCfg * pThis);

extern void
LLRP_RFModeCfg_decodeFields (
 LLRP_tSRFModeCfg * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_RFModeCfg_assimilateSubParameters (
 LLRP_tSRFModeCfg * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_RFModeCfg_encode (
  const LLRP_tSRFModeCfg *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_RFModeCfg_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdRFModeCfg_AntennaID;

extern llrp_u16_t
LLRP_RFModeCfg_getAntennaID (
  LLRP_tSRFModeCfg *pThis);

extern LLRP_tResultCode
LLRP_RFModeCfg_setAntennaID (
  LLRP_tSRFModeCfg *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdRFModeCfg_ForDataRate;

extern llrp_u16_t
LLRP_RFModeCfg_getForDataRate (
  LLRP_tSRFModeCfg *pThis);

extern LLRP_tResultCode
LLRP_RFModeCfg_setForDataRate (
  LLRP_tSRFModeCfg *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdRFModeCfg_RevDataRate;

extern llrp_u16_t
LLRP_RFModeCfg_getRevDataRate (
  LLRP_tSRFModeCfg *pThis);

extern LLRP_tResultCode
LLRP_RFModeCfg_setRevDataRate (
  LLRP_tSRFModeCfg *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdRFModeCfg_M_value;

extern LLRP_tEM_value_Type
LLRP_RFModeCfg_getM_value (
  LLRP_tSRFModeCfg *pThis);

extern LLRP_tResultCode
LLRP_RFModeCfg_setM_value (
  LLRP_tSRFModeCfg *pThis,
  LLRP_tEM_value_Type Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdRFModeCfg_Forward_link_modulation;

extern LLRP_tEForward_link_Type
LLRP_RFModeCfg_getForward_link_modulation (
  LLRP_tSRFModeCfg *pThis);

extern LLRP_tResultCode
LLRP_RFModeCfg_setForward_link_modulation (
  LLRP_tSRFModeCfg *pThis,
  LLRP_tEForward_link_Type Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdRFModeCfg_PIE_Value;

extern llrp_u16_t
LLRP_RFModeCfg_getPIE_Value (
  LLRP_tSRFModeCfg *pThis);

extern LLRP_tResultCode
LLRP_RFModeCfg_setPIE_Value (
  LLRP_tSRFModeCfg *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_SETCConfig
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t ETCVersion;

    llrp_u8_t N4Value;

    llrp_u8_t BSTInterval ;

    llrp_u16_t RSUIDChangeTime ;

    llrp_u8_t CrcChangeFlag;

    llrp_u8_t PllChannelId;

    llrp_u8_t TxPower;

    llrp_u8_t ModuleDepth;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdETCConfig;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdETCConfig[];

extern LLRP_tSETCConfig *
LLRP_ETCConfig_construct (void);

extern void
LLRP_ETCConfig_destruct (
 LLRP_tSETCConfig * pThis);

extern void
LLRP_ETCConfig_decodeFields (
 LLRP_tSETCConfig * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_ETCConfig_assimilateSubParameters (
 LLRP_tSETCConfig * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_ETCConfig_encode (
  const LLRP_tSETCConfig *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_ETCConfig_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdETCConfig_ETCVersion;

extern llrp_u8_t
LLRP_ETCConfig_getETCVersion (
  LLRP_tSETCConfig *pThis);

extern LLRP_tResultCode
LLRP_ETCConfig_setETCVersion (
  LLRP_tSETCConfig *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdETCConfig_N4Value;

extern llrp_u8_t
LLRP_ETCConfig_getN4Value (
  LLRP_tSETCConfig *pThis);

extern LLRP_tResultCode
LLRP_ETCConfig_setN4Value (
  LLRP_tSETCConfig *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdETCConfig_BSTInterval ;

extern llrp_u8_t
LLRP_ETCConfig_getBSTInterval  (
  LLRP_tSETCConfig *pThis);

extern LLRP_tResultCode
LLRP_ETCConfig_setBSTInterval  (
  LLRP_tSETCConfig *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdETCConfig_RSUIDChangeTime ;

extern llrp_u16_t
LLRP_ETCConfig_getRSUIDChangeTime  (
  LLRP_tSETCConfig *pThis);

extern LLRP_tResultCode
LLRP_ETCConfig_setRSUIDChangeTime  (
  LLRP_tSETCConfig *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdETCConfig_CrcChangeFlag;

extern llrp_u8_t
LLRP_ETCConfig_getCrcChangeFlag (
  LLRP_tSETCConfig *pThis);

extern LLRP_tResultCode
LLRP_ETCConfig_setCrcChangeFlag (
  LLRP_tSETCConfig *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdETCConfig_PllChannelId;

extern llrp_u8_t
LLRP_ETCConfig_getPllChannelId (
  LLRP_tSETCConfig *pThis);

extern LLRP_tResultCode
LLRP_ETCConfig_setPllChannelId (
  LLRP_tSETCConfig *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdETCConfig_TxPower;

extern llrp_u8_t
LLRP_ETCConfig_getTxPower (
  LLRP_tSETCConfig *pThis);

extern LLRP_tResultCode
LLRP_ETCConfig_setTxPower (
  LLRP_tSETCConfig *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdETCConfig_ModuleDepth;

extern llrp_u8_t
LLRP_ETCConfig_getModuleDepth (
  LLRP_tSETCConfig *pThis);

extern LLRP_tResultCode
LLRP_ETCConfig_setModuleDepth (
  LLRP_tSETCConfig *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SMPIAntennaConfiguration
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t AntennaID ;

  
    LLRP_tSRFReceiverSettings * pRFReceiverSettings;

    LLRP_tSRFTransmitterSettings * pRFTransmitterSettings;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdMPIAntennaConfiguration;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdMPIAntennaConfiguration[];

extern LLRP_tSMPIAntennaConfiguration *
LLRP_MPIAntennaConfiguration_construct (void);

extern void
LLRP_MPIAntennaConfiguration_destruct (
 LLRP_tSMPIAntennaConfiguration * pThis);

extern void
LLRP_MPIAntennaConfiguration_decodeFields (
 LLRP_tSMPIAntennaConfiguration * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_MPIAntennaConfiguration_assimilateSubParameters (
 LLRP_tSMPIAntennaConfiguration * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_MPIAntennaConfiguration_encode (
  const LLRP_tSMPIAntennaConfiguration *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_MPIAntennaConfiguration_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdMPIAntennaConfiguration_AntennaID ;

extern llrp_u16_t
LLRP_MPIAntennaConfiguration_getAntennaID  (
  LLRP_tSMPIAntennaConfiguration *pThis);

extern LLRP_tResultCode
LLRP_MPIAntennaConfiguration_setAntennaID  (
  LLRP_tSMPIAntennaConfiguration *pThis,
  llrp_u16_t Value);

  
extern LLRP_tSRFReceiverSettings *
LLRP_MPIAntennaConfiguration_getRFReceiverSettings (
  LLRP_tSMPIAntennaConfiguration *pThis);

extern LLRP_tResultCode
LLRP_MPIAntennaConfiguration_setRFReceiverSettings (
  LLRP_tSMPIAntennaConfiguration *pThis,
  LLRP_tSRFReceiverSettings *pValue);

extern LLRP_tSRFTransmitterSettings *
LLRP_MPIAntennaConfiguration_getRFTransmitterSettings (
  LLRP_tSMPIAntennaConfiguration *pThis);

extern LLRP_tResultCode
LLRP_MPIAntennaConfiguration_setRFTransmitterSettings (
  LLRP_tSMPIAntennaConfiguration *pThis,
  LLRP_tSRFTransmitterSettings *pValue);



  
struct LLRP_SRFReceiverSettings
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t ReceiverSensitivity ;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdRFReceiverSettings;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdRFReceiverSettings[];

extern LLRP_tSRFReceiverSettings *
LLRP_RFReceiverSettings_construct (void);

extern void
LLRP_RFReceiverSettings_destruct (
 LLRP_tSRFReceiverSettings * pThis);

extern void
LLRP_RFReceiverSettings_decodeFields (
 LLRP_tSRFReceiverSettings * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_RFReceiverSettings_assimilateSubParameters (
 LLRP_tSRFReceiverSettings * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_RFReceiverSettings_encode (
  const LLRP_tSRFReceiverSettings *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_RFReceiverSettings_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdRFReceiverSettings_ReceiverSensitivity ;

extern llrp_u16_t
LLRP_RFReceiverSettings_getReceiverSensitivity  (
  LLRP_tSRFReceiverSettings *pThis);

extern LLRP_tResultCode
LLRP_RFReceiverSettings_setReceiverSensitivity  (
  LLRP_tSRFReceiverSettings *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_SRFTransmitterSettings
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t TransmitPower ;

    llrp_u16_t HopTableID ;

    llrp_u16_t ChannelIndex ;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdRFTransmitterSettings;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdRFTransmitterSettings[];

extern LLRP_tSRFTransmitterSettings *
LLRP_RFTransmitterSettings_construct (void);

extern void
LLRP_RFTransmitterSettings_destruct (
 LLRP_tSRFTransmitterSettings * pThis);

extern void
LLRP_RFTransmitterSettings_decodeFields (
 LLRP_tSRFTransmitterSettings * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_RFTransmitterSettings_assimilateSubParameters (
 LLRP_tSRFTransmitterSettings * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_RFTransmitterSettings_encode (
  const LLRP_tSRFTransmitterSettings *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_RFTransmitterSettings_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdRFTransmitterSettings_TransmitPower ;

extern llrp_u16_t
LLRP_RFTransmitterSettings_getTransmitPower  (
  LLRP_tSRFTransmitterSettings *pThis);

extern LLRP_tResultCode
LLRP_RFTransmitterSettings_setTransmitPower  (
  LLRP_tSRFTransmitterSettings *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdRFTransmitterSettings_HopTableID ;

extern llrp_u16_t
LLRP_RFTransmitterSettings_getHopTableID  (
  LLRP_tSRFTransmitterSettings *pThis);

extern LLRP_tResultCode
LLRP_RFTransmitterSettings_setHopTableID  (
  LLRP_tSRFTransmitterSettings *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdRFTransmitterSettings_ChannelIndex ;

extern llrp_u16_t
LLRP_RFTransmitterSettings_getChannelIndex  (
  LLRP_tSRFTransmitterSettings *pThis);

extern LLRP_tResultCode
LLRP_RFTransmitterSettings_setChannelIndex  (
  LLRP_tSRFTransmitterSettings *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_SMPIProperties
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t RSUID ;

    llrp_u16_t PathInfo ;

    llrp_u8_t BackupStatus ;

    llrp_u8_t RFStatus ;

    llrp_u8_t RFMode ;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdMPIProperties;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdMPIProperties[];

extern LLRP_tSMPIProperties *
LLRP_MPIProperties_construct (void);

extern void
LLRP_MPIProperties_destruct (
 LLRP_tSMPIProperties * pThis);

extern void
LLRP_MPIProperties_decodeFields (
 LLRP_tSMPIProperties * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_MPIProperties_assimilateSubParameters (
 LLRP_tSMPIProperties * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_MPIProperties_encode (
  const LLRP_tSMPIProperties *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_MPIProperties_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdMPIProperties_RSUID ;

extern llrp_u16_t
LLRP_MPIProperties_getRSUID  (
  LLRP_tSMPIProperties *pThis);

extern LLRP_tResultCode
LLRP_MPIProperties_setRSUID  (
  LLRP_tSMPIProperties *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdMPIProperties_PathInfo ;

extern llrp_u16_t
LLRP_MPIProperties_getPathInfo  (
  LLRP_tSMPIProperties *pThis);

extern LLRP_tResultCode
LLRP_MPIProperties_setPathInfo  (
  LLRP_tSMPIProperties *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdMPIProperties_BackupStatus ;

extern llrp_u8_t
LLRP_MPIProperties_getBackupStatus  (
  LLRP_tSMPIProperties *pThis);

extern LLRP_tResultCode
LLRP_MPIProperties_setBackupStatus  (
  LLRP_tSMPIProperties *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdMPIProperties_RFStatus ;

extern llrp_u8_t
LLRP_MPIProperties_getRFStatus  (
  LLRP_tSMPIProperties *pThis);

extern LLRP_tResultCode
LLRP_MPIProperties_setRFStatus  (
  LLRP_tSMPIProperties *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdMPIProperties_RFMode ;

extern llrp_u8_t
LLRP_MPIProperties_getRFMode  (
  LLRP_tSMPIProperties *pThis);

extern LLRP_tResultCode
LLRP_MPIProperties_setRFMode  (
  LLRP_tSMPIProperties *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SMPIPsamWhiteList
{
    LLRP_tSParameter hdr;
  
  
    LLRP_tSPSAMID * listPSAMID;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdMPIPsamWhiteList;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdMPIPsamWhiteList[];

extern LLRP_tSMPIPsamWhiteList *
LLRP_MPIPsamWhiteList_construct (void);

extern void
LLRP_MPIPsamWhiteList_destruct (
 LLRP_tSMPIPsamWhiteList * pThis);

extern void
LLRP_MPIPsamWhiteList_decodeFields (
 LLRP_tSMPIPsamWhiteList * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_MPIPsamWhiteList_assimilateSubParameters (
 LLRP_tSMPIPsamWhiteList * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_MPIPsamWhiteList_encode (
  const LLRP_tSMPIPsamWhiteList *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_MPIPsamWhiteList_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
  
extern LLRP_tSPSAMID *
LLRP_MPIPsamWhiteList_beginPSAMID (
  LLRP_tSMPIPsamWhiteList *pThis);

extern LLRP_tSPSAMID *
LLRP_MPIPsamWhiteList_nextPSAMID (
  LLRP_tSPSAMID *pCurrent);

extern void
LLRP_MPIPsamWhiteList_clearPSAMID (
  LLRP_tSMPIPsamWhiteList *pThis);

extern LLRP_tResultCode
LLRP_MPIPsamWhiteList_addPSAMID (
  LLRP_tSMPIPsamWhiteList *pThis,
  LLRP_tSPSAMID *pValue);




  
struct LLRP_SPSAMID
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t num ;

    llrp_u8v_t PSAMID   ;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdPSAMID;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdPSAMID[];

extern LLRP_tSPSAMID *
LLRP_PSAMID_construct (void);

extern void
LLRP_PSAMID_destruct (
 LLRP_tSPSAMID * pThis);

extern void
LLRP_PSAMID_decodeFields (
 LLRP_tSPSAMID * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_PSAMID_assimilateSubParameters (
 LLRP_tSPSAMID * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_PSAMID_encode (
  const LLRP_tSPSAMID *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_PSAMID_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdPSAMID_num ;

extern llrp_u8_t
LLRP_PSAMID_getnum  (
  LLRP_tSPSAMID *pThis);

extern LLRP_tResultCode
LLRP_PSAMID_setnum  (
  LLRP_tSPSAMID *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdPSAMID_PSAMID   ;

extern llrp_u8v_t
LLRP_PSAMID_getPSAMID    (
  LLRP_tSPSAMID *pThis);

extern LLRP_tResultCode
LLRP_PSAMID_setPSAMID    (
  LLRP_tSPSAMID *pThis,
  llrp_u8v_t Value);

  


  
struct LLRP_SMPISIMWhiteList
{
    LLRP_tSParameter hdr;
  
  
    LLRP_tSTelNo * listTelNo;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdMPISIMWhiteList;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdMPISIMWhiteList[];

extern LLRP_tSMPISIMWhiteList *
LLRP_MPISIMWhiteList_construct (void);

extern void
LLRP_MPISIMWhiteList_destruct (
 LLRP_tSMPISIMWhiteList * pThis);

extern void
LLRP_MPISIMWhiteList_decodeFields (
 LLRP_tSMPISIMWhiteList * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_MPISIMWhiteList_assimilateSubParameters (
 LLRP_tSMPISIMWhiteList * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_MPISIMWhiteList_encode (
  const LLRP_tSMPISIMWhiteList *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_MPISIMWhiteList_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
  
extern LLRP_tSTelNo *
LLRP_MPISIMWhiteList_beginTelNo (
  LLRP_tSMPISIMWhiteList *pThis);

extern LLRP_tSTelNo *
LLRP_MPISIMWhiteList_nextTelNo (
  LLRP_tSTelNo *pCurrent);

extern void
LLRP_MPISIMWhiteList_clearTelNo (
  LLRP_tSMPISIMWhiteList *pThis);

extern LLRP_tResultCode
LLRP_MPISIMWhiteList_addTelNo (
  LLRP_tSMPISIMWhiteList *pThis,
  LLRP_tSTelNo *pValue);




  
struct LLRP_STelNo
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t Position;

    llrp_u8_t RW;

    llrp_u8v_t TelNo;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdTelNo;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdTelNo[];

extern LLRP_tSTelNo *
LLRP_TelNo_construct (void);

extern void
LLRP_TelNo_destruct (
 LLRP_tSTelNo * pThis);

extern void
LLRP_TelNo_decodeFields (
 LLRP_tSTelNo * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_TelNo_assimilateSubParameters (
 LLRP_tSTelNo * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_TelNo_encode (
  const LLRP_tSTelNo *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_TelNo_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdTelNo_Position;

extern llrp_u8_t
LLRP_TelNo_getPosition (
  LLRP_tSTelNo *pThis);

extern LLRP_tResultCode
LLRP_TelNo_setPosition (
  LLRP_tSTelNo *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdTelNo_RW;

extern llrp_u8_t
LLRP_TelNo_getRW (
  LLRP_tSTelNo *pThis);

extern LLRP_tResultCode
LLRP_TelNo_setRW (
  LLRP_tSTelNo *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdTelNo_TelNo;

extern llrp_u8v_t
LLRP_TelNo_getTelNo (
  LLRP_tSTelNo *pThis);

extern LLRP_tResultCode
LLRP_TelNo_setTelNo (
  LLRP_tSTelNo *pThis,
  llrp_u8v_t Value);

  


  
struct LLRP_SMPIPsamAuthenticationFile
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t PSAMnum;

    llrp_u16_t AuthenticationFile;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdMPIPsamAuthenticationFile;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdMPIPsamAuthenticationFile[];

extern LLRP_tSMPIPsamAuthenticationFile *
LLRP_MPIPsamAuthenticationFile_construct (void);

extern void
LLRP_MPIPsamAuthenticationFile_destruct (
 LLRP_tSMPIPsamAuthenticationFile * pThis);

extern void
LLRP_MPIPsamAuthenticationFile_decodeFields (
 LLRP_tSMPIPsamAuthenticationFile * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_MPIPsamAuthenticationFile_assimilateSubParameters (
 LLRP_tSMPIPsamAuthenticationFile * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_MPIPsamAuthenticationFile_encode (
  const LLRP_tSMPIPsamAuthenticationFile *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_MPIPsamAuthenticationFile_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdMPIPsamAuthenticationFile_PSAMnum;

extern llrp_u8_t
LLRP_MPIPsamAuthenticationFile_getPSAMnum (
  LLRP_tSMPIPsamAuthenticationFile *pThis);

extern LLRP_tResultCode
LLRP_MPIPsamAuthenticationFile_setPSAMnum (
  LLRP_tSMPIPsamAuthenticationFile *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdMPIPsamAuthenticationFile_AuthenticationFile;

extern llrp_u16_t
LLRP_MPIPsamAuthenticationFile_getAuthenticationFile (
  LLRP_tSMPIPsamAuthenticationFile *pThis);

extern LLRP_tResultCode
LLRP_MPIPsamAuthenticationFile_setAuthenticationFile (
  LLRP_tSMPIPsamAuthenticationFile *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_SMPISMSCenterNo
{
    LLRP_tSParameter hdr;
  
    llrp_u8v_t CenterNo;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdMPISMSCenterNo;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdMPISMSCenterNo[];

extern LLRP_tSMPISMSCenterNo *
LLRP_MPISMSCenterNo_construct (void);

extern void
LLRP_MPISMSCenterNo_destruct (
 LLRP_tSMPISMSCenterNo * pThis);

extern void
LLRP_MPISMSCenterNo_decodeFields (
 LLRP_tSMPISMSCenterNo * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_MPISMSCenterNo_assimilateSubParameters (
 LLRP_tSMPISMSCenterNo * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_MPISMSCenterNo_encode (
  const LLRP_tSMPISMSCenterNo *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_MPISMSCenterNo_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdMPISMSCenterNo_CenterNo;

extern llrp_u8v_t
LLRP_MPISMSCenterNo_getCenterNo (
  LLRP_tSMPISMSCenterNo *pThis);

extern LLRP_tResultCode
LLRP_MPISMSCenterNo_setCenterNo (
  LLRP_tSMPISMSCenterNo *pThis,
  llrp_u8v_t Value);

  


  
struct LLRP_SPPPDialConfiguration
{
    LLRP_tSParameter hdr;
  
    llrp_u1_t IsUsedDNS;

    llrp_u1_t IsReConn;

    LLRP_tEConnWaysType eConnWays;

    llrp_u32_t MasterDNS;

    llrp_u32_t SlaveDNS;

    llrp_u16_t ReConnTimer;

  
    LLRP_tSDialNumber * pDialNumber;

    LLRP_tSDialUser * pDialUser;

    LLRP_tSDialPass * pDialPass;

    LLRP_tSTimePhase * listTimePhase;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdPPPDialConfiguration;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdPPPDialConfiguration[];

extern LLRP_tSPPPDialConfiguration *
LLRP_PPPDialConfiguration_construct (void);

extern void
LLRP_PPPDialConfiguration_destruct (
 LLRP_tSPPPDialConfiguration * pThis);

extern void
LLRP_PPPDialConfiguration_decodeFields (
 LLRP_tSPPPDialConfiguration * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_PPPDialConfiguration_assimilateSubParameters (
 LLRP_tSPPPDialConfiguration * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_PPPDialConfiguration_encode (
  const LLRP_tSPPPDialConfiguration *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_PPPDialConfiguration_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdPPPDialConfiguration_IsUsedDNS;

extern llrp_u1_t
LLRP_PPPDialConfiguration_getIsUsedDNS (
  LLRP_tSPPPDialConfiguration *pThis);

extern LLRP_tResultCode
LLRP_PPPDialConfiguration_setIsUsedDNS (
  LLRP_tSPPPDialConfiguration *pThis,
  llrp_u1_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdPPPDialConfiguration_IsReConn;

extern llrp_u1_t
LLRP_PPPDialConfiguration_getIsReConn (
  LLRP_tSPPPDialConfiguration *pThis);

extern LLRP_tResultCode
LLRP_PPPDialConfiguration_setIsReConn (
  LLRP_tSPPPDialConfiguration *pThis,
  llrp_u1_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdPPPDialConfiguration_ConnWays;

extern LLRP_tEConnWaysType
LLRP_PPPDialConfiguration_getConnWays (
  LLRP_tSPPPDialConfiguration *pThis);

extern LLRP_tResultCode
LLRP_PPPDialConfiguration_setConnWays (
  LLRP_tSPPPDialConfiguration *pThis,
  LLRP_tEConnWaysType Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdPPPDialConfiguration_MasterDNS;

extern llrp_u32_t
LLRP_PPPDialConfiguration_getMasterDNS (
  LLRP_tSPPPDialConfiguration *pThis);

extern LLRP_tResultCode
LLRP_PPPDialConfiguration_setMasterDNS (
  LLRP_tSPPPDialConfiguration *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdPPPDialConfiguration_SlaveDNS;

extern llrp_u32_t
LLRP_PPPDialConfiguration_getSlaveDNS (
  LLRP_tSPPPDialConfiguration *pThis);

extern LLRP_tResultCode
LLRP_PPPDialConfiguration_setSlaveDNS (
  LLRP_tSPPPDialConfiguration *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdPPPDialConfiguration_ReConnTimer;

extern llrp_u16_t
LLRP_PPPDialConfiguration_getReConnTimer (
  LLRP_tSPPPDialConfiguration *pThis);

extern LLRP_tResultCode
LLRP_PPPDialConfiguration_setReConnTimer (
  LLRP_tSPPPDialConfiguration *pThis,
  llrp_u16_t Value);

  
extern LLRP_tSDialNumber *
LLRP_PPPDialConfiguration_getDialNumber (
  LLRP_tSPPPDialConfiguration *pThis);

extern LLRP_tResultCode
LLRP_PPPDialConfiguration_setDialNumber (
  LLRP_tSPPPDialConfiguration *pThis,
  LLRP_tSDialNumber *pValue);

extern LLRP_tSDialUser *
LLRP_PPPDialConfiguration_getDialUser (
  LLRP_tSPPPDialConfiguration *pThis);

extern LLRP_tResultCode
LLRP_PPPDialConfiguration_setDialUser (
  LLRP_tSPPPDialConfiguration *pThis,
  LLRP_tSDialUser *pValue);

extern LLRP_tSDialPass *
LLRP_PPPDialConfiguration_getDialPass (
  LLRP_tSPPPDialConfiguration *pThis);

extern LLRP_tResultCode
LLRP_PPPDialConfiguration_setDialPass (
  LLRP_tSPPPDialConfiguration *pThis,
  LLRP_tSDialPass *pValue);

extern LLRP_tSTimePhase *
LLRP_PPPDialConfiguration_beginTimePhase (
  LLRP_tSPPPDialConfiguration *pThis);

extern LLRP_tSTimePhase *
LLRP_PPPDialConfiguration_nextTimePhase (
  LLRP_tSTimePhase *pCurrent);

extern void
LLRP_PPPDialConfiguration_clearTimePhase (
  LLRP_tSPPPDialConfiguration *pThis);

extern LLRP_tResultCode
LLRP_PPPDialConfiguration_addTimePhase (
  LLRP_tSPPPDialConfiguration *pThis,
  LLRP_tSTimePhase *pValue);




  
struct LLRP_SDialNumber
{
    LLRP_tSParameter hdr;
  
    llrp_utf8v_t Number;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdDialNumber;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdDialNumber[];

extern LLRP_tSDialNumber *
LLRP_DialNumber_construct (void);

extern void
LLRP_DialNumber_destruct (
 LLRP_tSDialNumber * pThis);

extern void
LLRP_DialNumber_decodeFields (
 LLRP_tSDialNumber * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_DialNumber_assimilateSubParameters (
 LLRP_tSDialNumber * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_DialNumber_encode (
  const LLRP_tSDialNumber *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_DialNumber_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdDialNumber_Number;

extern llrp_utf8v_t
LLRP_DialNumber_getNumber (
  LLRP_tSDialNumber *pThis);

extern LLRP_tResultCode
LLRP_DialNumber_setNumber (
  LLRP_tSDialNumber *pThis,
  llrp_utf8v_t Value);

  


  
struct LLRP_SDialUser
{
    LLRP_tSParameter hdr;
  
    llrp_utf8v_t User;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdDialUser;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdDialUser[];

extern LLRP_tSDialUser *
LLRP_DialUser_construct (void);

extern void
LLRP_DialUser_destruct (
 LLRP_tSDialUser * pThis);

extern void
LLRP_DialUser_decodeFields (
 LLRP_tSDialUser * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_DialUser_assimilateSubParameters (
 LLRP_tSDialUser * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_DialUser_encode (
  const LLRP_tSDialUser *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_DialUser_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdDialUser_User;

extern llrp_utf8v_t
LLRP_DialUser_getUser (
  LLRP_tSDialUser *pThis);

extern LLRP_tResultCode
LLRP_DialUser_setUser (
  LLRP_tSDialUser *pThis,
  llrp_utf8v_t Value);

  


  
struct LLRP_SDialPass
{
    LLRP_tSParameter hdr;
  
    llrp_utf8v_t Pwd;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdDialPass;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdDialPass[];

extern LLRP_tSDialPass *
LLRP_DialPass_construct (void);

extern void
LLRP_DialPass_destruct (
 LLRP_tSDialPass * pThis);

extern void
LLRP_DialPass_decodeFields (
 LLRP_tSDialPass * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_DialPass_assimilateSubParameters (
 LLRP_tSDialPass * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_DialPass_encode (
  const LLRP_tSDialPass *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_DialPass_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdDialPass_Pwd;

extern llrp_utf8v_t
LLRP_DialPass_getPwd (
  LLRP_tSDialPass *pThis);

extern LLRP_tResultCode
LLRP_DialPass_setPwd (
  LLRP_tSDialPass *pThis,
  llrp_utf8v_t Value);

  


  
struct LLRP_STimePhase
{
    LLRP_tSParameter hdr;
  
    llrp_u32_t StartTime;

    llrp_u32_t EndTime;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdTimePhase;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdTimePhase[];

extern LLRP_tSTimePhase *
LLRP_TimePhase_construct (void);

extern void
LLRP_TimePhase_destruct (
 LLRP_tSTimePhase * pThis);

extern void
LLRP_TimePhase_decodeFields (
 LLRP_tSTimePhase * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_TimePhase_assimilateSubParameters (
 LLRP_tSTimePhase * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_TimePhase_encode (
  const LLRP_tSTimePhase *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_TimePhase_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdTimePhase_StartTime;

extern llrp_u32_t
LLRP_TimePhase_getStartTime (
  LLRP_tSTimePhase *pThis);

extern LLRP_tResultCode
LLRP_TimePhase_setStartTime (
  LLRP_tSTimePhase *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdTimePhase_EndTime;

extern llrp_u32_t
LLRP_TimePhase_getEndTime (
  LLRP_tSTimePhase *pThis);

extern LLRP_tResultCode
LLRP_TimePhase_setEndTime (
  LLRP_tSTimePhase *pThis,
  llrp_u32_t Value);

  


  
struct LLRP_SCommunicationConfiguration
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t CommType;

  
    LLRP_tSModeConfiguration * pModeConfiguration;

    LLRP_tSReaderAddressConfiguration * pReaderAddressConfiguration;

    LLRP_tSSerialPortConfiguration * listSerialPortConfiguration;

    LLRP_tSPPPDialConfiguration * pPPPDialConfiguration;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdCommunicationConfiguration;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdCommunicationConfiguration[];

extern LLRP_tSCommunicationConfiguration *
LLRP_CommunicationConfiguration_construct (void);

extern void
LLRP_CommunicationConfiguration_destruct (
 LLRP_tSCommunicationConfiguration * pThis);

extern void
LLRP_CommunicationConfiguration_decodeFields (
 LLRP_tSCommunicationConfiguration * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_CommunicationConfiguration_assimilateSubParameters (
 LLRP_tSCommunicationConfiguration * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_CommunicationConfiguration_encode (
  const LLRP_tSCommunicationConfiguration *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_CommunicationConfiguration_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdCommunicationConfiguration_CommType;

extern llrp_u16_t
LLRP_CommunicationConfiguration_getCommType (
  LLRP_tSCommunicationConfiguration *pThis);

extern LLRP_tResultCode
LLRP_CommunicationConfiguration_setCommType (
  LLRP_tSCommunicationConfiguration *pThis,
  llrp_u16_t Value);

  
extern LLRP_tSModeConfiguration *
LLRP_CommunicationConfiguration_getModeConfiguration (
  LLRP_tSCommunicationConfiguration *pThis);

extern LLRP_tResultCode
LLRP_CommunicationConfiguration_setModeConfiguration (
  LLRP_tSCommunicationConfiguration *pThis,
  LLRP_tSModeConfiguration *pValue);

extern LLRP_tSReaderAddressConfiguration *
LLRP_CommunicationConfiguration_getReaderAddressConfiguration (
  LLRP_tSCommunicationConfiguration *pThis);

extern LLRP_tResultCode
LLRP_CommunicationConfiguration_setReaderAddressConfiguration (
  LLRP_tSCommunicationConfiguration *pThis,
  LLRP_tSReaderAddressConfiguration *pValue);

extern LLRP_tSSerialPortConfiguration *
LLRP_CommunicationConfiguration_beginSerialPortConfiguration (
  LLRP_tSCommunicationConfiguration *pThis);

extern LLRP_tSSerialPortConfiguration *
LLRP_CommunicationConfiguration_nextSerialPortConfiguration (
  LLRP_tSSerialPortConfiguration *pCurrent);

extern void
LLRP_CommunicationConfiguration_clearSerialPortConfiguration (
  LLRP_tSCommunicationConfiguration *pThis);

extern LLRP_tResultCode
LLRP_CommunicationConfiguration_addSerialPortConfiguration (
  LLRP_tSCommunicationConfiguration *pThis,
  LLRP_tSSerialPortConfiguration *pValue);


extern LLRP_tSPPPDialConfiguration *
LLRP_CommunicationConfiguration_getPPPDialConfiguration (
  LLRP_tSCommunicationConfiguration *pThis);

extern LLRP_tResultCode
LLRP_CommunicationConfiguration_setPPPDialConfiguration (
  LLRP_tSCommunicationConfiguration *pThis,
  LLRP_tSPPPDialConfiguration *pValue);



  
struct LLRP_SModeConfiguration
{
    LLRP_tSParameter hdr;
  
    llrp_u1_t IsSingleton;

  
    LLRP_tSLinkConfiguration * listLinkConfiguration;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdModeConfiguration;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdModeConfiguration[];

extern LLRP_tSModeConfiguration *
LLRP_ModeConfiguration_construct (void);

extern void
LLRP_ModeConfiguration_destruct (
 LLRP_tSModeConfiguration * pThis);

extern void
LLRP_ModeConfiguration_decodeFields (
 LLRP_tSModeConfiguration * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_ModeConfiguration_assimilateSubParameters (
 LLRP_tSModeConfiguration * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_ModeConfiguration_encode (
  const LLRP_tSModeConfiguration *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_ModeConfiguration_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdModeConfiguration_IsSingleton;

extern llrp_u1_t
LLRP_ModeConfiguration_getIsSingleton (
  LLRP_tSModeConfiguration *pThis);

extern LLRP_tResultCode
LLRP_ModeConfiguration_setIsSingleton (
  LLRP_tSModeConfiguration *pThis,
  llrp_u1_t Value);

  
extern LLRP_tSLinkConfiguration *
LLRP_ModeConfiguration_beginLinkConfiguration (
  LLRP_tSModeConfiguration *pThis);

extern LLRP_tSLinkConfiguration *
LLRP_ModeConfiguration_nextLinkConfiguration (
  LLRP_tSLinkConfiguration *pCurrent);

extern void
LLRP_ModeConfiguration_clearLinkConfiguration (
  LLRP_tSModeConfiguration *pThis);

extern LLRP_tResultCode
LLRP_ModeConfiguration_addLinkConfiguration (
  LLRP_tSModeConfiguration *pThis,
  LLRP_tSLinkConfiguration *pValue);




  
struct LLRP_SReaderAddressConfiguration
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t AddressType;

    llrp_u8_t IPVersion;

  
    LLRP_tSIPVer4 * listIPVer4;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdReaderAddressConfiguration;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdReaderAddressConfiguration[];

extern LLRP_tSReaderAddressConfiguration *
LLRP_ReaderAddressConfiguration_construct (void);

extern void
LLRP_ReaderAddressConfiguration_destruct (
 LLRP_tSReaderAddressConfiguration * pThis);

extern void
LLRP_ReaderAddressConfiguration_decodeFields (
 LLRP_tSReaderAddressConfiguration * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_ReaderAddressConfiguration_assimilateSubParameters (
 LLRP_tSReaderAddressConfiguration * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_ReaderAddressConfiguration_encode (
  const LLRP_tSReaderAddressConfiguration *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_ReaderAddressConfiguration_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdReaderAddressConfiguration_AddressType;

extern llrp_u8_t
LLRP_ReaderAddressConfiguration_getAddressType (
  LLRP_tSReaderAddressConfiguration *pThis);

extern LLRP_tResultCode
LLRP_ReaderAddressConfiguration_setAddressType (
  LLRP_tSReaderAddressConfiguration *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdReaderAddressConfiguration_IPVersion;

extern llrp_u8_t
LLRP_ReaderAddressConfiguration_getIPVersion (
  LLRP_tSReaderAddressConfiguration *pThis);

extern LLRP_tResultCode
LLRP_ReaderAddressConfiguration_setIPVersion (
  LLRP_tSReaderAddressConfiguration *pThis,
  llrp_u8_t Value);

  
extern LLRP_tSIPVer4 *
LLRP_ReaderAddressConfiguration_beginIPVer4 (
  LLRP_tSReaderAddressConfiguration *pThis);

extern LLRP_tSIPVer4 *
LLRP_ReaderAddressConfiguration_nextIPVer4 (
  LLRP_tSIPVer4 *pCurrent);

extern void
LLRP_ReaderAddressConfiguration_clearIPVer4 (
  LLRP_tSReaderAddressConfiguration *pThis);

extern LLRP_tResultCode
LLRP_ReaderAddressConfiguration_addIPVer4 (
  LLRP_tSReaderAddressConfiguration *pThis,
  LLRP_tSIPVer4 *pValue);




  
struct LLRP_SIPVer4
{
    LLRP_tSParameter hdr;
  
    llrp_u32_t IPAddress;

    llrp_u32_t IPMask;

    llrp_u1_t IsDHCP;

  
    LLRP_tSGateWay * listGateWay;

    LLRP_tSDNSAddr * listDNSAddr;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdIPVer4;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdIPVer4[];

extern LLRP_tSIPVer4 *
LLRP_IPVer4_construct (void);

extern void
LLRP_IPVer4_destruct (
 LLRP_tSIPVer4 * pThis);

extern void
LLRP_IPVer4_decodeFields (
 LLRP_tSIPVer4 * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_IPVer4_assimilateSubParameters (
 LLRP_tSIPVer4 * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_IPVer4_encode (
  const LLRP_tSIPVer4 *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_IPVer4_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdIPVer4_IPAddress;

extern llrp_u32_t
LLRP_IPVer4_getIPAddress (
  LLRP_tSIPVer4 *pThis);

extern LLRP_tResultCode
LLRP_IPVer4_setIPAddress (
  LLRP_tSIPVer4 *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdIPVer4_IPMask;

extern llrp_u32_t
LLRP_IPVer4_getIPMask (
  LLRP_tSIPVer4 *pThis);

extern LLRP_tResultCode
LLRP_IPVer4_setIPMask (
  LLRP_tSIPVer4 *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdIPVer4_IsDHCP;

extern llrp_u1_t
LLRP_IPVer4_getIsDHCP (
  LLRP_tSIPVer4 *pThis);

extern LLRP_tResultCode
LLRP_IPVer4_setIsDHCP (
  LLRP_tSIPVer4 *pThis,
  llrp_u1_t Value);

  
extern LLRP_tSGateWay *
LLRP_IPVer4_beginGateWay (
  LLRP_tSIPVer4 *pThis);

extern LLRP_tSGateWay *
LLRP_IPVer4_nextGateWay (
  LLRP_tSGateWay *pCurrent);

extern void
LLRP_IPVer4_clearGateWay (
  LLRP_tSIPVer4 *pThis);

extern LLRP_tResultCode
LLRP_IPVer4_addGateWay (
  LLRP_tSIPVer4 *pThis,
  LLRP_tSGateWay *pValue);


extern LLRP_tSDNSAddr *
LLRP_IPVer4_beginDNSAddr (
  LLRP_tSIPVer4 *pThis);

extern LLRP_tSDNSAddr *
LLRP_IPVer4_nextDNSAddr (
  LLRP_tSDNSAddr *pCurrent);

extern void
LLRP_IPVer4_clearDNSAddr (
  LLRP_tSIPVer4 *pThis);

extern LLRP_tResultCode
LLRP_IPVer4_addDNSAddr (
  LLRP_tSIPVer4 *pThis,
  LLRP_tSDNSAddr *pValue);




  
struct LLRP_SGateWay
{
    LLRP_tSParameter hdr;
  
    llrp_u32_t Address;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdGateWay;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdGateWay[];

extern LLRP_tSGateWay *
LLRP_GateWay_construct (void);

extern void
LLRP_GateWay_destruct (
 LLRP_tSGateWay * pThis);

extern void
LLRP_GateWay_decodeFields (
 LLRP_tSGateWay * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_GateWay_assimilateSubParameters (
 LLRP_tSGateWay * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_GateWay_encode (
  const LLRP_tSGateWay *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_GateWay_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdGateWay_Address;

extern llrp_u32_t
LLRP_GateWay_getAddress (
  LLRP_tSGateWay *pThis);

extern LLRP_tResultCode
LLRP_GateWay_setAddress (
  LLRP_tSGateWay *pThis,
  llrp_u32_t Value);

  


  
struct LLRP_SDNSAddr
{
    LLRP_tSParameter hdr;
  
    llrp_u32_t Address;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdDNSAddr;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdDNSAddr[];

extern LLRP_tSDNSAddr *
LLRP_DNSAddr_construct (void);

extern void
LLRP_DNSAddr_destruct (
 LLRP_tSDNSAddr * pThis);

extern void
LLRP_DNSAddr_decodeFields (
 LLRP_tSDNSAddr * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_DNSAddr_assimilateSubParameters (
 LLRP_tSDNSAddr * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_DNSAddr_encode (
  const LLRP_tSDNSAddr *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_DNSAddr_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdDNSAddr_Address;

extern llrp_u32_t
LLRP_DNSAddr_getAddress (
  LLRP_tSDNSAddr *pThis);

extern LLRP_tResultCode
LLRP_DNSAddr_setAddress (
  LLRP_tSDNSAddr *pThis,
  llrp_u32_t Value);

  


  
struct LLRP_SNTPConfiguration
{
    LLRP_tSParameter hdr;
  
    llrp_s8_t TimeZoneH;

    llrp_s8_t TimeZoneM;

  
    LLRP_tSIPAddress * listIPAddress;

    LLRP_tSNtpPeriodTime * pNtpPeriodTime;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdNTPConfiguration;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdNTPConfiguration[];

extern LLRP_tSNTPConfiguration *
LLRP_NTPConfiguration_construct (void);

extern void
LLRP_NTPConfiguration_destruct (
 LLRP_tSNTPConfiguration * pThis);

extern void
LLRP_NTPConfiguration_decodeFields (
 LLRP_tSNTPConfiguration * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_NTPConfiguration_assimilateSubParameters (
 LLRP_tSNTPConfiguration * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_NTPConfiguration_encode (
  const LLRP_tSNTPConfiguration *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_NTPConfiguration_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdNTPConfiguration_TimeZoneH;

extern llrp_s8_t
LLRP_NTPConfiguration_getTimeZoneH (
  LLRP_tSNTPConfiguration *pThis);

extern LLRP_tResultCode
LLRP_NTPConfiguration_setTimeZoneH (
  LLRP_tSNTPConfiguration *pThis,
  llrp_s8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdNTPConfiguration_TimeZoneM;

extern llrp_s8_t
LLRP_NTPConfiguration_getTimeZoneM (
  LLRP_tSNTPConfiguration *pThis);

extern LLRP_tResultCode
LLRP_NTPConfiguration_setTimeZoneM (
  LLRP_tSNTPConfiguration *pThis,
  llrp_s8_t Value);

  
extern LLRP_tSIPAddress *
LLRP_NTPConfiguration_beginIPAddress (
  LLRP_tSNTPConfiguration *pThis);

extern LLRP_tSIPAddress *
LLRP_NTPConfiguration_nextIPAddress (
  LLRP_tSIPAddress *pCurrent);

extern void
LLRP_NTPConfiguration_clearIPAddress (
  LLRP_tSNTPConfiguration *pThis);

extern LLRP_tResultCode
LLRP_NTPConfiguration_addIPAddress (
  LLRP_tSNTPConfiguration *pThis,
  LLRP_tSIPAddress *pValue);


extern LLRP_tSNtpPeriodTime *
LLRP_NTPConfiguration_getNtpPeriodTime (
  LLRP_tSNTPConfiguration *pThis);

extern LLRP_tResultCode
LLRP_NTPConfiguration_setNtpPeriodTime (
  LLRP_tSNTPConfiguration *pThis,
  LLRP_tSNtpPeriodTime *pValue);



  
struct LLRP_SNtpPeriodTime
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t NtpPeriodValue;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdNtpPeriodTime;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdNtpPeriodTime[];

extern LLRP_tSNtpPeriodTime *
LLRP_NtpPeriodTime_construct (void);

extern void
LLRP_NtpPeriodTime_destruct (
 LLRP_tSNtpPeriodTime * pThis);

extern void
LLRP_NtpPeriodTime_decodeFields (
 LLRP_tSNtpPeriodTime * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_NtpPeriodTime_assimilateSubParameters (
 LLRP_tSNtpPeriodTime * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_NtpPeriodTime_encode (
  const LLRP_tSNtpPeriodTime *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_NtpPeriodTime_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdNtpPeriodTime_NtpPeriodValue;

extern llrp_u16_t
LLRP_NtpPeriodTime_getNtpPeriodValue (
  LLRP_tSNtpPeriodTime *pThis);

extern LLRP_tResultCode
LLRP_NtpPeriodTime_setNtpPeriodValue (
  LLRP_tSNtpPeriodTime *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_SIPAddress
{
    LLRP_tSParameter hdr;
  
    llrp_u32_t IpAddr;

    llrp_u16_t Port;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdIPAddress;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdIPAddress[];

extern LLRP_tSIPAddress *
LLRP_IPAddress_construct (void);

extern void
LLRP_IPAddress_destruct (
 LLRP_tSIPAddress * pThis);

extern void
LLRP_IPAddress_decodeFields (
 LLRP_tSIPAddress * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_IPAddress_assimilateSubParameters (
 LLRP_tSIPAddress * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_IPAddress_encode (
  const LLRP_tSIPAddress *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_IPAddress_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdIPAddress_IpAddr;

extern llrp_u32_t
LLRP_IPAddress_getIpAddr (
  LLRP_tSIPAddress *pThis);

extern LLRP_tResultCode
LLRP_IPAddress_setIpAddr (
  LLRP_tSIPAddress *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdIPAddress_Port;

extern llrp_u16_t
LLRP_IPAddress_getPort (
  LLRP_tSIPAddress *pThis);

extern LLRP_tResultCode
LLRP_IPAddress_setPort (
  LLRP_tSIPAddress *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_SClientAddressConfiguration
{
    LLRP_tSParameter hdr;
  
  
    LLRP_tSIPAddress * pIPAddress;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdClientAddressConfiguration;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdClientAddressConfiguration[];

extern LLRP_tSClientAddressConfiguration *
LLRP_ClientAddressConfiguration_construct (void);

extern void
LLRP_ClientAddressConfiguration_destruct (
 LLRP_tSClientAddressConfiguration * pThis);

extern void
LLRP_ClientAddressConfiguration_decodeFields (
 LLRP_tSClientAddressConfiguration * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_ClientAddressConfiguration_assimilateSubParameters (
 LLRP_tSClientAddressConfiguration * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_ClientAddressConfiguration_encode (
  const LLRP_tSClientAddressConfiguration *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_ClientAddressConfiguration_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
  
extern LLRP_tSIPAddress *
LLRP_ClientAddressConfiguration_getIPAddress (
  LLRP_tSClientAddressConfiguration *pThis);

extern LLRP_tResultCode
LLRP_ClientAddressConfiguration_setIPAddress (
  LLRP_tSClientAddressConfiguration *pThis,
  LLRP_tSIPAddress *pValue);



  
struct LLRP_SLinkConfiguration
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t LinkID;

  
    LLRP_tSCommMode * pCommMode;

    LLRP_tSClientAddressConfiguration * pClientAddressConfiguration;

    LLRP_tSHostPortConfiguration * pHostPortConfiguration;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdLinkConfiguration;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdLinkConfiguration[];

extern LLRP_tSLinkConfiguration *
LLRP_LinkConfiguration_construct (void);

extern void
LLRP_LinkConfiguration_destruct (
 LLRP_tSLinkConfiguration * pThis);

extern void
LLRP_LinkConfiguration_decodeFields (
 LLRP_tSLinkConfiguration * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_LinkConfiguration_assimilateSubParameters (
 LLRP_tSLinkConfiguration * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_LinkConfiguration_encode (
  const LLRP_tSLinkConfiguration *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_LinkConfiguration_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdLinkConfiguration_LinkID;

extern llrp_u8_t
LLRP_LinkConfiguration_getLinkID (
  LLRP_tSLinkConfiguration *pThis);

extern LLRP_tResultCode
LLRP_LinkConfiguration_setLinkID (
  LLRP_tSLinkConfiguration *pThis,
  llrp_u8_t Value);

  
extern LLRP_tSCommMode *
LLRP_LinkConfiguration_getCommMode (
  LLRP_tSLinkConfiguration *pThis);

extern LLRP_tResultCode
LLRP_LinkConfiguration_setCommMode (
  LLRP_tSLinkConfiguration *pThis,
  LLRP_tSCommMode *pValue);

extern LLRP_tSClientAddressConfiguration *
LLRP_LinkConfiguration_getClientAddressConfiguration (
  LLRP_tSLinkConfiguration *pThis);

extern LLRP_tResultCode
LLRP_LinkConfiguration_setClientAddressConfiguration (
  LLRP_tSLinkConfiguration *pThis,
  LLRP_tSClientAddressConfiguration *pValue);

extern LLRP_tSHostPortConfiguration *
LLRP_LinkConfiguration_getHostPortConfiguration (
  LLRP_tSLinkConfiguration *pThis);

extern LLRP_tResultCode
LLRP_LinkConfiguration_setHostPortConfiguration (
  LLRP_tSLinkConfiguration *pThis,
  LLRP_tSHostPortConfiguration *pValue);



  
struct LLRP_SCommMode
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t CommMode;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdCommMode;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdCommMode[];

extern LLRP_tSCommMode *
LLRP_CommMode_construct (void);

extern void
LLRP_CommMode_destruct (
 LLRP_tSCommMode * pThis);

extern void
LLRP_CommMode_decodeFields (
 LLRP_tSCommMode * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_CommMode_assimilateSubParameters (
 LLRP_tSCommMode * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_CommMode_encode (
  const LLRP_tSCommMode *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_CommMode_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdCommMode_CommMode;

extern llrp_u8_t
LLRP_CommMode_getCommMode (
  LLRP_tSCommMode *pThis);

extern LLRP_tResultCode
LLRP_CommMode_setCommMode (
  LLRP_tSCommMode *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SIsSingleton
{
    LLRP_tSParameter hdr;
  
    llrp_u1_t IsSingleton;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdIsSingleton;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdIsSingleton[];

extern LLRP_tSIsSingleton *
LLRP_IsSingleton_construct (void);

extern void
LLRP_IsSingleton_destruct (
 LLRP_tSIsSingleton * pThis);

extern void
LLRP_IsSingleton_decodeFields (
 LLRP_tSIsSingleton * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_IsSingleton_assimilateSubParameters (
 LLRP_tSIsSingleton * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_IsSingleton_encode (
  const LLRP_tSIsSingleton *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_IsSingleton_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdIsSingleton_IsSingleton;

extern llrp_u1_t
LLRP_IsSingleton_getIsSingleton (
  LLRP_tSIsSingleton *pThis);

extern LLRP_tResultCode
LLRP_IsSingleton_setIsSingleton (
  LLRP_tSIsSingleton *pThis,
  llrp_u1_t Value);

  


  
struct LLRP_SHostPortConfiguration
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t Port;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdHostPortConfiguration;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdHostPortConfiguration[];

extern LLRP_tSHostPortConfiguration *
LLRP_HostPortConfiguration_construct (void);

extern void
LLRP_HostPortConfiguration_destruct (
 LLRP_tSHostPortConfiguration * pThis);

extern void
LLRP_HostPortConfiguration_decodeFields (
 LLRP_tSHostPortConfiguration * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_HostPortConfiguration_assimilateSubParameters (
 LLRP_tSHostPortConfiguration * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_HostPortConfiguration_encode (
  const LLRP_tSHostPortConfiguration *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_HostPortConfiguration_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdHostPortConfiguration_Port;

extern llrp_u16_t
LLRP_HostPortConfiguration_getPort (
  LLRP_tSHostPortConfiguration *pThis);

extern LLRP_tResultCode
LLRP_HostPortConfiguration_setPort (
  LLRP_tSHostPortConfiguration *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_SLinkStateInfo
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t LinkID;

    llrp_u1_t IsActive;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdLinkStateInfo;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdLinkStateInfo[];

extern LLRP_tSLinkStateInfo *
LLRP_LinkStateInfo_construct (void);

extern void
LLRP_LinkStateInfo_destruct (
 LLRP_tSLinkStateInfo * pThis);

extern void
LLRP_LinkStateInfo_decodeFields (
 LLRP_tSLinkStateInfo * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_LinkStateInfo_assimilateSubParameters (
 LLRP_tSLinkStateInfo * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_LinkStateInfo_encode (
  const LLRP_tSLinkStateInfo *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_LinkStateInfo_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdLinkStateInfo_LinkID;

extern llrp_u8_t
LLRP_LinkStateInfo_getLinkID (
  LLRP_tSLinkStateInfo *pThis);

extern LLRP_tResultCode
LLRP_LinkStateInfo_setLinkID (
  LLRP_tSLinkStateInfo *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdLinkStateInfo_IsActive;

extern llrp_u1_t
LLRP_LinkStateInfo_getIsActive (
  LLRP_tSLinkStateInfo *pThis);

extern LLRP_tResultCode
LLRP_LinkStateInfo_setIsActive (
  LLRP_tSLinkStateInfo *pThis,
  llrp_u1_t Value);

  


  
struct LLRP_SSerialPortConfiguration
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t SerialPortType;

    llrp_u16_t SerialPortIndex;

    llrp_u16_t SerialAttributeIndex;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdSerialPortConfiguration;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSerialPortConfiguration[];

extern LLRP_tSSerialPortConfiguration *
LLRP_SerialPortConfiguration_construct (void);

extern void
LLRP_SerialPortConfiguration_destruct (
 LLRP_tSSerialPortConfiguration * pThis);

extern void
LLRP_SerialPortConfiguration_decodeFields (
 LLRP_tSSerialPortConfiguration * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SerialPortConfiguration_assimilateSubParameters (
 LLRP_tSSerialPortConfiguration * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SerialPortConfiguration_encode (
  const LLRP_tSSerialPortConfiguration *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_SerialPortConfiguration_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdSerialPortConfiguration_SerialPortType;

extern llrp_u8_t
LLRP_SerialPortConfiguration_getSerialPortType (
  LLRP_tSSerialPortConfiguration *pThis);

extern LLRP_tResultCode
LLRP_SerialPortConfiguration_setSerialPortType (
  LLRP_tSSerialPortConfiguration *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSerialPortConfiguration_SerialPortIndex;

extern llrp_u16_t
LLRP_SerialPortConfiguration_getSerialPortIndex (
  LLRP_tSSerialPortConfiguration *pThis);

extern LLRP_tResultCode
LLRP_SerialPortConfiguration_setSerialPortIndex (
  LLRP_tSSerialPortConfiguration *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSerialPortConfiguration_SerialAttributeIndex;

extern llrp_u16_t
LLRP_SerialPortConfiguration_getSerialAttributeIndex (
  LLRP_tSSerialPortConfiguration *pThis);

extern LLRP_tResultCode
LLRP_SerialPortConfiguration_setSerialAttributeIndex (
  LLRP_tSSerialPortConfiguration *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_STestItem
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t TestID;

  
    LLRP_tSParameter * pTestdata;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdTestItem;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdTestItem[];

extern LLRP_tSTestItem *
LLRP_TestItem_construct (void);

extern void
LLRP_TestItem_destruct (
 LLRP_tSTestItem * pThis);

extern void
LLRP_TestItem_decodeFields (
 LLRP_tSTestItem * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_TestItem_assimilateSubParameters (
 LLRP_tSTestItem * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_TestItem_encode (
  const LLRP_tSTestItem *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_TestItem_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdTestItem_TestID;

extern llrp_u16_t
LLRP_TestItem_getTestID (
  LLRP_tSTestItem *pThis);

extern LLRP_tResultCode
LLRP_TestItem_setTestID (
  LLRP_tSTestItem *pThis,
  llrp_u16_t Value);

  
extern LLRP_tSParameter *
LLRP_TestItem_getTestdata (
  LLRP_tSTestItem *pThis);

extern LLRP_tResultCode
LLRP_TestItem_setTestdata (
  LLRP_tSTestItem *pThis,
  LLRP_tSParameter *pValue);



  
struct LLRP_STestItemACK
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t ErrorCode;

    llrp_u16_t TestID;

  
    LLRP_tSParameter * pTestdataAck;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdTestItemACK;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdTestItemACK[];

extern LLRP_tSTestItemACK *
LLRP_TestItemACK_construct (void);

extern void
LLRP_TestItemACK_destruct (
 LLRP_tSTestItemACK * pThis);

extern void
LLRP_TestItemACK_decodeFields (
 LLRP_tSTestItemACK * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_TestItemACK_assimilateSubParameters (
 LLRP_tSTestItemACK * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_TestItemACK_encode (
  const LLRP_tSTestItemACK *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_TestItemACK_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdTestItemACK_ErrorCode;

extern llrp_u16_t
LLRP_TestItemACK_getErrorCode (
  LLRP_tSTestItemACK *pThis);

extern LLRP_tResultCode
LLRP_TestItemACK_setErrorCode (
  LLRP_tSTestItemACK *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdTestItemACK_TestID;

extern llrp_u16_t
LLRP_TestItemACK_getTestID (
  LLRP_tSTestItemACK *pThis);

extern LLRP_tResultCode
LLRP_TestItemACK_setTestID (
  LLRP_tSTestItemACK *pThis,
  llrp_u16_t Value);

  
extern LLRP_tSParameter *
LLRP_TestItemACK_getTestdataAck (
  LLRP_tSTestItemACK *pThis);

extern LLRP_tResultCode
LLRP_TestItemACK_setTestdataAck (
  LLRP_tSTestItemACK *pThis,
  LLRP_tSParameter *pValue);



  
struct LLRP_SGetK0ValueTestAck
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t K0ValueAnt1;

    llrp_u16_t K0ValueAnt2;

    llrp_u16_t K0ValueAnt3;

    llrp_u16_t K0ValueAnt4;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdGetK0ValueTestAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdGetK0ValueTestAck[];

extern LLRP_tSGetK0ValueTestAck *
LLRP_GetK0ValueTestAck_construct (void);

extern void
LLRP_GetK0ValueTestAck_destruct (
 LLRP_tSGetK0ValueTestAck * pThis);

extern void
LLRP_GetK0ValueTestAck_decodeFields (
 LLRP_tSGetK0ValueTestAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_GetK0ValueTestAck_assimilateSubParameters (
 LLRP_tSGetK0ValueTestAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_GetK0ValueTestAck_encode (
  const LLRP_tSGetK0ValueTestAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_GetK0ValueTestAck_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdGetK0ValueTestAck_K0ValueAnt1;

extern llrp_u16_t
LLRP_GetK0ValueTestAck_getK0ValueAnt1 (
  LLRP_tSGetK0ValueTestAck *pThis);

extern LLRP_tResultCode
LLRP_GetK0ValueTestAck_setK0ValueAnt1 (
  LLRP_tSGetK0ValueTestAck *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdGetK0ValueTestAck_K0ValueAnt2;

extern llrp_u16_t
LLRP_GetK0ValueTestAck_getK0ValueAnt2 (
  LLRP_tSGetK0ValueTestAck *pThis);

extern LLRP_tResultCode
LLRP_GetK0ValueTestAck_setK0ValueAnt2 (
  LLRP_tSGetK0ValueTestAck *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdGetK0ValueTestAck_K0ValueAnt3;

extern llrp_u16_t
LLRP_GetK0ValueTestAck_getK0ValueAnt3 (
  LLRP_tSGetK0ValueTestAck *pThis);

extern LLRP_tResultCode
LLRP_GetK0ValueTestAck_setK0ValueAnt3 (
  LLRP_tSGetK0ValueTestAck *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdGetK0ValueTestAck_K0ValueAnt4;

extern llrp_u16_t
LLRP_GetK0ValueTestAck_getK0ValueAnt4 (
  LLRP_tSGetK0ValueTestAck *pThis);

extern LLRP_tResultCode
LLRP_GetK0ValueTestAck_setK0ValueAnt4 (
  LLRP_tSGetK0ValueTestAck *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_SGetDATTTestAck
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t FPCDATTValueAnt1;

    llrp_u16_t FPCDATTValueAnt2;

    llrp_u16_t FPCDATTValueAnt3;

    llrp_u16_t FPCDATTValueAnt4;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdGetDATTTestAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdGetDATTTestAck[];

extern LLRP_tSGetDATTTestAck *
LLRP_GetDATTTestAck_construct (void);

extern void
LLRP_GetDATTTestAck_destruct (
 LLRP_tSGetDATTTestAck * pThis);

extern void
LLRP_GetDATTTestAck_decodeFields (
 LLRP_tSGetDATTTestAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_GetDATTTestAck_assimilateSubParameters (
 LLRP_tSGetDATTTestAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_GetDATTTestAck_encode (
  const LLRP_tSGetDATTTestAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_GetDATTTestAck_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdGetDATTTestAck_FPCDATTValueAnt1;

extern llrp_u16_t
LLRP_GetDATTTestAck_getFPCDATTValueAnt1 (
  LLRP_tSGetDATTTestAck *pThis);

extern LLRP_tResultCode
LLRP_GetDATTTestAck_setFPCDATTValueAnt1 (
  LLRP_tSGetDATTTestAck *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdGetDATTTestAck_FPCDATTValueAnt2;

extern llrp_u16_t
LLRP_GetDATTTestAck_getFPCDATTValueAnt2 (
  LLRP_tSGetDATTTestAck *pThis);

extern LLRP_tResultCode
LLRP_GetDATTTestAck_setFPCDATTValueAnt2 (
  LLRP_tSGetDATTTestAck *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdGetDATTTestAck_FPCDATTValueAnt3;

extern llrp_u16_t
LLRP_GetDATTTestAck_getFPCDATTValueAnt3 (
  LLRP_tSGetDATTTestAck *pThis);

extern LLRP_tResultCode
LLRP_GetDATTTestAck_setFPCDATTValueAnt3 (
  LLRP_tSGetDATTTestAck *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdGetDATTTestAck_FPCDATTValueAnt4;

extern llrp_u16_t
LLRP_GetDATTTestAck_getFPCDATTValueAnt4 (
  LLRP_tSGetDATTTestAck *pThis);

extern LLRP_tResultCode
LLRP_GetDATTTestAck_setFPCDATTValueAnt4 (
  LLRP_tSGetDATTTestAck *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_SPSAMTest
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t SAMCardNum;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdPSAMTest;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdPSAMTest[];

extern LLRP_tSPSAMTest *
LLRP_PSAMTest_construct (void);

extern void
LLRP_PSAMTest_destruct (
 LLRP_tSPSAMTest * pThis);

extern void
LLRP_PSAMTest_decodeFields (
 LLRP_tSPSAMTest * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_PSAMTest_assimilateSubParameters (
 LLRP_tSPSAMTest * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_PSAMTest_encode (
  const LLRP_tSPSAMTest *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_PSAMTest_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdPSAMTest_SAMCardNum;

extern llrp_u8_t
LLRP_PSAMTest_getSAMCardNum (
  LLRP_tSPSAMTest *pThis);

extern LLRP_tResultCode
LLRP_PSAMTest_setSAMCardNum (
  LLRP_tSPSAMTest *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SPSAMTestAck
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t SAMCardNum;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdPSAMTestAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdPSAMTestAck[];

extern LLRP_tSPSAMTestAck *
LLRP_PSAMTestAck_construct (void);

extern void
LLRP_PSAMTestAck_destruct (
 LLRP_tSPSAMTestAck * pThis);

extern void
LLRP_PSAMTestAck_decodeFields (
 LLRP_tSPSAMTestAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_PSAMTestAck_assimilateSubParameters (
 LLRP_tSPSAMTestAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_PSAMTestAck_encode (
  const LLRP_tSPSAMTestAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_PSAMTestAck_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdPSAMTestAck_SAMCardNum;

extern llrp_u8_t
LLRP_PSAMTestAck_getSAMCardNum (
  LLRP_tSPSAMTestAck *pThis);

extern LLRP_tResultCode
LLRP_PSAMTestAck_setSAMCardNum (
  LLRP_tSPSAMTestAck *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SFPGARWTestACK
{
    LLRP_tSParameter hdr;
  
    llrp_u32_t FpgaStatus;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdFPGARWTestACK;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdFPGARWTestACK[];

extern LLRP_tSFPGARWTestACK *
LLRP_FPGARWTestACK_construct (void);

extern void
LLRP_FPGARWTestACK_destruct (
 LLRP_tSFPGARWTestACK * pThis);

extern void
LLRP_FPGARWTestACK_decodeFields (
 LLRP_tSFPGARWTestACK * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_FPGARWTestACK_assimilateSubParameters (
 LLRP_tSFPGARWTestACK * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_FPGARWTestACK_encode (
  const LLRP_tSFPGARWTestACK *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_FPGARWTestACK_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdFPGARWTestACK_FpgaStatus;

extern llrp_u32_t
LLRP_FPGARWTestACK_getFpgaStatus (
  LLRP_tSFPGARWTestACK *pThis);

extern LLRP_tResultCode
LLRP_FPGARWTestACK_setFpgaStatus (
  LLRP_tSFPGARWTestACK *pThis,
  llrp_u32_t Value);

  


  
struct LLRP_SGPRSCommTest
{
    LLRP_tSParameter hdr;
  
    llrp_u32_t RemoteIP;

    llrp_u8_t SendedPacket;

    llrp_u8_t DialRetry;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdGPRSCommTest;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdGPRSCommTest[];

extern LLRP_tSGPRSCommTest *
LLRP_GPRSCommTest_construct (void);

extern void
LLRP_GPRSCommTest_destruct (
 LLRP_tSGPRSCommTest * pThis);

extern void
LLRP_GPRSCommTest_decodeFields (
 LLRP_tSGPRSCommTest * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_GPRSCommTest_assimilateSubParameters (
 LLRP_tSGPRSCommTest * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_GPRSCommTest_encode (
  const LLRP_tSGPRSCommTest *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_GPRSCommTest_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdGPRSCommTest_RemoteIP;

extern llrp_u32_t
LLRP_GPRSCommTest_getRemoteIP (
  LLRP_tSGPRSCommTest *pThis);

extern LLRP_tResultCode
LLRP_GPRSCommTest_setRemoteIP (
  LLRP_tSGPRSCommTest *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdGPRSCommTest_SendedPacket;

extern llrp_u8_t
LLRP_GPRSCommTest_getSendedPacket (
  LLRP_tSGPRSCommTest *pThis);

extern LLRP_tResultCode
LLRP_GPRSCommTest_setSendedPacket (
  LLRP_tSGPRSCommTest *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdGPRSCommTest_DialRetry;

extern llrp_u8_t
LLRP_GPRSCommTest_getDialRetry (
  LLRP_tSGPRSCommTest *pThis);

extern LLRP_tResultCode
LLRP_GPRSCommTest_setDialRetry (
  LLRP_tSGPRSCommTest *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SGPRSCommTestAck
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t PPPDial;

    llrp_u8_t ReceivedPacket;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdGPRSCommTestAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdGPRSCommTestAck[];

extern LLRP_tSGPRSCommTestAck *
LLRP_GPRSCommTestAck_construct (void);

extern void
LLRP_GPRSCommTestAck_destruct (
 LLRP_tSGPRSCommTestAck * pThis);

extern void
LLRP_GPRSCommTestAck_decodeFields (
 LLRP_tSGPRSCommTestAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_GPRSCommTestAck_assimilateSubParameters (
 LLRP_tSGPRSCommTestAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_GPRSCommTestAck_encode (
  const LLRP_tSGPRSCommTestAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_GPRSCommTestAck_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdGPRSCommTestAck_PPPDial;

extern llrp_u8_t
LLRP_GPRSCommTestAck_getPPPDial (
  LLRP_tSGPRSCommTestAck *pThis);

extern LLRP_tResultCode
LLRP_GPRSCommTestAck_setPPPDial (
  LLRP_tSGPRSCommTestAck *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdGPRSCommTestAck_ReceivedPacket;

extern llrp_u8_t
LLRP_GPRSCommTestAck_getReceivedPacket (
  LLRP_tSGPRSCommTestAck *pThis);

extern LLRP_tResultCode
LLRP_GPRSCommTestAck_setReceivedPacket (
  LLRP_tSGPRSCommTestAck *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_STemperatureQueryTest
{
    LLRP_tSParameter hdr;
  
  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdTemperatureQueryTest;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdTemperatureQueryTest[];

extern LLRP_tSTemperatureQueryTest *
LLRP_TemperatureQueryTest_construct (void);

extern void
LLRP_TemperatureQueryTest_destruct (
 LLRP_tSTemperatureQueryTest * pThis);

extern void
LLRP_TemperatureQueryTest_decodeFields (
 LLRP_tSTemperatureQueryTest * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_TemperatureQueryTest_assimilateSubParameters (
 LLRP_tSTemperatureQueryTest * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_TemperatureQueryTest_encode (
  const LLRP_tSTemperatureQueryTest *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_TemperatureQueryTest_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
  


  
struct LLRP_STemperatureQueryTestAck
{
    LLRP_tSParameter hdr;
  
    llrp_s8_t CPUTempValue;

    llrp_s8_t CPUBoardTempValue;

    llrp_s8_t AmplifierTempValue;

    llrp_s8_t AmplifierBoardTempValue;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdTemperatureQueryTestAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdTemperatureQueryTestAck[];

extern LLRP_tSTemperatureQueryTestAck *
LLRP_TemperatureQueryTestAck_construct (void);

extern void
LLRP_TemperatureQueryTestAck_destruct (
 LLRP_tSTemperatureQueryTestAck * pThis);

extern void
LLRP_TemperatureQueryTestAck_decodeFields (
 LLRP_tSTemperatureQueryTestAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_TemperatureQueryTestAck_assimilateSubParameters (
 LLRP_tSTemperatureQueryTestAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_TemperatureQueryTestAck_encode (
  const LLRP_tSTemperatureQueryTestAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_TemperatureQueryTestAck_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdTemperatureQueryTestAck_CPUTempValue;

extern llrp_s8_t
LLRP_TemperatureQueryTestAck_getCPUTempValue (
  LLRP_tSTemperatureQueryTestAck *pThis);

extern LLRP_tResultCode
LLRP_TemperatureQueryTestAck_setCPUTempValue (
  LLRP_tSTemperatureQueryTestAck *pThis,
  llrp_s8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdTemperatureQueryTestAck_CPUBoardTempValue;

extern llrp_s8_t
LLRP_TemperatureQueryTestAck_getCPUBoardTempValue (
  LLRP_tSTemperatureQueryTestAck *pThis);

extern LLRP_tResultCode
LLRP_TemperatureQueryTestAck_setCPUBoardTempValue (
  LLRP_tSTemperatureQueryTestAck *pThis,
  llrp_s8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdTemperatureQueryTestAck_AmplifierTempValue;

extern llrp_s8_t
LLRP_TemperatureQueryTestAck_getAmplifierTempValue (
  LLRP_tSTemperatureQueryTestAck *pThis);

extern LLRP_tResultCode
LLRP_TemperatureQueryTestAck_setAmplifierTempValue (
  LLRP_tSTemperatureQueryTestAck *pThis,
  llrp_s8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdTemperatureQueryTestAck_AmplifierBoardTempValue;

extern llrp_s8_t
LLRP_TemperatureQueryTestAck_getAmplifierBoardTempValue (
  LLRP_tSTemperatureQueryTestAck *pThis);

extern LLRP_tResultCode
LLRP_TemperatureQueryTestAck_setAmplifierBoardTempValue (
  LLRP_tSTemperatureQueryTestAck *pThis,
  llrp_s8_t Value);

  


  
struct LLRP_SHardwareVersionQueryTest
{
    LLRP_tSParameter hdr;
  
  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdHardwareVersionQueryTest;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdHardwareVersionQueryTest[];

extern LLRP_tSHardwareVersionQueryTest *
LLRP_HardwareVersionQueryTest_construct (void);

extern void
LLRP_HardwareVersionQueryTest_destruct (
 LLRP_tSHardwareVersionQueryTest * pThis);

extern void
LLRP_HardwareVersionQueryTest_decodeFields (
 LLRP_tSHardwareVersionQueryTest * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_HardwareVersionQueryTest_assimilateSubParameters (
 LLRP_tSHardwareVersionQueryTest * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_HardwareVersionQueryTest_encode (
  const LLRP_tSHardwareVersionQueryTest *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_HardwareVersionQueryTest_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
  


  
struct LLRP_SHardwareVersionQueryTestAck
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t RBCB0_TYPE;

    llrp_u8_t RBCB0_VERSION;

    llrp_u8_t RFCB0_TYPE;

    llrp_u8_t RFCB0_VERSION;

    llrp_u8_t PSIB_TYPE;

    llrp_u8_t PSIB_VERSION;

    llrp_u8_t RWCB_TYPE;

    llrp_u8_t RWCB_VERSION;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdHardwareVersionQueryTestAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdHardwareVersionQueryTestAck[];

extern LLRP_tSHardwareVersionQueryTestAck *
LLRP_HardwareVersionQueryTestAck_construct (void);

extern void
LLRP_HardwareVersionQueryTestAck_destruct (
 LLRP_tSHardwareVersionQueryTestAck * pThis);

extern void
LLRP_HardwareVersionQueryTestAck_decodeFields (
 LLRP_tSHardwareVersionQueryTestAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_HardwareVersionQueryTestAck_assimilateSubParameters (
 LLRP_tSHardwareVersionQueryTestAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_HardwareVersionQueryTestAck_encode (
  const LLRP_tSHardwareVersionQueryTestAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_HardwareVersionQueryTestAck_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdHardwareVersionQueryTestAck_RBCB0_TYPE;

extern llrp_u8_t
LLRP_HardwareVersionQueryTestAck_getRBCB0_TYPE (
  LLRP_tSHardwareVersionQueryTestAck *pThis);

extern LLRP_tResultCode
LLRP_HardwareVersionQueryTestAck_setRBCB0_TYPE (
  LLRP_tSHardwareVersionQueryTestAck *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdHardwareVersionQueryTestAck_RBCB0_VERSION;

extern llrp_u8_t
LLRP_HardwareVersionQueryTestAck_getRBCB0_VERSION (
  LLRP_tSHardwareVersionQueryTestAck *pThis);

extern LLRP_tResultCode
LLRP_HardwareVersionQueryTestAck_setRBCB0_VERSION (
  LLRP_tSHardwareVersionQueryTestAck *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdHardwareVersionQueryTestAck_RFCB0_TYPE;

extern llrp_u8_t
LLRP_HardwareVersionQueryTestAck_getRFCB0_TYPE (
  LLRP_tSHardwareVersionQueryTestAck *pThis);

extern LLRP_tResultCode
LLRP_HardwareVersionQueryTestAck_setRFCB0_TYPE (
  LLRP_tSHardwareVersionQueryTestAck *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdHardwareVersionQueryTestAck_RFCB0_VERSION;

extern llrp_u8_t
LLRP_HardwareVersionQueryTestAck_getRFCB0_VERSION (
  LLRP_tSHardwareVersionQueryTestAck *pThis);

extern LLRP_tResultCode
LLRP_HardwareVersionQueryTestAck_setRFCB0_VERSION (
  LLRP_tSHardwareVersionQueryTestAck *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdHardwareVersionQueryTestAck_PSIB_TYPE;

extern llrp_u8_t
LLRP_HardwareVersionQueryTestAck_getPSIB_TYPE (
  LLRP_tSHardwareVersionQueryTestAck *pThis);

extern LLRP_tResultCode
LLRP_HardwareVersionQueryTestAck_setPSIB_TYPE (
  LLRP_tSHardwareVersionQueryTestAck *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdHardwareVersionQueryTestAck_PSIB_VERSION;

extern llrp_u8_t
LLRP_HardwareVersionQueryTestAck_getPSIB_VERSION (
  LLRP_tSHardwareVersionQueryTestAck *pThis);

extern LLRP_tResultCode
LLRP_HardwareVersionQueryTestAck_setPSIB_VERSION (
  LLRP_tSHardwareVersionQueryTestAck *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdHardwareVersionQueryTestAck_RWCB_TYPE;

extern llrp_u8_t
LLRP_HardwareVersionQueryTestAck_getRWCB_TYPE (
  LLRP_tSHardwareVersionQueryTestAck *pThis);

extern LLRP_tResultCode
LLRP_HardwareVersionQueryTestAck_setRWCB_TYPE (
  LLRP_tSHardwareVersionQueryTestAck *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdHardwareVersionQueryTestAck_RWCB_VERSION;

extern llrp_u8_t
LLRP_HardwareVersionQueryTestAck_getRWCB_VERSION (
  LLRP_tSHardwareVersionQueryTestAck *pThis);

extern LLRP_tResultCode
LLRP_HardwareVersionQueryTestAck_setRWCB_VERSION (
  LLRP_tSHardwareVersionQueryTestAck *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SQueryLinkStatus
{
    LLRP_tSParameter hdr;
  
  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdQueryLinkStatus;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdQueryLinkStatus[];

extern LLRP_tSQueryLinkStatus *
LLRP_QueryLinkStatus_construct (void);

extern void
LLRP_QueryLinkStatus_destruct (
 LLRP_tSQueryLinkStatus * pThis);

extern void
LLRP_QueryLinkStatus_decodeFields (
 LLRP_tSQueryLinkStatus * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_QueryLinkStatus_assimilateSubParameters (
 LLRP_tSQueryLinkStatus * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_QueryLinkStatus_encode (
  const LLRP_tSQueryLinkStatus *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_QueryLinkStatus_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
  


  
struct LLRP_SQueryLinkStatusReqAck
{
    LLRP_tSParameter hdr;
  
    llrp_u32_t LinkNum;

  
    LLRP_tSCommLinkStatus * listCommLinkStatus;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdQueryLinkStatusReqAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdQueryLinkStatusReqAck[];

extern LLRP_tSQueryLinkStatusReqAck *
LLRP_QueryLinkStatusReqAck_construct (void);

extern void
LLRP_QueryLinkStatusReqAck_destruct (
 LLRP_tSQueryLinkStatusReqAck * pThis);

extern void
LLRP_QueryLinkStatusReqAck_decodeFields (
 LLRP_tSQueryLinkStatusReqAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_QueryLinkStatusReqAck_assimilateSubParameters (
 LLRP_tSQueryLinkStatusReqAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_QueryLinkStatusReqAck_encode (
  const LLRP_tSQueryLinkStatusReqAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_QueryLinkStatusReqAck_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdQueryLinkStatusReqAck_LinkNum;

extern llrp_u32_t
LLRP_QueryLinkStatusReqAck_getLinkNum (
  LLRP_tSQueryLinkStatusReqAck *pThis);

extern LLRP_tResultCode
LLRP_QueryLinkStatusReqAck_setLinkNum (
  LLRP_tSQueryLinkStatusReqAck *pThis,
  llrp_u32_t Value);

  
extern LLRP_tSCommLinkStatus *
LLRP_QueryLinkStatusReqAck_beginCommLinkStatus (
  LLRP_tSQueryLinkStatusReqAck *pThis);

extern LLRP_tSCommLinkStatus *
LLRP_QueryLinkStatusReqAck_nextCommLinkStatus (
  LLRP_tSCommLinkStatus *pCurrent);

extern void
LLRP_QueryLinkStatusReqAck_clearCommLinkStatus (
  LLRP_tSQueryLinkStatusReqAck *pThis);

extern LLRP_tResultCode
LLRP_QueryLinkStatusReqAck_addCommLinkStatus (
  LLRP_tSQueryLinkStatusReqAck *pThis,
  LLRP_tSCommLinkStatus *pValue);




  
struct LLRP_SRUPHardwareVersionQueryTestACK
{
    LLRP_tSParameter hdr;
  
  
    LLRP_tSRUPBoradInfo * listRUPBoradInfo;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdRUPHardwareVersionQueryTestACK;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdRUPHardwareVersionQueryTestACK[];

extern LLRP_tSRUPHardwareVersionQueryTestACK *
LLRP_RUPHardwareVersionQueryTestACK_construct (void);

extern void
LLRP_RUPHardwareVersionQueryTestACK_destruct (
 LLRP_tSRUPHardwareVersionQueryTestACK * pThis);

extern void
LLRP_RUPHardwareVersionQueryTestACK_decodeFields (
 LLRP_tSRUPHardwareVersionQueryTestACK * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_RUPHardwareVersionQueryTestACK_assimilateSubParameters (
 LLRP_tSRUPHardwareVersionQueryTestACK * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_RUPHardwareVersionQueryTestACK_encode (
  const LLRP_tSRUPHardwareVersionQueryTestACK *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_RUPHardwareVersionQueryTestACK_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
  
extern LLRP_tSRUPBoradInfo *
LLRP_RUPHardwareVersionQueryTestACK_beginRUPBoradInfo (
  LLRP_tSRUPHardwareVersionQueryTestACK *pThis);

extern LLRP_tSRUPBoradInfo *
LLRP_RUPHardwareVersionQueryTestACK_nextRUPBoradInfo (
  LLRP_tSRUPBoradInfo *pCurrent);

extern void
LLRP_RUPHardwareVersionQueryTestACK_clearRUPBoradInfo (
  LLRP_tSRUPHardwareVersionQueryTestACK *pThis);

extern LLRP_tResultCode
LLRP_RUPHardwareVersionQueryTestACK_addRUPBoradInfo (
  LLRP_tSRUPHardwareVersionQueryTestACK *pThis,
  LLRP_tSRUPBoradInfo *pValue);




  
struct LLRP_SRUPBoradInfo
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t BoardGlobalType;

    llrp_u8_t BoardType;

    llrp_u8_t BoardVer;

    llrp_u8_t BoardID;

    llrp_utf8v_t BoardDescribe;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdRUPBoradInfo;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdRUPBoradInfo[];

extern LLRP_tSRUPBoradInfo *
LLRP_RUPBoradInfo_construct (void);

extern void
LLRP_RUPBoradInfo_destruct (
 LLRP_tSRUPBoradInfo * pThis);

extern void
LLRP_RUPBoradInfo_decodeFields (
 LLRP_tSRUPBoradInfo * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_RUPBoradInfo_assimilateSubParameters (
 LLRP_tSRUPBoradInfo * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_RUPBoradInfo_encode (
  const LLRP_tSRUPBoradInfo *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_RUPBoradInfo_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdRUPBoradInfo_BoardGlobalType;

extern llrp_u8_t
LLRP_RUPBoradInfo_getBoardGlobalType (
  LLRP_tSRUPBoradInfo *pThis);

extern LLRP_tResultCode
LLRP_RUPBoradInfo_setBoardGlobalType (
  LLRP_tSRUPBoradInfo *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdRUPBoradInfo_BoardType;

extern llrp_u8_t
LLRP_RUPBoradInfo_getBoardType (
  LLRP_tSRUPBoradInfo *pThis);

extern LLRP_tResultCode
LLRP_RUPBoradInfo_setBoardType (
  LLRP_tSRUPBoradInfo *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdRUPBoradInfo_BoardVer;

extern llrp_u8_t
LLRP_RUPBoradInfo_getBoardVer (
  LLRP_tSRUPBoradInfo *pThis);

extern LLRP_tResultCode
LLRP_RUPBoradInfo_setBoardVer (
  LLRP_tSRUPBoradInfo *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdRUPBoradInfo_BoardID;

extern llrp_u8_t
LLRP_RUPBoradInfo_getBoardID (
  LLRP_tSRUPBoradInfo *pThis);

extern LLRP_tResultCode
LLRP_RUPBoradInfo_setBoardID (
  LLRP_tSRUPBoradInfo *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdRUPBoradInfo_BoardDescribe;

extern llrp_utf8v_t
LLRP_RUPBoradInfo_getBoardDescribe (
  LLRP_tSRUPBoradInfo *pThis);

extern LLRP_tResultCode
LLRP_RUPBoradInfo_setBoardDescribe (
  LLRP_tSRUPBoradInfo *pThis,
  llrp_utf8v_t Value);

  


  
struct LLRP_SRUPQueryLinkStatusReqAck
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t LinkNum;

  
    LLRP_tSCommLinkStatus * listCommLinkStatus;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdRUPQueryLinkStatusReqAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdRUPQueryLinkStatusReqAck[];

extern LLRP_tSRUPQueryLinkStatusReqAck *
LLRP_RUPQueryLinkStatusReqAck_construct (void);

extern void
LLRP_RUPQueryLinkStatusReqAck_destruct (
 LLRP_tSRUPQueryLinkStatusReqAck * pThis);

extern void
LLRP_RUPQueryLinkStatusReqAck_decodeFields (
 LLRP_tSRUPQueryLinkStatusReqAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_RUPQueryLinkStatusReqAck_assimilateSubParameters (
 LLRP_tSRUPQueryLinkStatusReqAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_RUPQueryLinkStatusReqAck_encode (
  const LLRP_tSRUPQueryLinkStatusReqAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_RUPQueryLinkStatusReqAck_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdRUPQueryLinkStatusReqAck_LinkNum;

extern llrp_u8_t
LLRP_RUPQueryLinkStatusReqAck_getLinkNum (
  LLRP_tSRUPQueryLinkStatusReqAck *pThis);

extern LLRP_tResultCode
LLRP_RUPQueryLinkStatusReqAck_setLinkNum (
  LLRP_tSRUPQueryLinkStatusReqAck *pThis,
  llrp_u8_t Value);

  
extern LLRP_tSCommLinkStatus *
LLRP_RUPQueryLinkStatusReqAck_beginCommLinkStatus (
  LLRP_tSRUPQueryLinkStatusReqAck *pThis);

extern LLRP_tSCommLinkStatus *
LLRP_RUPQueryLinkStatusReqAck_nextCommLinkStatus (
  LLRP_tSCommLinkStatus *pCurrent);

extern void
LLRP_RUPQueryLinkStatusReqAck_clearCommLinkStatus (
  LLRP_tSRUPQueryLinkStatusReqAck *pThis);

extern LLRP_tResultCode
LLRP_RUPQueryLinkStatusReqAck_addCommLinkStatus (
  LLRP_tSRUPQueryLinkStatusReqAck *pThis,
  LLRP_tSCommLinkStatus *pValue);




  
struct LLRP_SCommLinkStatus
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t LinkType;

    llrp_u8_t LinkIndex;

  
    LLRP_tSCommLinkDesc * pCommLinkDesc;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdCommLinkStatus;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdCommLinkStatus[];

extern LLRP_tSCommLinkStatus *
LLRP_CommLinkStatus_construct (void);

extern void
LLRP_CommLinkStatus_destruct (
 LLRP_tSCommLinkStatus * pThis);

extern void
LLRP_CommLinkStatus_decodeFields (
 LLRP_tSCommLinkStatus * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_CommLinkStatus_assimilateSubParameters (
 LLRP_tSCommLinkStatus * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_CommLinkStatus_encode (
  const LLRP_tSCommLinkStatus *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_CommLinkStatus_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdCommLinkStatus_LinkType;

extern llrp_u8_t
LLRP_CommLinkStatus_getLinkType (
  LLRP_tSCommLinkStatus *pThis);

extern LLRP_tResultCode
LLRP_CommLinkStatus_setLinkType (
  LLRP_tSCommLinkStatus *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdCommLinkStatus_LinkIndex;

extern llrp_u8_t
LLRP_CommLinkStatus_getLinkIndex (
  LLRP_tSCommLinkStatus *pThis);

extern LLRP_tResultCode
LLRP_CommLinkStatus_setLinkIndex (
  LLRP_tSCommLinkStatus *pThis,
  llrp_u8_t Value);

  
extern LLRP_tSCommLinkDesc *
LLRP_CommLinkStatus_getCommLinkDesc (
  LLRP_tSCommLinkStatus *pThis);

extern LLRP_tResultCode
LLRP_CommLinkStatus_setCommLinkDesc (
  LLRP_tSCommLinkStatus *pThis,
  LLRP_tSCommLinkDesc *pValue);



  
struct LLRP_SCommLinkDesc
{
    LLRP_tSParameter hdr;
  
  
    LLRP_tSCommSocket * pCommSocket;

    LLRP_tSCommSerialPort * pCommSerialPort;

    LLRP_tSCommWiegand * pCommWiegand;

    LLRP_tSCommGprs * pCommGprs;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdCommLinkDesc;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdCommLinkDesc[];

extern LLRP_tSCommLinkDesc *
LLRP_CommLinkDesc_construct (void);

extern void
LLRP_CommLinkDesc_destruct (
 LLRP_tSCommLinkDesc * pThis);

extern void
LLRP_CommLinkDesc_decodeFields (
 LLRP_tSCommLinkDesc * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_CommLinkDesc_assimilateSubParameters (
 LLRP_tSCommLinkDesc * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_CommLinkDesc_encode (
  const LLRP_tSCommLinkDesc *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_CommLinkDesc_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
  
extern LLRP_tSCommSocket *
LLRP_CommLinkDesc_getCommSocket (
  LLRP_tSCommLinkDesc *pThis);

extern LLRP_tResultCode
LLRP_CommLinkDesc_setCommSocket (
  LLRP_tSCommLinkDesc *pThis,
  LLRP_tSCommSocket *pValue);

extern LLRP_tSCommSerialPort *
LLRP_CommLinkDesc_getCommSerialPort (
  LLRP_tSCommLinkDesc *pThis);

extern LLRP_tResultCode
LLRP_CommLinkDesc_setCommSerialPort (
  LLRP_tSCommLinkDesc *pThis,
  LLRP_tSCommSerialPort *pValue);

extern LLRP_tSCommWiegand *
LLRP_CommLinkDesc_getCommWiegand (
  LLRP_tSCommLinkDesc *pThis);

extern LLRP_tResultCode
LLRP_CommLinkDesc_setCommWiegand (
  LLRP_tSCommLinkDesc *pThis,
  LLRP_tSCommWiegand *pValue);

extern LLRP_tSCommGprs *
LLRP_CommLinkDesc_getCommGprs (
  LLRP_tSCommLinkDesc *pThis);

extern LLRP_tResultCode
LLRP_CommLinkDesc_setCommGprs (
  LLRP_tSCommLinkDesc *pThis,
  LLRP_tSCommGprs *pValue);



  
struct LLRP_SPsamStatusReadAck
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t dwPsam0;

    llrp_u8_t dwPsam1;

    llrp_u8_t dwPsam2;

    llrp_u8_t dwPsam3;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdPsamStatusReadAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdPsamStatusReadAck[];

extern LLRP_tSPsamStatusReadAck *
LLRP_PsamStatusReadAck_construct (void);

extern void
LLRP_PsamStatusReadAck_destruct (
 LLRP_tSPsamStatusReadAck * pThis);

extern void
LLRP_PsamStatusReadAck_decodeFields (
 LLRP_tSPsamStatusReadAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_PsamStatusReadAck_assimilateSubParameters (
 LLRP_tSPsamStatusReadAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_PsamStatusReadAck_encode (
  const LLRP_tSPsamStatusReadAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_PsamStatusReadAck_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdPsamStatusReadAck_dwPsam0;

extern llrp_u8_t
LLRP_PsamStatusReadAck_getdwPsam0 (
  LLRP_tSPsamStatusReadAck *pThis);

extern LLRP_tResultCode
LLRP_PsamStatusReadAck_setdwPsam0 (
  LLRP_tSPsamStatusReadAck *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdPsamStatusReadAck_dwPsam1;

extern llrp_u8_t
LLRP_PsamStatusReadAck_getdwPsam1 (
  LLRP_tSPsamStatusReadAck *pThis);

extern LLRP_tResultCode
LLRP_PsamStatusReadAck_setdwPsam1 (
  LLRP_tSPsamStatusReadAck *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdPsamStatusReadAck_dwPsam2;

extern llrp_u8_t
LLRP_PsamStatusReadAck_getdwPsam2 (
  LLRP_tSPsamStatusReadAck *pThis);

extern LLRP_tResultCode
LLRP_PsamStatusReadAck_setdwPsam2 (
  LLRP_tSPsamStatusReadAck *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdPsamStatusReadAck_dwPsam3;

extern llrp_u8_t
LLRP_PsamStatusReadAck_getdwPsam3 (
  LLRP_tSPsamStatusReadAck *pThis);

extern LLRP_tResultCode
LLRP_PsamStatusReadAck_setdwPsam3 (
  LLRP_tSPsamStatusReadAck *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SGPRSmoduleTest
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t ucResult;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdGPRSmoduleTest;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdGPRSmoduleTest[];

extern LLRP_tSGPRSmoduleTest *
LLRP_GPRSmoduleTest_construct (void);

extern void
LLRP_GPRSmoduleTest_destruct (
 LLRP_tSGPRSmoduleTest * pThis);

extern void
LLRP_GPRSmoduleTest_decodeFields (
 LLRP_tSGPRSmoduleTest * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_GPRSmoduleTest_assimilateSubParameters (
 LLRP_tSGPRSmoduleTest * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_GPRSmoduleTest_encode (
  const LLRP_tSGPRSmoduleTest *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_GPRSmoduleTest_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdGPRSmoduleTest_ucResult;

extern llrp_u8_t
LLRP_GPRSmoduleTest_getucResult (
  LLRP_tSGPRSmoduleTest *pThis);

extern LLRP_tResultCode
LLRP_GPRSmoduleTest_setucResult (
  LLRP_tSGPRSmoduleTest *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SGPRSSignalQualityTest
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t ucResult;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdGPRSSignalQualityTest;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdGPRSSignalQualityTest[];

extern LLRP_tSGPRSSignalQualityTest *
LLRP_GPRSSignalQualityTest_construct (void);

extern void
LLRP_GPRSSignalQualityTest_destruct (
 LLRP_tSGPRSSignalQualityTest * pThis);

extern void
LLRP_GPRSSignalQualityTest_decodeFields (
 LLRP_tSGPRSSignalQualityTest * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_GPRSSignalQualityTest_assimilateSubParameters (
 LLRP_tSGPRSSignalQualityTest * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_GPRSSignalQualityTest_encode (
  const LLRP_tSGPRSSignalQualityTest *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_GPRSSignalQualityTest_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdGPRSSignalQualityTest_ucResult;

extern llrp_u8_t
LLRP_GPRSSignalQualityTest_getucResult (
  LLRP_tSGPRSSignalQualityTest *pThis);

extern LLRP_tResultCode
LLRP_GPRSSignalQualityTest_setucResult (
  LLRP_tSGPRSSignalQualityTest *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SC0ReadAck
{
    LLRP_tSParameter hdr;
  
    llrp_u8v_t Seconds;

    llrp_u8v_t Datetime;

    llrp_u8_t LaneMode;

    llrp_u8_t WaitTime;

    llrp_u8_t TxPower;

    llrp_u8_t PLLChannelID;

    llrp_u8_t BSTInterval;

    llrp_u8_t TransClass;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdC0ReadAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdC0ReadAck[];

extern LLRP_tSC0ReadAck *
LLRP_C0ReadAck_construct (void);

extern void
LLRP_C0ReadAck_destruct (
 LLRP_tSC0ReadAck * pThis);

extern void
LLRP_C0ReadAck_decodeFields (
 LLRP_tSC0ReadAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_C0ReadAck_assimilateSubParameters (
 LLRP_tSC0ReadAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_C0ReadAck_encode (
  const LLRP_tSC0ReadAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_C0ReadAck_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdC0ReadAck_Seconds;

extern llrp_u8v_t
LLRP_C0ReadAck_getSeconds (
  LLRP_tSC0ReadAck *pThis);

extern LLRP_tResultCode
LLRP_C0ReadAck_setSeconds (
  LLRP_tSC0ReadAck *pThis,
  llrp_u8v_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdC0ReadAck_Datetime;

extern llrp_u8v_t
LLRP_C0ReadAck_getDatetime (
  LLRP_tSC0ReadAck *pThis);

extern LLRP_tResultCode
LLRP_C0ReadAck_setDatetime (
  LLRP_tSC0ReadAck *pThis,
  llrp_u8v_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdC0ReadAck_LaneMode;

extern llrp_u8_t
LLRP_C0ReadAck_getLaneMode (
  LLRP_tSC0ReadAck *pThis);

extern LLRP_tResultCode
LLRP_C0ReadAck_setLaneMode (
  LLRP_tSC0ReadAck *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdC0ReadAck_WaitTime;

extern llrp_u8_t
LLRP_C0ReadAck_getWaitTime (
  LLRP_tSC0ReadAck *pThis);

extern LLRP_tResultCode
LLRP_C0ReadAck_setWaitTime (
  LLRP_tSC0ReadAck *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdC0ReadAck_TxPower;

extern llrp_u8_t
LLRP_C0ReadAck_getTxPower (
  LLRP_tSC0ReadAck *pThis);

extern LLRP_tResultCode
LLRP_C0ReadAck_setTxPower (
  LLRP_tSC0ReadAck *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdC0ReadAck_PLLChannelID;

extern llrp_u8_t
LLRP_C0ReadAck_getPLLChannelID (
  LLRP_tSC0ReadAck *pThis);

extern LLRP_tResultCode
LLRP_C0ReadAck_setPLLChannelID (
  LLRP_tSC0ReadAck *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdC0ReadAck_BSTInterval;

extern llrp_u8_t
LLRP_C0ReadAck_getBSTInterval (
  LLRP_tSC0ReadAck *pThis);

extern LLRP_tResultCode
LLRP_C0ReadAck_setBSTInterval (
  LLRP_tSC0ReadAck *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdC0ReadAck_TransClass;

extern llrp_u8_t
LLRP_C0ReadAck_getTransClass (
  LLRP_tSC0ReadAck *pThis);

extern LLRP_tResultCode
LLRP_C0ReadAck_setTransClass (
  LLRP_tSC0ReadAck *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SSignalStatus433MHz
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t PowerVal;

    llrp_u16_t SignalTestResult;

    llrp_u8_t RSSI;

    llrp_u8_t CalibrateResult;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdSignalStatus433MHz;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSignalStatus433MHz[];

extern LLRP_tSSignalStatus433MHz *
LLRP_SignalStatus433MHz_construct (void);

extern void
LLRP_SignalStatus433MHz_destruct (
 LLRP_tSSignalStatus433MHz * pThis);

extern void
LLRP_SignalStatus433MHz_decodeFields (
 LLRP_tSSignalStatus433MHz * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SignalStatus433MHz_assimilateSubParameters (
 LLRP_tSSignalStatus433MHz * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SignalStatus433MHz_encode (
  const LLRP_tSSignalStatus433MHz *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_SignalStatus433MHz_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdSignalStatus433MHz_PowerVal;

extern llrp_u16_t
LLRP_SignalStatus433MHz_getPowerVal (
  LLRP_tSSignalStatus433MHz *pThis);

extern LLRP_tResultCode
LLRP_SignalStatus433MHz_setPowerVal (
  LLRP_tSSignalStatus433MHz *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSignalStatus433MHz_SignalTestResult;

extern llrp_u16_t
LLRP_SignalStatus433MHz_getSignalTestResult (
  LLRP_tSSignalStatus433MHz *pThis);

extern LLRP_tResultCode
LLRP_SignalStatus433MHz_setSignalTestResult (
  LLRP_tSSignalStatus433MHz *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSignalStatus433MHz_RSSI;

extern llrp_u8_t
LLRP_SignalStatus433MHz_getRSSI (
  LLRP_tSSignalStatus433MHz *pThis);

extern LLRP_tResultCode
LLRP_SignalStatus433MHz_setRSSI (
  LLRP_tSSignalStatus433MHz *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSignalStatus433MHz_CalibrateResult;

extern llrp_u8_t
LLRP_SignalStatus433MHz_getCalibrateResult (
  LLRP_tSSignalStatus433MHz *pThis);

extern LLRP_tResultCode
LLRP_SignalStatus433MHz_setCalibrateResult (
  LLRP_tSSignalStatus433MHz *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SCC1101Test
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t Result;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdCC1101Test;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdCC1101Test[];

extern LLRP_tSCC1101Test *
LLRP_CC1101Test_construct (void);

extern void
LLRP_CC1101Test_destruct (
 LLRP_tSCC1101Test * pThis);

extern void
LLRP_CC1101Test_decodeFields (
 LLRP_tSCC1101Test * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_CC1101Test_assimilateSubParameters (
 LLRP_tSCC1101Test * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_CC1101Test_encode (
  const LLRP_tSCC1101Test *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_CC1101Test_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdCC1101Test_Result;

extern llrp_u8_t
LLRP_CC1101Test_getResult (
  LLRP_tSCC1101Test *pThis);

extern LLRP_tResultCode
LLRP_CC1101Test_setResult (
  LLRP_tSCC1101Test *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SCommSocket
{
    LLRP_tSParameter hdr;
  
    llrp_u32_t RemoteIp;

    llrp_u32_t LocalIp;

    llrp_u16_t RemotePort;

    llrp_u16_t LocalPort;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdCommSocket;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdCommSocket[];

extern LLRP_tSCommSocket *
LLRP_CommSocket_construct (void);

extern void
LLRP_CommSocket_destruct (
 LLRP_tSCommSocket * pThis);

extern void
LLRP_CommSocket_decodeFields (
 LLRP_tSCommSocket * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_CommSocket_assimilateSubParameters (
 LLRP_tSCommSocket * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_CommSocket_encode (
  const LLRP_tSCommSocket *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_CommSocket_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdCommSocket_RemoteIp;

extern llrp_u32_t
LLRP_CommSocket_getRemoteIp (
  LLRP_tSCommSocket *pThis);

extern LLRP_tResultCode
LLRP_CommSocket_setRemoteIp (
  LLRP_tSCommSocket *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdCommSocket_LocalIp;

extern llrp_u32_t
LLRP_CommSocket_getLocalIp (
  LLRP_tSCommSocket *pThis);

extern LLRP_tResultCode
LLRP_CommSocket_setLocalIp (
  LLRP_tSCommSocket *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdCommSocket_RemotePort;

extern llrp_u16_t
LLRP_CommSocket_getRemotePort (
  LLRP_tSCommSocket *pThis);

extern LLRP_tResultCode
LLRP_CommSocket_setRemotePort (
  LLRP_tSCommSocket *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdCommSocket_LocalPort;

extern llrp_u16_t
LLRP_CommSocket_getLocalPort (
  LLRP_tSCommSocket *pThis);

extern LLRP_tResultCode
LLRP_CommSocket_setLocalPort (
  LLRP_tSCommSocket *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_SCommSerialPort
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t SerialIndex;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdCommSerialPort;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdCommSerialPort[];

extern LLRP_tSCommSerialPort *
LLRP_CommSerialPort_construct (void);

extern void
LLRP_CommSerialPort_destruct (
 LLRP_tSCommSerialPort * pThis);

extern void
LLRP_CommSerialPort_decodeFields (
 LLRP_tSCommSerialPort * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_CommSerialPort_assimilateSubParameters (
 LLRP_tSCommSerialPort * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_CommSerialPort_encode (
  const LLRP_tSCommSerialPort *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_CommSerialPort_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdCommSerialPort_SerialIndex;

extern llrp_u8_t
LLRP_CommSerialPort_getSerialIndex (
  LLRP_tSCommSerialPort *pThis);

extern LLRP_tResultCode
LLRP_CommSerialPort_setSerialIndex (
  LLRP_tSCommSerialPort *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SCommWiegand
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t WiegandIndex;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdCommWiegand;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdCommWiegand[];

extern LLRP_tSCommWiegand *
LLRP_CommWiegand_construct (void);

extern void
LLRP_CommWiegand_destruct (
 LLRP_tSCommWiegand * pThis);

extern void
LLRP_CommWiegand_decodeFields (
 LLRP_tSCommWiegand * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_CommWiegand_assimilateSubParameters (
 LLRP_tSCommWiegand * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_CommWiegand_encode (
  const LLRP_tSCommWiegand *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_CommWiegand_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdCommWiegand_WiegandIndex;

extern llrp_u8_t
LLRP_CommWiegand_getWiegandIndex (
  LLRP_tSCommWiegand *pThis);

extern LLRP_tResultCode
LLRP_CommWiegand_setWiegandIndex (
  LLRP_tSCommWiegand *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SCommGprs
{
    LLRP_tSParameter hdr;
  
    llrp_u32_t RemoteIp;

    llrp_u16_t RemotePort;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdCommGprs;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdCommGprs[];

extern LLRP_tSCommGprs *
LLRP_CommGprs_construct (void);

extern void
LLRP_CommGprs_destruct (
 LLRP_tSCommGprs * pThis);

extern void
LLRP_CommGprs_decodeFields (
 LLRP_tSCommGprs * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_CommGprs_assimilateSubParameters (
 LLRP_tSCommGprs * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_CommGprs_encode (
  const LLRP_tSCommGprs *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_CommGprs_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdCommGprs_RemoteIp;

extern llrp_u32_t
LLRP_CommGprs_getRemoteIp (
  LLRP_tSCommGprs *pThis);

extern LLRP_tResultCode
LLRP_CommGprs_setRemoteIp (
  LLRP_tSCommGprs *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdCommGprs_RemotePort;

extern llrp_u16_t
LLRP_CommGprs_getRemotePort (
  LLRP_tSCommGprs *pThis);

extern LLRP_tResultCode
LLRP_CommGprs_setRemotePort (
  LLRP_tSCommGprs *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_SGpioWriteTest
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t GpioWriteData;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdGpioWriteTest;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdGpioWriteTest[];

extern LLRP_tSGpioWriteTest *
LLRP_GpioWriteTest_construct (void);

extern void
LLRP_GpioWriteTest_destruct (
 LLRP_tSGpioWriteTest * pThis);

extern void
LLRP_GpioWriteTest_decodeFields (
 LLRP_tSGpioWriteTest * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_GpioWriteTest_assimilateSubParameters (
 LLRP_tSGpioWriteTest * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_GpioWriteTest_encode (
  const LLRP_tSGpioWriteTest *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_GpioWriteTest_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdGpioWriteTest_GpioWriteData;

extern llrp_u8_t
LLRP_GpioWriteTest_getGpioWriteData (
  LLRP_tSGpioWriteTest *pThis);

extern LLRP_tResultCode
LLRP_GpioWriteTest_setGpioWriteData (
  LLRP_tSGpioWriteTest *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SSendAndReceiveRFTest
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t AntIndex;

    llrp_u8_t SendAndReceiveRFTestType;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdSendAndReceiveRFTest;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSendAndReceiveRFTest[];

extern LLRP_tSSendAndReceiveRFTest *
LLRP_SendAndReceiveRFTest_construct (void);

extern void
LLRP_SendAndReceiveRFTest_destruct (
 LLRP_tSSendAndReceiveRFTest * pThis);

extern void
LLRP_SendAndReceiveRFTest_decodeFields (
 LLRP_tSSendAndReceiveRFTest * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SendAndReceiveRFTest_assimilateSubParameters (
 LLRP_tSSendAndReceiveRFTest * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SendAndReceiveRFTest_encode (
  const LLRP_tSSendAndReceiveRFTest *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_SendAndReceiveRFTest_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdSendAndReceiveRFTest_AntIndex;

extern llrp_u8_t
LLRP_SendAndReceiveRFTest_getAntIndex (
  LLRP_tSSendAndReceiveRFTest *pThis);

extern LLRP_tResultCode
LLRP_SendAndReceiveRFTest_setAntIndex (
  LLRP_tSSendAndReceiveRFTest *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSendAndReceiveRFTest_SendAndReceiveRFTestType;

extern llrp_u8_t
LLRP_SendAndReceiveRFTest_getSendAndReceiveRFTestType (
  LLRP_tSSendAndReceiveRFTest *pThis);

extern LLRP_tResultCode
LLRP_SendAndReceiveRFTest_setSendAndReceiveRFTestType (
  LLRP_tSSendAndReceiveRFTest *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SReverseSensitivityTest
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t AntIndex;

    llrp_u16_t Cnt;

    llrp_u32_t Freq;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdReverseSensitivityTest;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdReverseSensitivityTest[];

extern LLRP_tSReverseSensitivityTest *
LLRP_ReverseSensitivityTest_construct (void);

extern void
LLRP_ReverseSensitivityTest_destruct (
 LLRP_tSReverseSensitivityTest * pThis);

extern void
LLRP_ReverseSensitivityTest_decodeFields (
 LLRP_tSReverseSensitivityTest * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_ReverseSensitivityTest_assimilateSubParameters (
 LLRP_tSReverseSensitivityTest * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_ReverseSensitivityTest_encode (
  const LLRP_tSReverseSensitivityTest *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_ReverseSensitivityTest_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdReverseSensitivityTest_AntIndex;

extern llrp_u8_t
LLRP_ReverseSensitivityTest_getAntIndex (
  LLRP_tSReverseSensitivityTest *pThis);

extern LLRP_tResultCode
LLRP_ReverseSensitivityTest_setAntIndex (
  LLRP_tSReverseSensitivityTest *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdReverseSensitivityTest_Cnt;

extern llrp_u16_t
LLRP_ReverseSensitivityTest_getCnt (
  LLRP_tSReverseSensitivityTest *pThis);

extern LLRP_tResultCode
LLRP_ReverseSensitivityTest_setCnt (
  LLRP_tSReverseSensitivityTest *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdReverseSensitivityTest_Freq;

extern llrp_u32_t
LLRP_ReverseSensitivityTest_getFreq (
  LLRP_tSReverseSensitivityTest *pThis);

extern LLRP_tResultCode
LLRP_ReverseSensitivityTest_setFreq (
  LLRP_tSReverseSensitivityTest *pThis,
  llrp_u32_t Value);

  


  
struct LLRP_SACParamReadWrite
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t Magic;

    llrp_u16_t InitK0;

  
    LLRP_tSPowerTable * listPowerTable;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdACParamReadWrite;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdACParamReadWrite[];

extern LLRP_tSACParamReadWrite *
LLRP_ACParamReadWrite_construct (void);

extern void
LLRP_ACParamReadWrite_destruct (
 LLRP_tSACParamReadWrite * pThis);

extern void
LLRP_ACParamReadWrite_decodeFields (
 LLRP_tSACParamReadWrite * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_ACParamReadWrite_assimilateSubParameters (
 LLRP_tSACParamReadWrite * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_ACParamReadWrite_encode (
  const LLRP_tSACParamReadWrite *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_ACParamReadWrite_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdACParamReadWrite_Magic;

extern llrp_u16_t
LLRP_ACParamReadWrite_getMagic (
  LLRP_tSACParamReadWrite *pThis);

extern LLRP_tResultCode
LLRP_ACParamReadWrite_setMagic (
  LLRP_tSACParamReadWrite *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdACParamReadWrite_InitK0;

extern llrp_u16_t
LLRP_ACParamReadWrite_getInitK0 (
  LLRP_tSACParamReadWrite *pThis);

extern LLRP_tResultCode
LLRP_ACParamReadWrite_setInitK0 (
  LLRP_tSACParamReadWrite *pThis,
  llrp_u16_t Value);

  
extern LLRP_tSPowerTable *
LLRP_ACParamReadWrite_beginPowerTable (
  LLRP_tSACParamReadWrite *pThis);

extern LLRP_tSPowerTable *
LLRP_ACParamReadWrite_nextPowerTable (
  LLRP_tSPowerTable *pCurrent);

extern void
LLRP_ACParamReadWrite_clearPowerTable (
  LLRP_tSACParamReadWrite *pThis);

extern LLRP_tResultCode
LLRP_ACParamReadWrite_addPowerTable (
  LLRP_tSACParamReadWrite *pThis,
  LLRP_tSPowerTable *pValue);




  
struct LLRP_SPowerTable
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t Power;

    llrp_u16_t Voltage;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdPowerTable;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdPowerTable[];

extern LLRP_tSPowerTable *
LLRP_PowerTable_construct (void);

extern void
LLRP_PowerTable_destruct (
 LLRP_tSPowerTable * pThis);

extern void
LLRP_PowerTable_decodeFields (
 LLRP_tSPowerTable * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_PowerTable_assimilateSubParameters (
 LLRP_tSPowerTable * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_PowerTable_encode (
  const LLRP_tSPowerTable *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_PowerTable_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdPowerTable_Power;

extern llrp_u16_t
LLRP_PowerTable_getPower (
  LLRP_tSPowerTable *pThis);

extern LLRP_tResultCode
LLRP_PowerTable_setPower (
  LLRP_tSPowerTable *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdPowerTable_Voltage;

extern llrp_u16_t
LLRP_PowerTable_getVoltage (
  LLRP_tSPowerTable *pThis);

extern LLRP_tResultCode
LLRP_PowerTable_setVoltage (
  LLRP_tSPowerTable *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_SACVoltageQuery
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t AntennaID;

    llrp_u8_t Direction;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdACVoltageQuery;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdACVoltageQuery[];

extern LLRP_tSACVoltageQuery *
LLRP_ACVoltageQuery_construct (void);

extern void
LLRP_ACVoltageQuery_destruct (
 LLRP_tSACVoltageQuery * pThis);

extern void
LLRP_ACVoltageQuery_decodeFields (
 LLRP_tSACVoltageQuery * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_ACVoltageQuery_assimilateSubParameters (
 LLRP_tSACVoltageQuery * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_ACVoltageQuery_encode (
  const LLRP_tSACVoltageQuery *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_ACVoltageQuery_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdACVoltageQuery_AntennaID;

extern llrp_u8_t
LLRP_ACVoltageQuery_getAntennaID (
  LLRP_tSACVoltageQuery *pThis);

extern LLRP_tResultCode
LLRP_ACVoltageQuery_setAntennaID (
  LLRP_tSACVoltageQuery *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdACVoltageQuery_Direction;

extern llrp_u8_t
LLRP_ACVoltageQuery_getDirection (
  LLRP_tSACVoltageQuery *pThis);

extern LLRP_tResultCode
LLRP_ACVoltageQuery_setDirection (
  LLRP_tSACVoltageQuery *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SSetAndGetK0
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t AntIndex;

    llrp_u8_t CmdType;

    llrp_u16_t K0Value;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdSetAndGetK0;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSetAndGetK0[];

extern LLRP_tSSetAndGetK0 *
LLRP_SetAndGetK0_construct (void);

extern void
LLRP_SetAndGetK0_destruct (
 LLRP_tSSetAndGetK0 * pThis);

extern void
LLRP_SetAndGetK0_decodeFields (
 LLRP_tSSetAndGetK0 * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SetAndGetK0_assimilateSubParameters (
 LLRP_tSSetAndGetK0 * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SetAndGetK0_encode (
  const LLRP_tSSetAndGetK0 *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_SetAndGetK0_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdSetAndGetK0_AntIndex;

extern llrp_u8_t
LLRP_SetAndGetK0_getAntIndex (
  LLRP_tSSetAndGetK0 *pThis);

extern LLRP_tResultCode
LLRP_SetAndGetK0_setAntIndex (
  LLRP_tSSetAndGetK0 *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSetAndGetK0_CmdType;

extern llrp_u8_t
LLRP_SetAndGetK0_getCmdType (
  LLRP_tSSetAndGetK0 *pThis);

extern LLRP_tResultCode
LLRP_SetAndGetK0_setCmdType (
  LLRP_tSSetAndGetK0 *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSetAndGetK0_K0Value;

extern llrp_u16_t
LLRP_SetAndGetK0_getK0Value (
  LLRP_tSSetAndGetK0 *pThis);

extern LLRP_tResultCode
LLRP_SetAndGetK0_setK0Value (
  LLRP_tSSetAndGetK0 *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_SPACtr
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t Status;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdPACtr;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdPACtr[];

extern LLRP_tSPACtr *
LLRP_PACtr_construct (void);

extern void
LLRP_PACtr_destruct (
 LLRP_tSPACtr * pThis);

extern void
LLRP_PACtr_decodeFields (
 LLRP_tSPACtr * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_PACtr_assimilateSubParameters (
 LLRP_tSPACtr * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_PACtr_encode (
  const LLRP_tSPACtr *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_PACtr_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdPACtr_Status;

extern llrp_u8_t
LLRP_PACtr_getStatus (
  LLRP_tSPACtr *pThis);

extern LLRP_tResultCode
LLRP_PACtr_setStatus (
  LLRP_tSPACtr *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SAutoCalibrite
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t AntNum;

    llrp_u8v_t AntIndex;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdAutoCalibrite;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdAutoCalibrite[];

extern LLRP_tSAutoCalibrite *
LLRP_AutoCalibrite_construct (void);

extern void
LLRP_AutoCalibrite_destruct (
 LLRP_tSAutoCalibrite * pThis);

extern void
LLRP_AutoCalibrite_decodeFields (
 LLRP_tSAutoCalibrite * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_AutoCalibrite_assimilateSubParameters (
 LLRP_tSAutoCalibrite * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_AutoCalibrite_encode (
  const LLRP_tSAutoCalibrite *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_AutoCalibrite_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdAutoCalibrite_AntNum;

extern llrp_u8_t
LLRP_AutoCalibrite_getAntNum (
  LLRP_tSAutoCalibrite *pThis);

extern LLRP_tResultCode
LLRP_AutoCalibrite_setAntNum (
  LLRP_tSAutoCalibrite *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdAutoCalibrite_AntIndex;

extern llrp_u8v_t
LLRP_AutoCalibrite_getAntIndex (
  LLRP_tSAutoCalibrite *pThis);

extern LLRP_tResultCode
LLRP_AutoCalibrite_setAntIndex (
  LLRP_tSAutoCalibrite *pThis,
  llrp_u8v_t Value);

  


  
struct LLRP_SMACAndSerail
{
    LLRP_tSParameter hdr;
  
  
    LLRP_tSSerailNumber * pSerailNumber;

    LLRP_tSMAC * pMAC;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdMACAndSerail;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdMACAndSerail[];

extern LLRP_tSMACAndSerail *
LLRP_MACAndSerail_construct (void);

extern void
LLRP_MACAndSerail_destruct (
 LLRP_tSMACAndSerail * pThis);

extern void
LLRP_MACAndSerail_decodeFields (
 LLRP_tSMACAndSerail * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_MACAndSerail_assimilateSubParameters (
 LLRP_tSMACAndSerail * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_MACAndSerail_encode (
  const LLRP_tSMACAndSerail *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_MACAndSerail_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
  
extern LLRP_tSSerailNumber *
LLRP_MACAndSerail_getSerailNumber (
  LLRP_tSMACAndSerail *pThis);

extern LLRP_tResultCode
LLRP_MACAndSerail_setSerailNumber (
  LLRP_tSMACAndSerail *pThis,
  LLRP_tSSerailNumber *pValue);

extern LLRP_tSMAC *
LLRP_MACAndSerail_getMAC (
  LLRP_tSMACAndSerail *pThis);

extern LLRP_tResultCode
LLRP_MACAndSerail_setMAC (
  LLRP_tSMACAndSerail *pThis,
  LLRP_tSMAC *pValue);



  
struct LLRP_SMAC
{
    LLRP_tSParameter hdr;
  
    llrp_u8v_t MacAddr;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdMAC;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdMAC[];

extern LLRP_tSMAC *
LLRP_MAC_construct (void);

extern void
LLRP_MAC_destruct (
 LLRP_tSMAC * pThis);

extern void
LLRP_MAC_decodeFields (
 LLRP_tSMAC * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_MAC_assimilateSubParameters (
 LLRP_tSMAC * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_MAC_encode (
  const LLRP_tSMAC *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_MAC_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdMAC_MacAddr;

extern llrp_u8v_t
LLRP_MAC_getMacAddr (
  LLRP_tSMAC *pThis);

extern LLRP_tResultCode
LLRP_MAC_setMacAddr (
  LLRP_tSMAC *pThis,
  llrp_u8v_t Value);

  


  
struct LLRP_SSerailNumber
{
    LLRP_tSParameter hdr;
  
    llrp_u8v_t ReaderSerial;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdSerailNumber;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSerailNumber[];

extern LLRP_tSSerailNumber *
LLRP_SerailNumber_construct (void);

extern void
LLRP_SerailNumber_destruct (
 LLRP_tSSerailNumber * pThis);

extern void
LLRP_SerailNumber_decodeFields (
 LLRP_tSSerailNumber * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SerailNumber_assimilateSubParameters (
 LLRP_tSSerailNumber * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SerailNumber_encode (
  const LLRP_tSSerailNumber *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_SerailNumber_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdSerailNumber_ReaderSerial;

extern llrp_u8v_t
LLRP_SerailNumber_getReaderSerial (
  LLRP_tSSerailNumber *pThis);

extern LLRP_tResultCode
LLRP_SerailNumber_setReaderSerial (
  LLRP_tSSerailNumber *pThis,
  llrp_u8v_t Value);

  


  
struct LLRP_SSetVoltage
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t AntIndex;

    llrp_u16_t HighVoltage;

    llrp_u32_t Frequency;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdSetVoltage;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSetVoltage[];

extern LLRP_tSSetVoltage *
LLRP_SetVoltage_construct (void);

extern void
LLRP_SetVoltage_destruct (
 LLRP_tSSetVoltage * pThis);

extern void
LLRP_SetVoltage_decodeFields (
 LLRP_tSSetVoltage * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SetVoltage_assimilateSubParameters (
 LLRP_tSSetVoltage * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SetVoltage_encode (
  const LLRP_tSSetVoltage *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_SetVoltage_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdSetVoltage_AntIndex;

extern llrp_u8_t
LLRP_SetVoltage_getAntIndex (
  LLRP_tSSetVoltage *pThis);

extern LLRP_tResultCode
LLRP_SetVoltage_setAntIndex (
  LLRP_tSSetVoltage *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSetVoltage_HighVoltage;

extern llrp_u16_t
LLRP_SetVoltage_getHighVoltage (
  LLRP_tSSetVoltage *pThis);

extern LLRP_tResultCode
LLRP_SetVoltage_setHighVoltage (
  LLRP_tSSetVoltage *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSetVoltage_Frequency;

extern llrp_u32_t
LLRP_SetVoltage_getFrequency (
  LLRP_tSSetVoltage *pThis);

extern LLRP_tResultCode
LLRP_SetVoltage_setFrequency (
  LLRP_tSSetVoltage *pThis,
  llrp_u32_t Value);

  


  
struct LLRP_SZXRIS6601PowerTable
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t ReaderType;

    llrp_u16_t PowerNum;

  
    LLRP_tSPowerTemplate * listPowerTemplate;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdZXRIS6601PowerTable;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdZXRIS6601PowerTable[];

extern LLRP_tSZXRIS6601PowerTable *
LLRP_ZXRIS6601PowerTable_construct (void);

extern void
LLRP_ZXRIS6601PowerTable_destruct (
 LLRP_tSZXRIS6601PowerTable * pThis);

extern void
LLRP_ZXRIS6601PowerTable_decodeFields (
 LLRP_tSZXRIS6601PowerTable * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_ZXRIS6601PowerTable_assimilateSubParameters (
 LLRP_tSZXRIS6601PowerTable * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_ZXRIS6601PowerTable_encode (
  const LLRP_tSZXRIS6601PowerTable *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_ZXRIS6601PowerTable_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdZXRIS6601PowerTable_ReaderType;

extern llrp_u8_t
LLRP_ZXRIS6601PowerTable_getReaderType (
  LLRP_tSZXRIS6601PowerTable *pThis);

extern LLRP_tResultCode
LLRP_ZXRIS6601PowerTable_setReaderType (
  LLRP_tSZXRIS6601PowerTable *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdZXRIS6601PowerTable_PowerNum;

extern llrp_u16_t
LLRP_ZXRIS6601PowerTable_getPowerNum (
  LLRP_tSZXRIS6601PowerTable *pThis);

extern LLRP_tResultCode
LLRP_ZXRIS6601PowerTable_setPowerNum (
  LLRP_tSZXRIS6601PowerTable *pThis,
  llrp_u16_t Value);

  
extern LLRP_tSPowerTemplate *
LLRP_ZXRIS6601PowerTable_beginPowerTemplate (
  LLRP_tSZXRIS6601PowerTable *pThis);

extern LLRP_tSPowerTemplate *
LLRP_ZXRIS6601PowerTable_nextPowerTemplate (
  LLRP_tSPowerTemplate *pCurrent);

extern void
LLRP_ZXRIS6601PowerTable_clearPowerTemplate (
  LLRP_tSZXRIS6601PowerTable *pThis);

extern LLRP_tResultCode
LLRP_ZXRIS6601PowerTable_addPowerTemplate (
  LLRP_tSZXRIS6601PowerTable *pThis,
  LLRP_tSPowerTemplate *pValue);




  
struct LLRP_SSetDATTValue
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t DATTValue;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdSetDATTValue;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSetDATTValue[];

extern LLRP_tSSetDATTValue *
LLRP_SetDATTValue_construct (void);

extern void
LLRP_SetDATTValue_destruct (
 LLRP_tSSetDATTValue * pThis);

extern void
LLRP_SetDATTValue_decodeFields (
 LLRP_tSSetDATTValue * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SetDATTValue_assimilateSubParameters (
 LLRP_tSSetDATTValue * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SetDATTValue_encode (
  const LLRP_tSSetDATTValue *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_SetDATTValue_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdSetDATTValue_DATTValue;

extern llrp_u16_t
LLRP_SetDATTValue_getDATTValue (
  LLRP_tSSetDATTValue *pThis);

extern LLRP_tResultCode
LLRP_SetDATTValue_setDATTValue (
  LLRP_tSSetDATTValue *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_SPowerTemplate
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t Power;

    llrp_u16_t HighVoltage;

    llrp_u16_t LowVoltage;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdPowerTemplate;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdPowerTemplate[];

extern LLRP_tSPowerTemplate *
LLRP_PowerTemplate_construct (void);

extern void
LLRP_PowerTemplate_destruct (
 LLRP_tSPowerTemplate * pThis);

extern void
LLRP_PowerTemplate_decodeFields (
 LLRP_tSPowerTemplate * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_PowerTemplate_assimilateSubParameters (
 LLRP_tSPowerTemplate * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_PowerTemplate_encode (
  const LLRP_tSPowerTemplate *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_PowerTemplate_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdPowerTemplate_Power;

extern llrp_u16_t
LLRP_PowerTemplate_getPower (
  LLRP_tSPowerTemplate *pThis);

extern LLRP_tResultCode
LLRP_PowerTemplate_setPower (
  LLRP_tSPowerTemplate *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdPowerTemplate_HighVoltage;

extern llrp_u16_t
LLRP_PowerTemplate_getHighVoltage (
  LLRP_tSPowerTemplate *pThis);

extern LLRP_tResultCode
LLRP_PowerTemplate_setHighVoltage (
  LLRP_tSPowerTemplate *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdPowerTemplate_LowVoltage;

extern llrp_u16_t
LLRP_PowerTemplate_getLowVoltage (
  LLRP_tSPowerTemplate *pThis);

extern LLRP_tResultCode
LLRP_PowerTemplate_setLowVoltage (
  LLRP_tSPowerTemplate *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_SBroadInf
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t ucBoardType;

    llrp_u8_t ucBoardVer;

    llrp_u8_t ucSubBoardNum;

    llrp_u8_t UcSubBoardPara;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdBroadInf;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdBroadInf[];

extern LLRP_tSBroadInf *
LLRP_BroadInf_construct (void);

extern void
LLRP_BroadInf_destruct (
 LLRP_tSBroadInf * pThis);

extern void
LLRP_BroadInf_decodeFields (
 LLRP_tSBroadInf * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_BroadInf_assimilateSubParameters (
 LLRP_tSBroadInf * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_BroadInf_encode (
  const LLRP_tSBroadInf *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_BroadInf_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdBroadInf_ucBoardType;

extern llrp_u8_t
LLRP_BroadInf_getucBoardType (
  LLRP_tSBroadInf *pThis);

extern LLRP_tResultCode
LLRP_BroadInf_setucBoardType (
  LLRP_tSBroadInf *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdBroadInf_ucBoardVer;

extern llrp_u8_t
LLRP_BroadInf_getucBoardVer (
  LLRP_tSBroadInf *pThis);

extern LLRP_tResultCode
LLRP_BroadInf_setucBoardVer (
  LLRP_tSBroadInf *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdBroadInf_ucSubBoardNum;

extern llrp_u8_t
LLRP_BroadInf_getucSubBoardNum (
  LLRP_tSBroadInf *pThis);

extern LLRP_tResultCode
LLRP_BroadInf_setucSubBoardNum (
  LLRP_tSBroadInf *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdBroadInf_UcSubBoardPara;

extern llrp_u8_t
LLRP_BroadInf_getUcSubBoardPara (
  LLRP_tSBroadInf *pThis);

extern LLRP_tResultCode
LLRP_BroadInf_setUcSubBoardPara (
  LLRP_tSBroadInf *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SRTCTime
{
    LLRP_tSParameter hdr;
  
    llrp_u32_t Date;

    llrp_u32_t Time;

    llrp_u8_t Week;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdRTCTime;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdRTCTime[];

extern LLRP_tSRTCTime *
LLRP_RTCTime_construct (void);

extern void
LLRP_RTCTime_destruct (
 LLRP_tSRTCTime * pThis);

extern void
LLRP_RTCTime_decodeFields (
 LLRP_tSRTCTime * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_RTCTime_assimilateSubParameters (
 LLRP_tSRTCTime * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_RTCTime_encode (
  const LLRP_tSRTCTime *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_RTCTime_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdRTCTime_Date;

extern llrp_u32_t
LLRP_RTCTime_getDate (
  LLRP_tSRTCTime *pThis);

extern LLRP_tResultCode
LLRP_RTCTime_setDate (
  LLRP_tSRTCTime *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdRTCTime_Time;

extern llrp_u32_t
LLRP_RTCTime_getTime (
  LLRP_tSRTCTime *pThis);

extern LLRP_tResultCode
LLRP_RTCTime_setTime (
  LLRP_tSRTCTime *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdRTCTime_Week;

extern llrp_u8_t
LLRP_RTCTime_getWeek (
  LLRP_tSRTCTime *pThis);

extern LLRP_tResultCode
LLRP_RTCTime_setWeek (
  LLRP_tSRTCTime *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_STestStartOrStop
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t StartOrStop;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdTestStartOrStop;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdTestStartOrStop[];

extern LLRP_tSTestStartOrStop *
LLRP_TestStartOrStop_construct (void);

extern void
LLRP_TestStartOrStop_destruct (
 LLRP_tSTestStartOrStop * pThis);

extern void
LLRP_TestStartOrStop_decodeFields (
 LLRP_tSTestStartOrStop * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_TestStartOrStop_assimilateSubParameters (
 LLRP_tSTestStartOrStop * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_TestStartOrStop_encode (
  const LLRP_tSTestStartOrStop *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_TestStartOrStop_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdTestStartOrStop_StartOrStop;

extern llrp_u8_t
LLRP_TestStartOrStop_getStartOrStop (
  LLRP_tSTestStartOrStop *pThis);

extern LLRP_tResultCode
LLRP_TestStartOrStop_setStartOrStop (
  LLRP_tSTestStartOrStop *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SNvramContent
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t Errorcode;

    llrp_u8_t BootFlag;

    llrp_u8_t CommunicationMode;

    llrp_u8_t LocationCfg;

    llrp_u8v_t ReaderSerial;

    llrp_u8v_t MacAddr;

    llrp_u8v_t LocationInfo;

    llrp_u8v_t IPCfg;

    llrp_u8v_t IPLocal;

    llrp_u8v_t Netmask;

    llrp_u8v_t Gateway;

    llrp_u8v_t Dns;

    llrp_u8v_t MWIP;

    llrp_u8v_t OMCIP;

    llrp_utf8v_t UserName;

    llrp_utf8v_t Password;

    llrp_u16_t DevID;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdNvramContent;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdNvramContent[];

extern LLRP_tSNvramContent *
LLRP_NvramContent_construct (void);

extern void
LLRP_NvramContent_destruct (
 LLRP_tSNvramContent * pThis);

extern void
LLRP_NvramContent_decodeFields (
 LLRP_tSNvramContent * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_NvramContent_assimilateSubParameters (
 LLRP_tSNvramContent * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_NvramContent_encode (
  const LLRP_tSNvramContent *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_NvramContent_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdNvramContent_Errorcode;

extern llrp_u8_t
LLRP_NvramContent_getErrorcode (
  LLRP_tSNvramContent *pThis);

extern LLRP_tResultCode
LLRP_NvramContent_setErrorcode (
  LLRP_tSNvramContent *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdNvramContent_BootFlag;

extern llrp_u8_t
LLRP_NvramContent_getBootFlag (
  LLRP_tSNvramContent *pThis);

extern LLRP_tResultCode
LLRP_NvramContent_setBootFlag (
  LLRP_tSNvramContent *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdNvramContent_CommunicationMode;

extern llrp_u8_t
LLRP_NvramContent_getCommunicationMode (
  LLRP_tSNvramContent *pThis);

extern LLRP_tResultCode
LLRP_NvramContent_setCommunicationMode (
  LLRP_tSNvramContent *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdNvramContent_LocationCfg;

extern llrp_u8_t
LLRP_NvramContent_getLocationCfg (
  LLRP_tSNvramContent *pThis);

extern LLRP_tResultCode
LLRP_NvramContent_setLocationCfg (
  LLRP_tSNvramContent *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdNvramContent_ReaderSerial;

extern llrp_u8v_t
LLRP_NvramContent_getReaderSerial (
  LLRP_tSNvramContent *pThis);

extern LLRP_tResultCode
LLRP_NvramContent_setReaderSerial (
  LLRP_tSNvramContent *pThis,
  llrp_u8v_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdNvramContent_MacAddr;

extern llrp_u8v_t
LLRP_NvramContent_getMacAddr (
  LLRP_tSNvramContent *pThis);

extern LLRP_tResultCode
LLRP_NvramContent_setMacAddr (
  LLRP_tSNvramContent *pThis,
  llrp_u8v_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdNvramContent_LocationInfo;

extern llrp_u8v_t
LLRP_NvramContent_getLocationInfo (
  LLRP_tSNvramContent *pThis);

extern LLRP_tResultCode
LLRP_NvramContent_setLocationInfo (
  LLRP_tSNvramContent *pThis,
  llrp_u8v_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdNvramContent_IPCfg;

extern llrp_u8v_t
LLRP_NvramContent_getIPCfg (
  LLRP_tSNvramContent *pThis);

extern LLRP_tResultCode
LLRP_NvramContent_setIPCfg (
  LLRP_tSNvramContent *pThis,
  llrp_u8v_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdNvramContent_IPLocal;

extern llrp_u8v_t
LLRP_NvramContent_getIPLocal (
  LLRP_tSNvramContent *pThis);

extern LLRP_tResultCode
LLRP_NvramContent_setIPLocal (
  LLRP_tSNvramContent *pThis,
  llrp_u8v_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdNvramContent_Netmask;

extern llrp_u8v_t
LLRP_NvramContent_getNetmask (
  LLRP_tSNvramContent *pThis);

extern LLRP_tResultCode
LLRP_NvramContent_setNetmask (
  LLRP_tSNvramContent *pThis,
  llrp_u8v_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdNvramContent_Gateway;

extern llrp_u8v_t
LLRP_NvramContent_getGateway (
  LLRP_tSNvramContent *pThis);

extern LLRP_tResultCode
LLRP_NvramContent_setGateway (
  LLRP_tSNvramContent *pThis,
  llrp_u8v_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdNvramContent_Dns;

extern llrp_u8v_t
LLRP_NvramContent_getDns (
  LLRP_tSNvramContent *pThis);

extern LLRP_tResultCode
LLRP_NvramContent_setDns (
  LLRP_tSNvramContent *pThis,
  llrp_u8v_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdNvramContent_MWIP;

extern llrp_u8v_t
LLRP_NvramContent_getMWIP (
  LLRP_tSNvramContent *pThis);

extern LLRP_tResultCode
LLRP_NvramContent_setMWIP (
  LLRP_tSNvramContent *pThis,
  llrp_u8v_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdNvramContent_OMCIP;

extern llrp_u8v_t
LLRP_NvramContent_getOMCIP (
  LLRP_tSNvramContent *pThis);

extern LLRP_tResultCode
LLRP_NvramContent_setOMCIP (
  LLRP_tSNvramContent *pThis,
  llrp_u8v_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdNvramContent_UserName;

extern llrp_utf8v_t
LLRP_NvramContent_getUserName (
  LLRP_tSNvramContent *pThis);

extern LLRP_tResultCode
LLRP_NvramContent_setUserName (
  LLRP_tSNvramContent *pThis,
  llrp_utf8v_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdNvramContent_Password;

extern llrp_utf8v_t
LLRP_NvramContent_getPassword (
  LLRP_tSNvramContent *pThis);

extern LLRP_tResultCode
LLRP_NvramContent_setPassword (
  LLRP_tSNvramContent *pThis,
  llrp_utf8v_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdNvramContent_DevID;

extern llrp_u16_t
LLRP_NvramContent_getDevID (
  LLRP_tSNvramContent *pThis);

extern LLRP_tResultCode
LLRP_NvramContent_setDevID (
  LLRP_tSNvramContent *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_SAntennaLinkStatusTest
{
    LLRP_tSParameter hdr;
  
    llrp_u32_t AntCount;

    llrp_u8v_t AntennaStatues;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdAntennaLinkStatusTest;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdAntennaLinkStatusTest[];

extern LLRP_tSAntennaLinkStatusTest *
LLRP_AntennaLinkStatusTest_construct (void);

extern void
LLRP_AntennaLinkStatusTest_destruct (
 LLRP_tSAntennaLinkStatusTest * pThis);

extern void
LLRP_AntennaLinkStatusTest_decodeFields (
 LLRP_tSAntennaLinkStatusTest * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_AntennaLinkStatusTest_assimilateSubParameters (
 LLRP_tSAntennaLinkStatusTest * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_AntennaLinkStatusTest_encode (
  const LLRP_tSAntennaLinkStatusTest *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_AntennaLinkStatusTest_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdAntennaLinkStatusTest_AntCount;

extern llrp_u32_t
LLRP_AntennaLinkStatusTest_getAntCount (
  LLRP_tSAntennaLinkStatusTest *pThis);

extern LLRP_tResultCode
LLRP_AntennaLinkStatusTest_setAntCount (
  LLRP_tSAntennaLinkStatusTest *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdAntennaLinkStatusTest_AntennaStatues;

extern llrp_u8v_t
LLRP_AntennaLinkStatusTest_getAntennaStatues (
  LLRP_tSAntennaLinkStatusTest *pThis);

extern LLRP_tResultCode
LLRP_AntennaLinkStatusTest_setAntennaStatues (
  LLRP_tSAntennaLinkStatusTest *pThis,
  llrp_u8v_t Value);

  


  
struct LLRP_SVSWRQueryTestACK
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t Ant1Vsw;

    llrp_u16_t Ant2Vsw;

    llrp_u16_t Ant3Vsw;

    llrp_u16_t Ant4Vsw;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdVSWRQueryTestACK;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdVSWRQueryTestACK[];

extern LLRP_tSVSWRQueryTestACK *
LLRP_VSWRQueryTestACK_construct (void);

extern void
LLRP_VSWRQueryTestACK_destruct (
 LLRP_tSVSWRQueryTestACK * pThis);

extern void
LLRP_VSWRQueryTestACK_decodeFields (
 LLRP_tSVSWRQueryTestACK * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_VSWRQueryTestACK_assimilateSubParameters (
 LLRP_tSVSWRQueryTestACK * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_VSWRQueryTestACK_encode (
  const LLRP_tSVSWRQueryTestACK *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_VSWRQueryTestACK_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdVSWRQueryTestACK_Ant1Vsw;

extern llrp_u16_t
LLRP_VSWRQueryTestACK_getAnt1Vsw (
  LLRP_tSVSWRQueryTestACK *pThis);

extern LLRP_tResultCode
LLRP_VSWRQueryTestACK_setAnt1Vsw (
  LLRP_tSVSWRQueryTestACK *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdVSWRQueryTestACK_Ant2Vsw;

extern llrp_u16_t
LLRP_VSWRQueryTestACK_getAnt2Vsw (
  LLRP_tSVSWRQueryTestACK *pThis);

extern LLRP_tResultCode
LLRP_VSWRQueryTestACK_setAnt2Vsw (
  LLRP_tSVSWRQueryTestACK *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdVSWRQueryTestACK_Ant3Vsw;

extern llrp_u16_t
LLRP_VSWRQueryTestACK_getAnt3Vsw (
  LLRP_tSVSWRQueryTestACK *pThis);

extern LLRP_tResultCode
LLRP_VSWRQueryTestACK_setAnt3Vsw (
  LLRP_tSVSWRQueryTestACK *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdVSWRQueryTestACK_Ant4Vsw;

extern llrp_u16_t
LLRP_VSWRQueryTestACK_getAnt4Vsw (
  LLRP_tSVSWRQueryTestACK *pThis);

extern LLRP_tResultCode
LLRP_VSWRQueryTestACK_setAnt4Vsw (
  LLRP_tSVSWRQueryTestACK *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_SReverseSensitivityDataACK
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t SuccessCnt;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdReverseSensitivityDataACK;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdReverseSensitivityDataACK[];

extern LLRP_tSReverseSensitivityDataACK *
LLRP_ReverseSensitivityDataACK_construct (void);

extern void
LLRP_ReverseSensitivityDataACK_destruct (
 LLRP_tSReverseSensitivityDataACK * pThis);

extern void
LLRP_ReverseSensitivityDataACK_decodeFields (
 LLRP_tSReverseSensitivityDataACK * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_ReverseSensitivityDataACK_assimilateSubParameters (
 LLRP_tSReverseSensitivityDataACK * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_ReverseSensitivityDataACK_encode (
  const LLRP_tSReverseSensitivityDataACK *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_ReverseSensitivityDataACK_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdReverseSensitivityDataACK_SuccessCnt;

extern llrp_u16_t
LLRP_ReverseSensitivityDataACK_getSuccessCnt (
  LLRP_tSReverseSensitivityDataACK *pThis);

extern LLRP_tResultCode
LLRP_ReverseSensitivityDataACK_setSuccessCnt (
  LLRP_tSReverseSensitivityDataACK *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_SGpioReadTestACK
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t GpioReadData;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdGpioReadTestACK;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdGpioReadTestACK[];

extern LLRP_tSGpioReadTestACK *
LLRP_GpioReadTestACK_construct (void);

extern void
LLRP_GpioReadTestACK_destruct (
 LLRP_tSGpioReadTestACK * pThis);

extern void
LLRP_GpioReadTestACK_decodeFields (
 LLRP_tSGpioReadTestACK * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_GpioReadTestACK_assimilateSubParameters (
 LLRP_tSGpioReadTestACK * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_GpioReadTestACK_encode (
  const LLRP_tSGpioReadTestACK *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_GpioReadTestACK_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdGpioReadTestACK_GpioReadData;

extern llrp_u8_t
LLRP_GpioReadTestACK_getGpioReadData (
  LLRP_tSGpioReadTestACK *pThis);

extern LLRP_tResultCode
LLRP_GpioReadTestACK_setGpioReadData (
  LLRP_tSGpioReadTestACK *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SEpldRegValueACK
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t EpldRegValue;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdEpldRegValueACK;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdEpldRegValueACK[];

extern LLRP_tSEpldRegValueACK *
LLRP_EpldRegValueACK_construct (void);

extern void
LLRP_EpldRegValueACK_destruct (
 LLRP_tSEpldRegValueACK * pThis);

extern void
LLRP_EpldRegValueACK_decodeFields (
 LLRP_tSEpldRegValueACK * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_EpldRegValueACK_assimilateSubParameters (
 LLRP_tSEpldRegValueACK * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_EpldRegValueACK_encode (
  const LLRP_tSEpldRegValueACK *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_EpldRegValueACK_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdEpldRegValueACK_EpldRegValue;

extern llrp_u8_t
LLRP_EpldRegValueACK_getEpldRegValue (
  LLRP_tSEpldRegValueACK *pThis);

extern LLRP_tResultCode
LLRP_EpldRegValueACK_setEpldRegValue (
  LLRP_tSEpldRegValueACK *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SFpgaValueACK
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t FpgaRegValue;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdFpgaValueACK;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdFpgaValueACK[];

extern LLRP_tSFpgaValueACK *
LLRP_FpgaValueACK_construct (void);

extern void
LLRP_FpgaValueACK_destruct (
 LLRP_tSFpgaValueACK * pThis);

extern void
LLRP_FpgaValueACK_decodeFields (
 LLRP_tSFpgaValueACK * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_FpgaValueACK_assimilateSubParameters (
 LLRP_tSFpgaValueACK * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_FpgaValueACK_encode (
  const LLRP_tSFpgaValueACK *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_FpgaValueACK_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdFpgaValueACK_FpgaRegValue;

extern llrp_u16_t
LLRP_FpgaValueACK_getFpgaRegValue (
  LLRP_tSFpgaValueACK *pThis);

extern LLRP_tResultCode
LLRP_FpgaValueACK_setFpgaRegValue (
  LLRP_tSFpgaValueACK *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_SEpldRWTestACK
{
    LLRP_tSParameter hdr;
  
    llrp_u32_t TestCnt;

    llrp_u32_t FailedCnt;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdEpldRWTestACK;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdEpldRWTestACK[];

extern LLRP_tSEpldRWTestACK *
LLRP_EpldRWTestACK_construct (void);

extern void
LLRP_EpldRWTestACK_destruct (
 LLRP_tSEpldRWTestACK * pThis);

extern void
LLRP_EpldRWTestACK_decodeFields (
 LLRP_tSEpldRWTestACK * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_EpldRWTestACK_assimilateSubParameters (
 LLRP_tSEpldRWTestACK * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_EpldRWTestACK_encode (
  const LLRP_tSEpldRWTestACK *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_EpldRWTestACK_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdEpldRWTestACK_TestCnt;

extern llrp_u32_t
LLRP_EpldRWTestACK_getTestCnt (
  LLRP_tSEpldRWTestACK *pThis);

extern LLRP_tResultCode
LLRP_EpldRWTestACK_setTestCnt (
  LLRP_tSEpldRWTestACK *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdEpldRWTestACK_FailedCnt;

extern llrp_u32_t
LLRP_EpldRWTestACK_getFailedCnt (
  LLRP_tSEpldRWTestACK *pThis);

extern LLRP_tResultCode
LLRP_EpldRWTestACK_setFailedCnt (
  LLRP_tSEpldRWTestACK *pThis,
  llrp_u32_t Value);

  


  
struct LLRP_SACVoltageQueryAck
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t Value;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdACVoltageQueryAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdACVoltageQueryAck[];

extern LLRP_tSACVoltageQueryAck *
LLRP_ACVoltageQueryAck_construct (void);

extern void
LLRP_ACVoltageQueryAck_destruct (
 LLRP_tSACVoltageQueryAck * pThis);

extern void
LLRP_ACVoltageQueryAck_decodeFields (
 LLRP_tSACVoltageQueryAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_ACVoltageQueryAck_assimilateSubParameters (
 LLRP_tSACVoltageQueryAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_ACVoltageQueryAck_encode (
  const LLRP_tSACVoltageQueryAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_ACVoltageQueryAck_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdACVoltageQueryAck_Value;

extern llrp_u16_t
LLRP_ACVoltageQueryAck_getValue (
  LLRP_tSACVoltageQueryAck *pThis);

extern LLRP_tResultCode
LLRP_ACVoltageQueryAck_setValue (
  LLRP_tSACVoltageQueryAck *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_SSetAndGetK0Ack
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t K0Value;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdSetAndGetK0Ack;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSetAndGetK0Ack[];

extern LLRP_tSSetAndGetK0Ack *
LLRP_SetAndGetK0Ack_construct (void);

extern void
LLRP_SetAndGetK0Ack_destruct (
 LLRP_tSSetAndGetK0Ack * pThis);

extern void
LLRP_SetAndGetK0Ack_decodeFields (
 LLRP_tSSetAndGetK0Ack * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SetAndGetK0Ack_assimilateSubParameters (
 LLRP_tSSetAndGetK0Ack * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SetAndGetK0Ack_encode (
  const LLRP_tSSetAndGetK0Ack *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_SetAndGetK0Ack_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdSetAndGetK0Ack_K0Value;

extern llrp_u16_t
LLRP_SetAndGetK0Ack_getK0Value (
  LLRP_tSSetAndGetK0Ack *pThis);

extern LLRP_tResultCode
LLRP_SetAndGetK0Ack_setK0Value (
  LLRP_tSSetAndGetK0Ack *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_SAntQueryPowerAck
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t ucAntNum;

  
    LLRP_tSAntPower * listAntPower;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdAntQueryPowerAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdAntQueryPowerAck[];

extern LLRP_tSAntQueryPowerAck *
LLRP_AntQueryPowerAck_construct (void);

extern void
LLRP_AntQueryPowerAck_destruct (
 LLRP_tSAntQueryPowerAck * pThis);

extern void
LLRP_AntQueryPowerAck_decodeFields (
 LLRP_tSAntQueryPowerAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_AntQueryPowerAck_assimilateSubParameters (
 LLRP_tSAntQueryPowerAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_AntQueryPowerAck_encode (
  const LLRP_tSAntQueryPowerAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_AntQueryPowerAck_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdAntQueryPowerAck_ucAntNum;

extern llrp_u16_t
LLRP_AntQueryPowerAck_getucAntNum (
  LLRP_tSAntQueryPowerAck *pThis);

extern LLRP_tResultCode
LLRP_AntQueryPowerAck_setucAntNum (
  LLRP_tSAntQueryPowerAck *pThis,
  llrp_u16_t Value);

  
extern LLRP_tSAntPower *
LLRP_AntQueryPowerAck_beginAntPower (
  LLRP_tSAntQueryPowerAck *pThis);

extern LLRP_tSAntPower *
LLRP_AntQueryPowerAck_nextAntPower (
  LLRP_tSAntPower *pCurrent);

extern void
LLRP_AntQueryPowerAck_clearAntPower (
  LLRP_tSAntQueryPowerAck *pThis);

extern LLRP_tResultCode
LLRP_AntQueryPowerAck_addAntPower (
  LLRP_tSAntQueryPowerAck *pThis,
  LLRP_tSAntPower *pValue);




  
struct LLRP_SAntPower
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t Power;

    llrp_u16_t K0;

    llrp_u8_t Status;

    llrp_u8_t AntIndex;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdAntPower;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdAntPower[];

extern LLRP_tSAntPower *
LLRP_AntPower_construct (void);

extern void
LLRP_AntPower_destruct (
 LLRP_tSAntPower * pThis);

extern void
LLRP_AntPower_decodeFields (
 LLRP_tSAntPower * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_AntPower_assimilateSubParameters (
 LLRP_tSAntPower * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_AntPower_encode (
  const LLRP_tSAntPower *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_AntPower_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdAntPower_Power;

extern llrp_u16_t
LLRP_AntPower_getPower (
  LLRP_tSAntPower *pThis);

extern LLRP_tResultCode
LLRP_AntPower_setPower (
  LLRP_tSAntPower *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdAntPower_K0;

extern llrp_u16_t
LLRP_AntPower_getK0 (
  LLRP_tSAntPower *pThis);

extern LLRP_tResultCode
LLRP_AntPower_setK0 (
  LLRP_tSAntPower *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdAntPower_Status;

extern llrp_u8_t
LLRP_AntPower_getStatus (
  LLRP_tSAntPower *pThis);

extern LLRP_tResultCode
LLRP_AntPower_setStatus (
  LLRP_tSAntPower *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdAntPower_AntIndex;

extern llrp_u8_t
LLRP_AntPower_getAntIndex (
  LLRP_tSAntPower *pThis);

extern LLRP_tResultCode
LLRP_AntPower_setAntIndex (
  LLRP_tSAntPower *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SAutoCalibrateAck
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t AntNum;

    llrp_u32_t Validity;

    llrp_u8v_t AntIndex;

  
    LLRP_tSAutoCalibrateResult * listAutoCalibrateResult;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdAutoCalibrateAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdAutoCalibrateAck[];

extern LLRP_tSAutoCalibrateAck *
LLRP_AutoCalibrateAck_construct (void);

extern void
LLRP_AutoCalibrateAck_destruct (
 LLRP_tSAutoCalibrateAck * pThis);

extern void
LLRP_AutoCalibrateAck_decodeFields (
 LLRP_tSAutoCalibrateAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_AutoCalibrateAck_assimilateSubParameters (
 LLRP_tSAutoCalibrateAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_AutoCalibrateAck_encode (
  const LLRP_tSAutoCalibrateAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_AutoCalibrateAck_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdAutoCalibrateAck_AntNum;

extern llrp_u8_t
LLRP_AutoCalibrateAck_getAntNum (
  LLRP_tSAutoCalibrateAck *pThis);

extern LLRP_tResultCode
LLRP_AutoCalibrateAck_setAntNum (
  LLRP_tSAutoCalibrateAck *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdAutoCalibrateAck_Validity;

extern llrp_u32_t
LLRP_AutoCalibrateAck_getValidity (
  LLRP_tSAutoCalibrateAck *pThis);

extern LLRP_tResultCode
LLRP_AutoCalibrateAck_setValidity (
  LLRP_tSAutoCalibrateAck *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdAutoCalibrateAck_AntIndex;

extern llrp_u8v_t
LLRP_AutoCalibrateAck_getAntIndex (
  LLRP_tSAutoCalibrateAck *pThis);

extern LLRP_tResultCode
LLRP_AutoCalibrateAck_setAntIndex (
  LLRP_tSAutoCalibrateAck *pThis,
  llrp_u8v_t Value);

  
extern LLRP_tSAutoCalibrateResult *
LLRP_AutoCalibrateAck_beginAutoCalibrateResult (
  LLRP_tSAutoCalibrateAck *pThis);

extern LLRP_tSAutoCalibrateResult *
LLRP_AutoCalibrateAck_nextAutoCalibrateResult (
  LLRP_tSAutoCalibrateResult *pCurrent);

extern void
LLRP_AutoCalibrateAck_clearAutoCalibrateResult (
  LLRP_tSAutoCalibrateAck *pThis);

extern LLRP_tResultCode
LLRP_AutoCalibrateAck_addAutoCalibrateResult (
  LLRP_tSAutoCalibrateAck *pThis,
  LLRP_tSAutoCalibrateResult *pValue);




  
struct LLRP_SAutoCalibrateResult
{
    LLRP_tSParameter hdr;
  
    llrp_u32_t Result;

    llrp_s16_t Power;

    llrp_u16_t K0;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdAutoCalibrateResult;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdAutoCalibrateResult[];

extern LLRP_tSAutoCalibrateResult *
LLRP_AutoCalibrateResult_construct (void);

extern void
LLRP_AutoCalibrateResult_destruct (
 LLRP_tSAutoCalibrateResult * pThis);

extern void
LLRP_AutoCalibrateResult_decodeFields (
 LLRP_tSAutoCalibrateResult * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_AutoCalibrateResult_assimilateSubParameters (
 LLRP_tSAutoCalibrateResult * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_AutoCalibrateResult_encode (
  const LLRP_tSAutoCalibrateResult *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_AutoCalibrateResult_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdAutoCalibrateResult_Result;

extern llrp_u32_t
LLRP_AutoCalibrateResult_getResult (
  LLRP_tSAutoCalibrateResult *pThis);

extern LLRP_tResultCode
LLRP_AutoCalibrateResult_setResult (
  LLRP_tSAutoCalibrateResult *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdAutoCalibrateResult_Power;

extern llrp_s16_t
LLRP_AutoCalibrateResult_getPower (
  LLRP_tSAutoCalibrateResult *pThis);

extern LLRP_tResultCode
LLRP_AutoCalibrateResult_setPower (
  LLRP_tSAutoCalibrateResult *pThis,
  llrp_s16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdAutoCalibrateResult_K0;

extern llrp_u16_t
LLRP_AutoCalibrateResult_getK0 (
  LLRP_tSAutoCalibrateResult *pThis);

extern LLRP_tResultCode
LLRP_AutoCalibrateResult_setK0 (
  LLRP_tSAutoCalibrateResult *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_SNetDelayTimeTestACK
{
    LLRP_tSParameter hdr;
  
    llrp_u32_t DelayTime;

    llrp_u32_t DelayTime1;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdNetDelayTimeTestACK;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdNetDelayTimeTestACK[];

extern LLRP_tSNetDelayTimeTestACK *
LLRP_NetDelayTimeTestACK_construct (void);

extern void
LLRP_NetDelayTimeTestACK_destruct (
 LLRP_tSNetDelayTimeTestACK * pThis);

extern void
LLRP_NetDelayTimeTestACK_decodeFields (
 LLRP_tSNetDelayTimeTestACK * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_NetDelayTimeTestACK_assimilateSubParameters (
 LLRP_tSNetDelayTimeTestACK * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_NetDelayTimeTestACK_encode (
  const LLRP_tSNetDelayTimeTestACK *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_NetDelayTimeTestACK_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdNetDelayTimeTestACK_DelayTime;

extern llrp_u32_t
LLRP_NetDelayTimeTestACK_getDelayTime (
  LLRP_tSNetDelayTimeTestACK *pThis);

extern LLRP_tResultCode
LLRP_NetDelayTimeTestACK_setDelayTime (
  LLRP_tSNetDelayTimeTestACK *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdNetDelayTimeTestACK_DelayTime1;

extern llrp_u32_t
LLRP_NetDelayTimeTestACK_getDelayTime1 (
  LLRP_tSNetDelayTimeTestACK *pThis);

extern LLRP_tResultCode
LLRP_NetDelayTimeTestACK_setDelayTime1 (
  LLRP_tSNetDelayTimeTestACK *pThis,
  llrp_u32_t Value);

  


  
struct LLRP_SPllTestACK
{
    LLRP_tSParameter hdr;
  
    llrp_u32_t TestCount;

    llrp_u16_t PllFakeLockedCount;

    llrp_u16_t PllErrCount;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdPllTestACK;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdPllTestACK[];

extern LLRP_tSPllTestACK *
LLRP_PllTestACK_construct (void);

extern void
LLRP_PllTestACK_destruct (
 LLRP_tSPllTestACK * pThis);

extern void
LLRP_PllTestACK_decodeFields (
 LLRP_tSPllTestACK * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_PllTestACK_assimilateSubParameters (
 LLRP_tSPllTestACK * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_PllTestACK_encode (
  const LLRP_tSPllTestACK *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_PllTestACK_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdPllTestACK_TestCount;

extern llrp_u32_t
LLRP_PllTestACK_getTestCount (
  LLRP_tSPllTestACK *pThis);

extern LLRP_tResultCode
LLRP_PllTestACK_setTestCount (
  LLRP_tSPllTestACK *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdPllTestACK_PllFakeLockedCount;

extern llrp_u16_t
LLRP_PllTestACK_getPllFakeLockedCount (
  LLRP_tSPllTestACK *pThis);

extern LLRP_tResultCode
LLRP_PllTestACK_setPllFakeLockedCount (
  LLRP_tSPllTestACK *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdPllTestACK_PllErrCount;

extern llrp_u16_t
LLRP_PllTestACK_getPllErrCount (
  LLRP_tSPllTestACK *pThis);

extern LLRP_tResultCode
LLRP_PllTestACK_setPllErrCount (
  LLRP_tSPllTestACK *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_STempSensorTestACK
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t Result;

    llrp_u8_t Sign;

    llrp_u16_t WTemp;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdTempSensorTestACK;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdTempSensorTestACK[];

extern LLRP_tSTempSensorTestACK *
LLRP_TempSensorTestACK_construct (void);

extern void
LLRP_TempSensorTestACK_destruct (
 LLRP_tSTempSensorTestACK * pThis);

extern void
LLRP_TempSensorTestACK_decodeFields (
 LLRP_tSTempSensorTestACK * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_TempSensorTestACK_assimilateSubParameters (
 LLRP_tSTempSensorTestACK * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_TempSensorTestACK_encode (
  const LLRP_tSTempSensorTestACK *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_TempSensorTestACK_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdTempSensorTestACK_Result;

extern llrp_u8_t
LLRP_TempSensorTestACK_getResult (
  LLRP_tSTempSensorTestACK *pThis);

extern LLRP_tResultCode
LLRP_TempSensorTestACK_setResult (
  LLRP_tSTempSensorTestACK *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdTempSensorTestACK_Sign;

extern llrp_u8_t
LLRP_TempSensorTestACK_getSign (
  LLRP_tSTempSensorTestACK *pThis);

extern LLRP_tResultCode
LLRP_TempSensorTestACK_setSign (
  LLRP_tSTempSensorTestACK *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdTempSensorTestACK_WTemp;

extern llrp_u16_t
LLRP_TempSensorTestACK_getWTemp (
  LLRP_tSTempSensorTestACK *pThis);

extern LLRP_tResultCode
LLRP_TempSensorTestACK_setWTemp (
  LLRP_tSTempSensorTestACK *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_SPowerIDReadTestACK
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t PowerID;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdPowerIDReadTestACK;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdPowerIDReadTestACK[];

extern LLRP_tSPowerIDReadTestACK *
LLRP_PowerIDReadTestACK_construct (void);

extern void
LLRP_PowerIDReadTestACK_destruct (
 LLRP_tSPowerIDReadTestACK * pThis);

extern void
LLRP_PowerIDReadTestACK_decodeFields (
 LLRP_tSPowerIDReadTestACK * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_PowerIDReadTestACK_assimilateSubParameters (
 LLRP_tSPowerIDReadTestACK * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_PowerIDReadTestACK_encode (
  const LLRP_tSPowerIDReadTestACK *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_PowerIDReadTestACK_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdPowerIDReadTestACK_PowerID;

extern llrp_u8_t
LLRP_PowerIDReadTestACK_getPowerID (
  LLRP_tSPowerIDReadTestACK *pThis);

extern LLRP_tResultCode
LLRP_PowerIDReadTestACK_setPowerID (
  LLRP_tSPowerIDReadTestACK *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SProtoclArmVersionTestACK
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t MaxVersion;

    llrp_u8_t MinVersion;

    llrp_u8_t SubVersion;

    llrp_u8_t Build;

    llrp_u8_t HardVersion;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdProtoclArmVersionTestACK;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdProtoclArmVersionTestACK[];

extern LLRP_tSProtoclArmVersionTestACK *
LLRP_ProtoclArmVersionTestACK_construct (void);

extern void
LLRP_ProtoclArmVersionTestACK_destruct (
 LLRP_tSProtoclArmVersionTestACK * pThis);

extern void
LLRP_ProtoclArmVersionTestACK_decodeFields (
 LLRP_tSProtoclArmVersionTestACK * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_ProtoclArmVersionTestACK_assimilateSubParameters (
 LLRP_tSProtoclArmVersionTestACK * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_ProtoclArmVersionTestACK_encode (
  const LLRP_tSProtoclArmVersionTestACK *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_ProtoclArmVersionTestACK_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdProtoclArmVersionTestACK_MaxVersion;

extern llrp_u8_t
LLRP_ProtoclArmVersionTestACK_getMaxVersion (
  LLRP_tSProtoclArmVersionTestACK *pThis);

extern LLRP_tResultCode
LLRP_ProtoclArmVersionTestACK_setMaxVersion (
  LLRP_tSProtoclArmVersionTestACK *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdProtoclArmVersionTestACK_MinVersion;

extern llrp_u8_t
LLRP_ProtoclArmVersionTestACK_getMinVersion (
  LLRP_tSProtoclArmVersionTestACK *pThis);

extern LLRP_tResultCode
LLRP_ProtoclArmVersionTestACK_setMinVersion (
  LLRP_tSProtoclArmVersionTestACK *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdProtoclArmVersionTestACK_SubVersion;

extern llrp_u8_t
LLRP_ProtoclArmVersionTestACK_getSubVersion (
  LLRP_tSProtoclArmVersionTestACK *pThis);

extern LLRP_tResultCode
LLRP_ProtoclArmVersionTestACK_setSubVersion (
  LLRP_tSProtoclArmVersionTestACK *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdProtoclArmVersionTestACK_Build;

extern llrp_u8_t
LLRP_ProtoclArmVersionTestACK_getBuild (
  LLRP_tSProtoclArmVersionTestACK *pThis);

extern LLRP_tResultCode
LLRP_ProtoclArmVersionTestACK_setBuild (
  LLRP_tSProtoclArmVersionTestACK *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdProtoclArmVersionTestACK_HardVersion;

extern llrp_u8_t
LLRP_ProtoclArmVersionTestACK_getHardVersion (
  LLRP_tSProtoclArmVersionTestACK *pThis);

extern LLRP_tResultCode
LLRP_ProtoclArmVersionTestACK_setHardVersion (
  LLRP_tSProtoclArmVersionTestACK *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SZXRIS6601ReportPwrTblAck
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t Result;

  
    LLRP_tSZXRIS6601PowerTable * pZXRIS6601PowerTable;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdZXRIS6601ReportPwrTblAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdZXRIS6601ReportPwrTblAck[];

extern LLRP_tSZXRIS6601ReportPwrTblAck *
LLRP_ZXRIS6601ReportPwrTblAck_construct (void);

extern void
LLRP_ZXRIS6601ReportPwrTblAck_destruct (
 LLRP_tSZXRIS6601ReportPwrTblAck * pThis);

extern void
LLRP_ZXRIS6601ReportPwrTblAck_decodeFields (
 LLRP_tSZXRIS6601ReportPwrTblAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_ZXRIS6601ReportPwrTblAck_assimilateSubParameters (
 LLRP_tSZXRIS6601ReportPwrTblAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_ZXRIS6601ReportPwrTblAck_encode (
  const LLRP_tSZXRIS6601ReportPwrTblAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_ZXRIS6601ReportPwrTblAck_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdZXRIS6601ReportPwrTblAck_Result;

extern llrp_u8_t
LLRP_ZXRIS6601ReportPwrTblAck_getResult (
  LLRP_tSZXRIS6601ReportPwrTblAck *pThis);

extern LLRP_tResultCode
LLRP_ZXRIS6601ReportPwrTblAck_setResult (
  LLRP_tSZXRIS6601ReportPwrTblAck *pThis,
  llrp_u8_t Value);

  
extern LLRP_tSZXRIS6601PowerTable *
LLRP_ZXRIS6601ReportPwrTblAck_getZXRIS6601PowerTable (
  LLRP_tSZXRIS6601ReportPwrTblAck *pThis);

extern LLRP_tResultCode
LLRP_ZXRIS6601ReportPwrTblAck_setZXRIS6601PowerTable (
  LLRP_tSZXRIS6601ReportPwrTblAck *pThis,
  LLRP_tSZXRIS6601PowerTable *pValue);



  
struct LLRP_STestKeyboardAck
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t KeyPushedDown;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdTestKeyboardAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdTestKeyboardAck[];

extern LLRP_tSTestKeyboardAck *
LLRP_TestKeyboardAck_construct (void);

extern void
LLRP_TestKeyboardAck_destruct (
 LLRP_tSTestKeyboardAck * pThis);

extern void
LLRP_TestKeyboardAck_decodeFields (
 LLRP_tSTestKeyboardAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_TestKeyboardAck_assimilateSubParameters (
 LLRP_tSTestKeyboardAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_TestKeyboardAck_encode (
  const LLRP_tSTestKeyboardAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_TestKeyboardAck_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdTestKeyboardAck_KeyPushedDown;

extern llrp_u8_t
LLRP_TestKeyboardAck_getKeyPushedDown (
  LLRP_tSTestKeyboardAck *pThis);

extern LLRP_tResultCode
LLRP_TestKeyboardAck_setKeyPushedDown (
  LLRP_tSTestKeyboardAck *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_STestTouchScrAck
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t ZonePushedDown;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdTestTouchScrAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdTestTouchScrAck[];

extern LLRP_tSTestTouchScrAck *
LLRP_TestTouchScrAck_construct (void);

extern void
LLRP_TestTouchScrAck_destruct (
 LLRP_tSTestTouchScrAck * pThis);

extern void
LLRP_TestTouchScrAck_decodeFields (
 LLRP_tSTestTouchScrAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_TestTouchScrAck_assimilateSubParameters (
 LLRP_tSTestTouchScrAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_TestTouchScrAck_encode (
  const LLRP_tSTestTouchScrAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_TestTouchScrAck_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdTestTouchScrAck_ZonePushedDown;

extern llrp_u8_t
LLRP_TestTouchScrAck_getZonePushedDown (
  LLRP_tSTestTouchScrAck *pThis);

extern LLRP_tResultCode
LLRP_TestTouchScrAck_setZonePushedDown (
  LLRP_tSTestTouchScrAck *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_STbTestItem
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t TestID;

  
    LLRP_tSParameter * pTbTestdata;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdTbTestItem;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdTbTestItem[];

extern LLRP_tSTbTestItem *
LLRP_TbTestItem_construct (void);

extern void
LLRP_TbTestItem_destruct (
 LLRP_tSTbTestItem * pThis);

extern void
LLRP_TbTestItem_decodeFields (
 LLRP_tSTbTestItem * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_TbTestItem_assimilateSubParameters (
 LLRP_tSTbTestItem * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_TbTestItem_encode (
  const LLRP_tSTbTestItem *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_TbTestItem_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdTbTestItem_TestID;

extern llrp_u16_t
LLRP_TbTestItem_getTestID (
  LLRP_tSTbTestItem *pThis);

extern LLRP_tResultCode
LLRP_TbTestItem_setTestID (
  LLRP_tSTbTestItem *pThis,
  llrp_u16_t Value);

  
extern LLRP_tSParameter *
LLRP_TbTestItem_getTbTestdata (
  LLRP_tSTbTestItem *pThis);

extern LLRP_tResultCode
LLRP_TbTestItem_setTbTestdata (
  LLRP_tSTbTestItem *pThis,
  LLRP_tSParameter *pValue);



  
struct LLRP_STbTestItemACK
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t TestID;

  
    LLRP_tSParameter * pTbTestdataAck;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdTbTestItemACK;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdTbTestItemACK[];

extern LLRP_tSTbTestItemACK *
LLRP_TbTestItemACK_construct (void);

extern void
LLRP_TbTestItemACK_destruct (
 LLRP_tSTbTestItemACK * pThis);

extern void
LLRP_TbTestItemACK_decodeFields (
 LLRP_tSTbTestItemACK * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_TbTestItemACK_assimilateSubParameters (
 LLRP_tSTbTestItemACK * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_TbTestItemACK_encode (
  const LLRP_tSTbTestItemACK *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_TbTestItemACK_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdTbTestItemACK_TestID;

extern llrp_u16_t
LLRP_TbTestItemACK_getTestID (
  LLRP_tSTbTestItemACK *pThis);

extern LLRP_tResultCode
LLRP_TbTestItemACK_setTestID (
  LLRP_tSTbTestItemACK *pThis,
  llrp_u16_t Value);

  
extern LLRP_tSParameter *
LLRP_TbTestItemACK_getTbTestdataAck (
  LLRP_tSTbTestItemACK *pThis);

extern LLRP_tResultCode
LLRP_TbTestItemACK_setTbTestdataAck (
  LLRP_tSTbTestItemACK *pThis,
  LLRP_tSParameter *pValue);



  
struct LLRP_SSetDeviceType
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t ReaderType;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdSetDeviceType;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSetDeviceType[];

extern LLRP_tSSetDeviceType *
LLRP_SetDeviceType_construct (void);

extern void
LLRP_SetDeviceType_destruct (
 LLRP_tSSetDeviceType * pThis);

extern void
LLRP_SetDeviceType_decodeFields (
 LLRP_tSSetDeviceType * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SetDeviceType_assimilateSubParameters (
 LLRP_tSSetDeviceType * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SetDeviceType_encode (
  const LLRP_tSSetDeviceType *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_SetDeviceType_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdSetDeviceType_ReaderType;

extern llrp_u8_t
LLRP_SetDeviceType_getReaderType (
  LLRP_tSSetDeviceType *pThis);

extern LLRP_tResultCode
LLRP_SetDeviceType_setReaderType (
  LLRP_tSSetDeviceType *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SVersionDwn
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t DeviceType;

    llrp_u8_t DownloadFlag;

    llrp_u32_t Baudrate;

    llrp_u32_t Ip;

    llrp_u32_t ServerIP;

    llrp_u32_t Mask;

    llrp_u32_t GateWayIP;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdVersionDwn;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdVersionDwn[];

extern LLRP_tSVersionDwn *
LLRP_VersionDwn_construct (void);

extern void
LLRP_VersionDwn_destruct (
 LLRP_tSVersionDwn * pThis);

extern void
LLRP_VersionDwn_decodeFields (
 LLRP_tSVersionDwn * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_VersionDwn_assimilateSubParameters (
 LLRP_tSVersionDwn * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_VersionDwn_encode (
  const LLRP_tSVersionDwn *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_VersionDwn_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdVersionDwn_DeviceType;

extern llrp_u8_t
LLRP_VersionDwn_getDeviceType (
  LLRP_tSVersionDwn *pThis);

extern LLRP_tResultCode
LLRP_VersionDwn_setDeviceType (
  LLRP_tSVersionDwn *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdVersionDwn_DownloadFlag;

extern llrp_u8_t
LLRP_VersionDwn_getDownloadFlag (
  LLRP_tSVersionDwn *pThis);

extern LLRP_tResultCode
LLRP_VersionDwn_setDownloadFlag (
  LLRP_tSVersionDwn *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdVersionDwn_Baudrate;

extern llrp_u32_t
LLRP_VersionDwn_getBaudrate (
  LLRP_tSVersionDwn *pThis);

extern LLRP_tResultCode
LLRP_VersionDwn_setBaudrate (
  LLRP_tSVersionDwn *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdVersionDwn_Ip;

extern llrp_u32_t
LLRP_VersionDwn_getIp (
  LLRP_tSVersionDwn *pThis);

extern LLRP_tResultCode
LLRP_VersionDwn_setIp (
  LLRP_tSVersionDwn *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdVersionDwn_ServerIP;

extern llrp_u32_t
LLRP_VersionDwn_getServerIP (
  LLRP_tSVersionDwn *pThis);

extern LLRP_tResultCode
LLRP_VersionDwn_setServerIP (
  LLRP_tSVersionDwn *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdVersionDwn_Mask;

extern llrp_u32_t
LLRP_VersionDwn_getMask (
  LLRP_tSVersionDwn *pThis);

extern LLRP_tResultCode
LLRP_VersionDwn_setMask (
  LLRP_tSVersionDwn *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdVersionDwn_GateWayIP;

extern llrp_u32_t
LLRP_VersionDwn_getGateWayIP (
  LLRP_tSVersionDwn *pThis);

extern LLRP_tResultCode
LLRP_VersionDwn_setGateWayIP (
  LLRP_tSVersionDwn *pThis,
  llrp_u32_t Value);

  


  
struct LLRP_SRs485Test
{
    LLRP_tSParameter hdr;
  
    llrp_u32_t Baudrate;

    llrp_u8_t SerialNum;

    llrp_u8_t Impedance;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdRs485Test;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdRs485Test[];

extern LLRP_tSRs485Test *
LLRP_Rs485Test_construct (void);

extern void
LLRP_Rs485Test_destruct (
 LLRP_tSRs485Test * pThis);

extern void
LLRP_Rs485Test_decodeFields (
 LLRP_tSRs485Test * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_Rs485Test_assimilateSubParameters (
 LLRP_tSRs485Test * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_Rs485Test_encode (
  const LLRP_tSRs485Test *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_Rs485Test_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdRs485Test_Baudrate;

extern llrp_u32_t
LLRP_Rs485Test_getBaudrate (
  LLRP_tSRs485Test *pThis);

extern LLRP_tResultCode
LLRP_Rs485Test_setBaudrate (
  LLRP_tSRs485Test *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdRs485Test_SerialNum;

extern llrp_u8_t
LLRP_Rs485Test_getSerialNum (
  LLRP_tSRs485Test *pThis);

extern LLRP_tResultCode
LLRP_Rs485Test_setSerialNum (
  LLRP_tSRs485Test *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdRs485Test_Impedance;

extern llrp_u8_t
LLRP_Rs485Test_getImpedance (
  LLRP_tSRs485Test *pThis);

extern LLRP_tResultCode
LLRP_Rs485Test_setImpedance (
  LLRP_tSRs485Test *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SGpioTest
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t CmdType;

    llrp_u8_t TestData;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdGpioTest;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdGpioTest[];

extern LLRP_tSGpioTest *
LLRP_GpioTest_construct (void);

extern void
LLRP_GpioTest_destruct (
 LLRP_tSGpioTest * pThis);

extern void
LLRP_GpioTest_decodeFields (
 LLRP_tSGpioTest * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_GpioTest_assimilateSubParameters (
 LLRP_tSGpioTest * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_GpioTest_encode (
  const LLRP_tSGpioTest *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_GpioTest_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdGpioTest_CmdType;

extern llrp_u8_t
LLRP_GpioTest_getCmdType (
  LLRP_tSGpioTest *pThis);

extern LLRP_tResultCode
LLRP_GpioTest_setCmdType (
  LLRP_tSGpioTest *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdGpioTest_TestData;

extern llrp_u8_t
LLRP_GpioTest_getTestData (
  LLRP_tSGpioTest *pThis);

extern LLRP_tResultCode
LLRP_GpioTest_setTestData (
  LLRP_tSGpioTest *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SAntSelect
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t AntNum;

    llrp_u8_t TestDevice;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdAntSelect;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdAntSelect[];

extern LLRP_tSAntSelect *
LLRP_AntSelect_construct (void);

extern void
LLRP_AntSelect_destruct (
 LLRP_tSAntSelect * pThis);

extern void
LLRP_AntSelect_decodeFields (
 LLRP_tSAntSelect * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_AntSelect_assimilateSubParameters (
 LLRP_tSAntSelect * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_AntSelect_encode (
  const LLRP_tSAntSelect *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_AntSelect_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdAntSelect_AntNum;

extern llrp_u8_t
LLRP_AntSelect_getAntNum (
  LLRP_tSAntSelect *pThis);

extern LLRP_tResultCode
LLRP_AntSelect_setAntNum (
  LLRP_tSAntSelect *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdAntSelect_TestDevice;

extern llrp_u8_t
LLRP_AntSelect_getTestDevice (
  LLRP_tSAntSelect *pThis);

extern LLRP_tResultCode
LLRP_AntSelect_setTestDevice (
  LLRP_tSAntSelect *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SAntInPositon
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t Ant1;

    llrp_u8_t Ant2;

    llrp_u8_t Ant3;

    llrp_u8_t Ant4;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdAntInPositon;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdAntInPositon[];

extern LLRP_tSAntInPositon *
LLRP_AntInPositon_construct (void);

extern void
LLRP_AntInPositon_destruct (
 LLRP_tSAntInPositon * pThis);

extern void
LLRP_AntInPositon_decodeFields (
 LLRP_tSAntInPositon * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_AntInPositon_assimilateSubParameters (
 LLRP_tSAntInPositon * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_AntInPositon_encode (
  const LLRP_tSAntInPositon *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_AntInPositon_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdAntInPositon_Ant1;

extern llrp_u8_t
LLRP_AntInPositon_getAnt1 (
  LLRP_tSAntInPositon *pThis);

extern LLRP_tResultCode
LLRP_AntInPositon_setAnt1 (
  LLRP_tSAntInPositon *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdAntInPositon_Ant2;

extern llrp_u8_t
LLRP_AntInPositon_getAnt2 (
  LLRP_tSAntInPositon *pThis);

extern LLRP_tResultCode
LLRP_AntInPositon_setAnt2 (
  LLRP_tSAntInPositon *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdAntInPositon_Ant3;

extern llrp_u8_t
LLRP_AntInPositon_getAnt3 (
  LLRP_tSAntInPositon *pThis);

extern LLRP_tResultCode
LLRP_AntInPositon_setAnt3 (
  LLRP_tSAntInPositon *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdAntInPositon_Ant4;

extern llrp_u8_t
LLRP_AntInPositon_getAnt4 (
  LLRP_tSAntInPositon *pThis);

extern LLRP_tResultCode
LLRP_AntInPositon_setAnt4 (
  LLRP_tSAntInPositon *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SSetDeviceTypeAck
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t Result;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdSetDeviceTypeAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSetDeviceTypeAck[];

extern LLRP_tSSetDeviceTypeAck *
LLRP_SetDeviceTypeAck_construct (void);

extern void
LLRP_SetDeviceTypeAck_destruct (
 LLRP_tSSetDeviceTypeAck * pThis);

extern void
LLRP_SetDeviceTypeAck_decodeFields (
 LLRP_tSSetDeviceTypeAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SetDeviceTypeAck_assimilateSubParameters (
 LLRP_tSSetDeviceTypeAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SetDeviceTypeAck_encode (
  const LLRP_tSSetDeviceTypeAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_SetDeviceTypeAck_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdSetDeviceTypeAck_Result;

extern llrp_u8_t
LLRP_SetDeviceTypeAck_getResult (
  LLRP_tSSetDeviceTypeAck *pThis);

extern LLRP_tResultCode
LLRP_SetDeviceTypeAck_setResult (
  LLRP_tSSetDeviceTypeAck *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SVersionDwnStart
{
    LLRP_tSParameter hdr;
  
  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdVersionDwnStart;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdVersionDwnStart[];

extern LLRP_tSVersionDwnStart *
LLRP_VersionDwnStart_construct (void);

extern void
LLRP_VersionDwnStart_destruct (
 LLRP_tSVersionDwnStart * pThis);

extern void
LLRP_VersionDwnStart_decodeFields (
 LLRP_tSVersionDwnStart * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_VersionDwnStart_assimilateSubParameters (
 LLRP_tSVersionDwnStart * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_VersionDwnStart_encode (
  const LLRP_tSVersionDwnStart *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_VersionDwnStart_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
  


  
struct LLRP_SVersionDwnHeartbeatAck
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t Result;

    llrp_u8_t Step;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdVersionDwnHeartbeatAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdVersionDwnHeartbeatAck[];

extern LLRP_tSVersionDwnHeartbeatAck *
LLRP_VersionDwnHeartbeatAck_construct (void);

extern void
LLRP_VersionDwnHeartbeatAck_destruct (
 LLRP_tSVersionDwnHeartbeatAck * pThis);

extern void
LLRP_VersionDwnHeartbeatAck_decodeFields (
 LLRP_tSVersionDwnHeartbeatAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_VersionDwnHeartbeatAck_assimilateSubParameters (
 LLRP_tSVersionDwnHeartbeatAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_VersionDwnHeartbeatAck_encode (
  const LLRP_tSVersionDwnHeartbeatAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_VersionDwnHeartbeatAck_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdVersionDwnHeartbeatAck_Result;

extern llrp_u8_t
LLRP_VersionDwnHeartbeatAck_getResult (
  LLRP_tSVersionDwnHeartbeatAck *pThis);

extern LLRP_tResultCode
LLRP_VersionDwnHeartbeatAck_setResult (
  LLRP_tSVersionDwnHeartbeatAck *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdVersionDwnHeartbeatAck_Step;

extern llrp_u8_t
LLRP_VersionDwnHeartbeatAck_getStep (
  LLRP_tSVersionDwnHeartbeatAck *pThis);

extern LLRP_tResultCode
LLRP_VersionDwnHeartbeatAck_setStep (
  LLRP_tSVersionDwnHeartbeatAck *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SVersionDwnChipMsgAck
{
    LLRP_tSParameter hdr;
  
    llrp_u32_t CpuClock;

    llrp_u32_t FlashSize;

    llrp_u32_t SdramSize;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdVersionDwnChipMsgAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdVersionDwnChipMsgAck[];

extern LLRP_tSVersionDwnChipMsgAck *
LLRP_VersionDwnChipMsgAck_construct (void);

extern void
LLRP_VersionDwnChipMsgAck_destruct (
 LLRP_tSVersionDwnChipMsgAck * pThis);

extern void
LLRP_VersionDwnChipMsgAck_decodeFields (
 LLRP_tSVersionDwnChipMsgAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_VersionDwnChipMsgAck_assimilateSubParameters (
 LLRP_tSVersionDwnChipMsgAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_VersionDwnChipMsgAck_encode (
  const LLRP_tSVersionDwnChipMsgAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_VersionDwnChipMsgAck_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdVersionDwnChipMsgAck_CpuClock;

extern llrp_u32_t
LLRP_VersionDwnChipMsgAck_getCpuClock (
  LLRP_tSVersionDwnChipMsgAck *pThis);

extern LLRP_tResultCode
LLRP_VersionDwnChipMsgAck_setCpuClock (
  LLRP_tSVersionDwnChipMsgAck *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdVersionDwnChipMsgAck_FlashSize;

extern llrp_u32_t
LLRP_VersionDwnChipMsgAck_getFlashSize (
  LLRP_tSVersionDwnChipMsgAck *pThis);

extern LLRP_tResultCode
LLRP_VersionDwnChipMsgAck_setFlashSize (
  LLRP_tSVersionDwnChipMsgAck *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdVersionDwnChipMsgAck_SdramSize;

extern llrp_u32_t
LLRP_VersionDwnChipMsgAck_getSdramSize (
  LLRP_tSVersionDwnChipMsgAck *pThis);

extern LLRP_tResultCode
LLRP_VersionDwnChipMsgAck_setSdramSize (
  LLRP_tSVersionDwnChipMsgAck *pThis,
  llrp_u32_t Value);

  


  
struct LLRP_SVersionDwnAck
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t RS232Result;

    llrp_u8_t SdramResult;

    llrp_u8_t FlashResult;

    llrp_u8_t DownResult;

    llrp_u32_t SdramAddr;

    llrp_u32_t FlashAddr;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdVersionDwnAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdVersionDwnAck[];

extern LLRP_tSVersionDwnAck *
LLRP_VersionDwnAck_construct (void);

extern void
LLRP_VersionDwnAck_destruct (
 LLRP_tSVersionDwnAck * pThis);

extern void
LLRP_VersionDwnAck_decodeFields (
 LLRP_tSVersionDwnAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_VersionDwnAck_assimilateSubParameters (
 LLRP_tSVersionDwnAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_VersionDwnAck_encode (
  const LLRP_tSVersionDwnAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_VersionDwnAck_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdVersionDwnAck_RS232Result;

extern llrp_u8_t
LLRP_VersionDwnAck_getRS232Result (
  LLRP_tSVersionDwnAck *pThis);

extern LLRP_tResultCode
LLRP_VersionDwnAck_setRS232Result (
  LLRP_tSVersionDwnAck *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdVersionDwnAck_SdramResult;

extern llrp_u8_t
LLRP_VersionDwnAck_getSdramResult (
  LLRP_tSVersionDwnAck *pThis);

extern LLRP_tResultCode
LLRP_VersionDwnAck_setSdramResult (
  LLRP_tSVersionDwnAck *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdVersionDwnAck_FlashResult;

extern llrp_u8_t
LLRP_VersionDwnAck_getFlashResult (
  LLRP_tSVersionDwnAck *pThis);

extern LLRP_tResultCode
LLRP_VersionDwnAck_setFlashResult (
  LLRP_tSVersionDwnAck *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdVersionDwnAck_DownResult;

extern llrp_u8_t
LLRP_VersionDwnAck_getDownResult (
  LLRP_tSVersionDwnAck *pThis);

extern LLRP_tResultCode
LLRP_VersionDwnAck_setDownResult (
  LLRP_tSVersionDwnAck *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdVersionDwnAck_SdramAddr;

extern llrp_u32_t
LLRP_VersionDwnAck_getSdramAddr (
  LLRP_tSVersionDwnAck *pThis);

extern LLRP_tResultCode
LLRP_VersionDwnAck_setSdramAddr (
  LLRP_tSVersionDwnAck *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdVersionDwnAck_FlashAddr;

extern llrp_u32_t
LLRP_VersionDwnAck_getFlashAddr (
  LLRP_tSVersionDwnAck *pThis);

extern LLRP_tResultCode
LLRP_VersionDwnAck_setFlashAddr (
  LLRP_tSVersionDwnAck *pThis,
  llrp_u32_t Value);

  


  
struct LLRP_SRs485TestAck
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t Rs485Result;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdRs485TestAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdRs485TestAck[];

extern LLRP_tSRs485TestAck *
LLRP_Rs485TestAck_construct (void);

extern void
LLRP_Rs485TestAck_destruct (
 LLRP_tSRs485TestAck * pThis);

extern void
LLRP_Rs485TestAck_decodeFields (
 LLRP_tSRs485TestAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_Rs485TestAck_assimilateSubParameters (
 LLRP_tSRs485TestAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_Rs485TestAck_encode (
  const LLRP_tSRs485TestAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_Rs485TestAck_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdRs485TestAck_Rs485Result;

extern llrp_u8_t
LLRP_Rs485TestAck_getRs485Result (
  LLRP_tSRs485TestAck *pThis);

extern LLRP_tResultCode
LLRP_Rs485TestAck_setRs485Result (
  LLRP_tSRs485TestAck *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SGpioTestAck
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t CmdType;

    llrp_u8_t ACKData;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdGpioTestAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdGpioTestAck[];

extern LLRP_tSGpioTestAck *
LLRP_GpioTestAck_construct (void);

extern void
LLRP_GpioTestAck_destruct (
 LLRP_tSGpioTestAck * pThis);

extern void
LLRP_GpioTestAck_decodeFields (
 LLRP_tSGpioTestAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_GpioTestAck_assimilateSubParameters (
 LLRP_tSGpioTestAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_GpioTestAck_encode (
  const LLRP_tSGpioTestAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_GpioTestAck_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdGpioTestAck_CmdType;

extern llrp_u8_t
LLRP_GpioTestAck_getCmdType (
  LLRP_tSGpioTestAck *pThis);

extern LLRP_tResultCode
LLRP_GpioTestAck_setCmdType (
  LLRP_tSGpioTestAck *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdGpioTestAck_ACKData;

extern llrp_u8_t
LLRP_GpioTestAck_getACKData (
  LLRP_tSGpioTestAck *pThis);

extern LLRP_tResultCode
LLRP_GpioTestAck_setACKData (
  LLRP_tSGpioTestAck *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SAntSelectAck
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t AntSelectResult;

    llrp_u8_t AntNum;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdAntSelectAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdAntSelectAck[];

extern LLRP_tSAntSelectAck *
LLRP_AntSelectAck_construct (void);

extern void
LLRP_AntSelectAck_destruct (
 LLRP_tSAntSelectAck * pThis);

extern void
LLRP_AntSelectAck_decodeFields (
 LLRP_tSAntSelectAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_AntSelectAck_assimilateSubParameters (
 LLRP_tSAntSelectAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_AntSelectAck_encode (
  const LLRP_tSAntSelectAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_AntSelectAck_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdAntSelectAck_AntSelectResult;

extern llrp_u8_t
LLRP_AntSelectAck_getAntSelectResult (
  LLRP_tSAntSelectAck *pThis);

extern LLRP_tResultCode
LLRP_AntSelectAck_setAntSelectResult (
  LLRP_tSAntSelectAck *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdAntSelectAck_AntNum;

extern llrp_u8_t
LLRP_AntSelectAck_getAntNum (
  LLRP_tSAntSelectAck *pThis);

extern LLRP_tResultCode
LLRP_AntSelectAck_setAntNum (
  LLRP_tSAntSelectAck *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SAntInPositonAck
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t AntInPositionResult;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdAntInPositonAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdAntInPositonAck[];

extern LLRP_tSAntInPositonAck *
LLRP_AntInPositonAck_construct (void);

extern void
LLRP_AntInPositonAck_destruct (
 LLRP_tSAntInPositonAck * pThis);

extern void
LLRP_AntInPositonAck_decodeFields (
 LLRP_tSAntInPositonAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_AntInPositonAck_assimilateSubParameters (
 LLRP_tSAntInPositonAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_AntInPositonAck_encode (
  const LLRP_tSAntInPositonAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_AntInPositonAck_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdAntInPositonAck_AntInPositionResult;

extern llrp_u8_t
LLRP_AntInPositonAck_getAntInPositionResult (
  LLRP_tSAntInPositonAck *pThis);

extern LLRP_tResultCode
LLRP_AntInPositonAck_setAntInPositionResult (
  LLRP_tSAntInPositonAck *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SDelAlarmInfo
{
    LLRP_tSParameter hdr;
  
  
    LLRP_tSDelAlarmAid * pDelAlarmAid;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdDelAlarmInfo;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdDelAlarmInfo[];

extern LLRP_tSDelAlarmInfo *
LLRP_DelAlarmInfo_construct (void);

extern void
LLRP_DelAlarmInfo_destruct (
 LLRP_tSDelAlarmInfo * pThis);

extern void
LLRP_DelAlarmInfo_decodeFields (
 LLRP_tSDelAlarmInfo * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_DelAlarmInfo_assimilateSubParameters (
 LLRP_tSDelAlarmInfo * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_DelAlarmInfo_encode (
  const LLRP_tSDelAlarmInfo *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_DelAlarmInfo_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
  
extern LLRP_tSDelAlarmAid *
LLRP_DelAlarmInfo_getDelAlarmAid (
  LLRP_tSDelAlarmInfo *pThis);

extern LLRP_tResultCode
LLRP_DelAlarmInfo_setDelAlarmAid (
  LLRP_tSDelAlarmInfo *pThis,
  LLRP_tSDelAlarmAid *pValue);



  
struct LLRP_SDelAlarmAid
{
    LLRP_tSParameter hdr;
  
    llrp_u32_t Aid;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdDelAlarmAid;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdDelAlarmAid[];

extern LLRP_tSDelAlarmAid *
LLRP_DelAlarmAid_construct (void);

extern void
LLRP_DelAlarmAid_destruct (
 LLRP_tSDelAlarmAid * pThis);

extern void
LLRP_DelAlarmAid_decodeFields (
 LLRP_tSDelAlarmAid * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_DelAlarmAid_assimilateSubParameters (
 LLRP_tSDelAlarmAid * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_DelAlarmAid_encode (
  const LLRP_tSDelAlarmAid *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_DelAlarmAid_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdDelAlarmAid_Aid;

extern llrp_u32_t
LLRP_DelAlarmAid_getAid (
  LLRP_tSDelAlarmAid *pThis);

extern LLRP_tResultCode
LLRP_DelAlarmAid_setAid (
  LLRP_tSDelAlarmAid *pThis,
  llrp_u32_t Value);

  


  
struct LLRP_SSyncInfo
{
    LLRP_tSParameter hdr;
  
  
    LLRP_tSSynAid * pSynAid;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdSyncInfo;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSyncInfo[];

extern LLRP_tSSyncInfo *
LLRP_SyncInfo_construct (void);

extern void
LLRP_SyncInfo_destruct (
 LLRP_tSSyncInfo * pThis);

extern void
LLRP_SyncInfo_decodeFields (
 LLRP_tSSyncInfo * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SyncInfo_assimilateSubParameters (
 LLRP_tSSyncInfo * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SyncInfo_encode (
  const LLRP_tSSyncInfo *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_SyncInfo_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
  
extern LLRP_tSSynAid *
LLRP_SyncInfo_getSynAid (
  LLRP_tSSyncInfo *pThis);

extern LLRP_tResultCode
LLRP_SyncInfo_setSynAid (
  LLRP_tSSyncInfo *pThis,
  LLRP_tSSynAid *pValue);



  
struct LLRP_SSynAid
{
    LLRP_tSParameter hdr;
  
    llrp_u32_t SeqNo;

    llrp_u16_t SystemNo;

    llrp_u16_t AidNum;

    llrp_u8_t SynType;

    llrp_u8_t PakageNo;

    llrp_u8_t PakageNum;

    llrp_u32v_t Aid;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdSynAid;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSynAid[];

extern LLRP_tSSynAid *
LLRP_SynAid_construct (void);

extern void
LLRP_SynAid_destruct (
 LLRP_tSSynAid * pThis);

extern void
LLRP_SynAid_decodeFields (
 LLRP_tSSynAid * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SynAid_assimilateSubParameters (
 LLRP_tSSynAid * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SynAid_encode (
  const LLRP_tSSynAid *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_SynAid_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdSynAid_SeqNo;

extern llrp_u32_t
LLRP_SynAid_getSeqNo (
  LLRP_tSSynAid *pThis);

extern LLRP_tResultCode
LLRP_SynAid_setSeqNo (
  LLRP_tSSynAid *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSynAid_SystemNo;

extern llrp_u16_t
LLRP_SynAid_getSystemNo (
  LLRP_tSSynAid *pThis);

extern LLRP_tResultCode
LLRP_SynAid_setSystemNo (
  LLRP_tSSynAid *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSynAid_AidNum;

extern llrp_u16_t
LLRP_SynAid_getAidNum (
  LLRP_tSSynAid *pThis);

extern LLRP_tResultCode
LLRP_SynAid_setAidNum (
  LLRP_tSSynAid *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSynAid_SynType;

extern llrp_u8_t
LLRP_SynAid_getSynType (
  LLRP_tSSynAid *pThis);

extern LLRP_tResultCode
LLRP_SynAid_setSynType (
  LLRP_tSSynAid *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSynAid_PakageNo;

extern llrp_u8_t
LLRP_SynAid_getPakageNo (
  LLRP_tSSynAid *pThis);

extern LLRP_tResultCode
LLRP_SynAid_setPakageNo (
  LLRP_tSSynAid *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSynAid_PakageNum;

extern llrp_u8_t
LLRP_SynAid_getPakageNum (
  LLRP_tSSynAid *pThis);

extern LLRP_tResultCode
LLRP_SynAid_setPakageNum (
  LLRP_tSSynAid *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSynAid_Aid;

extern llrp_u32v_t
LLRP_SynAid_getAid (
  LLRP_tSSynAid *pThis);

extern LLRP_tResultCode
LLRP_SynAid_setAid (
  LLRP_tSSynAid *pThis,
  llrp_u32v_t Value);

  


  
struct LLRP_SAlarmReportInfo
{
    LLRP_tSParameter hdr;
  
  
    LLRP_tSAlarmToBckgrd * pAlarmToBckgrd;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdAlarmReportInfo;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdAlarmReportInfo[];

extern LLRP_tSAlarmReportInfo *
LLRP_AlarmReportInfo_construct (void);

extern void
LLRP_AlarmReportInfo_destruct (
 LLRP_tSAlarmReportInfo * pThis);

extern void
LLRP_AlarmReportInfo_decodeFields (
 LLRP_tSAlarmReportInfo * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_AlarmReportInfo_assimilateSubParameters (
 LLRP_tSAlarmReportInfo * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_AlarmReportInfo_encode (
  const LLRP_tSAlarmReportInfo *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_AlarmReportInfo_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
  
extern LLRP_tSAlarmToBckgrd *
LLRP_AlarmReportInfo_getAlarmToBckgrd (
  LLRP_tSAlarmReportInfo *pThis);

extern LLRP_tResultCode
LLRP_AlarmReportInfo_setAlarmToBckgrd (
  LLRP_tSAlarmReportInfo *pThis,
  LLRP_tSAlarmToBckgrd *pValue);



  
struct LLRP_SAlarmToBckgrd
{
    LLRP_tSParameter hdr;
  
    llrp_u32_t Aid;

  
    LLRP_tSAlarmPID * pAlarmPID;

    LLRP_tSAlarmStruct * pAlarmStruct;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdAlarmToBckgrd;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdAlarmToBckgrd[];

extern LLRP_tSAlarmToBckgrd *
LLRP_AlarmToBckgrd_construct (void);

extern void
LLRP_AlarmToBckgrd_destruct (
 LLRP_tSAlarmToBckgrd * pThis);

extern void
LLRP_AlarmToBckgrd_decodeFields (
 LLRP_tSAlarmToBckgrd * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_AlarmToBckgrd_assimilateSubParameters (
 LLRP_tSAlarmToBckgrd * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_AlarmToBckgrd_encode (
  const LLRP_tSAlarmToBckgrd *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_AlarmToBckgrd_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdAlarmToBckgrd_Aid;

extern llrp_u32_t
LLRP_AlarmToBckgrd_getAid (
  LLRP_tSAlarmToBckgrd *pThis);

extern LLRP_tResultCode
LLRP_AlarmToBckgrd_setAid (
  LLRP_tSAlarmToBckgrd *pThis,
  llrp_u32_t Value);

  
extern LLRP_tSAlarmPID *
LLRP_AlarmToBckgrd_getAlarmPID (
  LLRP_tSAlarmToBckgrd *pThis);

extern LLRP_tResultCode
LLRP_AlarmToBckgrd_setAlarmPID (
  LLRP_tSAlarmToBckgrd *pThis,
  LLRP_tSAlarmPID *pValue);

extern LLRP_tSAlarmStruct *
LLRP_AlarmToBckgrd_getAlarmStruct (
  LLRP_tSAlarmToBckgrd *pThis);

extern LLRP_tResultCode
LLRP_AlarmToBckgrd_setAlarmStruct (
  LLRP_tSAlarmToBckgrd *pThis,
  LLRP_tSAlarmStruct *pValue);



  
struct LLRP_SAlarmPID
{
    LLRP_tSParameter hdr;
  
    llrp_u32_t Pno;

    llrp_u32_t DevID;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdAlarmPID;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdAlarmPID[];

extern LLRP_tSAlarmPID *
LLRP_AlarmPID_construct (void);

extern void
LLRP_AlarmPID_destruct (
 LLRP_tSAlarmPID * pThis);

extern void
LLRP_AlarmPID_decodeFields (
 LLRP_tSAlarmPID * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_AlarmPID_assimilateSubParameters (
 LLRP_tSAlarmPID * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_AlarmPID_encode (
  const LLRP_tSAlarmPID *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_AlarmPID_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdAlarmPID_Pno;

extern llrp_u32_t
LLRP_AlarmPID_getPno (
  LLRP_tSAlarmPID *pThis);

extern LLRP_tResultCode
LLRP_AlarmPID_setPno (
  LLRP_tSAlarmPID *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdAlarmPID_DevID;

extern llrp_u32_t
LLRP_AlarmPID_getDevID (
  LLRP_tSAlarmPID *pThis);

extern LLRP_tResultCode
LLRP_AlarmPID_setDevID (
  LLRP_tSAlarmPID *pThis,
  llrp_u32_t Value);

  


  
struct LLRP_SAlarmStruct
{
    LLRP_tSParameter hdr;
  
    llrp_u32_t Reserved;

  
    LLRP_tSAlarmSrcInfo * pAlarmSrcInfo;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdAlarmStruct;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdAlarmStruct[];

extern LLRP_tSAlarmStruct *
LLRP_AlarmStruct_construct (void);

extern void
LLRP_AlarmStruct_destruct (
 LLRP_tSAlarmStruct * pThis);

extern void
LLRP_AlarmStruct_decodeFields (
 LLRP_tSAlarmStruct * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_AlarmStruct_assimilateSubParameters (
 LLRP_tSAlarmStruct * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_AlarmStruct_encode (
  const LLRP_tSAlarmStruct *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_AlarmStruct_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdAlarmStruct_Reserved;

extern llrp_u32_t
LLRP_AlarmStruct_getReserved (
  LLRP_tSAlarmStruct *pThis);

extern LLRP_tResultCode
LLRP_AlarmStruct_setReserved (
  LLRP_tSAlarmStruct *pThis,
  llrp_u32_t Value);

  
extern LLRP_tSAlarmSrcInfo *
LLRP_AlarmStruct_getAlarmSrcInfo (
  LLRP_tSAlarmStruct *pThis);

extern LLRP_tResultCode
LLRP_AlarmStruct_setAlarmSrcInfo (
  LLRP_tSAlarmStruct *pThis,
  LLRP_tSAlarmSrcInfo *pValue);



  
struct LLRP_SAlarmSrcInfo
{
    LLRP_tSParameter hdr;
  
    llrp_u32_t AlarmCode;

    llrp_u32_t AlarmReason;

    llrp_u8_t AlarmLevel;

    llrp_u8_t DataLen;

    llrp_u16_t AlarmType;

    llrp_utf8v_t Datas;

  
    LLRP_tSSysSoftClock * pSysSoftClock;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdAlarmSrcInfo;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdAlarmSrcInfo[];

extern LLRP_tSAlarmSrcInfo *
LLRP_AlarmSrcInfo_construct (void);

extern void
LLRP_AlarmSrcInfo_destruct (
 LLRP_tSAlarmSrcInfo * pThis);

extern void
LLRP_AlarmSrcInfo_decodeFields (
 LLRP_tSAlarmSrcInfo * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_AlarmSrcInfo_assimilateSubParameters (
 LLRP_tSAlarmSrcInfo * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_AlarmSrcInfo_encode (
  const LLRP_tSAlarmSrcInfo *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_AlarmSrcInfo_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdAlarmSrcInfo_AlarmCode;

extern llrp_u32_t
LLRP_AlarmSrcInfo_getAlarmCode (
  LLRP_tSAlarmSrcInfo *pThis);

extern LLRP_tResultCode
LLRP_AlarmSrcInfo_setAlarmCode (
  LLRP_tSAlarmSrcInfo *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdAlarmSrcInfo_AlarmReason;

extern llrp_u32_t
LLRP_AlarmSrcInfo_getAlarmReason (
  LLRP_tSAlarmSrcInfo *pThis);

extern LLRP_tResultCode
LLRP_AlarmSrcInfo_setAlarmReason (
  LLRP_tSAlarmSrcInfo *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdAlarmSrcInfo_AlarmLevel;

extern llrp_u8_t
LLRP_AlarmSrcInfo_getAlarmLevel (
  LLRP_tSAlarmSrcInfo *pThis);

extern LLRP_tResultCode
LLRP_AlarmSrcInfo_setAlarmLevel (
  LLRP_tSAlarmSrcInfo *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdAlarmSrcInfo_DataLen;

extern llrp_u8_t
LLRP_AlarmSrcInfo_getDataLen (
  LLRP_tSAlarmSrcInfo *pThis);

extern LLRP_tResultCode
LLRP_AlarmSrcInfo_setDataLen (
  LLRP_tSAlarmSrcInfo *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdAlarmSrcInfo_AlarmType;

extern llrp_u16_t
LLRP_AlarmSrcInfo_getAlarmType (
  LLRP_tSAlarmSrcInfo *pThis);

extern LLRP_tResultCode
LLRP_AlarmSrcInfo_setAlarmType (
  LLRP_tSAlarmSrcInfo *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdAlarmSrcInfo_Datas;

extern llrp_utf8v_t
LLRP_AlarmSrcInfo_getDatas (
  LLRP_tSAlarmSrcInfo *pThis);

extern LLRP_tResultCode
LLRP_AlarmSrcInfo_setDatas (
  LLRP_tSAlarmSrcInfo *pThis,
  llrp_utf8v_t Value);

  
extern LLRP_tSSysSoftClock *
LLRP_AlarmSrcInfo_getSysSoftClock (
  LLRP_tSAlarmSrcInfo *pThis);

extern LLRP_tResultCode
LLRP_AlarmSrcInfo_setSysSoftClock (
  LLRP_tSAlarmSrcInfo *pThis,
  LLRP_tSSysSoftClock *pValue);



  
struct LLRP_SSysSoftClock
{
    LLRP_tSParameter hdr;
  
    llrp_u32_t Seconds;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdSysSoftClock;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSysSoftClock[];

extern LLRP_tSSysSoftClock *
LLRP_SysSoftClock_construct (void);

extern void
LLRP_SysSoftClock_destruct (
 LLRP_tSSysSoftClock * pThis);

extern void
LLRP_SysSoftClock_decodeFields (
 LLRP_tSSysSoftClock * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SysSoftClock_assimilateSubParameters (
 LLRP_tSSysSoftClock * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SysSoftClock_encode (
  const LLRP_tSSysSoftClock *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_SysSoftClock_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdSysSoftClock_Seconds;

extern llrp_u32_t
LLRP_SysSoftClock_getSeconds (
  LLRP_tSSysSoftClock *pThis);

extern LLRP_tResultCode
LLRP_SysSoftClock_setSeconds (
  LLRP_tSSysSoftClock *pThis,
  llrp_u32_t Value);

  


  
struct LLRP_SAlarmRestoreReportInfo
{
    LLRP_tSParameter hdr;
  
  
    LLRP_tSRestoreToBckgrd * pRestoreToBckgrd;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdAlarmRestoreReportInfo;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdAlarmRestoreReportInfo[];

extern LLRP_tSAlarmRestoreReportInfo *
LLRP_AlarmRestoreReportInfo_construct (void);

extern void
LLRP_AlarmRestoreReportInfo_destruct (
 LLRP_tSAlarmRestoreReportInfo * pThis);

extern void
LLRP_AlarmRestoreReportInfo_decodeFields (
 LLRP_tSAlarmRestoreReportInfo * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_AlarmRestoreReportInfo_assimilateSubParameters (
 LLRP_tSAlarmRestoreReportInfo * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_AlarmRestoreReportInfo_encode (
  const LLRP_tSAlarmRestoreReportInfo *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_AlarmRestoreReportInfo_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
  
extern LLRP_tSRestoreToBckgrd *
LLRP_AlarmRestoreReportInfo_getRestoreToBckgrd (
  LLRP_tSAlarmRestoreReportInfo *pThis);

extern LLRP_tResultCode
LLRP_AlarmRestoreReportInfo_setRestoreToBckgrd (
  LLRP_tSAlarmRestoreReportInfo *pThis,
  LLRP_tSRestoreToBckgrd *pValue);



  
struct LLRP_SRestoreToBckgrd
{
    LLRP_tSParameter hdr;
  
    llrp_u32_t Aid;

    llrp_u8_t RestoreType;

  
    LLRP_tSAlarmPID * pAlarmPID;

    LLRP_tSSysSoftClock * pSysSoftClock;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdRestoreToBckgrd;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdRestoreToBckgrd[];

extern LLRP_tSRestoreToBckgrd *
LLRP_RestoreToBckgrd_construct (void);

extern void
LLRP_RestoreToBckgrd_destruct (
 LLRP_tSRestoreToBckgrd * pThis);

extern void
LLRP_RestoreToBckgrd_decodeFields (
 LLRP_tSRestoreToBckgrd * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_RestoreToBckgrd_assimilateSubParameters (
 LLRP_tSRestoreToBckgrd * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_RestoreToBckgrd_encode (
  const LLRP_tSRestoreToBckgrd *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_RestoreToBckgrd_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdRestoreToBckgrd_Aid;

extern llrp_u32_t
LLRP_RestoreToBckgrd_getAid (
  LLRP_tSRestoreToBckgrd *pThis);

extern LLRP_tResultCode
LLRP_RestoreToBckgrd_setAid (
  LLRP_tSRestoreToBckgrd *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdRestoreToBckgrd_RestoreType;

extern llrp_u8_t
LLRP_RestoreToBckgrd_getRestoreType (
  LLRP_tSRestoreToBckgrd *pThis);

extern LLRP_tResultCode
LLRP_RestoreToBckgrd_setRestoreType (
  LLRP_tSRestoreToBckgrd *pThis,
  llrp_u8_t Value);

  
extern LLRP_tSAlarmPID *
LLRP_RestoreToBckgrd_getAlarmPID (
  LLRP_tSRestoreToBckgrd *pThis);

extern LLRP_tResultCode
LLRP_RestoreToBckgrd_setAlarmPID (
  LLRP_tSRestoreToBckgrd *pThis,
  LLRP_tSAlarmPID *pValue);

extern LLRP_tSSysSoftClock *
LLRP_RestoreToBckgrd_getSysSoftClock (
  LLRP_tSRestoreToBckgrd *pThis);

extern LLRP_tResultCode
LLRP_RestoreToBckgrd_setSysSoftClock (
  LLRP_tSRestoreToBckgrd *pThis,
  LLRP_tSSysSoftClock *pValue);



  
struct LLRP_SInformReportInfo
{
    LLRP_tSParameter hdr;
  
  
    LLRP_tSInformToUp * pInformToUp;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdInformReportInfo;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdInformReportInfo[];

extern LLRP_tSInformReportInfo *
LLRP_InformReportInfo_construct (void);

extern void
LLRP_InformReportInfo_destruct (
 LLRP_tSInformReportInfo * pThis);

extern void
LLRP_InformReportInfo_decodeFields (
 LLRP_tSInformReportInfo * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_InformReportInfo_assimilateSubParameters (
 LLRP_tSInformReportInfo * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_InformReportInfo_encode (
  const LLRP_tSInformReportInfo *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_InformReportInfo_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
  
extern LLRP_tSInformToUp *
LLRP_InformReportInfo_getInformToUp (
  LLRP_tSInformReportInfo *pThis);

extern LLRP_tResultCode
LLRP_InformReportInfo_setInformToUp (
  LLRP_tSInformReportInfo *pThis,
  LLRP_tSInformToUp *pValue);



  
struct LLRP_SInformToUp
{
    LLRP_tSParameter hdr;
  
  
    LLRP_tSAlarmPID * pAlarmPID;

    LLRP_tSAlarmStruct * pAlarmStruct;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdInformToUp;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdInformToUp[];

extern LLRP_tSInformToUp *
LLRP_InformToUp_construct (void);

extern void
LLRP_InformToUp_destruct (
 LLRP_tSInformToUp * pThis);

extern void
LLRP_InformToUp_decodeFields (
 LLRP_tSInformToUp * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_InformToUp_assimilateSubParameters (
 LLRP_tSInformToUp * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_InformToUp_encode (
  const LLRP_tSInformToUp *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_InformToUp_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
  
extern LLRP_tSAlarmPID *
LLRP_InformToUp_getAlarmPID (
  LLRP_tSInformToUp *pThis);

extern LLRP_tResultCode
LLRP_InformToUp_setAlarmPID (
  LLRP_tSInformToUp *pThis,
  LLRP_tSAlarmPID *pValue);

extern LLRP_tSAlarmStruct *
LLRP_InformToUp_getAlarmStruct (
  LLRP_tSInformToUp *pThis);

extern LLRP_tResultCode
LLRP_InformToUp_setAlarmStruct (
  LLRP_tSInformToUp *pThis,
  LLRP_tSAlarmStruct *pValue);



  
struct LLRP_SReaderVerActivateAck
{
    LLRP_tSParameter hdr;
  
    llrp_u32_t Result;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdReaderVerActivateAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdReaderVerActivateAck[];

extern LLRP_tSReaderVerActivateAck *
LLRP_ReaderVerActivateAck_construct (void);

extern void
LLRP_ReaderVerActivateAck_destruct (
 LLRP_tSReaderVerActivateAck * pThis);

extern void
LLRP_ReaderVerActivateAck_decodeFields (
 LLRP_tSReaderVerActivateAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_ReaderVerActivateAck_assimilateSubParameters (
 LLRP_tSReaderVerActivateAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_ReaderVerActivateAck_encode (
  const LLRP_tSReaderVerActivateAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_ReaderVerActivateAck_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdReaderVerActivateAck_Result;

extern llrp_u32_t
LLRP_ReaderVerActivateAck_getResult (
  LLRP_tSReaderVerActivateAck *pThis);

extern LLRP_tResultCode
LLRP_ReaderVerActivateAck_setResult (
  LLRP_tSReaderVerActivateAck *pThis,
  llrp_u32_t Value);

  


  
struct LLRP_SVerInfoQueryAck
{
    LLRP_tSParameter hdr;
  
    llrp_u32_t VerNum;

  
    LLRP_tSVerInfo * listVerInfo;

    LLRP_tSBasicVerInfo * listBasicVerInfo;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdVerInfoQueryAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdVerInfoQueryAck[];

extern LLRP_tSVerInfoQueryAck *
LLRP_VerInfoQueryAck_construct (void);

extern void
LLRP_VerInfoQueryAck_destruct (
 LLRP_tSVerInfoQueryAck * pThis);

extern void
LLRP_VerInfoQueryAck_decodeFields (
 LLRP_tSVerInfoQueryAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_VerInfoQueryAck_assimilateSubParameters (
 LLRP_tSVerInfoQueryAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_VerInfoQueryAck_encode (
  const LLRP_tSVerInfoQueryAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_VerInfoQueryAck_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdVerInfoQueryAck_VerNum;

extern llrp_u32_t
LLRP_VerInfoQueryAck_getVerNum (
  LLRP_tSVerInfoQueryAck *pThis);

extern LLRP_tResultCode
LLRP_VerInfoQueryAck_setVerNum (
  LLRP_tSVerInfoQueryAck *pThis,
  llrp_u32_t Value);

  
extern LLRP_tSVerInfo *
LLRP_VerInfoQueryAck_beginVerInfo (
  LLRP_tSVerInfoQueryAck *pThis);

extern LLRP_tSVerInfo *
LLRP_VerInfoQueryAck_nextVerInfo (
  LLRP_tSVerInfo *pCurrent);

extern void
LLRP_VerInfoQueryAck_clearVerInfo (
  LLRP_tSVerInfoQueryAck *pThis);

extern LLRP_tResultCode
LLRP_VerInfoQueryAck_addVerInfo (
  LLRP_tSVerInfoQueryAck *pThis,
  LLRP_tSVerInfo *pValue);


extern LLRP_tSBasicVerInfo *
LLRP_VerInfoQueryAck_beginBasicVerInfo (
  LLRP_tSVerInfoQueryAck *pThis);

extern LLRP_tSBasicVerInfo *
LLRP_VerInfoQueryAck_nextBasicVerInfo (
  LLRP_tSBasicVerInfo *pCurrent);

extern void
LLRP_VerInfoQueryAck_clearBasicVerInfo (
  LLRP_tSVerInfoQueryAck *pThis);

extern LLRP_tResultCode
LLRP_VerInfoQueryAck_addBasicVerInfo (
  LLRP_tSVerInfoQueryAck *pThis,
  LLRP_tSBasicVerInfo *pValue);




  
struct LLRP_SVerInfo
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t MaxVerInfo;

    llrp_u8_t MinVerInfo;

    llrp_u8_t SubVerInfo;

    llrp_u8_t BuildVerInfo;

    llrp_u8_t UsedOrSpare;

    llrp_u8_t SetUse;

    llrp_u8_t HasRun;

    llrp_u8_t CanRun;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdVerInfo;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdVerInfo[];

extern LLRP_tSVerInfo *
LLRP_VerInfo_construct (void);

extern void
LLRP_VerInfo_destruct (
 LLRP_tSVerInfo * pThis);

extern void
LLRP_VerInfo_decodeFields (
 LLRP_tSVerInfo * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_VerInfo_assimilateSubParameters (
 LLRP_tSVerInfo * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_VerInfo_encode (
  const LLRP_tSVerInfo *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_VerInfo_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdVerInfo_MaxVerInfo;

extern llrp_u8_t
LLRP_VerInfo_getMaxVerInfo (
  LLRP_tSVerInfo *pThis);

extern LLRP_tResultCode
LLRP_VerInfo_setMaxVerInfo (
  LLRP_tSVerInfo *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdVerInfo_MinVerInfo;

extern llrp_u8_t
LLRP_VerInfo_getMinVerInfo (
  LLRP_tSVerInfo *pThis);

extern LLRP_tResultCode
LLRP_VerInfo_setMinVerInfo (
  LLRP_tSVerInfo *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdVerInfo_SubVerInfo;

extern llrp_u8_t
LLRP_VerInfo_getSubVerInfo (
  LLRP_tSVerInfo *pThis);

extern LLRP_tResultCode
LLRP_VerInfo_setSubVerInfo (
  LLRP_tSVerInfo *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdVerInfo_BuildVerInfo;

extern llrp_u8_t
LLRP_VerInfo_getBuildVerInfo (
  LLRP_tSVerInfo *pThis);

extern LLRP_tResultCode
LLRP_VerInfo_setBuildVerInfo (
  LLRP_tSVerInfo *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdVerInfo_UsedOrSpare;

extern llrp_u8_t
LLRP_VerInfo_getUsedOrSpare (
  LLRP_tSVerInfo *pThis);

extern LLRP_tResultCode
LLRP_VerInfo_setUsedOrSpare (
  LLRP_tSVerInfo *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdVerInfo_SetUse;

extern llrp_u8_t
LLRP_VerInfo_getSetUse (
  LLRP_tSVerInfo *pThis);

extern LLRP_tResultCode
LLRP_VerInfo_setSetUse (
  LLRP_tSVerInfo *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdVerInfo_HasRun;

extern llrp_u8_t
LLRP_VerInfo_getHasRun (
  LLRP_tSVerInfo *pThis);

extern LLRP_tResultCode
LLRP_VerInfo_setHasRun (
  LLRP_tSVerInfo *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdVerInfo_CanRun;

extern llrp_u8_t
LLRP_VerInfo_getCanRun (
  LLRP_tSVerInfo *pThis);

extern LLRP_tResultCode
LLRP_VerInfo_setCanRun (
  LLRP_tSVerInfo *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SVersionDownloadRequest
{
    LLRP_tSParameter hdr;
  
    llrp_u32_t Version;

    llrp_u16_t SubVersionNum;

    llrp_u32_t ReaderMode;

  
    LLRP_tSSubVersionInfo * listSubVersionInfo;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdVersionDownloadRequest;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdVersionDownloadRequest[];

extern LLRP_tSVersionDownloadRequest *
LLRP_VersionDownloadRequest_construct (void);

extern void
LLRP_VersionDownloadRequest_destruct (
 LLRP_tSVersionDownloadRequest * pThis);

extern void
LLRP_VersionDownloadRequest_decodeFields (
 LLRP_tSVersionDownloadRequest * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_VersionDownloadRequest_assimilateSubParameters (
 LLRP_tSVersionDownloadRequest * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_VersionDownloadRequest_encode (
  const LLRP_tSVersionDownloadRequest *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_VersionDownloadRequest_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdVersionDownloadRequest_Version;

extern llrp_u32_t
LLRP_VersionDownloadRequest_getVersion (
  LLRP_tSVersionDownloadRequest *pThis);

extern LLRP_tResultCode
LLRP_VersionDownloadRequest_setVersion (
  LLRP_tSVersionDownloadRequest *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdVersionDownloadRequest_SubVersionNum;

extern llrp_u16_t
LLRP_VersionDownloadRequest_getSubVersionNum (
  LLRP_tSVersionDownloadRequest *pThis);

extern LLRP_tResultCode
LLRP_VersionDownloadRequest_setSubVersionNum (
  LLRP_tSVersionDownloadRequest *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdVersionDownloadRequest_ReaderMode;

extern llrp_u32_t
LLRP_VersionDownloadRequest_getReaderMode (
  LLRP_tSVersionDownloadRequest *pThis);

extern LLRP_tResultCode
LLRP_VersionDownloadRequest_setReaderMode (
  LLRP_tSVersionDownloadRequest *pThis,
  llrp_u32_t Value);

  
extern LLRP_tSSubVersionInfo *
LLRP_VersionDownloadRequest_beginSubVersionInfo (
  LLRP_tSVersionDownloadRequest *pThis);

extern LLRP_tSSubVersionInfo *
LLRP_VersionDownloadRequest_nextSubVersionInfo (
  LLRP_tSSubVersionInfo *pCurrent);

extern void
LLRP_VersionDownloadRequest_clearSubVersionInfo (
  LLRP_tSVersionDownloadRequest *pThis);

extern LLRP_tResultCode
LLRP_VersionDownloadRequest_addSubVersionInfo (
  LLRP_tSVersionDownloadRequest *pThis,
  LLRP_tSSubVersionInfo *pValue);




  
struct LLRP_SSubVersionInfo
{
    LLRP_tSParameter hdr;
  
    llrp_u32_t SubVersionType;

    llrp_u32_t SubVersion;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdSubVersionInfo;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSubVersionInfo[];

extern LLRP_tSSubVersionInfo *
LLRP_SubVersionInfo_construct (void);

extern void
LLRP_SubVersionInfo_destruct (
 LLRP_tSSubVersionInfo * pThis);

extern void
LLRP_SubVersionInfo_decodeFields (
 LLRP_tSSubVersionInfo * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SubVersionInfo_assimilateSubParameters (
 LLRP_tSSubVersionInfo * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SubVersionInfo_encode (
  const LLRP_tSSubVersionInfo *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_SubVersionInfo_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdSubVersionInfo_SubVersionType;

extern llrp_u32_t
LLRP_SubVersionInfo_getSubVersionType (
  LLRP_tSSubVersionInfo *pThis);

extern LLRP_tResultCode
LLRP_SubVersionInfo_setSubVersionType (
  LLRP_tSSubVersionInfo *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSubVersionInfo_SubVersion;

extern llrp_u32_t
LLRP_SubVersionInfo_getSubVersion (
  LLRP_tSSubVersionInfo *pThis);

extern LLRP_tResultCode
LLRP_SubVersionInfo_setSubVersion (
  LLRP_tSSubVersionInfo *pThis,
  llrp_u32_t Value);

  


  
struct LLRP_SVersionDownloadRequestAck
{
    LLRP_tSParameter hdr;
  
    llrp_u32_t Result;

    llrp_u32_t SubVersionNum;

  
    LLRP_tSSubVersionInfo * listSubVersionInfo;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdVersionDownloadRequestAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdVersionDownloadRequestAck[];

extern LLRP_tSVersionDownloadRequestAck *
LLRP_VersionDownloadRequestAck_construct (void);

extern void
LLRP_VersionDownloadRequestAck_destruct (
 LLRP_tSVersionDownloadRequestAck * pThis);

extern void
LLRP_VersionDownloadRequestAck_decodeFields (
 LLRP_tSVersionDownloadRequestAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_VersionDownloadRequestAck_assimilateSubParameters (
 LLRP_tSVersionDownloadRequestAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_VersionDownloadRequestAck_encode (
  const LLRP_tSVersionDownloadRequestAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_VersionDownloadRequestAck_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdVersionDownloadRequestAck_Result;

extern llrp_u32_t
LLRP_VersionDownloadRequestAck_getResult (
  LLRP_tSVersionDownloadRequestAck *pThis);

extern LLRP_tResultCode
LLRP_VersionDownloadRequestAck_setResult (
  LLRP_tSVersionDownloadRequestAck *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdVersionDownloadRequestAck_SubVersionNum;

extern llrp_u32_t
LLRP_VersionDownloadRequestAck_getSubVersionNum (
  LLRP_tSVersionDownloadRequestAck *pThis);

extern LLRP_tResultCode
LLRP_VersionDownloadRequestAck_setSubVersionNum (
  LLRP_tSVersionDownloadRequestAck *pThis,
  llrp_u32_t Value);

  
extern LLRP_tSSubVersionInfo *
LLRP_VersionDownloadRequestAck_beginSubVersionInfo (
  LLRP_tSVersionDownloadRequestAck *pThis);

extern LLRP_tSSubVersionInfo *
LLRP_VersionDownloadRequestAck_nextSubVersionInfo (
  LLRP_tSSubVersionInfo *pCurrent);

extern void
LLRP_VersionDownloadRequestAck_clearSubVersionInfo (
  LLRP_tSVersionDownloadRequestAck *pThis);

extern LLRP_tResultCode
LLRP_VersionDownloadRequestAck_addSubVersionInfo (
  LLRP_tSVersionDownloadRequestAck *pThis,
  LLRP_tSSubVersionInfo *pValue);




  
struct LLRP_SBasicVerInfo
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t MaxVerInfo;

    llrp_u8_t MinVerInfo;

    llrp_u8_t SubVerInfo;

    llrp_u8_t BuildVerInfo;

    llrp_u8_t VerType;

    llrp_u8_t RFBoardIndex;

    llrp_u8_t ucUsedOrSpare;

    llrp_utf8v_t VerInfo;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdBasicVerInfo;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdBasicVerInfo[];

extern LLRP_tSBasicVerInfo *
LLRP_BasicVerInfo_construct (void);

extern void
LLRP_BasicVerInfo_destruct (
 LLRP_tSBasicVerInfo * pThis);

extern void
LLRP_BasicVerInfo_decodeFields (
 LLRP_tSBasicVerInfo * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_BasicVerInfo_assimilateSubParameters (
 LLRP_tSBasicVerInfo * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_BasicVerInfo_encode (
  const LLRP_tSBasicVerInfo *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_BasicVerInfo_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdBasicVerInfo_MaxVerInfo;

extern llrp_u8_t
LLRP_BasicVerInfo_getMaxVerInfo (
  LLRP_tSBasicVerInfo *pThis);

extern LLRP_tResultCode
LLRP_BasicVerInfo_setMaxVerInfo (
  LLRP_tSBasicVerInfo *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdBasicVerInfo_MinVerInfo;

extern llrp_u8_t
LLRP_BasicVerInfo_getMinVerInfo (
  LLRP_tSBasicVerInfo *pThis);

extern LLRP_tResultCode
LLRP_BasicVerInfo_setMinVerInfo (
  LLRP_tSBasicVerInfo *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdBasicVerInfo_SubVerInfo;

extern llrp_u8_t
LLRP_BasicVerInfo_getSubVerInfo (
  LLRP_tSBasicVerInfo *pThis);

extern LLRP_tResultCode
LLRP_BasicVerInfo_setSubVerInfo (
  LLRP_tSBasicVerInfo *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdBasicVerInfo_BuildVerInfo;

extern llrp_u8_t
LLRP_BasicVerInfo_getBuildVerInfo (
  LLRP_tSBasicVerInfo *pThis);

extern LLRP_tResultCode
LLRP_BasicVerInfo_setBuildVerInfo (
  LLRP_tSBasicVerInfo *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdBasicVerInfo_VerType;

extern llrp_u8_t
LLRP_BasicVerInfo_getVerType (
  LLRP_tSBasicVerInfo *pThis);

extern LLRP_tResultCode
LLRP_BasicVerInfo_setVerType (
  LLRP_tSBasicVerInfo *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdBasicVerInfo_RFBoardIndex;

extern llrp_u8_t
LLRP_BasicVerInfo_getRFBoardIndex (
  LLRP_tSBasicVerInfo *pThis);

extern LLRP_tResultCode
LLRP_BasicVerInfo_setRFBoardIndex (
  LLRP_tSBasicVerInfo *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdBasicVerInfo_ucUsedOrSpare;

extern llrp_u8_t
LLRP_BasicVerInfo_getucUsedOrSpare (
  LLRP_tSBasicVerInfo *pThis);

extern LLRP_tResultCode
LLRP_BasicVerInfo_setucUsedOrSpare (
  LLRP_tSBasicVerInfo *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdBasicVerInfo_VerInfo;

extern llrp_utf8v_t
LLRP_BasicVerInfo_getVerInfo (
  LLRP_tSBasicVerInfo *pThis);

extern LLRP_tResultCode
LLRP_BasicVerInfo_setVerInfo (
  LLRP_tSBasicVerInfo *pThis,
  llrp_utf8v_t Value);

  


  
struct LLRP_SBasicVerInfoSelect
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t VerType;

    llrp_u8_t RFBoardIndex;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdBasicVerInfoSelect;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdBasicVerInfoSelect[];

extern LLRP_tSBasicVerInfoSelect *
LLRP_BasicVerInfoSelect_construct (void);

extern void
LLRP_BasicVerInfoSelect_destruct (
 LLRP_tSBasicVerInfoSelect * pThis);

extern void
LLRP_BasicVerInfoSelect_decodeFields (
 LLRP_tSBasicVerInfoSelect * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_BasicVerInfoSelect_assimilateSubParameters (
 LLRP_tSBasicVerInfoSelect * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_BasicVerInfoSelect_encode (
  const LLRP_tSBasicVerInfoSelect *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_BasicVerInfoSelect_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdBasicVerInfoSelect_VerType;

extern llrp_u8_t
LLRP_BasicVerInfoSelect_getVerType (
  LLRP_tSBasicVerInfoSelect *pThis);

extern LLRP_tResultCode
LLRP_BasicVerInfoSelect_setVerType (
  LLRP_tSBasicVerInfoSelect *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdBasicVerInfoSelect_RFBoardIndex;

extern llrp_u8_t
LLRP_BasicVerInfoSelect_getRFBoardIndex (
  LLRP_tSBasicVerInfoSelect *pThis);

extern LLRP_tResultCode
LLRP_BasicVerInfoSelect_setRFBoardIndex (
  LLRP_tSBasicVerInfoSelect *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SReaderVerDownload
{
    LLRP_tSParameter hdr;
  
    llrp_u32_t ServerIp;

    llrp_u16_t ServerPort;

    llrp_utf8v_t UserName;

    llrp_utf8v_t UserPass;

    llrp_u32_t MainVersion;

    llrp_u32_t FileNum;

  
    LLRP_tSReaderVerDownloadFile * listReaderVerDownloadFile;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdReaderVerDownload;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdReaderVerDownload[];

extern LLRP_tSReaderVerDownload *
LLRP_ReaderVerDownload_construct (void);

extern void
LLRP_ReaderVerDownload_destruct (
 LLRP_tSReaderVerDownload * pThis);

extern void
LLRP_ReaderVerDownload_decodeFields (
 LLRP_tSReaderVerDownload * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_ReaderVerDownload_assimilateSubParameters (
 LLRP_tSReaderVerDownload * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_ReaderVerDownload_encode (
  const LLRP_tSReaderVerDownload *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_ReaderVerDownload_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdReaderVerDownload_ServerIp;

extern llrp_u32_t
LLRP_ReaderVerDownload_getServerIp (
  LLRP_tSReaderVerDownload *pThis);

extern LLRP_tResultCode
LLRP_ReaderVerDownload_setServerIp (
  LLRP_tSReaderVerDownload *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdReaderVerDownload_ServerPort;

extern llrp_u16_t
LLRP_ReaderVerDownload_getServerPort (
  LLRP_tSReaderVerDownload *pThis);

extern LLRP_tResultCode
LLRP_ReaderVerDownload_setServerPort (
  LLRP_tSReaderVerDownload *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdReaderVerDownload_UserName;

extern llrp_utf8v_t
LLRP_ReaderVerDownload_getUserName (
  LLRP_tSReaderVerDownload *pThis);

extern LLRP_tResultCode
LLRP_ReaderVerDownload_setUserName (
  LLRP_tSReaderVerDownload *pThis,
  llrp_utf8v_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdReaderVerDownload_UserPass;

extern llrp_utf8v_t
LLRP_ReaderVerDownload_getUserPass (
  LLRP_tSReaderVerDownload *pThis);

extern LLRP_tResultCode
LLRP_ReaderVerDownload_setUserPass (
  LLRP_tSReaderVerDownload *pThis,
  llrp_utf8v_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdReaderVerDownload_MainVersion;

extern llrp_u32_t
LLRP_ReaderVerDownload_getMainVersion (
  LLRP_tSReaderVerDownload *pThis);

extern LLRP_tResultCode
LLRP_ReaderVerDownload_setMainVersion (
  LLRP_tSReaderVerDownload *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdReaderVerDownload_FileNum;

extern llrp_u32_t
LLRP_ReaderVerDownload_getFileNum (
  LLRP_tSReaderVerDownload *pThis);

extern LLRP_tResultCode
LLRP_ReaderVerDownload_setFileNum (
  LLRP_tSReaderVerDownload *pThis,
  llrp_u32_t Value);

  
extern LLRP_tSReaderVerDownloadFile *
LLRP_ReaderVerDownload_beginReaderVerDownloadFile (
  LLRP_tSReaderVerDownload *pThis);

extern LLRP_tSReaderVerDownloadFile *
LLRP_ReaderVerDownload_nextReaderVerDownloadFile (
  LLRP_tSReaderVerDownloadFile *pCurrent);

extern void
LLRP_ReaderVerDownload_clearReaderVerDownloadFile (
  LLRP_tSReaderVerDownload *pThis);

extern LLRP_tResultCode
LLRP_ReaderVerDownload_addReaderVerDownloadFile (
  LLRP_tSReaderVerDownload *pThis,
  LLRP_tSReaderVerDownloadFile *pValue);




  
struct LLRP_SReaderVerDownloadFile
{
    LLRP_tSParameter hdr;
  
    llrp_utf8v_t VersionPath;

    llrp_utf8v_t VersionName;

    llrp_u16_t VersionFileCRC;

    llrp_u32_t VersionType;

    llrp_u32_t SubVersion;

    llrp_u32_t FileSize;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdReaderVerDownloadFile;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdReaderVerDownloadFile[];

extern LLRP_tSReaderVerDownloadFile *
LLRP_ReaderVerDownloadFile_construct (void);

extern void
LLRP_ReaderVerDownloadFile_destruct (
 LLRP_tSReaderVerDownloadFile * pThis);

extern void
LLRP_ReaderVerDownloadFile_decodeFields (
 LLRP_tSReaderVerDownloadFile * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_ReaderVerDownloadFile_assimilateSubParameters (
 LLRP_tSReaderVerDownloadFile * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_ReaderVerDownloadFile_encode (
  const LLRP_tSReaderVerDownloadFile *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_ReaderVerDownloadFile_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdReaderVerDownloadFile_VersionPath;

extern llrp_utf8v_t
LLRP_ReaderVerDownloadFile_getVersionPath (
  LLRP_tSReaderVerDownloadFile *pThis);

extern LLRP_tResultCode
LLRP_ReaderVerDownloadFile_setVersionPath (
  LLRP_tSReaderVerDownloadFile *pThis,
  llrp_utf8v_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdReaderVerDownloadFile_VersionName;

extern llrp_utf8v_t
LLRP_ReaderVerDownloadFile_getVersionName (
  LLRP_tSReaderVerDownloadFile *pThis);

extern LLRP_tResultCode
LLRP_ReaderVerDownloadFile_setVersionName (
  LLRP_tSReaderVerDownloadFile *pThis,
  llrp_utf8v_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdReaderVerDownloadFile_VersionFileCRC;

extern llrp_u16_t
LLRP_ReaderVerDownloadFile_getVersionFileCRC (
  LLRP_tSReaderVerDownloadFile *pThis);

extern LLRP_tResultCode
LLRP_ReaderVerDownloadFile_setVersionFileCRC (
  LLRP_tSReaderVerDownloadFile *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdReaderVerDownloadFile_VersionType;

extern llrp_u32_t
LLRP_ReaderVerDownloadFile_getVersionType (
  LLRP_tSReaderVerDownloadFile *pThis);

extern LLRP_tResultCode
LLRP_ReaderVerDownloadFile_setVersionType (
  LLRP_tSReaderVerDownloadFile *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdReaderVerDownloadFile_SubVersion;

extern llrp_u32_t
LLRP_ReaderVerDownloadFile_getSubVersion (
  LLRP_tSReaderVerDownloadFile *pThis);

extern LLRP_tResultCode
LLRP_ReaderVerDownloadFile_setSubVersion (
  LLRP_tSReaderVerDownloadFile *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdReaderVerDownloadFile_FileSize;

extern llrp_u32_t
LLRP_ReaderVerDownloadFile_getFileSize (
  LLRP_tSReaderVerDownloadFile *pThis);

extern LLRP_tResultCode
LLRP_ReaderVerDownloadFile_setFileSize (
  LLRP_tSReaderVerDownloadFile *pThis,
  llrp_u32_t Value);

  


  
struct LLRP_SVersionDownloadAck
{
    LLRP_tSParameter hdr;
  
    llrp_u32_t Result;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdVersionDownloadAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdVersionDownloadAck[];

extern LLRP_tSVersionDownloadAck *
LLRP_VersionDownloadAck_construct (void);

extern void
LLRP_VersionDownloadAck_destruct (
 LLRP_tSVersionDownloadAck * pThis);

extern void
LLRP_VersionDownloadAck_decodeFields (
 LLRP_tSVersionDownloadAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_VersionDownloadAck_assimilateSubParameters (
 LLRP_tSVersionDownloadAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_VersionDownloadAck_encode (
  const LLRP_tSVersionDownloadAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_VersionDownloadAck_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdVersionDownloadAck_Result;

extern llrp_u32_t
LLRP_VersionDownloadAck_getResult (
  LLRP_tSVersionDownloadAck *pThis);

extern LLRP_tResultCode
LLRP_VersionDownloadAck_setResult (
  LLRP_tSVersionDownloadAck *pThis,
  llrp_u32_t Value);

  


  
struct LLRP_SSPVerInfoQueryResponse
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t VerNum;

  
    LLRP_tSSPVerInfo * listSPVerInfo;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdSPVerInfoQueryResponse;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSPVerInfoQueryResponse[];

extern LLRP_tSSPVerInfoQueryResponse *
LLRP_SPVerInfoQueryResponse_construct (void);

extern void
LLRP_SPVerInfoQueryResponse_destruct (
 LLRP_tSSPVerInfoQueryResponse * pThis);

extern void
LLRP_SPVerInfoQueryResponse_decodeFields (
 LLRP_tSSPVerInfoQueryResponse * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SPVerInfoQueryResponse_assimilateSubParameters (
 LLRP_tSSPVerInfoQueryResponse * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SPVerInfoQueryResponse_encode (
  const LLRP_tSSPVerInfoQueryResponse *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_SPVerInfoQueryResponse_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdSPVerInfoQueryResponse_VerNum;

extern llrp_u8_t
LLRP_SPVerInfoQueryResponse_getVerNum (
  LLRP_tSSPVerInfoQueryResponse *pThis);

extern LLRP_tResultCode
LLRP_SPVerInfoQueryResponse_setVerNum (
  LLRP_tSSPVerInfoQueryResponse *pThis,
  llrp_u8_t Value);

  
extern LLRP_tSSPVerInfo *
LLRP_SPVerInfoQueryResponse_beginSPVerInfo (
  LLRP_tSSPVerInfoQueryResponse *pThis);

extern LLRP_tSSPVerInfo *
LLRP_SPVerInfoQueryResponse_nextSPVerInfo (
  LLRP_tSSPVerInfo *pCurrent);

extern void
LLRP_SPVerInfoQueryResponse_clearSPVerInfo (
  LLRP_tSSPVerInfoQueryResponse *pThis);

extern LLRP_tResultCode
LLRP_SPVerInfoQueryResponse_addSPVerInfo (
  LLRP_tSSPVerInfoQueryResponse *pThis,
  LLRP_tSSPVerInfo *pValue);




  
struct LLRP_SSPVerInfo
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t SPVerMode;

    llrp_u8_t SPVerType;

    llrp_u8_t MaxSPVerInfo;

    llrp_u8_t MinSPVerInfo;

    llrp_u8_t BuildVerInfo;

    llrp_u8_t SubSPVerInfo;

    llrp_u8_t SPIndex;

    llrp_u8_t IsActive;

    llrp_u8_t IsUsedOrSpare;

    llrp_u8_t IsSetUse;

    llrp_utf8v_t SPVerInfo;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdSPVerInfo;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSPVerInfo[];

extern LLRP_tSSPVerInfo *
LLRP_SPVerInfo_construct (void);

extern void
LLRP_SPVerInfo_destruct (
 LLRP_tSSPVerInfo * pThis);

extern void
LLRP_SPVerInfo_decodeFields (
 LLRP_tSSPVerInfo * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SPVerInfo_assimilateSubParameters (
 LLRP_tSSPVerInfo * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SPVerInfo_encode (
  const LLRP_tSSPVerInfo *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_SPVerInfo_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdSPVerInfo_SPVerMode;

extern llrp_u8_t
LLRP_SPVerInfo_getSPVerMode (
  LLRP_tSSPVerInfo *pThis);

extern LLRP_tResultCode
LLRP_SPVerInfo_setSPVerMode (
  LLRP_tSSPVerInfo *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSPVerInfo_SPVerType;

extern llrp_u8_t
LLRP_SPVerInfo_getSPVerType (
  LLRP_tSSPVerInfo *pThis);

extern LLRP_tResultCode
LLRP_SPVerInfo_setSPVerType (
  LLRP_tSSPVerInfo *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSPVerInfo_MaxSPVerInfo;

extern llrp_u8_t
LLRP_SPVerInfo_getMaxSPVerInfo (
  LLRP_tSSPVerInfo *pThis);

extern LLRP_tResultCode
LLRP_SPVerInfo_setMaxSPVerInfo (
  LLRP_tSSPVerInfo *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSPVerInfo_MinSPVerInfo;

extern llrp_u8_t
LLRP_SPVerInfo_getMinSPVerInfo (
  LLRP_tSSPVerInfo *pThis);

extern LLRP_tResultCode
LLRP_SPVerInfo_setMinSPVerInfo (
  LLRP_tSSPVerInfo *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSPVerInfo_BuildVerInfo;

extern llrp_u8_t
LLRP_SPVerInfo_getBuildVerInfo (
  LLRP_tSSPVerInfo *pThis);

extern LLRP_tResultCode
LLRP_SPVerInfo_setBuildVerInfo (
  LLRP_tSSPVerInfo *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSPVerInfo_SubSPVerInfo;

extern llrp_u8_t
LLRP_SPVerInfo_getSubSPVerInfo (
  LLRP_tSSPVerInfo *pThis);

extern LLRP_tResultCode
LLRP_SPVerInfo_setSubSPVerInfo (
  LLRP_tSSPVerInfo *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSPVerInfo_SPIndex;

extern llrp_u8_t
LLRP_SPVerInfo_getSPIndex (
  LLRP_tSSPVerInfo *pThis);

extern LLRP_tResultCode
LLRP_SPVerInfo_setSPIndex (
  LLRP_tSSPVerInfo *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSPVerInfo_IsActive;

extern llrp_u8_t
LLRP_SPVerInfo_getIsActive (
  LLRP_tSSPVerInfo *pThis);

extern LLRP_tResultCode
LLRP_SPVerInfo_setIsActive (
  LLRP_tSSPVerInfo *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSPVerInfo_IsUsedOrSpare;

extern llrp_u8_t
LLRP_SPVerInfo_getIsUsedOrSpare (
  LLRP_tSSPVerInfo *pThis);

extern LLRP_tResultCode
LLRP_SPVerInfo_setIsUsedOrSpare (
  LLRP_tSSPVerInfo *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSPVerInfo_IsSetUse;

extern llrp_u8_t
LLRP_SPVerInfo_getIsSetUse (
  LLRP_tSSPVerInfo *pThis);

extern LLRP_tResultCode
LLRP_SPVerInfo_setIsSetUse (
  LLRP_tSSPVerInfo *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdSPVerInfo_SPVerInfo;

extern llrp_utf8v_t
LLRP_SPVerInfo_getSPVerInfo (
  LLRP_tSSPVerInfo *pThis);

extern LLRP_tResultCode
LLRP_SPVerInfo_setSPVerInfo (
  LLRP_tSSPVerInfo *pThis,
  llrp_utf8v_t Value);

  


  
struct LLRP_SReaderRunLog
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t EventId;

    llrp_u32_t Time;

    llrp_u8v_t LogData;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdReaderRunLog;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdReaderRunLog[];

extern LLRP_tSReaderRunLog *
LLRP_ReaderRunLog_construct (void);

extern void
LLRP_ReaderRunLog_destruct (
 LLRP_tSReaderRunLog * pThis);

extern void
LLRP_ReaderRunLog_decodeFields (
 LLRP_tSReaderRunLog * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_ReaderRunLog_assimilateSubParameters (
 LLRP_tSReaderRunLog * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_ReaderRunLog_encode (
  const LLRP_tSReaderRunLog *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_ReaderRunLog_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdReaderRunLog_EventId;

extern llrp_u16_t
LLRP_ReaderRunLog_getEventId (
  LLRP_tSReaderRunLog *pThis);

extern LLRP_tResultCode
LLRP_ReaderRunLog_setEventId (
  LLRP_tSReaderRunLog *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdReaderRunLog_Time;

extern llrp_u32_t
LLRP_ReaderRunLog_getTime (
  LLRP_tSReaderRunLog *pThis);

extern LLRP_tResultCode
LLRP_ReaderRunLog_setTime (
  LLRP_tSReaderRunLog *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdReaderRunLog_LogData;

extern llrp_u8v_t
LLRP_ReaderRunLog_getLogData (
  LLRP_tSReaderRunLog *pThis);

extern LLRP_tResultCode
LLRP_ReaderRunLog_setLogData (
  LLRP_tSReaderRunLog *pThis,
  llrp_u8v_t Value);

  


  
struct LLRP_SReaderRunException
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t FileId;

    llrp_u16_t Line;

    llrp_u32_t Time;

    llrp_u32_t Reversed1;

    llrp_u32_t Reversed2;

    llrp_u32_t Reversed3;

    llrp_u32_t ReasonId;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdReaderRunException;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdReaderRunException[];

extern LLRP_tSReaderRunException *
LLRP_ReaderRunException_construct (void);

extern void
LLRP_ReaderRunException_destruct (
 LLRP_tSReaderRunException * pThis);

extern void
LLRP_ReaderRunException_decodeFields (
 LLRP_tSReaderRunException * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_ReaderRunException_assimilateSubParameters (
 LLRP_tSReaderRunException * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_ReaderRunException_encode (
  const LLRP_tSReaderRunException *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_ReaderRunException_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdReaderRunException_FileId;

extern llrp_u16_t
LLRP_ReaderRunException_getFileId (
  LLRP_tSReaderRunException *pThis);

extern LLRP_tResultCode
LLRP_ReaderRunException_setFileId (
  LLRP_tSReaderRunException *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdReaderRunException_Line;

extern llrp_u16_t
LLRP_ReaderRunException_getLine (
  LLRP_tSReaderRunException *pThis);

extern LLRP_tResultCode
LLRP_ReaderRunException_setLine (
  LLRP_tSReaderRunException *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdReaderRunException_Time;

extern llrp_u32_t
LLRP_ReaderRunException_getTime (
  LLRP_tSReaderRunException *pThis);

extern LLRP_tResultCode
LLRP_ReaderRunException_setTime (
  LLRP_tSReaderRunException *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdReaderRunException_Reversed1;

extern llrp_u32_t
LLRP_ReaderRunException_getReversed1 (
  LLRP_tSReaderRunException *pThis);

extern LLRP_tResultCode
LLRP_ReaderRunException_setReversed1 (
  LLRP_tSReaderRunException *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdReaderRunException_Reversed2;

extern llrp_u32_t
LLRP_ReaderRunException_getReversed2 (
  LLRP_tSReaderRunException *pThis);

extern LLRP_tResultCode
LLRP_ReaderRunException_setReversed2 (
  LLRP_tSReaderRunException *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdReaderRunException_Reversed3;

extern llrp_u32_t
LLRP_ReaderRunException_getReversed3 (
  LLRP_tSReaderRunException *pThis);

extern LLRP_tResultCode
LLRP_ReaderRunException_setReversed3 (
  LLRP_tSReaderRunException *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdReaderRunException_ReasonId;

extern llrp_u32_t
LLRP_ReaderRunException_getReasonId (
  LLRP_tSReaderRunException *pThis);

extern LLRP_tResultCode
LLRP_ReaderRunException_setReasonId (
  LLRP_tSReaderRunException *pThis,
  llrp_u32_t Value);

  


  
struct LLRP_SRUPReaderRunLog
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t BoardId;

    llrp_u16_t EventId;

    llrp_u32_t Time;

    llrp_u8v_t LogData;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdRUPReaderRunLog;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdRUPReaderRunLog[];

extern LLRP_tSRUPReaderRunLog *
LLRP_RUPReaderRunLog_construct (void);

extern void
LLRP_RUPReaderRunLog_destruct (
 LLRP_tSRUPReaderRunLog * pThis);

extern void
LLRP_RUPReaderRunLog_decodeFields (
 LLRP_tSRUPReaderRunLog * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_RUPReaderRunLog_assimilateSubParameters (
 LLRP_tSRUPReaderRunLog * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_RUPReaderRunLog_encode (
  const LLRP_tSRUPReaderRunLog *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_RUPReaderRunLog_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdRUPReaderRunLog_BoardId;

extern llrp_u16_t
LLRP_RUPReaderRunLog_getBoardId (
  LLRP_tSRUPReaderRunLog *pThis);

extern LLRP_tResultCode
LLRP_RUPReaderRunLog_setBoardId (
  LLRP_tSRUPReaderRunLog *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdRUPReaderRunLog_EventId;

extern llrp_u16_t
LLRP_RUPReaderRunLog_getEventId (
  LLRP_tSRUPReaderRunLog *pThis);

extern LLRP_tResultCode
LLRP_RUPReaderRunLog_setEventId (
  LLRP_tSRUPReaderRunLog *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdRUPReaderRunLog_Time;

extern llrp_u32_t
LLRP_RUPReaderRunLog_getTime (
  LLRP_tSRUPReaderRunLog *pThis);

extern LLRP_tResultCode
LLRP_RUPReaderRunLog_setTime (
  LLRP_tSRUPReaderRunLog *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdRUPReaderRunLog_LogData;

extern llrp_u8v_t
LLRP_RUPReaderRunLog_getLogData (
  LLRP_tSRUPReaderRunLog *pThis);

extern LLRP_tResultCode
LLRP_RUPReaderRunLog_setLogData (
  LLRP_tSRUPReaderRunLog *pThis,
  llrp_u8v_t Value);

  


  
struct LLRP_SRUPReaderRunException
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t BoardId;

    llrp_u8v_t FileName;

    llrp_u16_t Line;

    llrp_u32_t Time;

    llrp_u32_t Reversed1;

    llrp_u32_t Reversed2;

    llrp_u32_t Reversed3;

    llrp_u32_t ReasonId;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdRUPReaderRunException;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdRUPReaderRunException[];

extern LLRP_tSRUPReaderRunException *
LLRP_RUPReaderRunException_construct (void);

extern void
LLRP_RUPReaderRunException_destruct (
 LLRP_tSRUPReaderRunException * pThis);

extern void
LLRP_RUPReaderRunException_decodeFields (
 LLRP_tSRUPReaderRunException * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_RUPReaderRunException_assimilateSubParameters (
 LLRP_tSRUPReaderRunException * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_RUPReaderRunException_encode (
  const LLRP_tSRUPReaderRunException *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_RUPReaderRunException_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdRUPReaderRunException_BoardId;

extern llrp_u16_t
LLRP_RUPReaderRunException_getBoardId (
  LLRP_tSRUPReaderRunException *pThis);

extern LLRP_tResultCode
LLRP_RUPReaderRunException_setBoardId (
  LLRP_tSRUPReaderRunException *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdRUPReaderRunException_FileName;

extern llrp_u8v_t
LLRP_RUPReaderRunException_getFileName (
  LLRP_tSRUPReaderRunException *pThis);

extern LLRP_tResultCode
LLRP_RUPReaderRunException_setFileName (
  LLRP_tSRUPReaderRunException *pThis,
  llrp_u8v_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdRUPReaderRunException_Line;

extern llrp_u16_t
LLRP_RUPReaderRunException_getLine (
  LLRP_tSRUPReaderRunException *pThis);

extern LLRP_tResultCode
LLRP_RUPReaderRunException_setLine (
  LLRP_tSRUPReaderRunException *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdRUPReaderRunException_Time;

extern llrp_u32_t
LLRP_RUPReaderRunException_getTime (
  LLRP_tSRUPReaderRunException *pThis);

extern LLRP_tResultCode
LLRP_RUPReaderRunException_setTime (
  LLRP_tSRUPReaderRunException *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdRUPReaderRunException_Reversed1;

extern llrp_u32_t
LLRP_RUPReaderRunException_getReversed1 (
  LLRP_tSRUPReaderRunException *pThis);

extern LLRP_tResultCode
LLRP_RUPReaderRunException_setReversed1 (
  LLRP_tSRUPReaderRunException *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdRUPReaderRunException_Reversed2;

extern llrp_u32_t
LLRP_RUPReaderRunException_getReversed2 (
  LLRP_tSRUPReaderRunException *pThis);

extern LLRP_tResultCode
LLRP_RUPReaderRunException_setReversed2 (
  LLRP_tSRUPReaderRunException *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdRUPReaderRunException_Reversed3;

extern llrp_u32_t
LLRP_RUPReaderRunException_getReversed3 (
  LLRP_tSRUPReaderRunException *pThis);

extern LLRP_tResultCode
LLRP_RUPReaderRunException_setReversed3 (
  LLRP_tSRUPReaderRunException *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdRUPReaderRunException_ReasonId;

extern llrp_u32_t
LLRP_RUPReaderRunException_getReasonId (
  LLRP_tSRUPReaderRunException *pThis);

extern LLRP_tResultCode
LLRP_RUPReaderRunException_setReasonId (
  LLRP_tSRUPReaderRunException *pThis,
  llrp_u32_t Value);

  


  
struct LLRP_SLogicCardCmd
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t CmdType;

    llrp_u8_t SectorNum;

    llrp_u8_t BlockNum;

    llrp_u8v_t Datas;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdLogicCardCmd;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdLogicCardCmd[];

extern LLRP_tSLogicCardCmd *
LLRP_LogicCardCmd_construct (void);

extern void
LLRP_LogicCardCmd_destruct (
 LLRP_tSLogicCardCmd * pThis);

extern void
LLRP_LogicCardCmd_decodeFields (
 LLRP_tSLogicCardCmd * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_LogicCardCmd_assimilateSubParameters (
 LLRP_tSLogicCardCmd * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_LogicCardCmd_encode (
  const LLRP_tSLogicCardCmd *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_LogicCardCmd_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdLogicCardCmd_CmdType;

extern llrp_u8_t
LLRP_LogicCardCmd_getCmdType (
  LLRP_tSLogicCardCmd *pThis);

extern LLRP_tResultCode
LLRP_LogicCardCmd_setCmdType (
  LLRP_tSLogicCardCmd *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdLogicCardCmd_SectorNum;

extern llrp_u8_t
LLRP_LogicCardCmd_getSectorNum (
  LLRP_tSLogicCardCmd *pThis);

extern LLRP_tResultCode
LLRP_LogicCardCmd_setSectorNum (
  LLRP_tSLogicCardCmd *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdLogicCardCmd_BlockNum;

extern llrp_u8_t
LLRP_LogicCardCmd_getBlockNum (
  LLRP_tSLogicCardCmd *pThis);

extern LLRP_tResultCode
LLRP_LogicCardCmd_setBlockNum (
  LLRP_tSLogicCardCmd *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdLogicCardCmd_Datas;

extern llrp_u8v_t
LLRP_LogicCardCmd_getDatas (
  LLRP_tSLogicCardCmd *pThis);

extern LLRP_tResultCode
LLRP_LogicCardCmd_setDatas (
  LLRP_tSLogicCardCmd *pThis,
  llrp_u8v_t Value);

  


  
struct LLRP_SLogicCardRsp
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t CmdType;

    llrp_u8_t SectorNum;

    llrp_u8_t BlockNum;

    llrp_u8_t Result;

    llrp_u8v_t Datas;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdLogicCardRsp;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdLogicCardRsp[];

extern LLRP_tSLogicCardRsp *
LLRP_LogicCardRsp_construct (void);

extern void
LLRP_LogicCardRsp_destruct (
 LLRP_tSLogicCardRsp * pThis);

extern void
LLRP_LogicCardRsp_decodeFields (
 LLRP_tSLogicCardRsp * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_LogicCardRsp_assimilateSubParameters (
 LLRP_tSLogicCardRsp * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_LogicCardRsp_encode (
  const LLRP_tSLogicCardRsp *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_LogicCardRsp_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdLogicCardRsp_CmdType;

extern llrp_u8_t
LLRP_LogicCardRsp_getCmdType (
  LLRP_tSLogicCardRsp *pThis);

extern LLRP_tResultCode
LLRP_LogicCardRsp_setCmdType (
  LLRP_tSLogicCardRsp *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdLogicCardRsp_SectorNum;

extern llrp_u8_t
LLRP_LogicCardRsp_getSectorNum (
  LLRP_tSLogicCardRsp *pThis);

extern LLRP_tResultCode
LLRP_LogicCardRsp_setSectorNum (
  LLRP_tSLogicCardRsp *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdLogicCardRsp_BlockNum;

extern llrp_u8_t
LLRP_LogicCardRsp_getBlockNum (
  LLRP_tSLogicCardRsp *pThis);

extern LLRP_tResultCode
LLRP_LogicCardRsp_setBlockNum (
  LLRP_tSLogicCardRsp *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdLogicCardRsp_Result;

extern llrp_u8_t
LLRP_LogicCardRsp_getResult (
  LLRP_tSLogicCardRsp *pThis);

extern LLRP_tResultCode
LLRP_LogicCardRsp_setResult (
  LLRP_tSLogicCardRsp *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdLogicCardRsp_Datas;

extern llrp_u8v_t
LLRP_LogicCardRsp_getDatas (
  LLRP_tSLogicCardRsp *pThis);

extern LLRP_tResultCode
LLRP_LogicCardRsp_setDatas (
  LLRP_tSLogicCardRsp *pThis,
  llrp_u8v_t Value);

  


  
struct LLRP_SCpuCardCmd
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t SockID;

    llrp_u8_t ProtolID;

    llrp_u8v_t Command;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdCpuCardCmd;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdCpuCardCmd[];

extern LLRP_tSCpuCardCmd *
LLRP_CpuCardCmd_construct (void);

extern void
LLRP_CpuCardCmd_destruct (
 LLRP_tSCpuCardCmd * pThis);

extern void
LLRP_CpuCardCmd_decodeFields (
 LLRP_tSCpuCardCmd * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_CpuCardCmd_assimilateSubParameters (
 LLRP_tSCpuCardCmd * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_CpuCardCmd_encode (
  const LLRP_tSCpuCardCmd *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_CpuCardCmd_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdCpuCardCmd_SockID;

extern llrp_u8_t
LLRP_CpuCardCmd_getSockID (
  LLRP_tSCpuCardCmd *pThis);

extern LLRP_tResultCode
LLRP_CpuCardCmd_setSockID (
  LLRP_tSCpuCardCmd *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdCpuCardCmd_ProtolID;

extern llrp_u8_t
LLRP_CpuCardCmd_getProtolID (
  LLRP_tSCpuCardCmd *pThis);

extern LLRP_tResultCode
LLRP_CpuCardCmd_setProtolID (
  LLRP_tSCpuCardCmd *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdCpuCardCmd_Command;

extern llrp_u8v_t
LLRP_CpuCardCmd_getCommand (
  LLRP_tSCpuCardCmd *pThis);

extern LLRP_tResultCode
LLRP_CpuCardCmd_setCommand (
  LLRP_tSCpuCardCmd *pThis,
  llrp_u8v_t Value);

  


  
struct LLRP_SDeviceCmd
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t Cmd;

    llrp_u8_t Parameter;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdDeviceCmd;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdDeviceCmd[];

extern LLRP_tSDeviceCmd *
LLRP_DeviceCmd_construct (void);

extern void
LLRP_DeviceCmd_destruct (
 LLRP_tSDeviceCmd * pThis);

extern void
LLRP_DeviceCmd_decodeFields (
 LLRP_tSDeviceCmd * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_DeviceCmd_assimilateSubParameters (
 LLRP_tSDeviceCmd * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_DeviceCmd_encode (
  const LLRP_tSDeviceCmd *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_DeviceCmd_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdDeviceCmd_Cmd;

extern llrp_u8_t
LLRP_DeviceCmd_getCmd (
  LLRP_tSDeviceCmd *pThis);

extern LLRP_tResultCode
LLRP_DeviceCmd_setCmd (
  LLRP_tSDeviceCmd *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdDeviceCmd_Parameter;

extern llrp_u8_t
LLRP_DeviceCmd_getParameter (
  LLRP_tSDeviceCmd *pThis);

extern LLRP_tResultCode
LLRP_DeviceCmd_setParameter (
  LLRP_tSDeviceCmd *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SCardResetCmd
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t SockID;

    llrp_u8_t ProtocolID;

    llrp_u8_t Cmd;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdCardResetCmd;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdCardResetCmd[];

extern LLRP_tSCardResetCmd *
LLRP_CardResetCmd_construct (void);

extern void
LLRP_CardResetCmd_destruct (
 LLRP_tSCardResetCmd * pThis);

extern void
LLRP_CardResetCmd_decodeFields (
 LLRP_tSCardResetCmd * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_CardResetCmd_assimilateSubParameters (
 LLRP_tSCardResetCmd * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_CardResetCmd_encode (
  const LLRP_tSCardResetCmd *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_CardResetCmd_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdCardResetCmd_SockID;

extern llrp_u8_t
LLRP_CardResetCmd_getSockID (
  LLRP_tSCardResetCmd *pThis);

extern LLRP_tResultCode
LLRP_CardResetCmd_setSockID (
  LLRP_tSCardResetCmd *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdCardResetCmd_ProtocolID;

extern llrp_u8_t
LLRP_CardResetCmd_getProtocolID (
  LLRP_tSCardResetCmd *pThis);

extern LLRP_tResultCode
LLRP_CardResetCmd_setProtocolID (
  LLRP_tSCardResetCmd *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdCardResetCmd_Cmd;

extern llrp_u8_t
LLRP_CardResetCmd_getCmd (
  LLRP_tSCardResetCmd *pThis);

extern LLRP_tResultCode
LLRP_CardResetCmd_setCmd (
  LLRP_tSCardResetCmd *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SCardResetRsp
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t SockID;

    llrp_u8_t ProtocolID;

    llrp_u8_t Result;

    llrp_u8v_t Datas;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdCardResetRsp;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdCardResetRsp[];

extern LLRP_tSCardResetRsp *
LLRP_CardResetRsp_construct (void);

extern void
LLRP_CardResetRsp_destruct (
 LLRP_tSCardResetRsp * pThis);

extern void
LLRP_CardResetRsp_decodeFields (
 LLRP_tSCardResetRsp * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_CardResetRsp_assimilateSubParameters (
 LLRP_tSCardResetRsp * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_CardResetRsp_encode (
  const LLRP_tSCardResetRsp *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_CardResetRsp_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdCardResetRsp_SockID;

extern llrp_u8_t
LLRP_CardResetRsp_getSockID (
  LLRP_tSCardResetRsp *pThis);

extern LLRP_tResultCode
LLRP_CardResetRsp_setSockID (
  LLRP_tSCardResetRsp *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdCardResetRsp_ProtocolID;

extern llrp_u8_t
LLRP_CardResetRsp_getProtocolID (
  LLRP_tSCardResetRsp *pThis);

extern LLRP_tResultCode
LLRP_CardResetRsp_setProtocolID (
  LLRP_tSCardResetRsp *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdCardResetRsp_Result;

extern llrp_u8_t
LLRP_CardResetRsp_getResult (
  LLRP_tSCardResetRsp *pThis);

extern LLRP_tResultCode
LLRP_CardResetRsp_setResult (
  LLRP_tSCardResetRsp *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdCardResetRsp_Datas;

extern llrp_u8v_t
LLRP_CardResetRsp_getDatas (
  LLRP_tSCardResetRsp *pThis);

extern LLRP_tResultCode
LLRP_CardResetRsp_setDatas (
  LLRP_tSCardResetRsp *pThis,
  llrp_u8v_t Value);

  


  
struct LLRP_SLowLevelCmd
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t ChipID;

    llrp_u8v_t Datas;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdLowLevelCmd;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdLowLevelCmd[];

extern LLRP_tSLowLevelCmd *
LLRP_LowLevelCmd_construct (void);

extern void
LLRP_LowLevelCmd_destruct (
 LLRP_tSLowLevelCmd * pThis);

extern void
LLRP_LowLevelCmd_decodeFields (
 LLRP_tSLowLevelCmd * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_LowLevelCmd_assimilateSubParameters (
 LLRP_tSLowLevelCmd * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_LowLevelCmd_encode (
  const LLRP_tSLowLevelCmd *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_LowLevelCmd_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdLowLevelCmd_ChipID;

extern llrp_u8_t
LLRP_LowLevelCmd_getChipID (
  LLRP_tSLowLevelCmd *pThis);

extern LLRP_tResultCode
LLRP_LowLevelCmd_setChipID (
  LLRP_tSLowLevelCmd *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdLowLevelCmd_Datas;

extern llrp_u8v_t
LLRP_LowLevelCmd_getDatas (
  LLRP_tSLowLevelCmd *pThis);

extern LLRP_tResultCode
LLRP_LowLevelCmd_setDatas (
  LLRP_tSLowLevelCmd *pThis,
  llrp_u8v_t Value);

  


  
struct LLRP_SLowLevelRsp
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t ChipID;

    llrp_u8v_t Datas;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdLowLevelRsp;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdLowLevelRsp[];

extern LLRP_tSLowLevelRsp *
LLRP_LowLevelRsp_construct (void);

extern void
LLRP_LowLevelRsp_destruct (
 LLRP_tSLowLevelRsp * pThis);

extern void
LLRP_LowLevelRsp_decodeFields (
 LLRP_tSLowLevelRsp * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_LowLevelRsp_assimilateSubParameters (
 LLRP_tSLowLevelRsp * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_LowLevelRsp_encode (
  const LLRP_tSLowLevelRsp *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_LowLevelRsp_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdLowLevelRsp_ChipID;

extern llrp_u8_t
LLRP_LowLevelRsp_getChipID (
  LLRP_tSLowLevelRsp *pThis);

extern LLRP_tResultCode
LLRP_LowLevelRsp_setChipID (
  LLRP_tSLowLevelRsp *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdLowLevelRsp_Datas;

extern llrp_u8v_t
LLRP_LowLevelRsp_getDatas (
  LLRP_tSLowLevelRsp *pThis);

extern LLRP_tResultCode
LLRP_LowLevelRsp_setDatas (
  LLRP_tSLowLevelRsp *pThis,
  llrp_u8v_t Value);

  


  
struct LLRP_SBroadCastTimeCmd
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t Year;

    llrp_u8_t Month;

    llrp_u8_t Day;

    llrp_u8_t Hour;

    llrp_u8_t Minute;

    llrp_u8_t Second;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdBroadCastTimeCmd;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdBroadCastTimeCmd[];

extern LLRP_tSBroadCastTimeCmd *
LLRP_BroadCastTimeCmd_construct (void);

extern void
LLRP_BroadCastTimeCmd_destruct (
 LLRP_tSBroadCastTimeCmd * pThis);

extern void
LLRP_BroadCastTimeCmd_decodeFields (
 LLRP_tSBroadCastTimeCmd * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_BroadCastTimeCmd_assimilateSubParameters (
 LLRP_tSBroadCastTimeCmd * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_BroadCastTimeCmd_encode (
  const LLRP_tSBroadCastTimeCmd *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_BroadCastTimeCmd_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdBroadCastTimeCmd_Year;

extern llrp_u16_t
LLRP_BroadCastTimeCmd_getYear (
  LLRP_tSBroadCastTimeCmd *pThis);

extern LLRP_tResultCode
LLRP_BroadCastTimeCmd_setYear (
  LLRP_tSBroadCastTimeCmd *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdBroadCastTimeCmd_Month;

extern llrp_u8_t
LLRP_BroadCastTimeCmd_getMonth (
  LLRP_tSBroadCastTimeCmd *pThis);

extern LLRP_tResultCode
LLRP_BroadCastTimeCmd_setMonth (
  LLRP_tSBroadCastTimeCmd *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdBroadCastTimeCmd_Day;

extern llrp_u8_t
LLRP_BroadCastTimeCmd_getDay (
  LLRP_tSBroadCastTimeCmd *pThis);

extern LLRP_tResultCode
LLRP_BroadCastTimeCmd_setDay (
  LLRP_tSBroadCastTimeCmd *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdBroadCastTimeCmd_Hour;

extern llrp_u8_t
LLRP_BroadCastTimeCmd_getHour (
  LLRP_tSBroadCastTimeCmd *pThis);

extern LLRP_tResultCode
LLRP_BroadCastTimeCmd_setHour (
  LLRP_tSBroadCastTimeCmd *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdBroadCastTimeCmd_Minute;

extern llrp_u8_t
LLRP_BroadCastTimeCmd_getMinute (
  LLRP_tSBroadCastTimeCmd *pThis);

extern LLRP_tResultCode
LLRP_BroadCastTimeCmd_setMinute (
  LLRP_tSBroadCastTimeCmd *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdBroadCastTimeCmd_Second;

extern llrp_u8_t
LLRP_BroadCastTimeCmd_getSecond (
  LLRP_tSBroadCastTimeCmd *pThis);

extern LLRP_tResultCode
LLRP_BroadCastTimeCmd_setSecond (
  LLRP_tSBroadCastTimeCmd *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SAlarmCmd
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t AlarmType;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdAlarmCmd;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdAlarmCmd[];

extern LLRP_tSAlarmCmd *
LLRP_AlarmCmd_construct (void);

extern void
LLRP_AlarmCmd_destruct (
 LLRP_tSAlarmCmd * pThis);

extern void
LLRP_AlarmCmd_decodeFields (
 LLRP_tSAlarmCmd * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_AlarmCmd_assimilateSubParameters (
 LLRP_tSAlarmCmd * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_AlarmCmd_encode (
  const LLRP_tSAlarmCmd *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_AlarmCmd_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdAlarmCmd_AlarmType;

extern llrp_u8_t
LLRP_AlarmCmd_getAlarmType (
  LLRP_tSAlarmCmd *pThis);

extern LLRP_tResultCode
LLRP_AlarmCmd_setAlarmType (
  LLRP_tSAlarmCmd *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SIDRsp
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t Result;

    llrp_u8_t CardNum;

    llrp_u8v_t ID;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdIDRsp;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdIDRsp[];

extern LLRP_tSIDRsp *
LLRP_IDRsp_construct (void);

extern void
LLRP_IDRsp_destruct (
 LLRP_tSIDRsp * pThis);

extern void
LLRP_IDRsp_decodeFields (
 LLRP_tSIDRsp * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_IDRsp_assimilateSubParameters (
 LLRP_tSIDRsp * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_IDRsp_encode (
  const LLRP_tSIDRsp *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_IDRsp_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdIDRsp_Result;

extern llrp_u8_t
LLRP_IDRsp_getResult (
  LLRP_tSIDRsp *pThis);

extern LLRP_tResultCode
LLRP_IDRsp_setResult (
  LLRP_tSIDRsp *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdIDRsp_CardNum;

extern llrp_u8_t
LLRP_IDRsp_getCardNum (
  LLRP_tSIDRsp *pThis);

extern LLRP_tResultCode
LLRP_IDRsp_setCardNum (
  LLRP_tSIDRsp *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdIDRsp_ID;

extern llrp_u8v_t
LLRP_IDRsp_getID (
  LLRP_tSIDRsp *pThis);

extern LLRP_tResultCode
LLRP_IDRsp_setID (
  LLRP_tSIDRsp *pThis,
  llrp_u8v_t Value);

  


  
struct LLRP_SInitKey
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t KeyType;

    llrp_u8v_t Key;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdInitKey;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdInitKey[];

extern LLRP_tSInitKey *
LLRP_InitKey_construct (void);

extern void
LLRP_InitKey_destruct (
 LLRP_tSInitKey * pThis);

extern void
LLRP_InitKey_decodeFields (
 LLRP_tSInitKey * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_InitKey_assimilateSubParameters (
 LLRP_tSInitKey * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_InitKey_encode (
  const LLRP_tSInitKey *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_InitKey_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdInitKey_KeyType;

extern llrp_u8_t
LLRP_InitKey_getKeyType (
  LLRP_tSInitKey *pThis);

extern LLRP_tResultCode
LLRP_InitKey_setKeyType (
  LLRP_tSInitKey *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdInitKey_Key;

extern llrp_u8v_t
LLRP_InitKey_getKey (
  LLRP_tSInitKey *pThis);

extern LLRP_tResultCode
LLRP_InitKey_setKey (
  LLRP_tSInitKey *pThis,
  llrp_u8v_t Value);

  


  
struct LLRP_SInitKeyAck
{
    LLRP_tSParameter hdr;
  
    llrp_u32_t Result;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdInitKeyAck;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdInitKeyAck[];

extern LLRP_tSInitKeyAck *
LLRP_InitKeyAck_construct (void);

extern void
LLRP_InitKeyAck_destruct (
 LLRP_tSInitKeyAck * pThis);

extern void
LLRP_InitKeyAck_decodeFields (
 LLRP_tSInitKeyAck * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_InitKeyAck_assimilateSubParameters (
 LLRP_tSInitKeyAck * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_InitKeyAck_encode (
  const LLRP_tSInitKeyAck *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_InitKeyAck_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdInitKeyAck_Result;

extern llrp_u32_t
LLRP_InitKeyAck_getResult (
  LLRP_tSInitKeyAck *pThis);

extern LLRP_tResultCode
LLRP_InitKeyAck_setResult (
  LLRP_tSInitKeyAck *pThis,
  llrp_u32_t Value);

  


  
struct LLRP_SDeviceCmdArray
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t Cmd;

    llrp_u8v_t Parameter;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdDeviceCmdArray;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdDeviceCmdArray[];

extern LLRP_tSDeviceCmdArray *
LLRP_DeviceCmdArray_construct (void);

extern void
LLRP_DeviceCmdArray_destruct (
 LLRP_tSDeviceCmdArray * pThis);

extern void
LLRP_DeviceCmdArray_decodeFields (
 LLRP_tSDeviceCmdArray * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_DeviceCmdArray_assimilateSubParameters (
 LLRP_tSDeviceCmdArray * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_DeviceCmdArray_encode (
  const LLRP_tSDeviceCmdArray *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_DeviceCmdArray_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdDeviceCmdArray_Cmd;

extern llrp_u8_t
LLRP_DeviceCmdArray_getCmd (
  LLRP_tSDeviceCmdArray *pThis);

extern LLRP_tResultCode
LLRP_DeviceCmdArray_setCmd (
  LLRP_tSDeviceCmdArray *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdDeviceCmdArray_Parameter;

extern llrp_u8v_t
LLRP_DeviceCmdArray_getParameter (
  LLRP_tSDeviceCmdArray *pThis);

extern LLRP_tResultCode
LLRP_DeviceCmdArray_setParameter (
  LLRP_tSDeviceCmdArray *pThis,
  llrp_u8v_t Value);

  


  
struct LLRP_SWiegandPLTCmd
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t CmdType;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdWiegandPLTCmd;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdWiegandPLTCmd[];

extern LLRP_tSWiegandPLTCmd *
LLRP_WiegandPLTCmd_construct (void);

extern void
LLRP_WiegandPLTCmd_destruct (
 LLRP_tSWiegandPLTCmd * pThis);

extern void
LLRP_WiegandPLTCmd_decodeFields (
 LLRP_tSWiegandPLTCmd * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_WiegandPLTCmd_assimilateSubParameters (
 LLRP_tSWiegandPLTCmd * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_WiegandPLTCmd_encode (
  const LLRP_tSWiegandPLTCmd *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_WiegandPLTCmd_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdWiegandPLTCmd_CmdType;

extern llrp_u8_t
LLRP_WiegandPLTCmd_getCmdType (
  LLRP_tSWiegandPLTCmd *pThis);

extern LLRP_tResultCode
LLRP_WiegandPLTCmd_setCmdType (
  LLRP_tSWiegandPLTCmd *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_SWiegandPLTResultCmd
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t Result;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdWiegandPLTResultCmd;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdWiegandPLTResultCmd[];

extern LLRP_tSWiegandPLTResultCmd *
LLRP_WiegandPLTResultCmd_construct (void);

extern void
LLRP_WiegandPLTResultCmd_destruct (
 LLRP_tSWiegandPLTResultCmd * pThis);

extern void
LLRP_WiegandPLTResultCmd_decodeFields (
 LLRP_tSWiegandPLTResultCmd * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_WiegandPLTResultCmd_assimilateSubParameters (
 LLRP_tSWiegandPLTResultCmd * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_WiegandPLTResultCmd_encode (
  const LLRP_tSWiegandPLTResultCmd *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_WiegandPLTResultCmd_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdWiegandPLTResultCmd_Result;

extern llrp_u8_t
LLRP_WiegandPLTResultCmd_getResult (
  LLRP_tSWiegandPLTResultCmd *pThis);

extern LLRP_tResultCode
LLRP_WiegandPLTResultCmd_setResult (
  LLRP_tSWiegandPLTResultCmd *pThis,
  llrp_u8_t Value);

  


  
struct LLRP_STagSimpleTestReport
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t AntennaID;

    llrp_u16_t InventTimeMs;

    llrp_u32_t InventTimeS;

    llrp_u32_t ChannelIndex;

  
    LLRP_tSParameter * pEPCParameter;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdTagSimpleTestReport;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdTagSimpleTestReport[];

extern LLRP_tSTagSimpleTestReport *
LLRP_TagSimpleTestReport_construct (void);

extern void
LLRP_TagSimpleTestReport_destruct (
 LLRP_tSTagSimpleTestReport * pThis);

extern void
LLRP_TagSimpleTestReport_decodeFields (
 LLRP_tSTagSimpleTestReport * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_TagSimpleTestReport_assimilateSubParameters (
 LLRP_tSTagSimpleTestReport * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_TagSimpleTestReport_encode (
  const LLRP_tSTagSimpleTestReport *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_TagSimpleTestReport_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdTagSimpleTestReport_AntennaID;

extern llrp_u8_t
LLRP_TagSimpleTestReport_getAntennaID (
  LLRP_tSTagSimpleTestReport *pThis);

extern LLRP_tResultCode
LLRP_TagSimpleTestReport_setAntennaID (
  LLRP_tSTagSimpleTestReport *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdTagSimpleTestReport_InventTimeMs;

extern llrp_u16_t
LLRP_TagSimpleTestReport_getInventTimeMs (
  LLRP_tSTagSimpleTestReport *pThis);

extern LLRP_tResultCode
LLRP_TagSimpleTestReport_setInventTimeMs (
  LLRP_tSTagSimpleTestReport *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdTagSimpleTestReport_InventTimeS;

extern llrp_u32_t
LLRP_TagSimpleTestReport_getInventTimeS (
  LLRP_tSTagSimpleTestReport *pThis);

extern LLRP_tResultCode
LLRP_TagSimpleTestReport_setInventTimeS (
  LLRP_tSTagSimpleTestReport *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdTagSimpleTestReport_ChannelIndex;

extern llrp_u32_t
LLRP_TagSimpleTestReport_getChannelIndex (
  LLRP_tSTagSimpleTestReport *pThis);

extern LLRP_tResultCode
LLRP_TagSimpleTestReport_setChannelIndex (
  LLRP_tSTagSimpleTestReport *pThis,
  llrp_u32_t Value);

  
extern LLRP_tSParameter *
LLRP_TagSimpleTestReport_getEPCParameter (
  LLRP_tSTagSimpleTestReport *pThis);

extern LLRP_tResultCode
LLRP_TagSimpleTestReport_setEPCParameter (
  LLRP_tSTagSimpleTestReport *pThis,
  LLRP_tSParameter *pValue);



  
struct LLRP_SOnceInventoryStat
{
    LLRP_tSParameter hdr;
  
    llrp_u16_t StartInventTimeMs;

    llrp_u32_t StartInventTimeS;

    llrp_u16_t FinishInventTimeMs;

    llrp_u32_t FinishInventTimeS;

    llrp_u16_t TagNum;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdOnceInventoryStat;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdOnceInventoryStat[];

extern LLRP_tSOnceInventoryStat *
LLRP_OnceInventoryStat_construct (void);

extern void
LLRP_OnceInventoryStat_destruct (
 LLRP_tSOnceInventoryStat * pThis);

extern void
LLRP_OnceInventoryStat_decodeFields (
 LLRP_tSOnceInventoryStat * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_OnceInventoryStat_assimilateSubParameters (
 LLRP_tSOnceInventoryStat * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_OnceInventoryStat_encode (
  const LLRP_tSOnceInventoryStat *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_OnceInventoryStat_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdOnceInventoryStat_StartInventTimeMs;

extern llrp_u16_t
LLRP_OnceInventoryStat_getStartInventTimeMs (
  LLRP_tSOnceInventoryStat *pThis);

extern LLRP_tResultCode
LLRP_OnceInventoryStat_setStartInventTimeMs (
  LLRP_tSOnceInventoryStat *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdOnceInventoryStat_StartInventTimeS;

extern llrp_u32_t
LLRP_OnceInventoryStat_getStartInventTimeS (
  LLRP_tSOnceInventoryStat *pThis);

extern LLRP_tResultCode
LLRP_OnceInventoryStat_setStartInventTimeS (
  LLRP_tSOnceInventoryStat *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdOnceInventoryStat_FinishInventTimeMs;

extern llrp_u16_t
LLRP_OnceInventoryStat_getFinishInventTimeMs (
  LLRP_tSOnceInventoryStat *pThis);

extern LLRP_tResultCode
LLRP_OnceInventoryStat_setFinishInventTimeMs (
  LLRP_tSOnceInventoryStat *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdOnceInventoryStat_FinishInventTimeS;

extern llrp_u32_t
LLRP_OnceInventoryStat_getFinishInventTimeS (
  LLRP_tSOnceInventoryStat *pThis);

extern LLRP_tResultCode
LLRP_OnceInventoryStat_setFinishInventTimeS (
  LLRP_tSOnceInventoryStat *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdOnceInventoryStat_TagNum;

extern llrp_u16_t
LLRP_OnceInventoryStat_getTagNum (
  LLRP_tSOnceInventoryStat *pThis);

extern LLRP_tResultCode
LLRP_OnceInventoryStat_setTagNum (
  LLRP_tSOnceInventoryStat *pThis,
  llrp_u16_t Value);

  


  
struct LLRP_SSimpleC1G2ReadParameter
{
    LLRP_tSParameter hdr;
  
  
    LLRP_tSC1G2TagInventoryMask * pC1G2TagInventoryMask;

    LLRP_tSC1G2Read * pC1G2Read;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdSimpleC1G2ReadParameter;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSimpleC1G2ReadParameter[];

extern LLRP_tSSimpleC1G2ReadParameter *
LLRP_SimpleC1G2ReadParameter_construct (void);

extern void
LLRP_SimpleC1G2ReadParameter_destruct (
 LLRP_tSSimpleC1G2ReadParameter * pThis);

extern void
LLRP_SimpleC1G2ReadParameter_decodeFields (
 LLRP_tSSimpleC1G2ReadParameter * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SimpleC1G2ReadParameter_assimilateSubParameters (
 LLRP_tSSimpleC1G2ReadParameter * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SimpleC1G2ReadParameter_encode (
  const LLRP_tSSimpleC1G2ReadParameter *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_SimpleC1G2ReadParameter_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
  
extern LLRP_tSC1G2TagInventoryMask *
LLRP_SimpleC1G2ReadParameter_getC1G2TagInventoryMask (
  LLRP_tSSimpleC1G2ReadParameter *pThis);

extern LLRP_tResultCode
LLRP_SimpleC1G2ReadParameter_setC1G2TagInventoryMask (
  LLRP_tSSimpleC1G2ReadParameter *pThis,
  LLRP_tSC1G2TagInventoryMask *pValue);

extern LLRP_tSC1G2Read *
LLRP_SimpleC1G2ReadParameter_getC1G2Read (
  LLRP_tSSimpleC1G2ReadParameter *pThis);

extern LLRP_tResultCode
LLRP_SimpleC1G2ReadParameter_setC1G2Read (
  LLRP_tSSimpleC1G2ReadParameter *pThis,
  LLRP_tSC1G2Read *pValue);



  
struct LLRP_SSimpleISO6BReadParameter
{
    LLRP_tSParameter hdr;
  
  
    LLRP_tSUIDData * pUIDData;

    LLRP_tSISO6BRead * pISO6BRead;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdSimpleISO6BReadParameter;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSimpleISO6BReadParameter[];

extern LLRP_tSSimpleISO6BReadParameter *
LLRP_SimpleISO6BReadParameter_construct (void);

extern void
LLRP_SimpleISO6BReadParameter_destruct (
 LLRP_tSSimpleISO6BReadParameter * pThis);

extern void
LLRP_SimpleISO6BReadParameter_decodeFields (
 LLRP_tSSimpleISO6BReadParameter * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SimpleISO6BReadParameter_assimilateSubParameters (
 LLRP_tSSimpleISO6BReadParameter * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SimpleISO6BReadParameter_encode (
  const LLRP_tSSimpleISO6BReadParameter *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_SimpleISO6BReadParameter_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
  
extern LLRP_tSUIDData *
LLRP_SimpleISO6BReadParameter_getUIDData (
  LLRP_tSSimpleISO6BReadParameter *pThis);

extern LLRP_tResultCode
LLRP_SimpleISO6BReadParameter_setUIDData (
  LLRP_tSSimpleISO6BReadParameter *pThis,
  LLRP_tSUIDData *pValue);

extern LLRP_tSISO6BRead *
LLRP_SimpleISO6BReadParameter_getISO6BRead (
  LLRP_tSSimpleISO6BReadParameter *pThis);

extern LLRP_tResultCode
LLRP_SimpleISO6BReadParameter_setISO6BRead (
  LLRP_tSSimpleISO6BReadParameter *pThis,
  LLRP_tSISO6BRead *pValue);



  
struct LLRP_SSimpleC1G2WriteParameter
{
    LLRP_tSParameter hdr;
  
  
    LLRP_tSC1G2TagInventoryMask * pC1G2TagInventoryMask;

    LLRP_tSC1G2Write * pC1G2Write;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdSimpleC1G2WriteParameter;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSimpleC1G2WriteParameter[];

extern LLRP_tSSimpleC1G2WriteParameter *
LLRP_SimpleC1G2WriteParameter_construct (void);

extern void
LLRP_SimpleC1G2WriteParameter_destruct (
 LLRP_tSSimpleC1G2WriteParameter * pThis);

extern void
LLRP_SimpleC1G2WriteParameter_decodeFields (
 LLRP_tSSimpleC1G2WriteParameter * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SimpleC1G2WriteParameter_assimilateSubParameters (
 LLRP_tSSimpleC1G2WriteParameter * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SimpleC1G2WriteParameter_encode (
  const LLRP_tSSimpleC1G2WriteParameter *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_SimpleC1G2WriteParameter_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
  
extern LLRP_tSC1G2TagInventoryMask *
LLRP_SimpleC1G2WriteParameter_getC1G2TagInventoryMask (
  LLRP_tSSimpleC1G2WriteParameter *pThis);

extern LLRP_tResultCode
LLRP_SimpleC1G2WriteParameter_setC1G2TagInventoryMask (
  LLRP_tSSimpleC1G2WriteParameter *pThis,
  LLRP_tSC1G2TagInventoryMask *pValue);

extern LLRP_tSC1G2Write *
LLRP_SimpleC1G2WriteParameter_getC1G2Write (
  LLRP_tSSimpleC1G2WriteParameter *pThis);

extern LLRP_tResultCode
LLRP_SimpleC1G2WriteParameter_setC1G2Write (
  LLRP_tSSimpleC1G2WriteParameter *pThis,
  LLRP_tSC1G2Write *pValue);



  
struct LLRP_SSimpleISO6BWriteParameter
{
    LLRP_tSParameter hdr;
  
  
    LLRP_tSUIDData * pUIDData;

    LLRP_tSISO6BWrite * pISO6BWrite;

};

extern const LLRP_tSTypeDescriptor
LLRP_tdSimpleISO6BWriteParameter;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdSimpleISO6BWriteParameter[];

extern LLRP_tSSimpleISO6BWriteParameter *
LLRP_SimpleISO6BWriteParameter_construct (void);

extern void
LLRP_SimpleISO6BWriteParameter_destruct (
 LLRP_tSSimpleISO6BWriteParameter * pThis);

extern void
LLRP_SimpleISO6BWriteParameter_decodeFields (
 LLRP_tSSimpleISO6BWriteParameter * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_SimpleISO6BWriteParameter_assimilateSubParameters (
 LLRP_tSSimpleISO6BWriteParameter * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_SimpleISO6BWriteParameter_encode (
  const LLRP_tSSimpleISO6BWriteParameter *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_SimpleISO6BWriteParameter_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
  
extern LLRP_tSUIDData *
LLRP_SimpleISO6BWriteParameter_getUIDData (
  LLRP_tSSimpleISO6BWriteParameter *pThis);

extern LLRP_tResultCode
LLRP_SimpleISO6BWriteParameter_setUIDData (
  LLRP_tSSimpleISO6BWriteParameter *pThis,
  LLRP_tSUIDData *pValue);

extern LLRP_tSISO6BWrite *
LLRP_SimpleISO6BWriteParameter_getISO6BWrite (
  LLRP_tSSimpleISO6BWriteParameter *pThis);

extern LLRP_tResultCode
LLRP_SimpleISO6BWriteParameter_setISO6BWrite (
  LLRP_tSSimpleISO6BWriteParameter *pThis,
  LLRP_tSISO6BWrite *pValue);



  
struct LLRP_STrackConfig
{
    LLRP_tSParameter hdr;
  
    llrp_u8_t DirectionSwitch;

    llrp_u8_t DetailSwitch;

    llrp_u16_t TrackMask;

    llrp_u1v_t ModuleSwitch;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdTrackConfig;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdTrackConfig[];

extern LLRP_tSTrackConfig *
LLRP_TrackConfig_construct (void);

extern void
LLRP_TrackConfig_destruct (
 LLRP_tSTrackConfig * pThis);

extern void
LLRP_TrackConfig_decodeFields (
 LLRP_tSTrackConfig * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_TrackConfig_assimilateSubParameters (
 LLRP_tSTrackConfig * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_TrackConfig_encode (
  const LLRP_tSTrackConfig *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_TrackConfig_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdTrackConfig_DirectionSwitch;

extern llrp_u8_t
LLRP_TrackConfig_getDirectionSwitch (
  LLRP_tSTrackConfig *pThis);

extern LLRP_tResultCode
LLRP_TrackConfig_setDirectionSwitch (
  LLRP_tSTrackConfig *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdTrackConfig_DetailSwitch;

extern llrp_u8_t
LLRP_TrackConfig_getDetailSwitch (
  LLRP_tSTrackConfig *pThis);

extern LLRP_tResultCode
LLRP_TrackConfig_setDetailSwitch (
  LLRP_tSTrackConfig *pThis,
  llrp_u8_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdTrackConfig_TrackMask;

extern llrp_u16_t
LLRP_TrackConfig_getTrackMask (
  LLRP_tSTrackConfig *pThis);

extern LLRP_tResultCode
LLRP_TrackConfig_setTrackMask (
  LLRP_tSTrackConfig *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdTrackConfig_ModuleSwitch;

extern llrp_u1v_t
LLRP_TrackConfig_getModuleSwitch (
  LLRP_tSTrackConfig *pThis);

extern LLRP_tResultCode
LLRP_TrackConfig_setModuleSwitch (
  LLRP_tSTrackConfig *pThis,
  llrp_u1v_t Value);

  


  
struct LLRP_SRunInfoConfig
{
    LLRP_tSParameter hdr;
  
    llrp_u1v_t LevelSwitch;

    llrp_u1v_t ModuleSwitch;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdRunInfoConfig;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdRunInfoConfig[];

extern LLRP_tSRunInfoConfig *
LLRP_RunInfoConfig_construct (void);

extern void
LLRP_RunInfoConfig_destruct (
 LLRP_tSRunInfoConfig * pThis);

extern void
LLRP_RunInfoConfig_decodeFields (
 LLRP_tSRunInfoConfig * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_RunInfoConfig_assimilateSubParameters (
 LLRP_tSRunInfoConfig * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_RunInfoConfig_encode (
  const LLRP_tSRunInfoConfig *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_RunInfoConfig_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdRunInfoConfig_LevelSwitch;

extern llrp_u1v_t
LLRP_RunInfoConfig_getLevelSwitch (
  LLRP_tSRunInfoConfig *pThis);

extern LLRP_tResultCode
LLRP_RunInfoConfig_setLevelSwitch (
  LLRP_tSRunInfoConfig *pThis,
  llrp_u1v_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdRunInfoConfig_ModuleSwitch;

extern llrp_u1v_t
LLRP_RunInfoConfig_getModuleSwitch (
  LLRP_tSRunInfoConfig *pThis);

extern LLRP_tResultCode
LLRP_RunInfoConfig_setModuleSwitch (
  LLRP_tSRunInfoConfig *pThis,
  llrp_u1v_t Value);

  


  
struct LLRP_SPwdIndexPara
{
    LLRP_tSParameter hdr;
  
    llrp_u32_t MB;

    llrp_u16_t WordPointer;

    llrp_u16_t WordCount;

  
};

extern const LLRP_tSTypeDescriptor
LLRP_tdPwdIndexPara;

extern const LLRP_tSFieldDescriptor *
LLRP_apfdPwdIndexPara[];

extern LLRP_tSPwdIndexPara *
LLRP_PwdIndexPara_construct (void);

extern void
LLRP_PwdIndexPara_destruct (
 LLRP_tSPwdIndexPara * pThis);

extern void
LLRP_PwdIndexPara_decodeFields (
 LLRP_tSPwdIndexPara * pThis,
 LLRP_tSDecoderStream * pDecoderStream);

extern void
LLRP_PwdIndexPara_assimilateSubParameters (
 LLRP_tSPwdIndexPara * pThis,
 LLRP_tSErrorDetails *          pError);

extern void
LLRP_PwdIndexPara_encode (
  const LLRP_tSPwdIndexPara *pThis,
  LLRP_tSEncoderStream *        pEncoderStream);

  
extern llrp_bool_t
LLRP_PwdIndexPara_isAllowedIn (
  const LLRP_tSTypeDescriptor *pEnclosingElementType);
  

  
extern const LLRP_tSFieldDescriptor
LLRP_fdPwdIndexPara_MB;

extern llrp_u32_t
LLRP_PwdIndexPara_getMB (
  LLRP_tSPwdIndexPara *pThis);

extern LLRP_tResultCode
LLRP_PwdIndexPara_setMB (
  LLRP_tSPwdIndexPara *pThis,
  llrp_u32_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdPwdIndexPara_WordPointer;

extern llrp_u16_t
LLRP_PwdIndexPara_getWordPointer (
  LLRP_tSPwdIndexPara *pThis);

extern LLRP_tResultCode
LLRP_PwdIndexPara_setWordPointer (
  LLRP_tSPwdIndexPara *pThis,
  llrp_u16_t Value);

extern const LLRP_tSFieldDescriptor
LLRP_fdPwdIndexPara_WordCount;

extern llrp_u16_t
LLRP_PwdIndexPara_getWordCount (
  LLRP_tSPwdIndexPara *pThis);

extern LLRP_tResultCode
LLRP_PwdIndexPara_setWordCount (
  LLRP_tSPwdIndexPara *pThis,
  llrp_u16_t Value);

  



extern llrp_bool_t
LLRP_Testdata_isMember (
  LLRP_tSParameter *            pParameter);

extern const LLRP_tSTypeDescriptor
LLRP_tdTestdata;


extern llrp_bool_t
LLRP_TestdataAck_isMember (
  LLRP_tSParameter *            pParameter);

extern const LLRP_tSTypeDescriptor
LLRP_tdTestdataAck;


extern llrp_bool_t
LLRP_TbTestdata_isMember (
  LLRP_tSParameter *            pParameter);

extern const LLRP_tSTypeDescriptor
LLRP_tdTbTestdata;


extern llrp_bool_t
LLRP_TbTestdataAck_isMember (
  LLRP_tSParameter *            pParameter);

extern const LLRP_tSTypeDescriptor
LLRP_tdTbTestdataAck;


extern llrp_bool_t
LLRP_Read_isMember (
  LLRP_tSParameter *            pParameter);

extern const LLRP_tSTypeDescriptor
LLRP_tdRead;


extern llrp_bool_t
LLRP_Write_isMember (
  LLRP_tSParameter *            pParameter);

extern const LLRP_tSTypeDescriptor
LLRP_tdWrite;


extern llrp_bool_t
LLRP_ReadOpSpecResult_isMember (
  LLRP_tSParameter *            pParameter);

extern const LLRP_tSTypeDescriptor
LLRP_tdReadOpSpecResult;


extern llrp_bool_t
LLRP_WriteOpSpecResult_isMember (
  LLRP_tSParameter *            pParameter);

extern const LLRP_tSTypeDescriptor
LLRP_tdWriteOpSpecResult;


void
LLRP_enrollLLRPCustTypesIntoRegistry (
  LLRP_tSTypeRegistry *         pTypeRegistry);

