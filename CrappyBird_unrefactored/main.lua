-- Bird0: render background and ground to the screen
-- Bird1: parallax scrolling, the mountain from far behind moving slower than the ground near us
-- Bird2: Render the bird
-- Bird3: Gravity added
-- Bird4: Anti-gravity added
WINDOW_WIDTH = 1280
WINDOW_HEIGHT = 720
VIRTUAL_WIDTH = 512
VIRTUAL_HEIGHT = 288
push = require 'push'
Class = require 'class'
require 'Bird'
require 'Pipe'
local background = love.graphics.newImage('background.png')
local ground = love.graphics.newImage('ground.png')
local backgroundX = 0 
local groundX = 0
local BACKGROUND_SCROLLING_SPEED = 30
local score = 0
GROUND_SCROLLING_SPEED = 100
local BACKGROUND_LOOPING_POINT = 413 -- depend on each image
game_state = 'start'
pipes = {}
unscored_pipes = {}
pipe_spawn_timer = 0
function love.load()
    instruction_Font = love.graphics.newFont('font.ttf', 16)
    score_Font = love.graphics.newFont('score.ttf', 18)
    love.graphics.setDefaultFilter('nearest', 'nearest')
    love.window.setTitle('Crappy Bird')
    push:setupScreen(VIRTUAL_WIDTH, VIRTUAL_HEIGHT, WINDOW_WIDTH, WINDOW_HEIGHT, {
        vsync = true,
        fullscreen = false,
        resizable = true
    })
    bird = Bird()
    love.keyboard.isPressed = {}
    sounds = {
        ['jump'] = love.audio.newSource('jump.wav', 'static'),
        ['hit'] = love.audio.newSource('hit.wav', 'static'),
        ['score'] = love.audio.newSource('score.wav', 'static'),
        ['music'] = love.audio.newSource('marios_way.mp3', 'static')
    }
    sounds['music']:setVolume(0.4)
    sounds['hit']:setVolume(0.4)
    sounds['jump']:setVolume(0.6)
    sounds['score']:setVolume(0.6)
    sounds['music']:setLooping(true)
    sounds['music']:play()
end

function love.resize(w, h)
    push:resize(w, h)
end

function love.keypressed(key)
    love.keyboard.isPressed[key] = true
    if key == 'escape' then
        love.event.quit()
    end
    if key == 'return' then
        pipe_spawn_timer = 2
        if game_state == 'start' then
            game_state = 'play'
        elseif game_state == 'fail' then
            game_state = 'start'
            -- pipes = {}
            -- unscored_pipes = {}
            -- bird:reset()
        end
    end
end
function love.keyboard.wasPressed(key)
    return love.keyboard.isPressed[key]
end
function love.update(dt)
    pipe_spawn_timer = pipe_spawn_timer + dt
    -- Stop scrolling background and ground and reset all stat when in fail state
    if game_state ~= 'fail' then
        backgroundX = (backgroundX + BACKGROUND_SCROLLING_SPEED*dt) % BACKGROUND_LOOPING_POINT
        groundX = (groundX + GROUND_SCROLLING_SPEED*dt) % VIRTUAL_WIDTH
    end
    if game_state == 'start' then
        pipes = {}
        unscored_pipes = {}
        bird:reset()
        score = 0
    end
    -- Gameplay logic
    if game_state == 'play' then
        bird:update(dt)
        love.keyboard.isPressed = {}
        -- Bird hits ground
        if (bird.y + bird.height > VIRTUAL_HEIGHT - 16) then
            game_state = 'fail'
            sounds['hit']:play()
        end
        -- Spawn a pipe after a period of time
        if pipe_spawn_timer > (math.random(17,27) / 10) then
            table.insert(pipes, Pipe())
            table.insert(unscored_pipes, pipes[table.maxn(pipes)])
            pipe_spawn_timer = 0
        end
        -- Loop all the pipes
        for k, pipe in pairs(pipes) do
            pipe:update(dt)
            -- Check score
            if (bird.x > unscored_pipes[1].x + unscored_pipes[1].width) then
                table.remove(unscored_pipes, 1)
                score = score + 1
                sounds['score']:play()
            end
            -- Check collision
            if bird:collisionDetection(pipe) then
                game_state = 'fail'
                sounds['hit']:play()
            end
            -- If the pipe goes pass the screen, remove it
            if pipe.x < -pipe.width then
                table.remove(pipes, k)
            end
        end
        
    end
    
end

function love.draw()
    push:start()
   
    -- render the scrolling background
    love.graphics.draw(background, -backgroundX, 0)
    -- render the scrolling ground
    love.graphics.draw(ground, -groundX, VIRTUAL_HEIGHT - 16)
    if game_state ~= 'fail' then
        -- Render bird
        bird:render()
        -- Render pipes
        
        for k, pipe in pairs(pipes) do
            pipe:render()
        end
        -- Print score
        love.graphics.setFont(score_Font)
        love.graphics.print('Score: ' .. tostring(score), 2, 2)
        -- render the scrolling ground
        love.graphics.draw(ground, -groundX, VIRTUAL_HEIGHT - 16)
    end
    if game_state == 'start' then
        love.graphics.setFont(instruction_Font)
        love.graphics.print('Press Enter', VIRTUAL_WIDTH/4 + 40, VIRTUAL_HEIGHT/4 + 20)
    end
    if game_state == 'fail' then
        love.graphics.setFont(instruction_Font)
        love.graphics.print('Press Enter to restart', VIRTUAL_WIDTH/4 - 50, VIRTUAL_HEIGHT/4 + 40)
        love.graphics.print('Your Score:' .. tostring(score), VIRTUAL_WIDTH/4 + 20, VIRTUAL_HEIGHT/4)

    end
    
    push:finish()
end