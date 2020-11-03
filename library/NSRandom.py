class NSRandom:
    mSeed1 = 0x00000000
    mSeed2 = 0x00000000
    mSeed3 = 0x00000000
    mSeed4 = 0x00000000

    def __init__(self):
        pass

    def init(self, seed):
        self.mSeed1 = 0xFFFFFFFF & (0x6C078965 * (seed ^ (seed >> 30)) + 1)
        self.mSeed2 = 0xFFFFFFFF & (0x6C078965 * (self.mSeed1 ^ (self.mSeed1 >> 30)) + 2)
        self.mSeed3 = 0xFFFFFFFF & (0x6C078965 * (self.mSeed2 ^ (self.mSeed2 >> 30)) + 3)
        self.mSeed4 = 0xFFFFFFFF & (0x6C078965 * (self.mSeed3 ^ (self.mSeed3 >> 30)) + 4)

    def getU32(self):
        n = self.mSeed1 ^ (0xFFFFFFFF & self.mSeed1 << 11)
        self.mSeed1 = self.mSeed2
        self.mSeed2 = self.mSeed3
        self.mSeed3 = self.mSeed4
        self.mSeed4 = (n ^ (n >> 8) ^ self.mSeed4 ^ (self.mSeed4 >> 19))
        
        return self.mSeed4