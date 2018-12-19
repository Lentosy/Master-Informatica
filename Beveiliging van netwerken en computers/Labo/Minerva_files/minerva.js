$(function() {
	// annotation button
	$('.annotation-button').click(function(){
		id = parseInt($(this).attr('data-video-id'));
		title = $(this).attr('data-video-title');
		position = jwplayer(id).getPosition();
		min = Math.floor(position/60);
		sec = Math.floor(position%60);
		str = title + ' [' + min + 'min ' + sec + 'sec] : ';
		if(CKEDITOR.instances['feedback_content'].getData()){
			CKEDITOR.instances['feedback_content'].insertText('\n\r');
		}
		CKEDITOR.instances['feedback_content'].insertText(str);
		jwplayer(id).pause();
	});

	// show or hide a plugin
	$(".pluginshow, .pluginhide").click(function(){

		// the id of the menusection
		var plugin_id = $(this).parent().attr("id");

		// the id of the icon the user clicked on
		var icon_id = $(this).attr("id");

		// getting the action and the plugin from the id of the icon
		var actionpluginarray = icon_id.split("_");
		var action = actionpluginarray[0];
		var plugin = actionpluginarray[1];

		// toggle the + and - icon
		$("#" + plugin_id +" .pluginshow").toggle();
		$("#" + plugin_id +" .pluginhide").toggle();

		// toggle the content
		$("#" + plugin_id +" .menusectioncontent").toggle();



		// store the user-setting
		$.get(api_get_path('WEB_CODE_PATH') + "ajaxHandler.php", { action: action, plugin: plugin },
		  function(data){
				//$("#confidentiallity_"+dissertation_document_id).parent().html(data);
		});

	});

	// show or hide a plugin
	$(".pluginremove").click(function(){

		// the id of the icon the user clicked on
		var icon_id = $(this).attr("id");

		// getting the action and the plugin from the id of the icon
		var actionpluginarray = icon_id.split("_");
		var action = actionpluginarray[0];
		var plugin = actionpluginarray[1];


		// remove the plugin
		$("#plugin_" + plugin).remove();


		// store the user-setting
		$.get(api_get_path('WEB_CODE_PATH') + "ajaxHandler.php", { action: action, plugin: plugin },
		  function(data){
				//$("#confidentiallity_"+dissertation_document_id).parent().html(data);
		});

	});

	// sortable table: select a row in a sortable table
	$('.sortabletable_checkbox').click(function(){
		$(this).parents('tr').toggleClass('row_selected');
	});

	// sortable table: indicate a column in the sortable table as sortable
	// disabled when including datatables js.
	$('table.display:not(.dataTable) th:not(.sorting) > a').append('<span class="sortableicon right ui-icon ui-icon-carat-2-n-s"></span>');

	// sortable table: give first column the class firstcolumn
	$('table.display tr').find('td:first').addClass('firstcolumn');

	// sortable table: give last column the class lastcolumn
	$('table.display tr').find('td:last').addClass('lastcolumn');

	// sortable table: give the first row a class firstrow
	$('table.display tr:first-child').addClass('firstrow');

	// sortable table: give the first row a class firstrow
	$('table.display tr:last-child').addClass('lastrow');

    // sortable table: give the first row a class firstrow
    $('table.display tr:even').addClass('even');

    // sortable table: give the first row a class firstrow
    $('table.display tr:odd').addClass('odd');

    // toggle subactions
	$('.hassubactions').on('click', function(){
		var subaction_id = $(this).attr('id');
		$('#'+subaction_id+'_subactions').slideToggle('slow');
	});

	// shortened items
	$('.short').hover(function(){
		$('span.short_more', this).toggle();
		$('span.short_rest', this).toggle();
	});



	// size of form elements should respect the size attribute
	$('input[size]').filter(':text').each(function(){
		var existingstyle = $(this).attr('style');
		if (existingstyle == undefined){
			existingstyle = '';
		}

		if ($(this).attr('size') > 0) {
			$(this).attr('style',existingstyle + 'width:'+(20+$(this).attr('size')*11)+'px;');
		}
	});
	$('input[size]').filter(':password').each(function(){
		var existingstyle = $(this).attr('style');
		if (existingstyle == undefined){
			existingstyle = '';
		}

		if ($(this).attr('size') > 0) {
			$(this).attr('style',existingstyle + 'width:'+(20+$(this).attr('size')*11)+'px;');
		}
	});


	$('div#user ul li:last').addClass('last-child');

	// Announcements
	$("#ann_use_sticky").on("change", function(){
		if ($(this).is(":checked")){
			$("#ann_sticky_until").show();
		} else {
			$("#ann_sticky_until").hide();
		}
	});
});


