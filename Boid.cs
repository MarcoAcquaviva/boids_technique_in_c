using Aiv.Fast2D;
using OpenTK;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Boids
{
    class Boid
    {
        Sprite sprite;
        Texture texture;
        float speed = 150;
        float alignRadius = 200;
        float cohesionRadius = 300;
        float separationRadius = 70;

        float sightHalfAngle = MathHelper.DegreesToRadians(150);

        float cohesionWeight = 1.0f;
        float separationnWeight = 8.0f;
        float alignmentWeight = 1.0f;

        float steerMult = 4.0f;

        public Vector2 Velocity;

        public Vector2 Position { get { return sprite.position; } set { sprite.position = value; } }

        public Vector2 Forward
        {
            get { return new Vector2((float)Math.Cos(sprite.Rotation), (float)Math.Sin(sprite.Rotation)); } // view direction

            set { sprite.Rotation = (float)Math.Atan2(value.Y, value.X); }
        }


        public Boid(Vector2 position)
        {
            texture = new Texture("Assets/boid.png");
            sprite = new Sprite(texture.Width, texture.Height);
            sprite.pivot = new Vector2(sprite.Width * 0.5f, sprite.Height * 0.5f);

            sprite.position = position;

            float randomX = RandomGenerator.GetRandomFloat() * (RandomGenerator.GetRandom(0, 2) == 0 ? -1.0f : 1.0f);
            float randomY = RandomGenerator.GetRandomFloat() * (RandomGenerator.GetRandom(0, 2) == 0 ? -1.0f : 1.0f);
            Velocity = new Vector2(randomX, randomY).Normalized() * speed;
            //Velocity = new Vector2(RandomGenerator.GetRandomFloat() , RandomGenerator.GetRandomFloat() ).Normalized() * speed;

            //Console.WriteLine((float)Math.Sign(RandomGenerator.GetRandom(-2, 2)));
        }

        protected virtual bool IsVisible(Vector2 point, float radius, float halfAngle, out Vector2 distance)
        {
            distance = point - Position;

            if (distance.Length <= radius)
            {
                float angle = (float)Math.Acos(Vector2.Dot(Forward, distance.Normalized()));
                if (angle <= halfAngle)
                {
                    return true;
                }
            }

            return false;
        }

        protected virtual Vector2 GetAlignment()
        {
            Vector2 v = new Vector2(0, 0);
            int count = 0;

            for (int i = 0; i < Program.Boids.Count; i++)
            {
                Boid b = Program.Boids[i];

                if (b != this)
                {
                    Vector2 dist;// = b.Position - Position;
                    if (IsVisible(b.Position,alignRadius, MathHelper.Pi, out dist))
                    {
                        v += b.Velocity;
                        count++;
                    }
                }
            }

            if (count > 0)
            {
                v /= count;
                if (v.Length != 0)
                {
                    v = v.Normalized() * speed;
                }

                //Velocity = Vector2.Lerp(Velocity, v, Program.Win.deltaTime*10);
            }

            return v;
        }

        protected virtual Vector2 GetCohesion()
        {
            Vector2 v = new Vector2(0, 0);
            int count = 0;

            for (int i = 0; i < Program.Boids.Count; i++)
            {
                Boid b = Program.Boids[i];

                if (b != this)
                {
                    Vector2 dist;// = b.Position - Position;
                    if (IsVisible(b.Position, cohesionRadius, MathHelper.Pi, out dist))
                    {
                        v += b.Position;
                        count++;
                    }
                }
            }

            if (count > 0)
            {
                v /= count;

                Vector2 distToCenter = v - Position;

                v = distToCenter.Normalized() * speed;

                //Velocity = Vector2.Lerp(Velocity, v, Program.Win.deltaTime * 5);
            }

            return v;
        }

        protected virtual Vector2 GetSeparation()
        {
            Vector2 v = new Vector2(0, 0);
            int count = 0;

            for (int i = 0; i < Program.Boids.Count; i++)
            {
                Boid b = Program.Boids[i];

                if (b != this)
                {
                    Vector2 dist;// = b.Position - Position;
                    if (IsVisible(b.Position, separationRadius, sightHalfAngle, out dist))
                    {
                        v += dist;
                        count++;
                    }
                }
            }

            if (count > 0)
            {
                v /= count;
                v = -v.Normalized() * speed;

                //Velocity = Vector2.Lerp(Velocity, v, Program.Win.deltaTime * 10);
                //sprite.SetMultiplyTint(1, 0, 0, 1);
            }
            else
            {
                //sprite.SetMultiplyTint(1, 1, 1, 1);
            }

            return v;
        }

        public virtual void Update()
        {

            if (Program.Target != Vector2.Zero)
            {
                alignmentWeight = 0;
                cohesionWeight = 0;
                Vector2 targetDist = Program.Target - Position;
                if (targetDist.Length > 200.0f)
                {
                    Velocity = (targetDist).Normalized() * speed;
                }
                else
                {
                    Velocity = Vector2.Zero;
                }
            }

            Vector2 alignment = GetAlignment() * alignmentWeight;
            Vector2 cohesion = GetCohesion() * cohesionWeight;
            Vector2 separation = GetSeparation() * separationnWeight;

            Vector2 result = Vector2.Zero;
            result.X += alignment.X + cohesion.X + separation.X;
            result.Y += alignment.Y + cohesion.Y + separation.Y;

            if (result != Vector2.Zero /*&& Velocity != Vector2.Zero*/)
            {
                result = result.Normalized();
                //float angle = (float)Math.Acos(Vector2.Dot(result, Velocity.Normalized()));
                //if (angle > 0.0f)
                {
                    Velocity = Vector2.Lerp(Velocity, result * speed, Program.Win.deltaTime * steerMult);
                    Velocity = Velocity.Normalized() * speed;
                }
            }

            Position += Velocity * Program.Win.deltaTime;

            //if (float.IsNaN(Position.X))
            //{
            //    Console.WriteLine("NaN");
            //}


            //Pacman effect
            if (sprite.position.X - sprite.Height >= Program.Win.Width)
            {
                sprite.position.X = 0;
            }
            else if (sprite.position.X + sprite.Height < 0)
            {
                sprite.position.X = Program.Win.Width;
            }

            if (sprite.position.Y - sprite.Height >= Program.Win.Height)
            {
                sprite.position.Y = 0;
            }
            else if (sprite.position.Y + sprite.Height < 0)
            {
                sprite.position.Y = Program.Win.Height;
            }

            //Console.WriteLine(Velocity.Length);

            //Vector2 delta = Velocity * Program.Win.deltaTime;
            //Vector2 newPos = sprite.position + delta;
            //Vector2 projectedPos = newPos + Velocity.Normalized() * sprite.Height;
            //if (projectedPos.Y < 0 || projectedPos.Y > Program.Win.Height)
            //{
            //    Velocity.Y = -Velocity.Y;
            //}
            //else if (projectedPos.X < 0 || projectedPos.X > Program.Win.Width)
            //{
            //    Velocity.X = -Velocity.X;
            //}
            //else
            //{
            //    sprite.position = newPos;
            //}

            if(Velocity.Length>0)
                sprite.Rotation = (float)Math.Atan2(Velocity.Y, Velocity.X);
        }

        public virtual void Draw()
        {
            sprite.DrawTexture(texture);
        }
    }
}
