#!/usr/bin/php
<?php
if ($argc <> 1) {
	echo "Fail. It needs to be read into standard input";
	exit(0);
}

function is_command($str)
{
	if ($str === "##start")
		return (true);
	else if ($str === "##end")
		return (true);
	return (false);
}

$stdin = fopen('php://stdin', 'r');
while ($line = fgets($stdin)) {
	$file[] = $line;
}

foreach ($file as $line) {
	if (preg_match("/^([0-9]+)$/", $line, $nb))
		$nbants = $nb[0];
	if (preg_match("/(.+) (-?[0-9]+) (-?[0-9]+)/", $line, $room))
		$rooms[] = $room;
	if (preg_match("/^(\w+)-(\w+)$/", $line, $tube))
		$tubes[] = $tube;
	if (preg_match_all("/L(\w+)-(\w+)/", $line, $ant))
		$ants[] = $ant;
}

$start = false;
$end = false;

foreach ($file as $line) {
	if ($line === "##start\n")
		$start = true;
	if ($line === "##end\n")
		$end = true;
	if (preg_match("/(.+) (-?[0-9]+) (-?[0-9]+)/", $line, $room)) {
		if ($start) {
			if (in_array($room, $rooms)) {
				$i = 0;
				foreach ($rooms as $elem) {
					if ($elem === $room)
						$rooms[$i][] = "s";
						++$i;
				}
			}
		}
		if ($end) {
			if (in_array($room, $rooms)) {
				$i = 0;
				foreach ($rooms as $elem) {
					if ($elem === $room)
						$rooms[$i][] = "e";
					++$i;
				}
			}
		}
		$end = false;
		$start = false;
	}
}

$x = 0;
$y = 0;

foreach ($rooms as $cell) {
	if ($cell[2] > $x)
		$x = $cell[2];
	if ($cell[3] > $y)
		$y = $cell[3];
}

//var_dump($nbants);
//var_dump($rooms);
//var_dump($tubes);
//var_dump($ants);

?>
