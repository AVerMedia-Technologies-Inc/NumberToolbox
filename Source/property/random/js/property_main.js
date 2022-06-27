const setWidgetSettings = AVT_CREATOR_CENTRAL_API.setWidgetSettings;
const getWidgetSettings = AVT_CREATOR_CENTRAL_API.getWidgetSettings;
const setPackageSettings = AVT_CREATOR_CENTRAL_API.setPackageSettings;
const getPackageSettings = AVT_CREATOR_CENTRAL_API.getPackageSettings;
const changeTitle = AVT_CREATOR_CENTRAL_API.changeTitle;
const changeImage = AVT_CREATOR_CENTRAL_API.changeImage;
const changeState = AVT_CREATOR_CENTRAL_API.changeState;
const sendToPropertyView = AVT_CREATOR_CENTRAL_API.sendToPropertyView;

const propertyEvents = new EventEmitter();
AVT_CREATOR_CENTRAL.on('sendToPropertyView', receive_from_widget);
AVT_CREATOR_CENTRAL.on('connected', property_main);
AVT_CREATOR_CENTRAL.on('didReceiveWidgetSettings', data => {
	//debugLog(data);
});
AVT_CREATOR_CENTRAL.on('didReceivePackageSettings', data => {
	//debugLog(data)
});
// AVT_CREATOR_CENTRAL.on('keyDown', data => {debugLog(data)});
// AVT_CREATOR_CENTRAL.on('keyUp', data => {debugLog(data)});
// AVT_CREATOR_CENTRAL.on('widgetTriggered', data => {debugLog(data)});
// AVT_CREATOR_CENTRAL.on('widgetWillAppear', data => {debugLog(data)});
// AVT_CREATOR_CENTRAL.on('widgetWillDisappear', data => {debugLog(data)});
// AVT_CREATOR_CENTRAL.on('propertyViewDidAppear', data => {debugLog(data)});
// AVT_CREATOR_CENTRAL.on('propertyViewDidDisappear', data => {debugLog(data)});
// AVT_CREATOR_CENTRAL.on('sendToPackage', data => {debugLog(data)});

let saveData = [];

function setSaveData(idKey, id, data) {
	let hasKey = false;
	for (const i in saveData) {
		if (Object.hasOwnProperty.call(saveData[i], idKey) && saveData[i][idKey] === id) {
			saveData[i] = data;
			hasKey = true;
		}
	}
	if(!hasKey) {
		saveData.push(data);
	}
	
	setWidgetSettings({
		'saveData' : saveData
	});
}

function getSaveData(idKey, id) {
	let result;
	for (const i in saveData) {
		if (Object.hasOwnProperty.call(saveData[i], idKey) && saveData[i][idKey] === id) {
			result = saveData[i];
		}
	}

	return result;
}

function property_main(data) {
	console.log('property_main........');	
}

function receive_from_widget(data) {
	if(data.payload.hasOwnProperty('action')) {
		let action = data.payload.action;
		propertyEvents.emit(action, data.payload);
	} else {
		console.log('unknown action: ', data)
	}
}

propertyEvents.on('set_number', data => {
	$('#' + data.label_name.id).text(data.label_name.name);
	let numberEditor = $('#' + data.number.id + ' > input');
	let oldVal = "";
	let defaultData = {
		'action' : 'on_number_editor_changed',
		'number_id': data.number.id,
		'text_content' : 0
	};
	if(data.hasOwnProperty('default_value')) {
		numberEditor.val(data.default_value);
		defaultData['text_content'] = data.default_value;
		//alert('text_content:'+data.default_value)
	}
	setSaveData('number_id', data.number.id, defaultData);
	
	numberEditor.on("change keyup paste", function() {
			let currentVal = $(numberEditor).val();
			if(currentVal == oldVal) {
					return; //check to prevent multiple simultaneous triggers
			}
			oldVal = currentVal;
			console.log("changed!");
			
			setSaveData('number_id', data.number.id, {
				'action' : 'on_number_editor_changed',
				'number_id': data.number.id,
				'text_content': Number(currentVal), 				
			});

	});
})
// connectCreatorCentral(8765, 'my-uuid', 'ax.register.property')
