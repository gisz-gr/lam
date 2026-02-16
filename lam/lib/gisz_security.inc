<?php

namespace GISZ;

/**
 * REMOTE_ADDR Replacement to ensure always real client address behind proxy chain.
 *
 * @return string
 */
function getRemoteAddr(): string {
	return getClientIP()[0];
}

/**
 * Returns the client IP and comma separated proxy IPs if any (HTTP_X_FORWARDED_FOR, HTTP_X_REAL_IP).
 *
 * @return String client IP (e.g. 10.10.10.10,11.11.11.11)
 */
function getClientIPForLogging(): string {
	return implode(',', getClientIP());
}

/**
 * Returns an array with client IP as first element and proxy IPs if any (HTTP_X_FORWARDED_FOR, HTTP_X_REAL_IP).
 *
 * @see https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/X-Forwarded-For
 *
 * @return array client IP and proxy IPs. Contains always at least one element.
 */
function getClientIP(): array {
	$ipList = [];
	if ( ! empty($_SERVER['HTTP_X_REAL_IP'])) {
		$ipList[] = $_SERVER['HTTP_X_REAL_IP'];
	}
	if ( ! empty($_SERVER['HTTP_X_FORWARDED_FOR'])) {
		$ipList += array_map(trim(...), explode(',', $_SERVER['HTTP_X_FORWARDED_FOR']));
	}
	if ( ! empty($_SERVER['REMOTE_ADDR'])) {
		$ipList[] = $_SERVER['REMOTE_ADDR'];
	}
	$ipList = array_unique($ipList);
	if (empty($ipList)) {
		return [''];
	}

	return $ipList;
}