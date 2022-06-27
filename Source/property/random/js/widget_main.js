
const sendToProperty = AVT_CREATOR_CENTRAL_API.sendToProperty;
const setImage = AVT_CREATOR_CENTRAL_API.setImage;

const widgetEvents = new EventEmitter();
AVT_CREATOR_CENTRAL.on('ax.property.connected', widget_main)
AVT_CREATOR_CENTRAL.on('ax.send.to.widget', recv_from_property);
// AVT_CREATOR_CENTRAL.on('ax.widget.triggered', widget_triggered);

function widget_main() {
  console.log('widget_main...');
  drawString('widget_main: property connected!')
} 

function recv_from_property(data) {
	if(data.params.payload.hasOwnProperty('action')) {
    let action = data.params.payload.action;
    widgetEvents.emit(action, data.params.payload);
  } else {
    console.log('unknown action: ', data)
    drawString('Unknown widget action!')
  }
}

widgetEvents.on('get_select_option', get_select_option)
widgetEvents.on('get_radio_option', get_select_option)
function get_select_option(data) {
	console.log('get_option:', data.option_val)
  drawString('get_option: ' + data.option_val)
}

widgetEvents.on('on_button_clicked', data => {
	console.log('btn_clicked:', data.button_id)
  drawString('btn_clicked: ' + data.button_id)
})

widgetEvents.on('on_checkbox_clicked', data => {
	console.log('checkbox_id:', data.checkbox_id+ ', checked:' + data.checked)
  drawString('chckbox_id: ' + data.checkbox_id+ ', checked:' + data.checked)
})

widgetEvents.on('on_texteditor_changed', data => {
	console.log('texteditor_id:', data.texteditor_id + ', text:' + data.text_content)
  drawString('texteditor_id: ' + data.texteditor_id + ', text:' + data.text_content)
})


function drawString(str) {
  let canvas = document.getElementById('canvas');
  let ctx = canvas.getContext("2d");
  ctx.clearRect(0, 0, canvas.width, canvas.height);

  ctx.width = canvas.width
  ctx.height = canvas.height
  ctx.beginPath();
  
  ctx.fillStyle = "#040000";
  ctx.font = "20px Arial-Rounded-MT-Bold";
  ctx.fillStyle = "#040000";
  ctx.fillRect(0, 0, 308, 108);
  
  let str_width = ctx.measureText(str).width;
  ctx.fillStyle = "#FFFFFF";
  ctx.fillText(str, (ctx.width/2)-(str_width/2), 75);
  setImage(canvas.toDataURL('image/png', 1))
}

// function widget_triggered(data) {
//   drawString('setting: ' + 'widget_trigger!')
// }


