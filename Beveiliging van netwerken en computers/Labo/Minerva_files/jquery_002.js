(function(c){c.fn.glossary=function(b,d){d=c.extend({ignorecase:!1,tiptag:"h6",excludetags:[],linktarget:"_blank",showonce:!1},d);var g=1;return this.each(function(l,p){c.each(d.excludetags,function(a,f){d.excludetags[a]=f.toUpperCase()});var m=function(a,f,b,k){var h=f,e=0;if(3==a.nodeType){var j=d.ignorecase?a.data.toLowerCase().indexOf(h.toLowerCase()):a.data.indexOf(h);0<=j&&!(-1<jQuery.inArray(c(a).parent().get(0).tagName,d.excludetags))&&(e=document.createElement("a"),e.className="glossaryTerm",
"0"==b?(e.id="glossaryID"+g,e.href="#",e.title="Click for '"+f+"' definition",e.className="glossaryTerm",c(e).click(function(a){c.glossaryTip("<"+d.tiptag+">"+f+"</"+d.tiptag+"><p>"+k+"</p>",{mouse_event:a});return!1})):"1"==b?(e.title="Click to look up '"+f+"' in Wikipedia",f=f.replace(/ /g,"_"),e.href="http://en.wikipedia.org/wiki/"+f,e.target=d.linktarget):"2"==b?(e.title="Click to search for '"+f+"' in Google",f=f.replace(/ /g,"+"),e.href="http://www.google.co.uk/search?q="+f,e.target=d.linktarget):
"3"==b&&(e.title="Click to view '"+f+"' definition",e.href=k,e.target=d.linktarget),a=a.splitText(j),a.splitText(h.length),b=a.cloneNode(!0),e.appendChild(b),a.parentNode.replaceChild(e,a),e=1,g+=1)}else if(1==a.nodeType&&a.childNodes&&!/(script|style)/i.test(a.tagName))for(h=0;h<a.childNodes.length;++h)j=m(a.childNodes[h],f,b,k),d.showonce&&1==j?(h=a.childNodes.length,e=1):h+=j;return e};c.ajax({type:"GET",url:b,dataType:"json",success:function(a){if(a)for(var b=a.length,d=0;d<b;d++){var c=a[d];
m(p,c.term,c.type,c.definition)}},error:function(){}})})};var b=function(){};c.extend(b.prototype,{setup:function(){c("#glossaryTip").length&&c("#glossaryTip").remove();b.holder=c('<div id="glossaryTip" style="max-width:260px;"><div id="glossaryClose"></div></div>');b.content=c('<div id="glossaryContent"></div>');c("body").append(b.holder.append(b.content))},show:function(c,d){b.content.html(c);var g=parseInt(d.mouse_event.pageX)+15,l=parseInt(d.mouse_event.pageY)+5;b.holder.css({top:l,left:g});b.holder.is(":hidden")&&
b.holder.show();b.holder.bind("click",function(){b.holder.stop(!0).fadeOut(200);return!1})}});c.glossaryTip=function(n,d){var g=c.glossaryTip.instance;g||(g=c.glossaryTip.instance=new b);g.setup();g.show(n,d);return g}})(jQuery);