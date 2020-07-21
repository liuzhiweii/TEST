##############################################################
#                  Source path information                   #
##############################################################
#export _USP_SRC_DIR_RDP   :=  $(_USP_SRC_DIR_RDP)

##############################################################
#                  Objects path information                  #
##############################################################
#export _USP_OBJS_DIR_UHF_RDP  :=  $(_USP_OBJS_DIR_UHF_RDP)/RDP



_RDP_OBJS = $(_USP_OBJS_DIR_UHF_RDP)/Rule.o \
            $(_USP_OBJS_DIR_UHF_RDP)/Report.o \
            $(_USP_OBJS_DIR_UHF_RDP)/RuleCheckPara.o \
			$(_USP_OBJS_DIR_UHF_RDP)/ReportSend.o \
	        $(_USP_OBJS_DIR_UHF_RDP)/ReportFilter.o \
			$(_USP_OBJS_DIR_UHF_RDP)/uhfllrpdispatch.o \
		    $(_USP_OBJS_DIR_UHF_RDP)/uhfllrpRule.o \
			$(_USP_OBJS_DIR_UHF_RDP)/uhfllrpEpc.o \
		    $(_USP_OBJS_DIR_UHF_RDP)/uhfllrpISO6B.o \
			$(_USP_OBJS_DIR_UHF_RDP)/uhfllrpGB.o \
		    $(_USP_OBJS_DIR_UHF_RDP)/uhfllrpReport.o	 

.PHONY : all RDP
			  	
all :  RDP
RDP : $(_RDP_OBJS)
	ar r $(_USP_LIB) $(_RDP_OBJS)

$(_USP_OBJS_DIR_UHF_RDP)/Rule.o: Rule.c
	$(CC)  $(CFLAGS) -c $< -o $@

$(_USP_OBJS_DIR_UHF_RDP)/Report.o: Report.c
	$(CC)  $(CFLAGS) -c $< -o $@
	
$(_USP_OBJS_DIR_UHF_RDP)/RuleCheckPara.o: RuleCheckPara.c
	$(CC)  $(CFLAGS) -c $< -o $@

$(_USP_OBJS_DIR_UHF_RDP)/ReportSend.o: ReportSend.c
	$(CC)  $(CFLAGS) -c $< -o $@
	
$(_USP_OBJS_DIR_UHF_RDP)/ReportFilter.o: ReportFilter.c
	$(CC)  $(CFLAGS) -c $< -o $@
	
$(_USP_OBJS_DIR_UHF_RDP)/uhfllrpdispatch.o: uhfllrpdispatch.c
	$(CC)  $(CFLAGS) -c $< -o $@
	
$(_USP_OBJS_DIR_UHF_RDP)/uhfllrpRule.o: uhfllrpRule.c
	$(CC)  $(CFLAGS) -c $< -o $@	
	
$(_USP_OBJS_DIR_UHF_RDP)/uhfllrpEpc.o: uhfllrpEpc.c
	$(CC)  $(CFLAGS) -c $< -o $@	
	
$(_USP_OBJS_DIR_UHF_RDP)/uhfllrpISO6B.o: uhfllrpISO6B.c
	$(CC)  $(CFLAGS) -c $< -o $@	

$(_USP_OBJS_DIR_UHF_RDP)/uhfllrpGB.o: uhfllrpGB.c
	$(CC)  $(CFLAGS) -c $< -o $@	
	
$(_USP_OBJS_DIR_UHF_RDP)/uhfllrpReport.o: uhfllrpReport.c
	$(CC)  $(CFLAGS) -c $< -o $@		
	