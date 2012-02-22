<?php include 'DB.php';
	
	header('content-type:text/html;charset=utf8');

	function initData() {
		$d = file('hzpy');
		$data = array();
		$i = 0;
		foreach ($d as $zpItem) {
			$t = explode(',', $zpItem);
			if(count($t) <= 4) {
				break;
			}else{
				$data[$t[0]][] = array('yin'=>$t[1],'shengmu'=>$t[2],'yunmu'=>$t[3]);
			}
		}
		
		return $data;
	}

	function getYinItems($str) {
		$data =	initData();
		$c = mb_strlen($str,"utf8");
		$y = array();
		for ($i=0;$i<$c;$i++) {
			$k = mb_substr($str, $i,1,"utf8");
			$y = (isset($data[$k]))?$data[$k]:array(array('yin'=>$k,'shengmu'=>$k,'yunmu'=>$k));
		}
		return $y;
	}
	 
	function combineItems($i,$j) {
		$c = array();
		foreach ($i as $m) {
			foreach ($j as $n) {
				$c[] = array('yin'=>$m['yin'].$n['yin'],'sm'=>$m['sm'].$n['sm']);
			}
		}
		return $c;
	}
	
	function getPinyin($str){
		$str = strtolower($str);
		$items = getYinItems($str);
		$k[] = array('yin'=>'','sm'=>'');
		foreach ($items as $c) {
			$k = combineItems($k, $c);
		}
		return $k;
	}
	
	
	if(isset($_POST['action'])) {
		$hz = $_POST['hanzi'];
		$did = $_POST['id'];
		$py = getPinyin($hz);
		foreach ($py as $i) {
			$d = new DB();
			$d->insert('pinyin', array('pinyin'=>$i['yin'],'hanzi'=>$hz,'did'=>$did));
			$d->insert('sm', array('sm'=>$i['sm'],'hanzi'=>$hz,'did'=>$did));
		}
	}
	
	
	function query($py) {
	   $py = strtolower($py);
	   $d = new DB();
	   var_dump($d->getItems('pinyin', 'wode'));
	}
	
	
	$msg = "的";
	echo "要查询的字：" . $msg . "<p>";
	
	echo "PHP扩展写的拼音查询，获得一个汉字的注音元素：<br>";
	echo "<br>当前内存消耗：".memory_get_usage()."<br>";
	$s = microtime(true);
	print_r(tmpy_get_pyitem($msg));	
	$d = microtime(true) - $s;
	echo "<br>当前内存消耗：".memory_get_usage()."<br>";
	echo "<br>耗时：".$d*1000 . "ms<br>";
	
	echo "PHP写的拼音查询，获得一个汉字的注音元素：<br>";
	echo "<br>当前内存消耗：".memory_get_usage()."<br>";
	$s = microtime(true);
	print_r(getYinItems($msg));
	$d = microtime(true) - $s;
	echo "<br>当前内存消耗：".memory_get_usage()."<br>";
	echo "耗时：".$d*1000 . "ms<br><p>";
	

	
?>

