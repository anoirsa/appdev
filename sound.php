<?php
$log_file = 'textcurl.txt';
$values = $_POST['db'];

$str = date("M d Y H :i:s",time()).' '.$values."\n";


//now we open the file


if(file_exists($log_file)) {
	$fp=fopen($log_file,a);   // the file is opened as append mode
	fwrite($fp , $str);
	fclose($fp);
	
}else {   // if the file doesn't exist .. open a new one 
	$fp = fopen($log_file,w);
	fwrite($fp,$str);
	fclose($fp);
	
}
