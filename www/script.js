// ============================================================
//  webserv — validation suite
// ============================================================

// --- Show the host:port serving this page, next to the brand.
(function () {
    var host = document.getElementById('host');
    if (host) host.textContent = window.location.host || 'localhost';
})();

// --- Live health check: ping the server, flip the antenna red if it stops answering.
(function () {
    var el = document.getElementById('health');
    var text = document.getElementById('health-text');
    if (!el || !text) return;

    function setState(state, label) {
        el.className = 'health ' + state;
        text.innerText = label;
    }

    function ping() {
        var ctrl = new AbortController();
        var timer = setTimeout(function () {
            ctrl.abort();
        }, 3000);
        fetch('/favicon.svg?_=' + Date.now(), {method: 'GET', cache: 'no-store', signal: ctrl.signal})
            .then(function () {
                setState('online', 'online');
            })
            .catch(function () {
                setState('offline', 'offline');
            })
            .finally(function () {
                clearTimeout(timer);
            });
    }

    ping();
    setInterval(ping, 2000);
})();

// --- Visit counter: GET the cookie CGI in place, read back the Set-Cookie value.
function visitCounter(outId) {
    var out = document.getElementById(outId);
    out.className = 'out';
    out.innerText = 'GET /cgi-bin/cookie.py ...';
    fetch('/cgi-bin/cookie.py', {cache: 'no-store'})
        .then(function (res) {
            if (!res.ok) throw new Error('HTTP ' + res.status);
            // The server just sent Set-Cookie: visits=N — read it back from the jar.
            var m = document.cookie.match(/(?:^|;\s*)visits=(\d+)/);
            var n = m ? m[1] : '?';
            out.className = 'out ok';
            out.innerText = 'HTTP ' + res.status + '   Set-Cookie: visits=' + n + '   → visited ' + n + '× this session';
        })
        .catch(function (err) {
            out.className = 'out err';
            out.innerText = 'error: ' + err.message;
        });
}

// --- DELETE requests, with the response printed to an inline output line.
function sendDelete(url, outId) {
    var out = document.getElementById(outId);
    out.className = 'out';
    out.innerText = 'DELETE ' + url + ' ...';
    fetch(url, {method: 'DELETE'})
        .then(function (res) {
            out.className = 'out ' + (res.ok ? 'ok' : 'err');
            out.innerText = 'HTTP ' + res.status + ' ' + res.statusText + '   ' + url;
        })
        .catch(function (err) {
            out.className = 'out err';
            out.innerText = 'network error: ' + err;
        });
}
