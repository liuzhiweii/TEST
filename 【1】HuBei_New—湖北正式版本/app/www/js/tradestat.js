

function clearTradeStat(){
	$.ajax({
			type:"POST",
			url:'api/v1/scheduler/tradestat',
			contentType: "application/json; charset=utf-8",
			data: JSON.stringify({"action": "clear"}),
			success: function(data){
				readTradeStat();
			},
			cache:false
		});
}

function updataDataList(raw_data){
	var successMacs = new Array();
	for(var i=0; i<raw_data.successMacs.length; i++){
		var mac = new Object();
		mac.id = (i+1).toString() + "  " + raw_data.successMacs[i].toString(16);
		mac.value = (i+1).toString() + "  " + raw_data.successMacs[i].toString(16);
		successMacs[i] = mac;		
	}	
	$("#successMacs").datalist({
		data : successMacs
	});
	
	var failMacs = new Array();
	
	for(var i=0; i<raw_data.failMacs.length; i++){
		var mac = new Object();
		mac.id = (i+1).toString() + "  " + raw_data.failMacs[i].toString(16);
		mac.value = (i+1).toString() + "  " + raw_data.failMacs[i].toString(16);
		failMacs[i] = mac;		
	}	
	$("#failMacs").datalist({
		data : failMacs
	});
	
	var timeoutMacs = new Array();
	for(var i=0; i<raw_data.timeoutMacs.length; i++){
		var mac = new Object();
		mac.id = (i+1).toString() + "  " + raw_data.timeoutMacs[i].toString(16);
		mac.value = (i+1).toString() + "  " + raw_data.timeoutMacs[i].toString(16);
		timeoutMacs[i] = mac;		
	}	
	$("#timeoutMacs").datalist({
		data : timeoutMacs
	});
}

function updateUI(data){
	$("#runTime").text(data.runTime);
	$("#tradeNum").text(data.tradeNum);
	$("#successNum").text(data.successNum);
	$("#failNum").text(data.failNum);
	$("#timeoutNum").text(data.timeoutNum);
	$("#minTradeTime").text(data.minTradeTime);
	$("#maxTradeTime").text(data.maxTradeTime);
	$("#avgTradeTime").text(data.avgTradeTime);
	updataDataList(data);
}


function readTradeStat(){
	$.ajax({
			type:"GET",
			url:'api/v1/scheduler/tradestat',
			contentType: "application/json; charset=utf-8",
			success: function(data){
				updateUI(data);
			},
			cache:false
		});
}

function initDataList(){
	$("#successMacs").datalist({
		textField:"id",
		valueField:"value"
	}
	);
	$("#failMacs").datalist({
		textField:"id",
		valueField:"value",
		data:[{id:"A400098", value:"A4000098"},{id:"A400098", value:"A4000098"},{id:"A400098", value:"A4000098"}]
	}
	);
	$("#timeoutMacs").datalist({
		textField:"id",
		valueField:"value",
		data:[{id:"A400098", value:"A4000098"},{id:"A400098", value:"A4000098"},{id:"A400098", value:"A4000098"}]
	}
	);
}

$(document).ready(function(){	
	initDataList();
	readTradeStat();
	setInterval(readTradeStat, 2000);
});
