(function (global) {
    global.document.addEventListener('DOMContentLoaded', function () {
        const toggle = global.document.getElementById('dark-mode-toggle');
    
        if (localStorage.getItem('dark-mode')) {
            toggle.innerHTML = '<i class="fa-regular fa-sun"></i>';
        }
        else {
            toggle.innerHTML = '<i class="fa-regular fa-moon"></i>';
        }
    
        toggle.addEventListener('click', function () {
            if (global.document.documentElement.classList.contains('dark-mode')) {
                global.document.documentElement.classList.remove('dark-mode');
                localStorage.removeItem('dark-mode');
                toggle.innerHTML = '<i class="fa-regular fa-moon"></i>';
            }
    	else {
                global.document.documentElement.classList.add('dark-mode');
                localStorage.setItem('dark-mode', 'on');
                toggle.innerHTML = '<i class="fa-regular fa-sun"></i>';
            }
        });
    });
}) (globalThis);
