Pipe = Class{}
PIPE_SCROLLING = -100
BLANK_SPACE = FLY_STEP - 5
local PIPE_IMAGE = love.graphics.newImage('pipe.png')
function Pipe:init()
    self.x = VIRTUAL_WIDTH
    self.y = math.random(120,220)
    self.width = PIPE_IMAGE:getWidth()
    self.height = PIPE_IMAGE:getHeight()
end

function Pipe:update(dt)
    self.x = self.x + PIPE_SCROLLING*dt
end

function Pipe:render()
    love.graphics.draw(PIPE_IMAGE, self.x, self.y)
    love.graphics.draw(PIPE_IMAGE, self.x + self.width, self.y - BLANK_SPACE, math.pi)
end