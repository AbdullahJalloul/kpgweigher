function getreporttblst()
{
	return document.reportform.tbselect;
}
function addreportlist()
{
	var lstctl = getreporttblst();
	var lstdata="@@reportlst@@";
	var lstarray = lstdata.split(',');//seperate by ','
	lstctl.length = lstarray.length-1;//ignore the last ,
	var index=0;
	for (index=0;index< lstctl.length;index++){
		lstctl[index].value=lstarray[index];
		lstctl[index].text=lstarray[index];
	}
	lstctl.value = "@@reportsz@@";

}
function exitReportform()
{
	return true;
}
function loadReportform()
{
	if(document.tbrform.curview.value == 'reporthtm'){
		addreportlist();
		var myid = document.getElementById('ReportBrowser');
		myid.Navigate('@@reporturl@@');
		if (GetCookie('showreporttb') == 'true')
			reportpopUp();	
	}
}

function reportsubmit(choice)
{
	//check the validaty first
	var tbsel=getreporttblst();
	var myid = document.getElementById('ReportBrowser');
	
	if(choice == 'tbcancel')
		return;
	if(choice == 'tbupdate')
	{	//reportsave
		document.reportform.cmdtype.value='report_update';
		document.reportform.reportsz.value=tbsel.value;
		document.reportform.submit();
		return;
	}
	if(choice == 'tbsavenew')
	{	//reportsave
		document.reportform.cmdtype.value='report_savenew';
		document.reportform.reportsz.value=tbsel.value;
		document.reportform.submit();
		return;
	}	
	if(choice == 'tbprint')
	{	//report print		
		document.reportform.cmdtype.value='report_print';
		document.reportform.submit();
		return;
	}	
	//regselect
	if(tbsel.value == '')		return;
	var lstdata="@@reportlst@@";
	if(lstdata.search(tbsel.value) >= 0)
	{
//		var myid = document.getElementById('ReportBrowser');
//		myid.Navigate('about:blank');
//		return;
		document.reportform.cmdtype.value='report_select';
		document.reportform.reportsz.value=tbsel.value;
		document.reportform.submit();
		return;
	}
}
function reportpopUp(distype)
{
    var tb1 = document.getElementById('reportitems');
    if(tb1.style.display == '')
    {
    	tb1.style.display = 'none';
    	SetCookie('showreporttb','false');
    }
    else
    {
	tb1.style.display = '';
	SetCookie('showreporttb','true');
    }	
}
document.writeln("<form name='reportform' method='POST' action='ToHtmlCtrl'>  ");
document.writeln("<table border='0' background='texture.jpg'><tr><td>");
document.writeln("<div id='reporttbdiv' style='position:absolute;width:100; color: #8C6D5A; zindex:0'>");
document.writeln("	 <input type='hidden' name='reportsz'>");
document.writeln("       <input type='hidden' name='cmdtype'><input type='hidden' name='oldpara'>");
document.writeln("	 <input type='hidden' name='para'><input type='hidden' name='otherpara'>");
document.writeln("       <table id='reportitems' style='' border = '0'  width='100' cellspacing='0' >  ");
document.writeln("       <tr><td>");
document.writeln("<a href=# ><img name='reportImage2' onClick='reportpopUp()' value='tbcancel' src='imgorg/pinon.gif' width='20' height='18' ></a>");
document.writeln("      </td>");
document.writeln(" 	<td ><select name='tbselect' onchange=reportsubmit('tbselect')></select></td>  ");
document.writeln("		<td ><font color='green'>|</font></td>  ");
document.writeln("		<td ><button type='button' onclick=reportsubmit('tbsavenew')>����Ϊ..</td>  ");
document.writeln("		<td ><font color='green'>|</font></td>  ");
document.writeln("		<td ><button type='button' onclick=reportsubmit('tbprint')>��ӡ����</td>  ");
document.writeln("		<td ><font color='green'>|</font></td>  ");
document.writeln("		</tr></table></div>");
document.writeln("<img name='reportImagel' onClick='reportpopUp()' src='imgorg/pinon.gif' width='20' height='18' >");
document.writeln("</td></tr><tr><td>");
document.writeln("<object classid='clsid:8856F961-340A-11D0-A96B-00C04FD705A2' id='ReportBrowser' width='655' height='500'>");
document.writeln("  <param name='ExtentX' value='7938'>");
document.writeln("  <param name='ExtentY' value='3969'>");
document.writeln("  <param name='ViewMode' value='0'>");
document.writeln("  <param name='Offline' value='1'>");
document.writeln("  <param name='Silent' value='0'>");
document.writeln("  <param name='RegisterAsBrowser' value='0'>");
document.writeln("  <param name='RegisterAsDropTarget' value='1'>");
document.writeln("  <param name='AutoArrange' value='0'>");
document.writeln("  <param name='NoClientEdge' value='0'>  <param name='AlignLeft' value='0'>");
document.writeln("  <param name='NoWebView' value='0'>");
document.writeln("  <param name='HideFileNames' value='0'>");
document.writeln("  <param name='SingleClick' value='0'>  <param name='SingleSelection' value='0'>");
document.writeln("  <param name='NoFolders' value='0'>");
document.writeln("  <param name='Transparent' value='0'>");
document.writeln("  <param name='ViewID' value='{0057D0E0-3573-11CF-AE69-08002B2E1262}'>");
document.writeln("  <param name='Location' value='@@reporturl@@'>");
document.writeln("</object>");
document.writeln("      </td></tr></table> ");
document.writeln("      </form>");
