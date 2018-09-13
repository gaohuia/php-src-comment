<?php

$a = 1;
if ($a == 1) {
	$a += 1;
} else {
	$a += 2;
}

function b()
{
	return 1;
}

return "hello world {$a} {$a} {$a}";