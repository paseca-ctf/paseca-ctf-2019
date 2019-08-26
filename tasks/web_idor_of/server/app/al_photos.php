<?php
if(isset($_POST['al']) && (int)$_POST['al'] === 1){
    $host = 'mysql';
    $db   = 'paseca';
    $user = 'root';
    $pass = 'p4s3c4';
    $charset = 'utf8';

    $dsn = "mysql:host=$host;dbname=$db;charset=$charset";
    $opt = [
        PDO::ATTR_ERRMODE            => PDO::ERRMODE_EXCEPTION,
        PDO::ATTR_DEFAULT_FETCH_MODE => PDO::FETCH_ASSOC,
        PDO::ATTR_EMULATE_PREPARES   => false,
    ];
    $pdo = new PDO($dsn, $user, $pass, $opt);
	
	if(isset($_POST['pid'])){
		$not_allowed = $pdo->query('SELECT id FROM img WHERE allowed = 0');
		$not_allowed = $not_allowed->fetchAll(PDO::FETCH_COLUMN, 0);
		
		if(in_array($_POST['pid'], $not_allowed)){
			echo '{"error": 20, "error_text": "Access Denied"}';
		} else {
			$pid = $_POST['pid'];
			$item = $pdo->prepare('SELECT src FROM img WHERE id = ?');
			$item->execute(array(kphp_intval($pid)));
			
			$data = $item->fetchAll();
			
			if(sizeof($data) == 0){
				echo '{"error": 22, "error_text": "Unknown Error"}';
			} else {
				echo '{"status": "success", "src": "'.$data[0]['src'].'"}';
			}
		}
	}
}
?>