function unlockmultipleactions(elementname){
	// unlock the multiple actions dropdown if at least one checkbox of the sortable table is checked
	if ($("input[name='"+elementname+"']:checked").length > 0){
		$("#multiple_actions").removeAttr("disabled");
		$("#multiple_actions_submit").removeAttr("disabled");
	} else {
		// lock the multiple actions dropdown if no checkbox of the sortable table is checked
		$("#multiple_actions").attr("disabled", "disabled");
		$("#multiple_actions_submit").attr("disabled", "disabled");
		$('input[name=select_all_none_actions]').prop('checked',false);
		$('input[name=select_all_none_actions_top]').prop('checked',false);
	}

	// if at least one checkbox of the sortable table is unchecked we no longer can check the "select all" checkboxes on top and at the bottom of the sortable table
	if ($("input[name='"+elementname+"']:enabled:not(:checked)").length > 0){
		$('input[name=select_all_none_actions_top]').prop('checked',false).removeClass('sortabletable_checkbox_checked').parent('label').removeClass('sortabletable_checkbox_checked');
		$('input[name=select_all_none_actions]').prop('checked',false).removeClass('sortabletable_checkbox_checked').parent('label').removeClass('multiple_actions_checkbox_checked');
	}
}

function select_all_none(master, individual){
	// checked or unchecked
	var value = $("input[name='"+master+"']").prop("checked");
	if (value == true){
		$("input[name='"+individual+"']:enabled").prop('checked',true).addClass('sortabletable_checkbox_checked').parent('label').addClass('sortabletable_checkbox_checked');
		$("input[name='"+individual+"']:enabled").parents('tr').addClass('row_selected');
		// check the upper or lower selectall/selectnone checkbox accordingly
		// in sortable table the action can come from the top or bottom checkbox
		if (master == 'select_all_none_actions') {
			$('input[name=select_all_none_actions_top]').prop('checked',true).addClass('sortabletable_checkbox_checked').parent('label').addClass('sortabletable_checkbox_checked');
		} else {
			$('input[name=select_all_none_actions]').prop('checked',true).addClass('sortabletable_checkbox_checked').parent('label').addClass('multiple_actions_checkbox_checked');
		}
	} else {
		$("input[name='"+individual+"']").prop('checked',false).removeClass('sortabletable_checkbox_checked').parent('label').removeClass('sortabletable_checkbox_checked');
		$("input[name='"+individual+"']:enabled").parents('tr').removeClass('row_selected');
		// check the upper or lower selectall/selectnone checkbox accordingly
		// in sortable table the action can come from the top or bottom checkbox
		if (master == 'select_all_none_actions') {
			$('input[name=select_all_none_actions_top]').prop('checked',false).removeClass('sortabletable_checkbox_checked').parent('label').removeClass('sortabletable_checkbox_checked');
		} else {
			$('input[name=select_all_none_actions]').prop('checked',false).removeClass('sortabletable_checkbox_checked').parent('label').removeClass('multiple_actions_checkbox_checked');
		}
	}
	unlockmultipleactions(individual);
}

/*
 * fetch and display help-information from the help-site (here:http://icto.ugent.be)
 * @author William De Gryse <william.degryse@ugent.be>, Ghent University, Belgium
 * @version january 2017
 * @param page : page for which help-information is requested
 */

function getdoc(page){

    if (page!=""){

    	if (!document.getElementById("helpDialog")) {
            $("body").append("<div id='helpDialog'></div>");
            $("#helpDialog").append("<iframe id='iHelp' width=100% height=100% frameborder='0'>");
        }
        var winH = $(window).height() - 180;
        $("#helpDialog").dialog({height: winH, width: '80%'});

        document.getElementById("iHelp").src = api_get_path('WEB_CODE_PATH') + "inc/lib/helpDialog.php?documentation_url=" + page;
    }
}


