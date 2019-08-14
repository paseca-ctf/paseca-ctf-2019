<?php
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
	
	$allowed = $pdo->query('SELECT id, src FROM img WHERE allowed = 1');
	
	$allowed = $allowed->fetchAll();
?>

<head>
	<link rel="stylesheet" href="style.css">
	<script src="https://ajax.googleapis.com/ajax/libs/jquery/2.1.3/jquery.min.js"></script>
	<script>
		function show(id){
			document.location.hash = '__';
			$.post("al_photos.php", {'al': 1, 'pid': id}, function(data){
				data = JSON.parse(data);
				$('#showbox')[0].innerHTML = '<a href="#_" class="lightbox trans" id="img"><img src="img/' + data['src'] + '"></a>';
				setTimeout(function(){document.location.hash = 'img';}, 500);
			});
		}
	</script>
</head>
<div class="container">
	<div class="top">
    	<ul>
			<?php
				foreach($allowed as $img){
					echo '<li><img src="'.file_get_contents('img/'.$img['src'].'.previ1').'" onclick="show('.$img['id'].')"></li>';
				}
			?>
        </ul>
		<div id="showbox">
		</div>
    </div>
</div>