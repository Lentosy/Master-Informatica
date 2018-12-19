//kurt.vanwynsberge@ugent.be, 20110203	

/*
 * function printit(style){
	
	window.print();
	setTimeout("$('link[media*=\"screen\"]').attr(\"href\",style);",500);

	//$('link[media*="screen"]').attr("href",url+"css/print/default.css");
	//$('link[media*="screen"]').attr("href",style);
	//window.location.reload(); //restore style
	
	return false;
}
*/

function printthis(body,script){
	
	content = "<html>" + body;  // + "</html>";
	content +="</html>";
	

	
	w = window.open(script, "printwindow", "location=1,status=1,scrollbars=1,width=800,height=600");	
	w.document.write(content);
	
		$(w.document).ready(function($) {
			setTimeout("w.print();",1000);
				//	w.document.body.onload=$(this).print();
				//bodyhtml = w.$("html").html();
				//bodyhtml=bodyhtml.replace(/<body /gi, "<body onload='javascript:window.print();' ");
				//bodyhtml = bodyhtml.replace(/css(?:\S*)default.css/g, "css/print/default.css");
				//w.$("html").html( bodyhtml);
				//w.print();
		});
	

}

function printme(url,script){

    //alternative
    if ($('div.fc-button-month').length){
        //agenda
	 				style = $('link[media*="screen"]').attr("href");
	 				$('#calendar').css('width', '18cm');
				    $('.fc-content .fc-state-highlight').css('background', '#dddddd');
				    $('#calendar').fullCalendar('render');
				    $('input[type=button]').css('display', 'none');
				    $('#header1').css('display', 'none');
				    $('.fc-header-left').css('display', 'none');
				    $('.fc-header-right').css('display', 'none');
					$('.fc-event-time').css('font-size', '0.75em');
				    $('.fc-event-title').css('font-size', '0.75em');
				    
				    bodyhtml = window.document.body.innerHTML;
					bodyhtml = "<html>" + $("html").html() + "</html>";
        // start = '<!--startcalprint-->';
        // einde = '<!--endprint-->';
        // printhtml = bodyhtml.substr(bodyhtml.lastIndexOf(start) + 20);
        // printhtml = printhtml.substring(0, printhtml.indexOf(einde));
        // printhtml = "<html>" + printhtml + "</html>";
				    // window.document.body.innerHTML = printhtml;
        // commented this out: doesn't seem to work for some reason..
        
        printthis(bodyhtml,script);
    }
    else{
        //gewone pagina
        bodyhtml = "<html>" + $("html").html() + "</html>";
        bodyhtml = bodyhtml.replace(/css(?:\S*)default.css/g, "css/print/default.css");
        printthis(bodyhtml,script);
	 			}	
}

function print_cal(button1,button2,button3) {
					
		var buttonOpts = {};
		buttonOpts[button1] = function () {
			    
			    $(this).dialog('close');
				$('#calendar').css('width', '18cm');
			    $('.fc-content .fc-state-highlight').css('background', '#dddddd');
			    $('#calendar').fullCalendar('render');
			    $('input[type=button]').css('display', 'none');
			    $('#header1').css('display', 'none');
			    $('.fc-header-left').css('display', 'none');
			    $('.fc-header-right').css('display', 'none');
				$('.fc-event-time').css('font-size', '0.75em');
			    $('.fc-event-title').css('font-size', '0.75em');
			    
			    bodyhtml = window.document.body.innerHTML;
			    start = '<!--startcalprint-->';
			    einde = '<!--endprint-->';
			    printhtml = bodyhtml.substr(bodyhtml.lastIndexOf(start) + 20);
			    printhtml = printhtml.substring(0, printhtml.indexOf(einde));
			    window.document.body.innerHTML = printhtml;
		};
		
		buttonOpts[button2] = function () {
			   
			    $(this).dialog('close');
				$('#calendar').css('width', '18cm');
			    $('.fc-content .fc-state-highlight').css('background', '#dddddd');
			    $('#calendar').fullCalendar('render');
			    $('input[type=button]').css('display', 'none');
			    $('#header1').css('display', 'none');
			    $('.fc-header-left').css('display', 'none');
			    $('.fc-header-right').css('display', 'none');
				$('.fc-event-time').css('font-size', '0.75em');
			    $('.fc-event-title').css('font-size', '0.75em');
			    
			    bodyhtml = window.document.body.innerHTML;
			    start = '<!--startcalprint-->';
			    einde = '<!--endprint-->';
			    printhtml = bodyhtml.substr(bodyhtml.indexOf(start) + 17);
			    printhtml = printhtml.substring(0, printhtml.indexOf(einde));
			    window.document.body.innerHTML = printhtml;
			    window.print();
			    
		};
		
		buttonOpts[button3] = function () {
		   	 	$(this).dialog('close');
		};

		$('#dialog').dialog({
		    title: 'Info',
		    resizable: false,
		    height: 180,
		    width:400,
		    modal: true,
		    buttons: buttonOpts
		});
}