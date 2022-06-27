$(document).ready(function(){
	const propertyEvents = new EventEmitter();
	const sendToPlugin = AVT_CREATOR_CENTRAL_API.sendToPlugin;
	const sendToProperty = AVT_CREATOR_CENTRAL_API.sendToProperty;
	const setSetting = AVT_CREATOR_CENTRAL_API.setSetting;
	const getSetting = AVT_CREATOR_CENTRAL_API.getSetting;
	const sendToSound = AVT_CREATOR_CENTRAL_API.sendToSound;
	const getToSound = AVT_CREATOR_CENTRAL_API.getToSound;
	const getToFile = AVT_CREATOR_CENTRAL_API.getToFile;
	const sendToFile = AVT_CREATOR_CENTRAL_API.sendToFile;
	const sendToControl = AVT_CREATOR_CENTRAL_API.sendToControl;
	const sendToReview = AVT_CREATOR_CENTRAL_API.sendToReview;
	const getToReview = AVT_CREATOR_CENTRAL_API.getToReview;
	
	let ringVal;
	let cur_audio_files = [];
	let i18n = {};

	AVT_CREATOR_CENTRAL.on('ax.send.to.property', data => {
			let action = '';
			if(data.params.payload.hasOwnProperty('action')) {
					action = data.params.payload.action;
					propertyEvents.emit(action, data.params.payload);
			}
	});

	function sethr(){ 
		for(var i=0;i <13;i++){
			if(i < 10){
				$("#hr_collection").append(`<option value="${i}">0${i}</option>`);
			}else{
				$("#hr_collection").append(`<option value="${i}">${i}</option>`);
			}
		};
	} 
	function setmin(){ 
		for(var i=0;i <60;i++){
			if(i < 10){
				$("#min_collection").append(`<option value="${i}">0${i}</option>`);
			}else{
				$("#min_collection").append(`<option value="${i}">${i}</option>`);
			}
		};
	} 
	sethr();
	setmin();


	$("#hr_collection").change(function(){
		sendToPlugin({
			'action' : 'set_hr_val',
			'hr': $(this).val()
		});  
	});

	$("#min_collection").change(function(){
		sendToPlugin({
			'action' : 'set_min_val',
			'min': $(this).val()
		});  
	});

	$("#am_pm_collection").change(function(){
		sendToPlugin({
			'action' : 'set_ampm_val',
			'ampm': $(this).val()
		});  
	});

	$("#ring").change(function() {
		ringVal=$(this).val()
		console.log('cur ring=' + ringVal)
		if(ringVal == 'default1'){
			$("#delete").removeClass("visible").addClass( "disable" );
		}else{
			$("#delete").removeClass("disable").addClass( "visible" );
		}
		sendToPlugin({
			'action' : 'set_ring_val',
			'ring': $(this).val()
		});  
	});

	$("#output").change(function() {
		sendToPlugin({
			'action' : 'set_output_val',
			'output': $(this).val()
		});  
	});

	$("#refresh").click(function(){
		sendToSound({ }); 
	});

	$("#add_img").click(function(){
		sendToFile({ }); 
	});

	$("#delete").click(function(){
		if(ringVal !== 'default1'){
			let ring_options = $('#ring option')
			for(let i = 0; i < ring_options.length; i++) {
				if(ring_options[i].value == ringVal) {
					ring_options[i].remove();
					break;
				}
			}
			let idx = cur_audio_files.indexOf(ringVal);
			if(idx >= 0) {
				cur_audio_files.splice(idx, 1); // remove from settings
				sendToPlugin({
					'action' : 'set_ring_array_val',
					'array_ring': cur_audio_files
				});  				
			}
			$("#delete").removeClass("visible").addClass( "disable" );
			$("#ring").val('default1')
			$("#ring").change()
		}
		
	})

	propertyEvents.on('send_hr_val', read_hr_val)
	function read_hr_val(data){
		$('#hr_collection').val(data.hr);
	}

	propertyEvents.on('send_min_val', read_min_val)
	function read_min_val(data){
		$('#min_collection').val(data.min);
	}

	propertyEvents.on('send_ampm_val', read_ampm_val)
	function read_ampm_val(data){
		$('#am_pm_collection').val(data.ampm);
	}

	propertyEvents.on('existing_files', build_list);
	function build_list(data) {
		cur_audio_files = []
		for(var i=0;i < data.file.length; i++){
			cur_audio_files.push(data.file[i])
			$("#ring").append(`<option value="${data.file[i]}">${data.file[i]}</option>`);	
		};
	}

	propertyEvents.on('send_ring_val', read_ring_val)
	function read_ring_val(data){
		ringVal = data.ring
		$('#ring').val(data.ring);
		// alert('set ring' + data.ring)
		if(ringVal == 'default1'){
			$("#delete").removeClass("visible").addClass( "disable" );
		}else{
			$("#delete").removeClass("disable").addClass( "visible" );
		}		
	}

	propertyEvents.on('set_ring_array_val', read_ring_array_val)
	function read_ring_array_val(data){
		let add_audio = [];
		for(var i=0;i < data.array_ring.length;i++){
			add_audio.push(data.array_ring[i]);
		}
		sendToReview(add_audio);
	}

	propertyEvents.on('send_devices_val', read_devices_val)
	function read_devices_val(data){
		let deviceName_length=JSON.stringify(data.sound_devices.length);
		$("#output").empty();
		for(var i=0;i < deviceName_length;i++){
			$("#output").append(`<option value="${data.sound_devices[i].deviceId}">${data.sound_devices[i].deviceName}</option>`);	
		};
	}

	propertyEvents.on('send_devices_restart_val', read_devices_restart_val)
	function read_devices_restart_val(data){
		$('#output').val(data.restart_devices);
	}

	propertyEvents.on('send_file_val', read_file_val)
	function read_file_val(data){
		ringVal=data.file.filePath;
		cur_audio_files.push(ringVal);
		$("#ring").append(`<option value="${data.file.filePath}">${data.file.filePath}</option>`);	
		$('#ring').val(ringVal);
		if(ringVal == 'default1'){
			$("#delete").removeClass("visible").addClass( "disable" );
		}else{
			$("#delete").removeClass("disable").addClass( "visible" );
		}
		sendToPlugin({
			'action' : 'set_ring_array_val',
			'array_ring': cur_audio_files
		});  

	}

	propertyEvents.on('setLanguage', data => {
			i18n = localization[data.data];
			for(let k in i18n) {
					$('.' + k).text(i18n[k]);
			}
	});


	AVT_CREATOR_CENTRAL.on('ax.update.existing.fileinfo', data => {
		console.log('get existed file ', data)
    sendToProperty({
      'action' : 'existing_files',
      'file': data.params.payload.reviewResult
    });
  })
  
	AVT_CREATOR_CENTRAL.on('ax.update.sound.output.list', data => {
    sendToProperty({
      'action' : 'send_devices_val',
      'sound_devices': data.params.payload.devices
    });
  })
 
	AVT_CREATOR_CENTRAL.on('ax.update.select.file.name', data => {
    sendToProperty({
      'action' : 'send_file_val',
      'file': data.params.payload
    });
  })


})

// connectCreatorCentral(8765, 'my-uuid', 'ax.register.property')