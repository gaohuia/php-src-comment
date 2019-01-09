<?php

error_reporting(E_ALL);
ini_set('display_errors', true);

$exists = class_exists('fucker');

var_dump($exists);

$fucker = new fucker();
echo $fucker->getName();


