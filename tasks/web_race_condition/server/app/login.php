<?php
	session_start();
	
	if(isset($_GET['act'])){
		if($_GET['act'] === 'logout'){
			session_destroy();
			die(header('Location: login.php'));
		}
	}
	
	if(isset($_SESSION['id'])){
		die(header('Location: index.php'));
	}
	
	$mbox = '';
	$boxid = 0;
	
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
	
	if(isset($_POST['act'])){
		if($_POST['act'] === 'login' && isset($_POST['login']) && isset($_POST['pass'])){
			$item = $pdo->prepare('SELECT id FROM app WHERE username = ? and password = ?');
			$item->execute(array($_POST['login'], $_POST['pass']));
			
			$user = $item->fetch();
			
			if(isset($user['id']) && $user['id'] > 0){
				$_SESSION['id'] = $user['id'];
				die(header('Location: index.php'));
			} else {
				error('Wrong username or password', 1);
			}
		}
		if($_POST['act'] === 'register' && isset($_POST['login']) && isset($_POST['pass'])){
			$item = $pdo->prepare('SELECT id FROM app WHERE username = ?');
			$item->execute(array($_POST['login']));
			if(sizeof($item->fetchAll()) === 0){
				if(preg_match('/^[a-z0-9]*$/i', $_POST['login']) && preg_match('/^[a-z0-9]*$/i', $_POST['pass'])){
					if(strlen($_POST['login']) >= 10 && strlen($_POST['login']) <= 20){
						if(strlen($_POST['pass']) >= 6 && strlen($_POST['pass']) <= 20){
							if($_POST['pass'] !== $_POST['login']){
								$item = $pdo->prepare('INSERT INTO app (username, password, r, db) VALUES (?, ?, 90, 0)');
								$item->execute(array($_POST['login'], $_POST['pass']));
								
								notify('Successfully registered! You may login now.', 2);
							} else {
								error('Username and password cannot be equal!', 2);
							}
						} else {
							error('Password must be from 6 to 20 characters long!', 2);
						}
					} else {
						error('Username must be from 10 to 20 characters long!', 2);
					}
				} else {
					error('Username or password contains restricted characters. Only A-Z, a-z, 0-9 are allowed.', 2);
				}
			} else {
				error('This username is already registered!', 2);
			}
		}
	}
	
	function error($text, $box){
		global $boxid;
		global $mbox;
		
		$boxid = $box;
		$mbox = '<div class="box error">'.$text.'</div>';
	}
	
	function notify($text, $box){
		global $boxid;
		global $mbox;
		
		$boxid = $box;
		$mbox = '<div class="box notify">'.$text.'</div>';
	}
?>

<html><head>
<link rel="stylesheet" href="style.css">
<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css">
<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/font-awesome/4.2.0/css/font-awesome.min.css">
<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js"></script>
<script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js"></script>
</head>
<body style="background-color: #eee;">
<div class="container">
<div class="jumbotron">
<nav class="navbar navbar-default navbar-fixed-top">
  <div class="container">
    <div class="navbar-header">
      <button type="button" class="navbar-toggle" data-toggle="collapse" data-target="#navbar">
        <span class="icon-bar"></span>
        <span class="icon-bar"></span>
        <span class="icon-bar"></span> 
      </button>
      <a class="navbar-brand" href="#">Horse Bank</a>
    </div>
    <div class="collapse navbar-collapse" id="navbar">
      <ul class="nav navbar-nav navbar-center">
        <li><a href="/">Home</a></li>
      </ul>
    </div>
  </div>
</nav><br><form class="loginform" action="?" method="POST" style="margin:0">
	<p><b>Sign In</b></p>
	<?php
		if($boxid === 1){
			echo $mbox;
		}
	?>
	<input type="hidden" name="act" value="login">
	<div class="form-group"><label for="login">Username: </label><input id="login" type="text" name="login" class="form-control" required></div>
	<div class="form-group"><label for="pass">Password: </label><input id="pass" type="password" name="pass" class="form-control" required></div>
	<br><button class="btn btn-primary" type="sumbit">Sign In</button></form>
	<br>
	<form class="loginform" action="?" method="POST" style="margin:0">
	<p><b>Sign Up</b></p>
	<?php
		if($boxid === 2){
			echo $mbox;
		}
	?>
	<input type="hidden" name="act" value="register">
	<div class="form-group"><label for="login">Username: </label><input id="login" type="text" name="login" class="form-control" required></div>
	<div class="form-group"><label for="pass">Password: </label><input id="pass" type="password" name="pass" class="form-control" required></div>
	<br><button class="btn btn-primary" type="sumbit">Sign Up</button></form></div>
</div>
</body></html>