//Debug 
$(() => {

  //設定　ComboBox 全部內容
  $('#trigger_set_amy_item').click(e => {
    sendToProperty({
			"action": "set_select_item",
			"select_button_1": {
				"id": "btnWarning",
				"src": "images/component_btn_addnew_block_nc_m.svg"
			},
			"select_button_2": {
				"id": "btnWarning2",
				"src": "images/component_btn_addnew_block_nc_m.svg"
			},
			"select_name": {
				"id": "Voice",
				"name": "Voice"
			},
			"select_options": {
				"id": "SelectVoice",
				"options": []
			}
    })
  });


  //設定　ComboBox 全部內容
  $('#trigger_set_select_1_item').click(e => {
    sendToProperty({
      'action' : 'set_select_item',
      'select_name': {
        'id': 'select_1_name',
        'name': '選單-1'
      },
      'select_options': {
        'id': 'select_1_options',
        // 'default_value': 'select-1-value-5',
        'options': [
          {'value': 'select-1-value-1', 'name': '選單-1-選項-1'},
          {'value': 'select-1-value-2', 'name': '選單-1-選項-2'},
          {'value': 'select-1-value-3', 'name': '選單-1-選項-3'},
          {'value': 'select-1-value-4', 'name': '選單-1-選項-4'},
        ]
      }
    })
  });

  //設定目前　ComboBox 內容 = select-1-value-2
  $('#trigger_set_select_1_value_2').click(e => {
    sendToProperty({
      'action' : 'set_select_option',
      'option_id': 'select_1_options',
      'option_val':  'select-1-value-2'
    })  
  });

  //設定目前　ComboBox 內容 = select-1-value-4
  $('#trigger_set_select_1_value_4').click(e => {
    sendToProperty({
      'action' : 'set_select_option',
      'option_id': 'select_1_options',
      'option_val':  'select-1-value-4'
    })  
  });

  //從 Widget 去取得　Property　ComboBox 的內容
  $('#trigger_get_select_1_value').click(e => {
    sendToProperty({
      'action' : 'get_select_option',
      'option_id': 'select_1_options',
    })
  });


  //設定　ComboBox 全部內容
  $('#trigger_set_select_2_item').click(e => {
    sendToProperty({
      'action' : 'set_select_item',
      'select_name': {
        'id': 'select_2_name',
        'name': '選單/按鈕-2'
      },
      'select_options': {
        'id': 'select_2_options',
        // 'disabled': true,  
        'placeholder': 'Please select an option',
        'options': [
          {'value': 'select-2-value-1', 'name': '選單-2-選項-1'},
          {'value': 'select-2-value-2', 'name': '選單-2-選項-2'},
          {'value': 'select-2-value-3', 'name': '選單-2-選項-3'},
          {'value': 'select-2-value-4', 'name': '選單-2-選項-4'},
        ]  
      },
      'select_button_1': {
        'id': 'select_2_button_1',
        'src': 'images/component_btn_addnew_block_nc_m.svg',
      },
      'select_button_2': {
        'id': 'select_2_button_2',
        'src': 'images/component_btn_refresh_block_nc_m.svg',
        // 'visibility': 'hidden', // [show or hidden]
      },      
    })
  });


  //設定　ComboBox 全部內容
  $('#trigger_set_select_3_item').click(e => {
    sendToProperty({
      'action' : 'set_select_item',
      'select_name': {
        'id': 'select_3_name',
        'name': '選單/按鈕-3'
      },
      'select_options': {
        'id': 'select_3_options',
        'options': [
          {'value': 'select-3-value-1', 'name': '選單-3-選項-1'},
          {'value': 'select-3-value-2', 'name': '選單-3-選項-2'},
          {'value': 'select-3-value-3', 'name': '選單-3-選項-3'},
          {'value': 'select-3-value-4', 'name': '選單-3-選項-4'},
        ]  
      },
      'select_button_1': {
        'id': 'select_3_button_1',
        'src': 'images/component_btn_addnew_block_nc_m.svg',
      },
    })
  });

  //設定 Radio-1　
  $('#trigger_set_radio_button_1').click(e => {
    sendToProperty({
      'action' : 'set_radio_button',
      'radio_name': {
        'id': 'radio_1_name',
        'name': 'Radio選單-1'
      },
      'radio_options': {
        'id': 'radio_1_options',
        'default_value': 'radio-1-value-2',
        // 'disabled': true,
        'options': [
          {'value': 'radio-1-value-1', 'name': '選項1'},
          {'value': 'radio-1-value-2', 'name': '選項2'},
        ]
      }
    });
  });

  //設定 Radio-2 
  $('#trigger_set_radio_button_2').click(e => {
    sendToProperty({
      'action' : 'set_radio_button',
      'radio_name': {
        'id': 'radio_2_name',
        'name': 'Radio選單-2'
      },
      'radio_options': {
        'id': 'radio_2_options',
        'default_value': 'radio-2-value-2',
        'options': [
          {'value': 'radio-2-value-1', 'name': '選項1'},
          {'value': 'radio-2-value-2', 'name': '選項2'},
          {'value': 'radio-2-value-3', 'name': '選項3'},
        ]
      }
    });
  });

  //設定 label1 　
  $('#trigger_set_lable_1_item').click(e => {
    sendToProperty({
      'action' : 'set_lable_item',
      'label_name': {
        'id': 'label_1_name',
        'name': 'Label-1 Name',
      }
    });
  });

  //設定　Label2  align + color +size
  $('#trigger_set_lable_2_item').click(e => {
    sendToProperty({
      'action' : 'set_lable_item',
      'align': 'right', 
      'label_name': {
        'id': 'label_2_name',
        'name': 'Label-2 Name',
        'font_size': '3px',
        'color': 'yellow', 
      },
      'label_button_1': {
        'id': 'label_2_button_1',
        'src': 'images/component_btn_addnew_block_nc_m.svg',
      },      
    });
  });

  //設定 label3 + button
  $('#trigger_set_lable_3_item').click(e => {
    sendToProperty({
      'action' : 'set_lable_item',
      'align': 'right', 
      'label_name': {
        'id': 'label_3_name',
        'name': 'Label-3 Name',
      },
      'label_button_1': {
        'id': 'label_3_button_1',
        'src': 'images/component_btn_addnew_block_nc_m.svg',
      },
      'label_button_2': {
        'id': 'label_3_button_2',
        'src': 'images/component_btn_addnew_block_nc_m.svg',
      }      
    });
  });

  //設定 Button-1
  $('#trigger_set_button_1').click(e => {
    sendToProperty({
      'action' : 'set_button',
      'align': 'center', 
      'button_1': {
        'id': 'button_1_1',
        'name': 'Button-1_1',
      }
    });
  });

  //設定 Button-2
  $('#trigger_set_button_2').click(e => {
    sendToProperty({
      'action' : 'set_button',
      'align': 'left', 
      'button_1': {
        'id': 'button_2_1',
        'name': 'Button-2_1',
      },     
      'button_2': {
        'id': 'button_2_2',
        'name': 'Button-2_2',
      },        
    });
  });

  //設定 Button-3
  $('#trigger_set_button_3').click(e => {
    sendToProperty({
      'action' : 'set_button',
      'align': 'right', 
      'button_1': {
        'id': 'button_3_1',
        'name': 'Button-3_1',
      }
    });
  });


  //設定 Checkbox-1
  $('#trigger_set_checkbox_1').click(e => {
    sendToProperty({
      'action' : 'set_checkbox',
      'checkbox': {
        'id': 'checkbox_1',
        'name': 'AVT checkbox-2',
        'checked': false,
        'disabled': true,
      }
    });
  });

  //設定 Text Edirot-1
  $('#trigger_set_texteditor_1').click(e => {
    sendToProperty({
      'action' : 'set_texteditor',
      'label_name': {
        'id': 'texteditor_1_name',
        'name': 'Text Editor - 1',
      },      
      'texteditor': {
        'id': 'texteditor_1',
      }
    });
  });

})

connectCreatorCentral(8765, 'my-uuid', 'ax.register.widget')
