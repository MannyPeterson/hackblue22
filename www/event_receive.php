
<?php


if(!isset($_GET['cid'])) {
	echo "E1";
	exit;
}


if(!isset($_GET['pid'])) {
	echo "E2";
	exit;
}


if(!isset($_GET['sn'])) {
	echo "E3";
	exit;
}


if(!isset($_GET['tmp'])) {
	echo "E4";
	exit;
}


$cid = $_GET['cid'];

if(strlen($cid) < 1 && strlen($cid) > 64) {
	echo "E5";
	exit;
}

$pid = $_GET['pid'];

if(strlen($pid) < 1 && strlen($pid) > 32) {
	echo "E6";
	exit;
}

$sn = $_GET['sn'];

if(strlen($sn) < 1 && strlen($sn) > 32) {
	echo "E7";
	exit;
}

$tmp = $_GET['tmp'];

if(strlen($tmp) < 1 && strlen($tmp) > 32) {
	echo "E8";
	exit;
}

if(!is_numeric($tmp)) {
	echo "E9";
	exit;
}


$conn = new mysqli('127.0.0.1:3306', 'hackblue22', 'fuzzer', 'hackblue22');
if($conn->connect_error ) {
	echo "E10";
	exit;
}


$sql = "INSERT INTO events (customer_id, product_id, serial_no, temperature, created) VALUES ('" . $cid . "', '" . $pid .  "', '" . $sn . "', '" . $tmp . "', CURRENT_TIME())";


if($conn->query($sql) != TRUE) {
	echo "E11";
	$conn->close();
	exit;
} 

$conn->close();

echo "OK";


exit;

?>