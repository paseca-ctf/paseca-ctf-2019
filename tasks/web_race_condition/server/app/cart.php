<?php
session_start();

if(!isset($_SESSION['id'])){
	exit();
}

$host = 'mysql';
$db   = 'paseca';
$user = 'root';
$pass = 'p4s3ca';
$charset = 'utf8';

$dsn = "mysql:host=$host;dbname=$db;charset=$charset";
$opt = [
	PDO::ATTR_ERRMODE            => PDO::ERRMODE_EXCEPTION,
	PDO::ATTR_DEFAULT_FETCH_MODE => PDO::FETCH_ASSOC,
	PDO::ATTR_EMULATE_PREPARES   => false,
];
$pdo = new PDO($dsn, $user, $pass, $opt);

if(isset($_POST['act']) && $_POST['act'] == 'buy' && isset($_POST['id'])){
	switch((int)$_POST['id']){
		case 0:
			$b = get_user_balance($_SESSION['id']);
			if($b['r'] >= 10){
				usleep(500000);
				$b['r'] -= 10;
				$b['db'] += 1;
				update_user_balance($_SESSION['id'], -10, 1);
				die('{"act": "buy", "status": "success", "r": '.$b['r'].', "db": '.$b['db'].'}');
			}
			die('{"act": "buy", "error": 2, "error_text": "Not enough balance"}');
			break;
		case 1:
			$b = get_user_balance($_SESSION['id']);
			if($b['db'] >= 1){
				usleep(500000);
				$b['db'] -= 1;
				$b['r'] += 10;
				update_user_balance($_SESSION['id'], 10, -1);
				die('{"act": "buy", "status": "success", "r": '.$b['r'].', "db": '.$b['db'].'}');
			}
			die('{"act": "buy", "error": 2, "error_text": "Not enough balance"}');
			break;
		case 2:
			$b = get_user_balance($_SESSION['id']);
			if($b['db'] >= 9){
				$b['db'] -= 9;
				update_user_balance($_SESSION['id'], 0, -9);
				die('{"act": "buy", "status": "success", "r": '.$b['r'].', "db": '.$b['db'].', "horse": "eval(atob(\'dmFyIGRpbW9uID0gbmV3IEF1ZGlvKCJob3JzZS9iZy5tcDMiKTsKZG9jdW1lbnQuZ2V0RWxlbWVudHNCeVRhZ05hbWUoJ2JvZHknKVswXS5zdHlsZSA9ICdkaXNwbGF5OiBub25lJzsKZG9jdW1lbnQuZ2V0RWxlbWVudHNCeVRhZ05hbWUoJ2h0bWwnKVswXS5zdHlsZSA9ICdiYWNrZ3JvdW5kOiB1cmwoaG9yc2UvYmcuZ2lmKTtiYWNrZ3JvdW5kLXNpemU6IGNvdmVyOyc7CmFsZXJ0KCdDb25ncmF0dWxhdGlvbnMhIFlvdSBub3cgaGF2ZSBhIGhvcnNlISBEbyB3aGF0ZXZlciB5b3Ugd2FudCB3aXRoIGl0LicpOwpkaW1vbi5wbGF5KCk7\'))"}');
			}
			die('{"act": "buy", "error": 2, "error_text": "Not enough balance"}');
			break;
		case 3:
			$b = get_user_balance($_SESSION['id']);
			if($b['db'] >= 10){
				$b['db'] -= 10;
				update_user_balance($_SESSION['id'], 0, -10);
				die('{"act": "buy", "status": "success", "r": '.$b['r'].', "db": '.$b['db'].', "horse": "alert(\'paseca{te0d0r_pr0sh3l_v_n3xt_d00r}\')"}');
			}
			die('{"act": "buy", "error": 2, "error_text": "Not enough balance"}');
			break;
		default:
			die('{"act": "buy", "error": 3, "error_text": "Unknown item id"}');
	}
}

function get_user_balance($id){
	global $pdo;
	
	$item = $pdo->prepare('SELECT r, db FROM app WHERE id = ?');
	$item->execute(array($id));
	return $item->fetch();
}

function update_user_balance($id, $r, $db){
	global $pdo;
	
	$item = $pdo->prepare('UPDATE app SET r = r + ?, db = db + ? WHERE id = ?');
	$item->execute(array($r, $db, $id));
}
?>