function api_get_path(path_type, academic_year) {
    switch (path_type) {
        case 'WEB_PATH':
            return settings.WEB_PATH;
        case 'WEB_CODE_PATH':
            return settings.WEB_CODE_PATH;
        case 'WEB_HOMEPAGE_PATH':
            return settings.WEB_HOMEPAGE_PATH;
        case 'WEB_IMG_PATH':
            return settings.WEB_IMG_PATH;
        case 'WEB_PLUGIN_PATH':
            return settings.WEB_PLUGIN_PATH;
        case 'WEB_USERS_PATH':
            return settings.WEB_USERS_PATH;
        case 'JAVASCRIPT_PATH':
            return settings.JAVASCRIPT_PATH;
        case 'WEB_COURSE_PATH':
            if(typeof settings.WEB_COURSE_PATH == 'string') {
                return settings.WEB_COURSE_PATH;
            } else {
                var course_paths = settings.WEB_COURSE_PATH;
                return course_paths[academic_year];
            }
        default:
            return '';
    }
}


$(document).ready(function(){
	$('th.sortable').on('click', function(){
		var index = $(this).index();
		var row = 0;
		var content = new Array();

		// fill an array with all the values of table
		$(this).parents('table').find('tbody tr:not(.tablefooter)').each(function(){
			var column = 0;
			content[row] = new Array();
			$(this).find('td').each(function(){
				content[row][column] = $(this).html();
				column++;
			});
			row++;
		});

		// reverse sorting
		if ($(this).hasClass('reverse')){
			var reverse = 1;
		} else {
			var reverse = -1;
		}
		$(this).toggleClass('reverse');

		// sort the array according to the index
		content.sort(function (a, b) {
			return (a[index] == b[index]) ? 0 : ((a[index] > b[index]) ? reverse : -1 * reverse);
		});

		var counter = 0;
		$(this).parents('table').find('tbody tr:not(.tablefooter)').each(function(){
			$(this).html("<td>" + content[counter].join("</td><td>") + "</td>");
			counter++;
		});
	});
});

/* Changes for new corporate identity */
$(document).ready(function() {
	$('.bodyform-checkbox input[type=checkbox]').on('change', function(){
		//$(this).closest('.bodyform-checkbox').toggleClass('bodyform-checkbox-checked');
	});

	$('.bodyform-checkbox').on('click', function(){
		$(this).toggleClass('bodyform-checkbox-checked');
		var checkbox = $(this).find('input[type=checkbox]');
		checkbox.prop("checked",!checkbox.prop("checked")).change();
	});

	if($('#use_timewindow').is(':checked')){
		$('#use_timewindow').parents('.bodyform-checkbox').addClass('bodyform-checkbox-checked');
	}

	if($('#ann_use_sticky').is(':checked')){
		$('#ann_use_sticky').parents('.bodyform-checkbox').addClass('bodyform-checkbox-checked');
		$('#ann_sticky_until').show();
	}



	$('#content').on('change', 'input.multiple_actions_checkbox', function(){
		if ($(this).is(':checked')){
			$(this).addClass('multiple_actions_checkbox_checked').parent('label').addClass('multiple_actions_checkbox_checked');

		} else {
			$(this).removeClass('multiple_actions_checkbox_checked').parent('label').removeClass('multiple_actions_checkbox_checked');

		}
	});

	$('.sortabletable_checkbox').on('change', function(){
		if ($(this).is(':checked')){
			$(this).addClass('multiple_actions_checkbox_checked').parent('label').addClass('sortabletable_checkbox_checked');
		} else {
			$(this).removeClass('multiple_actions_checkbox_checked').parent('label').removeClass('sortabletable_checkbox_checked');
		}
	});


	/*****************************************************
	 *  Dropdown menu   		                         *
	 *****************************************************/
	$('.dropdown-toggle').on('click', function(){
		$(this).toggleClass('open');
	});


	$('#menutoggle').on('click', function(){
		$('#subbarul ul#main_navigation').toggle();
	});
});
