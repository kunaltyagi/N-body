

namespace local {

	#define particleMass 1
	#define particleRadius 1


	class Point{
		public:
		double x;
		double y;
        double z;

		Point();
		Point operator -(Point P);
		Point operator -();
		Point operator +(Point P);
		double operator *(Point P); //dot product
		double operator ^(Point P);	//cross product
		double operator *(double k);
		void operator =(Point P);


		double modulo();


	};




  class Vector {
	  public:
	  double x;
	  double y;
      double z;
	  Vector (double a, double b, double z);
	  void  operator =(Vector P);
	  double length();
	  };





	class Particle{
		private:
		double _mass;
		Point _position;
		Vector _velocity;
		Vector _acceleration;
		double _radius;

		public:

		Particle();
		Particle(double mass = particleMass, double velocity =0 , double acceleration = 0, double radius=particleRadius , double position);
		Point getPosition();
		double move(double t);
		double getVelocity();
		void updateVelocity(double velocity);
		void updateAcceleration(double acceleration);
		void updatePosition(Point point);
		void addCoordinates(Point point);

		double getAcceleration();
		double getRadius();

	};

	class System{
		private:
		vector<Particle> _particles;
		double _simTime;
		double _probeInterval;
		int _NoOfParticles;

		public:





	};





//end of namespace local
}




