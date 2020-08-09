const { test } = require('uvu');
const assert = require('uvu/assert');

const { listOpenWindows } = require('.');


test('listWindows()', () => {
    const openWindows = listOpenWindows();

    console.log(openWindows);

    assert.equal(Array.isArray(openWindows), true);

    for (const window of openWindows) {
        assert.type(window.handle, 'number');
        assert.type(window.className, 'string');
        assert.type(window.caption, 'string');
        assert.type(window.processId, 'number');
        assert.type(window.processPath, 'string');
    }
});

test.run();
