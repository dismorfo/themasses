var Micro=Y.namespace("Template.Micro");Micro.options={code:/<%([\s\S]+?)%>/g,escapedOutput:/<%=([\s\S]+?)%>/g,rawOutput:/<%==([\s\S]+?)%>/g,stringEscape:/\\|'|\r|\n|\t|\u2028|\u2029/g},Micro.compile=function(e,t){var n=[],r="\uffff",i="\ufffe",s;return t=Y.merge(Micro.options,t),s="var $t='"+e.replace(/\ufffe|\uffff/g,"").replace(t.rawOutput,function(e,t){return i+(n.push("'+\n("+t+")+\n'")-1)+r}).replace(t.escapedOutput,function(e,t){return i+(n.push("'+\n$e("+t+")+\n'")-1)+r}).replace(t.code,function(e,t){return i+(n.push("';\n"+t+"\n$t+='")-1)+r}).replace(t.stringEscape,"\\$&").replace(/\ufffe(\d+)\uffff/g,function(e,t){return n[parseInt(t,10)]}).replace(/\n\$t\+='';\n/g,"\n")+"';\nreturn $t;",t.precompile?"function (Y, $e, data) {\n"+s+"\n}":this.revive(new Function("Y","$e","data",s))},Micro.precompile=function(e,t){return t||(t={}),t.precompile=!0,this.compile(e,t)},Micro.render=function(e,t,n){return this.compile(e,n)(t)},Micro.revive=function(e){return function(t){return t||(t={}),e.call(t,Y,Y.Escape.html,t)}};
