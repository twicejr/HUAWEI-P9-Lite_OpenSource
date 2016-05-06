#ifndef NSR_OSPF_COMMON_INCLUDED
#define NSR_OSPF_COMMON_INCLUDED

/*NSR OSPF备份TLV头的长度*/
#define NSR_OSPF_TLV_HEAD_LEN   2


#define NSR_OSPF_PUT_CHAR(B, C)   \
  (B)[0] = (NBB_BYTE)(C);  \
  (B)++;
  
#define NSR_OSPF_GET_CHAR(C, B)   \
  (C) = ((NBB_BYTE*)(B))[0]; \
  (B)++;

#define NSR_OSPF_PUT_SHORT(B, S)    \
  NBB_PUT_SHORT(B, S); \
  (B) += 2;

#define NSR_OSPF_GET_SHORT(S, B)    \
  NBB_GET_SHORT(S, B); \
  (B) += 2;

#define NSR_OSPF_PUT_LONG(B, L)     \
  NBB_PUT_LONG(B, L);  \
  (B) += 4;

#define NSR_OSPF_GET_LONG(L, B)     \
  NBB_GET_LONG(L, B);  \
  (B) += 4;

NBB_BOOL nsr_ospf_is_field_present(NBB_VOID *field_info, NBB_UINT field);
NBB_BOOL nsr_ospf_are_all_fields_present(NBB_VOID *field_info);
NBB_VOID nsr_ospf_set_field_present(NBB_VOID *field_info, NBB_UINT field);
NBB_VOID nsr_ospf_set_field_not_present(NBB_VOID *field_info, NBB_UINT field);
NBB_VOID nsr_ospf_set_all_fields_present(NBB_VOID *field_info);
NBB_VOID nsr_ospf_set_all_fields_not_present(NBB_VOID *field_info);
NBB_ULONG nsr_ospf_fill_tlv_header(NBB_BYTE *data_start, NBB_BYTE tlv_type, NBB_USHORT data_len);
NBB_ULONG nsr_ospf_get_tlv_header(NBB_BYTE *data_start, NBB_BYTE *tlv_type, NBB_USHORT *data_len);
NBB_INT nsr_ospf_compare_byte(NBB_VOID *first, NBB_VOID *second);

/*添加OSPF备份数据TLV头*/
#define NSR_OSPF_FILL_TLV_HEADER(DATA_START, TLV_TYPE, DATA_LEN)  \
  (NBB_VOID)nsr_ospf_fill_tlv_header(DATA_START, TLV_TYPE, DATA_LEN); \
  (DATA_START) += NSR_OSPF_TLV_HEAD_LEN;

/*获取OSPF备份数据TLV头*/
#define NSR_OSPF_GET_TLV_HEADER(DATA_START, TLV_TYPE, DATA_LEN)  \
  (NBB_VOID)nsr_ospf_get_tlv_header((DATA_START), (TLV_TYPE), (DATA_LEN)); \
  (DATA_START) += NSR_OSPF_TLV_HEAD_LEN;

#endif

