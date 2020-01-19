Bird = Class{}

local GRAVITY = 18
FLY_STEP = GRAVITY * 5
local image_selector = 0
local timer = 0
function Bird:init()
    self.velocity = 0
    self.mid_flap = love.graphics.newImage('bird-midflap.png')
    self.up_flap = love.graphics.newImage('bird-upflap.png')
    self.down_flap = love.graphics.newImage('bird-downflap.png')
    self.width = self.mid_flap:getWidth()
    self.height = self.mid_flap:getHeight()
    self.x = VIRTUAL_WIDTH / 2 - self.width / 2
    self.y = VIRTUAL_HEIGHT / 2 - self.height / 2
end

function Bird:update(dt)
    -- bird will go up for a little while and then go down
    -- use a dictionary to keep track of the pressed keys in last frame
    -- if i simply use love.keyboard.isDown, the longer i press the key, the longer the bird will fly up
    -- and that's not the gameplay we want
    timer = timer + dt
    if timer > 0.1 then
        image_selector = (image_selector + 1) % 3
        timer = 0
    end
    if love.keyboard.wasPressed('up') or love.keyboard.wasPressed('space') then
        self.velocity = -5
        sounds['jump']:play()
    else
        self.velocity = self.velocity + GRAVITY*dt
    end
    self.y = self.y + self.velocity
end
function Bird:reset()
    self.velocity = 0
    --self.mid_flap = love.graphics.newImage('bird.png')
    self.width = self.mid_flap:getWidth()
    self.height = self.mid_flap:getHeight()
    self.x = VIRTUAL_WIDTH / 2 - self.width / 2
    self.y = VIRTUAL_HEIGHT / 2 - self.height / 2
end
function Bird:render()
    if image_selector == 1 then
        love.graphics.draw(self.up_flap, self.x, self.y)
    elseif image_selector == 2 then
        love.graphics.draw(self.mid_flap, self.x, self.y)
    else
        love.graphics.draw(self.down_flap, self.x, self.y)
    end
    --love.graphics.print(tostring(self.y), 0, 0)
end

function Bird:collisionDetection(object)
    -- return false
    if (self.x + self.width < object.x + 1 or self.x > object.x + object.width - 1) or (self.y > object.y - BLANK_SPACE and self.y + self.height < object.y ) then
        return false
    else
        return true
    end
end