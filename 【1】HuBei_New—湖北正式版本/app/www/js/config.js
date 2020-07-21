

function updateRuningMode(data){
	if(data.mode){
			$("#runingmode").text("已打开");
			$("#runingmode").css("color", "green");
			$("#btn-open").addClass("easyui-linkbutton");
			$("#btn-open").text("关闭天线");

		}else{
			$("#runingmode").text("未打开");
			$("#runingmode").css("color", "red");
			$("#btn-open").addClass("easyui-linkbutton");
			$("#btn-open").text("打开天线");
		}
}


function getSchedulerRuningmode() {


	url = 'api/v1/scheduler/runingmode';
	$.getJSON(url, function(data, status) {
		updateRuningMode(data)
	})

}

function setSchedulerRuningMode(orig) {
	if(orig == "已打开"){
		$.ajax({
			type:"POST",
			url:'api/v1/scheduler/runingmode',
			contentType: "application/json; charset=utf-8",
			data: JSON.stringify({"mode": false}),
			success: function(data){
				updateRuningMode(data);
			},
			cache:false
		});
	}else{
		$.ajax({
			type:"POST",
			url:'api/v1/scheduler/runingmode',
			contentType: "application/json; charset=utf-8",
			data: JSON.stringify({"mode": true}),
			success: function(data){
				updateRuningMode(data);
			},
			cache:false
		});
	}
}

function updateConfig(config)
{
	var baseconfig = new Array();
	baseconfig[0] = config.baseconfig;
	$("#baseinfo").datagrid({
		data : baseconfig
	}
	);
	
	if(config.extendconfig.aid == 1)
	{
		config.extendconfig.aid = "AID1";
	}
	else
	{
		config.extendconfig.aid = "AID2";
	}
	
	if(config.extendconfig.commode == 1)
	{
		config.extendconfig.commode = "link";
	}
	else
	{
		config.extendconfig.commode = "broadcast";
	}
	
	var extendconfig = new Array();
	extendconfig[0] = config.extendconfig;
	$("#extendinfo").datagrid({
		data : extendconfig
	}
	);

	var psamconfig = config.psamconfig;
	for(var i=0; i<psamconfig.length; ++i){
		psam = psamconfig[i];
		if(psam.type == 1){
			psam.type = "SM4";
		}else{
			psam.type = "TDES";
		}
	}
	$("#psamconfig").datagrid({
		data : psamconfig
	}
	);

	var rfconfig = config.rfconfig
	$("#rfconfig").datagrid({
		data : rfconfig
	}
	);


}

function loadConfig(){
	$.ajax({
			type:"GET",
			url:'api/v1/scheduler/config',
			contentType: "application/json; charset=utf-8",
			success: function(data){
				updateConfig(data);
			},
			error: function(error){
				alert("read config fail");
			},
			cache:false
		});


}

function acceptModify(){
	$('#baseinfo').edatagrid('saveRow');
	$('#extendinfo').edatagrid('saveRow');
	$('#psamconfig').edatagrid('saveRow');
	$('#rfconfig').edatagrid('saveRow');
}

function submitModify(){
	var rawBaseConfig = $("#baseinfo").datagrid('getData');
	var baseconfig = rawBaseConfig["rows"][0];
	baseconfig.sleeptime = Number(baseconfig.sleeptime);
	baseconfig.parallel_trade = Number(baseconfig.parallel_trade);
	baseconfig.serverport = Number(baseconfig.serverport);
	
	var rawExtendConfig = $("#extendinfo").datagrid('getData');
	var extendconfig = rawExtendConfig["rows"][0];
	extendconfig.cpctimeout = Number(extendconfig.cpctimeout);
	extendconfig.cpcinterval = Number(extendconfig.cpcinterval);
	extendconfig.obutimeout = Number(extendconfig.obutimeout);
	extendconfig.obuinterval = Number(extendconfig.obuinterval);
	if(extendconfig.aid == "AID1")
	{
		extendconfig.aid = 1;
	}
	else
	{
		extendconfig.aid = 2;
	}
	
	if(extendconfig.commode == "link")
	{
		extendconfig.commode = 1;
	}
	else
	{
		extendconfig.commode = 2;
	}
	
	var rawPsamConfig = $("#psamconfig").datagrid('getData');
	var psamconfig = rawPsamConfig["rows"];
	for(var i=0; i<psamconfig.length; ++i){
		psam = psamconfig[i];
		if(psam.type == "SM4"){
			psam.type = 1;
		}
		else{
			psam.type = 2;
		}

		if((psam.enable == "false") || (!psam.enable)){
			psam.enable = false;
		}
		else{
			psam.enable = true;
		}
	}


	var rawRfConfig = $("#rfconfig").datagrid('getData');
	var rfconfig = rawRfConfig["rows"];
	for(var i=0; i<rfconfig.length; ++i){
		rf = rfconfig[i];
		if((rf.enable == "false") || (!rf.enable)){
			rf.enable = false;
		}
		else{
			rf.enable = true;
		}
		rf.power = Number(rf.power);
	}

	var config = new Object();
	config["baseconfig"] = baseconfig;
	config["psamconfig"] = psamconfig;
	config["rfconfig"] = rfconfig;
	config["extendconfig"] = extendconfig;
	$.ajax({
			type:"POST",
			url:'api/v1/scheduler/config',
			contentType: "application/json; charset=utf-8",
			data: JSON.stringify(config),
			success: function(data){
				if(data["result"] == "success"){
					alert("submit success, please reboot");
				}else{
					alert("submit fail");
				}
			},
			error: function(error){
				alert("submit fail");
			},
			cache:false
		});

}

function rebootReader(){
	var action = new Object;
	action["action"] = "reboot"
	$.ajax({
			type:"POST",
			url:'api/v1/version',
			contentType: "application/json; charset=utf-8",
			data: JSON.stringify(action),
			success: function(data){
				if(data["result"] == "success"){
					alert("reboot success");
				}
			},
			cache:false
		});
}

$(document).ready(function(){

	/*
	getSchedulerRuningmode();
	$("#btn-open").click(function(){
		setSchedulerRuningMode($("#runingmode").text());
	});
	*/

	loadConfig();
});

