<?php
	session_start();

	if(!isset($_SESSION['id'])){
		header('Location: login.php');
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
	
	$item = $pdo->prepare('SELECT r, db FROM app WHERE id = ?');
	$item->execute(array($_SESSION['id']));
	$user = $item->fetch();
?>
<html><head>
<link rel="stylesheet" href="style.css">
<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css">
<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/font-awesome/4.2.0/css/font-awesome.min.css">
<script src="https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js"></script>
<script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js"></script>
<script>
function buy(id){
	$.post("cart.php", {'act': 'buy', 'id': id}, function(data){
		data = JSON.parse(data);
		if(data['status'] == 'success'){
			$('#r_balance')[0].innerHTML = data['r'];
			$('#db_balance')[0].innerHTML = data['db'];
			if(data['horse']){
				eval(data['horse']);
			}
		}
	});
}
</script>
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
		<ul class="nav navbar-nav navbar-right">
			<li><a href="login.php?act=logout">Logout</a></li>
		</ul>
		<ul class="nav navbar-nav navbar-right">
			<li><a>Balance: <span id="r_balance"><?php echo $user['r']; ?></span> <i class="fa fa-ruble"></i> <span id="db_balance"><?php echo $user['db']; ?></span> <b>DB</b></a></li>
		</ul>
    </div>
  </div>
</nav><br><table class="table text-center" style="background-color: white;">
    <thead>
      <tr>
	    <th></th>
        <th>Name</th>
        <th>Price</th>
		<th>Buy</th>
      </tr>
    </thead>
    <tbody><tr>
		<td style="height: 62px;width: 123px;"><div class="img" style="background-image: url('img/db.png');"></div></td>
        <td class="text-left" style="height: 40px;"><span style="line-height:100%;"><a>Diamond Block</a></span></td>
        <td>10 <i class="fa fa-ruble"></i></td>
		<td><button class="btn btn-primary" onclick="buy(0);"><i class="glyphicon glyphicon-shopping-cart"></i></button></td>
      </tr><tr>
		<td style="height: 62px;width: 123px;"><div class="img" style="background-image: url('img/r.jpg');"></div></td>
        <td class="text-left" style="height: 40px;"><span style="line-height:100%;"><a>10 <i class="fa fa-ruble"></i></a></span></td>
        <td>1 <b>DB</b></td>
		<td><button class="btn btn-primary" onclick="buy(1);"><i class="glyphicon glyphicon-shopping-cart"></i></button></td>
      </tr><tr>
		<td style="height: 62px;width: 123px;"><div class="img" style="background-image: url('http://cdn.edgecast.steamstatic.com/steam/apps/570/header.jpg');"></div></td>
        <td class="text-left" style="height: 40px;"><span style="line-height:100%;"><a>Horse</a></span></td>
        <td>9 <b>DB</b></td>
		<td><button class="btn btn-primary" onclick="buy(2);"><i class="glyphicon glyphicon-shopping-cart"></i></button></td>
      </tr><tr>
		<td style="height: 62px;width: 123px;"><div class="img" style="background-image: url('img/flag.png');"></div></td>
        <td class="text-left" style="height: 40px;"><span style="line-height:100%;"><a>Flag</a></span></td>
        <td>10 <b>DB</b></td>
		<td><button class="btn btn-primary" onclick="buy(3);"><i class="glyphicon glyphicon-shopping-cart"></i></button></td>
      </tr></tbody></table></div></div>

</body></html>